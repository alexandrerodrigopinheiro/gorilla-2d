#ifndef G2D_GUI_GUI_H_
#define G2D_GUI_GUI_H_

#pragma once

#include <iostream>
#include <string>

namespace g2d
{
	namespace gui
	{
		typedef enum state
		{
			state_null = -1,
			state_enabled,
			state_hover,
			state_pressed,
			state_released,
			state_disabled
		}
		state;

		std::ostream& operator<<(std::ostream& stream, const g2d::gui::state& state);

		std::istream& operator>>(std::istream& stream, g2d::gui::state& state);

		g2d::gui::state to_state(const std::string& state);
	}
}

#endif /* G2D_GUI_GUI_H_ */
