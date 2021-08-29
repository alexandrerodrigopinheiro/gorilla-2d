#ifndef G2D_GRAPHIC_FONT_H_
#define G2D_GRAPHIC_FONT_H_

#pragma once

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>

namespace g2d
{
	namespace graphic
	{
		class font
		{
			public:

				font();

				~font();

				bool load(const std::string& filename, std::size_t dpi, bool verbose = false);

				void unload();

				TTF_Font* identifier() const;

				const std::string& filename() const;

				std::size_t dpi() const;

			private:

				TTF_Font* _font { nullptr };
				std::string _filename { std::string() };
				std::size_t _dpi { 0 };
		};
	}
}


#endif /* G2D_GRAPHIC_FONT_H_ */
