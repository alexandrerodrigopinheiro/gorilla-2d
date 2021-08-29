template<class... T>
inline void g2d::basic::unused(T&&...)
{
}

template<typename T, typename M>
inline T g2d::basic::to(M src)
{
	std::stringstream tmp;
	tmp << src;
	std::istringstream iss(tmp.str());
	T out;
	iss >> out;

	return out;
}

template<typename T>
std::vector<T> g2d::basic::explode(const std::string& src, const char delimeter)
{
    size_t start;
    size_t end = 0;
    std::vector<T> res;

    while ((start = src.find_first_not_of(delimeter, end)) != std::string::npos)
    {
        end = src.find(delimeter, start);
        res.push_back(g2d::basic::to<T>(src.substr(start, end - start)));
    }

	return res;
}

template<typename T>
std::vector<T> g2d::basic::slice(const std::vector<T>& org, std::size_t begin, std::size_t end)
{
	if (begin == end)
	{
		return std::vector<T>();
	}

    std::vector<T> vec;

	for (std::size_t i = begin; i < end; i++)
	{
		vec.push_back(org[i]);
	}

    return vec;
}

template <typename T, typename N>
inline std::vector<T> g2d::basic::slice(const std::vector<N>& org, std::size_t begin, std::size_t end)
{
	if (begin == end)
	{
		return std::vector<T>();
	}

    std::vector<T> vec;

	for (std::size_t i = begin; i < end; i++)
	{
		vec.push_back(g2d::basic::to<T>(org[i]));
	}

    return vec;
}
template<typename T>
inline void g2d::basic::swap(const std::vector<T>& org, std::vector<T>& dst, std::size_t begin)
{
	assert(org.size() <= dst.size());
	assert(static_cast<std::size_t>(begin + org.size()) <= dst.size());

	for (std::size_t i = 0; i < org.size(); i++)
	{
		dst[begin + i] = org[i];
	}
}

template<typename T>
inline bool g2d::basic::repeated(const std::vector<T>& org, T element)
{
	for (std::size_t i = 0; i < org.size(); i++)
	{
		if (org[i] == element)
		{
			return true;
		}
	}

	return false;
}

template<typename T, typename N>
inline bool g2d::basic::repeated(const std::vector<T>& org, N element)
{
	for (std::size_t i = 0; i < org.size(); i++)
	{
		if (org[i] == g2d::basic::to<T>(element))
		{
			return true;
		}
	}

	return false;
}

template<typename T>
inline bool g2d::basic::repeated(const std::vector<T>& org)
{
	for (std::size_t i = 0; i < org.size(); i++)
	{
		for (std::size_t j = i + 1; j < org.size(); j++)
		{
			if (org[i] == org[j])
			{
				return true;
			}
		}
	}

	return false;
}

template<typename T, std::size_t N>
inline constexpr std::size_t g2d::basic::array_size(T (&)[N])
{
	return N;
}

template<typename T, std::size_t N>
inline T* g2d::basic::array_begin(T (&array)[N])
{
	return &array[0];
}

template<typename T, std::size_t N>
inline T* g2d::basic::array_end(T (&array)[N])
{
	return &array[N];
}

template<typename T>
inline std::string g2d::basic::to_monetary(T org)
{
	std::string src = g2d::basic::to<std::string>(org);
	std::string job;
	std::string res;

	if (src.length() == 0)
	{
		return "0,00";
	}
	else if (src.length() == 1)
	{
		return "0,0" + src;
	}
	else if (src.length() == 2)
	{
		return "0," + src;
	}

	job.assign(src.begin(), src.end() - 2);
	std::reverse(job.begin(), job.end());

	for (std::size_t i = 0; i < job.length(); i++)
	{
		res += job[i];

		if ((i + 1) % 3 == 0 && i < job.length() - 1)
		{
			res += ".";
		}
	}

	std::reverse(res.begin(), res.end());
	job.assign(src.end() - 2, src.end());

	return (res + "," + job);
}
