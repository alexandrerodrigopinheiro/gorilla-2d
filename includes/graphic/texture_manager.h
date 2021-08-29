#ifndef G2D_GRAPHIC_TEXTURE_MANAGER_H_
#define G2D_GRAPHIC_TEXTURE_MANAGER_H_

#pragma once

#include <string>
#include <iostream>
#include <unordered_map>
#include <memory>

#include "texture.h"

namespace g2d
{
	namespace graphic
	{
		class texture_manager
		{
			public:

				texture_manager();

				~texture_manager();

				bool texture(size_t identity, const std::string& filename, bool verbose = false);

				void destroy();

				const g2d::graphic::texture& texture(std::size_t identity) const;

				std::size_t size() const;

			private:

				void analyze(const std::string& filename, std::size_t identity);

				std::unordered_map<std::string, std::size_t> _source { std::unordered_map<std::string,std::size_t>() };
				std::unordered_map<std::size_t, g2d::graphic::texture> _texture { std::unordered_map<std::size_t, g2d::graphic::texture>() };
		};

		typedef std::shared_ptr<g2d::graphic::texture_manager> texture_manager_ptr;
	}
}

#endif /* G2D_GRAPHIC_TEXTURE_MANAGER_H_ */
