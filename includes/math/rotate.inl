template <typename T>
inline g2d::math::rotate<T>::rotate()
	: _h(static_cast<T>(0))
	, _p(static_cast<T>(0))
	, _b(static_cast<T>(0))
	, _null(false)
{
}

template <typename T>
inline g2d::math::rotate<T>::rotate(T h, T p, T b)
	: _h(h)
	, _p(p)
	, _b(b)
	, _null(false)
{
}

template <typename T>
inline g2d::math::rotate<T>::rotate(T rotate)
	: _h(rotate)
	, _p(rotate)
	, _b(rotate)
	, _null(false)
{
}

template <typename T>
inline g2d::math::rotate<T>::~rotate()
{
}

template <typename T>
inline void g2d::math::rotate<T>::set(const g2d::math::rotate<T>& copy)
{
	this->_h = copy.h();
	this->_p = copy.p();
	this->_b = copy.b();
	this->_null = copy.annul();
}

template <typename T>
inline void g2d::math::rotate<T>::set(T rotate)
{
	this->_h = rotate;
	this->_p = rotate;
	this->_b = rotate;
}

template <typename T>
inline void g2d::math::rotate<T>::set(T h, T p, T b)
{
	this->_h = h;
	this->_p = p;
	this->_b = b;
}

template <typename T>
inline void g2d::math::rotate<T>::h(T h)
{
	this->_h = h;
}

template <typename T>
inline void g2d::math::rotate<T>::p(T p)
{
	this->_p = p;
}

template <typename T>
inline void g2d::math::rotate<T>::b(T b)
{
	this->_b = b;
}

template <typename T>
inline T g2d::math::rotate<T>::h() const
{
	return this->_h;
}

template <typename T>
inline T g2d::math::rotate<T>::p() const
{
	return this->_p;
}

template <typename T>
inline T g2d::math::rotate<T>::b() const
{
	return this->_b;
}

template <typename T>
inline g2d::math::rotate<T> g2d::math::rotate<T>::null() const
{
	return g2d::math::rotate<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), true);
}

template <typename T>
inline bool g2d::math::rotate<T>::annul() const
{
	return this->_null;
}

template <typename T>
inline bool g2d::math::rotate<T>::empty()
{
	return (this->_h == static_cast<T>(0)) && (this->_p == static_cast<T>(0)) && (this->_b == static_cast<T>(0));
}

template <typename T>
inline void g2d::math::rotate<T>::string_to(const std::string& h, const std::string& p, const std::string& b)
{
	this->_h = g2d::basic::to<T>(h);
	this->_p = g2d::basic::to<T>(p);
	this->_b = g2d::basic::to<T>(b);
}

template <typename T>
inline g2d::math::rotate<T> g2d::math::rotate<T>::operator++()
{
	++this->_h;
	++this->_p;
	++this->_b;

	return g2d::math::rotate<T>(this->_h, this->_p, this->_b);
}

template <typename T>
inline g2d::math::rotate<T> g2d::math::rotate<T>::operator++(int)
{
	g2d::math::rotate<T> result = *this;

	++this->_h;
	++this->_p;
	++this->_b;

	return result;
}

template <typename T>
inline g2d::math::rotate<T> g2d::math::rotate<T>::operator--()
{
	--this->_h;
	--this->_p;
	--this->_b;

	return g2d::math::rotate<T>(this->_h, this->_p, this->_b);
}

template <typename T>
inline g2d::math::rotate<T> g2d::math::rotate<T>::operator--(int)
{
	g2d::math::rotate<T> result = *this;

	--this->_h;
	--this->_p;
	--this->_b;

	return result;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator-()
{
	this->_h = -this->_h;
	this->_p = -this->_p;
	this->_b = -this->_b;

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator+()
{
	this->_h = +this->_h;
	this->_p = +this->_p;
	this->_b = +this->_b;

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator=(const g2d::math::rotate<T>& right)
{
	this->_h = right.h();
	this->_p = right.p();
	this->_b = right.b();

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator+(const g2d::math::rotate<T>& right)
{
	this->_h = this->_h + right.h();
	this->_p = this->_p + right.p();
	this->_b = this->_b + right.b();

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator-(const g2d::math::rotate<T>& right)
{
    this->_h = this->_h - right.h();
    this->_p = this->_p - right.p();
    this->_b = this->_b - right.b();

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator*(const g2d::math::rotate<T>& right)
{
    this->_h = this->_h * right.h();
    this->_p = this->_p * right.p();
    this->_b = this->_b * right.b();

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator/(const g2d::math::rotate<T>& right)
{
    this->_h = this->_h / right.h();
    this->_p = this->_p / right.p();
    this->_b = this->_b / right.b();

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator+=(const g2d::math::rotate<T>& right)
{
	this->_h = this->_h + right.h();
	this->_p = this->_p + right.p();
	this->_b = this->_b + right.b();

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator-=(const g2d::math::rotate<T>& right)
{
	this->_h = this->_h - right.h();
	this->_p = this->_p - right.p();
	this->_b = this->_b - right.b();

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator*=(const g2d::math::rotate<T>& right)
{
	this->_h = this->_h * right.h();
	this->_p = this->_p * right.p();
	this->_b = this->_b * right.b();

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator/=(const g2d::math::rotate<T>& right)
{
	this->_h = this->_h / right.h();
	this->_p = this->_p / right.p();
	this->_b = this->_b / right.b();

	return *this;
}

template <typename T>
inline bool g2d::math::rotate<T>::operator==(const g2d::math::rotate<T>& right)
{
	return (this->_h == right.h()) && (this->_p == right.p()) && (this->_b == right.b());
}

template <typename T>
inline bool g2d::math::rotate<T>::operator!=(const g2d::math::rotate<T>& right)
{
	return (this->_h != right.h()) && (this->_p != right.p()) && (this->_b != right.b());
}

template <typename T>
inline bool g2d::math::rotate<T>::operator>(const g2d::math::rotate<T>& right)
{
	return (this->_h > right.h()) && (this->_p > right.p()) && (this->_b > right.b());
}

template <typename T>
inline bool g2d::math::rotate<T>::operator<(const g2d::math::rotate<T>& right)
{
	return (this->_h < right.h()) && (this->_p < right.p()) && (this->_b < right.b());
}

template <typename T>
inline bool g2d::math::rotate<T>::operator>=(const g2d::math::rotate<T>& right)
{
	return (this->_h >= right.h()) && (this->_p >= right.p()) && (this->_b >= right.b());
}

template <typename T>
inline bool g2d::math::rotate<T>::operator<=(const g2d::math::rotate<T>& right)
{
	return (this->_h <= right.h()) && (this->_p <= right.p()) && (this->_b <= right.b());
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator=(T right)
{
	this->_h = right;
	this->_p = right;
	this->_b = right;

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator+(T right)
{
	this->_h = this->_h + right;
	this->_p = this->_p + right;
	this->_b = this->_b + right;

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator-(T right)
{
    this->_h = this->_h - right;
    this->_p = this->_p - right;
    this->_b = this->_b - right;

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator*(T right)
{
    this->_h = this->_h * right;
    this->_p = this->_p * right;
    this->_b = this->_b * right;

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator/(T right)
{
    this->_h = this->_h / right;
    this->_p = this->_p / right;
    this->_b = this->_b / right;

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator+=(T right)
{
	this->_h = this->_h + right;
	this->_p = this->_p + right;
	this->_b = this->_b + right;

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator-=(T right)
{
	this->_h = this->_h - right;
	this->_p = this->_p - right;
	this->_b = this->_b - right;

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator*=(T right)
{
	this->_h = this->_h * right;
	this->_p = this->_p * right;
	this->_b = this->_b * right;

	return *this;
}

template <typename T>
inline const g2d::math::rotate<T>& g2d::math::rotate<T>::operator/=(T right)
{
	this->_h = this->_h / right;
	this->_p = this->_p / right;
	this->_b = this->_b / right;

	return *this;
}

template <typename T>
inline bool g2d::math::rotate<T>::operator==(T right)
{
	return (this->_h == right) && (this->_p == right) && (this->_b == right);
}

template <typename T>
inline bool g2d::math::rotate<T>::operator!=(T right)
{
	return (this->_h != right) && (this->_p != right) && (this->_b != right);
}

template <typename T>
inline bool g2d::math::rotate<T>::operator>(T right)
{
	return (this->_h > right) && (this->_p > right) && (this->_b > right);
}

template <typename T>
inline bool g2d::math::rotate<T>::operator<(T right)
{
	return (this->_h < right) && (this->_p < right) && (this->_b < right);
}

template <typename T>
inline bool g2d::math::rotate<T>::operator>=(T right)
{
	return (this->_h >= right) && (this->_p >= right) && (this->_b >= right);
}

template <typename T>
inline g2d::math::rotate<T>::rotate(T h, T p, T b, bool null)
	: _h(h)
	, _p(p)
	, _b(b)
	, _null(null)
{
}

template <typename T>
inline std::ostream& g2d::math::operator<<(std::ostream& stream, const g2d::math::rotate<T>& right)
{
	return stream << "rotate { h " << right.h() << " p " << right.p() << " b " << right.b() << " }";
}

template <typename T>
inline std::istream& g2d::math::operator>>(std::istream& stream, g2d::math::rotate<T>& right)
{
	std::string garbage;
	T h;
	T p;
	T b;

	stream >> garbage >> garbage >> garbage >> h >> garbage >> p >> garbage >> b >> garbage;

	right.set(h, p, b);

	return stream;
}
