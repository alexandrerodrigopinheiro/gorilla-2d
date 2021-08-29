#ifndef G2D_ANIMATION_ANIMATION_H_
#define G2D_ANIMATION_ANIMATION_H_

#pragma once

#include <string>
#include <iostream>

namespace g2d
{
	namespace animation
	{
		typedef enum play
		{
			play_off = 0,
			play_on
		}
		play;

		std::ostream& operator<<(std::ostream& stream, const g2d::animation::play& play);

		std::istream& operator>>(std::istream& stream, g2d::animation::play& play);

		g2d::animation::play to_play(const std::string& play);

		typedef enum control
		{
			control_single = 0,
			control_cycle,
			control_pingpong,
			control_elastic
		}
		control;

		std::ostream& operator<<(std::ostream& stream, const g2d::animation::control& control);

		std::istream& operator>>(std::istream& stream, g2d::animation::control& control);

		g2d::animation::control to_control(const std::string& control);

		typedef enum course
		{
			course_backward = 0,
			course_forward
		}
		course;

		std::ostream& operator<<(std::ostream& stream, const g2d::animation::course& course);

		std::istream& operator>>(std::istream& stream, g2d::animation::course& course);

		g2d::animation::course to_course(const std::string& course);

		typedef enum interpolation
		{
			interpolation_soft = 0,
			interpolation_hard
		}
		interpolation;

		std::ostream& operator<<(std::ostream& stream, const g2d::animation::interpolation& interpolation);

		std::istream& operator>>(std::istream& stream, g2d::animation::interpolation& interpolation);

		g2d::animation::interpolation to_interpolation(const std::string& interpolation);
	}
}

#endif /* G2D_ANIMATION_ANIMATION_H_ */
