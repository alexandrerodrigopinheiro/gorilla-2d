#include "../../includes/crypto/crypto.h"

std::string g2d::crypto::show_uuid(const char* devname)
{
#if defined(__linux__) || defined(__linux) || defined(linux)
	blkid_probe pr = blkid_new_probe_from_filename(devname);

	if (!pr)
	{
		// err(2, "Failed to open %s", devname);
		std::cerr << "Failed to open :" << devname << std::endl;

		return "";
	}

	blkid_do_probe(pr);

	const char *uuid;
	int ret = blkid_probe_lookup_value(pr, "UUID", &uuid, NULL);

	if (ret < 0)
	{
		return "";
	}

	std::string result = uuid;
	blkid_free_probe(pr);
#else
	g2d::basic::unused(devname);
	std::string result = "";
#endif
	return result;
}

bool g2d::crypto::serial(struct hd_driveid* hd, const char* devname)
{
#if defined(__linux__) || defined(__linux) || defined(linux)
	int fd = open(devname, O_RDONLY | O_NONBLOCK);

	if (fd < 0)
	{
		fprintf(stderr, "ERROR: Cannot open device %s\n", devname);
		return false;
	}

	if (ioctl(fd, HDIO_GET_IDENTITY, hd) == 0)
	{
		// Success
		close(fd);
		return true;
	}
	else if (errno == -ENOMSG)
	{
		fprintf(stderr, "No hard disk identification information available\n");
	}
	else
	{
		perror("ERROR: HDIO_GET_IDENTITY");
	}

	close(fd);

	return false;
#else
	g2d::basic::unused(hd, devname);
	return false;
#endif
}

bool g2d::crypto::startup()
{
	CRYPTO_mem_ctrl(CRYPTO_MEM_CHECK_ON);
	OpenSSL_add_all_algorithms(); // Add all cipher and digest algorithms
	ERR_load_crypto_strings();
	ERR_load_OBJ_strings();
	return true;
}

void g2d::crypto::shutdown()
{
	ERR_free_strings(); // for ERR_load_crypto_strings
	EVP_cleanup(); // for OpenSSL_add_all_algorithms
	RAND_cleanup();
	CRYPTO_cleanup_all_ex_data();
}

bool g2d::crypto::seed_prng(void)
{
#if defined(_WIN32)
	char buffer[1024];
	// rtlgenrandom is provided by advapi32.dll on windows >= xp.
	// windows's rand_s() internally calls rtlgenrandom.
	// python's urandom() uses /dev/[u]random on unix-based systems and cryptgenrandom on windows systems.
	// crypto++ uses rtlgenrandom on windows.
	RtlGenRandom(&buffer, sizeof(buffer));
	RAND_add(buffer, sizeof(buffer), sizeof(buffer));
#elif defined(__linux__)
	// stick to /dev/urandom on linux, because /dev/random is blocking :-(
	RAND_load_file("/dev/urandom", 1024);
#else
	RAND_load_file("/dev/random", 1024);
#endif
	return true;
}

std::string g2d::crypto::bytes_to_hexstring(const uint8_t *bytes, size_t size)
{
	std::ostringstream ss;
	ss << std::hex << std::nouppercase << std::setfill('0');

	std::for_each(bytes, bytes+size, [&](int c)
		{
			ss << std::setw(2) << c;
		}
	);

	return ss.str();
}

std::string g2d::crypto::random_string(size_t size)
{
	unsigned char* buf = new unsigned char[size];
	int ret = RAND_bytes(buf, size);

	if (ret != 1)
	{
		delete buf;
		fprintf(stderr, "ERROR: %s\n", ERR_error_string(ERR_get_error(), NULL));

		return "";
	}

	std::string result = g2d::crypto::bytes_to_hexstring(buf, size);
	delete [] buf;

	return result;
}

std::string g2d::crypto::md5(const std::string& source)
{
	MD5_CTX ctx;
	MD5_Init(&ctx);
	MD5_Update(&ctx, source.c_str(), source.length());
	unsigned char digest[16];
	MD5_Final(digest, &ctx);

	return g2d::crypto::bytes_to_hexstring(digest, sizeof(digest));
}

std::string g2d::crypto::rot13(const std::string& source)
{
	std::string transformed;

	for (size_t i = 0; i < source.size(); ++i)
	{
		if (isalpha(source[i]))
		{
			if ((tolower(source[i]) - 'a') < 14)
			{
				transformed.append(1, source[i] + 13);
			}
			else
			{
				transformed.append(1, source[i] - 13);
			}
		}
		else
		{
			transformed.append(1, source[i]);
		}
	}

	return transformed;
}

std::string g2d::crypto::generate_user_pass(const std::string& uuid, const std::string& machine_pass)
{
	const std::string generated = g2d::crypto::md5(g2d::crypto::rot13(machine_pass) + uuid);
	const size_t length = generated.length();
	std::string result;

	// make the user-pass smaller by stripping-off 1 for each 4 bytes.
	// this will reduce the user-pass from 32 bytes to 24 bytes.
	for (size_t i = 0; i < length; i++)
	{
		if (i % 4)
		{
			result += generated[i];
		}
	}

	return result;
}

bool g2d::crypto::validate_user_pass(const std::string& uuid, const std::string& machine_pass, const std::string& user_pass)
{
	const std::string generated_user_pass = g2d::crypto::generate_user_pass(uuid, machine_pass);

	return generated_user_pass == user_pass;
}

bool g2d::crypto::is_empty_string(const char* str)
{
	return str == NULL || str[0] == '\0';
}

bool g2d::crypto::is_running_as_super_user(void)
{
	uid_t euid = geteuid();
	return euid == 0;
}

inline int force_ch_root(const char* dirname)
{
	if (g2d::crypto::is_empty_string(dirname))
	{
		fprintf(stderr, "Invalid chroot directory.\n");

		return -1;
	}

	if (!g2d::crypto::is_running_as_super_user())
	{
		fprintf(stderr, "Unable to chroot: not running as superuser\n");

		return -1;
	}

	if (chdir(dirname) != 0)
	{
		fprintf(stderr, "Unable to chdir to %s: %s\n", dirname, strerror(errno));

		return -1;
	}

	if (chroot(dirname) != 0)
	{
		fprintf(stderr, "Unable to chroot to %s: %s (Try using the absolute path)\n", dirname, strerror(errno));

		return -1;
	}

	return 0;
}

int g2d::crypto::drop_priv_perm(uid_t new_uid)
{
#if defined(__linux__) || defined(__linux) || defined(linux)
	uid_t ruid;
	uid_t euid;
	uid_t suid;

	// on linux one must use setresuid to permanently drop privileges.
	if (setresuid(new_uid, new_uid, new_uid) < 0)
	{
		return -1;
	}

	if (getresuid(&ruid, &euid, &suid) < 0)
	{
		return -1;
	}

	if (ruid != new_uid || euid != new_uid || suid != new_uid)
	{
		return -1;
	}
#else
	if (setuid(new_uid) < 0)
	{
		return -1;
	}

	if (geteuid() != new_uid)
	{
		return -1;
	}
#endif
	return 0;
}

int g2d::crypto::force_uid(const char *username)
{
	struct passwd *user;

	if (g2d::crypto::is_empty_string(username))
	{
		fprintf(stderr, "Invalid username provided for privileges dropping.\n");

		return -1;
	}

	if (!g2d::crypto::is_running_as_super_user())
	{
		fprintf(stderr, "Unable to force uid: not running as superuser\n");

		return -1;
	}

	user = getpwnam(username);

	if (user == NULL)
	{
		fprintf(stderr, "User %s doesn't exist\n", username);

		return -1;
	}

	if (g2d::crypto::drop_priv_perm(user->pw_uid) < 0)
	{
		fprintf(stderr, "Unable to setuid to %s: %s\n", username, strerror(errno));

		return -1;
	}

	return 0;
}


std::string g2d::crypto::encode_string(const std::string& data, const std::string& key)
{
	int value = 0;
	int index = 0;
	int max = key.size() - 1;
	std::string phrase;

	for (std::size_t i = 0; i < data.length(); i++)
	{
		value = static_cast<int>(data[i]) * static_cast<int>(key[index]);
		phrase += std::to_string(value) + (i == data.length() - 1 ? "" : " ");
		g2d::math::clamp(++index, 0, max);
	}

	return phrase;
}

std::string g2d::crypto::decode_string(const std::string& data, const std::string& key)
{
	int value = 0;
	int index = 0;
	int max = key.size() - 1;
	std::vector<int> ascii = g2d::basic::explode<int>(data, ' ');
	std::string phrase;

	for (std::size_t i = 0; i < ascii.size(); i++)
	{
		value = ascii[i] / static_cast<int>(key[index]);
		phrase += static_cast<char>(value);

		g2d::math::clamp(++index, 0, max);
	}

	return phrase;
}

char g2d::crypto::character_at(size_t index)
{
	static const char ascii[] = {
		"1234567890-"
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	};

	assert(index < g2d::basic::array_size(ascii));

	return ascii[index];
}

std::string g2d::crypto::formatted_password(const std::string& value)
{
	size_t length = value.length();
	std::string result;
	result.reserve(length * 2);

	for (size_t i = 0; i < length; i++)
	{
		if (i % 4 == 0 && i != 0)
		{
			result += ' ';
		}

		result += value[i];
	}

	return result;
}

std::string g2d::crypto::randomizer_string(std::size_t size)
{
	static const char alphanum[] =
	"0123456789"
	"!@#$%^&*"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz";
	int stringLength = g2d::basic::array_size(alphanum) - 1;
	std::string str;

	srand((unsigned long long int)time(NULL));

	for (std::size_t i = 0; i < size; i++)
	{
		str += alphanum[rand() % stringLength];
	}

	return str;
}

std::string g2d::crypto::encode(const std::string& str)
{
	unsigned char const* bytes_to_encode = (unsigned char const*)str.c_str();
	std::string res;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];
	unsigned int in_len = str.size();

	while (in_len--)
	{
		char_array_3[i++] = *(bytes_to_encode++);

		if (i == 3)
		{
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i <4) ; i++)
			{
				res += g2d::math::BASE64[char_array_4[i]];
			}

			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
		{
			char_array_3[j] = '\0';
		}

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
		{
			res += g2d::math::BASE64[char_array_4[j]];
		}

		while((i++ < 3))
		{
			res += '=';
		}
	}

	return res;
}

std::string g2d::crypto::decode(const std::string& str)
{
	std::string encoded_string = str;
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4];
	unsigned char char_array_3[3];
	std::string res;

	while (in_len-- && (encoded_string[in_] != '=') && g2d::math::is_math(encoded_string[in_]))
	{
		char_array_4[i++] = encoded_string[in_];
		in_++;

		if (i == 4)
		{
			for (i = 0; i <4; i++)
			{
				char_array_4[i] = g2d::math::BASE64.find(char_array_4[i]);
			}

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
			{
				res += char_array_3[i];
			}

			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 4; j++)
		{
			char_array_4[j] = 0;
		}

		for (j = 0; j < 4; j++)
		{
			char_array_4[j] = g2d::math::BASE64.find(char_array_4[j]);
		}

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++)
		{
			res += char_array_3[j];
		}
	}

	return res;
}
