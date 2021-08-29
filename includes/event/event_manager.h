#ifndef G2D_EVENT_EVENT_MANAGER_H_
#define G2D_EVENT_EVENT_MANAGER_H_

#pragma once

#include <string>
#include <iostream>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include "../graphic/sprite.h"

#include "keyboard.h"
#include "mouse.h"
#include "touch.h"

namespace g2d
{
	namespace event
	{
		class event_manager
		{
			public:

				event_manager();

				~event_manager();

				bool initialize(bool verbose = false);

				void destroy();

				void listener();

				void render();

				void release();

				const g2d::event::keyboard& keyoard() const;

				const g2d::event::mouse& mouse() const;

				const g2d::event::touch& touch() const;

				void verbose(bool verbose);

				bool opened() const;

				bool verbosed() const;

			private:

				bool _released { false };
				bool _pressed { false };
				bool _open { true };
				bool _verbose { false };
				g2d::event::type _type { g2d::event::type::type_none };
				g2d::event::keyboard _keyoard { g2d::event::keyboard() };
				g2d::event::mouse _mouse { g2d::event::mouse() };
				g2d::event::touch _touch { g2d::event::touch() };
				g2d::graphic::sprite* _touch_pulse { nullptr };
		};

		typedef std::shared_ptr<g2d::event::event_manager> event_manager_ptr;
	}
}

#endif /* G2D_EVENT_EVENT_MANAGER_H_ */
