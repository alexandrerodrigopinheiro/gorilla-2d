#include "../../includes/scene/serialize.h"

g2d::scene::serialize::serialize(const std::string& filename)
	: _filename(filename)
{
}

g2d::scene::serialize::~serialize()
{
	this->_filename.clear();
}

const std::string& g2d::scene::serialize::filename() const
{
	return this->_filename;
}
