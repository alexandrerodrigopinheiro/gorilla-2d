#include "../../includes/gui/ruler.h"

g2d::gui::ruler::ruler()
	: _visible(true)
	, _opacity(100.0)
	, _size(g2d::math::size2dd())
{
}

g2d::gui::ruler::ruler(double width, double height)
	: _visible(true)
	, _opacity(100.0)
	, _size(g2d::math::size2dd())
{
	this->initialize(width, height);
}

g2d::gui::ruler::~ruler()
{
	this->destroy();
}

bool g2d::gui::ruler::initialize(double width, double height)
{
	this->_size.set(width, height);

	return true;
}

void g2d::gui::ruler::destroy()
{
}

void g2d::gui::ruler::draw()
{
	if (this->_visible && this->_opacity > 0)
	{
		glPushMatrix();

		glEnable(GL_BLEND);
		glColor4d(0.0, 0.0, 0.0, 0.05);

		glEnable(GL_LINE_STIPPLE);

		glColor4d(0.0, 0.0, 0.0, 0.1);
		glLineWidth(0.5);
		glBegin(GL_LINES);

		for (std::size_t i = 5; i < this->_size.h(); i += 5)
		{
			glVertex2d(0, i);
			glVertex2d(this->_size.w(), i);
		}

		for (std::size_t i = 5; i < this->_size.w(); i += 5)
		{
			glVertex2d(i, 0);
			glVertex2d(i, this->_size.h());
		}

		glEnd();

		glColor4d(0.0, 0.0, 0.0, 0.3);
		glLineWidth(1.0);
		glBegin(GL_LINES);

		for (std::size_t i = 10; i < this->_size.h(); i += 10)
		{
			if (i % 50 != 0 && i % 100 != 0)
			{
				glVertex2d(0, i);
				glVertex2d(this->_size.w(), i);
			}
		}

		for (std::size_t i = 10; i < this->_size.w(); i += 10)
		{
			if (i % 50 != 0 && i % 100 != 0)
			{
				glVertex2d(i, 0);
				glVertex2d(i, this->_size.h());
			}
		}

		glEnd();

		glColor4d(0.0, 0.0, 0.0, 0.6);
		glLineWidth(1.5);
		glBegin(GL_LINES);

		for (std::size_t i = 50; i < this->_size.h(); i += 50)
		{
			glVertex2d(0.0, i);
			glVertex2d(this->_size.w(), i);
		}

		for (std::size_t i = 50; i < this->_size.w(); i += 50)
		{
			glVertex2d(i, 0.0);
			glVertex2d(i, this->_size.h());
		}

		glEnd();

		glColor4d(0.0, 0.0, 0.0, 0.9);
		glLineWidth(2.0);
		glBegin(GL_LINES);

		for (std::size_t i = 100; i < this->_size.h(); i += 100)
		{
			glVertex2d(0.0, i);
			glVertex2d(this->_size.w(), i);
		}

		for (std::size_t i = 100; i < this->_size.w(); i += 100)
		{
			glVertex2d(i, 0);
			glVertex2d(i, this->_size.h());
		}

		glEnd();

		glDisable(GL_LINE_STIPPLE);

		glDisable(GL_BLEND);
		glPopMatrix();
	}
}
