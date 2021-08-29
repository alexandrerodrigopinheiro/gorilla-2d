template <typename T>
inline g2d::math::vertex<T>::vertex()
	: _a(static_cast<T>(0))
	, _b(static_cast<T>(0))
	, _c(static_cast<T>(0))
	, _d(static_cast<T>(0))
	, _null(false)
{
}

template <typename T>
inline g2d::math::vertex<T>::vertex(T point)
	: _a(point)
	, _b(point)
	, _c(point)
	, _d(point)
	, _null(false)
{
}

template <typename T>
inline g2d::math::vertex<T>::vertex(T x, T y, T z)
	: _a(x, y, z)
	, _b(x, y, z)
	, _c(x, y, z)
	, _d(x, y, z)
	, _null(false)
{
}

template <typename T>
inline g2d::math::vertex<T>::vertex(const g2d::math::point3d<T>& a, const g2d::math::point3d<T>& b, const g2d::math::point3d<T>& c, const g2d::math::point3d<T>& d)
	: _a(a)
	, _b(b)
	, _c(c)
	, _d(d)
	, _null(false)
{
}

template <typename T>
inline g2d::math::vertex<T>::~vertex()
{
}

template <typename T>
inline void g2d::math::vertex<T>::set(const g2d::math::vertex<T>& vertex)
{
	this->_a = vertex.a();
	this->_b = vertex.b();
	this->_c = vertex.c();
	this->_d = vertex.d();
	this->_null = vertex.annul();
}

template <typename T>
inline void g2d::math::vertex<T>::set(T point)
{
	this->_a.set(point);
	this->_b.set(point);
	this->_c.set(point);
	this->_d.set(point);
}

template <typename T>
inline void g2d::math::vertex<T>::set(T x, T y, T z)
{
	this->_a.set(x, y, z);
	this->_b.set(x, y, z);
	this->_c.set(x, y, z);
	this->_d.set(x, y, z);
}

template <typename T>
inline void g2d::math::vertex<T>::set(const g2d::math::point3d<T>& a, const g2d::math::point3d<T>& b, const g2d::math::point3d<T>& c, const g2d::math::point3d<T>& d)
{
	this->_a = a;
	this->_b = b;
	this->_c = c;
	this->_d = d;
}

template <typename T>
inline void g2d::math::vertex<T>::a(const g2d::math::point3d<T>& point)
{
	this->_a = point;
}

template <typename T>
inline void g2d::math::vertex<T>::b(const g2d::math::point3d<T>& point)
{
	this->_b = point;
}

template <typename T>
inline void g2d::math::vertex<T>::c(const g2d::math::point3d<T>& point)
{
	this->_c = point;
}

template <typename T>
inline void g2d::math::vertex<T>::d(const g2d::math::point3d<T>& point)
{
	this->_d = point;
}

template <typename T>
inline void g2d::math::vertex<T>::a(T x, T y, T z)
{
	this->_a.set(x, y, z);
}

template <typename T>
inline void g2d::math::vertex<T>::b(T x, T y, T z)
{
	this->_b.set(x, y, z);
}

template <typename T>
inline void g2d::math::vertex<T>::c(T x, T y, T z)
{
	this->_c.set(x, y, z);
}

template <typename T>
inline void g2d::math::vertex<T>::d(T x, T y, T z)
{
	this->_d.set(x, y, z);
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::vertex<T>::a() const
{
	return this->_a;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::vertex<T>::b() const
{
	return this->_b;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::vertex<T>::c() const
{
	return this->_c;
}

template <typename T>
inline const g2d::math::point3d<T>& g2d::math::vertex<T>::d() const
{
	return this->_d;
}

template <typename T>
inline g2d::math::vertex<T> g2d::math::vertex<T>::null() const
{
	return g2d::math::vertex<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), true);
}

template <typename T>
inline bool g2d::math::vertex<T>::annul() const
{
	return this->_null;
}

template <typename T>
inline bool g2d::math::vertex<T>::empty() const
{
	return this->_a.empty() && this->_b.empty() && this->_c.empty() && this->_d.empty();
}

template <typename T>
inline void g2d::math::vertex<T>::string_to(const std::string& a, const std::string& b, const std::string& c, const std::string& d)
{
	this->_a = g2d::basic::to<g2d::math::point3d<T>>(a);
	this->_b = g2d::basic::to<g2d::math::point3d<T>>(b);
	this->_c = g2d::basic::to<g2d::math::point3d<T>>(c);
	this->_d = g2d::basic::to<g2d::math::point3d<T>>(d);
}

template <typename T>
inline g2d::math::vertex<T> g2d::math::vertex<T>::operator++()
{
	++this->_a;
	++this->_b;
	++this->_c;
	++this->_d;

	return g2d::math::vertex<T>(this->_a, this->_b, this->_c, this->_d);
}

template <typename T>
inline g2d::math::vertex<T> g2d::math::vertex<T>::operator++(int)
{
	g2d::math::vertex<T> result = *this;

	++this->_a;
	++this->_b;
	++this->_c;
	++this->_d;

	return result;
}

template <typename T>
inline g2d::math::vertex<T> g2d::math::vertex<T>::operator--()
{
	--this->_a;
	--this->_b;
	--this->_c;
	--this->_d;

	return g2d::math::vertex<T>(this->_a, this->_b, this->_c, this->_d);
}

template <typename T>
inline g2d::math::vertex<T> g2d::math::vertex<T>::operator--(int)
{
	g2d::math::vertex<T> result = *this;

	--this->_a;
	--this->_b;
	--this->_c;
	--this->_d;

	return result;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator-()
{
	this->_a = -this->_a;
	this->_b = -this->_b;
	this->_c = -this->_c;
	this->_d = -this->_d;

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator+()
{
	this->_a = +this->_a;
	this->_b = +this->_b;
	this->_c = +this->_c;
	this->_d = +this->_d;

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator=(const g2d::math::vertex<T>& right)
{
	this->_a = right.a();
	this->_b = right.b();
	this->_c = right.c();
	this->_d = right.d();

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator+(const g2d::math::vertex<T>& right)
{
	this->_a = this->_a + right.a();
	this->_b = this->_b + right.b();
	this->_c = this->_c + right.c();
	this->_d = this->_d + right.d();

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator-(const g2d::math::vertex<T>& right)
{
    this->_a = this->_a - right.a();
    this->_b = this->_b - right.b();
    this->_c = this->_c - right.c();
    this->_d = this->_d - right.d();

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator*(const g2d::math::vertex<T>& right)
{
    this->_a = this->_a * right.a();
    this->_b = this->_b * right.b();
    this->_c = this->_c * right.c();
    this->_d = this->_d * right.d();

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator/(const g2d::math::vertex<T>& right)
{
    this->_a = this->_a / right.a();
    this->_b = this->_b / right.b();
    this->_c = this->_c / right.c();
    this->_d = this->_d / right.d();

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator+=(const g2d::math::vertex<T>& right)
{
	this->_a = this->_a + right.a();
	this->_b = this->_b + right.b();
	this->_c = this->_c + right.c();
	this->_d = this->_d + right.d();

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator-=(const g2d::math::vertex<T>& right)
{
	this->_a = this->_a - right.a();
	this->_b = this->_b - right.b();
	this->_c = this->_c + right.c();
	this->_d = this->_d + right.d();

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator*=(const g2d::math::vertex<T>& right)
{
	this->_a = this->_a * right.a();
	this->_b = this->_b * right.b();
	this->_c = this->_c * right.c();
	this->_d = this->_d * right.d();

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator/=(const g2d::math::vertex<T>& right)
{
	this->_a = this->_a / right.a();
	this->_b = this->_b / right.b();
	this->_c = this->_c / right.c();
	this->_d = this->_d / right.d();

	return *this;
}

template <typename T>
inline bool g2d::math::vertex<T>::operator==(const g2d::math::vertex<T>& right)
{
	return (this->_a == right.a()) && (this->_b == right.b()) && (this->_c == right.c()) && (this->_d == right.d());
}

template <typename T>
inline bool g2d::math::vertex<T>::operator!=(const g2d::math::vertex<T>& right)
{
	return (this->_a != right.a()) && (this->_b != right.b()) && (this->_c != right.c()) && (this->_d != right.d());
}

template <typename T>
inline bool g2d::math::vertex<T>::operator>(const g2d::math::vertex<T>& right)
{
	return (this->_a > right.a()) && (this->_b > right.b()) && (this->_c > right.c()) && (this->_d > right.d());
}

template <typename T>
inline bool g2d::math::vertex<T>::operator<(const g2d::math::vertex<T>& right)
{
	return (this->_a < right.a()) && (this->_b < right.b()) && (this->_c < right.c()) && (this->_d < right.d());
}

template <typename T>
inline bool g2d::math::vertex<T>::operator>=(const g2d::math::vertex<T>& right)
{
	return (this->_a >= right.a()) && (this->_b >= right.b()) && (this->_c >= right.c()) && (this->_d >= right.d());
}

template <typename T>
inline bool g2d::math::vertex<T>::operator<=(const g2d::math::vertex<T>& right)
{
	return (this->_a <= right.a()) && (this->_b <= right.b()) && (this->_c <= right.c()) && (this->_d <= right.d());
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator=(T right)
{
	this->_a = right;
	this->_b = right;
	this->_c = right;
	this->_d = right;

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator+(T right)
{
	this->_a = this->_a + right;
	this->_b = this->_b + right;
	this->_c = this->_c + right;
	this->_d = this->_d + right;

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator-(T right)
{
    this->_a = this->_a - right;
    this->_b = this->_b - right;
    this->_c = this->_c - right;
    this->_d = this->_d - right;

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator*(T right)
{
    this->_a = this->_a * right;
    this->_b = this->_b * right;
    this->_c = this->_c * right;
    this->_d = this->_d * right;

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator/(T right)
{
    this->_a = this->_a / right;
    this->_b = this->_b / right;
    this->_c = this->_c / right;
    this->_d = this->_d / right;

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator+=(T right)
{
	this->_a = this->_a + right;
	this->_b = this->_b + right;
	this->_c = this->_c + right;
	this->_d = this->_d + right;

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator-=(T right)
{
	this->_a = this->_a - right;
	this->_b = this->_b - right;
	this->_c = this->_c - right;
	this->_a = this->_a - right;

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator*=(T right)
{
	this->_a = this->_a * right;
	this->_b = this->_b * right;
	this->_c = this->_c * right;
	this->_d = this->_d * right;

	return *this;
}

template <typename T>
inline const g2d::math::vertex<T>& g2d::math::vertex<T>::operator/=(T right)
{
	this->_a = this->_a / right;
	this->_b = this->_b / right;
	this->_c = this->_c / right;
	this->_d = this->_d / right;

	return *this;
}

template <typename T>
inline bool g2d::math::vertex<T>::operator==(T right)
{
	return (this->_a == right) && (this->_b == right) && (this->_c == right) && (this->_d == right);
}

template <typename T>
inline bool g2d::math::vertex<T>::operator!=(T right)
{
	return (this->_a != right) && (this->_b != right) && (this->_c != right) && (this->_d != right);
}

template <typename T>
inline bool g2d::math::vertex<T>::operator>(T right)
{
	return (this->_a > right) && (this->_b > right) && (this->_c > right) && (this->_d > right);
}

template <typename T>
inline bool g2d::math::vertex<T>::operator<(T right)
{
	return (this->_a < right) && (this->_b < right) && (this->_c < right) && (this->_d < right);
}

template <typename T>
inline bool g2d::math::vertex<T>::operator>=(T right)
{
	return (this->_a >= right) && (this->_b >= right) && (this->_c >= right) && (this->_d >= right);
}

template <typename T>
inline bool g2d::math::vertex<T>::operator<=(T right)
{
	return (this->_a <= right) && (this->_b <= right) && (this->_c <= right) && (this->_d <= right);
}

template <typename T>
inline g2d::math::vertex<T>::vertex(T a, T b, T c, T d, bool null)
	: _a(a)
	, _b(b)
	, _b(c)
	, _b(d)
	, _null(null)
{
}

template <typename T>
inline std::ostream& g2d::math::operator<<(std::ostream& stream, const g2d::math::vertex<T>& right)
{
	return stream << "vertex { a " << right.a() << " b " << right.b() << " c " << right.c() << " d " << right.d() << " }";
}

template <typename T>
inline std::istream& g2d::math::operator>>(std::istream& stream, g2d::math::vertex<T>& right)
{
	std::string garbage;
	T a;
	T b;
	T c;
	T d;

	stream >> garbage >> garbage >> garbage >> a >> garbage >> b >> garbage >> c >> garbage >> d >> garbage;

	right.set(a, b, c, d);

	return stream;
}
