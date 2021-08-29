template<class Serialize>
inline g2d::core::gorilla2d<Serialize>::gorilla2d(int argc, char **argv)
	: _verbose(false)
	, _window(nullptr)
	, _render(nullptr)
	, _camera(nullptr)
	, _charger(nullptr)
	, _scene_manager(nullptr)
	, _event_manager(nullptr)
	, _audio_manager(nullptr)
	, _texture_manager(nullptr)
	, _graphic_manager(nullptr)
	, _serialize(nullptr)
	, _scene(nullptr)
	, _hertz(nullptr)
	, _ruler(nullptr)
	, _pointer(nullptr)
	, _frame_rate(nullptr)
{
	g2d::basic::unused(argc, argv);
}

template<class Serialize>
inline g2d::core::gorilla2d<Serialize>::~gorilla2d()
{
	this->destroy();
}

template<class Serialize>
inline bool g2d::core::gorilla2d<Serialize>::initialize(const std::string& caption, int x, int y, int width, int height, std::size_t fps, bool fullscreen, bool verbose)
{
	this->_window = new g2d::core::window();
	this->_render = new g2d::core::render();
	this->_camera = new g2d::core::camera();
	this->_charger = new g2d::core::charger();
	this->_event_manager = new g2d::event::event_manager();
	this->_scene_manager = new g2d::scene::scene_manager<Serialize>();
	this->_audio_manager = new g2d::audio::audio_manager();
	this->_texture_manager = new g2d::graphic::texture_manager();
	this->_graphic_manager = new g2d::graphic::graphic_manager();
	this->_hertz = new g2d::clock::hertz();
	this->_ruler = new g2d::gui::ruler();
	this->_pointer = new g2d::gui::hud();
	this->_frame_rate = new g2d::gui::hud();
	this->_verbose = verbose;

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	if (!SDL_WasInit(SDL_INIT_VIDEO))
	{
		std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;

		return false;
	}

	if (!TTF_WasInit())
	{
		std::cerr << "TTF could not initialize! SDL Error: " << SDL_GetError() << std::endl;

		return false;
	}

	if (!this->_window->initialize(caption.c_str(), x, y, width, height, fullscreen))
	{
		std::cerr << "Window could not initialize!" << std::endl;

		return false;
	}

	if (!this->_render->initialize())
	{
		std::cerr << "Render could not initialize!" << std::endl;

		return false;
	}

	if (!this->_camera->initialize("camera", x, y, width, height))
	{
		std::cerr << "Camera could not initialize!" << std::endl;

		return false;
	}

	if (!this->_event_manager->initialize(this->_verbose))
	{
		std::cerr << "Event manager could not initialize!" << std::endl;

		return false;
	}

	if (!this->_charger->initialize())
	{
		std::cerr << "Charge could not initialize!" << std::endl;

		return false;
	}

#if 0
	const int AUDIO_FREQUENCY  = 22050;
	const int AUDIO_CHANNELS   = 2;
	const int AUDIO_CHUNK_SIZE = 4096;
#else
	const int AUDIO_FREQUENCY  = 44100;
	const int AUDIO_CHANNELS   = 2;
	const int AUDIO_CHUNK_SIZE = 2048;
#endif

	if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, AUDIO_CHANNELS, AUDIO_CHUNK_SIZE) == -1)
	{
		std::cerr << "Audio could not initialize!" << std::endl;

		return false;
	}

	if (!this->_hertz->initialize(fps == 0 ? g2d::clock::HERTZ : fps))
	{
		std::cerr << "Charge could not heartz!" << std::endl;

		return false;
	}

	if (!this->_ruler->initialize(width, height))
	{
		std::cerr << "Charge could not rules!" << std::endl;

		return false;
	}

	if (!this->_pointer->initialize("./assets/extra/system.ttf", 10, 100.0, 15.0, this->_verbose))
	{
		std::cerr << "Charge could not pointer!" << std::endl;

		return false;
	}

	if (!this->_frame_rate->initialize("./assets/extra/system.ttf", 10, 65.0, 15.0, this->_verbose))
	{
		std::cerr << "Charge could not frame rate!" << std::endl;

		return false;
	}

	if (this->_verbose)
	{
		SDL_ShowCursor(1);
	}

	return true;
}

template<class Serialize>
inline void g2d::core::gorilla2d<Serialize>::destroy()
{
	delete this->_window;
	delete this->_render;
	delete this->_camera;
	delete this->_charger;
	delete this->_scene_manager;
	delete this->_event_manager;
	delete this->_audio_manager;
	delete this->_texture_manager;
	delete this->_graphic_manager;
	delete this->_serialize;
	delete this->_hertz;
	delete this->_ruler;
	delete this->_pointer;
	delete this->_frame_rate;

	this->_window = nullptr;
	this->_render = nullptr;
	this->_camera = nullptr;
	this->_charger = nullptr;
	this->_scene_manager = nullptr;
	this->_event_manager = nullptr;
	this->_audio_manager = nullptr;
	this->_texture_manager = nullptr;
	this->_graphic_manager = nullptr;
	this->_serialize = nullptr;
	this->_hertz = nullptr;
	this->_ruler = nullptr;
	this->_pointer = nullptr;
	this->_frame_rate = nullptr;

	Mix_CloseAudio();

	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

template<class Serialize>
inline bool g2d::core::gorilla2d<Serialize>::serialize(Serialize* serialize)
{
	Serialize* copy = serialize;

	this->_serialize = copy;

	if (this->_serialize == nullptr)
	{
		return false;
	}

	return true;
}

template<class Serialize>
inline bool g2d::core::gorilla2d<Serialize>::scene(const std::initializer_list<g2d::core::scene<Serialize>>& scenes)
{
	for (auto scene : scenes)
	{
		g2d::scene::scene<Serialize>* copy = scene.scene;

		if (!this->_scene_manager->attach(scene.identity, copy))
		{
			return false;
		}
	}

	return true;
}

template<class Serialize>
inline bool g2d::core::gorilla2d<Serialize>::texture(const std::initializer_list<g2d::core::texture>& textures)
{
	for (auto texture : textures)
	{
		if (!this->_texture_manager->texture(texture.identity, texture.filename, this->_verbose ? this->_verbose : texture.verbose))
		{
			return false;
		}
	}

	return true;
}

template<class Serialize>
inline bool g2d::core::gorilla2d<Serialize>::emitter(const std::initializer_list<g2d::core::emitter>& emitters)
{
	for (auto emitter : emitters)
	{
		if (!this->_graphic_manager->emitter(emitter.identity, emitter.filename, emitter.emission, emitter.amount, this->_verbose ? this->_verbose : emitter.verbose))
		{
			return false;
		}
	}

	return true;
}

template<class Serialize>
inline bool g2d::core::gorilla2d<Serialize>::shape(const std::initializer_list<g2d::core::shape>& shapes)
{
	for (auto shape : shapes)
	{
		if (!this->_graphic_manager->shape(shape.identity, shape.width, shape.height, shape.dots, shape.form, this->_verbose ? this->_verbose : shape.verbose))
		{
			return false;
		}
	}

	return true;
}

template<class Serialize>
inline bool g2d::core::gorilla2d<Serialize>::sprite(const std::initializer_list<g2d::core::sprite>& sprites)
{
	for (auto sprite : sprites)
	{
		if (!this->_graphic_manager->sprite(sprite.identity, sprite.filename, sprite.columns, sprite.rows, sprite.frames, this->_verbose ? this->_verbose : sprite.verbose))
		{
			return false;
		}
	}

	return true;
}

template<class Serialize>
inline bool g2d::core::gorilla2d<Serialize>::stack(const std::initializer_list<g2d::core::stack>& stacks)
{
	for (auto stack : stacks)
	{
		if (!this->_graphic_manager->stack(stack.identity, stack.filename, this->_verbose ? this->_verbose : stack.verbose))
		{
			return false;
		}
	}

	return true;
}

template<class Serialize>
inline bool g2d::core::gorilla2d<Serialize>::video(const std::initializer_list<g2d::core::video>& videos)
{
	for (auto video : videos)
	{
		if (!this->_graphic_manager->video(video.identity, video.filename, this->_verbose ? this->_verbose : video.verbose))
		{
			return false;
		}
	}

	return true;
}

template<class Serialize>
inline bool g2d::core::gorilla2d<Serialize>::text(const std::initializer_list<g2d::core::text>& texts)
{
	for (auto text : texts)
	{
		if (!this->_graphic_manager->text(text.identity, text.filename, text.measure, this->_verbose ? this->_verbose : text.verbose))
		{
			return false;
		}
	}

	return true;
}

template<class Serialize>
inline bool g2d::core::gorilla2d<Serialize>::sound(const std::initializer_list<g2d::core::sound>& sounds)
{
	for (auto sound : sounds)
	{
		if (!this->_audio_manager->sound(sound.identity, sound.filename, this->_verbose ? this->_verbose : sound.verbose))
		{
			return false;
		}
	}

	return true;
}

template<class Serialize>
inline bool g2d::core::gorilla2d<Serialize>::music(const std::initializer_list<g2d::core::music>& musics)
{
	for (auto music : musics)
	{
		if (!this->_audio_manager->music(music.identity, music.filename, this->_verbose ? this->_verbose : music.verbose))
		{
			return false;
		}
	}

	return true;
}

template<class Serialize>
inline void g2d::core::gorilla2d<Serialize>::charger(std::size_t first_scene)
{
	std::size_t size = this->_graphic_manager->size() + this->_audio_manager->size() + this->_scene_manager->size();

	this->_charger->size(size);

	while (this->_window->open() && this->_charger->open())
	{
		this->_charger->update();
		this->_render->refresh();
		this->_window->render();
		this->_camera->render();
		this->_charger->render();
		this->_window->refrash();
		this->_hertz->synchronize();
	}

	this->_scene_manager->set(this->_serialize, this->_scene_manager, this->_texture_manager, this->_graphic_manager, this->_audio_manager);
	this->_scene_manager->change(first_scene);
	this->_charger->destroy();
}

template<class Serialize>
inline void g2d::core::gorilla2d<Serialize>::running()
{
	while (this->_window->open() && this->_event_manager->opened())
	{
		this->resolve();
		this->_event_manager->listener();
		this->_scene->keyboard(this->_event_manager->keyoard());
		this->_scene->mouse(this->_event_manager->mouse());
		this->_scene->touch(this->_event_manager->touch());
		this->_scene->update();
		this->_render->refresh();
		this->_window->render();
		this->_camera->render();
		this->_scene->render();
		this->_event_manager->render();
		this->_scene->wipeup();
		this->ruler();
		this->_window->refrash();
		this->_event_manager->release();
		this->_hertz->synchronize();
	}
}

template<class Serialize>
inline void g2d::core::gorilla2d<Serialize>::resolve()
{
	if (this->_scene_manager->change())
	{
		if (this->_scene_manager->last_scene() != 0)
		{
			this->_serialize->save();

			this->_scene->disappear();
		}

		this->_scene = this->_scene_manager->scene();

		this->_serialize->load();

	    this->_scene->appear();

		this->_scene_manager->update();
	}
}

template<class Serialize>
inline void g2d::core::gorilla2d<Serialize>::verbose(bool verbose)
{
	this->_verbose = verbose;
	SDL_ShowCursor(this->_verbose ? 1 : -1);
}

template<class Serialize>
inline bool g2d::core::gorilla2d<Serialize>::verbose() const
{
	return this->_verbose;
}

template<class Serialize>
inline void g2d::core::gorilla2d<Serialize>::ruler()
{
	if (this->_verbose)
	{
		int x;
		int y;

		SDL_GetMouseState(&x, &y);

		this->_frame_rate->content("FPS: " + std::to_string(this->_hertz->frequency()));
		this->_pointer->content("X: " + std::to_string(x) + " Y: " + std::to_string(y));

		this->_frame_rate->position(10.0, 10.0, 0.0);
		this->_pointer->position(static_cast<double>(x), static_cast<double>(y), 0.0);

		this->_ruler->draw();
		this->_frame_rate->draw();
		this->_pointer->draw();
	}
}
