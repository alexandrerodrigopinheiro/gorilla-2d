#include "../../includes/basic/basic.h"

std::string g2d::basic::to_hex_string(int value, std::size_t length)
{
    std::string hex_str;

    // integer value to hex-string.
    std::stringstream sstream;
    sstream << "0x" << std::setfill ('0') << std::setw(length) << std::hex << (int)value;

    hex_str = sstream.str();

    sstream.clear(); // clears out the stream-string.

    return hex_str;
}

std::vector<std::string> g2d::basic::explode(const std::string& src, const char delimeter)
{
    size_t start;
    size_t end = 0;
    std::vector<std::string> res;

    while ((start = src.find_first_not_of(delimeter, end)) != std::string::npos)
    {
        end = src.find(delimeter, start);
        res.push_back(src.substr(start, end - start));
    }

	return res;
}

std::string g2d::basic::replace(const std::string& src, const char org, const char dst)
{
	std::string str = src;
	std::string chg = g2d::basic::to<std::string>(dst);

	for (std::size_t i = 0; i < str.length(); i++)
	{
	    if (str[i] == org)
	    {
	    	str.replace(i, 1, chg);
	    }
	}

	return str;
}
