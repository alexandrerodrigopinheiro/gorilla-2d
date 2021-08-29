#ifndef G2D_CLOCK_TIMER_H_
#define G2D_CLOCK_TIMER_H_

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
		class timer
		{
			public:

				timer();

				~timer();

				void run();

				void play();

				void stop();

				void reset();

				void replay();

				bool played() const;

				std::size_t elapsed() const;

				std::size_t current() const;

			private:

				bool _play { false };
				std::size_t	_restore { 0 };
				std::size_t	_initial { 0 };
				std::size_t	_current { 0 };
		};
	}
}

#endif /* G2D_CLOCK_TIMER_H_ */
