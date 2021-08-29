template<class Serialize>
inline g2d::scene::scene<Serialize>::scene()
	: _serialize(nullptr)
	, _scene_manager(nullptr)
	, _texture_manager(nullptr)
	, _graphic_manager(nullptr)
	, _audio_manager(nullptr)
{
}

template<class Serialize>
inline g2d::scene::scene<Serialize>::~scene()
{
	this->_serialize = nullptr;
	this->_scene_manager = nullptr;
	this->_texture_manager = nullptr;
	this->_graphic_manager = nullptr;
	this->_audio_manager = nullptr;
}

template<class Serialize>
inline bool g2d::scene::scene<Serialize>::initialize(Serialize* serialize, g2d::scene::scene_manager<Serialize>* scene_manager, g2d::graphic::texture_manager* texture_manager, g2d::graphic::graphic_manager* graphic_manager, g2d::audio::audio_manager* audio_manager)
{
	this->_serialize = serialize;
	this->_scene_manager = scene_manager;
	this->_texture_manager = texture_manager;
	this->_graphic_manager = graphic_manager;
	this->_audio_manager = audio_manager;

	return true;
}

template<class Serialize>
Serialize* g2d::scene::scene<Serialize>::serialize() const
{
	return this->_serialize;
}

template<class Serialize>
inline g2d::scene::scene_manager<Serialize>* g2d::scene::scene<Serialize>::scene_manager() const
{
	return this->_scene_manager;
}

template<class Serialize>
inline g2d::graphic::texture_manager* g2d::scene::scene<Serialize>::texture_manager() const
{
	return this->_texture_manager;
}

template<class Serialize>
inline g2d::graphic::graphic_manager* g2d::scene::scene<Serialize>::graphic_manager() const
{
	return this->_graphic_manager;
}

template<class Serialize>
inline g2d::audio::audio_manager* g2d::scene::scene<Serialize>::audio_manager() const
{
	return this->_audio_manager;
}
