#ifndef G2D_EMITTER_CRYPTO_H_
#define G2D_EMITTER_CRYPTO_H_

#pragma once

#if defined(__linux__) || defined(__linux) || defined(linux)
#include <blkid/blkid.h>
#endif

#include <err.h>
#include <errno.h>
#include <fcntl.h>

#if defined(__linux__) || defined(__linux) || defined(linux)
#include <linux/hdreg.h>
#endif

#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <openssl/rand.h>

#if defined(_WIN32)
#  include <NTSecAPI.h>
#endif

#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <assert.h>

#include "../math/math.h"
#include "../basic/basic.h"

namespace g2d
{
	namespace crypto
	{
		std::string show_uuid(const char* devname);

		bool serial(struct hd_driveid* hd, const char* devname);

		bool startup();

		void shutdown();

		bool seed_prng(void);

		std::string bytes_to_hexstring(const uint8_t *bytes, size_t size);

		std::string random_string(size_t size);

		std::string md5(const std::string& source);

		std::string rot13(const std::string& source);

		std::string generate_user_pass(const std::string& uuid, const std::string& machine_pass);

		bool validate_user_pass(const std::string& uuid, const std::string& machine_pass, const std::string& user_pass);

		bool is_empty_string(const char* str);

		bool is_running_as_super_user(void);

		int force_ch_root(const char* dirname);

		int drop_priv_perm(uid_t new_uid);

		int force_uid(const char *username);

		std::string encode_string(const std::string& data, const std::string& key);

		std::string decode_string(const std::string& data, const std::string& key);

		char character_at(size_t index);

		std::string formatted_password(const std::string& value);

		std::string randomizer_string(std::size_t size);

		std::string encode(const std::string& str);

		std::string decode(const std::string& str);
	}
}

#endif /* G2D_EMITTER_CRYPTO_H_ */
