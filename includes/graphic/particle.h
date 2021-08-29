#ifndef G2D_GRAPHIC_PARTICLE_H_
#define G2D_GRAPHIC_PARTICLE_H_

#pragma once

#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "../animation/tweener.h"
#include "../basic/basic.h"
#include "../math/color.h"
#include "../math/math.h"
#include "../math/point2d.h"
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
		class particle
		{
			public:

				particle();

				~particle();

				bool initialize(const g2d::math::point3dd& position, const g2d::math::size2dd& size, bool verbose = false);

				bool animation(const std::string& animation, std::size_t length, std::size_t fps = g2d::clock::FPS);

				void destroy();

				void draw(uint identity);

				void play();

				void resume();

				void pause();

				void replay();

				void reset();

				bool played() const;

				bool onset() const;

				bool bound() const;

				void visible(bool visible);

				void wireframe(bool wireframe);

				void verbose(bool verbose);

				void time_to_live(double time_to_live);

				void gravity_radial_acceleration(double gravity_radial_acceleration);

				void gravity_tangential_acceleration(double gravity_tangential_acceleration);

				void radius_angle(double radius_angle);

				void radius_degrees_per_second(double radius_degrees_per_second);

				void radius_value(double radius_value);

				void radius_delta_value(double radius_delta_value);

				void atlas_index(std::size_t atlas_index);

				void flip(const g2d::graphic::flip& flip);

				void gravity_direction(const g2d::math::point3dd& gravity_direction);

				void gravity_direction(double x, double y, double z);

				void gravity_direction(double gravity_direction);

				void gravity_direction_x(double x);

				void gravity_direction_y(double y);

				void gravity_direction_z(double z);

				void color(const g2d::math::color& color);

				void color(double r, double g, double b, double a);

				void color(double color);

				void color_r(double r);

				void color_g(double g);

				void color_b(double b);

				void color_a(double a);

				void delta_color(const g2d::math::color& delta_color);

				void delta_color(double r, double g, double b, double a);

				void delta_color(double delta_color);

				void delta_color_r(double r);

				void delta_color_g(double g);

				void delta_color_b(double b);

				void delta_color_a(double a);

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

				void start_position(const g2d::math::point3dd& start_position);

				void start_position(double x, double y, double z);

				void start_position(double start_position);

				void start_position_x(double x);

				void start_position_y(double y);

				void start_position_z(double z);

				void rotate(const g2d::math::rotated& rotate);

				void rotate(double h, double p, double b);

				void rotate(double rotate);

				void rotate_h(double h);

				void rotate_p(double p);

				void rotate_b(double b);

				void delta_rotate(const g2d::math::rotated& delta_rotate);

				void delta_rotate(double h, double p, double b);

				void delta_rotate(double delta_rotate);

				void delta_rotate_h(double h);

				void delta_rotate_p(double p);

				void delta_rotate_b(double b);

				void scale(const g2d::math::size2dd& scale);

				void scale(double w, double h);

				void scale(double scale);

				void scale_w(double w);

				void scale_h(double h);

				void delta_size(const g2d::math::size2dd& delta_size);

				void delta_size(double w, double h);

				void delta_size(double delta_size);

				void delta_size_w(double w);

				void delta_size_h(double h);

				void size(const g2d::math::size2dd& size);

				void size(double w, double h);

				void size(double size);

				void size_w(double w);

				void size_h(double h);

				void append_time_to_live(double time_to_live);

				void append_gravity_radial_acceleration(double gravity_radial_acceleration);

				void append_gravity_tangential_acceleration(double gravity_tangential_acceleration);

				void append_radius_angle(double radius_angle);

				void append_radius_degrees_per_second(double radius_degrees_per_second);

				void append_radius_value(double radius_value);

				void append_radius_delta_value(double radius_delta_value);

				void append_atlas_index(std::size_t atlas_index);

				void append_gravity_direction(const g2d::math::point3dd& gravity_direction);

				void append_gravity_direction(double x, double y, double z);

				void append_gravity_direction(double gravity_direction);

				void append_gravity_direction_x(double x);

				void append_gravity_direction_y(double y);

				void append_gravity_direction_z(double z);

				void append_color(const g2d::math::color& color);

				void append_color(double r, double g, double b, double a);

				void append_color(double color);

				void append_color_r(double r);

				void append_color_g(double g);

				void append_color_b(double b);

				void append_color_a(double a);

				void append_delta_color(const g2d::math::color& delta_color);

				void append_delta_color(double r, double g, double b, double a);

				void append_delta_color(double delta_color);

				void append_delta_color_r(double r);

				void append_delta_color_g(double g);

				void append_delta_color_b(double b);

				void append_delta_color_a(double a);

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

				void append_start_position(const g2d::math::point3dd& start_position);

				void append_start_position(double x, double y, double z);

				void append_start_position(double start_position);

				void append_start_position_x(double x);

				void append_start_position_y(double y);

				void append_start_position_z(double z);

				void append_rotate(const g2d::math::rotated& rotate);

				void append_rotate(double h, double p, double b);

				void append_rotate(double rotate);

				void append_rotate_h(double h);

				void append_rotate_p(double p);

				void append_rotate_b(double b);

				void append_delta_rotate(const g2d::math::rotated& delta_rotate);

				void append_delta_rotate(double h, double p, double b);

				void append_delta_rotate(double delta_rotate);

				void append_delta_rotate_h(double h);

				void append_delta_rotate_p(double p);

				void append_delta_rotate_b(double b);

				void append_scale(const g2d::math::size2dd& scale);

				void append_scale(double w, double h);

				void append_scale(double scale);

				void append_scale_w(double w);

				void append_scale_h(double h);

				void append_delta_size(const g2d::math::size2dd& delta_size);

				void append_delta_size(double w, double h);

				void append_delta_size(double delta_size);

				void append_delta_size_w(double w);

				void append_delta_size_h(double h);

				void append_size(const g2d::math::size2dd& size);

				void append_size(double w, double h);

				void append_size(double size);

				void append_size_w(double w);

				void append_size_h(double h);

				bool visible() const;

				bool wireframe() const;

				bool verbose() const;

				double time_to_live() const;

				double gravity_radial_acceleration() const;

				double gravity_tangential_acceleration() const;

				double radius_angle() const;

				double radius_degrees_per_second() const;

				double radius_value() const;

				double radius_delta_value() const;

				std::size_t atlas_index() const;

				const g2d::graphic::flip& flip() const;

				const g2d::math::point3dd& gravity_direction() const;

				const g2d::math::color& color() const;

				const g2d::math::color& delta_color() const;

				const g2d::math::point2dd& pivot() const;

				const g2d::math::point3dd& position() const;

				const g2d::math::point3dd& start_position() const;

				const g2d::math::rotated& rotate() const;

				const g2d::math::rotated& delta_rotate() const;

				const g2d::math::size2dd& scale() const;

				const g2d::math::size2dd& delta_size() const;

				const g2d::math::size2dd& size() const;

				g2d::animation::tweener* animation() const;

			private:

				void bind(uint identity, const g2d::graphic::filter& filter = g2d::graphic::filter::filter_linear, const g2d::graphic::wrap& wrap = g2d::graphic::wrap::wrap_clamp);

				void mapping();

				bool _play { false };
				bool _visible { true };
				bool _wireframe { false };
				bool _verbose { false };
				double _time_to_live { 0 };
				double _gravity_radial_acceleration { 0.0 };
				double _gravity_tangential_acceleration { 0.0 };
				double _radius_angle { 0.0 };
				double _radius_degrees_per_second { 0.0 };
				double _radius_value { 0.0 };
				double _radius_delta_value { 0.0 };
				std::size_t _atlas_index { 0 };
				g2d::graphic::flip _flip { g2d::graphic::flip::flip_none };
				g2d::math::point3dd _gravity_direction { g2d::math::point3dd() };
				g2d::math::color _color { g2d::math::color(255) };
				g2d::math::color _delta_color { g2d::math::color(255) };
				g2d::math::point2dd _pivot { g2d::math::point2dd(0.5) };
				g2d::math::point3dd _position { g2d::math::point3dd(0.0) };
				g2d::math::point3dd _start_position { g2d::math::point3dd() };
				g2d::math::rotated _rotate { g2d::math::rotated(0.0) };
				g2d::math::rotated _delta_rotate { g2d::math::rotated() };
				g2d::math::size2dd _scale { g2d::math::size2dd(1.0) };
				g2d::math::size2dd _delta_size { g2d::math::size2dd() };
				g2d::math::size2dd _size { g2d::math::size2dd() };
				g2d::math::squared _offset { g2d::math::squared(0.0) };
				g2d::math::vertexd _vertex { g2d::math::vertexd(0.0) };
				g2d::math::uvmapd _uvmap { g2d::math::uvmapd(1.0) };
				g2d::animation::tweener* _animation { nullptr };
		};
	}
}

#endif /* G2D_GRAPHIC_PARTICLE_H_ */
