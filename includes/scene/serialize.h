#ifndef G2D_SCENE_SERIALIZE_H_
#define G2D_SCENE_SERIALIZE_H_

#pragma once

#include <string>
#include <iostream>

#include "../basic/basic.h"

namespace g2d
{
	namespace scene
	{
		class serialize
		{
			public:

				serialize(const std::string& filename);

				virtual ~serialize();

				virtual bool save() = 0;

				virtual bool load() = 0;

				const std::string& filename() const;

			private:

				std::string _filename { std::string() };
		};
	}
}

#endif /* G2D_SCENE_SERIALIZE_H_ */
