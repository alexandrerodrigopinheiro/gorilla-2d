#ifndef G2D_CLOCK_CLOCK_H_
#define G2D_CLOCK_CLOCK_H_

#pragma once

#include <ctime>
#include <string>
#include <iostream>

namespace g2d
{
	namespace clock
	{
		extern const std::size_t SECOND;
		extern const std::size_t HERTZ;
		extern const std::size_t FPS;
		extern const std::size_t LATENCY;

		std::string datetime_stamp();

		std::string date_stamp();

		std::string time_stamp();
	}
}

#endif /* G2D_CLOCK_CLOCK_H_ */
