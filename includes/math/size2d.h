#ifndef G2D_MATH_SIZE2D_H_
#define G2D_MATH_SIZE2D_H_

#pragma once

#include <iostream>
#include <string>

#include "../basic/basic.h"

namespace g2d
{
	namespace math
	{
		template <typename T>
		class size2d
		{
			public:

				size2d();

				size2d(T size);

				size2d(T w, T h);

				~size2d();

				void set(const g2d::math::size2d<T>& copy);

				void set(T size);

				void set(T w, T h);

				void w(T w);

				void h(T h);

				T w() const;

				T h() const;

				g2d::math::size2d<T> null() const;

				bool annul() const;

				bool empty();

				void string_to(const std::string& w, const std::string& h);

				g2d::math::size2d<T> operator++();

				g2d::math::size2d<T> operator++(int);

				g2d::math::size2d<T> operator--();

				g2d::math::size2d<T> operator--(int);

				g2d::math::size2d<T> operator-();

				g2d::math::size2d<T> operator+();

				const g2d::math::size2d<T>& operator=(const g2d::math::size2d<T>& right);

				const g2d::math::size2d<T>& operator+(const g2d::math::size2d<T>& right);

				const g2d::math::size2d<T>& operator-(const g2d::math::size2d<T>& right);

				const g2d::math::size2d<T>& operator*(const g2d::math::size2d<T>& right);

				const g2d::math::size2d<T>& operator/(const g2d::math::size2d<T>& right);

				const g2d::math::size2d<T>& operator+=(const g2d::math::size2d<T>& right);

				const g2d::math::size2d<T>& operator-=(const g2d::math::size2d<T>& right);

				const g2d::math::size2d<T>& operator*=(const g2d::math::size2d<T>& right);

				const g2d::math::size2d<T>& operator/=(const g2d::math::size2d<T>& right);

				bool operator==(const g2d::math::size2d<T>& right);

				bool operator!=(const g2d::math::size2d<T>& right);

				bool operator>(const g2d::math::size2d<T>& right);

				bool operator<(const g2d::math::size2d<T>& right);

				bool operator>=(const g2d::math::size2d<T>& right);

				bool operator<=(const g2d::math::size2d<T>& right);

				const g2d::math::size2d<T>& operator=(T right);

				const g2d::math::size2d<T>& operator+(T right);

				const g2d::math::size2d<T>& operator-(T right);

				const g2d::math::size2d<T>& operator*(T right);

				const g2d::math::size2d<T>& operator/(T right);

				const g2d::math::size2d<T>& operator+=(T right);

				const g2d::math::size2d<T>& operator-=(T right);

				const g2d::math::size2d<T>& operator*=(T right);

				const g2d::math::size2d<T>& operator/=(T right);

				bool operator==(T right);

				bool operator!=(T right);

				bool operator>(T right);

				bool operator<(T right);

				bool operator>=(T right);

				bool operator<=(T right);

			private:

				size2d(T w, T h, bool null);

				T _w { static_cast<T>(0) };
				T _h { static_cast<T>(0) };
				bool _null { true };
		};

		template <typename T>
		std::ostream& operator<<(std::ostream& stream, const g2d::math::size2d<T>& right);

		template <typename T>
		std::istream& operator>>(std::istream& stream, g2d::math::size2d<T>& right);

		typedef g2d::math::size2d<int> size2di;
		typedef g2d::math::size2d<unsigned int> size2du;
		typedef g2d::math::size2d<float> size2df;
		typedef g2d::math::size2d<double> size2dd;
	}
}

#include "size2d.inl"

#endif /* G2D_MATH_SIZE2D_H_ */
