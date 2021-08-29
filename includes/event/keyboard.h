#ifndef G2D_EVENT_KEYBOARD_H_
#define G2D_EVENT_KEYBOARD_H_

#pragma once

#include <string>
#include <iostream>

#include "event.h"

namespace g2d
{
	namespace event
	{
		class keyboard
		{
			public:

				keyboard();

				~keyboard();

				void pressed_button(const g2d::event::button& pressed_button);

				void released_button(const g2d::event::button& released_button);

				void pressed_key(const g2d::event::key& pressed_key);

				void released_key(const g2d::event::key& released_key);

				const g2d::event::button& pressed_button() const;

				const g2d::event::button& released_button() const;

				const g2d::event::key& pressed_key() const;

				const g2d::event::key& released_key() const;

				bool pressed() const;

				bool released() const;

				void clear();

			private:

				g2d::event::button _pressed_button { g2d::event::button::button_invalid};
				g2d::event::button _released_button { g2d::event::button::button_invalid};
				g2d::event::key	_pressed_key { g2d::event::key::key_none };
				g2d::event::key	_released_key { g2d::event::key::key_none };
		};
	}
}

#endif /* G2D_EVENT_KEYBOARD_H_ */
