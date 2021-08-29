#ifndef G2D_CORE_WINDOW_H_
#define G2D_CORE_WINDOW_H_

#pragma once

#include <cassert>
#include <string>
#include <memory>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <GL/glu.h>

#include "../math/point2d.h"

namespace g2d
{
	namespace core
	{
		class window
		{
			public:

				window();

				~window();

				bool initialize(const std::string& caption, int x, int y, int width, int height, bool fullscreen);

				void destroy();

				void render();

				void refrash();

				bool open() const;

			private:

				bool attribute();

				bool _open { false };
				SDL_Window* _window { nullptr };
				SDL_GLContext _context { nullptr };
		};
	}
}

#endif /* G2D_CORE_WINDOW_H_ */
