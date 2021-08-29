#ifndef G2D_SCENE_SCENE_H_
#define G2D_SCENE_SCENE_H_

#pragma once

#include <SDL2/SDL_events.h>

#include <string>
#include <iostream>

#include "../audio/audio_manager.h"
#include "../event/keyboard.h"
#include "../event/mouse.h"
#include "../event/touch.h"
#include "../graphic/graphic_manager.h"
#include "../graphic/texture_manager.h"

#include "serialize.h"

namespace g2d
{
	namespace scene
	{
		template<class Serialize>
		class scene_manager;

		template<class Serialize>
		class scene
		{
			public:

				scene();

				virtual ~scene();

				virtual bool initialize(Serialize* serialize, g2d::scene::scene_manager<Serialize>* scene_manager, g2d::graphic::texture_manager* texture_manager, g2d::graphic::graphic_manager* graphic_manager, g2d::audio::audio_manager* audio_manager);

				virtual void destroy() = 0;

				virtual void appear() = 0;

				virtual void disappear() = 0;

				virtual void keyboard(const g2d::event::keyboard& keyboard) = 0;

				virtual void mouse(const g2d::event::mouse& mouse) = 0;

				virtual void touch(const g2d::event::touch& touch) = 0;

				virtual void update() = 0;

				virtual void render() = 0;

				virtual void wipeup() = 0;

				Serialize* serialize() const;

				g2d::scene::scene_manager<Serialize>* scene_manager() const;

				g2d::graphic::texture_manager* texture_manager() const;

				g2d::graphic::graphic_manager* graphic_manager() const;

				g2d::audio::audio_manager* audio_manager() const;

			private:

				Serialize* _serialize { nullptr };
				g2d::scene::scene_manager<Serialize>* _scene_manager { nullptr };
				g2d::graphic::texture_manager* _texture_manager { nullptr };
				g2d::graphic::graphic_manager* _graphic_manager { nullptr };
				g2d::audio::audio_manager* _audio_manager { nullptr };
		};
	}
}

#include "scene.inl"

#endif /* G2D_SCENE_SCENE_H_ */
