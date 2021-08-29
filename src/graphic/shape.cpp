#include "../../includes/graphic/shape.h"

g2d::graphic::shape::shape()
	: _run(false)
	, _visible(true)
	, _wireframe(false)
	, _verbose(false)
	, _dots(4)
	, _form(g2d::graphic::form::form_square)
	, _color(g2d::math::color(255))
	, _pivot(g2d::math::point2dd(0.0))
	, _position(g2d::math::point3dd(0.0))
	, _rotate(g2d::math::rotated(0.0))
	, _size(g2d::math::size2dd(0.0))
	, _scale(g2d::math::size2dd(1.0))
	, _animations(std::map<std::string, g2d::animation::tweener*>())
	, _animation(nullptr)
	, _offset(g2d::math::squared(0.0))
	, _vertex(g2d::math::vertexd(0.0))
	, _uvmap(g2d::math::uvmapd(1.0))
{
}

g2d::graphic::shape::~shape()
{
	this->destroy();
}

bool g2d::graphic::shape::initialize(double width, double height, std::size_t dots, const g2d::graphic::form& form, bool verbose)
{
	this->_size.set(width, height);
	this->_dots = dots;
	this->_form = form;
	this->_verbose = verbose;

	this->_offset.x(0.0);
	this->_offset.y(0.0);
	this->_offset.w(this->_uvmap.u() + this->_offset.x());
	this->_offset.h(this->_uvmap.v() + this->_offset.y());

	return true;
}

bool g2d::graphic::shape::animation(const std::string& animation, std::size_t length, std::size_t fps)
{
	auto it = this->_animations.find(animation);

	if (it != this->_animations.end())
	{
		std::cerr << "Cannot reuse same identity: '" << animation << "', failed" << std::endl;

		return false;
	}

	this->_animations.insert(std::pair<std::string, g2d::animation::tweener*>(animation, new g2d::animation::tweener()));

	if (!this->_animations[animation]->initialize(animation, length, fps))
	{
		std::cerr << "Could not initialize the tweener: '" << animation << "', failed" << std::endl;

		return false;
	}

	if (this->_animation == nullptr)
	{
		this->_animation = this->_animations[animation];
	}

	return true;
}

void g2d::graphic::shape::destroy()
{
	for (auto& arg : this->_animations)
	{
		delete arg.second;
	}

	this->_animations.clear();
}

void g2d::graphic::shape::draw()
{
	if (this->_visible && this->_color.a() > 0 && this->_scale != 0)
	{
		this->mapping();

		glPushMatrix();

		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_BLEND);

		glTranslated(this->_position.x(), this->_position.y(), this->_position.z());

		glRotated(this->_rotate.h(), 1.0f, 0.0f, 0.0f);
		glRotated(this->_rotate.p(), 0.0f, 1.0f, 0.0f);
		glRotated(this->_rotate.b(), 0.0f, 0.0f, 1.0f);

		glScaled(this->_scale.w(), this->_scale.h(), 1.0f);

		glColor4d(this->_color.normal_r(), this->_color.normal_g(), this->_color.normal_b(), this->_color.normal_a());

		// draws shape geometry.
		switch (this->_form)
		{
			case g2d::graphic::form::form_square:
			{
				glBegin(GL_QUADS);

				glVertex3d(this->_vertex.a().x(), this->_vertex.a().y(), this->_vertex.a().z());
				glVertex3d(this->_vertex.b().x(), this->_vertex.b().y(), this->_vertex.b().z());
				glVertex3d(this->_vertex.c().x(), this->_vertex.c().y(), this->_vertex.c().z());
				glVertex3d(this->_vertex.d().x(), this->_vertex.d().y(), this->_vertex.d().z());

				glEnd();

				break;
			}
			case g2d::graphic::form::form_circle:
			{
				double radius = (this->_size.w() * this->_size.h()) / 2.0;
				double step = 360.0 / (2.0 * M_PI * radius);

				glBegin(GL_TRIANGLE_FAN);

				glVertex3d(0.0, 0.0, 0.0);

				for (double i = 0; i < 360.0; i += step)
				{
					glVertex3d((std::cos(g2d::math::RADIANS_TO_DEGREES * i) * radius), (std::sin(g2d::math::RADIANS_TO_DEGREES * i) * radius), 0.0);
				}

				glEnd();

				break;
			}
		}

		glDisable(GL_BLEND);
		glDisable(GL_COLOR_MATERIAL);

		if (this->_verbose)
		{
			glEnable(GL_LINE_STIPPLE);

			glTranslated(this->_position.x(), this->_position.y(), this->_position.z());

			glRotated(this->_rotate.h(), 1.0f, 0.0f, 0.0f);
			glRotated(this->_rotate.p(), 0.0f, 1.0f, 0.0f);
			glRotated(this->_rotate.b(), 0.0f, 0.0f, 1.0f);

			glScaled(this->_scale.w(), this->_scale.h(), 1.0f);

			glColor4d(0.0f, 1.0f, 0.0f, 1.0f);

			glLineWidth(2.0f);
			glBegin(GL_LINE_LOOP);
			glVertex3d(this->_vertex.a().x(), this->_vertex.a().y(), this->_vertex.a().z());
			glVertex3d(this->_vertex.b().x(), this->_vertex.b().y(), this->_vertex.b().z());
			glVertex3d(this->_vertex.c().x(), this->_vertex.c().y(), this->_vertex.c().z());
			glVertex3d(this->_vertex.d().x(), this->_vertex.d().y(), this->_vertex.d().z());
			glEnd();

			glColor4d(0.0f, 0.0f, 1.0f, 1.0f);
			glLineWidth(2.0f);
			glBegin(GL_LINES);
			glVertex3d(-10.0f, 0.0f, 0.0f);
			glVertex3d( 10.0f, 0.0f, 0.0f);
			glEnd();

			glColor4d(1.0f, 0.0f, 0.0f, 1.0f);
			glLineWidth(2.0f);
			glBegin(GL_LINES);
			glVertex3d(0.0f, -10.0f, 0.0f);
			glVertex3d(0.0f,  10.0f, 0.0f);
			glEnd();

			glDisable(GL_LINE_STIPPLE);
		}

		glPopMatrix();
	}
}

void g2d::graphic::shape::run()
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no animation, failed" << std::endl;

		return;
	}

	if (!this->_animation->has_tweener())
	{
		std::cerr << "There is no defined animation for this animation: '" << this->_animation << "', failed" << std::endl;

		return;
	}

	if (!this->_run)
	{
		return;
	}

	if (this->_animation->has_dots())
	{
		this->dots(this->_animation->dots());
	}

	if (this->_animation->has_visible())
	{
		this->visible(this->_animation->visible());
	}

	if (this->_animation->has_wireframe())
	{
		this->wireframe(this->_animation->wireframe());
	}

	if (this->_animation->has_form())
	{
		this->form(this->_animation->form());
	}

	if (this->_animation->has_color())
	{
		this->color(this->_animation->color());
	}

	if (this->_animation->has_pivot())
	{
		this->pivot(this->_animation->pivot());
	}

	if (this->_animation->has_position())
	{
		this->position(this->_animation->position());
	}

	if (this->_animation->has_scale())
	{
		this->scale(this->_animation->scale());
	}

	if (this->_animation->has_rotate())
	{
		this->rotate(this->_animation->rotate());
	}

	this->_animation->run();
}

void g2d::graphic::shape::play()
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no animation, failed" << std::endl;

		return;
	}

	if (!this->_animation->has_tweener())
	{
		std::cerr << "There is no defined animation for this animation: '" << this->_animation << "', failed" << std::endl;

		return;
	}

	this->_animation->play();
	this->_run = true;
}

void g2d::graphic::shape::pause()
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no animation, failed" << std::endl;

		return;
	}

	if (!this->_animation->has_tweener())
	{
		std::cerr << "There is no defined animation for this animation: '" << this->_animation << "', failed" << std::endl;

		return;
	}

	this->_animation->stop();
	this->_run = false;
}

void g2d::graphic::shape::replay()
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no animation, failed" << std::endl;

		return;
	}

	if (!this->_animation->has_tweener())
	{
		std::cerr << "There is no defined animation for this animation: '" << this->_animation << "', failed" << std::endl;

		return;
	}

	this->_animation->replay();
	this->_run = true;
}

void g2d::graphic::shape::reset()
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no animation, failed" << std::endl;

		return;
	}

	if (!this->_animation->has_tweener())
	{
		std::cerr << "There is no defined animation for this animation: '" << this->_animation << "', failed" << std::endl;

		return;
	}

	this->_animation->reset();
	this->_run = false;
}

bool g2d::graphic::shape::played() const
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no animation, failed" << std::endl;

		return false;
	}

	if (!this->_animation->has_tweener())
	{
		std::cerr << "There is no defined animation for this animation: '" << this->_animation << "', failed" << std::endl;

		return false;
	}

	return this->_animation->played() && this->_run;
}

bool g2d::graphic::shape::onset() const
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no animation, failed" << std::endl;

		return false;
	}

	if (!this->_animation->has_tweener())
	{
		std::cerr << "There is no defined animation for this animation: '" << this->_animation << "', failed" << std::endl;

		return false;
	}

	return this->_animation->onset();
}

bool g2d::graphic::shape::bound() const
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no animation, failed" << std::endl;

		return false;
	}

	if (!this->_animation->has_tweener())
	{
		std::cerr << "There is no defined animation for this animation: '" << this->_animation << "', failed" << std::endl;

		return false;
	}

	return this->_animation->bound();
}

void g2d::graphic::shape::visible(bool visible)
{
	this->_visible = visible;
}

void g2d::graphic::shape::wireframe(bool wireframe)
{
	this->_wireframe = wireframe;
}

void g2d::graphic::shape::verbose(bool verbose)
{
	this->_verbose = verbose;
}

void g2d::graphic::shape::dots(std::size_t dots)
{
	this->_dots = dots;
}

void g2d::graphic::shape::form(const g2d::graphic::form& form)
{
	this->_form = form;
}

void g2d::graphic::shape::color(const g2d::math::color& color)
{
	this->_color = color;
}

void g2d::graphic::shape::color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	this->_color.set(r, g, b, a);
}

void g2d::graphic::shape::color(std::uint8_t color)
{
	this->_color = color;
}

void g2d::graphic::shape::color_r(std::uint8_t r)
{
	this->_color.r(r);
}

void g2d::graphic::shape::color_g(std::uint8_t g)
{
	this->_color.g(g);
}

void g2d::graphic::shape::color_b(std::uint8_t b)
{
	this->_color.b(b);
}

void g2d::graphic::shape::color_a(std::uint8_t a)
{
	this->_color.a(a);
}

void g2d::graphic::shape::pivot(const g2d::math::point2dd& pivot)
{
	this->_pivot = pivot;
}

void g2d::graphic::shape::pivot(double x, double y)
{
	this->_pivot.set(x, y);
}

void g2d::graphic::shape::pivot(double pivot)
{
	this->_pivot = pivot;
}

void g2d::graphic::shape::pivot_x(double x)
{
	this->_pivot.x(x);
}

void g2d::graphic::shape::pivot_y(double y)
{
	this->_pivot.y(y);
}

void g2d::graphic::shape::position(const g2d::math::point3dd& position)
{
	this->_position = position;
}

void g2d::graphic::shape::position(double x, double y, double z)
{
	this->_position = g2d::math::point3dd(x, y, z);
}

void g2d::graphic::shape::position(double position)
{
	this->_position = position;
}

void g2d::graphic::shape::position_x(double x)
{
	this->_position.x(x);
}

void g2d::graphic::shape::position_y(double y)
{
	this->_position.y(y);
}

void g2d::graphic::shape::position_z(double z)
{
	this->_position.z(z);
}

void g2d::graphic::shape::rotate(const g2d::math::rotated& rotate)
{
	this->_rotate = rotate;
}

void g2d::graphic::shape::rotate(double h, double p, double b)
{
	this->_rotate.set(h, p, b);
}

void g2d::graphic::shape::rotate(double rotate)
{
	this->_rotate = rotate;
}

void g2d::graphic::shape::rotate_h(double h)
{
	this->_rotate.h(h);
}

void g2d::graphic::shape::rotate_p(double p)
{
	this->_rotate.p(p);
}

void g2d::graphic::shape::rotate_b(double b)
{
	this->_rotate.b(b);
}

void g2d::graphic::shape::scale(const g2d::math::size2dd& scale)
{
	this->_scale = scale;
}

void g2d::graphic::shape::scale(double w, double h)
{
	this->_scale.set(w, h);
}

void g2d::graphic::shape::scale(double scale)
{
	this->_scale = scale;
}

void g2d::graphic::shape::scale_w(double w)
{
	this->_scale.w(w);
}

void g2d::graphic::shape::scale_h(double h)
{
	this->_scale.h(h);
}

void g2d::graphic::shape::animation(const std::string& animation)
{
	auto it = this->_animations.find(animation);

	if (it == this->_animations.end())
	{
		std::cerr << "Cannot find animation: '" << animation << "', failed" << std::endl;

		exit(EXIT_FAILURE);
	}

	this->_animation = this->_animations[animation];
}

void g2d::graphic::shape::append_dots(std::size_t dots)
{
	this->_dots += dots;
}

void g2d::graphic::shape::append_color(const g2d::math::color& color)
{
	this->_color += color;
}

void g2d::graphic::shape::append_color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	this->_color += g2d::math::color(r, g, b, a);
}

void g2d::graphic::shape::append_color(std::uint8_t color)
{
	this->_color += color;
}

void g2d::graphic::shape::append_color_r(std::uint8_t r)
{
	this->_color.r(this->_color.r() + r);
}

void g2d::graphic::shape::append_color_g(std::uint8_t g)
{
	this->_color.g(this->_color.g() + g);
}

void g2d::graphic::shape::append_color_b(std::uint8_t b)
{
	this->_color.b(this->_color.b() + b);
}

void g2d::graphic::shape::append_color_a(std::uint8_t a)
{
	this->_color.a(this->_color.a() + a);
}

void g2d::graphic::shape::append_pivot(const g2d::math::point2dd& pivot)
{
	this->_pivot += pivot;
}

void g2d::graphic::shape::append_pivot(double x, double y)
{
	this->_pivot += g2d::math::point2dd(x, y);
}

void g2d::graphic::shape::append_pivot(double pivot)
{
	this->_pivot += pivot;
}

void g2d::graphic::shape::append_pivot_x(double x)
{
	this->_pivot.x(this->_pivot.x() + x);
}

void g2d::graphic::shape::append_pivot_y(double y)
{
	this->_pivot.y(this->_pivot.y() + y);
}

void g2d::graphic::shape::append_position(const g2d::math::point3dd& position)
{
	this->_position += position;
}

void g2d::graphic::shape::append_position(double x, double y, double z)
{
	this->_position += g2d::math::point3dd(x, y, z);
}

void g2d::graphic::shape::append_position(double position)
{
	this->_position += position;
}

void g2d::graphic::shape::append_position_x(double x)
{
	this->_position.x(this->_position.x() + x);
}

void g2d::graphic::shape::append_position_y(double y)
{
	this->_position.y(this->_position.y() + y);
}

void g2d::graphic::shape::append_position_z(double z)
{
	this->_position.z(this->_position.z() + z);
}

void g2d::graphic::shape::append_rotate(const g2d::math::rotated& rotate)
{
	this->_rotate += rotate;
}

void g2d::graphic::shape::append_rotate(double h, double p, double b)
{
	this->_rotate += g2d::math::rotated(h, p, b);
}

void g2d::graphic::shape::append_rotate(double rotate)
{
	this->_rotate += rotate;
}

void g2d::graphic::shape::append_rotate_h(double h)
{
	this->_rotate.h(this->_rotate.h() + h);
}

void g2d::graphic::shape::append_rotate_p(double p)
{
	this->_rotate.p(this->_rotate.p() + p);
}

void g2d::graphic::shape::append_rotate_b(double b)
{
	this->_rotate.b(this->_rotate.b() + b);
}

void g2d::graphic::shape::append_scale(const g2d::math::size2dd& scale)
{
	this->_scale += scale;
}

void g2d::graphic::shape::append_scale(double w, double h)
{
	this->_scale += g2d::math::size2dd(w, h);
}

void g2d::graphic::shape::append_scale(double scale)
{
	this->_scale += scale;
}

void g2d::graphic::shape::append_scale_w(double w)
{
	this->_scale.w(this->_scale.w() + w);
}

void g2d::graphic::shape::append_scale_h(double h)
{
	this->_scale.h(this->_scale.h() + h);
}

bool g2d::graphic::shape::visible() const
{
	return this->_visible;
}

bool g2d::graphic::shape::wireframe() const
{
	return this->_wireframe;
}

bool g2d::graphic::shape::verbose() const
{
	return this->_verbose;
}

std::size_t g2d::graphic::shape::dots() const
{
	return this->_dots;
}

const g2d::graphic::form& g2d::graphic::shape::form() const
{
	return this->_form;
}

const g2d::math::color& g2d::graphic::shape::color() const
{
	return this->_color;
}

const g2d::math::point2dd& g2d::graphic::shape::pivot() const
{
	return this->_pivot;
}

const g2d::math::point3dd& g2d::graphic::shape::position() const
{
	return this->_position;
}

const g2d::math::rotated& g2d::graphic::shape::rotate() const
{
	return this->_rotate;
}

const g2d::math::size2dd& g2d::graphic::shape::size() const
{
	return this->_size;
}

const g2d::math::size2dd& g2d::graphic::shape::scale() const
{
	return this->_scale;
}

g2d::animation::tweener* g2d::graphic::shape::animation() const
{

	return this->_animation;
}

void g2d::graphic::shape::mapping()
{
	double x = g2d::math::invert(this->_size.w() * this->_pivot.x());
	double y = g2d::math::invert(this->_size.h() * this->_pivot.y());
	double w = x + this->_size.w();
	double h = y + this->_size.h();

	this->_vertex.a(x, y, 0.0);
	this->_vertex.b(w, y, 0.0);
	this->_vertex.c(w, h, 0.0);
	this->_vertex.d(x, h, 0.0);
}
