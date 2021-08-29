#ifndef G2D_GRAPHIC_GRAPHIC_MANAGER_H_
#define G2D_GRAPHIC_GRAPHIC_MANAGER_H_

#pragma once

#include <string>
#include <iostream>
#include <unordered_map>
#include <memory>

#include "emitter.h"
#include "shape.h"
#include "sprite.h"
#include "stack.h"
#include "text.h"
#include "video.h"

namespace g2d
{
	namespace graphic
	{
		class graphic_manager
		{
			public:

				graphic_manager();

				~graphic_manager();

				bool emitter(std::size_t identity, const std::string& filename, const g2d::graphic::emission& emission, std::size_t amount, bool verbose = false);

				bool shape(std::size_t identity, double width, double height, std::size_t dots, const g2d::graphic::form& form, bool verbose = false);

				bool sprite(std::size_t identity, const std::string& filename, std::size_t columns, std::size_t rows, std::size_t frames, bool verbose = false);

				bool stack(std::size_t identity, const std::string& filename, bool verbose = false);

				bool text(std::size_t identity, const std::string& filename, std::size_t measure, bool verbose = false);

				bool video(std::size_t identity, const std::string& filename, bool verbose = false);

				void destroy();

				g2d::graphic::emitter* emitter(std::size_t identity) const;

				g2d::graphic::shape* shape(std::size_t identity) const;

				g2d::graphic::sprite* sprite(std::size_t identity) const;

				g2d::graphic::stack* stack(std::size_t identity) const;

				g2d::graphic::text* text(std::size_t identity) const;

				g2d::graphic::video* video(std::size_t identity) const;

				std::size_t size() const;

			private:

				void analyze(const std::string& filename, std::size_t identity);

				std::unordered_map<std::string, std::size_t> _source { std::unordered_map<std::string, std::size_t>() };
				std::unordered_map<std::size_t, g2d::graphic::emitter*> _emitter { std::unordered_map<std::size_t, g2d::graphic::emitter*>() };
				std::unordered_map<std::size_t, g2d::graphic::shape*> _shape { std::unordered_map<std::size_t, g2d::graphic::shape*>() };
				std::unordered_map<std::size_t, g2d::graphic::sprite*> _sprite { std::unordered_map<std::size_t, g2d::graphic::sprite*>() };
				std::unordered_map<std::size_t, g2d::graphic::stack*> _stack { std::unordered_map<std::size_t, g2d::graphic::stack*>() };
				std::unordered_map<std::size_t, g2d::graphic::text*> _text { std::unordered_map<std::size_t, g2d::graphic::text*>() };
				std::unordered_map<std::size_t, g2d::graphic::video*> _video { std::unordered_map<std::size_t, g2d::graphic::video*>() };
		};

		typedef std::shared_ptr<g2d::graphic::graphic_manager> graphic_manager_ptr;
	}
}

#endif /* G2D_GRAPHIC_GRAPHIC_MANAGER_H_ */
