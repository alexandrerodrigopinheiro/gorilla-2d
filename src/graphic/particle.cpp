#include "../../includes/graphic/particle.h"

g2d::graphic::particle::particle()
	: _play(false)
	, _visible(true)
	, _wireframe(false)
	, _verbose(false)
	, _time_to_live(0)
	, _gravity_radial_acceleration(0.0)
	, _gravity_tangential_acceleration(0.0)
	, _radius_angle(0.0)
	, _radius_degrees_per_second(0.0)
	, _radius_value(0.0)
	, _radius_delta_value(0.0)
	, _atlas_index(0)
	, _flip(g2d::graphic::flip::flip_none)
	, _gravity_direction(g2d::math::point3dd())
	, _color(g2d::math::color(255))
	, _delta_color(g2d::math::color(255))
	, _pivot(g2d::math::point2dd(0.5))
	, _position(g2d::math::point3dd(0.0))
	, _start_position(g2d::math::point3dd())
	, _rotate(g2d::math::rotated(0.0))
	, _delta_rotate(g2d::math::rotated())
	, _scale(g2d::math::size2dd(1.0))
	, _delta_size(g2d::math::size2dd())
	, _size(g2d::math::size2dd())
	, _offset(g2d::math::squared(0.0))
	, _vertex(g2d::math::vertexd(0.0))
	, _uvmap(g2d::math::uvmapd(1.0))
	, _animation(nullptr)
{
}

g2d::graphic::particle::~particle()
{
	this->destroy();
}

void g2d::graphic::particle::destroy()
{
	delete this->_animation;

	this->_animation = nullptr;
}

bool g2d::graphic::particle::initialize(const g2d::math::point3dd& position, const g2d::math::size2dd& size, bool verbose)
{
	this->_size = size;
	this->_position = position;
	this->_verbose = verbose;

	this->_offset.set(0.0, 0.0, 1.0, 1.0);
	this->_uvmap.set(1.0);

	this->mapping();

	return true;
}

bool g2d::graphic::particle::animation(const std::string& animation, std::size_t length, std::size_t fps)
{
	this->_animation = new g2d::animation::tweener();

	if (!this->_animation->initialize(animation, length, fps))
	{
		std::cerr << "Could not initialize the tweener: '" << animation << "', failed" << std::endl;

		return false;
	}

	return true;
}

void g2d::graphic::particle::draw(uint identity)
{
	if (this->_visible && this->_color.a() > 0 && this->_scale != 0)
	{
		this->mapping();

		glPushMatrix();

		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);

		this->bind(identity);

		glTranslated(this->_position.x(), this->_position.y(), this->_position.z());

		glRotated(this->_rotate.h(), 1.0f, 0.0f, 0.0f);
		glRotated(this->_rotate.p(), 0.0f, 1.0f, 0.0f);
		glRotated(this->_rotate.b(), 0.0f, 0.0f, 1.0f);

		glScaled(this->_scale.w(), this->_scale.h(), 1.0f);

		glColor4d(this->_color.normal_r(), this->_color.normal_g(), this->_color.normal_b(), this->_color.normal_a());

		glBegin(GL_QUADS);

		switch (this->_flip)
		{
			case g2d::graphic::flip::flip_none:
			{
				glTexCoord2d(this->_offset.x(), this->_offset.y()); glVertex3d(this->_vertex.a().x(), this->_vertex.a().y(), this->_vertex.a().z());
				glTexCoord2d(this->_offset.w(), this->_offset.y()); glVertex3d(this->_vertex.b().x(), this->_vertex.b().y(), this->_vertex.b().z());
				glTexCoord2d(this->_offset.w(), this->_offset.h()); glVertex3d(this->_vertex.c().x(), this->_vertex.c().y(), this->_vertex.c().z());
				glTexCoord2d(this->_offset.x(), this->_offset.h()); glVertex3d(this->_vertex.d().x(), this->_vertex.d().y(), this->_vertex.d().z());

				break;
			}
			case g2d::graphic::flip::flip_horizontal:
			{
				glTexCoord2d(this->_offset.x(), this->_offset.y()); glVertex3d(this->_vertex.b().x(), this->_vertex.b().y(), this->_vertex.b().z());
				glTexCoord2d(this->_offset.w(), this->_offset.y()); glVertex3d(this->_vertex.a().x(), this->_vertex.a().y(), this->_vertex.a().z());
				glTexCoord2d(this->_offset.w(), this->_offset.h()); glVertex3d(this->_vertex.d().x(), this->_vertex.d().y(), this->_vertex.d().z());
				glTexCoord2d(this->_offset.x(), this->_offset.h()); glVertex3d(this->_vertex.c().x(), this->_vertex.c().y(), this->_vertex.c().z());

				break;
			}
			case g2d::graphic::flip::flip_vertical:
			{
				glTexCoord2d(this->_offset.x(), this->_offset.y()); glVertex3d(this->_vertex.d().x(), this->_vertex.d().y(), this->_vertex.d().z());
				glTexCoord2d(this->_offset.w(), this->_offset.y()); glVertex3d(this->_vertex.c().x(), this->_vertex.c().y(), this->_vertex.c().z());
				glTexCoord2d(this->_offset.w(), this->_offset.h()); glVertex3d(this->_vertex.b().x(), this->_vertex.b().y(), this->_vertex.b().z());
				glTexCoord2d(this->_offset.x(), this->_offset.h()); glVertex3d(this->_vertex.a().x(), this->_vertex.a().y(), this->_vertex.a().z());

				break;
			}
			case g2d::graphic::flip::flip_all:
			{
				glTexCoord2d(this->_offset.x(), this->_offset.y()); glVertex3d(this->_vertex.c().x(), this->_vertex.c().y(), this->_vertex.c().z());
				glTexCoord2d(this->_offset.w(), this->_offset.y()); glVertex3d(this->_vertex.d().x(), this->_vertex.d().y(), this->_vertex.d().z());
				glTexCoord2d(this->_offset.w(), this->_offset.h()); glVertex3d(this->_vertex.a().x(), this->_vertex.a().y(), this->_vertex.a().z());
				glTexCoord2d(this->_offset.x(), this->_offset.h()); glVertex3d(this->_vertex.b().x(), this->_vertex.b().y(), this->_vertex.b().z());

				break;
			}
		}

		glEnd();

		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_COLOR_MATERIAL);

		if (this->_verbose)
		{
			glEnable(GL_LINE_STIPPLE);

			glTranslated(this->_position.x(), this->_position.y(), g2d::math::invert(this->_position.z()));

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

void g2d::graphic::particle::play()
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no animation, failed" << std::endl;

		return;
	}

	if (!this->_animation->has_tweener())
	{
		std::cerr << "There is no defined animation for this animation, failed" << std::endl;

		return;
	}

	if (!this->_play)
	{
		return;
	}

	if (this->_animation->has_visible())
	{
		this->visible(this->_animation->visible());
	}

	if (this->_animation->has_wireframe())
	{
		this->wireframe(this->_animation->wireframe());
	}

	if (this->_animation->has_flip())
	{
		this->flip(this->_animation->flip());
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

void g2d::graphic::particle::resume()
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no animation, failed" << std::endl;

		return;
	}

	if (!this->_animation->has_tweener())
	{
		std::cerr << "There is no defined animation for this animation, failed" << std::endl;

		return;
	}

	this->_animation->play();
	this->_play = true;
}

void g2d::graphic::particle::pause()
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no animation, failed" << std::endl;

		return;
	}

	if (!this->_animation->has_tweener())
	{
		std::cerr << "There is no defined animation for this animation, failed" << std::endl;

		return;
	}

	this->_animation->stop();
	this->_play = false;
}

void g2d::graphic::particle::replay()
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no animation, failed" << std::endl;

		return;
	}

	if (!this->_animation->has_tweener())
	{
		std::cerr << "There is no defined animation for this animation, failed" << std::endl;

		return;
	}

	this->_animation->replay();
	this->_play = true;
}

void g2d::graphic::particle::reset()
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no animation, failed" << std::endl;

		return;
	}

	if (!this->_animation->has_tweener())
	{
		std::cerr << "There is no defined animation for this animation, failed" << std::endl;

		return;
	}

	this->_animation->reset();
	this->_play = false;
}

bool g2d::graphic::particle::played() const
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no animation, failed" << std::endl;

		return false;
	}

	if (!this->_animation->has_tweener())
	{
		std::cerr << "There is no defined animation for this animation, failed" << std::endl;

		return false;
	}

	return this->_animation->played() && this->_play;
}

bool g2d::graphic::particle::onset() const
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no animation, failed" << std::endl;

		return false;
	}

	if (!this->_animation->has_tweener())
	{
		std::cerr << "There is no defined animation for this animation, failed" << std::endl;

		return false;
	}

	return this->_animation->onset();
}

bool g2d::graphic::particle::bound() const
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no animation, failed" << std::endl;

		return false;
	}

	if (!this->_animation->has_tweener())
	{
		std::cerr << "There is no defined animation for this animation, failed" << std::endl;

		return false;
	}

	return this->_animation->bound();
}

void g2d::graphic::particle::visible(bool visible)
{
	this->_visible = visible;
}

void g2d::graphic::particle::wireframe(bool wireframe)
{
	this->_wireframe = wireframe;
}

void g2d::graphic::particle::verbose(bool verbose)
{
	this->_verbose = verbose;
}

void g2d::graphic::particle::time_to_live(double time_to_live)
{
	this->_time_to_live = time_to_live;
}

void g2d::graphic::particle::gravity_radial_acceleration(double gravity_radial_acceleration)
{
	this->_gravity_radial_acceleration = gravity_radial_acceleration;
}

void g2d::graphic::particle::gravity_tangential_acceleration(double gravity_tangential_acceleration)
{
	this->_gravity_tangential_acceleration = gravity_tangential_acceleration;
}

void g2d::graphic::particle::radius_angle(double radius_angle)
{
	this->_radius_angle = radius_angle;
}

void g2d::graphic::particle::radius_degrees_per_second(double radius_degrees_per_second)
{
	this->_radius_degrees_per_second = radius_degrees_per_second;
}

void g2d::graphic::particle::radius_value(double radius_value)
{
	this->_radius_value = radius_value;
}

void g2d::graphic::particle::radius_delta_value(double radius_delta_value)
{
	this->_radius_delta_value = radius_delta_value;
}

void g2d::graphic::particle::atlas_index(std::size_t atlas_index)
{
	this->_atlas_index = atlas_index;
}

void g2d::graphic::particle::flip(const g2d::graphic::flip& flip)
{
	this->_flip = flip;
}

void g2d::graphic::particle::gravity_direction(const g2d::math::point3dd& gravity_direction)
{
	this->_gravity_direction = gravity_direction;
}

void g2d::graphic::particle::gravity_direction(double x, double y, double z)
{
	this->_gravity_direction.set(x, y, z);
}

void g2d::graphic::particle::gravity_direction(double gravity_direction)
{
	this->_gravity_direction = gravity_direction;
}

void g2d::graphic::particle::gravity_direction_x(double x)
{
	this->_gravity_direction.x(x);
}

void g2d::graphic::particle::gravity_direction_y(double y)
{
	this->_gravity_direction.y(y);
}

void g2d::graphic::particle::gravity_direction_z(double z)
{
	this->_gravity_direction.z(z);
}

void g2d::graphic::particle::color(const g2d::math::color& color)
{
	this->_color = color;
}

void g2d::graphic::particle::color(double r, double g, double b, double a)
{
	this->_color.set(r, g, b, a);
}

void g2d::graphic::particle::color(double color)
{
	this->_color = color;
}

void g2d::graphic::particle::color_r(double r)
{
	this->_color.r(r);
}

void g2d::graphic::particle::color_g(double g)
{
	this->_color.g(g);
}

void g2d::graphic::particle::color_b(double b)
{
	this->_color.b(b);
}

void g2d::graphic::particle::color_a(double a)
{
	this->_color.a(a);
}

void g2d::graphic::particle::delta_color(const g2d::math::color& delta_color)
{
	this->_delta_color = delta_color;
}

void g2d::graphic::particle::delta_color(double r, double g, double b, double a)
{
	this->_delta_color.set(r, g, b, a);
}

void g2d::graphic::particle::delta_color(double delta_color)
{
	this->_delta_color = delta_color;
}

void g2d::graphic::particle::delta_color_r(double r)
{
	this->_delta_color.r(r);
}

void g2d::graphic::particle::delta_color_g(double g)
{
	this->_delta_color.g(g);
}

void g2d::graphic::particle::delta_color_b(double b)
{
	this->_delta_color.b(b);
}

void g2d::graphic::particle::delta_color_a(double a)
{
	this->_delta_color.a(a);
}

void g2d::graphic::particle::pivot(const g2d::math::point2dd& pivot)
{
	this->_pivot = pivot;
}

void g2d::graphic::particle::pivot(double x, double y)
{
	this->_pivot.set(x, y);
}

void g2d::graphic::particle::pivot(double pivot)
{
	this->_pivot = pivot;
}

void g2d::graphic::particle::pivot_x(double x)
{
	this->_pivot.x(x);
}

void g2d::graphic::particle::pivot_y(double y)
{
	this->_pivot.y(y);
}

void g2d::graphic::particle::position(const g2d::math::point3dd& position)
{
	this->_position = position;
}

void g2d::graphic::particle::position(double x, double y, double z)
{
	this->_position.set(x, y, z);
}

void g2d::graphic::particle::position(double position)
{
	this->_position = position;
}

void g2d::graphic::particle::position_x(double x)
{
	this->_position.x(x);
}

void g2d::graphic::particle::position_y(double y)
{
	this->_position.y(y);
}

void g2d::graphic::particle::position_z(double z)
{
	this->_position.z(z);
}

void g2d::graphic::particle::start_position(const g2d::math::point3dd& start_position)
{
	this->_start_position = start_position;
}

void g2d::graphic::particle::start_position(double x, double y, double z)
{
	this->_start_position.set(x, y, z);
}

void g2d::graphic::particle::start_position(double position)
{
	this->_start_position = position;
}

void g2d::graphic::particle::start_position_x(double x)
{
	this->_start_position.x(x);
}

void g2d::graphic::particle::start_position_y(double y)
{
	this->_start_position.y(y);
}

void g2d::graphic::particle::start_position_z(double z)
{
	this->_start_position.z(z);
}

void g2d::graphic::particle::rotate(const g2d::math::rotated& rotate)
{
	this->_rotate = rotate;
}

void g2d::graphic::particle::rotate(double h, double p, double b)
{
	this->_rotate.set(h, p, b);
}

void g2d::graphic::particle::rotate(double rotate)
{
	this->_rotate = rotate;
}

void g2d::graphic::particle::rotate_h(double h)
{
	this->_rotate.h(h);
}

void g2d::graphic::particle::rotate_p(double p)
{
	this->_rotate.p(p);
}

void g2d::graphic::particle::rotate_b(double b)
{
	this->_rotate.b(b);
}

void g2d::graphic::particle::delta_rotate(const g2d::math::rotated& delta_rotate)
{
	this->_delta_rotate = delta_rotate;
}

void g2d::graphic::particle::delta_rotate(double h, double p, double b)
{
	this->_delta_rotate.set(h, p, b);
}

void g2d::graphic::particle::delta_rotate(double delta_rotate)
{
	this->_delta_rotate = delta_rotate;
}

void g2d::graphic::particle::delta_rotate_h(double h)
{
	this->_delta_rotate.h(h);
}

void g2d::graphic::particle::delta_rotate_p(double p)
{
	this->_delta_rotate.p(p);
}

void g2d::graphic::particle::delta_rotate_b(double b)
{
	this->_delta_rotate.b(b);
}

void g2d::graphic::particle::scale(const g2d::math::size2dd& scale)
{
	this->_scale = scale;
}

void g2d::graphic::particle::scale(double w, double h)
{
	this->_scale.set(w, h);
}

void g2d::graphic::particle::scale(double scale)
{
	this->_scale = scale;
}

void g2d::graphic::particle::scale_w(double w)
{
	this->_scale.w(w);
}

void g2d::graphic::particle::scale_h(double h)
{
	this->_scale.h(h);
}

void g2d::graphic::particle::delta_size(const g2d::math::size2dd& delta_size)
{
	this->_delta_size = delta_size;
}

void g2d::graphic::particle::delta_size(double w, double h)
{
	this->_delta_size.set(w, h);
}

void g2d::graphic::particle::delta_size(double delta_size)
{
	this->_delta_size = delta_size;
}

void g2d::graphic::particle::delta_size_w(double w)
{
	this->_delta_size.w(w);
}

void g2d::graphic::particle::delta_size_h(double h)
{
	this->_delta_size.h(h);
}

void g2d::graphic::particle::size(const g2d::math::size2dd& size)
{
	this->_size = size;
}

void g2d::graphic::particle::size(double w, double h)
{
	this->_size.set(w, h);
}

void g2d::graphic::particle::size(double size)
{
	this->_size = size;
}

void g2d::graphic::particle::size_w(double w)
{
	this->_size.w(w);
}

void g2d::graphic::particle::size_h(double h)
{
	this->_size.h(h);
}

void g2d::graphic::particle::append_time_to_live(double time_to_live)
{
	this->_time_to_live += time_to_live;
}

void g2d::graphic::particle::append_gravity_radial_acceleration(double gravity_radial_acceleration)
{
	this->_gravity_radial_acceleration += gravity_radial_acceleration;
}

void g2d::graphic::particle::append_gravity_tangential_acceleration(double gravity_tangential_acceleration)
{
	this->_gravity_tangential_acceleration += gravity_tangential_acceleration;
}

void g2d::graphic::particle::append_radius_angle(double radius_angle)
{
	this->_radius_angle += radius_angle;
}

void g2d::graphic::particle::append_radius_degrees_per_second(double radius_degrees_per_second)
{
	this->_radius_degrees_per_second += radius_degrees_per_second;
}

void g2d::graphic::particle::append_radius_value(double radius_value)
{
	this->_radius_value += radius_value;
}

void g2d::graphic::particle::append_radius_delta_value(double radius_delta_value)
{
	this->_radius_delta_value += radius_delta_value;
}

void g2d::graphic::particle::append_atlas_index(std::size_t atlas_index)
{
	this->_atlas_index += atlas_index;
}

void g2d::graphic::particle::append_gravity_direction(const g2d::math::point3dd& gravity_direction)
{
	this->_gravity_direction += gravity_direction;
}

void g2d::graphic::particle::append_gravity_direction(double x, double y, double z)
{
	this->_gravity_direction += g2d::math::point3dd(x, y, z);
}

void g2d::graphic::particle::append_gravity_direction(double gravity_direction)
{
	this->_gravity_direction += gravity_direction;
}

void g2d::graphic::particle::append_gravity_direction_x(double x)
{
	this->_gravity_direction.x(this->_gravity_direction.x() + x);
}

void g2d::graphic::particle::append_gravity_direction_y(double y)
{
	this->_gravity_direction.y(this->_gravity_direction.y() + y);
}

void g2d::graphic::particle::append_gravity_direction_z(double z)
{
	this->_gravity_direction.z(this->_gravity_direction.z() + z);
}

void g2d::graphic::particle::append_color(const g2d::math::color& color)
{
	this->_color += color;
}

void g2d::graphic::particle::append_color(double r, double g, double b, double a)
{
	this->_color += g2d::math::color(r, g, b, a);
}

void g2d::graphic::particle::append_color(double color)
{
	this->_color += color;
}

void g2d::graphic::particle::append_color_r(double r)
{
	this->_color.r(this->_color.r() + r);
}

void g2d::graphic::particle::append_color_g(double g)
{
	this->_color.g(this->_color.g() + g);
}

void g2d::graphic::particle::append_color_b(double b)
{
	this->_color.b(this->_color.b() + b);
}

void g2d::graphic::particle::append_color_a(double a)
{
	this->_color.a(this->_color.a() + a);
}

void g2d::graphic::particle::append_delta_color(const g2d::math::color& delta_color)
{
	this->_delta_color += delta_color;
}

void g2d::graphic::particle::append_delta_color(double r, double g, double b, double a)
{
	this->_delta_color += g2d::math::color(r, g, b, a);
}

void g2d::graphic::particle::append_delta_color(double delta_color)
{
	this->_delta_color += delta_color;
}

void g2d::graphic::particle::append_delta_color_r(double r)
{
	this->_delta_color.r(this->_delta_color.r() + r);
}

void g2d::graphic::particle::append_delta_color_g(double g)
{
	this->_delta_color.g(this->_delta_color.g() + g);
}

void g2d::graphic::particle::append_delta_color_b(double b)
{
	this->_delta_color.b(this->_delta_color.b() + b);
}

void g2d::graphic::particle::append_delta_color_a(double a)
{
	this->_delta_color.a(this->_delta_color.a() + a);
}

void g2d::graphic::particle::append_pivot(const g2d::math::point2dd& pivot)
{
	this->_pivot += pivot;
}

void g2d::graphic::particle::append_pivot(double x, double y)
{
	this->_pivot += g2d::math::point2dd(x, y);
}

void g2d::graphic::particle::append_pivot(double pivot)
{
	this->_pivot += pivot;
}

void g2d::graphic::particle::append_pivot_x(double x)
{
	this->_pivot.x(this->_pivot.x() + x);
}

void g2d::graphic::particle::append_pivot_y(double y)
{
	this->_pivot.y(this->_pivot.y() + y);
}

void g2d::graphic::particle::append_position(const g2d::math::point3dd& position)
{
	this->_position += position;
}

void g2d::graphic::particle::append_position(double x, double y, double z)
{
	this->_position += g2d::math::point3dd(x, y, z);
}

void g2d::graphic::particle::append_position(double position)
{
	this->_position += position;
}

void g2d::graphic::particle::append_position_x(double x)
{
	this->_position.x(this->_position.x() + x);
}

void g2d::graphic::particle::append_position_y(double y)
{
	this->_position.y(this->_position.y() + y);
}

void g2d::graphic::particle::append_position_z(double z)
{
	this->_position.z(this->_position.z() + z);
}

void g2d::graphic::particle::append_start_position(const g2d::math::point3dd& start_position)
{
	this->_start_position += start_position;
}

void g2d::graphic::particle::append_start_position(double x, double y, double z)
{
	this->_start_position += g2d::math::point3dd(x, y, z);
}

void g2d::graphic::particle::append_start_position(double start_position)
{
	this->_start_position += start_position;
}

void g2d::graphic::particle::append_start_position_x(double x)
{
	this->_start_position.x(this->_start_position.x() + x);
}

void g2d::graphic::particle::append_start_position_y(double y)
{
	this->_start_position.y(this->_start_position.y() + y);
}

void g2d::graphic::particle::append_start_position_z(double z)
{
	this->_start_position.z(this->_start_position.z() + z);
}

void g2d::graphic::particle::append_rotate(const g2d::math::rotated& rotate)
{
	this->_rotate += rotate;
}

void g2d::graphic::particle::append_rotate(double h, double p, double b)
{
	this->_rotate += g2d::math::rotated(h, p, b);
}

void g2d::graphic::particle::append_rotate(double rotate)
{
	this->_rotate += rotate;
}

void g2d::graphic::particle::append_rotate_h(double h)
{
	this->_rotate.h(this->_rotate.h() + h);
}

void g2d::graphic::particle::append_rotate_p(double p)
{
	this->_rotate.p(this->_rotate.p() + p);
}

void g2d::graphic::particle::append_rotate_b(double b)
{
	this->_rotate.b(this->_rotate.b() + b);
}

void g2d::graphic::particle::append_delta_rotate(const g2d::math::rotated& delta_rotate)
{
	this->_delta_rotate += delta_rotate;
}

void g2d::graphic::particle::append_delta_rotate(double h, double p, double b)
{
	this->_delta_rotate += g2d::math::rotated(h, p, b);
}

void g2d::graphic::particle::append_delta_rotate(double delta_rotate)
{
	this->_delta_rotate += delta_rotate;
}

void g2d::graphic::particle::append_delta_rotate_h(double h)
{
	this->_delta_rotate.h(this->_delta_rotate.h() + h);
}

void g2d::graphic::particle::append_delta_rotate_p(double p)
{
	this->_delta_rotate.p(this->_delta_rotate.p() + p);
}

void g2d::graphic::particle::append_delta_rotate_b(double b)
{
	this->_delta_rotate.b(this->_delta_rotate.b() + b);
}

void g2d::graphic::particle::append_scale(const g2d::math::size2dd& scale)
{
	this->_scale += scale;
}

void g2d::graphic::particle::append_scale(double w, double h)
{
	this->_scale += g2d::math::size2dd(w, h);
}

void g2d::graphic::particle::append_scale(double scale)
{
	this->_scale += scale;
}

void g2d::graphic::particle::append_scale_w(double w)
{
	this->_scale.w(this->_scale.w() + w);
}

void g2d::graphic::particle::append_scale_h(double h)
{
	this->_scale.h(this->_scale.h() + h);
}

void g2d::graphic::particle::append_delta_size(const g2d::math::size2dd& delta_size)
{
	this->_delta_size += delta_size;
}

void g2d::graphic::particle::append_delta_size(double w, double h)
{
	this->_size += g2d::math::size2dd(w, h);
}

void g2d::graphic::particle::append_delta_size(double delta_size)
{
	this->_delta_size += delta_size;
}

void g2d::graphic::particle::append_delta_size_w(double w)
{
	this->_delta_size.w(this->_delta_size.w() + w);
}

void g2d::graphic::particle::append_delta_size_h(double h)
{
	this->_delta_size.w(this->_delta_size.h() + h);
}

void g2d::graphic::particle::append_size(const g2d::math::size2dd& size)
{
	this->_size += size;
}

void g2d::graphic::particle::append_size(double w, double h)
{
	this->_size += g2d::math::size2dd(w, h);
}

void g2d::graphic::particle::append_size(double size)
{
	this->_size += size;
}

void g2d::graphic::particle::append_size_w(double w)
{
	this->_size.w(this->_size.w() + w);
}

void g2d::graphic::particle::append_size_h(double h)
{
	this->_size.h(this->_size.h() + h);
}

bool g2d::graphic::particle::visible() const
{
	return this->_visible;
}

bool g2d::graphic::particle::wireframe() const
{
	return this->_wireframe;
}

bool g2d::graphic::particle::verbose() const
{
	return this->_verbose;
}

double g2d::graphic::particle::time_to_live() const
{
	return this->_time_to_live;
}

double g2d::graphic::particle::gravity_radial_acceleration() const
{
	return this->_gravity_radial_acceleration;
}

double g2d::graphic::particle::gravity_tangential_acceleration() const
{
	return this->_gravity_tangential_acceleration;
}

double g2d::graphic::particle::radius_angle() const
{
	return this->_radius_angle;
}

double g2d::graphic::particle::radius_degrees_per_second() const
{
	return this->_radius_degrees_per_second;
}

double g2d::graphic::particle::radius_value() const
{
	return this->_radius_value;
}

double g2d::graphic::particle::radius_delta_value() const
{
	return this->_radius_delta_value;
}

const g2d::graphic::flip& g2d::graphic::particle::flip() const
{
	return this->_flip;
}

const g2d::math::point3dd& g2d::graphic::particle::gravity_direction() const
{
	return this->_gravity_direction;
}

const g2d::math::color& g2d::graphic::particle::color() const
{
	return this->_color;
}

const g2d::math::color& g2d::graphic::particle::delta_color() const
{
	return this->_delta_color;
}

const g2d::math::point2dd& g2d::graphic::particle::pivot() const
{
	return this->_pivot;
}

std::size_t g2d::graphic::particle::atlas_index() const
{
	return this->_atlas_index;
}

const g2d::math::point3dd& g2d::graphic::particle::position() const
{
	return this->_position;
}

const g2d::math::point3dd& g2d::graphic::particle::start_position() const
{
	return this->_start_position;
}

const g2d::math::rotated& g2d::graphic::particle::rotate() const
{
	return this->_rotate;
}

const g2d::math::rotated& g2d::graphic::particle::delta_rotate() const
{
	return this->_delta_rotate;
}

const g2d::math::size2dd& g2d::graphic::particle::scale() const
{
	return this->_scale;
}

const g2d::math::size2dd& g2d::graphic::particle::delta_size() const
{
	return this->_delta_size;
}

const g2d::math::size2dd& g2d::graphic::particle::size() const
{
	return this->_size;
}

g2d::animation::tweener* g2d::graphic::particle::animation() const
{
	return this->_animation;
}

void g2d::graphic::particle::bind(uint identity, const g2d::graphic::filter& filter, const g2d::graphic::wrap& wrap)
{
	GLenum error = glGetError();

	glBindTexture(GL_TEXTURE_2D, identity);

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error initializing OpenGL! " << gluErrorString(error) << std::endl;

		exit(EXIT_FAILURE);
	}

	switch (filter)
	{
		default:
		{
			break;
		}
		case g2d::graphic::filter::filter_nearest:
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			break;
		}
		case g2d::graphic::filter::filter_linear:
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			break;
		}
	}

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "Cannot filter identity: '" << gluErrorString(error) << "', failed" << std::endl;

		exit(EXIT_FAILURE);
	}

	switch (wrap)
	{
		default:
		{
			break;
		}
		case g2d::graphic::wrap::wrap_nearest:
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);

			break;
		}
		case g2d::graphic::wrap::wrap_clamp:
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			break;
		}
	}

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "Cannot wrap identity: '" << gluErrorString(error) << "', failed" << std::endl;

		return;
	}
}

void g2d::graphic::particle::mapping()
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
