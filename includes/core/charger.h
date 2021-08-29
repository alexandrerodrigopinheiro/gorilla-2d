#ifndef G2D_CORE_CHARGER_H_
#define G2D_CORE_CHARGER_H_

#pragma once

#include <string>
#include <iostream>
#include <initializer_list>

#include "../graphic/sprite.h"
#include "../math/color.h"

namespace g2d
{
	namespace core
	{
		class charger
		{
			public:

				charger();

				~charger();

				bool initialize();

				void destroy();

				void size(std::size_t size);

				void update();

				void render();

				bool open();

			private:

				double _bump { 0.0 };
				g2d::graphic::sprite* _background { nullptr };
				g2d::graphic::sprite* _bar { nullptr };
				g2d::graphic::sprite* _field { nullptr };
		};
	}
}

#endif /* G2D_CORE_CHARGER_H_ */
