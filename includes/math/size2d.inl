template <typename T>
inline g2d::math::size2d<T>::size2d()
	: _w(static_cast<T>(0))
	, _h(static_cast<T>(0))
	, _null(false)
{
}

template <typename T>
inline g2d::math::size2d<T>::size2d(T size)
	: _w(size)
	, _h(size)
	, _null(false)
{
}

template <typename T>
inline g2d::math::size2d<T>::size2d(T w, T h)
	: _w(w)
	, _h(h)
	, _null(false)
{
}

template <typename T>
inline g2d::math::size2d<T>::~size2d()
{
}

template <typename T>
inline void g2d::math::size2d<T>::set(const g2d::math::size2d<T>& copy)
{
	this->_w = copy.w();
	this->_h = copy.h();
	this->_null = copy.annul();
}

template <typename T>
inline void g2d::math::size2d<T>::set(T size)
{
	this->_w = size;
	this->_h = size;
}

template <typename T>
inline void g2d::math::size2d<T>::set(T w, T h)
{
	this->_w = w;
	this->_h = h;
}

template <typename T>
inline void g2d::math::size2d<T>::w(T w)
{
	this->_w = w;
}

template <typename T>
inline void g2d::math::size2d<T>::h(T h)
{
	this->_h = h;
}

template <typename T>
inline T g2d::math::size2d<T>::w() const
{
	return this->_w;
}

template <typename T>
inline T g2d::math::size2d<T>::h() const
{
	return this->_h;
}

template <typename T>
inline g2d::math::size2d<T> g2d::math::size2d<T>::null() const
{
	return g2d::math::size2d<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), true);
}

template <typename T>
inline bool g2d::math::size2d<T>::annul() const
{
	return this->_null;
}

template <typename T>
inline bool g2d::math::size2d<T>::empty()
{
	return (this->_w == 0) && (this->_h == 0);
}

template <typename T>
inline void g2d::math::size2d<T>::string_to(const std::string& w, const std::string& h)
{
	this->_w = g2d::basic::to<T>(w);
	this->_h = g2d::basic::to<T>(h);
}

template <typename T>
inline g2d::math::size2d<T> g2d::math::size2d<T>::operator++()
{
	++this->_w;
	++this->_h;

	return g2d::math::size2d<T>(this->_w, this->_h);
}

template <typename T>
inline g2d::math::size2d<T> g2d::math::size2d<T>::operator++(int)
{
	g2d::math::size2d<T> result = g2d::math::size2d<T>(this->_w, this->_h);

	++this->_w;
	++this->_h;

	return g2d::math::size2d<T>(this->_w, this->_h);
}

template <typename T>
inline g2d::math::size2d<T> g2d::math::size2d<T>::operator--()
{
	--this->_w;
	--this->_h;

	return g2d::math::size2d<T>(this->_w, this->_h);
}

template <typename T>
inline g2d::math::size2d<T> g2d::math::size2d<T>::operator--(int)
{
	g2d::math::size2d<T> result = g2d::math::size2d<T>(this->_w, this->_h);

	--this->_w;
	--this->_h;

	return result;
}

template <typename T>
inline g2d::math::size2d<T> g2d::math::size2d<T>::operator-()
{
	this->_w = -this->_w;
	this->_h = -this->_h;

	return g2d::math::size2d<T>(this->_w, this->_h);
}

template <typename T>
inline g2d::math::size2d<T> g2d::math::size2d<T>::operator+()
{
	this->_w = +this->_w;
	this->_h = +this->_h;

	return g2d::math::size2d<T>(this->_w, this->_h);
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator=(const g2d::math::size2d<T>& right)
{
	this->_w = right.w();
	this->_h = right.h();

	return *this;
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator+(const g2d::math::size2d<T>& right)
{
	this->_w = this->_w + right.w();
	this->_h = this->_h + right.h();

	return *this;
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator-(const g2d::math::size2d<T>& right)
{
    this->_w = this->_w - right.w();
    this->_h = this->_h - right.h();

	return *this;
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator*(const g2d::math::size2d<T>& right)
{
	this->_w = this->_w / right.w();
	this->_h = this->_h / right.h();

	return *this;
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator/(const g2d::math::size2d<T>& right)
{
	this->_w = this->_w / right.w();
	this->_h = this->_h / right.h();

	return *this;
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator+=(const g2d::math::size2d<T>& right)
{
	this->_w = this->_w + right.w();
	this->_h = this->_h + right.h();

	return *this;
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator-=(const g2d::math::size2d<T>& right)
{
	this->_w = this->_w - right.w();
	this->_h = this->_h - right.h();

	return *this;
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator*=(const g2d::math::size2d<T>& right)
{
	this->_w = this->_w * right.w();
	this->_h = this->_h * right.h();

	return *this;
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator/=(const g2d::math::size2d<T>& right)
{
	this->_w = this->_w / right.w();
	this->_h = this->_h / right.h();

	return *this;
}

template <typename T>
inline bool g2d::math::size2d<T>::operator==(const g2d::math::size2d<T>& right)
{
	return (this->_w == right.w()) && (this->_h == right.h());
}

template <typename T>
inline bool g2d::math::size2d<T>::operator!=(const g2d::math::size2d<T>& right)
{
	return (this->_w != right.w()) && (this->_h != right.h());
}

template <typename T>
inline bool g2d::math::size2d<T>::operator>(const g2d::math::size2d<T>& right)
{
	return (this->_w > right.w()) && (this->_h > right.h());
}

template <typename T>
inline bool g2d::math::size2d<T>::operator<(const g2d::math::size2d<T>& right)
{
	return (this->_w < right.w()) && (this->_h < right.h());
}

template <typename T>
inline bool g2d::math::size2d<T>::operator>=(const g2d::math::size2d<T>& right)
{
	return (this->_w >= right.w()) && (this->_h >= right.h());
}

template <typename T>
inline bool g2d::math::size2d<T>::operator<=(const g2d::math::size2d<T>& right)
{
	return (this->_w <= right.w()) && (this->_h <= right.h());
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator=(T right)
{
	this->_w = right;
	this->_h = right;

	return *this;
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator+(T right)
{
    this->_w = this->_w + right;
    this->_h = this->_h + right;

	return *this;
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator-(T right)
{
    this->_w = this->_w - right;
    this->_h = this->_h - right;

	return *this;
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator*(T right)
{
	this->_w = this->_w / right;
	this->_h = this->_h / right;

	return *this;
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator/(T right)
{
	this->_w = this->_w / right;
	this->_h = this->_h / right;

	return *this;
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator+=(T right)
{
	this->_w = this->_w + right;
	this->_h = this->_h + right;

	return *this;
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator-=(T right)
{
	this->_w = this->_w - right;
	this->_h = this->_h - right;

	return *this;
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator*=(T right)
{
	this->_w = this->_w * right;
	this->_h = this->_h * right;

	return *this;
}

template <typename T>
inline const g2d::math::size2d<T>& g2d::math::size2d<T>::operator/=(T right)
{
	this->_w = this->_w / right;
	this->_h = this->_h / right;

	return *this;
}

template <typename T>
inline bool g2d::math::size2d<T>::operator==(T right)
{
	return (this->_w == right) && (this->_h == right);
}

template <typename T>
inline bool g2d::math::size2d<T>::operator!=(T right)
{
	return (this->_w != right) && (this->_h != right);
}

template <typename T>
inline bool g2d::math::size2d<T>::operator>(T right)
{
	return (this->_w > right) && (this->_h > right);
}

template <typename T>
inline bool g2d::math::size2d<T>::operator<(T right)
{
	return (this->_w < right) && (this->_h < right);
}

template <typename T>
inline bool g2d::math::size2d<T>::operator>=(T right)
{
	return (this->_w >= right) && (this->_h >= right);
}

template <typename T>
inline bool g2d::math::size2d<T>::operator<=(T right)
{
	return (this->_w <= right) && (this->_h <= right);
}

template <typename T>
inline g2d::math::size2d<T>::size2d(T w, T h, bool null)
	: _w(w)
	, _h(h)
	, _null(null)
{
}

template <typename T>
inline std::ostream& g2d::math::operator<<(std::ostream& stream, const g2d::math::size2d<T>& right)
{
	return stream << "size { w " << right.w() << " h " << right.h() << " }";
}

template <typename T>
inline std::istream& g2d::math::operator>>(std::istream& stream, g2d::math::size2d<T>& right)
{
	std::string garbage;
	T w;
	T h;

	stream >> garbage >> garbage >> garbage >> w >> garbage >> h >> garbage;

	right.set(w, h);

	return stream;
}
