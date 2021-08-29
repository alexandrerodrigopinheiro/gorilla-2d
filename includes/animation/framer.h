#ifndef G2D_ANIMATION_FRAMER_H_
#define G2D_ANIMATION_FRAMER_H_

#pragma once

#include <iostream>
#include <string>

#include "../clock/timer.h"
#include "../math/math.h"

#include "animation.h"

namespace g2d
{
	namespace animation
	{
		class framer
		{
			public:

				framer();

				~framer();

				bool initialize(std::size_t expiry);

				void destroy();

				void run();

				void play();

				void stop();

				void replay();

				void reset();

				bool bound() const;

				bool played() const;

				void course(const g2d::animation::course& course);

				void frame(std::size_t frame);

				void expiry(std::size_t expiry);

				const g2d::animation::course& course() const;

				std::size_t frame() const;

				std::size_t expiry() const;

			private:

				g2d::clock::timer* _timer { nullptr };
				g2d::animation::course _course { g2d::animation::course::course_forward };
				std::size_t _expiry { 0 };
				std::size_t _frame { 0 };
				bool _play { false };
				bool _bound { false };
		};
	}
}

#endif /* G2D_ANIMATION_FRAMER_H_ */
