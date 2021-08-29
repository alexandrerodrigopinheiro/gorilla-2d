#include "../../includes/core/window.h"

g2d::core::window::window()
	: _open(false)
	, _window(nullptr)
	, _context(nullptr)
{
}

g2d::core::window::~window()
{
	this->destroy();
}

bool g2d::core::window::initialize(const std::string& caption, int x, int y, int width, int height, bool fullscreen)
{
	Uint32 flag = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS;

	if (fullscreen)
	{
		flag |= SDL_WINDOW_FULLSCREEN;
	}

	this->_window = SDL_CreateWindow(caption.c_str(), x, y, width, height, flag);

	if (this->_window == nullptr)
	{
		std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;

		return false;
	}

	this->_context = SDL_GL_CreateContext(this->_window);

	if (this->_context == nullptr)
	{
		std::cerr << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;

		return false;
	}

	if (!this->attribute())
	{
		std::cerr << "Unable to initialize OpenGL!" << std::endl;

		return false;
	}

	this->_open = true;

	return true;
}

void g2d::core::window::destroy()
{
	SDL_GL_DeleteContext(this->_context);
	SDL_DestroyWindow(this->_window);

	this->_context = nullptr;
	this->_window = nullptr;
}

void g2d::core::window::render()
{
	SDL_GL_MakeCurrent(this->_window, this->_context);
}

void g2d::core::window::refrash()
{
	SDL_GL_SwapWindow(this->_window);
}

bool g2d::core::window::open() const
{
	return this->_open;
}

bool g2d::core::window::attribute()
{
	GLenum error = GL_NO_ERROR;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error initializing OpenGL! " << gluErrorString(error) << std::endl;

		return false;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error initializing OpenGL! " << gluErrorString(error) << std::endl;

		return false;
	}

	glClearColor(0.f, 0.f, 0.f, 1.f);

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error initializing OpenGL! " << gluErrorString(error) << std::endl;

		return false;
	}

	return true;
}
