#ifndef G2D_GRAPHIC_GRAPHIC_H_
#define G2D_GRAPHIC_GRAPHIC_H_

#pragma once

#include <cassert>
#include <iostream>
#include <string>

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>

namespace g2d
{
	namespace graphic
	{
		extern const std::size_t DPI;
		extern const int DURATION_INFINITY;
		extern const int START_SIZE_EQUAL_TO_END_SIZE; // the starting size of the particle is equal to the ending size.
		extern const int START_RADIUS_EQUAL_TO_END_RADIUS; // the starting radius of the particle is equal to the ending radius.

		typedef enum opacity
		{
			opacity_none,
			opacity_in,
			opacity_out,
			opacity_in_out,
			opacity_out_in
		}
		opacity;

		typedef enum scale
		{
			scale_none,
			scale_in,
			scale_out,
			scale_in_out,
			scale_out_in
		}
		scale;

		typedef enum rotate
		{
			rotate_none,
			rotate_in,
			rotate_out,
			rotate_in_out,
			rotate_out_in
		}
		rotate;

		typedef enum mode
	    {
			mode_gravity,
			mode_radius
	    }
		mode;

		typedef enum emission
		{
			emission_none,
	        emission_fire,
	        emission_firework,
	        emission_sun,
	        emission_galaxy,
	        emission_flower,
	        emission_meteor,
	        emission_spiral,
	        emission_explosion,
	        emission_smoke,
	        emission_snow,
	        emission_rain,
			emission_jet,
			emission_square,
			emission_star,
			emission_circle,
			emission_tan_cos,
			emission_tan_sin,
			emission_random_1,
			emission_random_2,
			emission_random_3,
			emission_random_4,
			emission_random_5,
			emission_random_6
		}
		emission;

		std::ostream& operator<<(std::ostream& stream, const g2d::graphic::emission& emission);

		std::istream& operator>>(std::istream& stream, g2d::graphic::emission& emission);

		g2d::graphic::emission to_emission(const std::string& emission);

		typedef enum flip
		{
			flip_none = 0,
			flip_horizontal,
			flip_vertical,
			flip_all
		}
		flip;

		std::ostream& operator<<(std::ostream& stream, const g2d::graphic::flip& flip);

		std::istream& operator>>(std::istream& stream, g2d::graphic::flip& flip);

		g2d::graphic::flip to_flip(const std::string& flip);

		typedef enum weight
		{
			weight_normal = 0,
			weight_bold,
			weight_italic,
			weight_underline,
			weight_strikethrough
		}
		weight;

		std::ostream& operator<<(std::ostream& stream, const g2d::graphic::weight& weight);

		std::istream& operator>>(std::istream& stream, g2d::graphic::weight& weight);

		g2d::graphic::weight to_weight(const std::string& weight);

		typedef enum hinting
		{
			hinting_none = 0,
			hinting_normal,
			hinting_light,
			hinting_mono
		}
		hinting;

		std::ostream& operator<<(std::ostream& stream, const g2d::graphic::hinting& hinting);

		std::istream& operator>>(std::istream& stream, g2d::graphic::hinting& hinting);

		g2d::graphic::hinting to_hinting(const std::string& hinting);

		typedef enum form
		{
			form_square = 0,
			form_circle
		}
		form;

		std::ostream& operator<<(std::ostream& stream, const g2d::graphic::form& form);

		std::istream& operator>>(std::istream& stream, g2d::graphic::form& form);

		g2d::graphic::form to_form(const std::string& form);

		typedef enum filter
		{
			filter_nearest = GL_NEAREST,
			filter_linear = GL_LINEAR
		}
		filter;

		std::ostream& operator<<(std::ostream& stream, const g2d::graphic::filter& filter);

		std::istream& operator>>(std::istream& stream, g2d::graphic::filter& filter);

		g2d::graphic::filter to_filter(const std::string& filter);

		typedef enum wrap
		{
			wrap_nearest = GL_NEAREST,
			wrap_clamp = GL_CLAMP
		}
		wrap;

		std::ostream& operator<<(std::ostream& stream, const g2d::graphic::wrap& wrap);

		std::istream& operator>>(std::istream& stream, g2d::graphic::wrap& wrap);

		g2d::graphic::wrap to_wrap(const std::string& wrap);
	}
}

#endif /* G2D_GRAPHIC_GRAPHIC_H_ */
