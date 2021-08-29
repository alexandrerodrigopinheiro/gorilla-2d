#ifndef G2D_MATH_ROTATE_H_
#define G2D_MATH_ROTATE_H_

#pragma once

#include <iostream>
#include <string>

#include "../basic/basic.h"

namespace g2d
{
	namespace math
	{
		template <typename T>
		class rotate
		{
			public:

				rotate();

				rotate(T rotate);

				rotate(T h, T p, T b);

				~rotate();

				void set(const g2d::math::rotate<T>& copy);

				void set(T rotate);

				void set(T h, T p, T b);

				void h(T h);

				void p(T p);

				void b(T b);

				T h() const;

				T p() const;

				T b() const;

				g2d::math::rotate<T> null() const;

				bool annul() const;

				bool empty();

				void string_to(const std::string& h, const std::string& p, const std::string& b);

				g2d::math::rotate<T> operator++();

				g2d::math::rotate<T> operator++(int);

				g2d::math::rotate<T> operator--();

				g2d::math::rotate<T> operator--(int);

				const g2d::math::rotate<T>& operator-();

				const g2d::math::rotate<T>& operator+();

				const g2d::math::rotate<T>& operator=(const g2d::math::rotate<T>& right);

				const g2d::math::rotate<T>& operator+(const g2d::math::rotate<T>& right);

				const g2d::math::rotate<T>& operator-(const g2d::math::rotate<T>& right);

				const g2d::math::rotate<T>& operator*(const g2d::math::rotate<T>& right);

				const g2d::math::rotate<T>& operator/(const g2d::math::rotate<T>& right);

				const g2d::math::rotate<T>& operator+=(const g2d::math::rotate<T>& right);

				const g2d::math::rotate<T>& operator-=(const g2d::math::rotate<T>& right);

				const g2d::math::rotate<T>& operator*=(const g2d::math::rotate<T>& right);

				const g2d::math::rotate<T>& operator/=(const g2d::math::rotate<T>& right);

				bool operator==(const g2d::math::rotate<T>& right);

				bool operator!=(const g2d::math::rotate<T>& right);

				bool operator>(const g2d::math::rotate<T>& right);

				bool operator<(const g2d::math::rotate<T>& right);

				bool operator>=(const g2d::math::rotate<T>& right);

				bool operator<=(const g2d::math::rotate<T>& right);

				const g2d::math::rotate<T>& operator=(T right);

				const g2d::math::rotate<T>& operator+(T right);

				const g2d::math::rotate<T>& operator-(T right);

				const g2d::math::rotate<T>& operator*(T right);

				const g2d::math::rotate<T>& operator/(T right);

				const g2d::math::rotate<T>& operator+=(T right);

				const g2d::math::rotate<T>& operator-=(T right);

				const g2d::math::rotate<T>& operator*=(T right);

				const g2d::math::rotate<T>& operator/=(T right);

				bool operator==(T right);

				bool operator!=(T right);

				bool operator>(T right);

				bool operator<(T right);

				bool operator>=(T right);

				bool operator<=(T right);

			private:

				rotate(T h, T p, T b, bool null);

				T _h { static_cast<T>(0) };
				T _p { static_cast<T>(0) };
				T _b { static_cast<T>(0) };
				bool _null { true };
		};

		template <typename T>
		std::ostream& operator<<(std::ostream& stream, const g2d::math::rotate<T>& right);

		template <typename T>
		std::istream& operator>>(std::istream& stream, g2d::math::rotate<T>& right);

		typedef g2d::math::rotate<int> rotatei;
		typedef g2d::math::rotate<unsigned int> rotateu;
		typedef g2d::math::rotate<float> rotatef;
		typedef g2d::math::rotate<double> rotated;
	}
}

#include "rotate.inl"

#endif /* G2D_MATH_ROTATE_H_ */
