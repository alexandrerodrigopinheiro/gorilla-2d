#include "../../includes/core/render.h"

g2d::core::render::render()
{
}

g2d::core::render::~render()
{
}

bool g2d::core::render::initialize()
{
	GLenum error = GL_NO_ERROR;

	glShadeModel(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_MULTISAMPLE);
//	glEnable(GL_CULL_FACE);

	glDisable(GL_CULL_FACE);
//	glDisable(GL_BLEND);

	glAlphaFunc(GL_NOTEQUAL, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
//	glDepthFunc(GL_LESS);

	glFrontFace(GL_CW);
	glCullFace(GL_BACK);

	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClearDepth(1.0);

	error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error initializing OpenGL! " << gluErrorString(error) << std::endl;

		return false;
	}

	int max_texture;

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_texture);

	std::clog << "Size supported texture maximum " << max_texture << "x" << max_texture << ", info." << std::endl;

	return this->attribute();
}

bool g2d::core::render::attribute()
{
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

	// Turn on double buffering with a 24bit Z buffer.
	// You may need to change this to 16 or 32 for your system
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	int major_version = 0;
	int minor_version = 0;

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major_version);
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor_version);

	if (major_version >= 3)
	{
		// SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are disabled
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_MULTISAMPLESAMPLES, 2);

		int buffers;
		int samples;

		SDL_GL_GetAttribute(SDL_GLattr::SDL_GL_MULTISAMPLEBUFFERS, &buffers);
		SDL_GL_GetAttribute(SDL_GLattr::SDL_GL_MULTISAMPLESAMPLES, &samples);

		/* samples (2, 4, or 8 is about it) */
		if (buffers == 0 || samples == 0)
		{
			std::clog << "Could not create FSAA buffers '" << buffers << "' - samples '" << samples << "', failed." << std::endl;
		}

	}

	std::clog << "GL major version '" << major_version << "' and minor version '" << minor_version << "', info." << std::endl;

	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_ACCELERATED_VISUAL, 1);

	int acceleration;
	SDL_GL_GetAttribute(SDL_GLattr::SDL_GL_ACCELERATED_VISUAL, &acceleration);

	if (acceleration <= 0)
	{
		std::clog << "Could not be initialized video acceleration', info." << std::endl;
	}
	else
	{
		std::clog << "Video acceleration initialized, info." << std::endl;
	}

	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_ACCUM_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_ACCUM_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_ACCUM_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_ACCUM_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_MULTISAMPLESAMPLES, 2);

	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		std::clog << "Could not create VSYNC, failed." << std::endl;

		return false;
	}

	return true;
}

void g2d::core::render::refresh(const g2d::math::color& color)
{
	glClearColor(color.normal_r(), color.normal_g(), color.normal_b(), 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

