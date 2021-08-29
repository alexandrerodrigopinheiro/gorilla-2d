#ifndef G2D_MATH_UVMAP_H_
#define G2D_MATH_UVMAP_H_

#pragma once

#include <iostream>
#include <string>

#include "../basic/basic.h"

namespace g2d
{
	namespace math
	{
		template <typename T>
		class uvmap
		{
			public:

				uvmap();

				uvmap(T uvmap);

				uvmap(T u, T v);

				~uvmap();

				void set(const g2d::math::uvmap<T>& copy);

				void set(T uvmap);

				void set(T u, T v);

				void u(T u);

				void v(T v);

				T u() const;

				T v() const;

				g2d::math::uvmap<T> null() const;

				bool annul() const;

				bool empty();

				void string_to(const std::string& u, const std::string& v);

				g2d::math::uvmap<T> operator++();

				g2d::math::uvmap<T> operator++(int);

				g2d::math::uvmap<T> operator--();

				g2d::math::uvmap<T> operator--(int);

				const g2d::math::uvmap<T>& operator-();

				const g2d::math::uvmap<T>& operator+();

				const g2d::math::uvmap<T>& operator=(const g2d::math::uvmap<T>& right);

				const g2d::math::uvmap<T>& operator+(const g2d::math::uvmap<T>& right);

				const g2d::math::uvmap<T>& operator-(const g2d::math::uvmap<T>& right);

				const g2d::math::uvmap<T>& operator*(const g2d::math::uvmap<T>& right);

				const g2d::math::uvmap<T>& operator/(const g2d::math::uvmap<T>& right);

				const g2d::math::uvmap<T>& operator+=(const g2d::math::uvmap<T>& right);

				const g2d::math::uvmap<T>& operator-=(const g2d::math::uvmap<T>& right);

				const g2d::math::uvmap<T>& operator*=(const g2d::math::uvmap<T>& right);

				const g2d::math::uvmap<T>& operator/=(const g2d::math::uvmap<T>& right);

				bool operator==(const g2d::math::uvmap<T>& right);

				bool operator!=(const g2d::math::uvmap<T>& right);

				bool operator>(const g2d::math::uvmap<T>& right);

				bool operator<(const g2d::math::uvmap<T>& right);

				bool operator>=(const g2d::math::uvmap<T>& right);

				bool operator<=(const g2d::math::uvmap<T>& right);

				const g2d::math::uvmap<T>& operator=(T right);

				const g2d::math::uvmap<T>& operator+(T right);

				const g2d::math::uvmap<T>& operator-(T right);

				const g2d::math::uvmap<T>& operator*(T right);

				const g2d::math::uvmap<T>& operator/(T right);

				const g2d::math::uvmap<T>& operator+=(T right);

				const g2d::math::uvmap<T>& operator-=(T right);

				const g2d::math::uvmap<T>& operator*=(T right);

				const g2d::math::uvmap<T>& operator/=(T right);

				bool operator==(T right);

				bool operator!=(T right);

				bool operator>(T right);

				bool operator<(T right);

				bool operator>=(T right);

				bool operator<=(T right);

			private:

				uvmap(T u, T v, bool null);

				T _u { static_cast<T>(0) };
				T _v { static_cast<T>(0) };
				bool _null { true };
		};

		template <typename T>
		std::ostream& operator<<(std::ostream& stream, const g2d::math::uvmap<T>& right);

		template <typename T>
		std::istream& operator>>(std::istream& stream, g2d::math::uvmap<T>& right);

		typedef g2d::math::uvmap<int> uvmapi;
		typedef g2d::math::uvmap<unsigned int> uvmapu;
		typedef g2d::math::uvmap<float> uvmapf;
		typedef g2d::math::uvmap<double> uvmapd;
	}
}

#include "uvmap.inl"

#endif /* G2D_MATH_UVMAP_H_ */
