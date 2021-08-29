#ifndef G2D_CORE_RENDER_H_
#define G2D_CORE_RENDER_H_

#pragma once

#include <cassert>
#include <string>
#include <memory>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_video.h>

#include <GL/glu.h>

#include "../math/color.h"

namespace g2d
{
	namespace core
	{
		class render
		{
			public:

				render();

				~render();

				bool initialize();

				bool attribute();

				void refresh(const g2d::math::color& color = g2d::math::color::BLACK());
		};
	}
}

#endif /* G2D_CORE_WINDOW_H_ */
