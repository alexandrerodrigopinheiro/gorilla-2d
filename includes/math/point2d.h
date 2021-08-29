#ifndef G2D_MATH_POINT2D_H_
#define G2D_MATH_POINT2D_H_

#pragma once

#include <iostream>
#include <string>
#include <cmath>

#include "../basic/basic.h"

namespace g2d
{
	namespace math
	{
		template <typename T>
		class point2d
		{
			public:

				point2d();

				point2d(T point);

				point2d(T x, T y);

				~point2d();

				void set(const g2d::math::point2d<T>& copy);

				void set(T point);

				void set(T x, T y);

				void x(T x);

				void y(T y);

				T x() const;

				T y() const;

				g2d::math::point2d<T> null() const;

				bool annul() const;

				bool empty() const;

				double normalize() const;

			    double angle() const;

				void string_to(const std::string& x, const std::string& y);

				g2d::math::point2d<T> operator++();

				g2d::math::point2d<T> operator++(int);

				g2d::math::point2d<T> operator--();

				g2d::math::point2d<T> operator--(int);

				const g2d::math::point2d<T>& operator-();

				const g2d::math::point2d<T>& operator+();

				const g2d::math::point2d<T>& operator=(const g2d::math::point2d<T>& right);

				const g2d::math::point2d<T>& operator+(const g2d::math::point2d<T>& right);

				const g2d::math::point2d<T>& operator-(const g2d::math::point2d<T>& right);

				const g2d::math::point2d<T>& operator*(const g2d::math::point2d<T>& right);

				const g2d::math::point2d<T>& operator/(const g2d::math::point2d<T>& right);

				const g2d::math::point2d<T>& operator+=(const g2d::math::point2d<T>& right);

				const g2d::math::point2d<T>& operator-=(const g2d::math::point2d<T>& right);

				const g2d::math::point2d<T>& operator*=(const g2d::math::point2d<T>& right);

				const g2d::math::point2d<T>& operator/=(const g2d::math::point2d<T>& right);

				bool operator==(const g2d::math::point2d<T>& right);

				bool operator!=(const g2d::math::point2d<T>& right);

				bool operator>(const g2d::math::point2d<T>& right);

				bool operator<(const g2d::math::point2d<T>& right);

				bool operator>=(const g2d::math::point2d<T>& right);

				bool operator<=(const g2d::math::point2d<T>& right);

				const g2d::math::point2d<T>& operator=(T right);

				const g2d::math::point2d<T>& operator+(T right);

				const g2d::math::point2d<T>& operator-(T right);

				const g2d::math::point2d<T>& operator*(T right);

				const g2d::math::point2d<T>& operator/(T right);

				const g2d::math::point2d<T>& operator+=(T right);

				const g2d::math::point2d<T>& operator-=(T right);

				const g2d::math::point2d<T>& operator*=(T right);

				const g2d::math::point2d<T>& operator/=(T right);

				bool operator==(T right);

				bool operator!=(T right);

				bool operator>(T right);

				bool operator<(T right);

				bool operator>=(T right);

				bool operator<=(T right);

			private:

				point2d(T x, T y, bool null);

				T _x { static_cast<T>(0) };
				T _y { static_cast<T>(0) };
				bool _null { true };
		};

		template <typename T>
		std::ostream& operator<<(std::ostream& stream, const g2d::math::point2d<T>& right);

		template <typename T>
		std::istream& operator>>(std::istream& stream, g2d::math::point2d<T>& right);

		typedef g2d::math::point2d<int> point2di;
		typedef g2d::math::point2d<unsigned int> point2du;
		typedef g2d::math::point2d<float> point2df;
		typedef g2d::math::point2d<double> point2dd;
	}
}

#include "point2d.inl"

#endif /* G2D_MATH_POINT2D_H_ */
