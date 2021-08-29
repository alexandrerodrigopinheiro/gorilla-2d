#include "../../includes/core/charger.h"

#define CHARGARBAR_SIZE	290

g2d::core::charger::charger()
	: _bump(0.0)
	, _background(nullptr)
	, _bar(nullptr)
	, _field(nullptr)
{
}

g2d::core::charger::~charger()
{
	this->destroy();
}

bool g2d::core::charger::initialize()
{
	this->_background = new g2d::graphic::sprite();
	this->_bar = new g2d::graphic::sprite();
	this->_field = new g2d::graphic::sprite();

	if (!this->_background->initialize("./assets/charger/background.png", 1, 1, 1))
	{
		return false;
	}

	if (!this->_bar->initialize("./assets/charger/bar.png", 1, 1, 1))
	{
		return false;
	}

	if (!this->_field->initialize("./assets/charger/field.png", 1, 1, 1))
	{
		return false;
	}

	this->_field->position(271.0, 462.0, 0.0);
	this->_bar->position(-497.0, 477.0, 0.0);

	return true;
}

void g2d::core::charger::destroy()
{
	delete this->_background;
	delete this->_bar;
	delete this->_field;

	this->_background = nullptr;
	this->_bar = nullptr;
	this->_field = nullptr;
}

void g2d::core::charger::size(std::size_t size)
{
	this->_bump = CHARGARBAR_SIZE / size;
}

void g2d::core::charger::update()
{
	if (this->_bar->position().x() < static_cast<double>(CHARGARBAR_SIZE))
	{
		this->_bar->append_position_x(this->_bump);
	}
}

void g2d::core::charger::render()
{
	this->_field->draw();
	this->_bar->draw();
	this->_background->draw();
}

bool g2d::core::charger::open()
{
	return this->_bar->position().x() < static_cast<double>(CHARGARBAR_SIZE);
}
