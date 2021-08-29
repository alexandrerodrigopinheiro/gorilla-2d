#include "../../includes/core/camera.h"

g2d::core::camera::camera()
	: _name(std::string())
	, _color(g2d::math::color())
	, _position(g2d::math::point2dd())
	, _size(g2d::math::size2dd())
	, _rotate(g2d::math::rotated())
{
}

g2d::core::camera::~camera()
{
}

bool g2d::core::camera::initialize(const std::string& name, double x, double y, double width, double height)
{
	this->_name = name;
	this->_position.set(x, y);
	this->_size.set(width, height);

	return true;
}

void g2d::core::camera::render()
{
	glPushMatrix();

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glTranslated(this->_position.x(), this->_position.y(), 0.0);

	glRotated(this->_rotate.h(), 1.0, 0.0, 0.0);
	glRotated(this->_rotate.p(), 0.0, 1.0, 0.0);
	glRotated(this->_rotate.b(), 0.0, 0.0, 1.0);

	glScaled(this->_scale.w(), this->_scale.h(), 1.0);

	glColor4d(this->_color.normal_r(), this->_color.normal_g(), this->_color.normal_b(), this->_color.normal_a());

	glViewport(this->_position.x(), this->_position.y(), this->_size.w(), this->_size.h());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(this->_position.x(), this->_size.w(), this->_size.h(), this->_position.y(), g2d::math::invert(this->_size.w()), this->_size.w());
//	glFrustum(this->_position.x() / 2, this->_size.w() / 2, this->_size.h() / 2, this->_position.y() / 2, this->_size.w(), this->_size.w() * 2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);

	glPopMatrix();
}

void g2d::core::camera::name(const std::string& name)
{
	this->_name = name;
}

void g2d::core::camera::color(const g2d::math::color& color)
{
	this->_color = color;
}

void g2d::core::camera::color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	this->_color.set(r, g, b, a);
}

void g2d::core::camera::color_r(double r)
{
	this->_color.r(r);
}

void g2d::core::camera::color_g(double g)
{
	this->_color.g(g);
}

void g2d::core::camera::color_b(double b)
{
	this->_color.b(b);
}

void g2d::core::camera::position(double position)
{
	this->_position = position;
}

void g2d::core::camera::position(const g2d::math::point2dd& position)
{
	this->_position = position;
}

void g2d::core::camera::position(int x, int y)
{
	this->_position.set(x, y);
}

void g2d::core::camera::position_x(int x)
{
	this->_position.x(x);
}

void g2d::core::camera::position_y(int y)
{
	this->_position.y(y);
}

void g2d::core::camera::size(const g2d::math::size2dd& size)
{
	this->_size = size;
}

void g2d::core::camera::size(double w, double h)
{
	this->_size.set(w, h);
}

void g2d::core::camera::size_w(double w)
{
	this->_size.w(w);
}

void g2d::core::camera::size_h(double h)
{
	this->_size.h(h);
}

void g2d::core::camera::scale(const g2d::math::size2dd& scale)
{
	this->_scale = scale;
}

void g2d::core::camera::scale(double w, double h)
{
	this->_scale.set(w, h);
}

void g2d::core::camera::scale_w(double w)
{
	this->_scale.w(w);
}

void g2d::core::camera::scale_h(double h)
{
	this->_scale.h(h);
}

const std::string& g2d::core::camera::name() const
{
	return this->_name;
}

const g2d::math::color& g2d::core::camera::color() const
{
	return this->_color;
}

const g2d::math::point2dd& g2d::core::camera::position() const
{
	return this->_position;
}

const g2d::math::size2dd& g2d::core::camera::size() const
{
	return this->_size;
}

const g2d::math::size2dd& g2d::core::camera::scale() const
{
	return this->_scale;
}

const g2d::math::rotated& g2d::core::camera::rotate() const
{
	return this->_rotate;
}
