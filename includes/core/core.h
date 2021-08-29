#ifndef G2D_CORE_CORE_H_
#define G2D_CORE_CORE_H_

#pragma once

#include <iostream>
#include <string>

#include "../graphic/graphic.h"
#include "../scene/scene.h"

namespace g2d
{
	namespace core
	{
		template<class Serialize>
		struct scene
		{
			std::size_t identity;
			g2d::scene::scene<Serialize>* scene;
		};

		typedef struct texture
		{
			std::size_t identity;
			std::string filename;
			bool verbose;
		}
		texture;

		typedef struct emitter
		{
			std::size_t identity;
			std::string filename;
			std::size_t amount;
			g2d::graphic::emission emission;
			bool verbose;
		}
		emitter;

		typedef struct shape
		{
			std::size_t identity;
			double width;
			double height;
			std::size_t dots;
			g2d::graphic::form form;
			bool verbose;
		}
		shape;

		typedef struct sprite
		{
			std::size_t identity;
			std::string filename;
			std::size_t columns;
			std::size_t rows;
			std::size_t frames;
			bool verbose;
		}
		sprite;

		typedef struct stack
		{
			std::size_t identity;
			std::string filename;
			bool verbose;
		}
		stack;

		typedef struct text
		{
			std::size_t identity;
			std::string filename;
			std::size_t measure;
			bool verbose;
		}
		text;

		typedef struct video
		{
			std::size_t identity;
			std::string filename;
			bool verbose;
		}
		video;

		typedef struct sound
		{
			std::size_t identity;
			std::string filename;
			bool verbose;
		}
		sound;

		typedef struct music
		{
			std::size_t identity;
			std::string filename;
			bool verbose;
		}
		music;
	}
}

#endif /* G2D_CORE_CORE_H_ */
