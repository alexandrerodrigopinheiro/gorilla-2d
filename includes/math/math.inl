template<typename T>
inline T g2d::math::invert(T src)
{
	return -(src);
}

template<typename T>
inline T g2d::math::rule_of_three(T val, T left, T right)
{
	return (static_cast<T>(val) * static_cast<T>(right)) / static_cast<T>(left);
}

template<typename T, typename M>
inline T g2d::math::rule_of_three(T val, M left, M right)
{
	return (static_cast<T>(val) * static_cast<T>(right)) / static_cast<T>(left);
}

template<typename T, typename M>
inline T g2d::math::rule_of_three(T val, M left, T right)
{
	return (static_cast<T>(val) * static_cast<T>(right)) / static_cast<T>(left);
}

template<typename T, typename M>
inline T g2d::math::rule_of_three(T val, T left, M right)
{
	return (static_cast<T>(val) * static_cast<T>(right)) / static_cast<T>(left);
}

template<typename T>
inline T g2d::math::normal(T value, T min, T max)
{
	return (g2d::math::clamp(static_cast<T>(value), static_cast<T>(min), static_cast<T>(max)) / static_cast<T>(max));
}

template<typename T, typename M>
inline T g2d::math::normal(T value, M min, M max)
{
	return (g2d::math::clamp(static_cast<T>(value), static_cast<T>(min), static_cast<T>(max)) / static_cast<T>(max));
}

template<typename T, typename M>
inline T g2d::math::normal(T value, M min, T max)
{
	return (g2d::math::clamp(static_cast<T>(value), static_cast<T>(min), static_cast<T>(max)) / static_cast<T>(max));
}

template<typename T, typename M>
inline T g2d::math::normal(T value, T min, M max)
{
	return (g2d::math::clamp(static_cast<T>(value), static_cast<T>(min), static_cast<T>(max)) / static_cast<T>(max));
}

template<typename T>
inline T g2d::math::clamp(T value, T min, T max)
{
	return std::max(static_cast<T>(min), std::min(static_cast<T>(max), value));
}

template<typename T, typename M>
inline T g2d::math::clamp(T value, M min, M max)
{
	return std::max(static_cast<T>(min), std::min(static_cast<T>(max), value));
}

template<typename T, typename M>
inline T g2d::math::clamp(T value, M min, T max)
{
	return std::max(static_cast<T>(min), std::min(static_cast<T>(max), value));
}

template<typename T, typename M>
inline T g2d::math::clamp(T value, T min, M max)
{
	return std::max(static_cast<T>(min), std::min(static_cast<T>(max), value));
}

template<typename T>
inline T g2d::math::wrap(T value, T min, T max)
{
	return static_cast<T>(value) < static_cast<T>(min) ? static_cast<T>(max) : static_cast<T>(value) > static_cast<T>(max) ? static_cast<T>(min) : static_cast<T>(value);
}

template<typename T, typename M>
inline T g2d::math::wrap(T value, M min, M max)
{
	return static_cast<T>(value) < static_cast<T>(min) ? static_cast<T>(max) : static_cast<T>(value) > static_cast<T>(max) ? static_cast<T>(min) : static_cast<T>(value);
}

template<typename T, typename M>
inline T g2d::math::wrap(T value, M min, T max)
{
	return static_cast<T>(value) < static_cast<T>(min) ? static_cast<T>(max) : static_cast<T>(value) > static_cast<T>(max) ? static_cast<T>(min) : static_cast<T>(value);
}

template<typename T, typename M>
inline T g2d::math::wrap(T value, T min, M max)
{
	return static_cast<T>(value) < static_cast<T>(min) ? static_cast<T>(max) : static_cast<T>(value) > static_cast<T>(max) ? static_cast<T>(min) : static_cast<T>(value);
}

template<typename T>
inline T loop(T value, T min, T max)
{
	return static_cast<T>(value) % ((static_cast<T>(max) - static_cast<T>(min)) + static_cast<T>(1));
}

template<typename T, typename M>
inline T loop(T value, M min, M max)
{
	if (static_cast<T>(value) < static_cast<T>(min))
	{
		return static_cast<T>(max) - (static_cast<T>(value) % ((static_cast<T>(max) - static_cast<T>(min)) + static_cast<T>(1)));
	}
	else if (static_cast<T>(value) > static_cast<T>(max))
	{
		return static_cast<T>(min) + (static_cast<T>(value) % ((static_cast<T>(max) - static_cast<T>(min)) + static_cast<T>(1)));
	}
	return value;
}

template<typename T, typename M>
inline T loop(T value, M min, T max)
{
	if (static_cast<T>(value) < static_cast<T>(min))
	{
		return static_cast<T>(max) - (static_cast<T>(value) % ((static_cast<T>(max) - static_cast<T>(min)) + static_cast<T>(1)));
	}
	else if (static_cast<T>(value) > static_cast<T>(max))
	{
		return static_cast<T>(min) + (static_cast<T>(value) % ((static_cast<T>(max) - static_cast<T>(min)) + static_cast<T>(1)));
	}
	return value;
}

template<typename T, typename M>
inline T loop(T value, T min, M max)
{
	if (static_cast<T>(value) < static_cast<T>(min))
	{
		return static_cast<T>(max) - (static_cast<T>(value) % ((static_cast<T>(max) - static_cast<T>(min)) + static_cast<T>(1)));
	}
	else if (static_cast<T>(value) > static_cast<T>(max))
	{
		return static_cast<T>(min) + (static_cast<T>(value) % ((static_cast<T>(max) - static_cast<T>(min)) + static_cast<T>(1)));
	}
	return value;
}

template<typename T>
inline T g2d::math::normalize(T value, T min, T max)
{
	if (static_cast<T>(value) < static_cast<T>(min))
	{
		return static_cast<T>(max) - (static_cast<T>(value) % ((static_cast<T>(max) - static_cast<T>(min)) + static_cast<T>(1)));
	}
	else if (static_cast<T>(value) > static_cast<T>(max))
	{
		return static_cast<T>(min) + (static_cast<T>(value) % ((static_cast<T>(max) - static_cast<T>(min)) + static_cast<T>(1)));
	}
	return value;
}

template<typename T, typename M>
inline T g2d::math::normalize(T value, M min, M max)
{
	return (static_cast<T>(value) - static_cast<T>(min)) / (static_cast<T>(max) - static_cast<T>(min));
}

template<typename T, typename M>
inline T g2d::math::normalize(T value, M min, T max)
{
	return (static_cast<T>(value) - static_cast<T>(min)) / (static_cast<T>(max) - static_cast<T>(min));
}

template<typename T, typename M>
inline T g2d::math::normalize(T value, T min, M max)
{
	return (static_cast<T>(value) - static_cast<T>(min)) / (static_cast<T>(max) - static_cast<T>(min));
}

template<typename T>
inline T g2d::math::denormalize(T value, T min, T max)
{
	return (static_cast<T>(value ) * (static_cast<T>(max) - static_cast<T>(min)) + static_cast<T>(min));
}

template<typename T, typename M>
inline T g2d::math::denormalize(T value, M min, M max)
{
	return (static_cast<T>(value ) * (static_cast<T>(max) - static_cast<T>(min)) + static_cast<T>(min));
}

template<typename T, typename M>
inline T g2d::math::denormalize(T value, M min, T max)
{
	return (static_cast<T>(value ) * (static_cast<T>(max) - static_cast<T>(min)) + static_cast<T>(min));
}

template<typename T, typename M>
inline T g2d::math::denormalize(T value, T min, M max)
{
	return (static_cast<T>(value ) * (static_cast<T>(max) - static_cast<T>(min)) + static_cast<T>(min));
}

template<typename T>
inline T g2d::math::tweening(T v0, T v1, std::size_t k0, std::size_t k1, std::size_t frame)
{
	if (k1 < k0)
	{
		throw std::invalid_argument("Tween keyframe lower of range, failed, failed");

		exit(EXIT_FAILURE);
	}

	if (frame < k0 || frame > k1)
	{
		throw std::invalid_argument("Tween frame out of keyframe range, failed");

		exit(EXIT_FAILURE);
	}

	if (frame == k0)
	{
		return v0;
	}

	if (frame == k1)
	{
		return v1;
	}

	T f_frame = static_cast<T>(frame);
	T f_size = f_frame - k0;
	T f_sections = (k1 - k0);
	T f_displacement = (v1 - v0) / f_sections;

	return v0 + (f_displacement * f_size);
}

template<typename T>
inline double g2d::math::torad(T angle)
{
    return (static_cast<double>(angle) * 3.1415926535897932384626433832795028841971693993751058209749445923078164062) / 180;
}
