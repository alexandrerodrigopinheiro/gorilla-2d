template<class Serialize>
inline g2d::scene::scene_manager<Serialize>::scene_manager()
	: _change(false)
	, _last_scene(0)
	, _current_scene(0)
	, _scene(std::unordered_map<std::size_t, g2d::scene::scene<Serialize>*>())
{
}

template<class Serialize>
inline g2d::scene::scene_manager<Serialize>::~scene_manager()
{
	this->destroy();
}

template<class Serialize>
inline void g2d::scene::scene_manager<Serialize>::destroy()
{
	for (auto& arg : this->_scene)
	{
		delete arg.second;
	}
}

template<class Serialize>
inline bool g2d::scene::scene_manager<Serialize>::attach(std::size_t identity, g2d::scene::scene<Serialize>* scene)
{
    auto search = this->_scene.find(identity);

    if (search != this->_scene.end())
    {
    	std::clog << "Repeated identity: '" << identity << "',failed" << std::endl;

    	return false;
    }

	g2d::scene::scene<Serialize>* copy = scene;

	this->_scene.insert(std::make_pair(identity, copy));

	return true;
}

template<class Serialize>
inline bool g2d::scene::scene_manager<Serialize>::detach(std::size_t identity)
{
    auto search = this->_scene.find(identity);

    if (search != this->_scene.end())
    {
		this->_scene.erase(search);

		return true;
    }

	return false;
}

template<class Serialize>
inline bool g2d::scene::scene_manager<Serialize>::change(std::size_t identity)
{
	auto search = this->_scene.find(identity);

	if (search == this->_scene.end())
	{
		return false;
	}

	this->_last_scene = this->_current_scene != 0 ? this->_current_scene : this->_last_scene;

	this->_current_scene = identity;
	this->_change = true;

	return true;
}

template<class Serialize>
inline bool g2d::scene::scene_manager<Serialize>::change() const
{
    return this->_change;
}

template<class Serialize>
inline void g2d::scene::scene_manager<Serialize>::set(Serialize* serialize, g2d::scene::scene_manager<Serialize>* scene_manager, g2d::graphic::texture_manager* texture_manager, g2d::graphic::graphic_manager* graphic_manager, g2d::audio::audio_manager* audio_manager)
{
	for (auto scene : this->_scene)
	{
	    if (!scene.second->initialize(serialize, scene_manager, texture_manager, graphic_manager, audio_manager))
	    {
			std::cerr << "Cannot initialize scene, failed." << std::endl;

	    	exit(EXIT_FAILURE);
	    }
	}
}

template<class Serialize>
inline void g2d::scene::scene_manager<Serialize>::update()
{
    this->_change = false;
}

template<class Serialize>
inline std::size_t g2d::scene::scene_manager<Serialize>::last_scene() const
{
	return this->_last_scene;
}

template<class Serialize>
inline std::size_t g2d::scene::scene_manager<Serialize>::current_scene() const
{
	return this->_current_scene;
}

template<class Serialize>
inline g2d::scene::scene<Serialize>* g2d::scene::scene_manager<Serialize>::scene() const
{
    auto search = this->_scene.find(this->_current_scene);

    assert(search != this->_scene.end());

    return this->_scene.at(this->_current_scene);
}

template<class Serialize>
inline std::size_t g2d::scene::scene_manager<Serialize>::size() const
{
    return this->_scene.size();
}
