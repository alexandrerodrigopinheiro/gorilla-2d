#include "../../includes/clock/tick.h"

g2d::clock::tick::tick()
	: _play(false)
	, _initial(0)
	, _current(0)
{
}

g2d::clock::tick::~tick()
{
}

void g2d::clock::tick::run()
{
	if (!this->_play)
	{
		return;
	}

	auto now = std::chrono::steady_clock::now();
	auto duration = now.time_since_epoch();

	this->_current += std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() - this->_initial;
	this->_initial = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

void g2d::clock::tick::play()
{
	auto now = std::chrono::steady_clock::now();
	auto duration = now.time_since_epoch();

	this->_initial = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	this->_play = true;
}

void g2d::clock::tick::pause()
{
	this->_play = false;
}

void g2d::clock::tick::reset()
{
	auto now = std::chrono::steady_clock::now();
	auto duration = now.time_since_epoch();

	this->_initial = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();;
	this->_current = 0;
	this->_play = false;
}

void g2d::clock::tick::replay()
{
	auto now = std::chrono::steady_clock::now();
	auto duration = now.time_since_epoch();

	this->_initial = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();;
	this->_current = 0;
	this->_play = true;
}

void g2d::clock::tick::current(std::size_t current)
{
	this->_current = current;
}

std::size_t g2d::clock::tick::current() const
{
	return this->_current;
}

bool g2d::clock::tick::played() const
{
	return this->_play;
}
