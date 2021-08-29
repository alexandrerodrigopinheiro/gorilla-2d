#ifndef G2D_ESCPOS_DATA_H_
#define G2D_ESCPOS_DATA_H_

#pragma once

#include <string>
#include <map>
#include <utility>

#include "escpos.h"

namespace g2d
{
	namespace escpos
	{
		class data : public std::pair<std::string, std::string>
		{
			public:

				static g2d::escpos::data matching(std::string to_match);

			private:

			    data(const std::string& id);

			    static void initialize();

			    static std::map<std::string, g2d::escpos::data*> static_data_map;

			    std::string _id { std::string() };
		};
	}
}

#endif /* G2D_ESCPOS_DATA_H_ */
