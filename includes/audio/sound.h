#ifndef G2D_AUDIO_SOUND_H_
#define G2D_AUDIO_SOUND_H_

#pragma once

#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>

#include "../basic/basic.h"
#include "../math/math.h"

namespace g2d
{
	namespace audio
	{
		class sound
		{
			public:

				sound();

				~sound();

				bool initialize(const std::string& filename, bool verbose = false);

				void destroy();

				void run();

				void play();

				void stop();

				void loop();

				bool looped() const;

				bool played() const;

				void volume(double volume);

				double volume() const;

			private:

				int _channel { -1 };
				int _loop { 0 };
				bool _play { false };
				double _volume { 100.0 };
				Mix_Chunk* _sound { nullptr };
				std::string _filename { std::string() };
		};
	}
}

#endif /* G2D_AUDIO_SOUND_H_ */
