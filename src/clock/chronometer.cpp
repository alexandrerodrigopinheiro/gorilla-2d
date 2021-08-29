#include "../../includes/clock/chronometer.h"

g2d::clock::chronometer::chronometer()
	: _tick(g2d::clock::tick())
	, _maximum(0)
{
}

g2d::clock::chronometer::chronometer(uint64_t maximum)
	: _tick(g2d::clock::tick())
	, _maximum(maximum)
{
	assert(this->initialize(maximum));
}

g2d::clock::chronometer::~chronometer()
{
}

bool g2d::clock::chronometer::initialize(uint64_t maximum)
{
	this->_maximum = maximum;

	return true;
}

void g2d::clock::chronometer::destroy()
{
}

void g2d::clock::chronometer::run()
{
	this->_tick.run();
}

void g2d::clock::chronometer::play()
{
	this->_tick.play();
}

void g2d::clock::chronometer::pause()
{
	this->_tick.pause();
}

void g2d::clock::chronometer::reset()
{
	this->_tick.reset();
}

void g2d::clock::chronometer::replay()
{
	this->_tick.replay();
}

void g2d::clock::chronometer::end()
{
	this->_tick.current(this->_maximum);
}

void g2d::clock::chronometer::maximum(uint64_t maximum)
{
	this->_maximum = maximum;
}

bool g2d::clock::chronometer::bound() const
{
	return this->_tick.current() == this->_maximum;
}

bool g2d::clock::chronometer::onset() const
{
	return this->_tick.current() == 0;
}

bool g2d::clock::chronometer::played() const
{
	return this->_tick.played();
}

std::size_t g2d::clock::chronometer::maximum() const
{
	return this->_maximum;
}

std::size_t g2d::clock::chronometer::current() const
{
	return this->_tick.current();
}
