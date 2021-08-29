template<typename T>
inline std::vector<T> g2d::random::cut(const std::vector<T>& vec)
{
	std::vector<T> first;
	std::vector<T> second;
	std::vector<T> out;

	for (std::size_t i = 0; i < vec.size(); i++)
	{
		if (i < vec.size() / 2)
		{
			first.push_back(vec[i]);
		}
		else
		{
			second.push_back(vec[i]);
		}
	}

	for (std::size_t i = 0; i < second.size(); i++)
	{
		out.push_back(second[i]);
	}

	for (std::size_t i = 0; i < first.size(); i++)
	{
		out.push_back(first[i]);
	}

	return out;
}

template<typename T>
inline T g2d::random::random_range(const g2d::math::range<T> range)
{
	return range.get_begin() + rand() * (range.get_end() - range.get_begin());
}

template<typename T>
inline T g2d::random::random_int(const g2d::math::range<T> range)
{
	return std::floor(range.get_begin() + rand() * (range.get_end() - range.get_begin() + 1));
}

template<typename T>
inline T g2d::random::random_int(T min, T max)
{
	return std::floor(min + rand() * (max - min + 1));
}
