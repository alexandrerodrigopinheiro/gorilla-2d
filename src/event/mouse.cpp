#include "../../includes/event/mouse.h"

g2d::event::mouse::mouse()
	: _cursor(g2d::event::cursor::cursor_none)
	, _position(g2d::math::point2dd().null())
{
}

g2d::event::mouse::~mouse()
{
}

void g2d::event::mouse::cursor(const g2d::event::cursor& cursor)
{
	this->_cursor = cursor;
}

void g2d::event::mouse::position(const g2d::math::point2dd& position)
{
	this->_position = position;
}

void g2d::event::mouse::position(double position)
{
	this->_position.set(position);
}

void g2d::event::mouse::position(double x, double y)
{
	this->_position.set(x, y);
}

void g2d::event::mouse::position_x(double x)
{
	this->_position.x(x);
}

void g2d::event::mouse::position_y(double y)
{
	this->_position.y(y);
}

bool g2d::event::mouse::motioned() const
{
	return this->_cursor == g2d::event::cursor::cursor_motion;
}

bool g2d::event::mouse::pressed() const
{
	return this->_cursor == g2d::event::cursor::cursor_pressed;
}

bool g2d::event::mouse::released() const
{
	return this->_cursor == g2d::event::cursor::cursor_released;
}

const g2d::math::point2dd& g2d::event::mouse::position() const
{
	return this->_position;
}

const g2d::event::cursor& g2d::event::mouse::cursor() const
{
	return this->_cursor;
}

void g2d::event::mouse::clear()
{
	this->_cursor   = g2d::event::cursor::cursor_none;
	this->_position = g2d::math::point2dd().null();
}
