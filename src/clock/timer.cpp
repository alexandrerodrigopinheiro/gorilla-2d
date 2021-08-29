#include "../../includes/clock/timer.h"

g2d::clock::timer::timer()
	: _play(false)
	, _restore(0)
	, _initial(0)
	, _current(0)
{
}

g2d::clock::timer::~timer()
{
}

void g2d::clock::timer::run()
{
	if (this->_play)
	{
		this->_restore = this->current();
		return;
	}

	this->_current = this->current();
	this->_restore = 0;
}

void g2d::clock::timer::play()
{
	this->_play = true;

	if (this->_restore == 0)
	{
		this->_initial = this->current();
		return;
	}

	this->_initial += this->_restore;
	this->_restore = 0;
}

void g2d::clock::timer::stop()
{
	this->_play = false;
	this->_restore = this->current();
}

void g2d::clock::timer::reset()
{
	this->_restore = 0;
	this->_initial = this->current();
	this->_current = this->_initial;
	this->_play = false;
}

void g2d::clock::timer::replay()
{
	this->_restore = 0;
	this->_initial = this->current();
	this->_current = this->_initial;
	this->_play = true;
}

std::size_t g2d::clock::timer::elapsed() const
{
	return this->current() - this->_initial;
}

std::size_t g2d::clock::timer::current() const
{
	auto now = std::chrono::steady_clock::now();
	auto duration = now.time_since_epoch();

	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

bool g2d::clock::timer::played() const
{
	return this->_play;
}
