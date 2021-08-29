#ifndef G2D_ANIMATION_BAZIER_H_
#define G2D_ANIMATION_BAZIER_H_

#pragma once

#include <iostream>
#include <string>

#include "../math/math.h"
#include "../math/point3d.h"

namespace g2d
{
	namespace animation
	{
		template<typename T>
		class bazier
		{
			public:

				bazier();

				~bazier();

				void update();

				void play();

				void stop();

				void replay();

				void reset();

				void bind_point(const g2d::math::point3d<T>& point);

				void bind_point(T x, T y, T z);

				void bind_point(T point);

				void bind_point_x(T x);

				void bind_point_y(T y);

				void bind_point_z(T z);

				void speed(double speed);

				g2d::math::point3d<T> point();

				double speed() const;

				double time() const;

				std::size_t node() const;

				bool bound() const;

			private:

				bool _running { false };
				double _time { 0 };
				std::size_t _node { 0 };
				double _speed { 0.001 };
				std::vector<g2d::math::point3d<T>> _vector { std::vector<g2d::math::point3d<T>>() };
		};

		typedef g2d::animation::bazier<int> bazieri;
		typedef g2d::animation::bazier<unsigned int> bazieru;
		typedef g2d::animation::bazier<float> bazierf;
		typedef g2d::animation::bazier<double> bazierd;
	}
}

#include "bazier.inl"

#endif /* G2D_ANIMATION_BAZIER_H_ */
