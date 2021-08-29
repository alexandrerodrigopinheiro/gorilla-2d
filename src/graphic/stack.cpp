#include "../../includes/graphic/stack.h"

g2d::graphic::stack::stack()
	: _run(false)
	, _visible(true)
	, _wireframe(false)
	, _verbose(false)
	, _identity(std::vector<uint>())
	, _index(0)
	, _length(1)
	, _filename(std::vector<std::string>())
	, _flip(g2d::graphic::flip::flip_none)
	, _color(g2d::math::color(255))
	, _pivot(g2d::math::point2dd(0.0))
	, _position(g2d::math::point3dd(0.0))
	, _rotate(g2d::math::rotated(0.0))
	, _scale(g2d::math::size2dd(1.0))
	, _animations(std::map<std::string, g2d::animation::tweener*>())
	, _animation(nullptr)
	, _size(std::vector<g2d::math::size2dd>())
	, _offset(g2d::math::squared(0.0))
	, _vertex(g2d::math::vertexd(0.0))
	, _uvmap(g2d::math::uvmapd(1.0))
{
}

g2d::graphic::stack::~stack()
{
	this->destroy();
}

bool g2d::graphic::stack::initialize(const std::string& filename, bool verbose)
{
	SDL_Surface* image = nullptr;

	image = IMG_Load(filename.c_str());

	if (image == nullptr)
	{
		std::cerr << "Cannot load stack '" << filename << "', failed." << std::endl;

		return false;
	}

	if (verbose)
	{
		std::clog << "Loading stack '" << filename << "', OK. -- " << static_cast<int>(image->format->BitsPerPixel) << " bpp" << std::endl;
	}

	uint identity;

	GLenum error = glGetError();

	glGenTextures(1, &identity);
	glBindTexture(GL_TEXTURE_2D, identity);

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "Cannot generate texture: '" << gluErrorString(error) << "', failed" << std::endl;

		return false;
	}

	this->_identity.push_back(identity);

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

	this->_size.push_back(g2d::math::size2dd(static_cast<double>(image->w), static_cast<double>(image->h)));

	SDL_FreeSurface(image);

	this->_filename.push_back(filename);

	this->_length = this->_identity.size();

	this->_uvmap.set(1.0);

	this->_offset.x(0.0);
	this->_offset.y(0.0);
	this->_offset.w(this->_uvmap.u() + this->_offset.x());
	this->_offset.h(this->_uvmap.v() + this->_offset.y());

	this->mapping();

	return true;
}

bool g2d::graphic::stack::initialize(const g2d::graphic::texture& texture, bool verbose)
{
	this->_identity.push_back(texture.identity());

	this->bind();


	this->_size.push_back(g2d::math::size2dd(texture.size().w(), texture.size().h()));

	this->_uvmap.set(1.0);

	this->_offset.x(0.0);
	this->_offset.y(0.0);
	this->_offset.w(this->_uvmap.u() + this->_offset.x());
	this->_offset.h(this->_uvmap.v() + this->_offset.y());

	this->_filename.push_back(texture.filename());

	this->_length = this->_identity.size();
	this->_verbose = verbose;

	this->mapping();

	return true;
}

bool g2d::graphic::stack::animation(const std::string& animation, std::size_t length, std::size_t fps)
{
	auto it = this->_animations.find(animation);

	if (it != this->_animations.end())
	{
		std::cerr << "Cannot reuse same identity: '" << animation << "', failed" << std::endl;

		return false;
	}

	this->_animations.insert(std::pair<std::string, g2d::animation::tweener*>(animation, new g2d::animation::tweener()));

	if (this->_animations[animation]->initialize(animation, length, fps))
	{
		std::cerr << "Could not initialize the animation: '" << animation << "', failed" << std::endl;

		return false;
	}

	if (this->_animation == nullptr)
	{
		this->_animation = this->_animations[animation];
	}

	return true;
}

void g2d::graphic::stack::destroy()
{
	for (std::size_t i = 0; i < this->_identity.size(); i++)
	{
		GLuint data = this->_identity[i];

		glDeleteTextures(1, &data);
	}

	for (auto& arg : this->_animations)
	{
		delete arg.second;
	}

	this->_identity.clear();
	this->_animations.clear();
}

void g2d::graphic::stack::draw()
{
	if (this->_visible && this->_color.a() > 0 && this->_scale != 0)
	{
		this->mapping();

		glPushMatrix();

		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);

		this->bind();

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

void g2d::graphic::stack::run()
{
	if (this->_animation == nullptr)
	{
		std::cerr << "There is no identity, failed" << std::endl;

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

void g2d::graphic::stack::play()
{
	if (this->_animation == nullptr)
	{
		return;
	}

	if (!this->_animation->has_tweener())
	{
		return;
	}

	this->_animation->play();
	this->_run = true;
}

void g2d::graphic::stack::pause()
{
	if (this->_animation == nullptr)
	{
		return;
	}

	if (!this->_animation->has_tweener())
	{
		return;
	}

	this->_animation->stop();
	this->_run = false;
}

void g2d::graphic::stack::replay()
{
	if (this->_animation == nullptr)
	{
		return;
	}

	if (!this->_animation->has_tweener())
	{
		return;
	}

	this->_animation->replay();
	this->_run = true;
}

void g2d::graphic::stack::reset()
{
	if (this->_animation == nullptr)
	{
		return;
	}

	if (!this->_animation->has_tweener())
	{
		return;
	}

	this->_animation->reset();
	this->_run = false;
}

bool g2d::graphic::stack::played() const
{
	if (this->_animation == nullptr)
	{
		return false;
	}

	if (!this->_animation->has_tweener())
	{
		return false;
	}

	return this->_animation->played() && this->_run;
}

bool g2d::graphic::stack::onset() const
{
	if (this->_animation == nullptr)
	{
		return false;
	}

	if (!this->_animation->has_tweener())
	{
		return false;
	}

	return this->_animation->onset();
}

bool g2d::graphic::stack::bound() const
{
	if (this->_animation == nullptr)
	{
		return false;
	}

	if (!this->_animation->has_tweener())
	{
		return false;
	}

	return this->_animation->bound();
}

void g2d::graphic::stack::visible(bool visible)
{
	this->_visible = visible;
}

void g2d::graphic::stack::wireframe(bool wireframe)
{
	this->_wireframe = wireframe;
}

void g2d::graphic::stack::verbose(bool verbose)
{
	this->_verbose = verbose;
}

void g2d::graphic::stack::index(std::size_t index)
{
	this->_index = g2d::math::clamp(index, 0, this->_length - 1);
}

void g2d::graphic::stack::flip(const g2d::graphic::flip& flip)
{
	this->_flip = flip;
}

void g2d::graphic::stack::color(const g2d::math::color& color)
{
	this->_color = color;
}

void g2d::graphic::stack::color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	this->_color.set(r, g, b, a);
}

void g2d::graphic::stack::color(std::uint8_t color)
{
	this->_color = color;
}

void g2d::graphic::stack::color_r(std::uint8_t r)
{
	this->_color.r(r);
}

void g2d::graphic::stack::color_g(std::uint8_t g)
{
	this->_color.g(g);
}

void g2d::graphic::stack::color_b(std::uint8_t b)
{
	this->_color.b(b);
}

void g2d::graphic::stack::color_a(std::uint8_t a)
{
	this->_color.a(a);
}

void g2d::graphic::stack::pivot(const g2d::math::point2dd& pivot)
{
	this->_pivot = pivot;
}

void g2d::graphic::stack::pivot(double x, double y)
{
	this->_pivot.set(x, y);
}

void g2d::graphic::stack::pivot(double pivot)
{
	this->_pivot = pivot;
}

void g2d::graphic::stack::pivot_x(double x)
{
	this->_pivot.x(x);
}

void g2d::graphic::stack::pivot_y(double y)
{
	this->_pivot.y(y);
}

void g2d::graphic::stack::position(const g2d::math::point3dd& position)
{
	this->_position = position;
}

void g2d::graphic::stack::position(double x, double y, double z)
{
	this->_position = g2d::math::point3dd(x, y, z);
}

void g2d::graphic::stack::position(double position)
{
	this->_position = position;
}

void g2d::graphic::stack::position_x(double x)
{
	this->_position.x(x);
}

void g2d::graphic::stack::position_y(double y)
{
	this->_position.y(y);
}

void g2d::graphic::stack::position_z(double z)
{
	this->_position.z(z);
}

void g2d::graphic::stack::rotate(const g2d::math::rotated& rotate)
{
	this->_rotate = rotate;
}

void g2d::graphic::stack::rotate(double h, double p, double b)
{
	this->_rotate.set(h, p, b);
}

void g2d::graphic::stack::rotate(double rotate)
{
	this->_rotate = rotate;
}

void g2d::graphic::stack::rotate_h(double h)
{
	this->_rotate.h(h);
}

void g2d::graphic::stack::rotate_p(double p)
{
	this->_rotate.p(p);
}

void g2d::graphic::stack::rotate_b(double b)
{
	this->_rotate.b(b);
}

void g2d::graphic::stack::scale(const g2d::math::size2dd& scale)
{
	this->_scale = scale;
}

void g2d::graphic::stack::scale(double w, double h)
{
	this->_scale.set(w, h);
}

void g2d::graphic::stack::scale(double scale)
{
	this->_scale = scale;
}

void g2d::graphic::stack::scale_w(double w)
{
	this->_scale.w(w);
}

void g2d::graphic::stack::scale_h(double h)
{
	this->_scale.h(h);
}

void g2d::graphic::stack::animation(const std::string& animation)
{
	auto it = this->_animations.find(animation);

	if (it == this->_animations.end())
	{
		std::cerr << "Can not find animation: '" << animation << "', failed" << std::endl;

		exit(EXIT_FAILURE);
	}

	this->_animation = this->_animations[animation];
}

void g2d::graphic::stack::append_color(const g2d::math::color& color)
{
	this->_color += color;
}

void g2d::graphic::stack::append_color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	this->_color += g2d::math::color(r, g, b, a);
}

void g2d::graphic::stack::append_color(std::uint8_t color)
{
	this->_color += color;
}

void g2d::graphic::stack::append_color_r(std::uint8_t r)
{
	this->_color.r(this->_color.r() + r);
}

void g2d::graphic::stack::append_color_g(std::uint8_t g)
{
	this->_color.g(this->_color.g() + g);
}

void g2d::graphic::stack::append_color_b(std::uint8_t b)
{
	this->_color.b(this->_color.b() + b);
}

void g2d::graphic::stack::append_color_a(std::uint8_t a)
{
	this->_color.a(this->_color.a() + a);
}

void g2d::graphic::stack::append_pivot(const g2d::math::point2dd& pivot)
{
	this->_pivot += pivot;
}

void g2d::graphic::stack::append_pivot(double x, double y)
{
	this->_pivot += g2d::math::point2dd(x, y);
}

void g2d::graphic::stack::append_pivot(double pivot)
{
	this->_pivot += pivot;
}

void g2d::graphic::stack::append_pivot_x(double x)
{
	this->_pivot.x(this->_pivot.x() + x);
}

void g2d::graphic::stack::append_pivot_y(double y)
{
	this->_pivot.y(this->_pivot.y() + y);
}

void g2d::graphic::stack::append_position(const g2d::math::point3dd& position)
{
	this->_position += position;
}

void g2d::graphic::stack::append_position(double x, double y, double z)
{
	this->_position += g2d::math::point3dd(x, y, z);
}

void g2d::graphic::stack::append_position(double position)
{
	this->_position += position;
}

void g2d::graphic::stack::append_position_x(double x)
{
	this->_position.x(this->_position.x() + x);
}

void g2d::graphic::stack::append_position_y(double y)
{
	this->_position.y(this->_position.y() + y);
}

void g2d::graphic::stack::append_position_z(double z)
{
	this->_position.z(this->_position.z() + z);
}

void g2d::graphic::stack::append_rotate(const g2d::math::rotated& rotate)
{
	this->_rotate += rotate;
}

void g2d::graphic::stack::append_rotate(double h, double p, double b)
{
	this->_rotate += g2d::math::rotated(h, p, b);
}

void g2d::graphic::stack::append_rotate(double rotate)
{
	this->_rotate += rotate;
}

void g2d::graphic::stack::append_rotate_h(double h)
{
	this->_rotate.h(this->_rotate.h() + h);
}

void g2d::graphic::stack::append_rotate_p(double p)
{
	this->_rotate.p(this->_rotate.p() + p);
}

void g2d::graphic::stack::append_rotate_b(double b)
{
	this->_rotate.b(this->_rotate.b() + b);
}

void g2d::graphic::stack::append_scale(const g2d::math::size2dd& scale)
{
	this->_scale += scale;
}

void g2d::graphic::stack::append_scale(double w, double h)
{
	this->_scale += g2d::math::size2dd(w, h);
}

void g2d::graphic::stack::append_scale(double scale)
{
	this->_scale += scale;
}

void g2d::graphic::stack::append_scale_w(double w)
{
	this->_scale.w(this->_scale.w() + w);
}

void g2d::graphic::stack::append_scale_h(double h)
{
	this->_scale.h(this->_scale.h() + h);
}

bool g2d::graphic::stack::visible() const
{
	return this->_visible;
}

bool g2d::graphic::stack::wireframe() const
{
	return this->_wireframe;
}

bool g2d::graphic::stack::verbose() const
{
	return this->_verbose;
}

std::size_t g2d::graphic::stack::length() const
{
	return this->_length;
}

const std::string& g2d::graphic::stack::filename() const
{
	assert(this->_index < this->_identity.size() && this->_identity.size() != 0);

	return this->_filename[this->_index];
}

const g2d::graphic::flip& g2d::graphic::stack::flip() const
{
	return this->_flip;
}

const g2d::math::color& g2d::graphic::stack::color() const
{
	return this->_color;
}

const g2d::math::point2dd& g2d::graphic::stack::pivot() const
{
	return this->_pivot;
}

const g2d::math::point3dd& g2d::graphic::stack::position() const
{
	return this->_position;
}

const g2d::math::rotated& g2d::graphic::stack::rotate() const
{
	return this->_rotate;
}

const g2d::math::size2dd& g2d::graphic::stack::size() const
{
	assert(this->_index < this->_identity.size() && this->_identity.size() != 0);

	return this->_size[this->_index];
}

const g2d::math::size2dd& g2d::graphic::stack::scale() const
{
	return this->_scale;
}

g2d::animation::tweener* g2d::graphic::stack::animation() const
{
	return this->_animation;
}

void g2d::graphic::stack::mapping()
{
	assert(this->_index < this->_identity.size() && this->_identity.size() != 0);

	double x = g2d::math::invert(this->_size[this->_index].w() * this->_pivot.x());
	double y = g2d::math::invert(this->_size[this->_index].h() * this->_pivot.y());
	double w = x + this->_size[this->_index].w();
	double h = y + this->_size[this->_index].h();

	this->_vertex.a(x, y, 0.0);
	this->_vertex.b(w, y, 0.0);
	this->_vertex.c(w, h, 0.0);
	this->_vertex.d(x, h, 0.0);
}

void g2d::graphic::stack::bind(const g2d::graphic::filter& filter, const g2d::graphic::wrap& wrap)
{
	GLenum error = glGetError();

	assert(this->_index < this->_identity.size() && this->_identity.size() != 0);

	glBindTexture(GL_TEXTURE_2D, this->_identity[this->_index]);

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

