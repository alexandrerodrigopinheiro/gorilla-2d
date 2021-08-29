#include "../../includes/gui/hud.h"

g2d::gui::hud::hud()
	: _shape(nullptr)
	, _text(nullptr)
	, _verbose(true)
	, _visible(true)
	, _color(255)
	, _position(g2d::math::point3dd())
	, _rotate(g2d::math::rotated())
	, _scale(g2d::math::size2dd(1))
	, _size(g2d::math::size2dd())
{
}

g2d::gui::hud::~hud()
{
	this->destroy();
}

bool g2d::gui::hud::initialize(const std::string& filename, std::size_t measure, double width, double height, bool verbose)
{
	this->_verbose = verbose;

	this->_shape = new g2d::graphic::shape();

	if (!this->_shape->initialize(width, height, 4, g2d::graphic::form::form_square, this->_verbose))
	{
		return false;
	}

	this->_shape->color(0, 0, 0, 178);

	this->_text = new g2d::graphic::text();

	if (!this->_text->initialize(filename, measure, this->_verbose))
	{
		return false;
	}

	this->_text->pivot(0.5);
	this->_text->position(this->_shape->size().w() / 2.0, (this->_shape->size().h() / 2.0), 0.0);
	this->_text->color(255);

	this->_size.set(width, height);

	return true;
}

void g2d::gui::hud::destroy()
{
	delete this->_shape;
	delete this->_text;

	this->_shape  = nullptr;
	this->_text = nullptr;
}

void g2d::gui::hud::draw()
{
	if (this->_visible && this->_color.a() > 0 && this->_scale != 0)
	{
		glPushMatrix();

		glEnable(GL_BLEND);

		glTranslated(this->_position.x(), this->_position.y(), this->_position.z());

		glRotated(this->_rotate.h(), 1.0, 0.0, 0.0);
		glRotated(this->_rotate.p(), 0.0, 1.0, 0.0);
		glRotated(this->_rotate.b(), 0.0, 0.0, 1.0);

		glScaled(this->_scale.w(), this->_scale.h(), 1.0);

		glColor4d(this->_color.normal_r(), this->_color.normal_g(), this->_color.normal_b(), this->_color.normal_a());

		this->_shape->draw();
		this->_text->draw();

		glDisable(GL_BLEND);

		glPopMatrix();
	}
}

void g2d::gui::hud::verbose(bool verbose)
{
	this->_verbose = verbose;
}

void g2d::gui::hud::visible(bool visible)
{
	this->_visible = visible;
}

void g2d::gui::hud::content(const std::string& content)
{
	this->_text->content(content);
}

void g2d::gui::hud::color(const g2d::math::color& color)
{
	this->_color = color;
}

void g2d::gui::hud::color(double r, double g, double b, double a)
{
	this->_color.set(r, g, b, a);
}

void g2d::gui::hud::color_r(double r)
{
	this->_color.r(r);
}

void g2d::gui::hud::color_g(double g)
{
	this->_color.g(g);
}

void g2d::gui::hud::color_b(double b)
{
	this->_color.b(b);
}

void g2d::gui::hud::color_a(double a)
{
	this->_color.a(a);
}

void g2d::gui::hud::position(const g2d::math::point3dd& position)
{
	this->_position = position;
}

void g2d::gui::hud::position(double x, double y, double z)
{
	this->_position.set(x, y, z);
}

void g2d::gui::hud::position_x(double x)
{
	this->_position.x(x);
}

void g2d::gui::hud::position_y(double y)
{
	this->_position.y(y);
}

void g2d::gui::hud::rotate(const g2d::math::rotated& rotate)
{
	this->_rotate = rotate;
}

void g2d::gui::hud::rotate(double h, double p, double b)
{
	this->_rotate.set(h, p, b);
}

void g2d::gui::hud::rotate_h(double h)
{
	this->_rotate.h(h);
}

void g2d::gui::hud::rotate_p(double p)
{
	this->_rotate.p(p);
}

void g2d::gui::hud::rotate_b(double b)
{
	this->_rotate.b(b);
}

void g2d::gui::hud::scale(const g2d::math::size2dd& scale)
{
	this->_scale = scale;
}

void g2d::gui::hud::scale(double w, double h)
{
	this->_scale.set(w, h);
}

void g2d::gui::hud::scale_w(double w)
{
	this->_scale.w(w);
}

void g2d::gui::hud::scale_h(double h)
{
	this->_scale.h(h);
}

const std::string& g2d::gui::hud::content() const
{
	return this->_text->content();
}

bool g2d::gui::hud::verbose() const
{
	return this->_verbose;
}

bool g2d::gui::hud::visible() const
{
	return this->_visible;
}

const g2d::math::color& g2d::gui::hud::color() const
{
	return this->_color;
}

const g2d::math::point3dd& g2d::gui::hud::position() const
{
	return this->_position;
}

const g2d::math::rotated& g2d::gui::hud::rotate() const
{
	return this->_rotate;
}

const g2d::math::size2dd& g2d::gui::hud::scale() const
{
	return this->_scale;
}

const g2d::math::size2dd& g2d::gui::hud::size() const
{
	return this->_size;
}
