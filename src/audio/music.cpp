#include "../../includes/audio/music.h"

g2d::audio::music::music()
	: _loop(-1)
	, _play(false)
	, _volume(100.0)
	, _music(nullptr)
	, _filename(std::string())
{
}

g2d::audio::music::~music()
{
	this->destroy();
}

bool g2d::audio::music::initialize(const std::string& filename, bool verbose)
{
	this->_music = Mix_LoadMUS(filename.c_str());

	if (this->_music == nullptr)
	{
		std::cerr << "Cannot load music '" << filename << "' -- " << Mix_GetError() << ", failed." << std::endl;

		return false;
	}

	g2d::basic::unused(verbose);
	this->_filename = filename;

	return true;
}

void g2d::audio::music::destroy()
{
	Mix_FreeMusic(this->_music);
}

void g2d::audio::music::play()
{
	Mix_PlayMusic(this->_music, this->_loop);

	this->_play = true;
}

void g2d::audio::music::stop()
{
	if (this->_play)
	{
		Mix_PauseMusic();

		this->_play = false;
	}
}

void g2d::audio::music::loop()
{
	this->_loop = this->_loop == 0 ? -1 : this->_loop;
}

bool g2d::audio::music::looped() const
{
	return this->_loop;
}

bool g2d::audio::music::played() const
{
	return this->_play;
}

void g2d::audio::music::volume(double volume)
{
	this->_volume = g2d::math::clamp(volume, 0.0, 100.0);

	Mix_VolumeMusic(g2d::math::rule_of_three(this->_volume, MIX_MAX_VOLUME, 100.0));
}

double g2d::audio::music::volume() const
{
	return this->_volume;
}
