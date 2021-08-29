#ifndef G2D_MATH_MATH_H_
#define G2D_MATH_MATH_H_

#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <functional>

#include "point2d.h"

namespace g2d
{
	namespace math
	{
		extern const std::size_t LIFE;
		extern const std::string BASE64;
		extern const double PI;
		extern const double GRAVITY;
		extern const double RADIANS_TO_DEGREES;
		extern const double CHANNEL_BEGIN;
		extern const double CHANNEL_END;

		template<typename T>
		T invert(T src);

		template<typename T>
		T rule_of_three(T val, T left, T right);

		template<typename T, typename M>
		T rule_of_three(T val, M left, M right);

		template<typename T, typename M>
		T rule_of_three(T val, M left, T right);

		template<typename T, typename M>
		T rule_of_three(T val, T left, M right);

		template<typename T>
		T normal(T value, T min, T max);

		template<typename T, typename M>
		T normal(T value, M min, M max);

		template<typename T, typename M>
		T normal(T value, M min, T max);

		template<typename T, typename M>
		T normal(T value, T min, M max);

		template<typename T>
		T clamp(T value, T min, T max);

		template<typename T, typename M>
		T clamp(T value, M min, M max);

		template<typename T, typename M>
		T clamp(T value, M min, T max);

		template<typename T, typename M>
		T clamp(T value, T min, M max);

		template<typename T>
		T wrap(T value, T min, T max);

		template<typename T, typename M>
		T wrap(T value, M min, M max);

		template<typename T, typename M>
		T wrap(T value, M min, T max);

		template<typename T, typename M>
		T wrap(T value, T min, M max);

		template<typename T>
		T loop(T value, T min, T max);

		template<typename T, typename M>
		T loop(T value, M min, M max);

		template<typename T, typename M>
		T loop(T value, M min, T max);

		template<typename T, typename M>
		T loop(T value, T min, M max);

		template<typename T>
		T normalize(T value, T min, T max);

		template<typename T, typename M>
		T normalize(T value, M min, M max);

		template<typename T, typename M>
		T normalize(T value, M min, T max);

		template<typename T, typename M>
		T normalize(T value, T min, M max);

		template<typename T>
		T denormalize(T value, T min, T max);

		template<typename T, typename M>
		T denormalize(T value, M min, M max);

		template<typename T, typename M>
		T denormalize(T value, M min, T max);

		template<typename T, typename M>
		T denormalize(T value, T min, M max);

		template<typename T>
		T tweening(T v0, T v1, std::size_t k0, std::size_t k1, std::size_t frame);

		template<typename T>
		double torad(T angle);

		double bounce_out(double t, double b , double c, double d);

		double bounce_in(double t,double b , double c, double d);

		double bounce_in_out(double t, double b, double c, double d);

		bool is_math(const std::string& str);

		bool is_math(char arg);

		double degrees_to_radians(double angle);

		double radians_to_degrees(double angle);

		g2d::math::point2dd normalize_point2d(double x, double y);

		double random_m11(unsigned int* seed);
	}
}

#include "math.inl"

#endif /* G2D_MATH_MATH_H_ */
