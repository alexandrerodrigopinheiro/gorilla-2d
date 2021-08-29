#include "../../includes/gui/button.h"

g2d::gui::button::button()
	: _button(nullptr)
	, _state(g2d::gui::state::state_enabled)
	, _sensible(g2d::math::squared())
{
}

g2d::gui::button::~button()
{
	this->destroy();
}

bool g2d::gui::button::initialize(const std::string& filename, std::size_t colunm, std::size_t rows, std::size_t frames)
{
	if (!this->_button->initialize(filename, colunm, rows, frames))
	{
		std::cerr << "Can not load file '" << filename << "', failed." << std::endl;

		return false;
	}

	this->_sensible.set(0.0, 0.0, this->_button->size().w(), this->_button->size().h());

	return true;
}

void g2d::gui::button::destroy()
{
	this->_button->destroy();
}

void g2d::gui::button::draw()
{
	this->_button->draw();
}

void g2d::gui::button::state(const g2d::gui::state& state)
{
	this->_state = state;

	switch (this->_state)
	{
		case g2d::gui::state::state_enabled:
		{
			this->_button->index(static_cast<std::size_t>(g2d::gui::state::state_enabled));

			break;
		}
		case g2d::gui::state::state_hover:
		{
			this->_button->index(static_cast<std::size_t>(g2d::gui::state::state_hover));

			break;
		}
		case g2d::gui::state::state_pressed:
		{
			this->_button->index(static_cast<std::size_t>(g2d::gui::state::state_pressed));

			break;
		}
		case g2d::gui::state::state_released:
		{
			this->_button->index(static_cast<std::size_t>(g2d::gui::state::state_released));

			break;
		}
		case g2d::gui::state::state_disabled:
		{
			this->_button->index(static_cast<std::size_t>(g2d::gui::state::state_disabled));

			break;
		}
		default:
		{
			break;
		}
	}
}

void g2d::gui::button::sensible(const g2d::math::squared& sensible)
{
	this->_sensible = sensible;
}

void g2d::gui::button::sensible(double sensible)
{
	this->_sensible = sensible;
}

void g2d::gui::button::sensible(double x, double y, double w, double h)
{
	this->_sensible.set(x, y, w, h);
}

void g2d::gui::button::sensible_x(double x)
{
	this->_sensible.x(x);
}

void g2d::gui::button::sensible_y(double y)
{
	this->_sensible.y(y);
}

void g2d::gui::button::sensible_w(double w)
{
	this->_sensible.w(w);
}

void g2d::gui::button::sensible_h(double h)
{
	this->_sensible.h(h);
}

void g2d::gui::button::position(const g2d::math::point3dd& position)
{
	this->_button->position(position);
}

void g2d::gui::button::position(double position)
{
	this->_button->position(position);
}

void g2d::gui::button::position(double x, double y, double z)
{
	this->_button->position(x, y, z);
}

void g2d::gui::button::position_x(double x)
{
	this->_button->position_x(x);
}

void g2d::gui::button::position_y(double y)
{
	this->_button->position_y(y);
}

void g2d::gui::button::position_z(double z)
{
	this->_button->position_z(z);
}

const g2d::math::squared& g2d::gui::button::sensible() const
{
	return this->_sensible;
}

const g2d::math::point3dd& g2d::gui::button::position() const
{
	return this->_button->position();
}

const g2d::gui::state& g2d::gui::button::state() const
{
	return this->_state;
}

std::ostream& operator<<(std::ostream& stream, const g2d::gui::button& button)
{
	return stream << button.state();
}

std::istream& operator>>(std::istream& stream, g2d::gui::button& button)
{
	g2d::gui::state state;

	stream >> state;
	button.state(state);

	return stream;
}
