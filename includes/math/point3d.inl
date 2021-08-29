template <typename T>
inline g2d::math::point3d<T>::point3d()
	: _x(static_cast<T>(0))
	, _y(static_cast<T>(0))
	, _z(static_cast<T>(0))
	, _null(false)
{
}

template <typename T>
inline g2d::math::point3d<T>::point3d(T x, T y, T z)
	: _x(x)
	, _y(y)
	, _z(z)
	, _null(false)
{
}

template <typename T>
inline g2d::math::point3d<T>::point3d(T point)
	: _x(point)
	, _y(point)
	, _z(point)
	, _null(false)
{
}

template <typename T>
inline g2d::math::point3d<T>::~point3d()
{
}

template <typename T>
inline void g2d::math::point3d<T>::set(const g2d::math::point3d<T>& copy)
{
	this->_x = copy.x();
	this->_y = copy.y();
	this->_z = copy.z();
	this->_null = copy.annul();
}

template <typename T>
inline void g2d::math::point3d<T>::set(T point)
{
	this->_x = point;
	this->_y = point;
	this->_z = point;
}

template <typename T>
inline void g2d::math::point3d<T>::set(T x, T y, T z)
{
	this->_x = x;
	this->_y = y;
	this->_z = z;
}

template <typename T>
inline void g2d::math::point3d<T>::x(T x)
{
	this->_x = x;
}

template <typename T>
inline void g2d::math::point3d<T>::y(T y)
{
	this->_y = y;
}

template <typename T>
inline void g2d::math::point3d<T>::z(T z)
{
	this->_z = z;
}

template <typename T>
inline T g2d::math::point3d<T>::x() const
{
	return this->_x;
}

template <typename T>
inline T g2d::math::point3d<T>::y() const
{
	return this->_y;
}

template <typename T>
inline T g2d::math::point3d<T>::z() const
{
	return this->_z;
}

template <typename T>
inline g2d::math::point3d<T> g2d::math::point3d<T>::null() const
{
	return g2d::math::point3d<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), true);
}

template <typename T>
inline bool g2d::math::point3d<T>::annul() const
{
	return this->_null;
}

template <typename T>
inline bool g2d::math::point3d<T>::empty() const
{
	return (this->_x == static_cast<T>(0)) && (this->_y == static_cast<T>(0)) && (this->_z == static_cast<T>(0));
}

template <typename T>
inline double g2d::math::point3d<T>::normalize() const
{
	return std::sqrt(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z);
}

template <typename T>
inline double g2d::math::point3d<T>::angle() const
{
	return std::atan2(this->_y, this->_x);
}

template <typename T>
inline void g2d::math::point3d<T>::string_to(const std::string& x, const std::string& y, const std::string& z)
{
	this->_x = g2d::basic::to<T>(x);
	this->_y = g2d::basic::to<T>(y);
	this->_z = g2d::basic::to<T>(z);
}

template <typename T>
inline g2d::math::point3d<T> g2d::math::point3d<T>::operator++()
{
	++this->_x;
	++this->_y;
	++this->_z;

	return g2d::math::point3d<T>(this->_x, this->_y, this->_z);
}

template <typename T>
inline g2d::math::point3d<T> g2d::math::point3d<T>::operator++(int)
{
	g2d::math::point3d<T> result = *this;

	++this->_x;
	++this->_y;
	++this->_z;

	return result;
}

template <typename T>
inline g2d::math::point3d<T> g2d::math::point3d<T>::operator--()
{
	--this->_x;
	--this->_y;
	--this->_z;

	return g2d::math::point3d<T>(this->_x, this->_y, this->_z);
}

template <typename T>
inline g2d::math::point3d<T> g2d::math::point3d<T>::operator--(int)
{
	g2d::math::point3d<T> result = *this;

	--this->_x;
	--this->_y;
	--this->_z;

	return result;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator-()
{
	this->_x = -this->_x;
	this->_y = -this->_y;
	this->_z = -this->_z;

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator+()
{
	this->_x = +this->_x;
	this->_y = +this->_y;
	this->_z = +this->_z;

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator=(const g2d::math::point3d<T>& right)
{
	this->_x = right.x();
	this->_y = right.y();
	this->_z = right.z();

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator+(const g2d::math::point3d<T>& right)
{
	this->_x = this->_x + right.x();
	this->_y = this->_y + right.y();
	this->_z = this->_z + right.z();

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator-(const g2d::math::point3d<T>& right)
{
    this->_x = this->_x - right.x();
    this->_y = this->_y - right.y();
    this->_z = this->_z - right.z();

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator*(const g2d::math::point3d<T>& right)
{
    this->_x = this->_x * right.x();
    this->_y = this->_y * right.y();
    this->_z = this->_z * right.z();

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator/(const g2d::math::point3d<T>& right)
{
	this->_x = this->_x / right;
	this->_y = this->_y / right;
	this->_z = this->_z / right;

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator+=(const g2d::math::point3d<T>& right)
{
	this->_x = this->_x + right.x();
	this->_y = this->_y + right.y();
	this->_z = this->_z + right.z();

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator-=(const g2d::math::point3d<T>& right)
{
	this->_x = this->_x - right.x();
	this->_y = this->_y - right.y();
	this->_z = this->_z - right.z();

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator*=(const g2d::math::point3d<T>& right)
{
	this->_x = this->_x * right.x();
	this->_y = this->_y * right.y();
	this->_z = this->_z * right.z();

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator/=(const g2d::math::point3d<T>& right)
{
	this->_x = this->_x / right.x();
	this->_y = this->_y / right.y();
	this->_z = this->_z / right.z();

    return *this;
}

template <typename T>
inline bool g2d::math::point3d<T>::operator==(const g2d::math::point3d<T>& right)
{
	return (this->_x == right.x()) && (this->_y == right.y()) && (this->_z == right.z());
}

template <typename T>
inline bool g2d::math::point3d<T>::operator!=(const g2d::math::point3d<T>& right)
{
	return (this->_x != right.x()) && (this->_y != right.y()) && (this->_z != right.z());
}

template <typename T>
inline bool g2d::math::point3d<T>::operator>(const g2d::math::point3d<T>& right)
{
	return (this->_x > right.x()) && (this->_y > right.y()) && (this->_z > right.z());
}

template <typename T>
inline bool g2d::math::point3d<T>::operator<(const g2d::math::point3d<T>& right)
{
	return (this->_x < right.x()) && (this->_y < right.y()) && (this->_z < right.z());
}

template <typename T>
inline bool g2d::math::point3d<T>::operator>=(const g2d::math::point3d<T>& right)
{
	return (this->_x >= right.x()) && (this->_y >= right.y()) && (this->_z >= right.z());
}

template <typename T>
inline bool g2d::math::point3d<T>::operator<=(const g2d::math::point3d<T>& right)
{
	return (this->_x <= right.x()) && (this->_y <= right.y()) && (this->_z <= right.z());
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator=(T right)
{
	this->_x = right;
	this->_y = right;
	this->_z = right;

    return *this;}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator+(T right)
{
	this->_x = this->_x + right;
	this->_y = this->_y + right;
	this->_z = this->_z + right;

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator-(T right)
{
    this->_x = this->_x - right;
    this->_y = this->_y - right;
    this->_z = this->_z - right;

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator*(T right)
{
    this->_x = this->_x * right;
    this->_y = this->_y * right;
    this->_z = this->_z * right;

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator/(T right)
{
	this->_x = this->_x / right;
	this->_y = this->_y / right;
	this->_z = this->_z / right;

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator+=(T right)
{
	this->_x = this->_x + right;
	this->_y = this->_y + right;
	this->_z = this->_z + right;

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator-=(T right)
{
	this->_x = this->_x - right;
	this->_y = this->_y - right;
	this->_z = this->_z - right;

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator*=(T right)
{
	this->_x = this->_x * right;
	this->_y = this->_y * right;
	this->_z = this->_z * right;

    return *this;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::point3d<T>::operator/=(T right)
{
	this->_x = this->_x / right;
	this->_y = this->_y / right;
	this->_z = this->_z / right;

    return *this;
}

template <typename T>
inline bool g2d::math::point3d<T>::operator==(T right)
{
	return (this->_x == right) && (this->_y == right) && (this->_z == right);
}

template <typename T>
inline bool g2d::math::point3d<T>::operator!=(T right)
{
	return (this->_x != right) && (this->_y != right) && (this->_z != right);
}

template <typename T>
inline bool g2d::math::point3d<T>::operator>(T right)
{
	return (this->_x > right) && (this->_y > right) && (this->_z > right);
}

template <typename T>
inline bool g2d::math::point3d<T>::operator<(T right)
{
	return (this->_x < right) && (this->_y < right) && (this->_z < right);
}

template <typename T>
inline bool g2d::math::point3d<T>::operator>=(T right)
{
	return (this->_x >= right) && (this->_y >= right) && (this->_z >= right);
}

template <typename T>
inline bool g2d::math::point3d<T>::operator<=(T right)
{
	return (this->_x <= right) && (this->_y <= right) && (this->_z <= right);
}

template <typename T>
inline g2d::math::point3d<T>::point3d(T x, T y, T z, bool null)
	: _x(x)
	, _y(y)
	, _z(z)
	, _null(null)
{
}

template <typename T>
inline std::ostream& g2d::math::operator<<(std::ostream& stream, const g2d::math::point3d<T>& right)
{
	return stream << "point3d { x " << right.x() << " y " << right.y() << " z " << right.z() << " }";
}

template <typename T>
inline std::istream& g2d::math::operator>>(std::istream& stream, g2d::math::point3d<T>& right)
{
	std::string garbage;
	T x;
	T y;
	T z;

	stream >> garbage >> garbage >> garbage >> x >> garbage >> y >> garbage >> z >> garbage;

	right.set(x, y, z);

	return stream;
}
