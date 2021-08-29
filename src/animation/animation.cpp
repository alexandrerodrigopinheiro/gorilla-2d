#include "../../includes/animation/animation.h"

std::ostream& g2d::animation::operator<<(std::ostream& stream, const g2d::animation::play& play)
{
	switch (play)
	{
		case g2d::animation::play::play_off:
		{
			stream << "play { off }";

			break;
		}
		case g2d::animation::play::play_on:
		{
			stream << "play { on }";

			break;
		}
	}

	return stream;
}

std::istream& g2d::animation::operator>>(std::istream& stream, g2d::animation::play& play)
{
	std::string garbage;
	std::string value;

	stream >> garbage >> garbage >> value >> garbage;

	if (value == "off")
	{
		play = g2d::animation::play::play_off;
	}
	else if (value == "on")
	{
		play = g2d::animation::play::play_on;
	}

	return stream;
}

g2d::animation::play g2d::animation::to_play(const std::string& play)
{
	g2d::animation::play out;

	if (play == "off")
	{
		out = g2d::animation::play::play_off;
	}
	else if (play == "on")
	{
		out = g2d::animation::play::play_on;
	}

	return out;
}

std::ostream& g2d::animation::operator<<(std::ostream& stream, const g2d::animation::control& control)
{
	switch (control)
	{
		case g2d::animation::control::control_single:
		{
			stream << "control { single }";

			break;
		}
		case g2d::animation::control::control_cycle:
		{
			stream << "control { cycle }";

			break;
		}
		case g2d::animation::control::control_pingpong:
		{
			stream << "control { pingpong }";

			break;
		}
		case g2d::animation::control::control_elastic:
		{
			stream << "control { elastic }";

			break;
		}
	}

	return stream;
}

std::istream& g2d::animation::operator>>(std::istream& stream, g2d::animation::control& control)
{
	std::string garbage;
	std::string value;

	stream >> garbage >> garbage >> value >> garbage;

	if (value == "single")
	{
		control = g2d::animation::control::control_single;
	}
	else if (value == "cycle")
	{
		control = g2d::animation::control::control_cycle;
	}
	else if (garbage == "pingpong")
	{
		control = g2d::animation::control::control_pingpong;
	}
	else if (value == "elastic")
	{
		control = g2d::animation::control::control_elastic;
	}

	return stream;
}

g2d::animation::control g2d::animation::to_control(const std::string& control)
{
	g2d::animation::control out;

	if (control == "single")
	{
		out = g2d::animation::control::control_single;
	}
	else if (control == "cycle")
	{
		out = g2d::animation::control::control_cycle;
	}
	else if (control == "pingpong")
	{
		out = g2d::animation::control::control_pingpong;
	}
	else if (control == "elastic")
	{
		out = g2d::animation::control::control_elastic;
	}

	return out;
}

std::ostream& g2d::animation::operator<<(std::ostream& stream, const g2d::animation::course& course)
{
	switch (course)
	{
		case g2d::animation::course::course_backward:
		{
			stream << "course { backward }";

			break;
		}
		case g2d::animation::course::course_forward:
		{
			stream << "course { forward }";

			break;
		}
	}

	return stream;
}

std::istream& g2d::animation::operator>>(std::istream& stream, g2d::animation::course& course)
{
	std::string garbage;
	std::string value;

	stream >> garbage >> garbage >> value >> garbage;

	if (value == "backward")
	{
		course = g2d::animation::course::course_backward;
	}
	else if (value == "forward")
	{
		course = g2d::animation::course::course_forward;
	}

	return stream;
}

g2d::animation::course g2d::animation::to_course(const std::string& course)
{
	g2d::animation::course out;

	if (course == "backward")
	{
		out = g2d::animation::course::course_backward;
	}
	else if (course == "forward")
	{
		out = g2d::animation::course::course_forward;
	}

	return out;
}

std::ostream& g2d::animation::operator<<(std::ostream& stream, const g2d::animation::interpolation& interpolation)
{
	switch (interpolation)
	{
		case g2d::animation::interpolation::interpolation_soft:
		{
			stream << "interpolation { soft }";

			break;
		}
		case g2d::animation::interpolation::interpolation_hard:
		{
			stream << "interpolation { hard }";

			break;
		}
	}

	return stream;
}

std::istream& g2d::animation::operator>>(std::istream& stream, g2d::animation::interpolation& interpolation)
{
	std::string garbage;
	std::string value;

	stream >> garbage >> garbage >> value >> garbage;

	if (value == "soft")
	{
		interpolation = g2d::animation::interpolation::interpolation_soft;
	}
	else if (value == "hard")
	{
		interpolation = g2d::animation::interpolation::interpolation_hard;
	}

	return stream;
}

g2d::animation::interpolation g2d::animation::to_interpolation(const std::string& interpolation)
{
	g2d::animation::interpolation out;

	if (interpolation == "soft")
	{
		out = g2d::animation::interpolation::interpolation_soft;
	}
	else if (interpolation == "hard")
	{
		out = g2d::animation::interpolation::interpolation_hard;
	}

	return out;
}
