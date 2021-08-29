#include "../../includes/audio/audio_manager.h"

g2d::audio::audio_manager::audio_manager()
	: _source(std::unordered_map<std::string,std::size_t>())
	, _sound(std::unordered_map<std::size_t, g2d::audio::sound*>())
	, _music(std::unordered_map<std::size_t, g2d::audio::music*>())
{
}

g2d::audio::audio_manager::~audio_manager()
{
	this->destroy();
}

bool g2d::audio::audio_manager::sound(std::size_t identity, const std::string& filename, bool verbose)
{
	this->analyze(filename, identity);

    auto search = this->_sound.find(identity);

    if(search == this->_sound.end())
    {
		this->_sound.insert(std::make_pair(identity, new g2d::audio::sound()));

		if (!this->_sound.at(identity)->initialize(filename, verbose))
		{
			return false;
		}

		return true;
    }

	std::cerr << "Repeated identity: '" << filename << "' at '" << identity << "',failed" << std::endl;

	return false;
}

bool g2d::audio::audio_manager::music(std::size_t identity, const std::string& filename, bool verbose)
{
	this->analyze(filename, identity);

    auto search = this->_music.find(identity);

    if(search == this->_music.end())
    {
		this->_music.insert(std::make_pair(identity, new g2d::audio::music()));

		if (!this->_music.at(identity)->initialize(filename, verbose))
		{
			return false;
		}

		return true;
    }

	std::cerr << "Repeated identity: '" << filename << "' at '" << identity << "',failed" << std::endl;

	return false;
}

void g2d::audio::audio_manager::destroy()
{
	for (auto& arg : this->_sound)
	{
		delete arg.second;
	}

	for (auto& arg : this->_music)
	{
		delete arg.second;
	}
}

g2d::audio::sound* g2d::audio::audio_manager::sound(std::size_t identity) const
{
    auto search = this->_sound.find(identity);

    assert(search != this->_sound.end());

    return this->_sound.at(identity);
}

g2d::audio::music* g2d::audio::audio_manager::music(std::size_t identity) const
{
    auto search = this->_music.find(identity);

    assert(search != this->_music.end());

    return this->_music.at(identity);
}

std::size_t g2d::audio::audio_manager::size() const
{
    return this->_source.size();
}

void g2d::audio::audio_manager::analyze(const std::string& filename, std::size_t identity)
{
	auto search = this->_source.find(filename);

    assert(search == this->_source.end());

	this->_source.insert(std::make_pair(filename, identity));
}
