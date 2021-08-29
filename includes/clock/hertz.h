#ifndef G2D_CLOCK_HERTZ_H_
#define G2D_CLOCK_HERTZ_H_

#pragma once

#include <string>
#include <iostream>

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#include "frequency.h"
#include "timer.h"

namespace g2d
{
	namespace clock
	{
		class hertz
		{
			public:

				hertz();

				~hertz();

				bool initialize(std::size_t fps);

				void destroy();

				void synchronize();

				void fps(std::size_t fps);

				std::size_t fps() const;

				std::size_t latency() const;

				std::size_t frequency() const;

				std::size_t current();

			private:

				g2d::clock::timer* _timer { nullptr };
				g2d::clock::frequency* _frequency { nullptr };
				std::size_t _fps { g2d::clock::FPS };
				std::size_t _latency { g2d::clock::LATENCY };
		};
	}
}

#endif /* G2D_CLOCK_HERTZ_H_ */
