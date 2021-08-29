#ifndef G2D_GUI_BUTTON_H_
#define G2D_GUI_BUTTON_H_

#pragma once

#include <iostream>
#include <string>

#include "../graphic/sprite.h"
#include "../math/color.h"
#include "../math/point3d.h"
#include "../math/square.h"
#include "../math/size2d.h"

#include "gui.h"

namespace g2d
{
	namespace gui
	{
		class button
		{
			public:

				button();

				~button();

				bool initialize(const std::string& filename, std::size_t colunm, std::size_t rows, std::size_t frames);

				void destroy();

				void draw();

				void state(const g2d::gui::state& state);

				void sensible(const g2d::math::squared& sensible);

				void sensible(double sensible);

				void sensible(double x, double y, double w, double h);

				void sensible_x(double x);

				void sensible_y(double y);

				void sensible_w(double w);

				void sensible_h(double h);

				void position(const g2d::math::point3dd& position);

				void position(double position);

				void position(double x, double y, double z);

				void position_x(double x);

				void position_y(double y);

				void position_z(double z);

				const g2d::math::squared& sensible() const;

				const g2d::math::point3dd& position() const;

				const g2d::gui::state& state() const;

				friend std::ostream& operator<<(std::ostream& stream, const button& button);

				friend std::istream& operator>>(std::istream& stream, button& button);

			private:

				g2d::graphic::sprite* _button { nullptr };
				g2d::gui::state _state { g2d::gui::state::state_enabled };
				g2d::math::squared _sensible { g2d::math::squared() };
		};
	}
}

#endif /* G2D_GUI_BUTTON_H_ */
