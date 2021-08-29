template <typename T>
inline g2d::math::range<T>::range()
	: _begin(static_cast<T>(0))
	, _end(static_cast<T>(0))
	, _null(false)
{
}

template <typename T>
inline g2d::math::range<T>::range(T range)
	: _begin(range)
	, _end(range)
	, _null(false)
{
}

template <typename T>
inline g2d::math::range<T>::range(T begin, T end)
	: _begin(begin)
	, _end(end)
	, _null(false)
{
}

template <typename T>
inline g2d::math::range<T>::~range()
{
}

template <typename T>
inline void g2d::math::range<T>::set(const g2d::math::range<T>& copy)
{
	this->_begin = copy.begin();
	this->_end = copy.end();
	this->_null = copy.annul();
}

template <typename T>
inline void g2d::math::range<T>::set(T range)
{
	this->_begin = range;
	this->_end = range;
}

template <typename T>
inline void g2d::math::range<T>::set(T begin, T end)
{
	this->_begin = begin;
	this->_end = end;
}

template <typename T>
inline void g2d::math::range<T>::begin(T begin)
{
	this->_begin = begin;
}

template <typename T>
inline void g2d::math::range<T>::end(T end)
{
	this->_end = end;
}

template <typename T>
inline T g2d::math::range<T>::begin() const
{
	return this->_begin;
}

template <typename T>
inline T g2d::math::range<T>::end() const
{
	return this->_end;
}

template <typename T>
inline g2d::math::range<T> g2d::math::range<T>::null() const
{
	return g2d::math::range<T>(static_cast<T>(0), static_cast<T>(0), true);
}

template <typename T>
inline bool g2d::math::range<T>::annul() const
{
	return this->_null;
}

template <typename T>
inline bool g2d::math::range<T>::empty()
{
	return this->_begin == static_cast<T>(0) && this->_end == static_cast<T>(0);
}

template <typename T>
inline bool g2d::math::range<T>::intersection(const g2d::math::range<T>& begin, const g2d::math::range<T>& end)
{
	return (this->_begin >= begin.begin() && this->_begin <= end.begin()) && (this->_end >= begin.end() && this->_end <= end.end());
}

template <typename T>
inline T g2d::math::range<T>::interval()
{
	T min = std::min(this->_begin, this->_end);
	T max = std::max(this->_begin, this->_end);

	return max - min;
}

template <typename T>
inline void g2d::math::range<T>::clear()
{
	this->_begin = static_cast<T>(0);
	this->_end = static_cast<T>(0);
}

template <typename T>
inline void g2d::math::range<T>::string_to(const std::string& begin, const std::string& end)
{
	this->_begin = g2d::basic::to<T>(begin);
	this->_end = g2d::basic::to<T>(end);
}

template <typename T>
inline g2d::math::range<T> g2d::math::range<T>::operator++()
{
	++this->_begin;
	++this->_end;

	return g2d::math::range<T>(this->_begin, this->_end);
}

template <typename T>
inline g2d::math::range<T> g2d::math::range<T>::operator++(int)
{
	g2d::math::range<T> result = *this;

	++this->_begin;
	++this->_end;

	return result;
}

template <typename T>
inline g2d::math::range<T> g2d::math::range<T>::operator--()
{
	--this->_begin;
	--this->_end;

	return g2d::math::range<T>(this->_begin, this->_end);
}

template <typename T>
inline g2d::math::range<T> g2d::math::range<T>::operator--(int)
{
	g2d::math::range<T> result = *this;

	--this->_begin;
	--this->_end;

	return result;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator-()
{
	this->_begin = -this->_begin;
	this->_end = -this->_end;

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator+()
{
	this->_begin = +this->_begin;
	this->_end = +this->_end;

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator=(const g2d::math::range<T>& right)
{
	this->_begin = right.begin();
	this->_end = right.end();

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator+(const g2d::math::range<T>& right)
{
	this->_begin = this->_begin + right.begin();
	this->_end = this->_end + right.end();

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator-(const g2d::math::range<T>& right)
{
    this->_begin = this->_begin - right.begin();
    this->_end = this->_end - right.end();

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator*(const g2d::math::range<T>& right)
{
    this->_begin = this->_begin * right.begin();
    this->_end = this->_end * right.end();

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator/(const g2d::math::range<T>& right)
{
    this->_begin = this->_begin / right.begin();
    this->_end = this->_end / right.end();

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator+=(const g2d::math::range<T>& right)
{
	this->_begin = this->_begin + right.begin();
	this->_end = this->_end + right.end();

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator-=(const g2d::math::range<T>& right)
{
	this->_begin = this->_begin - right.begin();
	this->_end = this->_end - right.end();

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator*=(const g2d::math::range<T>& right)
{
	this->_begin = this->_begin * right.begin();
	this->_end = this->_end * right.end();

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator/=(const g2d::math::range<T>& right)
{
	this->_begin = this->_begin / right.begin();
	this->_end = this->_end / right.end();

	return *this;
}

template <typename T>
inline bool g2d::math::range<T>::operator==(const g2d::math::range<T>& right)
{
	return (this->_begin == right.begin()) && (this->_end == right.end());
}

template <typename T>
inline bool g2d::math::range<T>::operator!=(const g2d::math::range<T>& right)
{
	return (this->_begin != right.begin()) && (this->_end != right.end());
}

template <typename T>
inline bool g2d::math::range<T>::operator>(const g2d::math::range<T>& right)
{
	return (this->_begin > right.begin()) && (this->_end > right.end());
}

template <typename T>
inline bool g2d::math::range<T>::operator<(const g2d::math::range<T>& right)
{
	return (this->_begin < right.begin()) && (this->_end < right.end());
}

template <typename T>
inline bool g2d::math::range<T>::operator>=(const g2d::math::range<T>& right)
{
	return (this->_begin >= right.begin()) && (this->_end >= right.end());
}

template <typename T>
inline bool g2d::math::range<T>::operator<=(const g2d::math::range<T>& right)
{
	return (this->_begin <= right.begin()) && (this->_end <= right.end());
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator=(T right)
{
	this->_begin = right;
	this->_end = right;

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator+(T right)
{
	this->_begin = this->_begin + right;
	this->_end = this->_end + right;

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator-(T right)
{
    this->_begin = this->_begin - right;
    this->_end = this->_end - right;

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator*(T right)
{
    this->_begin = this->_begin * right;
    this->_end = this->_end * right;

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator/(T right)
{
    this->_begin = this->_begin / right;
    this->_end = this->_end / right;

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator+=(T right)
{
	this->_begin = this->_begin + right;
	this->_end = this->_end + right;

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator-=(T right)
{
	this->_begin = this->_begin - right;
	this->_end = this->_end - right;

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator*=(T right)
{
	this->_begin = this->_begin * right;
	this->_end = this->_end * right;

	return *this;
}

template <typename T>
inline const g2d::math::range<T>& g2d::math::range<T>::operator/=(T right)
{
	this->_begin = this->_begin / right;
	this->_end = this->_end / right;

	return *this;
}

template <typename T>
inline bool g2d::math::range<T>::operator==(T right)
{
	return (this->_begin == right) && (this->_end == right);
}

template <typename T>
inline bool g2d::math::range<T>::operator!=(T right)
{
	return (this->_begin != right) && (this->_end != right);
}

template <typename T>
inline bool g2d::math::range<T>::operator>(T right)
{
	return (this->_begin > right) && (this->_end > right);
}

template <typename T>
inline bool g2d::math::range<T>::operator<(T right)
{
	return (this->_begin < right) && (this->_end < right);
}

template <typename T>
inline bool g2d::math::range<T>::operator>=(T right)
{
	return (this->_begin >= right) && (this->_end >= right);
}

template <typename T>
inline bool g2d::math::range<T>::operator<=(T right)
{
	return (this->_begin <= right) && (this->_end <= right);
}

template <typename T>
inline g2d::math::range<T>::range(T begin, T end, bool null)
	: _begin(begin)
	, _end(end)
	, _null(null)
{
}


template <typename T>
inline std::ostream& g2d::math::operator<<(std::ostream& stream, const g2d::math::range<T>& right)
{
	return stream << "range { begin " << right.begin() << " end " << right.end() << " }";
}


template <typename T>

inline std::istream& g2d::math::operator>>(std::istream& stream, g2d::math::range<T>& right)
{
	std::string garbage;
	T begin;
	T end;

	stream >> garbage >> garbage >> garbage >> begin >> garbage >> end >> garbage;

	right.set(begin, end);

	return stream;
}
