#ifndef G2D_RANDOM_RANDOM_H_
#define G2D_RANDOM_RANDOM_H_

#pragma once

#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <cmath>
#include <ctime>

#include "../math/range.h"

namespace g2d
{
	namespace random
	{

		typedef std::mt19937 randomer;

		void seed();

		int unique_number(int src[], std::size_t size, int min, int max);

		int number();

		int number(int min, int max);

		int number(int src[], std::size_t min, std::size_t max);

		void fill_unique_number(int src[], std::size_t size, int min, int max);

		int* fill_unique_number(std::size_t size, int min, int max);

		void fill_reference_number(int dst[], std::size_t dstsize, int org[], std::size_t orgsize);

		int random_range(int begin, int end);

		template<typename T>
		std::vector<T> cut(const std::vector<T>& vec);

		template<typename T>
		T random_range(const g2d::math::range<T> range);

		template<typename T>
		T random_int(const g2d::math::range<T> range);

		template<typename T>
		T random_int(T min, T max);
	}
}

#include "random.inl"

#endif /* G2D_RANDOM_RANDOM_H_ */
