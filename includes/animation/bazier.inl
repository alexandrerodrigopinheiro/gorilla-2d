template <typename T>
inline g2d::animation::bazier<T>::bazier()
	: _running(false)
	, _time(0)
	, _node(0)
	, _speed(0.001)
	, _vector(std::vector<g2d::math::point3d<T>>())
{
}

template <typename T>
inline g2d::animation::bazier<T>::~bazier()
{
	this->_vector.clear();
}

template <typename T>
inline void g2d::animation::bazier<T>::update()
{
	this->_time = g2d::math::clamp(this->_time + this->_speed, 0.0, 1.0);
}

template <typename T>
inline void g2d::animation::bazier<T>::play()
{
	this->_running = true;
}

template <typename T>
inline void g2d::animation::bazier<T>::stop()
{
	this->_running = false;
}

template <typename T>
inline void g2d::animation::bazier<T>::replay()
{
	this->_running = true;
	this->_time = 0.0;
}

template <typename T>
inline void g2d::animation::bazier<T>::reset()
{
	this->_running = false;
	this->_time = 0.0;
}

template <typename T>
inline void g2d::animation::bazier<T>::bind_point(const g2d::math::point3d<T>& point)
{
	this->_vector.push_back(point);
	this->_node = this->_vector.size() - 1;
}

template <typename T>
inline void g2d::animation::bazier<T>::bind_point(T x, T y, T z)
{
	this->_vector.push_back(g2d::math::point3d<T>(x, y, z));
	this->_node = this->_vector.size() - 1;
}

template <typename T>
inline void g2d::animation::bazier<T>::bind_point(T point)
{
	this->_vector.push_back(g2d::math::point3d<T>(point));
	this->_node = this->_vector.size() - 1;
}

template <typename T>
inline void g2d::animation::bazier<T>::bind_point_x(T x)
{
	this->_vector.push_back(g2d::math::point3d<T>(x, static_cast<T>(0), static_cast<T>(0)));
	this->_node = this->_vector.size() - 1;
}

template <typename T>
inline void g2d::animation::bazier<T>::bind_point_y(T y)
{
	this->_vector.push_back(g2d::math::point3d<T>(static_cast<T>(0), y, static_cast<T>(0)));
	this->_node = this->_vector.size() - 1;
}

template <typename T>
inline void g2d::animation::bazier<T>::bind_point_z(T z)
{
	this->_vector.push_back(g2d::math::point3d<T>(static_cast<T>(0), static_cast<T>(0), z));
	this->_node = this->_vector.size() - 1;
}

template <typename T>
inline void g2d::animation::bazier<T>::speed(double speed)
{
	this->_speed = speed;
}


template <typename T>
inline g2d::math::point3d<T> g2d::animation::bazier<T>::point()
{
	int kn;
	int nn;
	int nkn;
	double blend;
	double muk;
	double munk;

	g2d::math::point3d<T> b = g2d::math::point3d<T>(0.0);

	muk  = 1;
	munk = pow(1 - this->_time, (double)this->_node);

	for (int k = 0; k <= static_cast<int>(this->_node); k++)
	{
		nn = this->_node;
		kn = k;
		nkn = this->_node - k;
		blend = muk * munk;
		muk *= this->_time;
		munk /= (1 - this->_time);

		while (nn >= 1)
		{
			blend *= nn;
			nn--;

			if (kn > 1)
			{
				blend /= (double)kn;
				kn--;
			}

			if (nkn > 1)
			{
				blend /= (double)nkn;
				nkn--;
			}
		}

		b.x(b.x() + this->_vector[k].x() * blend);
		b.y(b.y() + this->_vector[k].y() * blend);
		b.z(b.z() + this->_vector[k].z() * blend);
	}

	if (this->_time == 1)
	{
		return this->_vector[this->_node];
	}

	if (this->_time == 0)
	{
		return this->_vector[0];
	}

	return b;
}

template <typename T>
inline double g2d::animation::bazier<T>::speed() const
{
	return this->_speed;
}

template <typename T>
inline double g2d::animation::bazier<T>::time() const
{
	return this->_time;
}

template <typename T>
inline std::size_t g2d::animation::bazier<T>::node() const
{
	return this->_node;
}

template <typename T>
inline bool g2d::animation::bazier<T>::bound() const
{
	return this->_time == 1.0;
}
