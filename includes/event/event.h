#ifndef YGL_EVENT_EVENT_H_
#define G2D_EVENT_EVENT_H_

#pragma once

#include <string>
#include <iostream>

namespace g2d
{
	namespace event
	{
		typedef enum button
		{
			button_invalid = -1,
			button_exit = 0,
			button_play,
			button_turbo,
			button_autoplay,
			button_extraball,
			button_decrease_speed,
			button_increase_speed,
			button_maximum_pattern,
			button_decrease_pattern,
			button_increase_pattern,
			button_maximum_bet,
			button_decrease_bet,
			button_increase_bet,
			button_credit,
			button_change_pattern,
			button_setting,
			button_cashout,
			button_payment,
			button_log,
			button_help,
			button_read,
			button_debug_fullscreen,
			button_debug_info,
			button_debug_ruler
		}
		button;

		std::ostream& operator<<(std::ostream& stream, const g2d::event::button& button);

		std::istream& operator>>(std::istream& stream, g2d::event::button& button);

		g2d::event::button to_button(const std::string& arg);

		typedef enum type
		{
			type_none = -1,
			type_button = 0,
			type_keyboard,
			type_mouse,
			type_touch
		}
		type;

		std::ostream& operator<<(std::ostream& stream, const g2d::event::type& type);

		std::istream& operator>>(std::istream& stream, g2d::event::type& type);

		g2d::event::type to_type(const std::string& arg);

		typedef enum click
		{
			click_none = -1,
			click_released = 0,
			click_pressed
		}
		click;

		std::ostream& operator<<(std::ostream& stream, const g2d::event::click& click);

		std::istream& operator>>(std::istream& stream, g2d::event::click& click);

		g2d::event::click to_click(const std::string& arg);

		typedef enum key
		{
			key_none = -1,
			key_released = 0,
			key_pressed
		}
		key;

		std::ostream& operator<<(std::ostream& stream, const g2d::event::key& key);

		std::istream& operator>>(std::istream& stream, g2d::event::key& key);

		g2d::event::key to_key(const std::string& arg);

		typedef enum cursor
		{
			cursor_none = -1,
			cursor_motion = 0,
			cursor_released,
			cursor_pressed
		}
		cursor;

		std::ostream& operator<<(std::ostream& stream, const g2d::event::cursor& cursor);

		std::istream& operator>>(std::istream& stream, g2d::event::cursor& cursor);

		g2d::event::cursor to_cursor(const std::string& arg);

		typedef enum finger
		{
			finger_none = -1,
			finger_motion = 0,
			finger_released,
			finger_pressed
		}
		finger;

		std::ostream& operator<<(std::ostream& stream, const g2d::event::finger& finger);

		std::istream& operator>>(std::istream& stream, g2d::event::finger& finger);

		g2d::event::finger to_finger(const std::string& arg);
	}
}

#endif /* G2D_EVENT_EVENT_H_ */
