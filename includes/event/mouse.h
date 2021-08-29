#ifndef G2D_EVENT_MOUSE_H_
#define G2D_EVENT_MOUSE_H_

#pragma once

#include <string>
#include <iostream>

#include "../math/point2d.h"

#include "event.h"

namespace g2d
{
	namespace event
	{
		class mouse
		{
			public:

				mouse();

				~mouse();

				void cursor(const g2d::event::cursor& cursor);

				void position(const g2d::math::point2dd& position);

				void position(double x, double y);

				void position(double position);

				void position_x(double x);

				void position_y(double y);

				bool motioned() const;

				bool pressed() const;

				bool released() const;

				const g2d::math::point2dd& position() const;

				const g2d::event::cursor& cursor() const;

				void clear();

			private:

				g2d::event::cursor _cursor { g2d::event::cursor::cursor_none };
				g2d::math::point2dd _position { g2d::math::point2dd().null() };
		};
	}
}

#endif /* G2D_EVENT_MOUSE_H_ */
