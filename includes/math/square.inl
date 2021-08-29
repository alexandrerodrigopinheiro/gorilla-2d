template <typename T>
inline g2d::math::square<T>::square()
	: _x(static_cast<T>(0))
	, _y(static_cast<T>(0))
	, _w(static_cast<T>(0))
	, _h(static_cast<T>(0))
	, _null(false)
{
}

template <typename T>
inline g2d::math::square<T>::square(T square)
	: _x(square)
	, _y(square)
	, _w(square)
	, _h(square)
	, _null(false)
{
}

template <typename T>
inline g2d::math::square<T>::square(T x, T y, T w, T h)
	: _x(x)
	, _y(y)
	, _w(w)
	, _h(h)
	, _null(false)
{
}

template <typename T>
inline g2d::math::square<T>::~square()
{
}

template <typename T>
inline void g2d::math::square<T>::set(const g2d::math::square<T>& copy)
{
	this->_x = copy.x();
	this->_y = copy.y();
	this->_w = copy.w();
	this->_h = copy.h();
	this->_null = copy.annul();
}

template <typename T>
inline void g2d::math::square<T>::set(T square)
{
	this->_x = square;
	this->_y = square;
	this->_w = square;
	this->_h = square;
}

template <typename T>
inline void g2d::math::square<T>::set(T x, T y, T w, T h)
{
	this->_x = x;
	this->_y = y;
	this->_w = w;
	this->_h = h;
}

template <typename T>
inline void g2d::math::square<T>::x(T x)
{
	this->_x = x;
}

template <typename T>
inline void g2d::math::square<T>::y(T y)
{
	this->_y = y;
}

template <typename T>
inline void g2d::math::square<T>::w(T w)
{
	this->_w = w;
}

template <typename T>
inline void g2d::math::square<T>::h(T h)
{
	this->_h = h;
}

template <typename T>
inline T g2d::math::square<T>::x() const
{
	return this->_x;
}

template <typename T>
inline T g2d::math::square<T>::y() const
{
	return this->_y;
}

template <typename T>
inline T g2d::math::square<T>::w() const
{
	return this->_w;
}

template <typename T>
inline T g2d::math::square<T>::h() const
{
	return this->_h;
}

template <typename T>
inline g2d::math::square<T> g2d::math::square<T>::null() const
{
	return g2d::math::square<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), true);
}

template <typename T>
inline bool g2d::math::square<T>::annul() const
{
	return this->_null;
}

template <typename T>
inline bool g2d::math::square<T>::empty()
{
	return (this->_x == 0) && (this->_y == 0) && (this->_w == 0) && (this->_h == 0);
}

template <typename T>
inline void g2d::math::square<T>::string_to(const std::string& x, const std::string& y, const std::string& w, const std::string& h)
{
	this->_x = g2d::basic::to<T>(x);
	this->_y = g2d::basic::to<T>(y);
	this->_w = g2d::basic::to<T>(w);
	this->_h = g2d::basic::to<T>(h);
}

template <typename T>
inline g2d::math::square<T> g2d::math::square<T>::operator++()
{
	++this->_x;
	++this->_y;
	++this->_w;
	++this->_h;

	return g2d::math::square<T>(this->_x, this->_y, this->_w, this->_h);
}

template <typename T>
inline g2d::math::square<T> g2d::math::square<T>::operator++(int)
{
	g2d::math::square<T> result = *this;

	++this->_x;
	++this->_y;
	++this->_w;
	++this->_h;

	return result;
}

template <typename T>
inline g2d::math::square<T> g2d::math::square<T>::operator--()
{
	--this->_x;
	--this->_y;
	--this->_w;
	--this->_h;

	return g2d::math::square<T>(this->_x, this->_y, this->_w, this->_h);
}

template <typename T>
inline g2d::math::square<T> g2d::math::square<T>::operator--(int)
{
	g2d::math::square<T> result = *this;

	--this->_x;
	--this->_y;
	--this->_w;
	--this->_h;

	return result;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator-()
{
	this->_x = -this->_x;
	this->_y = -this->_y;
	this->_w = -this->_w;
	this->_h = -this->_h;

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator+()
{
	this->_x = +this->_x;
	this->_y = +this->_y;
	this->_w = +this->_w;
	this->_h = +this->_h;

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator=(const g2d::math::square<T>& right)
{
	this->_x = right.x();
	this->_y = right.y();
	this->_w = right.w();
	this->_h = right.h();

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator+(const g2d::math::square<T>& right)
{
	this->_x = this->_x + right.x();
	this->_y = this->_y + right.y();
	this->_w = this->_w + right.w();
	this->_h = this->_h + right.h();

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator-(const g2d::math::square<T>& right)
{
    this->_x = this->_x - right.x();
    this->_y = this->_y - right.y();
    this->_w = this->_w - right.w();
    this->_h = this->_h - right.h();

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator*(const g2d::math::square<T>& right)
{
    this->_x = this->_x * right.x();
    this->_y = this->_y * right.y();
    this->_w = this->_w * right.w();
    this->_h = this->_h * right.h();

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator/(const g2d::math::square<T>& right)
{
    this->_x = this->_x / right.x();
    this->_y = this->_y / right.y();
    this->_w = this->_w / right.w();
    this->_h = this->_h / right.h();

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator+=(const g2d::math::square<T>& right)
{
	this->_x = this->_x + right.x();
	this->_y = this->_y + right.y();
	this->_w = this->_w + right.w();
	this->_h = this->_h + right.h();

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator-=(const g2d::math::square<T>& right)
{
	this->_x = this->_x - right.x();
	this->_y = this->_y - right.y();
	this->_w = this->_w - right.w();
	this->_h = this->_h - right.h();

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator*=(const g2d::math::square<T>& right)
{
	this->_x = this->_x * right.x();
	this->_y = this->_y * right.y();
	this->_w = this->_w * right.w();
	this->_h = this->_h * right.h();

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator/=(const g2d::math::square<T>& right)
{
	this->_x = this->_x / right.x();
	this->_y = this->_y / right.y();
	this->_w = this->_w / right.w();
	this->_h = this->_h / right.h();

	return *this;
}

template <typename T>
inline bool g2d::math::square<T>::operator==(const g2d::math::square<T>& right)
{
	return (this->_x == right.x()) && (this->_y == right.y()) && (this->_w == right.w()) && (this->_h == right.h());
}

template <typename T>
inline bool g2d::math::square<T>::operator!=(const g2d::math::square<T>& right)
{
	return (this->_x != right.x()) && (this->_y != right.y()) && (this->_w != right.w()) && (this->_h != right.h());
}

template <typename T>
inline bool g2d::math::square<T>::operator>(const g2d::math::square<T>& right)
{
	return (this->_x > right.x()) && (this->_y > right.y()) && (this->_w > right.w()) && (this->_h > right.h());
}

template <typename T>
inline bool g2d::math::square<T>::operator<(const g2d::math::square<T>& right)
{
	return (this->_x < right.x()) && (this->_y < right.y()) && (this->_w < right.w()) && (this->_h < right.h());
}

template <typename T>
inline bool g2d::math::square<T>::operator>=(const g2d::math::square<T>& right)
{
	return (this->_x >= right.x()) && (this->_y >= right.y()) && (this->_w >= right.w()) && (this->_h >= right.h());
}

template <typename T>
inline bool g2d::math::square<T>::operator<=(const g2d::math::square<T>& right)
{
	return (this->_x <= right.x()) && (this->_y <= right.y()) && (this->_w <= right.w()) && (this->_h <= right.h());
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator=(T right)
{
	this->_x = right;
	this->_y = right;
	this->_w = right;
	this->_h = right;

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator+(T right)
{
	this->_x = this->_x + right;
	this->_y = this->_y + right;
	this->_w = this->_w + right;
	this->_h = this->_h + right;

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator-(T right)
{
    this->_x = this->_x - right;
    this->_y = this->_y - right;
    this->_w = this->_w - right;
    this->_h = this->_h - right;

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator*(T right)
{
    this->_x = this->_x * right;
    this->_y = this->_y * right;
    this->_w = this->_w * right;
    this->_h = this->_h * right;

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator/(T right)
{
    this->_x = this->_x / right;
    this->_y = this->_y / right;
    this->_w = this->_w / right;
    this->_h = this->_h / right;

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator+=(T right)
{
	this->_x = this->_x + right;
	this->_y = this->_y + right;
	this->_w = this->_w + right;
	this->_h = this->_h + right;

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator-=(T right)
{
	this->_x = this->_x - right;
	this->_y = this->_y - right;
	this->_w = this->_w - right;
	this->_h = this->_h - right;

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator*=(T right)
{
	this->_x = this->_x * right;
	this->_y = this->_y * right;
	this->_w = this->_w * right;
	this->_h = this->_h * right;

	return *this;
}

template <typename T>
inline const g2d::math::square<T>& g2d::math::square<T>::operator/=(T right)
{
	this->_x = this->_x / right;
	this->_y = this->_y / right;
	this->_w = this->_w / right;
	this->_h = this->_h / right;

	return *this;
}

template <typename T>
inline bool g2d::math::square<T>::operator==(T right)
{
	return (this->_x == right) && (this->_y == right) && (this->_w == right) && (this->_h == right);
}

template <typename T>
inline bool g2d::math::square<T>::operator!=(T right)
{
	return (this->_x != right) && (this->_y != right) && (this->_w != right) && (this->_h != right);
}

template <typename T>
inline bool g2d::math::square<T>::operator>(T right)
{
	return (this->_x > right) && (this->_y > right) && (this->_w > right) && (this->_h > right);
}

template <typename T>
inline bool g2d::math::square<T>::operator<(T right)
{
	return (this->_x < right) && (this->_y < right) && (this->_w < right) && (this->_h < right);
}

template <typename T>
inline bool g2d::math::square<T>::operator>=(T right)
{
	return (this->_x >= right) && (this->_y >= right) && (this->_w >= right) && (this->_h >= right);
}

template <typename T>
inline bool g2d::math::square<T>::operator<=(T right)
{
	return (this->_x <= right) && (this->_y <= right) && (this->_w <= right) && (this->_h <= right);
}

template <typename T>
inline g2d::math::square<T>::square(T x, T y, T w, T h, bool null)
	: _x(x)
	, _y(y)
	, _w(w)
	, _h(h)
	, _null(null)
{
}

template <typename T>
inline std::ostream& g2d::math::operator<<(std::ostream& stream, const g2d::math::square<T>& right)
{
	return stream << "square { x " << right.x() << " y " << right.y() << " w " << right.w() << " h " << right.h() << " }";
}

template <typename T>
inline std::istream& g2d::math::operator>>(std::istream& stream, g2d::math::square<T>& right)
{
	std::string garbage;
	T x;
	T y;
	T w;
	T h;

	stream >> garbage >> garbage >> garbage >> x >> garbage >> y >> garbage >> w >> garbage >> h >> garbage;

	right.set(x, y, w);

	return stream;
}
