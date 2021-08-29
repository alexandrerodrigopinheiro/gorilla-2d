#include "../../includes/event/touch.h"

g2d::event::touch::touch()
	: _finger(g2d::event::finger::finger_none)
	, _position(g2d::math::point2dd().null())
{
}

g2d::event::touch::~touch()
{
}

void g2d::event::touch::finger(const g2d::event::finger& finger)
{
	this->_finger = finger;
}

void g2d::event::touch::position(double position)
{
	this->_position.set(position);
}

void g2d::event::touch::position(const g2d::math::point2dd& position)
{
	this->_position = position;
}

void g2d::event::touch::position(double x, double y)
{
	this->_position.set(x, y);
}

void g2d::event::touch::position_x(double x)
{
	this->_position.x(x);
}

void g2d::event::touch::position_y(double y)
{
	this->_position.y(y);
}

bool g2d::event::touch::motioned() const
{
	return this->_finger == g2d::event::finger::finger_motion;
}

bool g2d::event::touch::pressed() const
{
	return this->_finger == g2d::event::finger::finger_pressed;
}

bool g2d::event::touch::released() const
{
	return this->_finger == g2d::event::finger::finger_released;
}

const g2d::math::point2dd& g2d::event::touch::position() const
{
	return this->_position;
}

const g2d::event::finger& g2d::event::touch::finger() const
{
	return this->_finger;
}

void g2d::event::touch::clear()
{
	this->_finger = g2d::event::finger::finger_none;
	this->_position = g2d::math::point2dd().null();
}
