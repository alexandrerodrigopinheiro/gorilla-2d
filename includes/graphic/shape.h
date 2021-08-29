#ifndef G2D_GRAPHIC_SHAPE_H_
#define G2D_GRAPHIC_SHAPE_H_

#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "../animation/tweener.h"
#include "../basic/basic.h"
#include "../clock/clock.h"
#include "../math/math.h"
#include "../math/color.h"
#include "../math/point2d.h"
#include "../math/point3d.h"
#include "../math/rotate.h"
#include "../math/size2d.h"
#include "../math/square.h"
#include "../math/uvmap.h"
#include "../math/vertex.h"

#include "graphic.h"

namespace g2d
{
	namespace graphic
	{
		class shape
		{
			public:

				shape();

				~shape();

				bool initialize(double width, double height, std::size_t dots, const g2d::graphic::form& form, bool verbose = false);

				bool animation(const std::string& animation, std::size_t length, std::size_t fps = g2d::clock::FPS);

				void destroy();

				void draw();

				void run();

				void play();

				void pause();

				void replay();

				void reset();

				bool played() const;

				bool onset() const;

				bool bound() const;

				void visible(bool visible);

				void wireframe(bool wireframe);

				void verbose(bool verbose);

				void dots(std::size_t dots);

				void form(const g2d::graphic::form& form);

				void color(const g2d::math::color& color);

				void color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);

				void color(std::uint8_t color);

				void color_r(std::uint8_t r);

				void color_g(std::uint8_t g);

				void color_b(std::uint8_t b);

				void color_a(std::uint8_t a);

				void pivot(const g2d::math::point2dd& pivot);

				void pivot(double x, double y);

				void pivot(double pivot);

				void pivot_x(double x);

				void pivot_y(double y);

				void position(const g2d::math::point3dd& position);

				void position(double x, double y, double z);

				void position(double position);

				void position_x(double x);

				void position_y(double y);

				void position_z(double z);

				void rotate(const g2d::math::rotated& rotate);

				void rotate(double h, double p, double b);

				void rotate(double rotate);

				void rotate_h(double h);

				void rotate_p(double p);

				void rotate_b(double b);

				void scale(const g2d::math::size2dd& scale);

				void scale(double w, double h);

				void scale(double scale);

				void scale_w(double w);

				void scale_h(double h);

				void animation(const std::string& animation);

				void append_dots(std::size_t dots);

				void append_color(const g2d::math::color& color);

				void append_color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);

				void append_color(std::uint8_t color);

				void append_color_r(std::uint8_t r);

				void append_color_g(std::uint8_t g);

				void append_color_b(std::uint8_t b);

				void append_color_a(std::uint8_t a);

				void append_pivot(const g2d::math::point2dd& pivot);

				void append_pivot(double x, double y);

				void append_pivot(double pivot);

				void append_pivot_x(double x);

				void append_pivot_y(double y);

				void append_position(const g2d::math::point3dd& position);

				void append_position(double x, double y, double z);

				void append_position(double position);

				void append_position_x(double x);

				void append_position_y(double y);

				void append_position_z(double z);

				void append_rotate(const g2d::math::rotated& rotate);

				void append_rotate(double h, double p, double b);

				void append_rotate(double rotate);

				void append_rotate_h(double h);

				void append_rotate_p(double p);

				void append_rotate_b(double b);

				void append_scale(const g2d::math::size2dd& scale);

				void append_scale(double w, double h);

				void append_scale(double scale);

				void append_scale_w(double w);

				void append_scale_h(double h);

				bool visible() const;

				bool wireframe() const;

				bool verbose() const;

				std::size_t dots() const;

				const g2d::graphic::form& form() const;

				const g2d::math::color& color() const;

				const g2d::math::point2dd& pivot() const;

				const g2d::math::point3dd& position() const;

				const g2d::math::rotated& rotate() const;

				const g2d::math::size2dd& size() const;

				const g2d::math::size2dd& scale() const;

				g2d::animation::tweener* animation() const;

			private:

				void mapping();

				bool _run { false };
				bool _visible { true };
				bool _wireframe { false };
				bool _verbose { false };
				std::size_t _dots { 4 };
				g2d::graphic::form _form { g2d::graphic::form::form_square };
				g2d::math::color _color { g2d::math::color(255) };
				g2d::math::point2dd _pivot { g2d::math::point2dd(0.0) };
				g2d::math::point3dd _position { g2d::math::point3dd(0.0) };
				g2d::math::rotated _rotate { g2d::math::rotated(0.0) };
				g2d::math::size2dd _size { g2d::math::size2dd(0.0) };
				g2d::math::size2dd _scale { g2d::math::size2dd(1.0) };
				std::map<std::string, g2d::animation::tweener*> _animations { std::map<std::string, g2d::animation::tweener*>() };
				g2d::animation::tweener* _animation { nullptr };
				g2d::math::squared _offset { g2d::math::squared(0.0) };
				g2d::math::vertexd _vertex { g2d::math::vertexd(0.0) };
				g2d::math::uvmapd _uvmap { g2d::math::uvmapd(1.0) };
		};
	}
}

#endif /* G2D_GRAPHIC_SHAPE_H_ */
