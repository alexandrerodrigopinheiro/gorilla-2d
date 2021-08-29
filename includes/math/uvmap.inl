template <typename T>
inline g2d::math::uvmap<T>::uvmap()
	: _u(static_cast<T>(0))
	, _v(static_cast<T>(0))
	, _null(false)
{
}

template <typename T>
inline g2d::math::uvmap<T>::uvmap(T uvmap)
	: _u(uvmap)
	, _v(uvmap)
	, _null(false)
{
}

template <typename T>
inline g2d::math::uvmap<T>::uvmap(T u, T v)
	: _u(u)
	, _v(v)
	, _null(false)
{
}

template <typename T>
inline g2d::math::uvmap<T>::~uvmap()
{
}

template <typename T>
inline void g2d::math::uvmap<T>::set(const g2d::math::uvmap<T>& copy)
{
	this->_u = copy.u();
	this->_v = copy.v();
	this->_null = copy.annul();
}

template <typename T>
inline void g2d::math::uvmap<T>::set(T uvmap)
{
	this->_u = uvmap;
	this->_v = uvmap;
}

template <typename T>
inline void g2d::math::uvmap<T>::set(T u, T v)
{
	this->_u = u;
	this->_v = v;
}

template <typename T>
inline void g2d::math::uvmap<T>::u(T u)
{
	this->_u = u;
}

template <typename T>
inline void g2d::math::uvmap<T>::v(T v)
{
	this->_v = v;
}

template <typename T>
inline T g2d::math::uvmap<T>::u() const
{
	return this->_u;
}

template <typename T>
inline T g2d::math::uvmap<T>::v() const
{
	return this->_v;
}

template <typename T>
inline g2d::math::uvmap<T> g2d::math::uvmap<T>::null() const
{
	return g2d::math::uvmap<T>(0, 0, true);
}

template <typename T>
inline bool g2d::math::uvmap<T>::annul() const
{
	return this->_null;
}

template <typename T>
inline bool g2d::math::uvmap<T>::empty()
{
	return (this->_u == 0) && (this->_v == 0);
}

template <typename T>
inline void g2d::math::uvmap<T>::string_to(const std::string& u, const std::string& v)
{
	this->_u = g2d::basic::to<T>(u);
	this->_v = g2d::basic::to<T>(v);
}

template <typename T>
inline g2d::math::uvmap<T> g2d::math::uvmap<T>::operator++()
{
	++this->_u;
	++this->_v;

	return g2d::math::uvmap<T>(this->_u, this->_v);
}

template <typename T>
inline g2d::math::uvmap<T> g2d::math::uvmap<T>::operator++(int)
{
	g2d::math::uvmap<T> result = *this;

	++this->_u;
	++this->_v;

	return result;
}

template <typename T>
inline g2d::math::uvmap<T> g2d::math::uvmap<T>::operator--()
{
	--this->_u;
	--this->_v;

	return g2d::math::uvmap<T>(this->_u, this->_v);
}

template <typename T>
inline g2d::math::uvmap<T> g2d::math::uvmap<T>::operator--(int)
{
	g2d::math::uvmap<T> result = *this;

	--this->_u;
	--this->_v;

	return result;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator-()
{
    this->_u = -this->_u;
    this->_v = -this->_v;

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator+()
{
    this->_u = +this->_u;
    this->_v = +this->_v;

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator=(const g2d::math::uvmap<T>& right)
{
    this->_u = right.u();
    this->_v = right.v();

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator+(const g2d::math::uvmap<T>& right)
{
    this->_u = this->_u + right.u();
    this->_v = this->_v + right.v();

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator-(const g2d::math::uvmap<T>& right)
{
    this->_u = this->_u - right.u();
    this->_v = this->_v - right.v();

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator*(const g2d::math::uvmap<T>& right)
{
	this->_u = this->_u * right.u();
	this->_v = this->_v * right.v();

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator/(const g2d::math::uvmap<T>& right)
{
	this->_u = this->_u / right.u();
	this->_v = this->_v / right.v();

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator+=(const g2d::math::uvmap<T>& right)
{
	this->_u = this->_u + right.u();
	this->_v = this->_v + right.v();

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator-=(const g2d::math::uvmap<T>& right)
{
	this->_u = this->_u - right.u();
	this->_v = this->_v - right.v();

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator*=(const g2d::math::uvmap<T>& right)
{
	this->_u = this->_u * right.u();
	this->_v = this->_v * right.v();

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator/=(const g2d::math::uvmap<T>& right)
{
	this->_u = this->_u / right.u();
	this->_v = this->_v / right.v();

	return *this;
}

template <typename T>
inline bool g2d::math::uvmap<T>::operator==(const g2d::math::uvmap<T>& right)
{
	return (this->_u == right.u()) && (this->_v == right.v());
}

template <typename T>
inline bool g2d::math::uvmap<T>::operator!=(const g2d::math::uvmap<T>& right)
{
	return (this->_u != right.u()) && (this->_v != right.v());
}

template <typename T>
inline bool g2d::math::uvmap<T>::operator>(const g2d::math::uvmap<T>& right)
{
	return (this->_u > right.u()) && (this->_v > right.v());
}

template <typename T>
inline bool g2d::math::uvmap<T>::operator<(const g2d::math::uvmap<T>& right)
{
	return (this->_u < right.u()) && (this->_v < right.v());
}

template <typename T>
inline bool g2d::math::uvmap<T>::operator>=(const g2d::math::uvmap<T>& right)
{
	return (this->_u >= right.u()) && (this->_v >= right.v());
}

template <typename T>
inline bool g2d::math::uvmap<T>::operator<=(const g2d::math::uvmap<T>& right)
{
	return (this->_u <= right.u()) && (this->_v <= right.v());
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator=(T right)
{
    this->_u = right;
    this->_v = right;

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator+(T right)
{
    this->_u = this->_u + right;
    this->_v = this->_v + right;

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator-(T right)
{
    this->_u = this->_u - right;
    this->_v = this->_v - right;

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator*(T right)
{
	this->_u = this->_u * right;
	this->_v = this->_v * right;

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator/(T right)
{
	this->_u = this->_u / right;
	this->_v = this->_v / right;

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator+=(T right)
{
	this->_u = this->_u + right;
	this->_v = this->_v + right;

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator-=(T right)
{
	this->_u = this->_u - right;
	this->_v = this->_v - right;

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator*=(T right)
{
	this->_u = this->_u * right;
	this->_v = this->_v * right;

	return *this;
}

template <typename T>
inline const g2d::math::uvmap<T>& g2d::math::uvmap<T>::operator/=(T right)
{
	this->_u = this->_u / right;
	this->_v = this->_v / right;

	return *this;
}

template <typename T>
inline bool g2d::math::uvmap<T>::operator==(T right)
{
	return (this->_u == right) && (this->_v == right);
}

template <typename T>
inline bool g2d::math::uvmap<T>::operator!=(T right)
{
	return (this->_u != right) && (this->_v != right);
}

template <typename T>
inline bool g2d::math::uvmap<T>::operator>(T right)
{
	return (this->_u > right) && (this->_v > right);
}

template <typename T>
inline bool g2d::math::uvmap<T>::operator<(T right)
{
	return (this->_u < right) && (this->_v < right);
}

template <typename T>
inline bool g2d::math::uvmap<T>::operator>=(T right)
{
	return (this->_u >= right) && (this->_v >= right);
}

template <typename T>
inline bool g2d::math::uvmap<T>::operator<=(T right)
{
	return (this->_u <= right) && (this->_v <= right);
}

template <typename T>
inline g2d::math::uvmap<T>::uvmap(T u, T v, bool null)
	: _u(u)
	, _v(v)
	, _null(null)
{
}

template <typename T>
inline std::ostream& g2d::math::operator<<(std::ostream& stream, const g2d::math::uvmap<T>& right)
{
	return stream << "uvmap { u " << right.u() << " v " << right.v() << " }";
}

template <typename T>
inline std::istream& g2d::math::operator>>(std::istream& stream, g2d::math::uvmap<T>& right)
{
	std::string garbage;
	T u;
	T v;

	stream >> garbage >> garbage >> garbage >> u >> garbage >> v >> garbage;

	right.set(u, v);

	return stream;
}
