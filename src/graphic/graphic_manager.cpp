#include "../../includes/graphic/graphic_manager.h"

g2d::graphic::graphic_manager::graphic_manager()
	: _source(std::unordered_map<std::string, std::size_t>())
	, _emitter(std::unordered_map<std::size_t, g2d::graphic::emitter*>())
	, _shape(std::unordered_map<std::size_t, g2d::graphic::shape*>())
	, _sprite(std::unordered_map<std::size_t, g2d::graphic::sprite*>())
	, _stack(std::unordered_map<std::size_t, g2d::graphic::stack*>())
	, _text(std::unordered_map<std::size_t, g2d::graphic::text*>())
	, _video(std::unordered_map<std::size_t, g2d::graphic::video*>())
{
}

g2d::graphic::graphic_manager::~graphic_manager()
{
	this->destroy();
}

bool g2d::graphic::graphic_manager::emitter(std::size_t identity, const std::string& filename, const g2d::graphic::emission& emission, std::size_t amount, bool verbose)
{
	this->analyze(filename, identity);

    auto search = this->_emitter.find(identity);

    if(search == this->_emitter.end())
    {
		this->_emitter.insert(std::make_pair(identity, new g2d::graphic::emitter()));

		if (!this->_emitter.at(identity)->initialize(filename, emission, amount, verbose))
		{
			return false;
		}

		return true;
    }

	std::clog << "Repeated identity: '" << identity << "' => '" << emission << "',failed" << std::endl;

	return false;
}

bool g2d::graphic::graphic_manager::shape(std::size_t identity, double width, double height, std::size_t dots, const g2d::graphic::form& form, bool verbose)
{
	/*this->analyze(identity, form);

    auto search = this->_shape.find(identity);

    if(search == this->_shape.end())
    {*/
		this->_shape.insert(std::make_pair(identity, new g2d::graphic::shape()));

		if (!this->_shape.at(identity)->initialize(width, height, dots, form, verbose))
		{
			return false;
		}

		return true;
//    }

//	std::clog << "Repeated identity: '" << identity << "' => '" << form << "',failed" << std::endl;

//	return false;
}

bool g2d::graphic::graphic_manager::sprite(std::size_t identity, const std::string& filename, std::size_t columns, std::size_t rows, std::size_t frames, bool verbose)
{
	this->analyze(filename, identity);

    auto search = this->_sprite.find(identity);

    if(search == this->_sprite.end())
    {
		this->_sprite.insert(std::make_pair(identity, new g2d::graphic::sprite()));

		if (!this->_sprite.at(identity)->initialize(filename, columns, rows, frames, verbose))
		{
			return false;
		}

		return true;
    }

	std::clog << "Repeated identity: '" << identity << "' => '" << filename << "',failed" << std::endl;

	return false;
}

bool g2d::graphic::graphic_manager::stack(std::size_t identity, const std::string& filename, bool verbose)
{
	this->analyze(filename, identity);

    auto search = this->_stack.find(identity);

    if(search == this->_stack.end())
    {
		this->_stack.insert(std::make_pair(identity, new g2d::graphic::stack()));

		if (!this->_stack.at(identity)->initialize(filename, verbose))
		{
			return false;
		}

		return true;
    }

	if (!this->_stack.at(identity)->initialize(filename))
	{
		std::clog << "Repeated filename: '" << filename << "' => '" << identity << "',failed" << std::endl;

		return false;
	}

	return true;
}

bool g2d::graphic::graphic_manager::text(std::size_t identity, const std::string& filename, std::size_t measure, bool verbose)
{
	this->analyze(filename, identity);

    auto search = this->_text.find(identity);

    if(search == this->_text.end())
    {
		this->_text.insert(std::make_pair(identity, new g2d::graphic::text()));

		if (!this->_text.at(identity)->initialize(filename, measure, verbose))
		{
			return false;
		}

		return true;
    }

	std::clog << "Repeated identity: '" << identity << "' => '" << filename << "',failed" << std::endl;

	return false;
}

bool g2d::graphic::graphic_manager::video(std::size_t identity, const std::string& filename, bool verbose)
{
	this->analyze(filename, identity);

    auto search = this->_video.find(identity);

    if(search == this->_video.end())
    {
		this->_video.insert(std::make_pair(identity, new g2d::graphic::video()));

		if (!this->_video.at(identity)->initialize(filename, verbose))
		{
			return false;
		}

		return true;
    }

	std::clog << "Repeated identity: '" << identity << "' => '" << filename << "',failed" << std::endl;

	return false;
}

void g2d::graphic::graphic_manager::destroy()
{
	for (auto& arg : this->_emitter)
	{
		delete arg.second;
	}

	for (auto& arg : this->_shape)
	{
		delete arg.second;
	}

	for (auto& arg : this->_sprite)
	{
		delete arg.second;
	}

	for (auto& arg : this->_stack)
	{
		delete arg.second;
	}

	for (auto& arg : this->_text)
	{
		delete arg.second;
	}

	for (auto& arg : this->_video)
	{
		delete arg.second;
	}
}

g2d::graphic::emitter* g2d::graphic::graphic_manager::emitter(std::size_t identity) const
{
    auto search = this->_emitter.find(identity);

    assert(search != this->_emitter.end());

    return this->_emitter.at(identity);
}

g2d::graphic::shape* g2d::graphic::graphic_manager::shape(std::size_t identity) const
{
    auto search = this->_shape.find(identity);

    assert(search != this->_shape.end());

    return this->_shape.at(identity);
}

g2d::graphic::sprite* g2d::graphic::graphic_manager::sprite(std::size_t identity) const
{
    auto search = this->_sprite.find(identity);

    assert(search != this->_sprite.end());

    return this->_sprite.at(identity);
}

g2d::graphic::stack* g2d::graphic::graphic_manager::stack(std::size_t identity) const
{
    auto search = this->_stack.find(identity);

    assert(search != this->_stack.end());

    return this->_stack.at(identity);
}

g2d::graphic::text* g2d::graphic::graphic_manager::text(std::size_t identity) const
{
    auto search = this->_text.find(identity);

    assert(search != this->_text.end());

    return this->_text.at(identity);
}

g2d::graphic::video* g2d::graphic::graphic_manager::video(std::size_t identity) const
{
    auto search = this->_video.find(identity);

    assert(search != this->_video.end());

    return this->_video.at(identity);
}

std::size_t g2d::graphic::graphic_manager::size() const
{
    return this->_source.size();
}

void g2d::graphic::graphic_manager::analyze(const std::string& filename, std::size_t identity)
{
	auto search = this->_source.find(filename);

	if(search == this->_source.end())
	{
		this->_source.insert(std::make_pair(filename, identity));
	}
	else
	{
		std::cerr << "Repeated source: '" << filename << "' at '" << identity << "',failed" << std::endl;

		exit(EXIT_FAILURE);
	}
}
