#ifndef G2D_CLOCK_TICK_H_
#define G2D_CLOCK_TICK_H_

#pragma once

#include <chrono>
#include <ratio>
#include <thread>
#include <string>
#include <iostream>

namespace g2d
{
	namespace clock
	{
		class tick
		{
			public:

				tick();

				~tick();

				void run();

				void play();

				void pause();

				void reset();

				void replay();

				bool played() const;

				void current(uint64_t current);

				uint64_t current() const;

			private:

				bool _play { false };
				uint64_t _initial { 0 };
				uint64_t _current { 0 };
		};
	}
}

#endif /* G2D_CLOCK_TICK_H_ */
