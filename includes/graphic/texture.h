#ifndef G2D_GRAPHIC_TEXTURE_H_
#define G2D_GRAPHIC_TEXTURE_H_

#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "../basic/basic.h"
#include "../math/size2d.h"

#include "graphic.h"

namespace g2d
{
	namespace graphic
	{
		class texture
		{
			public:

				texture();

				~texture();

				bool initialize(const std::string& filename, bool verbose = false);

				void destroy();

				uint identity() const;

				const std::string& filename() const;

				const g2d::math::size2dd& size() const;

			private:

				uint _identity { 0 };
				std::string _filename { std::string() };
				g2d::math::size2dd _size { g2d::math::size2dd(0.0) };
		};
	}
}

#endif /* G2D_GRAPHIC_TEXTURE_H_ */
