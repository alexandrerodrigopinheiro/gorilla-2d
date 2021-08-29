#ifndef G2D_EVENT_TOUCH_H_
#define G2D_EVENT_TOUCH_H_

#pragma once

#include <string>
#include <iostream>

#include "../math/point2d.h"

#include "event.h"

namespace g2d
{
	namespace event
	{
		class touch
		{
			public:

				touch();

				~touch();

				void finger(const g2d::event::finger& finger);

				void position(double position);

				void position(const g2d::math::point2dd& position);

				void position(double x, double y);

				void position_x(double x);

				void position_y(double y);

				bool motioned() const;

				bool pressed() const;

				bool released() const;

				const g2d::math::point2dd& position() const;

				const g2d::event::finger& finger() const;

				void clear();

			private:

				g2d::event::finger _finger { g2d::event::finger::finger_none };
				g2d::math::point2dd _position { g2d::math::point2dd().null() };
		};
	}
}

#endif /* G2D_EVENT_TOUCH_H_ */
