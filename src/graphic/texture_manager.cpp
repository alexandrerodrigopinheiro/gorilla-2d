
#include "../../includes/graphic/texture_manager.h"

g2d::graphic::texture_manager::texture_manager()
	: _source(std::unordered_map<std::string,std::size_t>())
	, _texture(std::unordered_map<std::size_t, g2d::graphic::texture>())
{
}

g2d::graphic::texture_manager::~texture_manager()
{
	this->destroy();
}

bool g2d::graphic::texture_manager::texture(std::size_t identity, const std::string& filename, bool verbose)
{
	this->analyze(filename, identity);

    auto search = this->_texture.find(identity);

    if(search == this->_texture.end())
    {
		this->_texture.insert(std::make_pair(identity, g2d::graphic::texture()));

		if (!this->_texture.at(identity).initialize(filename, verbose))
		{
			return false;
		}

		return true;
    }

	std::clog << "Repeated identity: '" << identity << "' as '" << filename << "',failed" << std::endl;

	return false;
}

void g2d::graphic::texture_manager::destroy()
{
	for (auto& arg : this->_texture)
	{
		arg.second.destroy();
//		delete arg.second;
	}
}

const g2d::graphic::texture& g2d::graphic::texture_manager::texture(std::size_t identity) const
{
    auto search = this->_texture.find(identity);

    assert(search != this->_texture.end());

    return this->_texture.at(identity);
}

std::size_t g2d::graphic::texture_manager::size() const
{
    return this->_source.size();
}

void g2d::graphic::texture_manager::analyze(const std::string& filename, std::size_t identity)
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
