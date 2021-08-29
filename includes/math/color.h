#ifndef G2D_MATH_COLOR_H_
#define G2D_MATH_COLOR_H_

#pragma once

#include <string>
#include <iostream>

#include "../basic/basic.h"

#include "math.h"

namespace g2d
{
	namespace math
	{
		class color
		{
			public:

				color();

				color(double color);

				color(const g2d::math::color& color);

				color(double r, double g, double b, double a);

				~color();

				void set(double color);

				void set(const g2d::math::color& color);

				void set(double r, double g, double b, double a);

				void r(double r);

				void g(double g);

				void b(double b);

				void a(double a);

				double r() const;

				double g() const;

				double b() const;

				double a() const;

				double normal_r() const;

				double normal_g() const;

				double normal_b() const;

				double normal_a() const;

				g2d::math::color annul() const;

				bool null() const;

				void string_to(const std::string& r, const std::string& g, const std::string& b, const std::string& a);

				g2d::math::color operator++();

				g2d::math::color operator++(int);

				g2d::math::color operator--();

				g2d::math::color operator--(int);

				static g2d::math::color ALICEBLUE();

				static g2d::math::color ANTIQUEWHITE();

				static g2d::math::color AQUA();

				static g2d::math::color AQUAMARINE();

				static g2d::math::color AZURE();

				static g2d::math::color BEIGE();

				static g2d::math::color BISQUE();

				static g2d::math::color BLACK();

				static g2d::math::color BLANCHEDALMOND();

				static g2d::math::color BLUE();

				static g2d::math::color BLUELIGHT();

				static g2d::math::color BLUEVIOLET();

				static g2d::math::color BROWN();

				static g2d::math::color BURLYWOOD();

				static g2d::math::color CADETBLUE();

				static g2d::math::color CHARTREUSE();

				static g2d::math::color CHOCOLATE();

				static g2d::math::color CORAL();

				static g2d::math::color CORNFLOWERBLUE();

				static g2d::math::color CORNSILK();

				static g2d::math::color CRIMSON();

				static g2d::math::color CYAN();

				static g2d::math::color DARKBLUE();

				static g2d::math::color DARKCYAN();

				static g2d::math::color DARKGOLDENROD();

				static g2d::math::color DARKGRAY();

				static g2d::math::color DARKGREEN();

				static g2d::math::color DARKKHAKI();

				static g2d::math::color DARKMAGENTA();

				static g2d::math::color DARKOLIVEGREEN();

				static g2d::math::color DARKORANGE();

				static g2d::math::color DARKORCHID();

				static g2d::math::color DARKRED();

				static g2d::math::color DARKSALMON();

				static g2d::math::color DARKSEAGREEN();

				static g2d::math::color DARKSLATEBLUE();

				static g2d::math::color DARKSLATEGRAY();

				static g2d::math::color DARKSLATEGREY();

				static g2d::math::color DARKTURQUOISE();

				static g2d::math::color DARKVIOLET();

				static g2d::math::color DEEPPINK();

				static g2d::math::color DEEPSKYBLUE();

				static g2d::math::color DIMGRAY();

				static g2d::math::color DODGERBLUE();

				static g2d::math::color FIREBRICK();

				static g2d::math::color FLORALWHITE();

				static g2d::math::color FORESTGREEN();

				static g2d::math::color FUCHSIA();

				static g2d::math::color GAINSBORO();

				static g2d::math::color GHOSTWHITE();

				static g2d::math::color GOLD();

				static g2d::math::color GOLDENROD();

				static g2d::math::color GREY();

				static g2d::math::color GREEN();

				static g2d::math::color GREENYELLOW();

				static g2d::math::color HONEYDEW();

				static g2d::math::color HOTPINK();

				static g2d::math::color INDIANRED();

				static g2d::math::color INDIGO();

				static g2d::math::color IVORY();

				static g2d::math::color KHAKI();

				static g2d::math::color LAVENDER();

				static g2d::math::color LAVENDERBLUSH();

				static g2d::math::color LAWNGREEN();

				static g2d::math::color LEMONCHIFFON();

				static g2d::math::color LIGHTBLUE();

				static g2d::math::color LIGHTCORAL();

				static g2d::math::color LIGHTCYAN();

				static g2d::math::color LIGHTGOLDENRODYELLOW();

				static g2d::math::color LIGHTGREY();

				static g2d::math::color LIGHTGREEN();

				static g2d::math::color LIGHTPINK();

				static g2d::math::color LIGHTSALMON();

				static g2d::math::color LIGHTSEAGREEN();

				static g2d::math::color LIGHTSKYBLUE();

				static g2d::math::color LIGHTSLATEGRAY();

				static g2d::math::color LIGHTSTEELBLUE();

				static g2d::math::color LIGHTYELLOW();

				static g2d::math::color LIME();

				static g2d::math::color LIMEGREEN();

				static g2d::math::color LINEN();

				static g2d::math::color MAGENTA();

				static g2d::math::color MAROON();

				static g2d::math::color MEDIUMAQUAMARINE();

				static g2d::math::color MEDIUMBLUE();

				static g2d::math::color MEDIUMORCHID();

				static g2d::math::color MEDIUMPURPLE();

				static g2d::math::color MEDIUMSEAGREEN();

				static g2d::math::color MEDIUMSLATEBLUE();

				static g2d::math::color MEDIUMSPRINGGREEN();

				static g2d::math::color MEDIUMTURQUOISE();

				static g2d::math::color MEDIUMVIOLETRED();

				static g2d::math::color MIDNIGHTBLUE();

				static g2d::math::color MINTCREAM();

				static g2d::math::color MISTYROSE();

				static g2d::math::color MOCCASIN();

				static g2d::math::color NAVAJOWHITE();

				static g2d::math::color NAVY();

				static g2d::math::color OLDLACE();

				static g2d::math::color OLIVE();

				static g2d::math::color OLIVEDRAB();

				static g2d::math::color ORANGE();

				static g2d::math::color ORANGERED();

				static g2d::math::color ORCHID();

				static g2d::math::color PALEGOLDENROD();

				static g2d::math::color PALEGREEN();

				static g2d::math::color PALETURQUOISE();

				static g2d::math::color PALEVIOLETRED();

				static g2d::math::color PAPAYAWHIP();

				static g2d::math::color PEACHPUFF();

				static g2d::math::color PERU();

				static g2d::math::color PINK();

				static g2d::math::color PLUM();

				static g2d::math::color POWDERBLUE();

				static g2d::math::color PURPLE();

				static g2d::math::color REBECCAPURPLE();

				static g2d::math::color RED();

				static g2d::math::color ROSYBROWN();

				static g2d::math::color ROYALBLUE();

				static g2d::math::color SADDLEBROWN();

				static g2d::math::color SALMON();

				static g2d::math::color SANDYBROWN();

				static g2d::math::color SEAGREEN();

				static g2d::math::color SEASHELL();

				static g2d::math::color SIENNA();

				static g2d::math::color SILVER();

				static g2d::math::color SKYBLUE();

				static g2d::math::color SLATEBLUE();

				static g2d::math::color SLATEGRAY();

				static g2d::math::color SNOW();

				static g2d::math::color SPRINGGREEN();

				static g2d::math::color STEELBLUE();

				static g2d::math::color TAN();

				static g2d::math::color TEAL();

				static g2d::math::color THISTLE();

				static g2d::math::color TOMATO();

				static g2d::math::color TURQUOISE();

				static g2d::math::color VIOLET();

				static g2d::math::color WHEAT();

				static g2d::math::color WHITE();

				static g2d::math::color WHITESMOKE();

				static g2d::math::color YELLOW();

				static g2d::math::color YELLOWGREEN();

				const g2d::math::color& operator=(const g2d::math::color& right);

				const g2d::math::color& operator+(const g2d::math::color& right);

				const g2d::math::color& operator-(const g2d::math::color& right);

				const g2d::math::color& operator/(const g2d::math::color& right);

				const g2d::math::color& operator*(const g2d::math::color& right);

				const g2d::math::color& operator+=(const g2d::math::color& right);

				const g2d::math::color& operator-=(const g2d::math::color& right);

				const g2d::math::color& operator*=(const g2d::math::color& right);

				const g2d::math::color& operator/=(const g2d::math::color& right);

				bool operator==(const g2d::math::color& right);

				bool operator!=(const g2d::math::color& right);

				bool operator>(const g2d::math::color& right);

				bool operator<(const g2d::math::color& right);

				bool operator>=(const g2d::math::color& right);

				bool operator<=(const g2d::math::color& right);

				const g2d::math::color& operator=(double right);

				const g2d::math::color& operator+(double right);

				const g2d::math::color& operator-(double right);

				const g2d::math::color& operator/(double right);

				const g2d::math::color& operator*(double right);

				const g2d::math::color& operator+=(double right);

				const g2d::math::color& operator-=(double right);

				const g2d::math::color& operator*=(double right);

				const g2d::math::color& operator/=(double right);

				bool operator==(double right);

				bool operator!=(double right);

				bool operator>(double right);

				bool operator<(double right);

				bool operator>=(double right);

				bool operator<=(double right);

				static double to_hex(const std::string& hex);

				static g2d::math::color hex_to_color(const std::string& hex);

			private:

				color(double r, double g, double b, double a, bool null);

				double _r { g2d::math::CHANNEL_END };
				double _g { g2d::math::CHANNEL_END };
				double _b { g2d::math::CHANNEL_END };
				double _a { g2d::math::CHANNEL_END };
				bool _null { false };
		};

		std::ostream& operator<<(std::ostream& stream, const g2d::math::color& right);

		std::istream& operator>>(std::istream& stream, g2d::math::color& right);
	}
}

#endif /* G2D_MATH_COLOR_H_ */
