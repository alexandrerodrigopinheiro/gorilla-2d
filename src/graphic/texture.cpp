#include "../../includes/graphic/texture.h"

g2d::graphic::texture::texture()
	: _identity(0)
	, _filename(std::string())
	, _size(g2d::math::size2dd(0.0))
{
}

g2d::graphic::texture::~texture()
{
	this->destroy();
}

bool g2d::graphic::texture::initialize(const std::string& filename, bool verbose)
{
	SDL_Surface* image = nullptr;

	image = IMG_Load(filename.c_str());

	if (image == nullptr)
	{
		std::cerr << "Cannot load texture '" << filename << "', failed." << std::endl;

		return false;
	}

	if (verbose)
	{
		std::clog << "Loading texture '" << filename << "', OK. -- " << static_cast<int>(image->format->BitsPerPixel) << " bpp" << std::endl;
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

	this->_size.set(static_cast<double>(image->w), static_cast<double>(image->h));

	this->_filename = filename;

	SDL_FreeSurface(image);

	return true;
}

void g2d::graphic::texture::destroy()
{
	this->_filename.clear();

	glDeleteTextures(1, &this->_identity);
}

uint g2d::graphic::texture::identity() const
{
	return this->_identity;
}

const std::string& g2d::graphic::texture::filename() const
{
	return this->_filename;
}

const g2d::math::size2dd& g2d::graphic::texture::size() const
{
	return this->_size;
}
