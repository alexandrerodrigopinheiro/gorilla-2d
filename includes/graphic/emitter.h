#ifndef G2D_GRAPHIC_EMITTER_H_
#define G2D_GRAPHIC_EMITTER_H_

#pragma once

#include <string>
#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "../basic/basic.h"
#include "../math/color.h"
#include "../math/math.h"
#include "../math/point2d.h"
#include "../math/rotate.h"
#include "../math/square.h"
#include "../math/size2d.h"
#include "../math/uvmap.h"
#include "../math/vertex.h"

#include "emitter.h"
#include "graphic.h"
#include "particle.h"
#include "texture.h"

namespace g2d
{
	namespace graphic
	{
		class emitter
		{
			public:

				emitter();

				~emitter();

				bool initialize(const std::string& filename, const g2d::graphic::emission& emission, std::size_t amount = 0, bool verbose = false);

				bool initialize(const g2d::graphic::texture& texture, const g2d::graphic::emission& emission, std::size_t amount = 0, bool verbose = false);

				void destroy();

				void draw();

				void update();

				void resize_particles(std::size_t number_of_particles);

				bool paused() const;

				void pause();

				void resume();

				void add_particles(std::size_t amount);

				void stop_emitter();

				void reemitter();

				bool ended() const;

				bool auto_remove_on_finish() const;

				void emission(const g2d::graphic::emission& emission);

				void auto_remove_on_finish(bool auto_remove_on_finish);

				void gravity_value(const g2d::math::point3dd& gravity_value);

				void gravity_speed(double gravity_speed);

				void gravity_speed_variance(double gravity_speed_variance);

				void gravity_tangential_acceleration(double gravity_tangential_acceleration);

				void gravity_tangential_acceleration_variance(double gravity_tangential_acceleration_variance);

				void gravity_radial_acceleration(double gravity_radial_acceleration);

				void gravity_radial_acceleration_variance(double gravity_radial_acceleration_variance);

				void gravity_rotation_is_directional(bool gravity_rotation_is_directional);

				void radius_start(double radius_start);

				void radius_start_variance(double radius_start_variance);

				void end_radius(double end_radius);

				void end_radius_variance(double end_radius_variance);

				void radius_rotate_per_second(double degrees);

				void radius_rotate_per_second_variance(double degrees);

				void rotate(double rotate);

				void scale(double scale);

				void scale_w(double w);

				void scale_h(double h);

				void atlas_index(std::size_t index);

				void duration(double duration);

				void pivot(double x, double y);

				void pivot(const g2d::math::point2dd& pivot);

				void pivot(double pivot);

				void pivot_x(double x);

				void pivot_y(double y);

				void position(double x, double y, double z);

				void position(const g2d::math::point3dd& position);

				void position(double position);

				void position_x(double x);

				void position_y(double y);

				void position_z(double z);

				void position_variance(const g2d::math::point3dd& position);

				void life(double life);

				void life_variance(double life_variance);

				void angle(double angle);

				void angle_variance(double angle_variance);

				void flip(const g2d::graphic::flip& flip);

				void mode(const g2d::graphic::mode& mode);

				void start_size(double start_size);

				void start_size_variance(double start_size_variance);

				void end_size(double end_size);

				void end_size_variance(double end_size_variance);

				void size(const g2d::math::size2dd& size);

				void size(double w, double h);

				void size(double size);

				void size_w(double w);

				void size_h(double h);

				void start_color(const g2d::math::color& start_color);

				void start_color_variance(const g2d::math::color& start_color_variance);

				void end_color(const g2d::math::color& end_color);

				void end_color_variance(const g2d::math::color& end_color_variance);

				void start_spin(double start_spin);

				void start_spin_variance(double start_spin_variance);

				void end_spin(double end_spin);

				void end_spin_variance(double end_spin_variance);

				void emission_rate(double emission_rate);

				void total_particles(std::size_t total_particles);

				void opacity_modify_rgb(bool opacity_modify_rgb);

				const g2d::math::point3dd& gravity_value();

				const g2d::math::point3dd& gravity_speed() const;

				const g2d::math::point3dd& speed_variance() const;

				const g2d::math::point3dd& gravity_tangential_acceleration() const;

				const g2d::math::point3dd& gravity_tangential_acceleration_variance() const;

				const g2d::math::point3dd& radial_acceleration() const;

				const g2d::math::point3dd& gravity_radial_acceleration_variance() const;

				bool gravity_rotation_is_directional() const;

				double radius_start() const;

				double radius_start_variance() const;

				double end_radius() const;

				double end_radius_variance() const;

				double radius_rotate_per_second() const;

				double radius_rotate_per_second_variance() const;

				bool active() const;

				std::size_t atlas_index() const;

				std::size_t particle_count() const;

				double duration() const;

				const g2d::math::point3dd& position() const;

				const g2d::math::point3dd& position_variance() const;

				double life() const;

				double life_variance() const;

				double angle() const;

				double angle_variance() const;

				const g2d::graphic::flip& flip() const;

				const g2d::graphic::mode& mode() const;

				double start_size() const;

				double start_size_variance() const;

				double end_size() const;

				double end_size_variance() const;

				const g2d::math::color& start_color() const;

				const g2d::math::color& start_color_variance() const;

				const g2d::math::color& end_color() const;

				const g2d::math::color& end_color_variance() const;

				double start_spin() const;

				double start_spin_variance() const;

				double end_spin() const;

				double end_spin_variance() const;

				double emission_rate() const;

				std::size_t total_particles() const;

				bool opacity_modify_rgb() const;

			private:

				bool initialize_with_total_particles(std::size_t number_of_particles);

				void bind(const g2d::graphic::filter& filter = g2d::graphic::filter::filter_linear, const g2d::graphic::wrap& wrap = g2d::graphic::wrap::wrap_clamp);

				void mapping();

				bool _run { false };
				bool _visible { true };
				bool _wireframe { false };
				bool _verbose { false };
				uint _identity { 0 };
				std::size_t _atlas_index { 0 };
				std::size_t _allocated_particles { 0 };
				std::size_t _particle_size { 0 };
				std::size_t _total_particles { 0 };
				int _y_coord_flipped { 1 };
				bool _blend_additive { true };
				bool _auto_remove_on_finish { false };
				bool _transform_emitter_dirty { false };
				bool _active { true };
				bool _opacity_modify_rgb { false };
				bool _paused { false };
				bool _start_position_compatible { false };
				bool _gravity_rotation_is_directional { false };
				double _elapsed { 0 };
				double _emission_counter { 0.0 };
				double _duration { 0.0 };
				double _life { 0.0 };
				double _life_variance { 0.0 };
				double _angle { 0.0 };
				double _angle_variance { 0.0 };
				double _start_size { 0.0 };
				double _start_size_variance { 0.0 };
				double _end_size { 0.0 };
				double _end_size_variance { 0.0 };
				double _start_spin { 0.0 };
				double _start_spin_variance { 0.0 };
				double _end_spin { 0.0 };
				double _end_spin_variance { 0.0 };
				double _emission_rate { 0.0 };
				double _radius_start { 0.0 };
				double _radius_start_variance { 0.0 };
				double _radius_end { 0.0 };
				double _radius_end_variance { 0.0 };
				double _radius_rotate_per_second { 0.0 };
				double _radius_rotate_per_second_variance { 0.0 };
				std::string _filename { std::string() };
				std::string _configuration_name { std::string() };
				g2d::graphic::flip _flip { g2d::graphic::flip::flip_none };
				g2d::graphic::mode _mode { g2d::graphic::mode::mode_gravity };
				g2d::graphic::emission _emission { g2d::graphic::emission::emission_none };
				g2d::math::point2dd _pivot { g2d::math::point2dd(0.0) };
				g2d::math::size2dd _scale { g2d::math::size2dd(1.0) };
				g2d::math::rotated _rotate { g2d::math::rotated() };
				g2d::math::color _color { g2d::math::color(255) };
				g2d::math::color _start_color { g2d::math::color(255) };
				g2d::math::color _start_color_variance { g2d::math::color(255) };
				g2d::math::color _end_color { g2d::math::color(255) };
				g2d::math::color _end_color_variance { g2d::math::color(255) };
				g2d::math::point3dd _start_position { g2d::math::point3dd() };
				g2d::math::point3dd _position_variance { g2d::math::point3dd() };
				g2d::math::point3dd _position { g2d::math::point3dd() };
				g2d::math::point3dd _gravity_value { g2d::math::point3dd() };
				g2d::math::point3dd _gravity_speed { g2d::math::point3dd() };
				g2d::math::point3dd _gravity_speed_variance { g2d::math::point3dd() };
				g2d::math::point3dd _gravity_tangential_acceleration { g2d::math::point3dd() };
				g2d::math::point3dd _gravity_tangential_acceleration_variance { g2d::math::point3dd() };
				g2d::math::point3dd _gravity_radial_acceleration { g2d::math::point3dd() };
				g2d::math::point3dd _gravity_radial_acceleration_variance { g2d::math::point3dd() };
				g2d::math::size2dd _source_size { g2d::math::size2dd() };
				g2d::math::size2dd _size { g2d::math::size2dd() };
				g2d::math::vertexd _vertex { g2d::math::vertexd(0.0) };
				std::vector<g2d::graphic::particle> _particles { std::vector<g2d::graphic::particle>() };
		};
	}
}

#endif /* G2D_GRAPHIC_EMITTER_H_ */
