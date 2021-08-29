#ifndef G2D_MATH_VERTEX_H_
#define G2D_MATH_VERTEX_H_

#pragma once

#include <string>
#include <iostream>

#include "../basic/basic.h"

#include "point3d.h"

namespace g2d
{
	namespace math
	{
		template<class T>
		class vertex
		{
			public:

				vertex();

				vertex(T point);

				vertex(T x, T y, T z);

				vertex(const g2d::math::point3d<T>& a, const g2d::math::point3d<T>& b, const g2d::math::point3d<T>& c, const g2d::math::point3d<T>& d);

				~vertex();

				void set(const g2d::math::vertex<T>& vertex);

				void set(T point);

				void set(T x, T y, T z);

				void set(const g2d::math::point3d<T>& a, const g2d::math::point3d<T>& b, const g2d::math::point3d<T>& c, const g2d::math::point3d<T>& d);

				void a(const g2d::math::point3d<T>& point);

				void b(const g2d::math::point3d<T>& point);

				void c(const g2d::math::point3d<T>& point);

				void d(const g2d::math::point3d<T>& point);

				void a(T x, T y, T z);

				void b(T x, T y, T z);

				void c(T x, T y, T z);

				void d(T x, T y, T z);

				const g2d::math::point3d<T>& a() const;

				const g2d::math::point3d<T>& b() const;

				const g2d::math::point3d<T>& c() const;

				const g2d::math::point3d<T>& d() const;

				g2d::math::vertex<T> null() const;

				bool annul() const;

				bool empty() const;

				void string_to(const std::string& a, const std::string& b, const std::string& c, const std::string& d);

				g2d::math::vertex<T> operator++();

				g2d::math::vertex<T> operator++(int);

				g2d::math::vertex<T> operator--();

				g2d::math::vertex<T> operator--(int);

				const g2d::math::vertex<T>& operator-();

				const g2d::math::vertex<T>& operator+();

				const g2d::math::vertex<T>& operator=(const g2d::math::vertex<T>& right);

				const g2d::math::vertex<T>& operator+(const g2d::math::vertex<T>& right);

				const g2d::math::vertex<T>& operator-(const g2d::math::vertex<T>& right);

				const g2d::math::vertex<T>& operator*(const g2d::math::vertex<T>& right);

				const g2d::math::vertex<T>& operator/(const g2d::math::vertex<T>& right);

				const g2d::math::vertex<T>& operator+=(const g2d::math::vertex<T>& right);

				const g2d::math::vertex<T>& operator-=(const g2d::math::vertex<T>& right);

				const g2d::math::vertex<T>& operator*=(const g2d::math::vertex<T>& right);

				const g2d::math::vertex<T>& operator/=(const g2d::math::vertex<T>& right);

				bool operator==(const g2d::math::vertex<T>& right);

				bool operator!=(const g2d::math::vertex<T>& right);

				bool operator>(const g2d::math::vertex<T>& right);

				bool operator<(const g2d::math::vertex<T>& right);

				bool operator>=(const g2d::math::vertex<T>& right);

				bool operator<=(const g2d::math::vertex<T>& right);

				const g2d::math::vertex<T>& operator=(T right);

				const g2d::math::vertex<T>& operator+(T right);

				const g2d::math::vertex<T>& operator-(T right);

				const g2d::math::vertex<T>& operator*(T right);

				const g2d::math::vertex<T>& operator/(T right);

				const g2d::math::vertex<T>& operator+=(T right);

				const g2d::math::vertex<T>& operator-=(T right);

				const g2d::math::vertex<T>& operator*=(T right);

				const g2d::math::vertex<T>& operator/=(T right);

				bool operator==(T right);

				bool operator!=(T right);

				bool operator>(T right);

				bool operator<(T right);

				bool operator>=(T right);

				bool operator<=(T right);

			private:

				vertex(T a, T b, T c, T d, bool null);

				g2d::math::point3d<T>	_a { g2d::math::point3d<T>() };
				g2d::math::point3d<T>	_b { g2d::math::point3d<T>() };
				g2d::math::point3d<T>	_c { g2d::math::point3d<T>() };
				g2d::math::point3d<T>	_d { g2d::math::point3d<T>()};
				bool _null { false };
		};

		template <typename T>
		std::ostream& operator<<(std::ostream& stream, const g2d::math::vertex<T>& right);

		template <typename T>
		std::istream& operator>>(std::istream& stream, g2d::math::vertex<T>& right);

		typedef g2d::math::vertex<int> vertexi;
		typedef g2d::math::vertex<unsigned int> vertexu;
		typedef g2d::math::vertex<float> vertexf;
		typedef g2d::math::vertex<double> vertexd;
	}
}

#include "vertex.inl"

#endif /* G2D_MATH_VERTEX_H_ */
