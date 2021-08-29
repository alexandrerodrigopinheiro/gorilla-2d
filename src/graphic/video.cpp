#include "../../includes/graphic/video.h"

g2d::graphic::video::video()
	: _video(nullptr)
	, _run(true)
	, _visible(true)
	, _wireframe(false)
	, _verbose(false)
	, _frame(cv::Mat())
	, _identity(0)
	, _filename(std::string())
	, _flip(g2d::graphic::flip::flip_none)
	, _color(g2d::math::color(255))
	, _pivot(g2d::math::point2dd(0.0))
	, _position(g2d::math::point3dd(0.0))
	, _rotate(g2d::math::rotated(0.0))
	, _size(g2d::math::size2dd(0.0))
	, _scale(g2d::math::size2dd(1.0))
	, _offset(g2d::math::squared(0.0))
	, _vertex(g2d::math::vertexd(0.0))
	, _uvmap(g2d::math::uvmapd(1.0))
{
}

g2d::graphic::video::~video()
{
	this->destroy();
}

bool g2d::graphic::video::initialize(const std::string& filename, bool verbose)
{
	this->_video = new cv::VideoCapture();

	if (filename.find_first_not_of("0123456789") == std::string::npos)
	{
		int device = std::stoi(filename);

		if (!this->_video->open(device))
		{
			return false;
		}

		this->_verbose = verbose;

		if (this->_verbose)
		{
			std::clog << "Loading video '/dev/video" << filename << "', OK." << std::endl;
		}
	}
	else
	{
		if (!this->_video->open(filename))
		{
			return false;
		}

		this->_verbose = verbose;

		if (this->_verbose)
		{
			std::clog << "Loading video '" << filename << "', OK." << std::endl;
		}
	}

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

	return true;
}

void g2d::graphic::video::destroy()
{
	glDeleteTextures(1, &this->_identity);

	this->_video->release();

	delete this->_video;

	this->_video = nullptr;
}

void g2d::graphic::video::draw()
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

void g2d::graphic::video::play()
{
	this->_run = true;
}

void g2d::graphic::video::pause()
{
	this->_run = false;
}

bool g2d::graphic::video::played() const
{
	return this->_run;
}

bool g2d::graphic::video::onset() const
{
	return static_cast<std::size_t>(this->_video->get(CV_CAP_PROP_POS_FRAMES)) == 0;
}

bool g2d::graphic::video::bound() const
{
	return static_cast<std::size_t>(this->_video->get(CV_CAP_PROP_POS_FRAMES)) == static_cast<std::size_t>(this->_video->get(CV_CAP_PROP_FRAME_COUNT));
}

bool g2d::graphic::video::shoot(const std::string& path)
{
	return cv::imwrite(path, this->_frame);
}

void g2d::graphic::video::visible(bool visible)
{
	this->_visible = visible;
}

void g2d::graphic::video::wireframe(bool wireframe)
{
	this->_wireframe = wireframe;
}

void g2d::graphic::video::verbose(bool verbose)
{
	this->_verbose = verbose;
}

void g2d::graphic::video::flip(const g2d::graphic::flip& flip)
{
	this->_flip = flip;
}

void g2d::graphic::video::color(const g2d::math::color& color)
{
	this->_color = color;
}

void g2d::graphic::video::color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	this->_color.set(r, g, b, a);
}

void g2d::graphic::video::color(std::uint8_t color)
{
	this->_color = color;
}

void g2d::graphic::video::color_r(std::uint8_t r)
{
	this->_color.r(r);
}

void g2d::graphic::video::color_g(std::uint8_t g)
{
	this->_color.g(g);
}

void g2d::graphic::video::color_b(std::uint8_t b)
{
	this->_color.b(b);
}

void g2d::graphic::video::color_a(std::uint8_t a)
{
	this->_color.a(a);
}

void g2d::graphic::video::pivot(const g2d::math::point2dd& pivot)
{
	this->_pivot = pivot;
}

void g2d::graphic::video::pivot(double x, double y)
{
	this->_pivot.set(x, y);
}

void g2d::graphic::video::pivot(double pivot)
{
	this->_pivot = pivot;
}

void g2d::graphic::video::pivot_x(double x)
{
	this->_pivot.x(x);
}

void g2d::graphic::video::pivot_y(double y)
{
	this->_pivot.y(y);
}

void g2d::graphic::video::position(const g2d::math::point3dd& position)
{
	this->_position = position;
}

void g2d::graphic::video::position(double x, double y, double z)
{
	this->_position = g2d::math::point3dd(x, y, z);
}

void g2d::graphic::video::position(double position)
{
	this->_position = position;
}

void g2d::graphic::video::position_x(double x)
{
	this->_position.x(x);
}

void g2d::graphic::video::position_y(double y)
{
	this->_position.y(y);
}

void g2d::graphic::video::position_z(double z)
{
	this->_position.z(z);
}

void g2d::graphic::video::rotate(const g2d::math::rotated& rotate)
{
	this->_rotate = rotate;
}

void g2d::graphic::video::rotate(double h, double p, double b)
{
	this->_rotate.set(h, p, b);
}

void g2d::graphic::video::rotate(double rotate)
{
	this->_rotate = rotate;
}

void g2d::graphic::video::rotate_h(double h)
{
	this->_rotate.h(h);
}

void g2d::graphic::video::rotate_p(double p)
{
	this->_rotate.p(p);
}

void g2d::graphic::video::rotate_b(double b)
{
	this->_rotate.b(b);
}

void g2d::graphic::video::scale(const g2d::math::size2dd& scale)
{
	this->_scale = scale;
}

void g2d::graphic::video::scale(double w, double h)
{
	this->_scale.set(w, h);
}

void g2d::graphic::video::scale(double scale)
{
	this->_scale = scale;
}

void g2d::graphic::video::scale_w(double w)
{
	this->_scale.w(w);
}

void g2d::graphic::video::scale_h(double h)
{
	this->_scale.h(h);
}

void g2d::graphic::video::append_color(const g2d::math::color& color)
{
	this->_color += color;
}

void g2d::graphic::video::append_color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	this->_color += g2d::math::color(r, g, b, a);
}

void g2d::graphic::video::append_color(std::uint8_t color)
{
	this->_color += color;
}

void g2d::graphic::video::append_color_r(std::uint8_t r)
{
	this->_color.r(this->_color.r() + r);
}

void g2d::graphic::video::append_color_g(std::uint8_t g)
{
	this->_color.g(this->_color.g() + g);
}

void g2d::graphic::video::append_color_b(std::uint8_t b)
{
	this->_color.b(this->_color.b() + b);
}

void g2d::graphic::video::append_color_a(std::uint8_t a)
{
	this->_color.a(this->_color.a() + a);
}

void g2d::graphic::video::append_pivot(const g2d::math::point2dd& pivot)
{
	this->_pivot += pivot;
}

void g2d::graphic::video::append_pivot(double x, double y)
{
	this->_pivot += g2d::math::point2dd(x, y);
}

void g2d::graphic::video::append_pivot(double pivot)
{
	this->_pivot += pivot;
}

void g2d::graphic::video::append_pivot_x(double x)
{
	this->_pivot.x(this->_pivot.x() + x);
}

void g2d::graphic::video::append_pivot_y(double y)
{
	this->_pivot.y(this->_pivot.y() + y);
}

void g2d::graphic::video::append_position(const g2d::math::point3dd& position)
{
	this->_position += position;
}

void g2d::graphic::video::append_position(double x, double y, double z)
{
	this->_position += g2d::math::point3dd(x, y, z);
}

void g2d::graphic::video::append_position(double position)
{
	this->_position += position;
}

void g2d::graphic::video::append_position_x(double x)
{
	this->_position.x(this->_position.x() + x);
}

void g2d::graphic::video::append_position_y(double y)
{
	this->_position.y(this->_position.y() + y);
}

void g2d::graphic::video::append_position_z(double z)
{
	this->_position.z(this->_position.z() + z);
}

void g2d::graphic::video::append_rotate(const g2d::math::rotated& rotate)
{
	this->_rotate += rotate;
}

void g2d::graphic::video::append_rotate(double h, double p, double b)
{
	this->_rotate += g2d::math::rotated(h, p, b);
}

void g2d::graphic::video::append_rotate(double rotate)
{
	this->_rotate += rotate;
}

void g2d::graphic::video::append_rotate_h(double h)
{
	this->_rotate.h(this->_rotate.h() + h);
}

void g2d::graphic::video::append_rotate_p(double p)
{
	this->_rotate.p(this->_rotate.p() + p);
}

void g2d::graphic::video::append_rotate_b(double b)
{
	this->_rotate.b(this->_rotate.b() + b);
}

void g2d::graphic::video::append_scale(const g2d::math::size2dd& scale)
{
	this->_scale += scale;
}

void g2d::graphic::video::append_scale(double w, double h)
{
	this->_scale += g2d::math::size2dd(w, h);
}

void g2d::graphic::video::append_scale(double scale)
{
	this->_scale += scale;
}

void g2d::graphic::video::append_scale_w(double w)
{
	this->_scale.w(this->_scale.w() + w);
}

void g2d::graphic::video::append_scale_h(double h)
{
	this->_scale.h(this->_scale.h() + h);
}

bool g2d::graphic::video::visible() const
{
	return this->_visible;
}

bool g2d::graphic::video::wireframe() const
{
	return this->_wireframe;
}

bool g2d::graphic::video::verbose() const
{
	return this->_verbose;
}

const cv::Mat& g2d::graphic::video::frame() const
{
	return this->_frame;
}

double g2d::graphic::video::moment() const
{
	return this->_video->get(CV_CAP_PROP_POS_MSEC);
}

std::size_t g2d::graphic::video::current() const
{
	return static_cast<std::size_t>(this->_video->get(CV_CAP_PROP_POS_FRAMES));
}

std::size_t g2d::graphic::video::length() const
{
	return static_cast<std::size_t>(this->_video->get(CV_CAP_PROP_FRAME_COUNT));
}

const std::string& g2d::graphic::video::filename() const
{
	return this->_filename;
}

const g2d::graphic::flip& g2d::graphic::video::flip() const
{
	return this->_flip;
}

const g2d::math::color& g2d::graphic::video::color() const
{
	return this->_color;
}

const g2d::math::point2dd& g2d::graphic::video::pivot() const
{
	return this->_pivot;
}

const g2d::math::point3dd& g2d::graphic::video::position() const
{
	return this->_position;
}

const g2d::math::rotated& g2d::graphic::video::rotate() const
{
	return this->_rotate;
}

const g2d::math::size2dd& g2d::graphic::video::size() const
{
	return this->_size;
}

const g2d::math::size2dd& g2d::graphic::video::scale() const
{
	return this->_scale;
}

void g2d::graphic::video::bind(const g2d::graphic::filter& filter, const g2d::graphic::wrap& wrap)
{
	GLenum error = glGetError();

	glBindTexture(GL_TEXTURE_2D, this->_identity);

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "Cannot filter identity: '" << gluErrorString(error) << "', failed" << std::endl;
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
	}
}

void g2d::graphic::video::mapping()
{
	if (!this->_run)
	{
		return;
	}

	cv::Mat image;

	if (this->_video->read(image))
	{
		if (image.empty())
		{
			std::cerr << "Cannot transport video, failed" << std::endl;

			exit(EXIT_FAILURE);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, this->_identity);

			GLint internal_format = 0;
			GLint format = 0;

			switch (image.channels())
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
					internal_format = GL_BGR;
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

			glPixelStorei(GL_UNPACK_ALIGNMENT, image.cols % 4 == 0 ? 4 : 1);
			glTexImage2D(GL_TEXTURE_2D, 0, format, image.cols, image.rows, 0, internal_format, GL_UNSIGNED_BYTE, (void *) image.ptr());

			// calculates the dimensions of the polygon.
			this->_size.w(static_cast<double>(image.cols));
			this->_size.h(static_cast<double>(image.rows));

			double x = g2d::math::invert(this->_size.w() * this->_pivot.x());
			double y = g2d::math::invert(this->_size.h() * this->_pivot.y());
			double w = x + this->_size.w();
			double h = y + this->_size.h();

			this->_vertex.a(x, y, 0.0);
			this->_vertex.b(w, y, 0.0);
			this->_vertex.c(w, h, 0.0);
			this->_vertex.d(x, h, 0.0);

			this->_frame = image;
		}
	}
}
