template <typename T>
inline g2d::math::point2d<T>::point2d()
	: _x(static_cast<T>(0))
	, _y(static_cast<T>(0))
	, _null(false)
{
}

template <typename T>
inline g2d::math::point2d<T>::point2d(T x, T y)
	: _x(x)
	, _y(y)
	, _null(false)
{
}

template <typename T>
inline g2d::math::point2d<T>::point2d(T point)
	: _x(point)
	, _y(point)
	, _null(false)
{
}

template <typename T>
inline g2d::math::point2d<T>::~point2d()
{
}

template <typename T>
inline void g2d::math::point2d<T>::set(const g2d::math::point2d<T>& copy)
{
	this->_x = copy.x();
	this->_y = copy.y();
	this->_null = copy.annul();
}

template <typename T>
inline void g2d::math::point2d<T>::set(T point)
{
	this->_x = point;
	this->_y = point;
}

template <typename T>
inline void g2d::math::point2d<T>::set(T x, T y)
{
	this->_x = x;
	this->_y = y;
}

template <typename T>
inline void g2d::math::point2d<T>::x(T x)
{
	this->_x = x;
}

template <typename T>
inline void g2d::math::point2d<T>::y(T y)
{
	this->_y = y;
}

template <typename T>
inline T g2d::math::point2d<T>::x() const
{
	return this->_x;
}

template <typename T>
inline T g2d::math::point2d<T>::y() const
{
	return this->_y;
}

template <typename T>
inline g2d::math::point2d<T> g2d::math::point2d<T>::null() const
{
	return g2d::math::point2d<T>(static_cast<T>(0), static_cast<T>(0), true);
}

template <typename T>
inline bool g2d::math::point2d<T>::annul() const
{
	return this->_null;
}

template <typename T>
inline bool g2d::math::point2d<T>::empty() const
{
	return (this->_x == static_cast<T>(0)) && (this->_y == static_cast<T>(0));
}

template <typename T>
inline double g2d::math::point2d<T>::normalize() const
{
	return std::sqrt(this->_x * this->_x + this->_y * this->_y);
}

template <typename T>
inline double g2d::math::point2d<T>::angle() const
{
	return std::atan2(this->_y, this->_x);
}

template <typename T>
inline void g2d::math::point2d<T>::string_to(const std::string& x, const std::string& y)
{
	this->_x = g2d::basic::to<T>(x);
	this->_y = g2d::basic::to<T>(y);
}

template <typename T>
inline g2d::math::point2d<T> g2d::math::point2d<T>::operator++()
{
	++this->_x;
	++this->_y;

	return g2d::math::point2d<T>(this->_x, this->_y);
}

template <typename T>
inline g2d::math::point2d<T> g2d::math::point2d<T>::operator++(int)
{
	g2d::math::point2d<T> result = *this;

	++this->_x;
	++this->_y;

	return result;
}

template <typename T>
inline g2d::math::point2d<T> g2d::math::point2d<T>::operator--()
{
	--this->_x;
	--this->_y;

	return g2d::math::point2d<T>(this->_x, this->_y);
}

template <typename T>
inline g2d::math::point2d<T> g2d::math::point2d<T>::operator--(int)
{
	g2d::math::point2d<T> result = *this;

	--this->_x;
	--this->_y;

	return result;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator-()
{
	this->_x = -this->_x;
	this->_y = -this->_y;

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator+()
{
	this->_x = +this->_x;
	this->_y = +this->_y;

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator=(const g2d::math::point2d<T>& right)
{
	this->_x = right.x();
	this->_y = right.y();

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator+(const g2d::math::point2d<T>& right)
{
	this->_x = this->_x / right.x();
	this->_y = this->_y / right.y();

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator-(const g2d::math::point2d<T>& right)
{
    this->_x = this->_x - right.x();
    this->_y = this->_y - right.y();

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator*(const g2d::math::point2d<T>& right)
{
    this->_x = this->_x * right.x();
    this->_y = this->_y * right.y();

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator/(const g2d::math::point2d<T>& right)
{
    this->_x = this->_x / right.x();
    this->_y = this->_y / right.y();

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator+=(const g2d::math::point2d<T>& right)
{
	this->_x = this->_x + right.x();
	this->_y = this->_y + right.y();

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator-=(const g2d::math::point2d<T>& right)
{
	this->_x = this->_x - right.x();
	this->_y = this->_y - right.y();

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator*=(const g2d::math::point2d<T>& right)
{
	this->_x = this->_x * right.x();
	this->_y = this->_y * right.y();

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator/=(const g2d::math::point2d<T>& right)
{
	this->_x = this->_x / right.x();
	this->_y = this->_y / right.y();

	return *this;
}

template <typename T>
inline bool g2d::math::point2d<T>::operator==(const g2d::math::point2d<T>& right)
{
	return (this->_x == right.x()) && (this->_y == right.y());
}

template <typename T>
inline bool g2d::math::point2d<T>::operator!=(const g2d::math::point2d<T>& right)
{
	return (this->_x != right.x()) && (this->_y != right.y());
}

template <typename T>
inline bool g2d::math::point2d<T>::operator>(const g2d::math::point2d<T>& right)
{
	return (this->_x > right.x()) && (this->_y > right.y());
}

template <typename T>
inline bool g2d::math::point2d<T>::operator<(const g2d::math::point2d<T>& right)
{
	return (this->_x < right.x()) && (this->_y < right.y());
}

template <typename T>
inline bool g2d::math::point2d<T>::operator>=(const g2d::math::point2d<T>& right)
{
	return (this->_x >= right.x()) && (this->_y >= right.y());
}

template <typename T>
inline bool g2d::math::point2d<T>::operator<=(const g2d::math::point2d<T>& right)
{
	return (this->_x <= right.x()) && (this->_y <= right.y());
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator=(T right)
{
	this->_x = right;
	this->_y = right;

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator+(T right)
{
	this->_x = this->_x + right.x();
	this->_y = this->_y + right.y();

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator-(T right)
{
    this->_x = this->_x - right;
    this->_y = this->_y - right;

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator*(T right)
{
    this->_x = this->_x * right;
    this->_y = this->_y * right;

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator/(T right)
{
    this->_x = this->_x / right;
    this->_y = this->_y / right;

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator+=(T right)
{
	this->_x = this->_x + right;
	this->_y = this->_y + right;

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator-=(T right)
{
	this->_x = this->_x - right;
	this->_y = this->_y - right;

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator*=(T right)
{
	this->_x = this->_x * right;
	this->_y = this->_y * right;

	return *this;
}

template <typename T>
inline const g2d::math::point2d<T>& g2d::math::point2d<T>::operator/=(T right)
{
	this->_x = this->_x / right;
	this->_y = this->_y / right;

	return *this;
}

template <typename T>
inline bool g2d::math::point2d<T>::operator==(T right)
{
	return (this->_x == right) && (this->_y == right);
}

template <typename T>
inline bool g2d::math::point2d<T>::operator!=(T right)
{
	return (this->_x != right) && (this->_y != right);
}

template <typename T>
inline bool g2d::math::point2d<T>::operator>(T right)
{
	return (this->_x > right) && (this->_y > right);
}

template <typename T>
inline bool g2d::math::point2d<T>::operator<(T right)
{
	return (this->_x < right) && (this->_y < right);
}

template <typename T>
inline bool g2d::math::point2d<T>::operator>=(T right)
{
	return (this->_x >= right) && (this->_y >= right);
}

template <typename T>
inline bool g2d::math::point2d<T>::operator<=(T right)
{
	return (this->_x <= right) && (this->_y <= right);
}

template <typename T>
inline g2d::math::point2d<T>::point2d(T x, T y, bool null)
	: _x(x)
	, _y(y)
	, _null(null)
{
}

template <typename T>
inline std::ostream& g2d::math::operator<<(std::ostream& stream, const g2d::math::point2d<T>& right)
{
	return stream << "point2d { x " << right.x() << " y " << right.y() << " }";
}

template <typename T>
inline std::istream& g2d::math::operator>>(std::istream& stream, g2d::math::point2d<T>& right)
{
	std::string garbage;
	T x;
	T y;
	T z;

	stream >> garbage >> garbage >> garbage >> x >> garbage >> y >> garbage >> z >> garbage;

	right.set(x, y, z);

	return stream;
}
