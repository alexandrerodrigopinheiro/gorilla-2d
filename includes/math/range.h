#ifndef G2D_MATH_RANGE_H_
#define G2D_MATH_RANGE_H_

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
		class range
		{
			public:

				range();

				range(T range);

				range(T begin, T end);

				~range();

				void set(const g2d::math::range<T>& copy);

				void set(T range);

				void set(T begin, T end);

				void begin(T begin);

				void end(T end);

				T begin() const;

				T end() const;

				g2d::math::range<T> null() const;

				bool annul() const;

				bool empty();

				bool intersection(const g2d::math::range<T>& begin, const g2d::math::range<T>& end);

				T interval();

				void clear();

				void string_to(const std::string& begin, const std::string& end);

				g2d::math::range<T> operator++();

				g2d::math::range<T> operator++(int);

				g2d::math::range<T> operator--();

				g2d::math::range<T> operator--(int);

				const g2d::math::range<T>& operator-();

				const g2d::math::range<T>& operator+();

				const g2d::math::range<T>& operator=(const g2d::math::range<T>& right);

				const g2d::math::range<T>& operator+(const g2d::math::range<T>& right);

				const g2d::math::range<T>& operator-(const g2d::math::range<T>& right);

				const g2d::math::range<T>& operator*(const g2d::math::range<T>& right);

				const g2d::math::range<T>& operator/(const g2d::math::range<T>& right);

				const g2d::math::range<T>& operator+=(const g2d::math::range<T>& right);

				const g2d::math::range<T>& operator-=(const g2d::math::range<T>& right);

				const g2d::math::range<T>& operator*=(const g2d::math::range<T>& right);

				const g2d::math::range<T>& operator/=(const g2d::math::range<T>& right);

				bool operator==(const g2d::math::range<T>& right);

				bool operator!=(const g2d::math::range<T>& right);

				bool operator>(const g2d::math::range<T>& right);

				bool operator<(const g2d::math::range<T>& right);

				bool operator>=(const g2d::math::range<T>& right);

				bool operator<=(const g2d::math::range<T>& right);

				const g2d::math::range<T>& operator=(T right);

				const g2d::math::range<T>& operator+(T right);

				const g2d::math::range<T>& operator-(T right);

				const g2d::math::range<T>& operator*(T right);

				const g2d::math::range<T>& operator/(T right);

				const g2d::math::range<T>& operator+=(T right);

				const g2d::math::range<T>& operator-=(T right);

				const g2d::math::range<T>& operator*=(T right);

				const g2d::math::range<T>& operator/=(T right);

				bool operator==(T right);

				bool operator!=(T right);

				bool operator>(T right);

				bool operator<(T right);

				bool operator>=(T right);

				bool operator<=(T right);

			private:

				range(T begin, T end, bool null);

				T _begin { static_cast<T>(0) };
				T _end { static_cast<T>(0) };
				bool _null { true };
		};

		template <typename T>
		std::ostream& operator<<(std::ostream& stream, const g2d::math::range<T>& right);

		template <typename T>
		std::istream& operator>>(std::istream& stream, g2d::math::range<T>& right);

		typedef g2d::math::range<int> rangei;
		typedef g2d::math::range<unsigned int> rangeu;
		typedef g2d::math::range<float> rangef;
		typedef g2d::math::range<double> ranged;
	}
}

#include "range.inl"

#endif /* G2D_MATH_RANGE_H_ */
