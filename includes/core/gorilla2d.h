#ifndef G2D_CORE_GORILLA2D_H_
#define G2D_CORE_GORILLA2D_H_

#pragma once

#include <cassert>
#include <string>
#include <iostream>
#include <initializer_list>

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "camera.h"
#include "core.h"
#include "render.h"
#include "window.h"

#include "../audio/audio_manager.h"
#include "../basic/basic.h"
#include "../clock/hertz.h"
#include "../core/charger.h"
#include "../event/event_manager.h"
#include "../graphic/texture_manager.h"
#include "../graphic/graphic_manager.h"
#include "../gui/ruler.h"
#include "../gui/hud.h"
#include "../scene/scene_manager.h"
#include "../scene/scene.h"

namespace g2d
{
	namespace core
	{
		template<class Serialize>
		class gorilla2d
		{
			public:

				gorilla2d(int argc, char **argv);

				~gorilla2d();

				bool initialize(const std::string& caption, int x, int y, int width, int height, std::size_t fps, bool fullscreen, bool verbose);

				void destroy();

				bool serialize(Serialize* serialize);

				bool scene(const std::initializer_list<g2d::core::scene<Serialize>>& scenes);

				bool texture(const std::initializer_list<g2d::core::texture>& textures);

				bool emitter(const std::initializer_list<g2d::core::emitter>& emitters);

				bool shape(const std::initializer_list<g2d::core::shape>& shapes);

				bool sprite(const std::initializer_list<g2d::core::sprite>& sprites);

				bool stack(const std::initializer_list<g2d::core::stack>& stacks);

				bool text(const std::initializer_list<g2d::core::text>& texts);

				bool video(const std::initializer_list<g2d::core::video>& videos);

				bool sound(const std::initializer_list<g2d::core::sound>& sounds);

				bool music(const std::initializer_list<g2d::core::music>& musics);

				void charger(std::size_t first_scene);

				void running();

				void verbose(bool verbose);

				bool verbose() const;

			private:

				void resolve();

				void ruler();

				bool _verbose { false };
				g2d::core::window* _window { nullptr };
				g2d::core::render* _render { nullptr };
				g2d::core::camera* _camera { nullptr };
				g2d::core::charger* _charger { nullptr };
				g2d::scene::scene_manager<Serialize>* _scene_manager { nullptr };
				g2d::event::event_manager* _event_manager { nullptr };
				g2d::audio::audio_manager* _audio_manager { nullptr };
				g2d::graphic::texture_manager* _texture_manager { nullptr };
				g2d::graphic::graphic_manager* _graphic_manager { nullptr };
				Serialize* _serialize { nullptr };
				g2d::scene::scene<Serialize>* _scene { nullptr };
				g2d::clock::hertz* _hertz { nullptr };
				g2d::gui::ruler* _ruler { nullptr };
				g2d::gui::hud* _pointer { nullptr };
				g2d::gui::hud* _frame_rate { nullptr };
		};
	}
}

#include "gorilla2d.inl"

#endif /* G2D_CORE_GORILLA2D_H_ */
