#include "../../includes/math/math.h"

const std::size_t g2d::math::LIFE = 500;
const std::string g2d::math::BASE64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const double g2d::math::PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;
const double g2d::math::GRAVITY = 9.83;
const double g2d::math::RADIANS_TO_DEGREES = 0.0174532925;
const double g2d::math::CHANNEL_BEGIN = 0.0;
const double g2d::math::CHANNEL_END = 255.0;

double g2d::math::bounce_out(double t, double b , double c, double d)
{
	if ((t /= d) < (1 / 2.75f))
	{
		return c * (7.5625f * t * t) + b;
	}
	else if (t < (2 / 2.75f))
	{
		double post = t -= (1.5f / 2.75f);

		return c * (7.5625f * (post) * t + .75f) + b;
	}
	else if (t < (2.5 / 2.75))
	{
		double post = t -= (2.25f / 2.75f);

		return c * (7.5625f * (post) * t + .9375f) + b;
	}

	double post = t -= (2.625f / 2.75f);

	return c * (7.5625f * (post) * t + .984375f) + b;
}

double g2d::math::bounce_in(double t,double b , double c, double d)
{
	return c - g2d::math::bounce_out(d - t, 0, c, d) + b;
}

double g2d::math::bounce_in_out(double t, double b, double c, double d)
{
	if (t < d / 2)
	{
		return g2d::math::bounce_in(t * 2, 0, c, d) * 0.5f + b;
	}
	else
	{
		return g2d::math::bounce_out(t * 2 - d, 0, c, d) * 0.5f + c * 0.5f + b;
	}
}

bool g2d::math::is_math(const std::string& str)
{
	for (std::size_t i = 0; i < str.length(); i++)
	{
		char arg = str[i];

		if ((isalnum(arg) || (arg == '+') || (arg == '/')))
		{
			return true;
		}
	}

	return false;
}

bool g2d::math::is_math(char arg)
{
	if ((isalnum(arg) || (arg == '+') || (arg == '/')))
	{
		return true;
	}

	return false;
}

double g2d::math::degrees_to_radians(double angle)
{
    return angle * 0.01745329252f;
}

double g2d::math::radians_to_degrees(double angle)
{
    return angle * 57.29577951f;
}

g2d::math::point2dd g2d::math::normalize_point2d(double x, double y)
{
    double n = x * x + y * y;

    // already normalized.
    if (n == 1.0f)
    {
        return g2d::math::point2dd(x, y);
    }

    n = std::sqrt(n);

    // too close to zero.
    if (n < 1e-5)
    {
    	return g2d::math::point2dd(x, y);
    }

    n = 1.0f / n;

    return g2d::math::point2dd(x * n, y * n);
}

double g2d::math::random_m11(unsigned int* seed)
{
    *seed = * seed * 134775813 + 1;

    union
    {
        uint32_t d;
        float f;
    } u;

    u.d = (((uint32_t)(*seed) & 0x7fff) << 8) | 0x40000000;

    return static_cast<double>(u.f - 3.0f);
}
