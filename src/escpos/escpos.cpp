#include "../../includes/escpos/escpos.h"

// cuts the paper after \x96 vertical spaces.
std::string g2d::escpos::CUT = { '\x1d', '\x56', '\x41', '\x96' };

// equivalent to ESC @.
std::string g2d::escpos::RESET = { '\x1d', '\x40' };

// equivalent to ESC M n for font type A.
std::string g2d::escpos::FONT_A = { '\x1b', '\x4d', '\x00' };

// equivalent to ESC M n for font type B.
std::string g2d::escpos::FONT_B = { '\x1b', '\x4d', '\x01' };

// equivalent to ESC - n for underline text.
std::string g2d::escpos::UNDERLINE_OFF = { '\x1b', '\x2d', '\x00' };

std::string g2d::escpos::UNDERLINE_1_DOT = { '\x1b', '\x2d', '\x01' };

std::string g2d::escpos::UNDERLINE_2_DOT = { '\x1b', '\x2d', '\x02' };

// equivalent to ESC.
std::string g2d::escpos::BOLD_ON = { '\x1b', '\x45', '\x01' };

std::string g2d::escpos::BOLD_OFF = { '\x1b', '\x45', '\x00' };
