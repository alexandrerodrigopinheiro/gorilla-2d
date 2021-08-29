#ifndef G2D_CLOCK_CHRONOMETER_H_
#define G2D_CLOCK_CHRONOMETER_H_

#pragma once

#include <cassert>
#include <chrono>
#include <ratio>
#include <thread>
#include <string>
#include <iostream>

#include "tick.h"

namespace g2d
{
	namespace clock
	{
		class chronometer
		{
			public:

				chronometer();

				chronometer(uint64_t maximum);

				~chronometer();

				bool initialize(uint64_t maximum);

				void destroy();

				void run();

				void play();

				void pause();

				void reset();

				void replay();

				void end();

				void maximum(uint64_t maximum);

				bool bound() const;

				bool onset() const;

				bool played() const;

				uint64_t maximum() const;

				uint64_t current() const;

			private:

				g2d::clock::tick _tick { g2d::clock::tick() };
				uint64_t _maximum { 0 };
		};
	}
}

#endif /* G2D_CLOCK_CHRONOMETER_H_ */
