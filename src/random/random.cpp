#include "../../includes/random/random.h"

void g2d::random::seed()
{
	std::srand((unsigned long long int)time(NULL));
}

int g2d::random::unique_number(int src[], std::size_t size, int min, int max)
{
	int arg = std::rand() % max + min;

	for (std::size_t i = 0; i < size; i++)
	{
		if (src[i] == arg)
		{
			i = 0;
			arg = std::rand() % max + min;
		}
	}

	return arg;
}

int g2d::random::number()
{
	return std::rand();
}

int g2d::random::number(int min, int max)
{
	return std::rand() % max + min;
}

int g2d::random::number(int src[], std::size_t min, std::size_t max)
{
	return src[(rand() % (max - min)) + min];
}

void g2d::random::fill_unique_number(int src[], std::size_t size, int min, int max)
{
	for (std::size_t i = 0; i < size; i++)
	{
		src[i] = g2d::random::unique_number(src, size, min, max);
	}
}

int* g2d::random::fill_unique_number(std::size_t size, int min, int max)
{
	int* vec = new int[size];

	for (std::size_t i = 0; i < size; i++)
	{
		vec[i] = g2d::random::unique_number(vec, size, min, max);
	}

	return vec;
}

void g2d::random::fill_reference_number(int dst[], std::size_t dstsize, int org[], std::size_t orgsize)
{
	int* vec = new int[dstsize];

	g2d::random::fill_unique_number(vec, dstsize, 0, orgsize - 1);

	for (std::size_t i = 0; i < dstsize; i++)
	{
		dst[i] = org[vec[i]];
	}
}

int g2d::random::random_range(int begin, int end)
{
	return begin + std::rand() * (end - begin);
}
