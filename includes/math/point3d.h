#ifndef G2D_MATH_POINT3D_H_
#define G2D_MATH_POINT3D_H_

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
		class point3d
		{
			public:

				point3d();

				point3d(T point);

				point3d(T x, T y, T z);

				~point3d();

				void set(const g2d::math::point3d<T>& copy);

				void set(T point);

				void set(T x, T y, T z);

				void x(T x);

				void y(T y);

				void z(T z);

				T x() const;

				T y() const;

				T z() const;

				g2d::math::point3d<T> null() const;

				bool annul() const;

				bool empty() const;

			    double normalize() const;

			    double angle() const;

				void string_to(const std::string& x, const std::string& y, const std::string& z);

				g2d::math::point3d<T> operator++();

				g2d::math::point3d<T> operator++(int);

				g2d::math::point3d<T> operator--();

				g2d::math::point3d<T> operator--(int);

				const g2d::math::point3d<T>& operator-();

				const g2d::math::point3d<T>& operator+();

				const g2d::math::point3d<T>& operator=(const g2d::math::point3d<T>& right);

				const g2d::math::point3d<T>& operator+(const g2d::math::point3d<T>& right);

				const g2d::math::point3d<T>& operator-(const g2d::math::point3d<T>& right);

				const g2d::math::point3d<T>& operator*(const g2d::math::point3d<T>& right);

				const g2d::math::point3d<T>& operator/(const g2d::math::point3d<T>& right);

				const g2d::math::point3d<T>& operator+=(const g2d::math::point3d<T>& right);

				const g2d::math::point3d<T>& operator-=(const g2d::math::point3d<T>& right);

				const g2d::math::point3d<T>& operator*=(const g2d::math::point3d<T>& right);

				const g2d::math::point3d<T>& operator/=(const g2d::math::point3d<T>& right);

				bool operator==(const g2d::math::point3d<T>& right);

				bool operator!=(const g2d::math::point3d<T>& right);

				bool operator>(const g2d::math::point3d<T>& right);

				bool operator<(const g2d::math::point3d<T>& right);

				bool operator>=(const g2d::math::point3d<T>& right);

				bool operator<=(const g2d::math::point3d<T>& right);

				const g2d::math::point3d<T>& operator=(T right);

				const g2d::math::point3d<T>& operator+(T right);

				const g2d::math::point3d<T>& operator-(T right);

				const g2d::math::point3d<T>& operator*(T right);

				const g2d::math::point3d<T>& operator/(T right);

				const g2d::math::point3d<T>& operator+=(T right);

				const g2d::math::point3d<T>& operator-=(T right);

				const g2d::math::point3d<T>& operator*=(T right);

				const g2d::math::point3d<T>& operator/=(T right);

				bool operator==(T right);

				bool operator!=(T right);

				bool operator>(T right);

				bool operator<(T right);

				bool operator>=(T right);

				bool operator<=(T right);

			private:

				point3d(T x, T y, T z, bool null);

				T _x { static_cast<T>(0) };
				T _y { static_cast<T>(0) };
				T _z { static_cast<T>(0) };
				bool _null { true };
		};

		template <typename T>
		std::ostream& operator<<(std::ostream& stream, const g2d::math::point3d<T>& right);

		template <typename T>
		std::istream& operator>>(std::istream& stream, g2d::math::point3d<T>& right);

		typedef g2d::math::point3d<int> point3di;
		typedef g2d::math::point3d<unsigned int> point3du;
		typedef g2d::math::point3d<float> point3df;
		typedef g2d::math::point3d<double> point3dd;
	}
}

#include "point3d.inl"

#endif /* G2D_MATH_POINT3D_H_ */
