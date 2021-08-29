#ifndef G2D_CORE_CAMERA_H_
#define G2D_CORE_CAMERA_H_

#pragma once

#include <cassert>
#include <string>
#include <memory>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "../math/math.h"
#include "../math/color.h"
#include "../math/point2d.h"
#include "../math/size2d.h"
#include "../math/rotate.h"

namespace g2d
{
	namespace core
	{
		class camera
		{
			public:

				camera();

				~camera();

				bool initialize(const std::string& name, double x, double y, double width, double height);

				void render();

				void name(const std::string& name);

				void color(const g2d::math::color& color);

				void color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

				void color_r(double r);

				void color_g(double g);

				void color_b(double b);

				void color_a(double a);

				void position(double position);

				void position(const g2d::math::point2dd& position);

				void position(int x, int y);

				void position_x(int x);

				void position_y(int y);

				void size(const g2d::math::size2dd& size);

				void size(double w, double h);

				void size_w(double w);

				void size_h(double h);

				void scale(const g2d::math::size2dd& size);

				void scale(double w, double h);

				void scale_w(double w);

				void scale_h(double h);

				const std::string& name() const;

				const g2d::math::color& color() const;

				const g2d::math::point2dd& position() const;

				const g2d::math::size2dd& size() const;

				const g2d::math::size2dd& scale() const;

				const g2d::math::rotated& rotate() const;

			private:

				std::string _name { std::string() };
				g2d::math::color _color { g2d::math::color() };
				g2d::math::point2dd _position { g2d::math::point2dd() };
				g2d::math::size2dd _size { g2d::math::size2dd() };
				g2d::math::size2dd _scale { g2d::math::size2dd() };
				g2d::math::rotated _rotate { g2d::math::rotated() };
		};
	}
}

#endif /* G2D_CORE_CAMERA_H_ */
