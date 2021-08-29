#include "../../includes/clock/clock.h"

const std::size_t g2d::clock::SECOND = 1000;
const std::size_t g2d::clock::HERTZ = 65;
const std::size_t g2d::clock::FPS = 30;
const std::size_t g2d::clock::LATENCY = g2d::clock::SECOND / g2d::clock::HERTZ;

std::string g2d::clock::datetime_stamp()
{
	time_t now = std::time(0);
	struct tm tstruct;
	char buf[80];

	tstruct = *std::localtime(&now);

	/** Visit http://en.cppreference.com/w/cpp/chrono/c/strftime */
	/** for more information about date/time format. */
	std::strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", &tstruct);

	return std::string(buf);
}

std::string g2d::clock::date_stamp()
{
	time_t now = std::time(0);
	struct tm tstruct;
	char buf[80];

	tstruct = *std::localtime(&now);

	/** Visit http://en.cppreference.com/w/cpp/chrono/c/strftime */
	/** for more information about date/time format. */
	std::strftime(buf, sizeof(buf), "%Y%m%d", &tstruct);

	return std::string(buf);
}

std::string g2d::clock::time_stamp()
{
	time_t now = std::time(0);
	struct tm tstruct;
	char buf[80];

	tstruct = *std::localtime(&now);

	/** Visit http://en.cppreference.com/w/cpp/chrono/c/strftime */
	/** for more information about date/time format. */
	std::strftime(buf, sizeof(buf), "%H%M%S", &tstruct);

	return std::string(buf);
}
