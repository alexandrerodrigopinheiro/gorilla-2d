#include "../../includes/clock/hertz.h"

g2d::clock::hertz::hertz()
	: _timer(nullptr)
	, _frequency(nullptr)
{
}

g2d::clock::hertz::~hertz()
{
	this->destroy();
}

bool g2d::clock::hertz::initialize(std::size_t fps)
{
	this->_timer = new g2d::clock::timer();
	this->_frequency = new g2d::clock::frequency();

	if (!this->_frequency->initialize())
	{
		return false;
	}

	this->_timer->play();

	this->_fps = fps == 0 ? this->current() : fps;
	this->_latency = g2d::clock::SECOND / this->_fps;

	return true;
}

void g2d::clock::hertz::destroy()
{
	delete _timer;
	delete _frequency;

	this->_timer = nullptr;
	this->_frequency = nullptr;
}

void g2d::clock::hertz::synchronize()
{
	do
	{
		this->_timer->run();
	}
	while (this->_timer->elapsed() < this->_latency);

	this->_frequency->update();
	this->_timer->replay();
}

void g2d::clock::hertz::fps(std::size_t fps)
{
	this->_fps = fps;
	this->_latency = g2d::clock::SECOND / this->_fps;
}

std::size_t g2d::clock::hertz::fps() const
{
	return this->_fps;
}

std::size_t g2d::clock::hertz::latency() const
{
	return this->_latency;
}

std::size_t g2d::clock::hertz::frequency() const
{
	return this->_frequency->current();
}

std::size_t g2d::clock::hertz::current()
{
//	int num_sizes;
//	Rotation current_rotation;
	Display* dpy = XOpenDisplay(nullptr);
	Window root = RootWindow(dpy, 0);
//	XRRScreenSize* xrrs = XRRSizes(dpy, 0, &num_sizes);
//	GET CURRENT RESOLUTION AND FREQUENCY
	XRRScreenConfiguration* conf = XRRGetScreenInfo(dpy, root);
//	short current_rate = XRRConfigCurrentRate(conf);
//	SizeID current_size_id = XRRConfigCurrentConfiguration(conf, &current_rotation);
//	int current_width = xrrs[current_size_id].width;
//	int current_height = xrrs[current_size_id].height;

	XCloseDisplay(dpy);

	return (std::size_t)XRRConfigCurrentRate(conf);
}

