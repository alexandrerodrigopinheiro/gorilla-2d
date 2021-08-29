#include "../../includes/graphic/text.h"

g2d::graphic::text::text()
	: _body(nullptr)
	, _stroke(nullptr)
	, _shadow(nullptr)
	, _run(false)
	, _visible(true)
	, _wireframe(false)
	, _verbose(false)
	, _identity(0)
	, _measure(0)
	, _thickness(0)
	, _content(std::string())
	, _filename(std::string())
	, _hinting(g2d::graphic::hinting::hinting_normal)
	, _weight(g2d::graphic::weight::weight_normal)
	, _flip(g2d::graphic::flip::flip_none)
	, _thickness_color(g2d::math::color(0, 0, 0, 255))
	, _shadow_color(g2d::math::color(128, 128, 128, 255))
	, _body_color(g2d::math::color(255))
	, _color(g2d::math::color(255))
	, _bump(g2d::math::point2dd(0.0))
	, _pivot(g2d::math::point2dd(0.0))
	, _shadow_position(g2d::math::point2dd(0.0))
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

g2d::graphic::text::~text()
{
	this->destroy();
}

bool g2d::graphic::text::initialize(const std::string& filename, std::size_t measure, bool verbose)
{
	this->_body = TTF_OpenFont(filename.c_str(), measure);

	if (this->_body == nullptr)
	{
		std::cerr << "Cannot initialize font '" << filename << " -- " << TTF_GetError() << "', failed" << std::endl;

		return false;
	}

	this->_stroke = TTF_OpenFont(filename.c_str(), measure);

	if (this->_stroke == nullptr)
	{
		std::cerr << "Cannot initialize font '" << filename << " -- " << TTF_GetError() << "', failed" << std::endl;

		return false;
	}

	this->_shadow = TTF_OpenFont(filename.c_str(), measure);

	if (this->_shadow == nullptr)
	{
		std::cerr << "Cannot initialize font '" << filename << " -- " << TTF_GetError() << "', failed" << std::endl;

		return false;
	}

	if (verbose)
	{
		std::clog << "Loading text '" << filename << "', OK. -- " << measure << " dpi" << std::endl;
	}

	this->_filename = filename;
	this->_measure = measure;
	this->_verbose = verbose;

	TTF_SetFontStyle(this->_body, TTF_STYLE_NORMAL);
	TTF_SetFontStyle(this->_stroke, TTF_STYLE_NORMAL);
	TTF_SetFontStyle(this->_shadow, TTF_STYLE_NORMAL);

	TTF_SetFontHinting(this->_body, TTF_HINTING_NORMAL);
	TTF_SetFontHinting(this->_stroke, TTF_HINTING_NORMAL);
	TTF_SetFontHinting(this->_shadow, TTF_HINTING_NORMAL);

	GLenum error = glGetError();

	glGenTextures(1, &this->_identity);

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "Cannot generate texture: '" << gluErrorString(error) << "', failed" << std::endl;

		return false;
	}

	this->_uvmap.u(1.0);
	this->_uvmap.v(1.0);

	this->_offset.x(0.0);
	this->_offset.y(0.0);
	this->_offset.w(this->_uvmap.u() + this->_offset.x());
	this->_offset.h(this->_uvmap.v() + this->_offset.y());

	this->mapping();

	return true;
}

bool g2d::graphic::text::animation(const std::string& animation, std::size_t length, std::size_t fps)
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

void g2d::graphic::text::destroy()
{
	TTF_CloseFont(this->_body);
	TTF_CloseFont(this->_stroke);
	TTF_CloseFont(this->_shadow);

	this->_body = nullptr;
	this->_stroke = nullptr;
	this->_shadow = nullptr;

	glDeleteTextures(1, &this->_identity);

	for (auto& arg : this->_animations)
	{
		delete arg.second;
	}

	this->_animations.clear();
}

void g2d::graphic::text::draw()
{
	if (this->_visible && this->_color.a() > 0 && this->_scale != 0 && !this->_content.empty())
	{
		this->mapping();

		glPushMatrix();

		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);

		this->bind();

		glTranslated(this->_position.x() + this->_bump.x(), this->_position.y() + this->_bump.y(), this->_position.z());

		glRotated(this->_rotate.h(), 1.0, 0.0, 0.0);
		glRotated(this->_rotate.p(), 0.0, 1.0, 0.0);
		glRotated(this->_rotate.b(), 0.0, 0.0, 1.0);

		glScaled(this->_scale.w(), this->_scale.h(), 1.0);

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

		if (this->_wireframe)
		{
			glEnable(GL_LINE_STIPPLE);

			glTranslated(this->_position.x(), this->_position.y(), -1.0);

			glRotated(this->_rotate.h(), 1.0, 0.0, 0.0);
			glRotated(this->_rotate.p(), 0.0, 1.0, 0.0);
			glRotated(this->_rotate.b(), 0.0, 0.0, 1.0);

			glScaled(this->_scale.w(), this->_scale.h(), 1.0);

			glColor4d(0.0, 1.0, 0.0, 1.0);
			glLineWidth(2.0);
			glBegin(GL_LINE_LOOP);
			glVertex3d(this->_vertex.a().x(), this->_vertex.a().y(), this->_vertex.a().z());
			glVertex3d(this->_vertex.b().x(), this->_vertex.b().y(), this->_vertex.b().z());
			glVertex3d(this->_vertex.c().x(), this->_vertex.c().y(), this->_vertex.c().z());
			glVertex3d(this->_vertex.d().x(), this->_vertex.d().y(), this->_vertex.d().z());
			glEnd();

			glColor4d(0.0, 0.0, 1.0, 1.0);
			glLineWidth(2.0);
			glBegin(GL_LINES);
			glVertex3d(-10.0, 0.0, 0.0);
			glVertex3d( 10.0, 0.0, 0.0);
			glEnd();

			glColor4d(1.0, 0.0, 0.0, 1.0);
			glLineWidth(2.0);
			glBegin(GL_LINES);
			glVertex3d(0.0, -10.0, 0.0);
			glVertex3d(0.0,  10.0, 0.0);
			glEnd();

			glDisable(GL_LINE_STIPPLE);
		}

		glPopMatrix();
	}
}

void g2d::graphic::text::run()
{
	assert(this->_animation != nullptr && this->_animation->has_tweener());

	if (!this->_run)
	{
		return;
	}

	if (this->_animation->has_content())
	{
		this->content(this->_animation->content());
	}

	if (this->_animation->has_visible())
	{
		this->visible(this->_animation->visible());
	}

	if (this->_animation->has_wireframe())
	{
		this->wireframe(this->_animation->wireframe());
	}

	if (this->_animation->has_hinting())
	{
		this->hinting(this->_animation->hinting());
	}

	if (this->_animation->has_weight())
	{
		this->weight(this->_animation->weight());
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

void g2d::graphic::text::play()
{
	assert(this->_animation != nullptr && this->_animation->has_tweener());

	this->_animation->play();
	this->_run = true;
}

void g2d::graphic::text::pause()
{
	assert(this->_animation != nullptr && this->_animation->has_tweener());

	this->_animation->stop();
	this->_run = false;
}

void g2d::graphic::text::replay()
{
	assert(this->_animation != nullptr && this->_animation->has_tweener());

	this->_animation->replay();
	this->_run = true;
}

void g2d::graphic::text::reset()
{
	assert(this->_animation != nullptr && this->_animation->has_tweener());

	this->_animation->reset();
	this->_run = false;
}

bool g2d::graphic::text::played() const
{
	assert(this->_animation != nullptr && this->_animation->has_tweener());

	return this->_animation->played() && this->_run;
}

bool g2d::graphic::text::onset() const
{
	assert(this->_animation != nullptr && this->_animation->has_tweener());

	return this->_animation->onset();
}

bool g2d::graphic::text::bound() const
{
	assert(this->_animation != nullptr && this->_animation->has_tweener());

	return this->_animation->bound();
}

void g2d::graphic::text::visible(bool visible)
{
	this->_visible = visible;
}

void g2d::graphic::text::wireframe(bool wireframe)
{
	this->_wireframe = wireframe;
}

void g2d::graphic::text::verbose(bool verbose)
{
	this->_verbose = verbose;
}

void g2d::graphic::text::measure(std::size_t measure)
{
	if (this->_measure == measure)
	{
		return;
	}

	this->_body = TTF_OpenFont(this->_filename.c_str(), measure);

	if (this->_body == nullptr)
	{
		std::cerr << "Cannot initialize font '" << this->_filename << " -- " << TTF_GetError() << "', failed" << std::endl;

		exit(EXIT_FAILURE);
	}

	this->_stroke = TTF_OpenFont(this->_filename.c_str(), measure);

	if (this->_stroke == nullptr)
	{
		std::cerr << "Cannot initialize font '" << this->_filename << " -- " << TTF_GetError() << "', failed" << std::endl;

		exit(EXIT_FAILURE);
	}

	this->_shadow = TTF_OpenFont(this->_filename.c_str(), measure);

	if (this->_shadow == nullptr)
	{
		std::cerr << "Cannot initialize font '" << this->_filename << " -- " << TTF_GetError() << "', failed" << std::endl;

		exit(EXIT_FAILURE);
	}

	if (this->_verbose)
	{
		std::clog << "Loading text '" << this->_filename << "', OK.-- " << measure << " dpi" << std::endl;
	}

	this->_measure = measure;
}

void g2d::graphic::text::thickness(std::size_t thickness)
{
	this->_thickness = thickness;
}

void g2d::graphic::text::content(const std::string& content)
{
	this->_content = content;
}

void g2d::graphic::text::hinting(const g2d::graphic::hinting& hinting)
{
	this->_hinting = hinting;
}

void g2d::graphic::text::weight(const g2d::graphic::weight& weight)
{
	this->_weight = weight;
}

void g2d::graphic::text::flip(const g2d::graphic::flip& flip)
{
	this->_flip = flip;
}

void g2d::graphic::text::thickness_color(const g2d::math::color& color)
{
	this->_thickness_color = color;
}

void g2d::graphic::text::thickness_color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	this->_thickness_color.set(r, g, b, a);
}

void g2d::graphic::text::thickness_color(std::uint8_t color)
{
	this->_thickness_color = color;
}

void g2d::graphic::text::thickness_color_r(std::uint8_t r)
{
	this->_thickness_color.r(r);
}

void g2d::graphic::text::thickness_color_g(std::uint8_t g)
{
	this->_thickness_color.g(g);
}

void g2d::graphic::text::thickness_color_b(std::uint8_t b)
{
	this->_thickness_color.b(b);
}

void g2d::graphic::text::thickness_color_a(std::uint8_t a)
{
	this->_thickness_color.a(a);
}

void g2d::graphic::text::shadow_color(const g2d::math::color& color)
{
	this->_shadow_color = color;
}

void g2d::graphic::text::shadow_color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	this->_shadow_color.set(r, g, b, a);
}

void g2d::graphic::text::shadow_color(std::uint8_t color)
{
	this->_shadow_color = color;
}

void g2d::graphic::text::shadow_color_r(std::uint8_t r)
{
	this->_shadow_color.r(r);
}

void g2d::graphic::text::shadow_color_g(std::uint8_t g)
{
	this->_shadow_color.g(g);
}

void g2d::graphic::text::shadow_color_b(std::uint8_t b)
{
	this->_shadow_color.b(b);
}

void g2d::graphic::text::shadow_color_a(std::uint8_t a)
{
	this->_shadow_color.a(a);
}

void g2d::graphic::text::body_color(const g2d::math::color& color)
{
	this->_body_color = color;
}

void g2d::graphic::text::body_color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	this->_body_color.set(r, g, b, a);
}

void g2d::graphic::text::body_color(std::uint8_t color)
{
	this->_body_color = color;
}

void g2d::graphic::text::body_color_r(std::uint8_t r)
{
	this->_body_color.r(r);
}

void g2d::graphic::text::body_color_g(std::uint8_t g)
{
	this->_body_color.g(g);
}

void g2d::graphic::text::body_color_b(std::uint8_t b)
{
	this->_body_color.b(b);
}

void g2d::graphic::text::body_color_a(std::uint8_t a)
{
	this->_body_color.a(a);
}

void g2d::graphic::text::color(const g2d::math::color& color)
{
	this->_color = color;
}

void g2d::graphic::text::color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	this->_color.set(r, g, b, a);
}

void g2d::graphic::text::color(std::uint8_t color)
{
	this->_color = color;
}

void g2d::graphic::text::color_r(std::uint8_t r)
{
	this->_color.r(r);
}

void g2d::graphic::text::color_g(std::uint8_t g)
{
	this->_color.g(g);
}

void g2d::graphic::text::color_b(std::uint8_t b)
{
	this->_color.b(b);
}

void g2d::graphic::text::color_a(std::uint8_t a)
{
	this->_color.a(a);
}

void g2d::graphic::text::pivot(const g2d::math::point2dd& pivot)
{
	this->_pivot = pivot;
}

void g2d::graphic::text::pivot(double x, double y)
{
	this->_pivot.set(x, y);
}

void g2d::graphic::text::pivot(double pivot)
{
	this->_pivot = pivot;
}

void g2d::graphic::text::pivot_x(double x)
{
	this->_pivot.x(x);
}

void g2d::graphic::text::pivot_y(double y)
{
	this->_pivot.y(y);
}

void g2d::graphic::text::shadow_position(const g2d::math::point2dd& position)
{
	this->_shadow_position = position;
}

void g2d::graphic::text::shadow_position(double x, double y)
{
	this->_shadow_position = g2d::math::point2dd(x, y);
}

void g2d::graphic::text::shadow_position(double position)
{
	this->_shadow_position = position;
}

void g2d::graphic::text::shadow_position_x(double x)
{
	this->_shadow_position.x(x);
}

void g2d::graphic::text::shadow_position_y(double y)
{
	this->_shadow_position.y(y);
}

void g2d::graphic::text::position(const g2d::math::point3dd& position)
{
	this->_position = position;
}

void g2d::graphic::text::position(double x, double y, double z)
{
	this->_position = g2d::math::point3dd(x, y, z);
}

void g2d::graphic::text::position(double position)
{
	this->_position = position;
}

void g2d::graphic::text::position_x(double x)
{
	this->_position.x(x);
}

void g2d::graphic::text::position_y(double y)
{
	this->_position.y(y);
}

void g2d::graphic::text::position_z(double z)
{
	this->_position.z(z);
}

void g2d::graphic::text::rotate(const g2d::math::rotated& rotate)
{
	this->_rotate = rotate;
}

void g2d::graphic::text::rotate(double h, double p, double b)
{
	this->_rotate.set(h, p, b);
}

void g2d::graphic::text::rotate(double rotate)
{
	this->_rotate = rotate;
}

void g2d::graphic::text::rotate_h(double h)
{
	this->_rotate.h(h);
}

void g2d::graphic::text::rotate_p(double p)
{
	this->_rotate.p(p);
}

void g2d::graphic::text::rotate_b(double b)
{
	this->_rotate.b(b);
}

void g2d::graphic::text::scale(const g2d::math::size2dd& scale)
{
	this->_scale = scale;
}

void g2d::graphic::text::scale(double w, double h)
{
	this->_scale.set(w, h);
}

void g2d::graphic::text::scale(double scale)
{
	this->_scale = scale;
}

void g2d::graphic::text::scale_w(double w)
{
	this->_scale.w(w);
}

void g2d::graphic::text::scale_h(double h)
{
	this->_scale.h(h);
}

void g2d::graphic::text::animation(const std::string& animation)
{
	auto it = this->_animations.find(animation);

	if (it == this->_animations.end())
	{
		std::cerr << "Cannot find animation: '" << animation << "', failed" << std::endl;

		exit(EXIT_FAILURE);
	}

	this->_animation = this->_animations[animation];
}

void g2d::graphic::text::append_measure(std::size_t measure)
{
	this->_measure += measure;
}

void g2d::graphic::text::append_thickness(std::size_t thickness)
{
	this->_thickness += thickness;

	TTF_SetFontOutline(this->_stroke, this->_thickness);
}

void g2d::graphic::text::append_thickness_color(const g2d::math::color& color)
{
	this->_thickness_color += color;
}

void g2d::graphic::text::append_thickness_color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	this->_thickness_color += g2d::math::color(r, g, b, a);
}

void g2d::graphic::text::append_thickness_color(std::uint8_t color)
{
	this->_thickness_color += color;
}

void g2d::graphic::text::append_thickness_color_r(std::uint8_t r)
{
	this->_thickness_color.r(this->_thickness_color.r() + r);
}

void g2d::graphic::text::append_thickness_color_g(std::uint8_t g)
{
	this->_thickness_color.g(this->_thickness_color.g() + g);
}

void g2d::graphic::text::append_thickness_color_b(std::uint8_t b)
{
	this->_thickness_color.b(this->_thickness_color.b() + b);
}

void g2d::graphic::text::append_thickness_color_a(std::uint8_t a)
{
	this->_thickness_color.a(this->_thickness_color.a() + a);
}

void g2d::graphic::text::append_shadow_color(const g2d::math::color& color)
{
	this->_shadow_color += color;
}

void g2d::graphic::text::append_shadow_color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	this->_shadow_color += g2d::math::color(r, g, b, a);
}

void g2d::graphic::text::append_shadow_color(std::uint8_t color)
{
	this->_shadow_color += color;
}

void g2d::graphic::text::append_shadow_color_r(std::uint8_t r)
{
	this->_shadow_color.r(this->_shadow_color.r() + r);
}

void g2d::graphic::text::append_shadow_color_g(std::uint8_t g)
{
	this->_shadow_color.g(this->_shadow_color.g() + g);
}

void g2d::graphic::text::append_shadow_color_b(std::uint8_t b)
{
	this->_shadow_color.b(this->_shadow_color.b() + b);
}

void g2d::graphic::text::append_shadow_color_a(std::uint8_t a)
{
	this->_shadow_color.a(this->_shadow_color.a() + a);
}

void g2d::graphic::text::append_body_color(const g2d::math::color& color)
{
	this->_body_color += color;
}

void g2d::graphic::text::append_body_color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	this->_body_color += g2d::math::color(r, g, b, a);
}

void g2d::graphic::text::append_body_color(std::uint8_t color)
{
	this->_body_color += color;
}

void g2d::graphic::text::append_body_color_r(std::uint8_t r)
{
	this->_body_color.r(this->_body_color.r() + r);
}

void g2d::graphic::text::append_body_color_g(std::uint8_t g)
{
	this->_body_color.g(this->_body_color.g() + g);
}

void g2d::graphic::text::append_body_color_b(std::uint8_t b)
{
	this->_body_color.b(this->_body_color.b() + b);
}

void g2d::graphic::text::append_body_color_a(std::uint8_t a)
{
	this->_body_color.a(this->_body_color.a() + a);
}

void g2d::graphic::text::append_color(const g2d::math::color& color)
{
	this->_color += color;
}

void g2d::graphic::text::append_color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	this->_color += g2d::math::color(r, g, b, a);
}

void g2d::graphic::text::append_color(std::uint8_t color)
{
	this->_color += color;
}

void g2d::graphic::text::append_color_r(std::uint8_t r)
{
	this->_color.r(this->_color.r() + r);
}

void g2d::graphic::text::append_color_g(std::uint8_t g)
{
	this->_color.g(this->_color.g() + g);
}

void g2d::graphic::text::append_color_b(std::uint8_t b)
{
	this->_color.b(this->_color.b() + b);
}

void g2d::graphic::text::append_color_a(std::uint8_t a)
{
	this->_color.a(this->_color.a() + a);
}

void g2d::graphic::text::append_pivot(const g2d::math::point2dd& pivot)
{
	this->_pivot += pivot;
}

void g2d::graphic::text::append_pivot(double x, double y)
{
	this->_pivot += g2d::math::point2dd(x, y);
}

void g2d::graphic::text::append_pivot(double pivot)
{
	this->_pivot += pivot;
}

void g2d::graphic::text::append_pivot_x(double x)
{
	this->_pivot.x(this->_pivot.x() + x);
}

void g2d::graphic::text::append_pivot_y(double y)
{
	this->_pivot.y(this->_pivot.y() + y);
}

void g2d::graphic::text::append_shadow_position(const g2d::math::point2dd& shadow_position)
{
	this->_shadow_position += shadow_position;
}

void g2d::graphic::text::append_shadow_position(double x, double y)
{
	this->_shadow_position += g2d::math::point2dd(x, y);
}

void g2d::graphic::text::append_shadow_position(double shadow_position)
{
	this->_shadow_position += shadow_position;
}

void g2d::graphic::text::append_shadow_position_x(double x)
{
	this->_shadow_position.x(this->_position.x() + x);
}

void g2d::graphic::text::append_shadow_position_y(double y)
{
	this->_shadow_position.y(this->_position.y() + y);
}

void g2d::graphic::text::append_position(const g2d::math::point3dd& position)
{
	this->_position += position;
}

void g2d::graphic::text::append_position(double x, double y, double z)
{
	this->_position += g2d::math::point3dd(x, y, z);
}

void g2d::graphic::text::append_position(double position)
{
	this->_position += position;
}

void g2d::graphic::text::append_position_x(double x)
{
	this->_position.x(this->_position.x() + x);
}

void g2d::graphic::text::append_position_y(double y)
{
	this->_position.y(this->_position.y() + y);
}

void g2d::graphic::text::append_position_z(double z)
{
	this->_position.z(this->_position.z() + z);
}

void g2d::graphic::text::append_rotate(const g2d::math::rotated& rotate)
{
	this->_rotate += rotate;
}

void g2d::graphic::text::append_rotate(double h, double p, double b)
{
	this->_rotate += g2d::math::rotated(h, p, b);
}

void g2d::graphic::text::append_rotate(double rotate)
{
	this->_rotate += rotate;
}

void g2d::graphic::text::append_rotate_h(double h)
{
	this->_rotate.h(this->_rotate.h() + h);
}

void g2d::graphic::text::append_rotate_p(double p)
{
	this->_rotate.p(this->_rotate.p() + p);
}

void g2d::graphic::text::append_rotate_b(double b)
{
	this->_rotate.b(this->_rotate.b() + b);
}

void g2d::graphic::text::append_scale(const g2d::math::size2dd& scale)
{
	this->_scale += scale;
}

void g2d::graphic::text::append_scale(double w, double h)
{
	this->_scale += g2d::math::size2dd(w, h);
}

void g2d::graphic::text::append_scale(double scale)
{
	this->_scale += scale;
}

void g2d::graphic::text::append_scale_w(double w)
{
	this->_scale.w(this->_scale.w() + w);
}

void g2d::graphic::text::append_scale_h(double h)
{
	this->_scale.h(this->_scale.h() + h);
}

bool g2d::graphic::text::visible() const
{
	return this->_visible;
}

bool g2d::graphic::text::wireframe() const
{
	return this->_wireframe;
}

bool g2d::graphic::text::verbose() const
{
	return this->_verbose;
}

std::size_t g2d::graphic::text::measure() const
{
	return this->_measure;
}

std::size_t g2d::graphic::text::thickness() const
{
	return this->_thickness;
}

const std::string& g2d::graphic::text::content() const
{
	return this->_content;
}

const std::string& g2d::graphic::text::filename() const
{
	return this->_filename;
}

const g2d::graphic::hinting& g2d::graphic::text::hinting() const
{
	return this->_hinting;
}

const g2d::graphic::weight& g2d::graphic::text::weight() const
{
	return this->_weight;
}

const g2d::graphic::flip& g2d::graphic::text::flip() const
{
	return this->_flip;
}

const g2d::math::color& g2d::graphic::text::thickness_color() const
{
	return this->_thickness_color;
}

const g2d::math::color& g2d::graphic::text::shadow_color() const
{
	return this->_shadow_color;
}

const g2d::math::color& g2d::graphic::text::body_color() const
{
	return this->_body_color;
}

const g2d::math::color& g2d::graphic::text::color() const
{
	return this->_color;
}

const g2d::math::point2dd& g2d::graphic::text::pivot() const
{
	return this->_pivot;
}

const g2d::math::point2dd& g2d::graphic::text::shadow_position() const
{
	return this->_shadow_position;
}

const g2d::math::point3dd& g2d::graphic::text::position() const
{
	return this->_position;
}

const g2d::math::rotated& g2d::graphic::text::rotate() const
{
	return this->_rotate;
}

const g2d::math::size2dd& g2d::graphic::text::size() const
{
	return this->_size;
}

const g2d::math::size2dd& g2d::graphic::text::scale() const
{
	return this->_scale;
}

g2d::animation::tweener* g2d::graphic::text::animation() const
{
	return this->_animation;
}

void g2d::graphic::text::bind(const g2d::graphic::filter& filter, const g2d::graphic::wrap& wrap)
{
	GLenum error = glGetError();

	glBindTexture(GL_TEXTURE_2D, this->_identity);

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "Cannot bind identity: '" << gluErrorString(error) << "', failed" << std::endl;

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

		exit(EXIT_FAILURE);
	}
}

void g2d::graphic::text::mapping()
{
	if (this->_content.empty())
	{
		return;
	}

	switch (this->_weight)
	{
		default:
		{
			break;
		}
		case g2d::graphic::weight::weight_normal:
		{
			TTF_SetFontStyle(this->_body, TTF_STYLE_NORMAL);
			TTF_SetFontStyle(this->_stroke, TTF_STYLE_NORMAL);
			TTF_SetFontStyle(this->_shadow, TTF_STYLE_NORMAL);

			break;
		}
		case g2d::graphic::weight::weight_bold:
		{
			TTF_SetFontStyle(this->_body, TTF_STYLE_BOLD);
			TTF_SetFontStyle(this->_stroke, TTF_STYLE_BOLD);
			TTF_SetFontStyle(this->_shadow, TTF_STYLE_BOLD);

			break;
		}
		case g2d::graphic::weight::weight_italic:
		{
			TTF_SetFontStyle(this->_body, TTF_STYLE_ITALIC);
			TTF_SetFontStyle(this->_stroke, TTF_STYLE_ITALIC);
			TTF_SetFontStyle(this->_shadow, TTF_STYLE_ITALIC);

			break;
		}
		case g2d::graphic::weight::weight_underline:
		{
			TTF_SetFontStyle(this->_body, TTF_STYLE_UNDERLINE);
			TTF_SetFontStyle(this->_stroke, TTF_STYLE_UNDERLINE);
			TTF_SetFontStyle(this->_shadow, TTF_STYLE_UNDERLINE);

			break;
		}
		case g2d::graphic::weight::weight_strikethrough:
		{
			TTF_SetFontStyle(this->_body, TTF_STYLE_STRIKETHROUGH);
			TTF_SetFontStyle(this->_stroke, TTF_STYLE_STRIKETHROUGH);
			TTF_SetFontStyle(this->_shadow, TTF_STYLE_STRIKETHROUGH);

			break;
		}
	}

	switch (this->_hinting)
	{
		default:
		{
			break;
		}
		case g2d::graphic::hinting::hinting_none:
		{
			TTF_SetFontHinting(this->_body, TTF_HINTING_NONE);
			TTF_SetFontHinting(this->_stroke, TTF_HINTING_NONE);
			TTF_SetFontHinting(this->_shadow, TTF_HINTING_NONE);

			break;
		}
		case g2d::graphic::hinting::hinting_normal:
		{
			TTF_SetFontHinting(this->_body, TTF_HINTING_NORMAL);
			TTF_SetFontHinting(this->_stroke, TTF_HINTING_NORMAL);
			TTF_SetFontHinting(this->_shadow, TTF_HINTING_NORMAL);

			break;
		}
		case g2d::graphic::hinting::hinting_light:
		{
			TTF_SetFontHinting(this->_body, TTF_HINTING_LIGHT);
			TTF_SetFontHinting(this->_stroke, TTF_HINTING_LIGHT);
			TTF_SetFontHinting(this->_shadow, TTF_HINTING_LIGHT);

			break;
		}
		case g2d::graphic::hinting::hinting_mono:
		{
			TTF_SetFontHinting(this->_body, TTF_HINTING_MONO);
			TTF_SetFontHinting(this->_stroke, TTF_HINTING_MONO);
			TTF_SetFontHinting(this->_shadow, TTF_HINTING_MONO);

			break;
		}
	}

	SDL_Surface* image = nullptr;
	SDL_Surface* base = nullptr;

	g2d::math::size2dd stroke = g2d::math::size2dd(0.0);
	g2d::math::size2dd body = g2d::math::size2dd(0.0);
	g2d::math::size2dd shadow = g2d::math::size2dd(0.0);

	// merge thickness.
	if (this->_thickness != 0)
	{
		TTF_SetFontOutline(this->_stroke, this->_thickness);

		base = TTF_RenderUTF8_Blended(this->_stroke, this->_content.c_str(), {
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGB masks */
			static_cast<Uint8>(this->_thickness_color.r()),
			static_cast<Uint8>(this->_thickness_color.g()),
			static_cast<Uint8>(this->_thickness_color.b()),
			static_cast<Uint8>(this->_thickness_color.a())
#else
			static_cast<Uint8>(this->_thickness_color.b()),
			static_cast<Uint8>(this->_thickness_color.g()),
			static_cast<Uint8>(this->_thickness_color.r()),
			static_cast<Uint8>(this->_thickness_color.a())
#endif
		});

		stroke.set(static_cast<double>(base->w), static_cast<double>(base->h));

		SDL_SetSurfaceBlendMode(base, SDL_BLENDMODE_BLEND);

		SDL_Surface* merge = TTF_RenderUTF8_Blended(this->_body, this->_content.c_str(), {
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGB masks */
			static_cast<Uint8>(this->_body_color.r()),
			static_cast<Uint8>(this->_body_color.g()),
			static_cast<Uint8>(this->_body_color.b()),
			static_cast<Uint8>(this->_body_color.a())
#else
			static_cast<Uint8>(this->_body_color.b()),
			static_cast<Uint8>(this->_body_color.g()),
			static_cast<Uint8>(this->_body_color.r()),
			static_cast<Uint8>(this->_body_color.a())
#endif
		});

		body.set(static_cast<double>(merge->w), static_cast<double>(merge->h));

		SDL_Rect rect = {
			static_cast<int>(this->_thickness),
			static_cast<int>(this->_thickness),
			base->w,
			base->h
		};

		SDL_BlitSurface(merge, NULL, base, &rect);

		SDL_FreeSurface(merge);
	}
	else
	{
		base = TTF_RenderUTF8_Blended(this->_body, this->_content.c_str(), {
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGB masks */
			static_cast<Uint8>(this->_color.r()),
			static_cast<Uint8>(this->_color.g()),
			static_cast<Uint8>(this->_color.b()),
			static_cast<Uint8>(this->_color.a())
#else
			static_cast<Uint8>(this->_color.b()),
			static_cast<Uint8>(this->_color.g()),
			static_cast<Uint8>(this->_color.r()),
			static_cast<Uint8>(this->_color.a())
#endif
		});

		body.set(static_cast<double>(base->w), static_cast<double>(base->h));
	}

	// merge shadow
	if (this->_shadow_position != 0)
	{
		SDL_Surface* merge = TTF_RenderUTF8_Blended(this->_shadow, this->_content.c_str(), {
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGB masks */
			static_cast<Uint8>(this->_shadow_color.r()),
			static_cast<Uint8>(this->_shadow_color.g()),
			static_cast<Uint8>(this->_shadow_color.b()),
			static_cast<Uint8>(this->_shadow_color.a())
#else
			static_cast<Uint8>(this->_shadow_color.b()),
			static_cast<Uint8>(this->_shadow_color.g()),
			static_cast<Uint8>(this->_shadow_color.r()),
			static_cast<Uint8>(this->_shadow_color.a())
#endif
		});

		int w = static_cast<int>(std::abs(this->_shadow_position.x())) + static_cast<int>(this->_thickness) + merge->w;
		int h = static_cast<int>(std::abs(this->_shadow_position.y())) + static_cast<int>(this->_thickness) + merge->h;
#if 0
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	    Uint32 rmask = 0xff000000;
	    Uint32 gmask = 0x00ff0000;
	    Uint32 bmask = 0x0000ff00;
	    Uint32 amask = 0x000000ff;
#else
	    Uint32 rmask = 0x000000ff;
	    Uint32 gmask = 0x0000ff00;
	    Uint32 bmask = 0x00ff0000;
	    Uint32 amask = 0xff000000;
#endif

	    image = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);
#else
		image = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA32);
#endif
		SDL_SetSurfaceBlendMode(image, SDL_BLENDMODE_ADD);

		int x = this->_shadow_position.x() <= 0.0 ? 0.0 : static_cast<int>(std::abs(this->_shadow_position.x()));
		int y = this->_shadow_position.y() <= 0.0 ? 0.0 : static_cast<int>(std::abs(this->_shadow_position.y()));

		shadow.set(static_cast<double>(image->w), static_cast<double>(image->h));

		SDL_Rect rect = { x, y, merge->w, merge->h };

		SDL_BlitSurface(merge, NULL, image, &rect);

		SDL_FreeSurface(merge);
	}
	else
	{
#if 0
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	    Uint32 rmask = 0xff000000;
	    Uint32 gmask = 0x00ff0000;
	    Uint32 bmask = 0x0000ff00;
	    Uint32 amask = 0x000000ff;
#else
	    Uint32 rmask = 0x000000ff;
	    Uint32 gmask = 0x0000ff00;
	    Uint32 bmask = 0x00ff0000;
	    Uint32 amask = 0xff000000;
#endif
	    image = SDL_CreateRGBSurface(0, base->w, base->h, 32, rmask, gmask, bmask, amask);
#else
		image = SDL_CreateRGBSurfaceWithFormat(0, base->w, base->h, 32, SDL_PIXELFORMAT_RGBA32);
#endif
		shadow.set(static_cast<double>(image->w), static_cast<double>(image->h));
	}

	// merge all.
	SDL_SetSurfaceBlendMode(image, SDL_BLENDMODE_ADD);

	int x = this->_shadow_position.x() >= 0.0 ? 0 : static_cast<int>(std::abs(this->_shadow_position.x()));
	int y = this->_shadow_position.y() >= 0.0 ? 0 : static_cast<int>(std::abs(this->_shadow_position.y()));

	SDL_Rect rect = { x, y, image->w, image->h };

	SDL_BlitSurface(base, NULL, image, &rect);

	SDL_FreeSurface(base);

	if (image == nullptr)
	{
		std::cerr << "Cannot transport TTF: '" << SDL_GetError() << "', failed" << std::endl;

		exit(EXIT_FAILURE);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, this->_identity);

		GLint internal_format = 0;
		GLint format = 0;

		switch (image->format->BytesPerPixel)
		{
			case 1:
			{
				internal_format = GL_LUMINANCE;
				format = GL_RED;
				break;
			}
			case 2:
			{
				internal_format = GL_LUMINANCE_ALPHA;
				format = GL_RG;
				break;
			}
			case 3:
			{
				internal_format = GL_RGB;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGB masks */
				format = GL_RGB;
#else
				format = GL_BGR;
#endif
				break;
			}
			case 4:
			{
				internal_format = GL_RGBA;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
				format = GL_RGBA;
#else
				format = GL_BGRA;
#endif
				break;
			}
			default:
			{
				std::cerr << "Unknown image format, failed" << std::endl;

				exit(EXIT_FAILURE);
			}
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, image->w % 4 == 0 ? 4 : 1);
		glTexImage2D(GL_TEXTURE_2D, 0, internal_format, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

		// calculates the dimensions of the polygon.
		this->_size.set(static_cast<double>(image->w), static_cast<double>(image->h));
		this->_bump.set(g2d::math::invert(static_cast<double>(this->_thickness)) - this->_shadow_position.x(), g2d::math::invert(static_cast<double>(this->_thickness)) - this->_shadow_position.y());

		SDL_FreeSurface(image);

		double x = g2d::math::invert(this->_size.w() * this->_pivot.x());
		double y = g2d::math::invert(this->_size.h() * this->_pivot.y());
		double w = x + this->_size.w();
		double h = y + this->_size.h();

		this->_vertex.a(x, y, 0.0);
		this->_vertex.b(w, y, 0.0);
		this->_vertex.c(w, h, 0.0);
		this->_vertex.d(x, h, 0.0);
	}
}



void g2d::graphic::text::mappingB()
{
	if (this->_content.empty())
	{
		return;
	}

	switch (this->_weight)
	{
		default:
		{
			break;
		}
		case g2d::graphic::weight::weight_normal:
		{
			TTF_SetFontStyle(this->_body, TTF_STYLE_NORMAL);
			TTF_SetFontStyle(this->_stroke, TTF_STYLE_NORMAL);
			TTF_SetFontStyle(this->_shadow, TTF_STYLE_NORMAL);

			break;
		}
		case g2d::graphic::weight::weight_bold:
		{
			TTF_SetFontStyle(this->_body, TTF_STYLE_BOLD);
			TTF_SetFontStyle(this->_stroke, TTF_STYLE_BOLD);
			TTF_SetFontStyle(this->_shadow, TTF_STYLE_BOLD);

			break;
		}
		case g2d::graphic::weight::weight_italic:
		{
			TTF_SetFontStyle(this->_body, TTF_STYLE_ITALIC);
			TTF_SetFontStyle(this->_stroke, TTF_STYLE_ITALIC);
			TTF_SetFontStyle(this->_shadow, TTF_STYLE_ITALIC);

			break;
		}
		case g2d::graphic::weight::weight_underline:
		{
			TTF_SetFontStyle(this->_body, TTF_STYLE_UNDERLINE);
			TTF_SetFontStyle(this->_stroke, TTF_STYLE_UNDERLINE);
			TTF_SetFontStyle(this->_shadow, TTF_STYLE_UNDERLINE);

			break;
		}
		case g2d::graphic::weight::weight_strikethrough:
		{
			TTF_SetFontStyle(this->_body, TTF_STYLE_STRIKETHROUGH);
			TTF_SetFontStyle(this->_stroke, TTF_STYLE_STRIKETHROUGH);
			TTF_SetFontStyle(this->_shadow, TTF_STYLE_STRIKETHROUGH);

			break;
		}
	}

	switch (this->_hinting)
	{
		default:
		{
			break;
		}
		case g2d::graphic::hinting::hinting_none:
		{
			TTF_SetFontHinting(this->_body, TTF_HINTING_NONE);
			TTF_SetFontHinting(this->_stroke, TTF_HINTING_NONE);
			TTF_SetFontHinting(this->_shadow, TTF_HINTING_NONE);

			break;
		}
		case g2d::graphic::hinting::hinting_normal:
		{
			TTF_SetFontHinting(this->_body, TTF_HINTING_NORMAL);
			TTF_SetFontHinting(this->_stroke, TTF_HINTING_NORMAL);
			TTF_SetFontHinting(this->_shadow, TTF_HINTING_NORMAL);

			break;
		}
		case g2d::graphic::hinting::hinting_light:
		{
			TTF_SetFontHinting(this->_body, TTF_HINTING_LIGHT);
			TTF_SetFontHinting(this->_stroke, TTF_HINTING_LIGHT);
			TTF_SetFontHinting(this->_shadow, TTF_HINTING_LIGHT);

			break;
		}
		case g2d::graphic::hinting::hinting_mono:
		{
			TTF_SetFontHinting(this->_body, TTF_HINTING_MONO);
			TTF_SetFontHinting(this->_stroke, TTF_HINTING_MONO);
			TTF_SetFontHinting(this->_shadow, TTF_HINTING_MONO);

			break;
		}
	}

	SDL_Surface* image = nullptr;
	SDL_Surface* layer_body = nullptr;
	SDL_Surface* layer_shadow = nullptr;
	SDL_Surface* layer_thickness = nullptr;

	g2d::math::squared body = g2d::math::squared(0.0);
	g2d::math::squared shadow = g2d::math::squared(0.0);
	g2d::math::squared thickness = g2d::math::squared(0.0);

	layer_body = TTF_RenderUTF8_Blended(this->_body, this->_content.c_str(), {
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGB masks */
		static_cast<Uint8>(this->_body_color.r()),
		static_cast<Uint8>(this->_body_color.g()),
		static_cast<Uint8>(this->_body_color.b()),
		static_cast<Uint8>(this->_body_color.a())
#else
		static_cast<Uint8>(this->_body_color.b()),
		static_cast<Uint8>(this->_body_color.g()),
		static_cast<Uint8>(this->_body_color.r()),
		static_cast<Uint8>(this->_body_color.a())
#endif
	});

	body.set(0.0, 0.0, static_cast<double>(layer_body->w), static_cast<double>(layer_body->h));

	// merge thickness.
	if (this->_thickness != 0)
	{
		TTF_SetFontOutline(this->_stroke, this->_thickness);

		layer_thickness = TTF_RenderUTF8_Blended(this->_stroke, this->_content.c_str(), {
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGB masks */
			static_cast<Uint8>(this->_thickness_color.r()),
			static_cast<Uint8>(this->_thickness_color.g()),
			static_cast<Uint8>(this->_thickness_color.b()),
			static_cast<Uint8>(this->_thickness_color.a())
#else
			static_cast<Uint8>(this->_thickness_color.b()),
			static_cast<Uint8>(this->_thickness_color.g()),
			static_cast<Uint8>(this->_thickness_color.r()),
			static_cast<Uint8>(this->_thickness_color.a())
#endif
		});

		thickness.set(0.0, 0.0, static_cast<double>(layer_thickness->w), static_cast<double>(layer_thickness->h));
	}

	// merge shadow
	if (this->_shadow_position != 0)
	{
		SDL_Surface* layer_shadow = TTF_RenderUTF8_Blended(this->_shadow, this->_content.c_str(), {
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGB masks */
			static_cast<Uint8>(this->_shadow_color.r()),
			static_cast<Uint8>(this->_shadow_color.g()),
			static_cast<Uint8>(this->_shadow_color.b()),
			static_cast<Uint8>(this->_shadow_color.a())
#else
			static_cast<Uint8>(this->_shadow_color.b()),
			static_cast<Uint8>(this->_shadow_color.g()),
			static_cast<Uint8>(this->_shadow_color.r()),
			static_cast<Uint8>(this->_shadow_color.a())
#endif
		});

		shadow.set(
			0.0,
			0.0,
			static_cast<double>(std::abs(this->_shadow_position.x())) + static_cast<double>(this->_thickness) + layer_shadow->w,
			static_cast<double>(std::abs(this->_shadow_position.y())) + static_cast<double>(this->_thickness) + layer_shadow->h
		);
	}
	/** merge all */
	int w = std::max(body.w(), std::max(shadow.w(), thickness.w()));
	int h = std::max(body.h(), std::max(shadow.h(), thickness.h()));
#if 0
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	    Uint32 rmask = 0xff000000;
	    Uint32 gmask = 0x00ff0000;
	    Uint32 bmask = 0x0000ff00;
	    Uint32 amask = 0x000000ff;
#else
	    Uint32 rmask = 0x000000ff;
	    Uint32 gmask = 0x0000ff00;
	    Uint32 bmask = 0x00ff0000;
	    Uint32 amask = 0xff000000;
#endif
	    image = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);
#else
		image = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA32);
#endif
	/** shadow */
	if (layer_shadow != nullptr)
	{
		int x = this->_shadow_position.x() >= 0.0 ? 0 : static_cast<int>(std::abs(this->_shadow_position.x()));
		int y = this->_shadow_position.y() >= 0.0 ? 0 : static_cast<int>(std::abs(this->_shadow_position.y()));

		SDL_Rect rect = { x, y, layer_shadow->w, layer_shadow->h };

		SDL_SetSurfaceBlendMode(image, SDL_BLENDMODE_ADD);
		SDL_BlitSurface(layer_shadow, NULL, image, &rect);
		SDL_FreeSurface(layer_shadow);
	}
	/** thickness */
	if (layer_thickness != nullptr)
	{
		int x = this->_shadow_position.x() >= 0.0 ? 0 : static_cast<int>(std::abs(this->_shadow_position.x()));
		int y = this->_shadow_position.y() >= 0.0 ? 0 : static_cast<int>(std::abs(this->_shadow_position.y()));

		SDL_Rect rect = { x, y, layer_thickness->w, layer_thickness->h };

		SDL_SetSurfaceBlendMode(image, SDL_BLENDMODE_ADD);
		SDL_BlitSurface(layer_thickness, NULL, image, &rect);
		SDL_FreeSurface(layer_thickness);
	}
	/** body */
	int x = this->_shadow_position.x() >= 0.0 ? this->_thickness + 0 : this->_thickness + static_cast<int>(std::abs(this->_shadow_position.x()));
	int y = this->_shadow_position.y() >= 0.0 ? this->_thickness + 0 : this->_thickness + static_cast<int>(std::abs(this->_shadow_position.y()));

	SDL_Rect rect = { x, y, image->w, image->h };

	SDL_SetSurfaceBlendMode(image, SDL_BLENDMODE_ADD);
	SDL_BlitSurface(layer_body, NULL, image, &rect);
	SDL_FreeSurface(layer_body);

	/** bind */
	if (image == nullptr)
	{
		std::cerr << "Cannot transport TTF: '" << SDL_GetError() << "', failed" << std::endl;

		exit(EXIT_FAILURE);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, this->_identity);

		GLint internal_format = 0;
		GLint format = 0;

		switch (image->format->BytesPerPixel)
		{
			case 1:
			{
				internal_format = GL_LUMINANCE;
				format = GL_RED;
				break;
			}
			case 2:
			{
				internal_format = GL_LUMINANCE_ALPHA;
				format = GL_RG;
				break;
			}
			case 3:
			{
				internal_format = GL_RGB;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGB masks */
				format = GL_RGB;
#else
				format = GL_BGR;
#endif
				break;
			}
			case 4:
			{
				internal_format = GL_RGBA;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
				format = GL_RGBA;
#else
				format = GL_BGRA;
#endif
				break;
			}
			default:
			{
				std::cerr << "Unknown image format, failed" << std::endl;

				exit(EXIT_FAILURE);
			}
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, image->w % 4 == 0 ? 4 : 1);
		glTexImage2D(GL_TEXTURE_2D, 0, internal_format, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

		// calculates the dimensions of the polygon.
		this->_size.set(static_cast<double>(image->w), static_cast<double>(image->h));
		this->_bump.set(g2d::math::invert(static_cast<double>(this->_thickness)) - this->_shadow_position.x(), g2d::math::invert(static_cast<double>(this->_thickness)) - this->_shadow_position.y());

		SDL_FreeSurface(image);

		double x = g2d::math::invert(this->_size.w() * this->_pivot.x());
		double y = g2d::math::invert(this->_size.h() * this->_pivot.y());
		double w = x + this->_size.w();
		double h = y + this->_size.h();

		this->_vertex.a(x, y, 0.0);
		this->_vertex.b(w, y, 0.0);
		this->_vertex.c(w, h, 0.0);
		this->_vertex.d(x, h, 0.0);
	}
}
