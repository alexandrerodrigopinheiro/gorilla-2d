#include "../../includes/animation/timeline.h"

g2d::animation::timeline::timeline()
	: _framer(nullptr)
	, _length(0)
	, _course(g2d::animation::course::course_forward)
	, _control(g2d::animation::control::control_single)
	, _frame_per_second(g2d::clock::FPS)
	, _frame_rate(g2d::clock::SECOND)
{
}

g2d::animation::timeline::~timeline()
{
	this->destroy();
}

bool g2d::animation::timeline::initialize(std::size_t length, std::size_t fps)
{
	this->_length = length;
	this->_control = g2d::animation::control::control_single;
	this->_frame_per_second = fps;
	this->_frame_rate = g2d::clock::SECOND;

	this->_framer = new g2d::animation::framer();

	if (!this->_framer->initialize(this->_frame_rate / this->_frame_per_second))
	{
		return false;
	}

	this->_framer->stop();

	return true;
}

void g2d::animation::timeline::destroy()
{
	delete this->_framer;

	this->_framer = nullptr;
}

void g2d::animation::timeline::run()
{
	this->_framer->run();

	if (this->_framer->bound())
	{
		switch (this->_control)
		{
			case g2d::animation::control::control_single:
			{
				this->_framer->frame(g2d::math::clamp(this->_framer->frame(), 0, this->_length));

				break;
			}
			case g2d::animation::control::control_cycle:
			{
				this->_framer->frame(g2d::math::wrap(this->_framer->frame(), 0, this->_length));

				break;
			}
			case g2d::animation::control::control_pingpong:
			{
				this->_framer->frame(g2d::math::clamp(this->_framer->frame(), 0, this->_length));

				if (this->_framer->frame() == this->_length)
				{
					this->_framer->course(g2d::animation::course::course_backward);
				}
				else if (this->_framer->frame() == 0)
				{
					this->_framer->course(g2d::animation::course::course_forward);
				}

				break;
			}
			case g2d::animation::control::control_elastic:
			{
				/* ... -> <- ... */
				this->_framer->frame(g2d::math::clamp(this->_framer->frame(), 0, this->_length));

				if (this->_framer->frame() == this->_length)
				{
					this->_framer->course(g2d::animation::course::course_backward);
				}
				else if (this->_framer->frame() == 0)
				{
					this->_framer->course(g2d::animation::course::course_forward);
				}

				break;
			}
		}
	}
}

void g2d::animation::timeline::play()
{
	this->_framer->play();
}

void g2d::animation::timeline::stop()
{
	this->_framer->stop();
}

void g2d::animation::timeline::replay()
{
	this->_framer->replay();
}

void g2d::animation::timeline::reset()
{
	this->_framer->reset();
}

bool g2d::animation::timeline::played() const
{
	return this->_framer->played();
}

void g2d::animation::timeline::begin()
{
	this->_framer->frame(0);
}

void g2d::animation::timeline::end()
{
	this->_framer->frame(this->_length);
}

bool g2d::animation::timeline::bound() const
{
	return (this->_framer->frame() == this->_length);
}

bool g2d::animation::timeline::onset() const
{
	return (this->_framer->frame() == 0);
}

void g2d::animation::timeline::course(const g2d::animation::course& course)
{
	this->_course = course;
	this->_framer->course(course);
}

void g2d::animation::timeline::control(const g2d::animation::control& control)
{
	this->_control = control;
}

void g2d::animation::timeline::fps(std::size_t frame_per_second)
{
	this->_frame_per_second = frame_per_second;

	this->_framer->expiry(this->_frame_rate / this->_frame_per_second);
}

void g2d::animation::timeline::frame_rate(std::size_t frame_rate)
{
	this->_frame_rate = frame_rate;

	this->_framer->expiry(this->_frame_rate / this->_frame_per_second);
}

void g2d::animation::timeline::frame(std::size_t frame)
{
	this->_framer->frame(frame);
}

std::size_t g2d::animation::timeline::length() const
{
	return this->_length;
}

const g2d::animation::course& g2d::animation::timeline::course() const
{
	return this->_course;
}

const g2d::animation::control& g2d::animation::timeline::control() const
{
	return this->_control;
}

std::size_t g2d::animation::timeline::fps() const
{
	return this->_frame_per_second;
}

std::size_t g2d::animation::timeline::frame_rate() const
{
	return this->_frame_rate;
}

std::size_t g2d::animation::timeline::frame() const
{
	return this->_framer->frame();
}

std::ostream& g2d::animation::operator<<(std::ostream& stream, const g2d::animation::timeline& timeline)
{
	stream << "timeline {";
	stream << " " << timeline.frame();
	stream << " " << timeline.length();
	stream << " " << timeline.course();
	stream << " " << timeline.control();
	stream << " " << timeline.fps();
	stream << " " << timeline.frame_rate();
	stream << " " << timeline.played();
	stream << " }";

	return stream;
}

std::istream& g2d::animation::operator>>(std::istream& stream, g2d::animation::timeline& timeline)
{
	std::string garbage;
	std::size_t frame;
//	g2d::math::rangeui timeline;
	g2d::animation::course course;
	g2d::animation::control control;
	std::size_t frame_per_second;
	std::size_t frame_rate;
	bool play;

	stream >> garbage >> garbage;
	stream >> frame;
//	stream >> timeline;
	stream >> course;
	stream >> control;
	stream >> frame_per_second;
	stream >> frame_rate;
	stream >> play;
	stream >> garbage;

	timeline.frame(frame);
//	timeline.timeline(timeline);
	timeline.course(course);
	timeline.control(control);
	timeline.fps(frame_per_second);
	timeline.frame_rate(frame_rate);
	(play ? timeline.play() : timeline.stop());

	return stream;
}
