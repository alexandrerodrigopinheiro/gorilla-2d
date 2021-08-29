#ifndef G2D_GUI_HUD_H_
#define G2D_GUI_HUD_H_

#pragma once

#include <iostream>
#include <string>

#include "../graphic/shape.h"
#include "../graphic/text.h"
#include "../math/color.h"
#include "../math/point2d.h"
#include "../math/point3d.h"
#include "../math/rotate.h"
#include "../math/size2d.h"
#include "../math/math.h"

namespace g2d
{
	namespace gui
	{
		class hud
		{
			public:

				hud();

				~hud();

				bool initialize(const std::string& filename, std::size_t measure, double width, double height, bool verbose = false);

				void destroy();

				void draw();

				void verbose(bool verbose);

				void visible(bool visible);

				void content(const std::string& content);

				void color(double color);

				void color(const g2d::math::color& color);

				void color(double r, double g, double b, double a);

				void color_r(double r);

				void color_g(double g);

				void color_b(double b);

				void color_a(double a);

				void position(double position);

				void position(const g2d::math::point3dd& position);

				void position(double x, double y, double z);

				void position_x(double x);

				void position_y(double y);

				void position_z(double z);

				void rotate(double rotate);

				void rotate(const g2d::math::rotated& rotate);

				void rotate(double h, double p, double b);

				void rotate_h(double h);

				void rotate_p(double p);

				void rotate_b(double b);

				void scale(double scale);

				void scale(const g2d::math::size2dd& scale);

				void scale(double w, double h);

				void scale_w(double w);

				void scale_h(double h);

				bool verbose() const;

				bool visible() const;

				const std::string& content() const;

				const g2d::math::color& color() const;

				const g2d::math::point3dd& position() const;

				const g2d::math::rotated& rotate() const;

				const g2d::math::size2dd& scale() const;

				const g2d::math::size2dd& size() const;

			private:

				g2d::graphic::shape* _shape { nullptr };
				g2d::graphic::text* _text { nullptr };
				bool _verbose { false };
				bool _visible { true };
				g2d::math::color _color { g2d::math::color().WHITE() };
				g2d::math::point3dd _position { g2d::math::point3dd() };
				g2d::math::rotated _rotate { g2d::math::rotated() };
				g2d::math::size2dd _scale { g2d::math::size2dd(1) };
				g2d::math::size2dd _size { g2d::math::size2dd() };
		};
	}
}

#endif /* G2D_GUI_HUD_H_ */
