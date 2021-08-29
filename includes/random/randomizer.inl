template <class RandomAccessIterator>
inline void g2d::random::randomizer::shuffle(RandomAccessIterator first, RandomAccessIterator last)
{
	auto dist = [this](const ptrdiff_t n)
	{
		return std::uniform_int_distribution<ptrdiff_t>(0, n - 1)(this->_randomer);
	};

	std::random_shuffle(first, last, dist);
}

template <typename T>
inline T g2d::random::randomizer::unique(const std::vector<T> vec, T begin, T end)
{
	return vec[this->unique(begin, end)];
}

template <typename T>
inline T g2d::random::randomizer::unique(T begin, T end)
{
	return static_cast<T>((std::rand() % (end - begin)) + begin);
}
