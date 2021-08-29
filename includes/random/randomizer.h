#ifndef G2D_RANDOM_RANDOMIZER_H_
#define G2D_RANDOM_RANDOMIZER_H_

#pragma once

#include <iostream>
#include <string>
#include <random>
#include <cstddef>
#include <ctime>
#include <algorithm>

#include "../math/math.h"
#include "../math/range.h"

#include "random.h"

namespace g2d
{
	namespace random
	{
		class randomizer
		{
			public:

				randomizer();

				randomizer(const g2d::random::randomizer& copy);

				~randomizer();

				void seed();

				template <class RandomAccessIterator>
				void shuffle(RandomAccessIterator first, RandomAccessIterator last);

				template <typename T>
				T unique(const std::vector<T> vec, T begin, T end);

				template <typename T>
				T unique(T begin, T end);

			private:

				g2d::random::randomer _randomer;
		};
	}
}

#include "randomizer.inl"

#endif /* G2D_RANDOM_RANDOMIZER_H_ */
