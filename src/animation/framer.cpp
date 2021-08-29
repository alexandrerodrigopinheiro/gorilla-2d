#include "../../includes/animation/framer.h"

g2d::animation::framer::framer()
	: _timer(nullptr)
	, _course(g2d::animation::course::course_forward)
	, _expiry(0)
	, _frame(0)
	, _play(false)
	, _bound(false)
{
}

g2d::animation::framer::~framer()
{
	this->destroy();
}

bool g2d::animation::framer::initialize(std::size_t expired)
{
	this->_timer = new g2d::clock::timer();
	this->_course = g2d::animation::course::course_forward;
	this->_expiry = expired;
	this->_frame = 0;

	this->reset();

	return true;
}

void g2d::animation::framer::destroy()
{
	delete this->_timer;

	this->_timer = nullptr;
}

void g2d::animation::framer::run()
{
	this->_timer->run();

	if (this->_play)
	{
		if (this->_timer->elapsed() >= this->_expiry)
		{
			switch (this->_course)
			{
				case g2d::animation::course::course_forward:
				{
					this->_frame++;

					break;
				}
				case g2d::animation::course::course_backward:
				{
					this->_frame = this->_frame == 0 ? this->_frame : this->_frame - 1;

					break;
				}
			}

			this->_timer->replay();

			this->_bound = true;
		}
		else
		{
			this->_bound = false;
		}
	}
}

void g2d::animation::framer::play()
{
	this->_timer->play();

	this->_play = true;
}

void g2d::animation::framer::stop()
{
	this->_timer->stop();

	this->_play = false;
}

void g2d::animation::framer::replay()
{
	this->_timer->replay();

	this->_frame = 0;
	this->_play = true;
	this->_bound = false;
}

void g2d::animation::framer::reset()
{
	this->_timer->reset();
}

bool g2d::animation::framer::bound() const
{
	return this->_bound;
}

bool g2d::animation::framer::played() const
{
	return this->_play;
}

void g2d::animation::framer::course(const g2d::animation::course& course)
{
	this->_course = course;
}

void g2d::animation::framer::frame(std::size_t frame)
{
	this->_frame = frame;
}

void g2d::animation::framer::expiry(std::size_t expired)
{
	this->_expiry = expired;
}

const g2d::animation::course& g2d::animation::framer::course() const
{
	return this->_course;
}

std::size_t g2d::animation::framer::frame() const
{
	return this->_frame;
}

std::size_t g2d::animation::framer::expiry() const
{
	return this->_expiry;
}
