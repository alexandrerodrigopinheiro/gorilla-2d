#ifndef G2D_CLOCK_FREQUENCY_H_
#define G2D_CLOCK_FREQUENCY_H_

#pragma once

#include <string>
#include <iostream>

#include "clock.h"
#include "timer.h"

namespace g2d
{
	namespace clock
	{
		class frequency
		{
			public:

				frequency();

				~frequency();

				bool initialize();

				void destroy();

				bool update();

				uint64_t current();

			private:

				g2d::clock::timer* _timer { nullptr };
				uint64_t _counter { 0 };
				uint64_t _frequency { 0 };
		};
	}
}

#endif /* G2D_CLOCK_FREQUENCY_H_ */
