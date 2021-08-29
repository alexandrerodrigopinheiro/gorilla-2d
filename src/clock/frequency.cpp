#include "../../includes/clock/frequency.h"

g2d::clock::frequency::frequency()
	: _timer(nullptr)
	, _counter(0)
	, _frequency(0)
{
}

g2d::clock::frequency::~frequency()
{
	this->destroy();
}


bool g2d::clock::frequency::initialize()
{
	this->_timer = new g2d::clock::timer();
	this->_timer->replay();

	return true;
}

void g2d::clock::frequency::destroy()
{
	delete this->_timer;

	this->_timer = nullptr;
}

bool g2d::clock::frequency::update()
{
	this->_timer->run();

	if (this->_timer->elapsed() >= g2d::clock::SECOND)
	{
		this->_frequency = this->_counter;
		this->_counter = 0;

		this->_timer->replay();
	}

	return true;
}

uint64_t g2d::clock::frequency::current()
{
	this->_counter++;

	return this->_frequency;
}
