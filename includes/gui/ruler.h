#ifndef G2D_GUI_RULER_H_
#define G2D_GUI_RULER_H_

#pragma once

#include <iostream>
#include <string>

#include <GL/gl.h>
#include <SDL2/SDL_opengl.h>

#include "../math/size2d.h"

namespace g2d
{
	namespace gui
	{
		class ruler
		{
			public:

				ruler();

				ruler(double width, double height);

				~ruler();

				bool initialize(double width, double height);

				void destroy();

				void draw();

				void visible(bool visible);

				void opacity(double opacity);

				bool visible() const;

				double opacity() const;

				const g2d::math::size2dd& size() const;

			private:

				bool _visible { true };
				double _opacity { 100.0 };
				g2d::math::size2dd _size { g2d::math::size2dd() };
		};
	}
}

#endif /* G2D_GUI_RULER_H_ */
