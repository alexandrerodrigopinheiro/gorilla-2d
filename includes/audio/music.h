#ifndef G2D_AUDIO_MUSIC_H_
#define G2D_AUDIO_MUSIC_H_

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
		class music
		{
			public:

				music();

				~music();

				bool initialize(const std::string& filename, bool verbose = false);

				void destroy();

				void play();

				void stop();

				void loop();

				bool looped() const;

				bool played() const;

				void volume(double volume);

				double volume() const;

			private:

				int _loop { -1 };
				bool _play { false };
				double _volume { 100.0 };
				Mix_Music* _music { nullptr };
				std::string _filename { std::string() };
		};
	}
}

#endif /* G2D_AUDIO_MUSIC_H_ */
