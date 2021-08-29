#include "../../includes/graphic/sprite.h"

g2d::graphic::sprite::sprite()
	: _run(false)
	, _visible(true)
	, _wireframe(false)
	, _verbose(false)
	, _identity(0)
	, _index(0)
	, _columns(1)
	, _rows(1)
	, _length(1)
	, _filename(std::string())
	, _flip(g2d::graphic::flip::flip_none)
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

g2d::graphic::sprite::~sprite()
{
	this->destroy();
}

bool g2d::graphic::sprite::initialize(const std::string& filename, std::size_t columns, std::size_t rows, std::size_t length, bool verbose)
{
	SDL_Surface* image = nullptr;

	image = IMG_Load(filename.c_str());

	if (image == nullptr)
	{
		std::cerr << "Cannot load sprite '" << filename << "', failed." << std::endl;

		return false;
	}

	if (verbose)
	{
		std::clog << "Loading sprite '" << filename << "', OK. -- " << static_cast<int>(image->format->BitsPerPixel) << " bpp" << std::endl;
	}

	GLenum error = glGetError();

	glGenTextures(1, &this->_identity);
	glBindTexture(GL_TEXTURE_2D, this->_identity);

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "Cannot generate texture: '" << gluErrorString(error) << "', failed" << std::endl;

		return false;
	}

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

	double width = static_cast<double>(image->w);
	double height = static_cast<double>(image->h);

	SDL_FreeSurface(image);

	this->_size.w(width / static_cast<double>(columns));
	this->_size.h(height / static_cast<double>(rows));

	this->_uvmap.u(this->_size.w() / width);
	this->_uvmap.v(this->_size.h() / height);

	this->_filename = filename;
	this->_columns = columns;
	this->_rows = rows;
	this->_length = length;

	this->index(0);

	this->mapping();

	return true;
}

bool g2d::graphic::sprite::initialize(const g2d::graphic::texture& texture, std::size_t columns, std::size_t rows, std::size_t length, bool verbose)
{
	this->_identity = texture.identity();

	this->bind();

	this->_size.w(texture.size().w() / static_cast<double>(columns));
	this->_size.h(texture.size().h() / static_cast<double>(rows));

	this->_uvmap.u(this->_size.w() / texture.size().w());
	this->_uvmap.v(this->_size.h() / texture.size().h());

	this->_filename = texture.filename();
	this->_columns = columns;
	this->_rows = rows;
	this->_length = length;
	this->_verbose = verbose;

	this->index(0);

	this->mapping();

	return true;
}

bool g2d::graphic::sprite::animation(const std::string& animation, std::size_t length, std::size_t fps)
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

void g2d::graphic::sprite::destroy()
{
	glDeleteTextures(1, &this->_identity);

	for (auto& arg : this->_animations)
	{
		delete arg.second;
	}

	delete this->_animation;

	this->_animation = nullptr;

	this->_animations.clear();
}

void g2d::graphic::sprite::draw()
{
	if (this->_visible && this->_color.a() > 0.0 && this->_scale != 0.0)
	{
		this->mapping();

		glPushMatrix();

		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);

		this->bind();

		glTranslated(this->_position.x(), this->_position.y(), this->_position.z());

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

void g2d::graphic::sprite::run()
{
	assert(this->_animation != nullptr && this->_animation->has_tweener());

	if (!this->_run)
	{
		return;
	}

	if (this->_animation->has_index())
	{
		this->index(this->_animation->index());
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

void g2d::graphic::sprite::play()
{
	assert(this->_animation != nullptr && this->_animation->has_tweener());

	this->_animation->play();
	this->_run = true;
}

void g2d::graphic::sprite::pause()
{
	assert(this->_animation != nullptr && this->_animation->has_tweener());

	this->_animation->stop();
	this->_run = false;
}

void g2d::graphic::sprite::replay()
{
	assert(this->_animation != nullptr && this->_animation->has_tweener());

	this->_animation->replay();
	this->_run = true;
}

void g2d::graphic::sprite::reset()
{
	assert(this->_animation != nullptr && this->_animation->has_tweener());

	this->_animation->reset();
	this->_run = false;
}

bool g2d::graphic::sprite::played() const
{
	assert(this->_animation != nullptr && this->_animation->has_tweener());

	return this->_animation->played() && this->_run;
}

bool g2d::graphic::sprite::onset() const
{
	assert(this->_animation != nullptr && this->_animation->has_tweener());

	return this->_animation->onset();
}

bool g2d::graphic::sprite::bound() const
{
	assert(this->_animation != nullptr && this->_animation->has_tweener());

	return this->_animation->bound();
}

void g2d::graphic::sprite::visible(bool visible)
{
	this->_visible = visible;
}

void g2d::graphic::sprite::wireframe(bool wireframe)
{
	this->_wireframe = wireframe;
}

void g2d::graphic::sprite::verbose(bool verbose)
{
	this->_verbose = verbose;
}

void g2d::graphic::sprite::index(std::size_t index)
{
	this->_index = g2d::math::clamp(index, 0, this->_length - 1);

	this->_offset.x(this->_uvmap.u() * static_cast<double>(this->_index % this->_columns));
	this->_offset.y(this->_uvmap.v() * static_cast<double>(this->_index / this->_columns));
	this->_offset.w(this->_uvmap.u() + this->_offset.x());
	this->_offset.h(this->_uvmap.v() + this->_offset.y());
}

void g2d::graphic::sprite::flip(const g2d::graphic::flip& flip)
{
	this->_flip = flip;
}

void g2d::graphic::sprite::color(const g2d::math::color& color)
{
	this->_color = color;
}

void g2d::graphic::sprite::color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	this->_color.set(r, g, b, a);
}

void g2d::graphic::sprite::color(std::uint8_t color)
{
	this->_color = color;
}

void g2d::graphic::sprite::color_r(std::uint8_t r)
{
	this->_color.r(r);
}

void g2d::graphic::sprite::color_g(std::uint8_t g)
{
	this->_color.g(g);
}

void g2d::graphic::sprite::color_b(std::uint8_t b)
{
	this->_color.b(b);
}

void g2d::graphic::sprite::color_a(std::uint8_t a)
{
	this->_color.a(a);
}

void g2d::graphic::sprite::pivot(const g2d::math::point2dd& pivot)
{
	this->_pivot = pivot;
}

void g2d::graphic::sprite::pivot(double x, double y)
{
	this->_pivot.set(x, y);
}

void g2d::graphic::sprite::pivot(double pivot)
{
	this->_pivot = pivot;
}

void g2d::graphic::sprite::pivot_x(double x)
{
	this->_pivot.x(x);
}

void g2d::graphic::sprite::pivot_y(double y)
{
	this->_pivot.y(y);
}

void g2d::graphic::sprite::position(const g2d::math::point3dd& position)
{
	this->_position = position;
}

void g2d::graphic::sprite::position(double x, double y, double z)
{
	this->_position = g2d::math::point3dd(x, y, z);
}

void g2d::graphic::sprite::position(double position)
{
	this->_position = position;
}

void g2d::graphic::sprite::position_x(double x)
{
	this->_position.x(x);
}

void g2d::graphic::sprite::position_y(double y)
{
	this->_position.y(y);
}

void g2d::graphic::sprite::position_z(double z)
{
	this->_position.z(z);
}

void g2d::graphic::sprite::rotate(const g2d::math::rotated& rotate)
{
	this->_rotate = rotate;
}

void g2d::graphic::sprite::rotate(double h, double p, double b)
{
	this->_rotate.set(h, p, b);
}

void g2d::graphic::sprite::rotate(double rotate)
{
	this->_rotate = rotate;
}

void g2d::graphic::sprite::rotate_h(double h)
{
	this->_rotate.h(h);
}

void g2d::graphic::sprite::rotate_p(double p)
{
	this->_rotate.p(p);
}

void g2d::graphic::sprite::rotate_b(double b)
{
	this->_rotate.b(b);
}

void g2d::graphic::sprite::scale(const g2d::math::size2dd& scale)
{
	this->_scale = scale;
}

void g2d::graphic::sprite::scale(double w, double h)
{
	this->_scale.set(w, h);
}

void g2d::graphic::sprite::scale(double scale)
{
	this->_scale = scale;
}

void g2d::graphic::sprite::scale_w(double w)
{
	this->_scale.w(w);
}

void g2d::graphic::sprite::scale_h(double h)
{
	this->_scale.h(h);
}

void g2d::graphic::sprite::animation(const std::string& animation)
{
	auto search = this->_animations.find(animation);

	if (search == this->_animations.end())
	{
		std::cerr << "Cannot find animation: '" << animation << "', failed" << std::endl;

		exit(EXIT_FAILURE);
	}

	this->_animation = this->_animations[animation];
}

void g2d::graphic::sprite::append_color(const g2d::math::color& color)
{
	this->_color += color;
}

void g2d::graphic::sprite::append_color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	this->_color += g2d::math::color(r, g, b, a);
}

void g2d::graphic::sprite::append_color(std::uint8_t color)
{
	this->_color += color;
}

void g2d::graphic::sprite::append_color_r(std::uint8_t r)
{
	this->_color.r(this->_color.r() + r);
}

void g2d::graphic::sprite::append_color_g(std::uint8_t g)
{
	this->_color.g(this->_color.g() + g);
}

void g2d::graphic::sprite::append_color_b(std::uint8_t b)
{
	this->_color.b(this->_color.b() + b);
}

void g2d::graphic::sprite::append_color_a(std::uint8_t a)
{
	this->_color.a(this->_color.a() + a);
}

void g2d::graphic::sprite::append_pivot(const g2d::math::point2dd& pivot)
{
	this->_pivot += pivot;
}

void g2d::graphic::sprite::append_pivot(double x, double y)
{
	this->_pivot += g2d::math::point2dd(x, y);
}

void g2d::graphic::sprite::append_pivot(double pivot)
{
	this->_pivot += pivot;
}

void g2d::graphic::sprite::append_pivot_x(double x)
{
	this->_pivot.x(this->_pivot.x() + x);
}

void g2d::graphic::sprite::append_pivot_y(double y)
{
	this->_pivot.y(this->_pivot.y() + y);
}

void g2d::graphic::sprite::append_position(const g2d::math::point3dd& position)
{
	this->_position += position;
}

void g2d::graphic::sprite::append_position(double x, double y, double z)
{
	this->_position += g2d::math::point3dd(x, y, z);
}

void g2d::graphic::sprite::append_position(double position)
{
	this->_position += position;
}

void g2d::graphic::sprite::append_position_x(double x)
{
	this->_position.x(this->_position.x() + x);
}

void g2d::graphic::sprite::append_position_y(double y)
{
	this->_position.y(this->_position.y() + y);
}

void g2d::graphic::sprite::append_position_z(double z)
{
	this->_position.z(this->_position.z() + z);
}

void g2d::graphic::sprite::append_rotate(const g2d::math::rotated& rotate)
{
	this->_rotate += rotate;
}

void g2d::graphic::sprite::append_rotate(double h, double p, double b)
{
	this->_rotate += g2d::math::rotated(h, p, b);
}

void g2d::graphic::sprite::append_rotate(double rotate)
{
	this->_rotate += rotate;
}

void g2d::graphic::sprite::append_rotate_h(double h)
{
	this->_rotate.h(this->_rotate.h() + h);
}

void g2d::graphic::sprite::append_rotate_p(double p)
{
	this->_rotate.p(this->_rotate.p() + p);
}

void g2d::graphic::sprite::append_rotate_b(double b)
{
	this->_rotate.b(this->_rotate.b() + b);
}

void g2d::graphic::sprite::append_scale(const g2d::math::size2dd& scale)
{
	this->_scale += scale;
}

void g2d::graphic::sprite::append_scale(double w, double h)
{
	this->_scale += g2d::math::size2dd(w, h);
}

void g2d::graphic::sprite::append_scale(double scale)
{
	this->_scale += scale;
}

void g2d::graphic::sprite::append_scale_w(double w)
{
	this->_scale.w(this->_scale.w() + w);
}

void g2d::graphic::sprite::append_scale_h(double h)
{
	this->_scale.h(this->_scale.h() + h);
}

bool g2d::graphic::sprite::visible() const
{
	return this->_visible;
}

bool g2d::graphic::sprite::wireframe() const
{
	return this->_wireframe;
}

bool g2d::graphic::sprite::verbose() const
{
	return this->_verbose;
}

std::size_t g2d::graphic::sprite::index() const
{
	return this->_index;
}

std::size_t g2d::graphic::sprite::columns() const
{
	return this->_columns;
}

std::size_t g2d::graphic::sprite::rows() const
{
	return this->_rows;
}

std::size_t g2d::graphic::sprite::length() const
{
	return this->_length;
}

const std::string& g2d::graphic::sprite::filename() const
{
	return this->_filename;
}

const g2d::graphic::flip& g2d::graphic::sprite::flip() const
{
	return this->_flip;
}

const g2d::math::color& g2d::graphic::sprite::color() const
{
	return this->_color;
}

const g2d::math::point2dd& g2d::graphic::sprite::pivot() const
{
	return this->_pivot;
}

const g2d::math::point3dd& g2d::graphic::sprite::position() const
{
	return this->_position;
}

const g2d::math::rotated& g2d::graphic::sprite::rotate() const
{
	return this->_rotate;
}

const g2d::math::size2dd& g2d::graphic::sprite::size() const
{
	return this->_size;
}

const g2d::math::size2dd& g2d::graphic::sprite::scale() const
{
	return this->_scale;
}

g2d::animation::tweener* g2d::graphic::sprite::animation() const
{
	return this->_animation;
}

void g2d::graphic::sprite::mapping()
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

void g2d::graphic::sprite::bind(const g2d::graphic::filter& filter, const g2d::graphic::wrap& wrap)
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
