#ifndef G2D_AUDIO_AUDIO_MANAGER_H_
#define G2D_AUDIO_AUDIO_MANAGER_H_

#pragma once

#include <cassert>
#include <string>
#include <iostream>
#include <unordered_map>
#include <memory>

#include "sound.h"
#include "music.h"

namespace g2d
{
	namespace audio
	{
		class audio_manager
		{
			public:

				audio_manager();

				~audio_manager();

				bool sound(std::size_t identity, const std::string& filename, bool verbose);

				bool music(std::size_t identity, const std::string& filename, bool verbose);

				void destroy();

				g2d::audio::sound* sound(std::size_t identity) const;

				g2d::audio::music* music(std::size_t identity) const;

				std::size_t size() const;

			private:

				void analyze(const std::string& filename, std::size_t identity);

				std::unordered_map<std::string, std::size_t> _source { std::unordered_map<std::string, std::size_t>() };
				std::unordered_map<std::size_t, g2d::audio::sound*> _sound { std::unordered_map<std::size_t, g2d::audio::sound*>() };
				std::unordered_map<std::size_t, g2d::audio::music*> _music { std::unordered_map<std::size_t, g2d::audio::music*>() };
		};

		typedef std::shared_ptr<g2d::audio::audio_manager> audio_manager_ptr;
	}
}

#endif /* G2D_AUDIO_AUDIO_MANAGER_H_ */
