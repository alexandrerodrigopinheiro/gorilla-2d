#include "../../includes/event/keyboard.h"

g2d::event::keyboard::keyboard()
	: _pressed_button(g2d::event::button::button_invalid)
	, _released_button(g2d::event::button::button_invalid)
	, _pressed_key(g2d::event::key::key_none)
	, _released_key(g2d::event::key::key_none)
{
}

g2d::event::keyboard::~keyboard()
{
}

void g2d::event::keyboard::pressed_button(const g2d::event::button& pressed_button)
{
	this->_pressed_button = pressed_button;
}

void g2d::event::keyboard::released_button(const g2d::event::button& released_button)
{
	this->_released_button = released_button;
}

void g2d::event::keyboard::pressed_key(const g2d::event::key& pressed_key)
{
	this->_pressed_key = pressed_key;
}

void g2d::event::keyboard::released_key(const g2d::event::key& released_key)
{
	this->_released_key = released_key;
}

const g2d::event::button& g2d::event::keyboard::pressed_button() const
{
	return this->_pressed_button;
}

const g2d::event::button& g2d::event::keyboard::released_button() const
{
	return this->_released_button;
}

const g2d::event::key& g2d::event::keyboard::pressed_key() const
{
	return this->_pressed_key;
}

const g2d::event::key& g2d::event::keyboard::released_key() const
{
	return this->_released_key;
}

bool g2d::event::keyboard::pressed() const
{
	return this->_pressed_key == g2d::event::key::key_pressed;
}

bool g2d::event::keyboard::released() const
{
	return this->_released_key == g2d::event::key::key_released;
}

void g2d::event::keyboard::clear()
{
	this->_pressed_button = g2d::event::button::button_invalid;
	this->_released_button = g2d::event::button::button_invalid;
	this->_pressed_key = g2d::event::key::key_none;
	this->_released_key = g2d::event::key::key_none;
}
