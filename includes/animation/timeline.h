
#ifndef YGL_ANIMATION_TIMELINE_H_
#define G2D_ANIMATION_TIMELINE_H_

#pragma once

#include <iostream>
#include <string>

#include "../clock/clock.h"
#include "../clock/timer.h"
#include "../math/range.h"

#include "animation.h"
#include "framer.h"

namespace g2d
{
	namespace animation
	{
		class timeline
		{
			public:

				timeline();

				~timeline();

				bool initialize(std::size_t length, std::size_t fps = g2d::clock::FPS);

				void destroy();

				void run();

				void play();

				void stop();

				void replay();

				void reset();

				bool played() const;

				void begin();

				void end();

				bool bound() const;

				bool onset() const;

				void length(std::size_t length);

				void course(const g2d::animation::course& course);

				void control(const g2d::animation::control& control);

				void fps(std::size_t frame_per_second);

				void frame_rate(std::size_t frame_rate);

				void frame(std::size_t frame);

				std::size_t length() const;

				const g2d::animation::course& course() const;

				const g2d::animation::control& control() const;

				std::size_t fps() const;

				std::size_t frame_rate() const;

				std::size_t frame() const;

			private:

				g2d::animation::framer*	_framer { nullptr };
				std::size_t _length { 0 };
				g2d::animation::course	_course { g2d::animation::course::course_forward };
				g2d::animation::control	_control { g2d::animation::control::control_single };
				std::size_t _frame_per_second { g2d::clock::FPS };
				std::size_t _frame_rate { g2d::clock::SECOND };
		};

		std::ostream& operator<<(std::ostream& stream, const g2d::animation::timeline& timeline);

		std::istream& operator>>(std::istream& stream, g2d::animation::timeline& timeline);
	}
}

#endif /* G2D_ANIMATION_TIMELINE_H_ */
