#ifndef G2D_ESCPOS_ESCPOS_H_
#define G2D_ESCPOS_ESCPOS_H_

#pragma once

#include <string>
#include <iostream>

namespace g2d
{
	namespace escpos
	{
		// cuts the paper after \x96 vertical spaces.
		extern std::string CUT;

		// equivalent to esc @.
		extern std::string RESET;

		// equivalent to esc m n for font type a.
		extern std::string FONT_A;

		// equivalent to esc m n for font type b.
		extern std::string FONT_B;

		// equivalent to esc - n for underline text.
		extern std::string UNDERLINE_OFF;

		extern std::string UNDERLINE_1_DOT;

		extern std::string UNDERLINE_2_DOT;

		// equivalent to esc.
		extern std::string BOLD_ON;

		extern std::string BOLD_OFF;
	}
}

#endif /* G2D_ESCPOS_ESCPOS_H_ */
