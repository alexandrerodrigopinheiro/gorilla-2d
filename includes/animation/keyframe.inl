template<typename T>
inline g2d::animation::keyframe<T>::keyframe()
	: _frame(0)
	, _value(static_cast<T>(0))
{
}

template<typename T>
inline g2d::animation::keyframe<T>::keyframe(std::size_t frame, T value)
	: _frame(frame)
	, _value(value)
{
}

template<typename T>
inline void g2d::animation::keyframe<T>::frame(std::size_t frame)
{
	this->_frame = frame;
}

template<typename T>
inline void g2d::animation::keyframe<T>::value(T value)
{
	this->_value = value;
}

template<typename T>
inline std::size_t g2d::animation::keyframe<T>::frame() const
{
	return this->_frame;
}

template<typename T>
inline T g2d::animation::keyframe<T>::value() const
{
	return this->_value;
}
