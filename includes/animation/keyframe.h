#ifndef G2D_ANIMATION_KEYFRAME_H_
#define G2D_ANIMATION_KEYFRAME_H_

#pragma once

#include <iostream>
#include <string>

namespace g2d
{
	namespace animation
	{
		template<typename T>
		class keyframe
		{
			public:

				keyframe();

				keyframe(std::size_t frame, T value);

				void frame(std::size_t frame);

				void value(T value);

				std::size_t frame() const;

				T value() const;

			private:

				std::size_t _frame { 0 };
				T _value { static_cast<T>(0) };
		};
	}
}

#include "keyframe.inl"

#endif /* G2D_ANIMATION_KEYFRAME_H_ */
