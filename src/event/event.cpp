#include "../../includes/event/event.h"

std::ostream& g2d::event::operator<<(std::ostream& stream, const g2d::event::button& button)
{
	switch(button)
	{
		case g2d::event::button_invalid:
		{
			stream << "button { invalid }";
			break;
		}
		case g2d::event::button_exit:
		{
			stream << "button { exit }";
			break;
		}
		case g2d::event::button_play:
		{
			stream << "button { play }";
			break;
		}
		case g2d::event::button_turbo:
		{
			stream << "button { turbo }";
			break;
		}
		case g2d::event::button_autoplay:
		{
			stream << "button { autoplay }";
			break;
		}
		case g2d::event::button_extraball:
		{
			stream << "button { extraball }";
			break;
		}
		case g2d::event::button_decrease_speed:
		{
			stream << "button { decrease_speed }";
			break;
		}
		case g2d::event::button_increase_speed:
		{
			stream << "button { increase_speed }";
			break;
		}
		case g2d::event::button_maximum_pattern:
		{
			stream << "button { maximum_pattern }";
			break;
		}
		case g2d::event::button_decrease_pattern:
		{
			stream << "button { decrease_pattern }";
			break;
		}
		case g2d::event::button_increase_pattern:
		{
			stream << "button { increase_pattern }";
			break;
		}
		case g2d::event::button_maximum_bet:
		{
			stream << "button { maximum_bet }";
			break;
		}
		case g2d::event::button_decrease_bet:
		{
			stream << "button { decrease_bet }";
			break;
		}
		case g2d::event::button_increase_bet:
		{
			stream << "button { increase_bet }";
			break;
		}
		case g2d::event::button_credit:
		{
			stream << "button { credit }";
			break;
		}
		case g2d::event::button_change_pattern:
		{
			stream << "button { change_pattern }";
			break;
		}
		case g2d::event::button_setting:
		{
			stream << "button { setting }";
			break;
		}
		case g2d::event::button_cashout:
		{
			stream << "button { cashout }";
			break;
		}
		case g2d::event::button_payment:
		{
			stream << "button { payment }";
			break;
		}
		case g2d::event::button_log:
		{
			stream << "button { log }";
			break;
		}
		case g2d::event::button_help:
		{
			stream << "button { help }";
			break;
		}
		case g2d::event::button_read:
		{
			stream << "button { read }";
			break;
		}
		case g2d::event::button_debug_fullscreen:
		{
			stream << "button { debug_fullscreen }";
			break;
		}
		case g2d::event::button_debug_ruler:
		{
			stream << "button { debug_ruler }";
			break;
		}
		case g2d::event::button_debug_info:
		{
			stream << "button { debug_info }";
			break;
		}
	}

	return stream;
}

std::istream& g2d::event::operator>>(std::istream& stream, g2d::event::button& button)
{
	std::string garbage;
	std::string value;

	stream >> garbage >> garbage >> value >> garbage;

	if (value == "invalid")
	{
		button = g2d::event::button_invalid;
	}
	else if (value == "exit")
	{
		button = g2d::event::button_exit;
	}
	else if (value == "play")
	{
		button = g2d::event::button_play;
	}
	else if (value == "turbo")
	{
		button = g2d::event::button_turbo;
	}
	else if (value == "autoplay")
	{
		button = g2d::event::button_autoplay;
	}
	else if (value == "extraball")
	{
		button = g2d::event::button_extraball;
	}
	else if (value == "decrease_speed")
	{
		button = g2d::event::button_decrease_speed;
	}
	else if (value == "increase_speed")
	{
		button = g2d::event::button_increase_speed;
	}
	else if (value == "maximum_pattern")
	{
		button = g2d::event::button_maximum_pattern;
	}
	else if (value == "decrease_pattern")
	{
		button = g2d::event::button_decrease_pattern;
	}
	else if (value == "increase_pattern")
	{
		button = g2d::event::button_increase_pattern;
	}
	else if (value == "maximum_bet")
	{
		button = g2d::event::button_maximum_bet;
	}
	else if (value == "decrease_bet")
	{
		button = g2d::event::button_decrease_bet;
	}
	else if (value == "increase_bet")
	{
		button = g2d::event::button_increase_bet;
	}
	else if (value == "credit")
	{
		button = g2d::event::button_credit;
	}
	else if (value == "change_pattern")
	{
		button = g2d::event::button_change_pattern;
	}
	else if (value == "setting")
	{
		button = g2d::event::button_setting;
	}
	else if (value == "cashout")
	{
		button = g2d::event::button_cashout;
	}
	else if (value == "payment")
	{
		button = g2d::event::button_payment;
	}
	else if (value == "log")
	{
		button = g2d::event::button_log;
	}
	else if (value == "help")
	{
		button = g2d::event::button_help;
	}
	else if (value == "turbo")
	{
		button = g2d::event::button_turbo;
	}
	else if (value == "debug_fullscreen")
	{
		button = g2d::event::button_debug_fullscreen;
	}
	else if (value == "debug_info")
	{
		button = g2d::event::button_debug_info;
	}
	else if (value == "debug_ruler")
	{
		button = g2d::event::button_debug_ruler;
	}

	return stream;
}

g2d::event::button g2d::event::to_button(const std::string& arg)
{
	g2d::event::button out;

	if (arg == "invalid")
	{
		out = g2d::event::button::button_invalid;
	}
	else if (arg == "exit")
	{
		out = g2d::event::button::button_exit;
	}
	else if (arg == "play")
	{
		out = g2d::event::button::button_play;
	}
	else if (arg == "turbo")
	{
		out = g2d::event::button::button_turbo;
	}
	else if (arg == "autoplay")
	{
		out = g2d::event::button::button_autoplay;
	}
	else if (arg == "extraball")
	{
		out = g2d::event::button::button_extraball;
	}
	else if (arg == "decrease_speed")
	{
		out = g2d::event::button::button_decrease_speed;
	}
	else if (arg == "increase_speed")
	{
		out = g2d::event::button::button_increase_speed;
	}
	else if (arg == "maximum_pattern")
	{
		out = g2d::event::button::button_maximum_pattern;
	}
	else if (arg == "increase_pattern")
	{
		out = g2d::event::button::button_increase_pattern;
	}
	else if (arg == "decrease_pattern")
	{
		out = g2d::event::button::button_decrease_pattern;
	}
	else if (arg == "maximum_bet")
	{
		out = g2d::event::button::button_maximum_bet;
	}
	else if (arg == "decrease_bet")
	{
		out = g2d::event::button::button_decrease_bet;
	}
	else if (arg == "increase_bet")
	{
		out = g2d::event::button::button_increase_bet;
	}
	else if (arg == "credit")
	{
		out = g2d::event::button::button_credit;
	}
	else if (arg == "decrease_bet")
	{
		out = g2d::event::button::button_decrease_bet;
	}
	else if (arg == "change_pattern")
	{
		out = g2d::event::button::button_change_pattern;
	}
	else if (arg == "setting")
	{
		out = g2d::event::button::button_setting;
	}
	else if (arg == "cashout")
	{
		out = g2d::event::button::button_cashout;
	}
	else if (arg == "payment")
	{
		out = g2d::event::button::button_payment;
	}
	else if (arg == "log")
	{
		out = g2d::event::button::button_log;
	}
	else if (arg == "help")
	{
		out = g2d::event::button::button_help;
	}
	else if (arg == "read")
	{
		out = g2d::event::button::button_read;
	}
	else if (arg == "debug_fullscreen")
	{
		out = g2d::event::button::button_debug_fullscreen;
	}
	else if (arg == "debug_info")
	{
		out = g2d::event::button::button_debug_info;
	}
	else if (arg == "debug_ruler")
	{
		out = g2d::event::button::button_debug_ruler;
	}

	return out;
}
std::ostream& g2d::event::operator<<(std::ostream& stream, const g2d::event::type& type)
{
	switch(type)
	{
		case g2d::event::type_none:
		{
			stream << "type { none }";
			break;
		}
		case g2d::event::type_button:
		{
			stream << "type { button }";
			break;
		}
		case g2d::event::type_keyboard:
		{
			stream << "type { keyboard }";
			break;
		}
		case g2d::event::type_mouse:
		{
			stream << "type { mouse }";
			break;
		}
		case g2d::event::type_touch:
		{
			stream << "type { touch }";
			break;
		}
	}

	return stream;
}

std::istream& g2d::event::operator>>(std::istream& stream, g2d::event::type& type)
{
	std::string garbage;
	std::string value;

	stream >> garbage >> garbage >> value >> garbage;

	if (value == "none")
	{
		type = g2d::event::type_none;
	}
	else if (value == "button")
	{
		type = g2d::event::type_button;
	}
	else if (value == "keyboard")
	{
		type = g2d::event::type_keyboard;
	}
	else if (value == "mouse")
	{
		type = g2d::event::type_mouse;
	}
	else if (value == "touch")
	{
		type = g2d::event::type_touch;
	}

	return stream;
}

g2d::event::type g2d::event::to_type(const std::string& arg)
{
	g2d::event::type out;

	if (arg == "none")
	{
		out = g2d::event::type::type_none;
	}
	else if (arg == "button")
	{
		out = g2d::event::type::type_button;
	}
	else if (arg == "keyboard")
	{
		out = g2d::event::type::type_keyboard;
	}
	else if (arg == "mouse")
	{
		out = g2d::event::type::type_mouse;
	}
	else if (arg == "touch")
	{
		out = g2d::event::type::type_touch;
	}

	return out;
}

std::ostream& g2d::event::operator<<(std::ostream& stream, const g2d::event::click& click)
{
	switch(click)
	{
		case g2d::event::click_none:
		{
			stream << "click { none }";
			break;
		}
		case g2d::event::click_released:
		{
			stream << "click { release }";
			break;
		}
		case g2d::event::click_pressed:
		{
			stream << "click { pressed }";
			break;
		}
	}

	return stream;
}

std::istream& g2d::event::operator>>(std::istream& stream, g2d::event::click& click)
{
	std::string garbage;
	std::string value;

	stream >> garbage >> garbage >> value >> garbage;

	if (value == "none")
	{
		click = g2d::event::click_none;
	}
	else if (value == "release")
	{
		click = g2d::event::click_released;
	}
	else if (value == "pressed")
	{
		click = g2d::event::click_pressed;
	}

	return stream;
}

g2d::event::click g2d::event::to_click(const std::string& arg)
{
	g2d::event::click out;

	if (arg == "none")
	{
		out = g2d::event::click::click_none;
	}
	else if (arg == "released")
	{
		out = g2d::event::click::click_released;
	}
	else if (arg == "pressed")
	{
		out = g2d::event::click::click_pressed;
	}

	return out;
}

std::ostream& g2d::event::operator<<(std::ostream& stream, const g2d::event::key& key)
{
	switch(key)
	{
		case g2d::event::key_none:
		{
			stream << "key { none }";
			break;
		}
		case g2d::event::key_released:
		{
			stream << "key { release }";
			break;
		}
		case g2d::event::key_pressed:
		{
			stream << "key { pressed }";
			break;
		}
	}

	return stream;
}

std::istream& g2d::event::operator>>(std::istream& stream, g2d::event::key& key)
{
	std::string garbage;
	std::string value;

	stream >> garbage >> garbage >> value >> garbage;

	if (value == "none")
	{
		key = g2d::event::key_none;
	}
	else if (value == "release")
	{
		key = g2d::event::key_released;
	}
	else if (value == "pressed")
	{
		key = g2d::event::key_pressed;
	}

	return stream;
}

g2d::event::key g2d::event::to_key(const std::string& arg)
{
	g2d::event::key out;

	if (arg == "none")
	{
		out = g2d::event::key::key_none;
	}
	else if (arg == "released")
	{
		out = g2d::event::key::key_released;
	}
	else if (arg == "pressed")
	{
		out = g2d::event::key::key_pressed;
	}

	return out;
}

std::ostream& g2d::event::operator<<(std::ostream& stream, const g2d::event::cursor& cursor)
{
	switch(cursor)
	{
		case g2d::event::cursor_none:
		{
			stream << "cursor { none }";
			break;
		}
		case g2d::event::cursor_motion:
		{
			stream << "cursor { motion }";
			break;
		}
		case g2d::event::cursor_released:
		{
			stream << "cursor { release }";
			break;
		}
		case g2d::event::cursor_pressed:
		{
			stream << "cursor { pressed }";
			break;
		}
	}

	return stream;
}

std::istream& g2d::event::operator>>(std::istream& stream, g2d::event::cursor& cursor)
{
	std::string garbage;
	std::string value;

	stream >> garbage >> garbage >> value >> garbage;

	if (value == "none")
	{
		cursor = g2d::event::cursor_none;
	}
	else if (value == "motion")
	{
		cursor = g2d::event::cursor_motion;
	}
	else if (value == "release")
	{
		cursor = g2d::event::cursor_released;
	}
	else if (value == "pressed")
	{
		cursor = g2d::event::cursor_pressed;
	}

	return stream;
}

g2d::event::cursor g2d::event::to_cursor(const std::string& arg)
{
	g2d::event::cursor out;

	if (arg == "none")
	{
		out = g2d::event::cursor::cursor_none;
	}
	else if (arg == "motion")
	{
		out = g2d::event::cursor::cursor_motion;
	}
	else if (arg == "released")
	{
		out = g2d::event::cursor::cursor_released;
	}
	else if (arg == "pressed")
	{
		out = g2d::event::cursor::cursor_pressed;
	}

	return out;
}

std::ostream& g2d::event::operator<<(std::ostream& stream, const g2d::event::finger& finger)
{
	switch(finger)
	{
		case g2d::event::finger_none:
		{
			stream << "finger { none }";
			break;
		}
		case g2d::event::finger_motion:
		{
			stream << "finger { motion }";
			break;
		}
		case g2d::event::finger_released:
		{
			stream << "finger { release }";
			break;
		}
		case g2d::event::finger_pressed:
		{
			stream << "finger { pressed }";
			break;
		}
	}

	return stream;
}

std::istream& g2d::event::operator>>(std::istream& stream, g2d::event::finger& finger)
{
	std::string garbage;
	std::string value;

	stream >> garbage >> garbage >> value >> garbage;

	if (value == "none")
	{
		finger = g2d::event::finger_none;
	}
	else if (value == "motion")
	{
		finger = g2d::event::finger_motion;
	}
	else if (value == "release")
	{
		finger = g2d::event::finger_released;
	}
	else if (value == "pressed")
	{
		finger = g2d::event::finger_pressed;
	}

	return stream;
}

g2d::event::finger g2d::event::to_finger(const std::string& arg)
{
	g2d::event::finger out;

	if (arg == "none")
	{
		out = g2d::event::finger::finger_none;
	}
	else if (arg == "motion")
	{
		out = g2d::event::finger::finger_motion;
	}
	else if (arg == "released")
	{
		out = g2d::event::finger::finger_released;
	}
	else if (arg == "pressed")
	{
		out = g2d::event::finger::finger_pressed;
	}

	return out;
}
