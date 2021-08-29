#ifndef G2D_ANIMATION_TWEENER_H_
#define G2D_ANIMATION_TWEENER_H_

#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "../graphic/graphic.h"
#include "../math/color.h"
#include "../math/math.h"
#include "../math/point2d.h"
#include "../math/point3d.h"
#include "../math/rotate.h"
#include "../math/size2d.h"

#include "animation.h"
#include "keyframe.h"
#include "timeline.h"

namespace g2d
{
	namespace animation
	{
		class tweener
		{
			public:

				tweener();

				~tweener();

				bool initialize(const std::string& identity, std::size_t length, std::size_t fps = g2d::clock::FPS);

				void destroy();

				void run();

				void play();

				void stop();

				void replay();

				void reset();

				bool played() const;

				bool bound() const;

				bool onset() const;

				std::size_t length() const;

				std::size_t frame() const;

				void course(const g2d::animation::course& course);

				void control(const g2d::animation::control& control);

				const g2d::animation::course& course() const;

				const g2d::animation::control& control() const;

				void bind_measure(std::size_t keyframe, std::size_t measure);

				void bind_content(std::size_t keyframe, std::string& content);

				void bind_hinting(std::size_t keyframe, const g2d::graphic::hinting& hinting);

				void bind_weight(std::size_t keyframe, const g2d::graphic::weight& weight);

				void bind_dots(std::size_t keyframe, std::size_t dots);

				void bind_index(std::size_t keyframe, std::size_t index);

				void bind_visible(std::size_t keyframe, bool visible);

				void bind_wireframe(std::size_t keyframe, bool wireframe);

				void bind_form(std::size_t keyframe, const g2d::graphic::form& form);

				void bind_flip(std::size_t keyframe, const g2d::graphic::flip& flip);

				void bind_color(std::size_t keyframe, const g2d::math::color& color);

				void bind_pivot(std::size_t keyframe, const g2d::math::point2dd& pivot);

				void bind_position(std::size_t keyframe, const g2d::math::point3dd& position);

				void bind_scale(std::size_t keyframe, const g2d::math::size2dd& scale);

				void bind_rotate(std::size_t keyframe, const g2d::math::rotated& rotate);

				void bind_size(std::size_t keyframe, const g2d::math::size2dd& size);

				void clear();

				void clear_measure();

				void clear_content();

				void clear_hinting();

				void clear_weight();

				void clear_dots();

				void clear_index();

				void clear_visible();

				void clear_wireframe();

				void clear_form();

				void clear_flip();

				void clear_color();

				void clear_pivot();

				void clear_position();

				void clear_scale();

				void clear_rotate();

				void clear_size();

				std::size_t size_tweening() const;

				std::size_t size_measure() const;

				std::size_t size_content() const;

				std::size_t size_hinting() const;

				std::size_t size_weight() const;

				std::size_t size_dots() const;

				std::size_t size_index() const;

				std::size_t size_visible() const;

				std::size_t size_wireframe() const;

				std::size_t size_form() const;

				std::size_t size_flip() const;

				std::size_t size_color() const;

				std::size_t size_pivot() const;

				std::size_t size_position() const;

				std::size_t size_scale() const;

				std::size_t size_rotate() const;

				std::size_t size_size() const;

				const g2d::animation::keyframe<std::size_t>& keyframe_measure(std::size_t index) const;

				const g2d::animation::keyframe<std::string>& keyframe_content(std::size_t index) const;

				const g2d::animation::keyframe<g2d::graphic::hinting>& keyframe_hinting(std::size_t index) const;

				const g2d::animation::keyframe<g2d::graphic::weight>& keyframe_weight(std::size_t index) const;

				const g2d::animation::keyframe<std::size_t>& keyframe_dots(std::size_t index) const;

				const g2d::animation::keyframe<std::size_t>& keyframe_index(std::size_t index) const;

				const g2d::animation::keyframe<bool>& keyframe_visible(std::size_t index) const;

				const g2d::animation::keyframe<bool>& keyframe_wireframe(std::size_t index) const;

				const g2d::animation::keyframe<g2d::graphic::form>& keyframe_form(std::size_t index) const;

				const g2d::animation::keyframe<g2d::graphic::flip>& keyframe_flip(std::size_t index) const;

				const g2d::animation::keyframe<g2d::math::color>& keyframe_color(std::size_t index) const;

				const g2d::animation::keyframe<g2d::math::point2dd>& keyframe_pivot(std::size_t index) const;

				const g2d::animation::keyframe<g2d::math::point3dd>& keyframe_position(std::size_t index) const;

				const g2d::animation::keyframe<g2d::math::size2dd>& keyframe_scale(std::size_t index) const;

				const g2d::animation::keyframe<g2d::math::rotated>& keyframe_rotate(std::size_t index) const;

				const g2d::animation::keyframe<g2d::math::size2dd>& keyframe_size(std::size_t index) const;

				bool has_tweener() const;

				bool has_measure() const;

				bool has_content() const;

				bool has_hinting() const;

				bool has_weight() const;

				bool has_dots() const;

				bool has_index() const;

				bool has_visible() const;

				bool has_wireframe() const;

				bool has_form() const;

				bool has_flip() const;

				bool has_color() const;

				bool has_pivot() const;

				bool has_position() const;

				bool has_scale() const;

				bool has_rotate() const;

				bool has_size() const;

				std::size_t measure();

				std::string content();

				g2d::graphic::hinting hinting();

				g2d::graphic::weight weight();

				std::size_t dots();

				std::size_t index();

				bool visible();

				bool wireframe();

				g2d::graphic::form form();

				g2d::graphic::flip flip();

				g2d::math::color color();

				g2d::math::point2dd pivot();

				double depth();

				g2d::math::point3dd position();

				g2d::math::size2dd scale();

				g2d::math::rotated rotate();

				g2d::math::size2dd size();

			private:

				std::string _identity { std::string() };
				g2d::animation::timeline* _timeline { nullptr };
				std::vector<g2d::animation::keyframe<std::size_t>> _measure { std::vector<g2d::animation::keyframe<std::size_t>>() };
				std::vector<g2d::animation::keyframe<std::string>> _content { std::vector<g2d::animation::keyframe<std::string>>() };
				std::vector<g2d::animation::keyframe<g2d::graphic::hinting>> _hinting { std::vector<g2d::animation::keyframe<g2d::graphic::hinting>>() };
				std::vector<g2d::animation::keyframe<g2d::graphic::weight>> _weight { std::vector<g2d::animation::keyframe<g2d::graphic::weight>>() };
				std::vector<g2d::animation::keyframe<std::size_t>> _dots { std::vector<g2d::animation::keyframe<std::size_t>>() };
				std::vector<g2d::animation::keyframe<std::size_t>> _index { std::vector<g2d::animation::keyframe<std::size_t>>() };
				std::vector<g2d::animation::keyframe<bool>> _visible { std::vector<g2d::animation::keyframe<bool>>() };
				std::vector<g2d::animation::keyframe<bool>> _wireframe { std::vector<g2d::animation::keyframe<bool>>() };
				std::vector<g2d::animation::keyframe<g2d::graphic::form>> _form { std::vector<g2d::animation::keyframe<g2d::graphic::form>>() };
				std::vector<g2d::animation::keyframe<g2d::graphic::flip>> _flip { std::vector<g2d::animation::keyframe<g2d::graphic::flip>>() };
				std::vector<g2d::animation::keyframe<g2d::math::color>> _color { std::vector<g2d::animation::keyframe<g2d::math::color>>() };
				std::vector<g2d::animation::keyframe<g2d::math::point2dd>> _pivot { std::vector<g2d::animation::keyframe<g2d::math::point2dd>>() };
				std::vector<g2d::animation::keyframe<g2d::math::point3dd>> _position { std::vector<g2d::animation::keyframe<g2d::math::point3dd>>() };
				std::vector<g2d::animation::keyframe<g2d::math::size2dd>> _scale { std::vector<g2d::animation::keyframe<g2d::math::size2dd>>() };
				std::vector<g2d::animation::keyframe<g2d::math::rotated>> _rotate { std::vector<g2d::animation::keyframe<g2d::math::rotated>>() };
				std::vector<g2d::animation::keyframe<g2d::math::size2dd>> _size { std::vector<g2d::animation::keyframe<g2d::math::size2dd>>() };
		};
	}
}

#endif /* G2D_ANIMATION_TWEENER_H_ */
