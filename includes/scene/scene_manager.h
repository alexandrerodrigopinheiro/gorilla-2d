#ifndef G2D_SCENE_SCENE_MANAGER_H_
#define G2D_SCENE_SCENE_MANAGER_H_

#pragma once

#include <cassert>
#include <string>
#include <iostream>
#include <unordered_map>
#include <memory>

#include "scene.h"

namespace g2d
{
	namespace scene
	{
		template<class Serialize>
		class scene_manager
		{
			public:

				scene_manager();

				~scene_manager();

				void destroy();

				bool attach(std::size_t identity, g2d::scene::scene<Serialize>* scene);

				bool detach(std::size_t identity);

				bool change(std::size_t identity);

				void update();

				bool change() const;

				void set(Serialize* serialize, g2d::scene::scene_manager<Serialize>* scene_manager, g2d::graphic::texture_manager* texture_manager, g2d::graphic::graphic_manager* graphic_manager, g2d::audio::audio_manager* audio_manager);

				std::size_t last_scene() const;

				std::size_t current_scene() const;

				g2d::scene::scene<Serialize>* scene() const;

				std::size_t size() const;

			private:

				bool _change { false };
				std::size_t _last_scene { 0 };
				std::size_t _current_scene { 0 };
				std::unordered_map<std::size_t, g2d::scene::scene<Serialize>*> _scene { std::unordered_map<std::size_t, g2d::scene::scene<Serialize>*>() };
		};
	}
}

#include "scene_manager.inl"

#endif /* G2D_SCENE_SCENE_MANAGER_H_ */
