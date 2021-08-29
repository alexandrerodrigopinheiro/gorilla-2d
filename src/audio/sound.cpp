#include "../../includes/audio/sound.h"

g2d::audio::sound::sound()
	: _channel(-1)
	, _loop(0)
	, _play(false)
	, _volume(100.0)
	, _sound(nullptr)
	, _filename(std::string())
{
}

g2d::audio::sound::~sound()
{
	this->destroy();
}

bool g2d::audio::sound::initialize(const std::string& filename, bool verbose)
{
	this->_sound = Mix_LoadWAV(filename.c_str());

	if (this->_sound == nullptr)
	{
		throw std::invalid_argument("Cannot load sound '" + filename + "' -- " + g2d::basic::to<std::string>(Mix_GetError()) + ", failed.");

		return false;
	}

	g2d::basic::unused(verbose);
	this->_filename = filename;

	return true;
}

void g2d::audio::sound::destroy()
{
	Mix_FreeChunk(this->_sound);
}

void g2d::audio::sound::run()
{
	Mix_PlayChannel(this->_channel, this->_sound, this->_loop);

	this->_play = true;
}

void g2d::audio::sound::play()
{
	this->_play = true;
}

void g2d::audio::sound::stop()
{
	this->_play = false;

	Mix_HaltChannel(this->_channel);
}

void g2d::audio::sound::loop()
{
	this->_loop = this->_loop == 0 ? -1 : this->_loop;
}

bool g2d::audio::sound::played() const
{
	return Mix_Playing(this->_channel);
}

bool g2d::audio::sound::looped() const
{
	return this->_loop;
}

void g2d::audio::sound::volume(double volume)
{
	this->_volume = g2d::math::clamp(volume, 0.0, 100.0);

	Mix_VolumeChunk(this->_sound, g2d::math::rule_of_three(this->_volume, MIX_MAX_VOLUME, 100.0));
}

double g2d::audio::sound::volume() const
{
	return this->_volume;
}
