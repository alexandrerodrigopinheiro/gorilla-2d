#include "../../includes/gui/gui.h"

std::ostream& g2d::gui::operator<<(std::ostream& stream, const g2d::gui::state& state)
{
	switch (state)
	{
		case g2d::gui::state::state_null:
		{
			stream << "state { null }";

			break;
		}
		case g2d::gui::state::state_enabled:
		{
			stream << "state { normal }";

			break;
		}
		case g2d::gui::state::state_hover:
		{
			stream << "state { hover }";

			break;
		}
		case g2d::gui::state::state_pressed:
		{
			stream << "state { pressed }";

			break;
		}
		case g2d::gui::state::state_released:
		{
			stream << "state { released }";

			break;
		}
		case g2d::gui::state::state_disabled:
		{
			stream << "state { disabled }";

			break;
		}
	}

	return stream;
}

std::istream& g2d::gui::operator>>(std::istream& stream, g2d::gui::state& state)
{
	std::string garbage;
	std::string value;

	stream >> garbage >> garbage >> value >> garbage;

	if (value == "null")
	{
		state = g2d::gui::state::state_null;
	}
	else if (value == "normal")
	{
		state = g2d::gui::state::state_enabled;
	}
	else if (value == "hover")
	{
		state = g2d::gui::state::state_hover;
	}
	else if (value == "pressed")
	{
		state = g2d::gui::state::state_pressed;
	}
	else if (value == "released")
	{
		state = g2d::gui::state::state_released;
	}
	else if (value == "disabled")
	{
		state = g2d::gui::state::state_disabled;
	}

	return stream;
}

g2d::gui::state g2d::gui::to_state(const std::string& state)
{
	g2d::gui::state out;

	if (state == "null")
	{
		out = g2d::gui::state::state_null;
	}
	else if (state == "normal")
	{
		out = g2d::gui::state::state_enabled;
	}
	else if (state == "hover")
	{
		out = g2d::gui::state::state_hover;
	}
	else if (state == "pressed")
	{
		out = g2d::gui::state::state_pressed;
	}
	else if (state == "released")
	{
		out = g2d::gui::state::state_released;
	}
	else if (state == "disabled")
	{
		out = g2d::gui::state::state_disabled;
	}

	return out;
}
