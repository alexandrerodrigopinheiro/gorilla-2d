#include "../../includes/graphic/graphic.h"

const std::size_t g2d::graphic::DPI = 72;
const int g2d::graphic::DURATION_INFINITY = -1;
const int g2d::graphic::START_SIZE_EQUAL_TO_END_SIZE = -1;
const int g2d::graphic::START_RADIUS_EQUAL_TO_END_RADIUS = -1;

std::ostream& g2d::graphic::operator<<(std::ostream& stream, const g2d::graphic::emission& emission)
{
	switch (emission)
	{
		case g2d::graphic::emission::emission_none:
		{
			stream << "emission { none }";
			break;
		}
		case g2d::graphic::emission::emission_fire:
		{
			stream << "emission { fire }";
			break;
		}
		case g2d::graphic::emission::emission_firework:
		{
			stream << "emission { firework }";
			break;
		}
		case g2d::graphic::emission::emission_sun:
		{
			stream << "emission { sun }";
			break;
		}
		case g2d::graphic::emission::emission_galaxy:
		{
			stream << "emission { galaxy }";
			break;
		}
		case g2d::graphic::emission::emission_flower:
		{
			stream << "emission { flower }";
			break;
		}
		case g2d::graphic::emission::emission_meteor:
		{
			stream << "emission { meteor }";
			break;
		}
		case g2d::graphic::emission::emission_spiral:
		{
			stream << "emission { spiral }";
			break;
		}
		case g2d::graphic::emission::emission_explosion:
		{
			stream << "emission { explosion }";
			break;
		}
		case g2d::graphic::emission::emission_smoke:
		{
			stream << "emission { smoke }";
			break;
		}
		case g2d::graphic::emission::emission_snow:
		{
			stream << "emission { snow }";
			break;
		}
		case g2d::graphic::emission::emission_rain:
		{
			stream << "emission { rain }";
			break;
		}
		case g2d::graphic::emission::emission_jet:
		{
			stream << "emission { jet }";
			break;
		}
		case g2d::graphic::emission::emission_square:
		{
			stream << "emission { normal }";
			break;
		}
		case g2d::graphic::emission::emission_star:
		{
			stream << "emission { star }";
			break;
		}
		case g2d::graphic::emission::emission_circle:
		{
			stream << "emission { circle }";
			break;
		}
		case g2d::graphic::emission::emission_tan_cos:
		{
			stream << "emission { tan_cos }";
			break;
		}
		case g2d::graphic::emission::emission_tan_sin:
		{
			stream << "emission { tan_sin }";
			break;
		}
		case g2d::graphic::emission::emission_random_1:
		{
			stream << "emission { random_1 }";
			break;
		}
		case g2d::graphic::emission::emission_random_2:
		{
			stream << "emission { random_2 }";
			break;
		}
		case g2d::graphic::emission::emission_random_3:
		{
			stream << "emission { random_3 }";
			break;
		}
		case g2d::graphic::emission::emission_random_4:
		{
			stream << "emission { random_4 }";
			break;
		}
		case g2d::graphic::emission::emission_random_5:
		{
			stream << "emission { random_5 }";
			break;
		}
		case g2d::graphic::emission::emission_random_6:
		{
			stream << "emission { random_6 }";
			break;
		}
	}

	return stream;
}

std::istream& g2d::graphic::operator>>(std::istream& stream, g2d::graphic::emission& emission)
{
	std::string garbage;
	std::string value;

	stream >> garbage;
	stream >> garbage;
	stream >> value;
	stream >> garbage;

	if (value == "none")
	{
		emission = g2d::graphic::emission::emission_none;
	}
	else if (value == "fire")
	{
		emission = g2d::graphic::emission::emission_fire;
	}
	else if (value == "firework")
	{
		emission = g2d::graphic::emission::emission_firework;
	}
	else if (value == "sun")
	{
		emission = g2d::graphic::emission::emission_sun;
	}
	else if (value == "galaxy")
	{
		emission = g2d::graphic::emission::emission_galaxy;
	}
	else if (value == "flower")
	{
		emission = g2d::graphic::emission::emission_flower;
	}
	else if (value == "meteor")
	{
		emission = g2d::graphic::emission::emission_meteor;
	}
	else if (value == "spiral")
	{
		emission = g2d::graphic::emission::emission_spiral;
	}
	else if (value == "explosion")
	{
		emission = g2d::graphic::emission::emission_explosion;
	}
	else if (value == "smoke")
	{
		emission = g2d::graphic::emission::emission_smoke;
	}
	else if (value == "snow")
	{
		emission = g2d::graphic::emission::emission_snow;
	}
	else if (value == "rain")
	{
		emission = g2d::graphic::emission::emission_rain;
	}
	else if (value == "jet")
	{
		emission = g2d::graphic::emission::emission_jet;
	}
	else if (value == "square")
	{
		emission = g2d::graphic::emission::emission_square;
	}
	else if (value == "star")
	{
		emission = g2d::graphic::emission::emission_star;
	}
	else if (value == "circle")
	{
		emission = g2d::graphic::emission::emission_circle;
	}
	else if (value == "tan_cos")
	{
		emission = g2d::graphic::emission::emission_tan_cos;
	}
	else if (value == "tan_sin")
	{
		emission = g2d::graphic::emission::emission_tan_sin;
	}
	else if (value == "random_1")
	{
		emission = g2d::graphic::emission::emission_random_1;
	}
	else if (value == "random_2")
	{
		emission = g2d::graphic::emission::emission_random_2;
	}
	else if (value == "random_3")
	{
		emission = g2d::graphic::emission::emission_random_3;
	}
	else if (value == "random_4")
	{
		emission = g2d::graphic::emission::emission_random_4;
	}
	else if (value == "random_5")
	{
		emission = g2d::graphic::emission::emission_random_5;
	}
	else if (value == "random_6")
	{
		emission = g2d::graphic::emission::emission_random_6;
	}

	return stream;
}

g2d::graphic::emission g2d::graphic::to_emission(const std::string& emission)
{
	g2d::graphic::emission out;

	if (emission == "none")
	{
		out = g2d::graphic::emission::emission_none;
	}
	else if (emission == "fire")
	{
		out = g2d::graphic::emission::emission_fire;
	}
	else if (emission == "firework")
	{
		out = g2d::graphic::emission::emission_firework;
	}
	else if (emission == "sun")
	{
		out = g2d::graphic::emission::emission_sun;
	}
	else if (emission == "galaxy")
	{
		out = g2d::graphic::emission::emission_galaxy;
	}
	else if (emission == "flower")
	{
		out = g2d::graphic::emission::emission_flower;
	}
	else if (emission == "meteor")
	{
		out = g2d::graphic::emission::emission_meteor;
	}
	else if (emission == "spiral")
	{
		out = g2d::graphic::emission::emission_spiral;
	}
	else if (emission == "explosion")
	{
		out = g2d::graphic::emission::emission_explosion;
	}
	else if (emission == "smoke")
	{
		out = g2d::graphic::emission::emission_smoke;
	}
	else if (emission == "snow")
	{
		out = g2d::graphic::emission::emission_snow;
	}
	else if (emission == "rain")
	{
		out = g2d::graphic::emission::emission_rain;
	}
	else if (emission == "jet")
	{
		out = g2d::graphic::emission::emission_jet;
	}
	else if (emission == "square")
	{
		out = g2d::graphic::emission::emission_square;
	}
	else if (emission == "star")
	{
		out = g2d::graphic::emission::emission_star;
	}
	else if (emission == "circle")
	{
		out = g2d::graphic::emission::emission_circle;
	}
	else if (emission == "tan_cos")
	{
		out = g2d::graphic::emission::emission_tan_cos;
	}
	else if (emission == "tan_sin")
	{
		out = g2d::graphic::emission::emission_tan_sin;
	}
	else if (emission == "random_1")
	{
		out = g2d::graphic::emission::emission_random_1;
	}
	else if (emission == "random_2")
	{
		out = g2d::graphic::emission::emission_random_2;
	}
	else if (emission == "random_3")
	{
		out = g2d::graphic::emission::emission_random_3;
	}
	else if (emission == "random_4")
	{
		out = g2d::graphic::emission::emission_random_4;
	}
	else if (emission == "random_5")
	{
		out = g2d::graphic::emission::emission_random_5;
	}
	else if (emission == "random_6")
	{
		out = g2d::graphic::emission::emission_random_6;
	}

	return out;
}

std::ostream& g2d::graphic::operator<<(std::ostream& stream, const g2d::graphic::flip& flip)
{
	switch (flip)
	{
		case g2d::graphic::flip::flip_none:
		{
			stream << " flip { none }";

			break;
		}
		case g2d::graphic::flip::flip_horizontal:
		{
			stream << " flip { horizontal }";

			break;
		}
		case g2d::graphic::flip::flip_vertical:
		{
			stream << " flip { vertical }";

			break;
		}
		case g2d::graphic::flip::flip_all:
		{
			stream << " flip { all }";

			break;
		}
	}

	return stream;
}

std::istream& g2d::graphic::operator>>(std::istream& stream, g2d::graphic::flip& flip)
{
	std::string garbage;
	std::string value;

	stream >> garbage;
	stream >> garbage;
	stream >> value;
	stream >> garbage;

	if (value == "none")
	{
		flip = g2d::graphic::flip::flip_none;
	}
	else if (value == "horizontal")
	{
		flip = g2d::graphic::flip::flip_horizontal;
	}
	else if (value == "vertical")
	{
		flip = g2d::graphic::flip::flip_vertical;
	}
	else if (value == "all")
	{
		flip = g2d::graphic::flip::flip_all;
	}

	return stream;
}

g2d::graphic::flip g2d::graphic::to_flip(const std::string& flip)
{
	g2d::graphic::flip out;

	if (flip == "none")
	{
		out = g2d::graphic::flip::flip_none;
	}
	else if (flip == "horizontal")
	{
		out = g2d::graphic::flip::flip_horizontal;
	}
	else if (flip == "vertical")
	{
		out = g2d::graphic::flip::flip_vertical;
	}
	else if (flip == "all")
	{
		out = g2d::graphic::flip::flip_all;
	}

	return out;
}

std::ostream& g2d::graphic::operator<<(std::ostream& stream, const g2d::graphic::weight& weight)
{
	switch (weight)
	{
		case g2d::graphic::weight::weight_normal:
		{
			stream << "weight { normal }";

			break;
		}
		case g2d::graphic::weight::weight_bold:
		{
			stream << "weight { bold }";

			break;
		}
		case g2d::graphic::weight::weight_italic:
		{
			stream << "weight { italic }";

			break;
		}
		case g2d::graphic::weight::weight_underline:
		{
			stream << "weight { underline }";

			break;
		}
		case g2d::graphic::weight::weight_strikethrough:
		{
			stream << "weight { strikethrough }";

			break;
		}
	}

	return stream;
}

std::istream& g2d::graphic::operator>>(std::istream& stream, g2d::graphic::weight& weight)
{
	std::string garbage;
	std::string value;

	stream >> garbage;
	stream >> garbage;
	stream >> value;
	stream >> garbage;

	if (value == "normal")
	{
		weight = g2d::graphic::weight::weight_normal;
	}
	else if (value == "bold")
	{
		weight = g2d::graphic::weight::weight_bold;
	}
	else if (value == "italic")
	{
		weight = g2d::graphic::weight::weight_italic;
	}
	else if (value == "underline")
	{
		weight = g2d::graphic::weight::weight_underline;
	}
	else if (value == "strikethrough")
	{
		weight = g2d::graphic::weight::weight_strikethrough;
	}

	return stream;
}

g2d::graphic::weight g2d::graphic::to_weight(const std::string& weight)
{
	g2d::graphic::weight out;

	if (weight == "normal")
	{
		out = g2d::graphic::weight::weight_normal;
	}
	else if (weight == "bold")
	{
		out = g2d::graphic::weight::weight_bold;
	}
	else if (weight == "italic")
	{
		out = g2d::graphic::weight::weight_italic;
	}
	else if (weight == "underline")
	{
		out = g2d::graphic::weight::weight_underline;
	}
	else if (weight == "strikethrough")
	{
		out = g2d::graphic::weight::weight_strikethrough;
	}

	return out;
}

std::ostream& g2d::graphic::operator<<(std::ostream& stream, const g2d::graphic::hinting& hinting)
{
	switch (hinting)
	{
		case g2d::graphic::hinting::hinting_none:
		{
			stream << "hinting { none }";

			break;
		}
		case g2d::graphic::hinting::hinting_normal:
		{
			stream << "hinting { normal}";

			break;
		}
		case g2d::graphic::hinting::hinting_light:
		{
			stream << "hinting { light }";

			break;
		}
		case g2d::graphic::hinting::hinting_mono:
		{
			stream << "hinting { mono }";

			break;
		}
	}

	return stream;
}

std::istream& g2d::graphic::operator>>(std::istream& stream, g2d::graphic::hinting& hinting)
{
	std::string garbage;
	std::string value;

	stream >> garbage;
	stream >> garbage;
	stream >> value;
	stream >> garbage;

	if (value == "none")
	{
		hinting = g2d::graphic::hinting::hinting_none;
	}
	else if (value == "normal")
	{
		hinting = g2d::graphic::hinting::hinting_normal;
	}
	else if (value == "light")
	{
		hinting = g2d::graphic::hinting::hinting_light;
	}
	else if (value == "mono")
	{
		hinting = g2d::graphic::hinting::hinting_mono;
	}

	return stream;
}

g2d::graphic::hinting g2d::graphic::to_hinting(const std::string& hinting)
{
	g2d::graphic::hinting out;

	if (hinting == "none")
	{
		out = g2d::graphic::hinting::hinting_none;
	}
	else if (hinting == "normal")
	{
		out = g2d::graphic::hinting::hinting_normal;
	}
	else if (hinting == "light")
	{
		out = g2d::graphic::hinting::hinting_light;
	}
	else if (hinting == "mono")
	{
		out = g2d::graphic::hinting::hinting_mono;
	}

	return out;
}

std::ostream& g2d::graphic::operator<<(std::ostream& stream, const g2d::graphic::form& form)
{
	switch (form)
	{
		case g2d::graphic::form::form_square:
		{
			stream << "form { square }";

			break;
		}
		case g2d::graphic::form::form_circle:
		{
			stream << "form { circle }";

			break;
		}
	}

	return stream;
}

std::istream& g2d::graphic::operator>>(std::istream& stream, g2d::graphic::form& form)
{
	std::string garbage;
	std::string value;

	stream >> garbage;
	stream >> garbage;
	stream >> value;
	stream >> garbage;

	if (value == "square")
	{
		form = g2d::graphic::form::form_square;
	}
	else if (value == "circle")
	{
		form = g2d::graphic::form::form_circle;
	}

	return stream;
}

g2d::graphic::form g2d::graphic::to_form(const std::string& form)
{
	g2d::graphic::form out;

	if (form == "square")
	{
		out = g2d::graphic::form::form_square;
	}
	else if (form == "circle")
	{
		out = g2d::graphic::form::form_circle;
	}

	return out;
}

std::ostream& g2d::graphic::operator<<(std::ostream& stream, const g2d::graphic::filter& filter)
{
	switch (filter)
	{
		default:
		{
			break;
		}
		case g2d::graphic::filter::filter_nearest:
		{
			stream << " filter { nearest }";

			break;
		}
		case g2d::graphic::filter::filter_linear:
		{
			stream << " filter { linear }";

			break;
		}
	}

	return stream;
}

std::istream& g2d::graphic::operator>>(std::istream& stream, g2d::graphic::filter& filter)
{
	std::string garbage;
	std::string value;

	stream >> garbage;
	stream >> garbage;
	stream >> value;
	stream >> garbage;

	if (value == "nearest")
	{
		filter = g2d::graphic::filter::filter_linear;
	}
	else if (value == "linear")
	{
		filter = g2d::graphic::filter::filter_linear;
	}

	return stream;
}

g2d::graphic::filter g2d::graphic::to_filter(const std::string& filter)
{
	g2d::graphic::filter out;

	if (filter == "nearest")
	{
		out = g2d::graphic::filter::filter_linear;
	}
	else if (filter == "linear")
	{
		out = g2d::graphic::filter::filter_linear;
	}

	return out;
}

std::ostream& g2d::graphic::operator<<(std::ostream& stream, const g2d::graphic::wrap& wrap)
{
	switch (wrap)
	{
		default:
		{
			break;
		}
		case g2d::graphic::wrap::wrap_nearest:
		{
			stream << "wrap { nearest }";

			break;
		}
		case g2d::graphic::wrap::wrap_clamp:
		{
			stream << "wrap { clamp }";

			break;
		}
	}

	return stream;
}

std::istream& g2d::graphic::operator>>(std::istream& stream, g2d::graphic::wrap& wrap)
{
	std::string garbage;
	std::string value;

	stream >> garbage;
	stream >> garbage;
	stream >> value;
	stream >> garbage;

	if (value == "nearest")
	{
		wrap = g2d::graphic::wrap::wrap_nearest;
	}
	else if (value == "clamp")
	{
		wrap = g2d::graphic::wrap::wrap_clamp;
	}

	return stream;
}

g2d::graphic::wrap g2d::graphic::to_wrap(const std::string& wrap)
{
	g2d::graphic::wrap out;

	if (wrap == "nearest")
	{
		out = g2d::graphic::wrap::wrap_nearest;
	}
	else if (wrap == "clamp")
	{
		out = g2d::graphic::wrap::wrap_clamp;
	}

	return out;
}
