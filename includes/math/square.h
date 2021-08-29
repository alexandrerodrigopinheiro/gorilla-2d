#ifndef G2D_MATH_SQUARE_H_
#define G2D_MATH_SQUARE_H_

#pragma once

#include <iostream>
#include <string>

#include "../basic/basic.h"

namespace g2d
{
	namespace math
	{
		template <typename T>
		class square
		{
			public:

				square();

				square(T square);

				square(T x, T y, T w, T h);

				~square();

				void set(const g2d::math::square<T>& copy);

				void set(T square);

				void set(T x, T y, T w, T h);

				void x(T x);

				void y(T y);

				void w(T w);

				void h(T h);

				T x() const;

				T y() const;

				T w() const;

				T h() const;

				g2d::math::square<T> null() const;

				bool annul() const;

				bool empty();

				void string_to(const std::string& x, const std::string& y, const std::string& w, const std::string& h);

				g2d::math::square<T> operator++();

				g2d::math::square<T> operator++(int);

				g2d::math::square<T> operator--();

				g2d::math::square<T> operator--(int);

				const g2d::math::square<T>& operator-();

				const g2d::math::square<T>& operator+();

				const g2d::math::square<T>& operator=(const g2d::math::square<T>& right);

				const g2d::math::square<T>& operator+(const g2d::math::square<T>& right);

				const g2d::math::square<T>& operator-(const g2d::math::square<T>& right);

				const g2d::math::square<T>& operator*(const g2d::math::square<T>& right);

				const g2d::math::square<T>& operator/(const g2d::math::square<T>& right);

				const g2d::math::square<T>& operator+=(const g2d::math::square<T>& right);

				const g2d::math::square<T>& operator-=(const g2d::math::square<T>& right);

				const g2d::math::square<T>& operator*=(const g2d::math::square<T>& right);

				const g2d::math::square<T>& operator/=(const g2d::math::square<T>& right);

				bool operator==(const g2d::math::square<T>& right);

				bool operator!=(const g2d::math::square<T>& right);

				bool operator>(const g2d::math::square<T>& right);

				bool operator<(const g2d::math::square<T>& right);

				bool operator>=(const g2d::math::square<T>& right);

				bool operator<=(const g2d::math::square<T>& right);

				const g2d::math::square<T>& operator=(T right);

				const g2d::math::square<T>& operator+(T right);

				const g2d::math::square<T>& operator-(T right);

				const g2d::math::square<T>& operator*(T right);

				const g2d::math::square<T>& operator/(T right);

				const g2d::math::square<T>& operator+=(T right);

				const g2d::math::square<T>& operator-=(T right);

				const g2d::math::square<T>& operator*=(T right);

				const g2d::math::square<T>& operator/=(T right);

				bool operator==(T right);

				bool operator!=(T right);

				bool operator>(T right);

				bool operator<(T right);

				bool operator>=(T right);

				bool operator<=(T right);

			private:

				square(T x, T y, T w, T h, bool null);

				T _x { 0 };
				T _y { 0 };
				T _w { 0 };
				T _h { 0 };
				bool _null { true };
		};


		template <typename T>
		std::ostream& operator<<(std::ostream& stream, const g2d::math::square<T>& right);

		template <typename T>
		std::istream& operator>>(std::istream& stream, g2d::math::square<T>& right);

		typedef g2d::math::square<int> squarei;
		typedef g2d::math::square<unsigned int> squareu;
		typedef g2d::math::square<float> squaref;
		typedef g2d::math::square<double> squared;
	}
}

#include "square.inl"

#endif /* G2D_MATH_SQUARE_H_ */
