#include "../../includes/math/color.h"

g2d::math::color::color()
	: _r(g2d::math::CHANNEL_END)
	, _g(g2d::math::CHANNEL_END)
	, _b(g2d::math::CHANNEL_END)
	, _a(g2d::math::CHANNEL_END)
	, _null(false)
{
}

g2d::math::color::color(double color)
	: _r(g2d::math::clamp(color, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END))
	, _g(g2d::math::clamp(color, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END))
	, _b(g2d::math::clamp(color, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END))
	, _a(g2d::math::clamp(color, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END))
	, _null(false)
{
}

g2d::math::color::color(const g2d::math::color& color)
	: _r(g2d::math::clamp(color.r(), g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END))
	, _g(g2d::math::clamp(color.g(), g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END))
	, _b(g2d::math::clamp(color.b(), g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END))
	, _a(g2d::math::clamp(color.a(), g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END))
	, _null(false)
{
}

g2d::math::color::color(double r, double g, double b, double a)
	: _r(g2d::math::clamp(r, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END))
	, _g(g2d::math::clamp(g, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END))
	, _b(g2d::math::clamp(b, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END))
	, _a(g2d::math::clamp(a, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END))
	, _null(false)
{
}

g2d::math::color::~color()
{
}

void g2d::math::color::set(double color)
{
	this->_r = g2d::math::clamp(color, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_g = g2d::math::clamp(color, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_b = g2d::math::clamp(color, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_a = g2d::math::clamp(color, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
}

void g2d::math::color::set(const g2d::math::color& color)
{
	this->_r = g2d::math::clamp(color.r(), g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_g = g2d::math::clamp(color.g(), g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_b = g2d::math::clamp(color.b(), g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_a = g2d::math::clamp(color.a(), g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
}

void g2d::math::color::set(double r, double g, double b, double a)
{
	this->_r = g2d::math::clamp(r, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_g = g2d::math::clamp(g, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_b = g2d::math::clamp(b, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_a = g2d::math::clamp(a, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
}

void g2d::math::color::r(double r)
{
	this->_r = g2d::math::clamp(r, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
}

void g2d::math::color::g(double g)
{
	this->_g = g2d::math::clamp(g, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
}

void g2d::math::color::b(double b)
{
	this->_b = g2d::math::clamp(b, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
}

void g2d::math::color::a(double a)
{
	this->_a = g2d::math::clamp(a, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
}

double g2d::math::color::r() const
{
	return this->_r;
}

double g2d::math::color::g() const
{
	return this->_g;
}

double g2d::math::color::b() const
{
	return this->_b;
}

double g2d::math::color::a() const
{
	return this->_a;
}

double g2d::math::color::normal_r() const
{
	return this->_r / g2d::math::CHANNEL_END;
}

double g2d::math::color::normal_g() const
{
	return this->_g / g2d::math::CHANNEL_END;
}

double g2d::math::color::normal_b() const
{
	return this->_b / g2d::math::CHANNEL_END;
}

double g2d::math::color::normal_a() const
{
	return this->_a / g2d::math::CHANNEL_END;
}

g2d::math::color g2d::math::color::annul() const
{
	return g2d::math::color(g2d::math::CHANNEL_END, g2d::math::CHANNEL_END, g2d::math::CHANNEL_END, g2d::math::CHANNEL_END, true);
}

bool g2d::math::color::null() const
{
	return this->_null;
}

void g2d::math::color::string_to(const std::string& r, const std::string& g, const std::string& b, const std::string& a)
{
	this->_r = g2d::math::clamp(g2d::basic::to<double>(r), g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_g = g2d::math::clamp(g2d::basic::to<double>(g), g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_b = g2d::math::clamp(g2d::basic::to<double>(b), g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_a = g2d::math::clamp(g2d::basic::to<double>(a), g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
}

g2d::math::color g2d::math::color::ALICEBLUE()
{
	return g2d::math::color::hex_to_color("F0F8FF");
}

g2d::math::color g2d::math::color::ANTIQUEWHITE()
{
	return g2d::math::color::hex_to_color("FAEBD7");
}

g2d::math::color g2d::math::color::AQUA()
{
	return g2d::math::color::hex_to_color("00FFFF");
}

g2d::math::color g2d::math::color::AQUAMARINE()
{
	return g2d::math::color::hex_to_color("7FFFD4");
}

g2d::math::color g2d::math::color::AZURE()
{
	return g2d::math::color::hex_to_color("F0FFFF");
}

g2d::math::color g2d::math::color::BEIGE()
{
	return g2d::math::color::hex_to_color("F5F5DC");
}

g2d::math::color g2d::math::color::BISQUE()
{
	return g2d::math::color::hex_to_color("FFE4C4");
}

g2d::math::color g2d::math::color::BLACK()
{
	return g2d::math::color::hex_to_color("000000");
}

g2d::math::color g2d::math::color::BLANCHEDALMOND()
{
	return g2d::math::color::hex_to_color("FFEBCD");
}

g2d::math::color g2d::math::color::BLUE()
{
	return g2d::math::color::hex_to_color("0000FF");
}

g2d::math::color g2d::math::color::BLUELIGHT()
{
	return g2d::math::color::hex_to_color("007DFF");
}

g2d::math::color g2d::math::color::BLUEVIOLET()
{
	return g2d::math::color::hex_to_color("8A2BE2");
}

g2d::math::color g2d::math::color::BROWN()
{
	return g2d::math::color::hex_to_color("A52A2A");
}

g2d::math::color g2d::math::color::BURLYWOOD()
{
	return g2d::math::color::hex_to_color("DEB887");
}

g2d::math::color g2d::math::color::CADETBLUE()
{
	return g2d::math::color::hex_to_color("5F9EA0");
}

g2d::math::color g2d::math::color::CHARTREUSE()
{
	return g2d::math::color::hex_to_color("7FFF00");
}

g2d::math::color g2d::math::color::CHOCOLATE()
{
	return g2d::math::color::hex_to_color("D2691E");
}

g2d::math::color g2d::math::color::CORAL()
{
	return g2d::math::color::hex_to_color("FF7F50");
}

g2d::math::color g2d::math::color::CORNFLOWERBLUE()
{
	return g2d::math::color::hex_to_color("6495ED");
}

g2d::math::color g2d::math::color::CORNSILK()
{
	return g2d::math::color::hex_to_color("FFF8DC");
}

g2d::math::color g2d::math::color::CRIMSON()
{
	return g2d::math::color::hex_to_color("DC143C");
}

g2d::math::color g2d::math::color::CYAN()
{
	return g2d::math::color::hex_to_color("00FFFF");
}

g2d::math::color g2d::math::color::DARKBLUE()
{
	return g2d::math::color::hex_to_color("00008B");
}

g2d::math::color g2d::math::color::DARKCYAN()
{
	return g2d::math::color::hex_to_color("008B8B");
}

g2d::math::color g2d::math::color::DARKGOLDENROD()
{
	return g2d::math::color::hex_to_color("B8860B");
}

g2d::math::color g2d::math::color::DARKGRAY()
{
	return g2d::math::color::hex_to_color("A9A9A9");
}

g2d::math::color g2d::math::color::DARKGREEN()
{
	return g2d::math::color::hex_to_color("006400");
}

g2d::math::color g2d::math::color::DARKKHAKI()
{
	return g2d::math::color::hex_to_color("BDB76B");
}

g2d::math::color g2d::math::color::DARKMAGENTA()
{
	return g2d::math::color::hex_to_color("8B008B");
}

g2d::math::color g2d::math::color::DARKOLIVEGREEN()
{
	return g2d::math::color::hex_to_color("556B2F");
}

g2d::math::color g2d::math::color::DARKORANGE()
{
	return g2d::math::color::hex_to_color("FF8C00");
}

g2d::math::color g2d::math::color::DARKORCHID()
{
	return g2d::math::color::hex_to_color("9932CC");
}

g2d::math::color g2d::math::color::DARKRED()
{
	return g2d::math::color::hex_to_color("8B0000");
}

g2d::math::color g2d::math::color::DARKSALMON()
{
	return g2d::math::color::hex_to_color("E9967A");
}

g2d::math::color g2d::math::color::DARKSEAGREEN()
{
	return g2d::math::color::hex_to_color("8FBC8F");
}

g2d::math::color g2d::math::color::DARKSLATEBLUE()
{
	return g2d::math::color::hex_to_color("483D8B");
}

g2d::math::color g2d::math::color::DARKSLATEGRAY()
{
	return g2d::math::color::hex_to_color("2F4F4F");
}

g2d::math::color g2d::math::color::DARKSLATEGREY()
{
	return g2d::math::color::hex_to_color("2F4F4F");
}

g2d::math::color g2d::math::color::DARKTURQUOISE()
{
	return g2d::math::color::hex_to_color("00CED1");
}

g2d::math::color g2d::math::color::DARKVIOLET()
{
	return g2d::math::color::hex_to_color("9400D3");
}

g2d::math::color g2d::math::color::DEEPPINK()
{
	return g2d::math::color::hex_to_color("FF1493");
}

g2d::math::color g2d::math::color::DEEPSKYBLUE()
{
	return g2d::math::color::hex_to_color("00BFFF");
}

g2d::math::color g2d::math::color::DIMGRAY()
{
	return g2d::math::color::hex_to_color("696969");
}

g2d::math::color g2d::math::color::DODGERBLUE()
{
	return g2d::math::color::hex_to_color("1E90FF");
}

g2d::math::color g2d::math::color::FIREBRICK()
{
	return g2d::math::color::hex_to_color("B22222");
}

g2d::math::color g2d::math::color::FLORALWHITE()
{
	return g2d::math::color::hex_to_color("FFFAF0");
}

g2d::math::color g2d::math::color::FORESTGREEN()
{
	return g2d::math::color::hex_to_color("228B22");
}

g2d::math::color g2d::math::color::FUCHSIA()
{
	return g2d::math::color::hex_to_color("FF00FF");
}

g2d::math::color g2d::math::color::GAINSBORO()
{
	return g2d::math::color::hex_to_color("DCDCDC");
}

g2d::math::color g2d::math::color::GHOSTWHITE()
{
	return g2d::math::color::hex_to_color("F8F8FF");
}

g2d::math::color g2d::math::color::GOLD()
{
	return g2d::math::color::hex_to_color("FFD700");
}

g2d::math::color g2d::math::color::GOLDENROD()
{
	return g2d::math::color::hex_to_color("DAA520");
}

g2d::math::color g2d::math::color::GREY()
{
	return g2d::math::color::hex_to_color("808080");
}

g2d::math::color g2d::math::color::GREEN()
{
	return g2d::math::color::hex_to_color("008000");
}

g2d::math::color g2d::math::color::GREENYELLOW()
{
	return g2d::math::color::hex_to_color("ADFF2F");
}

g2d::math::color g2d::math::color::HONEYDEW()
{
	return g2d::math::color::hex_to_color("F0FFF0");
}

g2d::math::color g2d::math::color::HOTPINK()
{
	return g2d::math::color::hex_to_color("FF69B4");
}

g2d::math::color g2d::math::color::INDIANRED()
{
	return g2d::math::color::hex_to_color("CD5C5C");
}

g2d::math::color g2d::math::color::INDIGO ()
{
	return g2d::math::color::hex_to_color("4B0082");
}

g2d::math::color g2d::math::color::IVORY()
{
	return g2d::math::color::hex_to_color("FFFFF0");
}

g2d::math::color g2d::math::color::KHAKI()
{
	return g2d::math::color::hex_to_color("F0E68C");
}

g2d::math::color g2d::math::color::LAVENDER()
{
	return g2d::math::color::hex_to_color("E6E6FA");
}

g2d::math::color g2d::math::color::LAVENDERBLUSH()
{
	return g2d::math::color::hex_to_color("FFF0F5");
}

g2d::math::color g2d::math::color::LAWNGREEN()
{
	return g2d::math::color::hex_to_color("7CFC00");
}

g2d::math::color g2d::math::color::LEMONCHIFFON()
{
	return g2d::math::color::hex_to_color("FFFACD");
}

g2d::math::color g2d::math::color::LIGHTBLUE()
{
	return g2d::math::color::hex_to_color("ADD8E6");
}

g2d::math::color g2d::math::color::LIGHTCORAL()
{
	return g2d::math::color::hex_to_color("F08080");
}

g2d::math::color g2d::math::color::LIGHTCYAN()
{
	return g2d::math::color::hex_to_color("E0FFFF");
}

g2d::math::color g2d::math::color::LIGHTGOLDENRODYELLOW()
{
	return g2d::math::color::hex_to_color("FAFAD2");
}

g2d::math::color g2d::math::color::LIGHTGREY()
{
	return g2d::math::color::hex_to_color("D3D3D3");
}

g2d::math::color g2d::math::color::LIGHTGREEN()
{
	return g2d::math::color::hex_to_color("90EE90");
}

g2d::math::color g2d::math::color::LIGHTPINK()
{
	return g2d::math::color::hex_to_color("FFB6C1");
}

g2d::math::color g2d::math::color::LIGHTSALMON()
{
	return g2d::math::color::hex_to_color("FFA07A");
}

g2d::math::color g2d::math::color::LIGHTSEAGREEN()
{
	return g2d::math::color::hex_to_color("20B2AA");
}

g2d::math::color g2d::math::color::LIGHTSKYBLUE()
{
	return g2d::math::color::hex_to_color("87CEFA");
}

g2d::math::color g2d::math::color::LIGHTSLATEGRAY()
{
	return g2d::math::color::hex_to_color("778899");
}

g2d::math::color g2d::math::color::LIGHTSTEELBLUE()
{
	return g2d::math::color::hex_to_color("B0C4DE");
}

g2d::math::color g2d::math::color::LIGHTYELLOW()
{
	return g2d::math::color::hex_to_color("FFFFE0");
}

g2d::math::color g2d::math::color::LIME()
{
	return g2d::math::color::hex_to_color("00FF00");
}

g2d::math::color g2d::math::color::LIMEGREEN()
{
	return g2d::math::color::hex_to_color("32CD32");
}

g2d::math::color g2d::math::color::LINEN()
{
	return g2d::math::color::hex_to_color("FAF0E6");
}

g2d::math::color g2d::math::color::MAGENTA()
{
	return g2d::math::color::hex_to_color("FF00FF");
}

g2d::math::color g2d::math::color::MAROON()
{
	return g2d::math::color::hex_to_color("800000");
}

g2d::math::color g2d::math::color::MEDIUMAQUAMARINE()
{
	return g2d::math::color::hex_to_color("66CDAA");
}

g2d::math::color g2d::math::color::MEDIUMBLUE()
{
	return g2d::math::color::hex_to_color("0000CD");
}

g2d::math::color g2d::math::color::MEDIUMORCHID()
{
	return g2d::math::color::hex_to_color("BA55D3");
}

g2d::math::color g2d::math::color::MEDIUMPURPLE()
{
	return g2d::math::color::hex_to_color("9370DB");
}

g2d::math::color g2d::math::color::MEDIUMSEAGREEN()
{
	return g2d::math::color::hex_to_color("3CB371");
}

g2d::math::color g2d::math::color::MEDIUMSLATEBLUE()
{
	return g2d::math::color::hex_to_color("7B68EE");
}

g2d::math::color g2d::math::color::MEDIUMSPRINGGREEN()
{
	return g2d::math::color::hex_to_color("00FA9A");
}

g2d::math::color g2d::math::color::MEDIUMTURQUOISE()
{
	return g2d::math::color::hex_to_color("48D1CC");
}

g2d::math::color g2d::math::color::MEDIUMVIOLETRED()
{
	return g2d::math::color::hex_to_color("C71585");
}

g2d::math::color g2d::math::color::MIDNIGHTBLUE()
{
	return g2d::math::color::hex_to_color("191970");
}

g2d::math::color g2d::math::color::MINTCREAM()
{
	return g2d::math::color::hex_to_color("F5FFFA");
}

g2d::math::color g2d::math::color::MISTYROSE()
{
	return g2d::math::color::hex_to_color("FFE4E1");
}

g2d::math::color g2d::math::color::MOCCASIN()
{
	return g2d::math::color::hex_to_color("FFE4B5");
}

g2d::math::color g2d::math::color::NAVAJOWHITE()
{
	return g2d::math::color::hex_to_color("FFDEAD");
}

g2d::math::color g2d::math::color::NAVY()
{
	return g2d::math::color::hex_to_color("000080");
}

g2d::math::color g2d::math::color::OLDLACE()
{
	return g2d::math::color::hex_to_color("FDF5E6");
}

g2d::math::color g2d::math::color::OLIVE()
{
	return g2d::math::color::hex_to_color("808000");
}

g2d::math::color g2d::math::color::OLIVEDRAB()
{
	return g2d::math::color::hex_to_color("6B8E23");
}

g2d::math::color g2d::math::color::ORANGE()
{
	return g2d::math::color::hex_to_color("FFA500");
}

g2d::math::color g2d::math::color::ORANGERED()
{
	return g2d::math::color::hex_to_color("FF4500");
}

g2d::math::color g2d::math::color::ORCHID()
{
	return g2d::math::color::hex_to_color("DA70D6");
}

g2d::math::color g2d::math::color::PALEGOLDENROD()
{
	return g2d::math::color::hex_to_color("EEE8AA");
}

g2d::math::color g2d::math::color::PALEGREEN()
{
	return g2d::math::color::hex_to_color("98FB98");
}

g2d::math::color g2d::math::color::PALETURQUOISE()
{
	return g2d::math::color::hex_to_color("AFEEEE");
}

g2d::math::color g2d::math::color::PALEVIOLETRED()
{
	return g2d::math::color::hex_to_color("DB7093");
}

g2d::math::color g2d::math::color::PAPAYAWHIP()
{
	return g2d::math::color::hex_to_color("FFEFD5");
}

g2d::math::color g2d::math::color::PEACHPUFF()
{
	return g2d::math::color::hex_to_color("FFDAB9");
}

g2d::math::color g2d::math::color::PERU()
{
	return g2d::math::color::hex_to_color("CD853F");
}

g2d::math::color g2d::math::color::PINK()
{
	return g2d::math::color::hex_to_color("FFC0CB");
}

g2d::math::color g2d::math::color::PLUM()
{
	return g2d::math::color::hex_to_color("DDA0DD");
}

g2d::math::color g2d::math::color::POWDERBLUE()
{
	return g2d::math::color::hex_to_color("B0E0E6");
}

g2d::math::color g2d::math::color::PURPLE()
{
	return g2d::math::color::hex_to_color("800080");
}

g2d::math::color g2d::math::color::REBECCAPURPLE()
{
	return g2d::math::color::hex_to_color("663399");
}

g2d::math::color g2d::math::color::RED()
{
	return g2d::math::color::hex_to_color("FF0000");
}

g2d::math::color g2d::math::color::ROSYBROWN()
{
	return g2d::math::color::hex_to_color("BC8F8F");
}

g2d::math::color g2d::math::color::ROYALBLUE()
{
	return g2d::math::color::hex_to_color("4169E1");
}

g2d::math::color g2d::math::color::SADDLEBROWN()
{
	return g2d::math::color::hex_to_color("8B4513");
}

g2d::math::color g2d::math::color::SALMON()
{
	return g2d::math::color::hex_to_color("FA8072");
}

g2d::math::color g2d::math::color::SANDYBROWN()
{
	return g2d::math::color::hex_to_color("F4A460");
}

g2d::math::color g2d::math::color::SEAGREEN()
{
	return g2d::math::color::hex_to_color("2E8B57");
}

g2d::math::color g2d::math::color::SEASHELL()
{
	return g2d::math::color::hex_to_color("FFF5EE");
}

g2d::math::color g2d::math::color::SIENNA()
{
	return g2d::math::color::hex_to_color("A0522D");
}

g2d::math::color g2d::math::color::SILVER()
{
	return g2d::math::color::hex_to_color("C0C0C0");
}

g2d::math::color g2d::math::color::SKYBLUE()
{
	return g2d::math::color::hex_to_color("87CEEB");
}

g2d::math::color g2d::math::color::SLATEBLUE()
{
	return g2d::math::color::hex_to_color("6A5ACD");
}

g2d::math::color g2d::math::color::SLATEGRAY()
{
	return g2d::math::color::hex_to_color("708090");
}

g2d::math::color g2d::math::color::SNOW()
{
	return g2d::math::color::hex_to_color("FFFAFA");
}

g2d::math::color g2d::math::color::SPRINGGREEN()
{
	return g2d::math::color::hex_to_color("00FF7F");
}

g2d::math::color g2d::math::color::STEELBLUE()
{
	return g2d::math::color::hex_to_color("4682B4");
}

g2d::math::color g2d::math::color::TAN()
{
	return g2d::math::color::hex_to_color("D2B48C");
}

g2d::math::color g2d::math::color::TEAL()
{
	return g2d::math::color::hex_to_color("008080");
}

g2d::math::color g2d::math::color::THISTLE()
{
	return g2d::math::color::hex_to_color("D8BFD8");
}

g2d::math::color g2d::math::color::TOMATO()
{
	return g2d::math::color::hex_to_color("FF6347");
}

g2d::math::color g2d::math::color::TURQUOISE()
{
	return g2d::math::color::hex_to_color("40E0D0");
}

g2d::math::color g2d::math::color::VIOLET()
{
	return g2d::math::color::hex_to_color("EE82EE");
}

g2d::math::color g2d::math::color::WHEAT()
{
	return g2d::math::color::hex_to_color("F5DEB3");
}

g2d::math::color g2d::math::color::WHITE()
{
	return g2d::math::color::hex_to_color("FFFFFF");
}

g2d::math::color g2d::math::color::WHITESMOKE()
{
	return g2d::math::color::hex_to_color("F5F5F5");
}

g2d::math::color g2d::math::color::YELLOW()
{
	return g2d::math::color::hex_to_color("FFFF00");
}

g2d::math::color g2d::math::color::YELLOWGREEN()
{
	return g2d::math::color::hex_to_color("9ACD32");
}

g2d::math::color g2d::math::color::operator++()
{
	++this->_r;
	++this->_g;
	++this->_b;
	++this->_a;

    return g2d::math::color(this->_r, this->_g, this->_b, this->_a);
}

g2d::math::color g2d::math::color::operator++(int)
{
	const g2d::math::color& result = *this;

	++this->_r;
	++this->_g;
	++this->_b;
	++this->_a;

	return result;
}

g2d::math::color g2d::math::color::operator--()
{
	--this->_r;
	--this->_g;
	--this->_b;
	--this->_a;

    return g2d::math::color(this->_r, this->_g, this->_b, this->_a);
}

g2d::math::color g2d::math::color::operator--(int)
{
	const g2d::math::color& result = *this;

	--this->_r;
	--this->_g;
	--this->_b;
	--this->_a;

	return result;
}

const g2d::math::color& g2d::math::color::operator=(const g2d::math::color& right)
{
	this->_r = right.r();
	this->_g = right.g();
	this->_b = right.b();
	this->_a = right.a();

    return *this;
}

const g2d::math::color& g2d::math::color::operator+(const g2d::math::color& right)
{
	this->_r = this->_r / right.r();
	this->_g = this->_g / right.g();
	this->_b = this->_b / right.b();
	this->_a = this->_a / right.a();

    return *this;
}

const g2d::math::color& g2d::math::color::operator-(const g2d::math::color& right)
{
	this->_r = this->_r - right.r();
	this->_g = this->_g - right.g();
	this->_b = this->_b - right.b();
	this->_a = this->_a - right.a();

    return *this;
}

const g2d::math::color& g2d::math::color::operator/(const g2d::math::color& right)
{
	this->_r = this->_r / right.r();
	this->_g = this->_g / right.g();
	this->_b = this->_b / right.b();
	this->_a = this->_a / right.a();

    return *this;
}

const g2d::math::color& g2d::math::color::operator*(const g2d::math::color& right)
{
	this->_r = this->_r * right.r();
	this->_g = this->_g * right.g();
	this->_b = this->_b * right.b();
	this->_a = this->_a * right.a();

    return *this;
}

const g2d::math::color& g2d::math::color::operator+=(const g2d::math::color& right)
{
	this->_r = this->_r + right.r();
	this->_g = this->_g + right.g();
	this->_b = this->_b + right.b();
	this->_a = this->_a + right.a();

    return *this;
}

const g2d::math::color& g2d::math::color::operator-=(const g2d::math::color& right)
{
	this->_r = this->_r - right.r();
	this->_g = this->_g - right.g();
	this->_b = this->_b - right.b();
	this->_a = this->_a - right.a();

    return *this;
}

const g2d::math::color& g2d::math::color::operator*=(const g2d::math::color& right)
{
	this->_r = this->_r * right.r();
	this->_g = this->_g * right.g();
	this->_b = this->_b * right.b();
	this->_a = this->_a * right.a();

    return *this;
}

const g2d::math::color& g2d::math::color::operator/=(const g2d::math::color& right)
{
	this->_r = this->_r / right.r();
	this->_g = this->_g / right.g();
	this->_b = this->_b / right.b();
	this->_a = this->_a / right.a();

    return *this;
}

bool g2d::math::color::operator==(const g2d::math::color& right)
{
	return (this->_r == right.r()) && (this->_g == right.g()) && (this->_b == right.b()) && (this->_a == right.a());
}

bool g2d::math::color::operator!=(const g2d::math::color& right)
{
	return (this->_r != right.r()) && (this->_g != right.g()) && (this->_b != right.b()) && (this->_a != right.a());
}

bool g2d::math::color::operator>(const g2d::math::color& right)
{
	return (this->_r > right.r()) && (this->_g > right.g()) && (this->_b > right.b()) && (this->_a > right.a());
}

bool g2d::math::color::operator<(const g2d::math::color& right)
{
	return (this->_r < right.r()) && (this->_g < right.g()) && (this->_b < right.b()) && (this->_a < right.a());
}

bool g2d::math::color::operator>=(const g2d::math::color& right)
{
	return (this->_r >= right.r()) && (this->_g >= right.g()) && (this->_b >= right.b()) && (this->_a >= right.a());
}

bool g2d::math::color::operator<=(const g2d::math::color& right)
{
	return (this->_r <= right.r()) && (this->_g <= right.g()) && (this->_b <= right.b()) && (this->_a <= right.a());
}

const g2d::math::color& g2d::math::color::operator=(double right)
{
	this->_r = g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_g = g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_b = g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_a = g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);

    return *this;
}

const g2d::math::color& g2d::math::color::operator+(double right)
{
	this->_r = this->_r + g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_g = this->_g + g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_b = this->_b + g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_a = this->_a + g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);

    return *this;
}

const g2d::math::color& g2d::math::color::operator-(double right)
{
	this->_r = this->_r - g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_g = this->_g - g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_b = this->_b - g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_a = this->_a - g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);

    return *this;
}

const g2d::math::color& g2d::math::color::operator/(double right)
{
	this->_r = this->_r / g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_g = this->_g / g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_b = this->_b / g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_a = this->_a / g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);

    return *this;
}

const g2d::math::color& g2d::math::color::operator*(double right)
{
	this->_r = this->_r * g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_g = this->_g * g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_b = this->_b * g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_a = this->_a * g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);

    return *this;
}

const g2d::math::color& g2d::math::color::operator+=(double right)
{
	this->_r = this->_r + g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_g = this->_g + g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_b = this->_b + g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_a = this->_a + g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);

    return *this;
}

const g2d::math::color& g2d::math::color::operator-=(double right)
{
	this->_r = this->_r - g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_g = this->_g - g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_b = this->_b - g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_a = this->_a - g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);

    return *this;
}

const g2d::math::color& g2d::math::color::operator*=(double right)
{
	this->_r = this->_r * g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_g = this->_g * g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_b = this->_b * g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_a = this->_a * g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);

    return *this;
}

const g2d::math::color& g2d::math::color::operator/=(double right)
{
	this->_r = this->_r / g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_g = this->_g / g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_b = this->_b / g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);
	this->_a = this->_a / g2d::math::clamp(right, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END);

	return *this;
}

bool g2d::math::color::operator==(double right)
{
	return (this->_r == right) && (this->_g == right) && (this->_b == right) && (this->_a == right);
}

bool g2d::math::color::operator!=(double right)
{
	return (this->_r != right) && (this->_g != right) && (this->_b != right) && (this->_a != right);
}

bool g2d::math::color::operator>(double right)
{
	return (this->_r > right) && (this->_g > right) && (this->_b > right) && (this->_a > right);
}

bool g2d::math::color::operator<(double right)
{
	return (this->_r < right) && (this->_g < right) && (this->_b < right) && (this->_a < right);
}

bool g2d::math::color::operator>=(double right)
{
	return (this->_r >= right) && (this->_g >= right) && (this->_b >= right) && (this->_a >= right);
}

bool g2d::math::color::operator<=(double right)
{
	return (this->_r <= right) && (this->_g <= right) && (this->_b <= right) && (this->_a <= right);
}

double g2d::math::color::to_hex(const std::string& hex)
{
	int value = 0;
	int size = hex.length();
	for (int a = 0, b = size - 1; b >= 0; a++, b--)
	{
		if (hex[b] >= '0' && hex[b] <= '9')
		{
			value += (hex[b] - '0') * (1 << (a * 4));
		}

		else
		{
			switch (hex[b])
			{
				case 'A':
				case 'a':
				{
					value += 10 * (1 << (a * 4));
					break;
				}
				case 'B':
				case 'b':
				{
					value += 11 * (1 << (a * 4));
					break;
				}
				case 'C':
				case 'c':
				{
					value += 12 * (1 << (a * 4));
					break;
				}
				case 'D':
				case 'd':
				{
					value += 13 * (1 << (a * 4));
					break;
				}
				case 'E':
				case 'e':
				{
					value += 14 * (1 << (a * 4));
					break;
				}
				case 'F':
				case 'f':
				{
					value += 15 * (1 << (a * 4));
					break;
				}
				default:
				{
					std::cerr << "Cannot convert hex color valid '" << hex[b] << "', failed." << std::endl;

					exit(0);

					break;
				}
			}
		}
	}

	return static_cast<double>(value);
}

g2d::math::color g2d::math::color::hex_to_color(const std::string& hex)
{
	std::string r = hex.substr(0, 2);
	std::string g = hex.substr(2, 2);
	std::string b = hex.substr(4, 2);

	return g2d::math::color(g2d::math::color::to_hex(r), g2d::math::color::to_hex(g), g2d::math::color::to_hex(b), g2d::math::CHANNEL_END);
}

g2d::math::color::color(double r, double g, double b, double a, bool null)
	: _r(g2d::math::clamp(r, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END))
	, _g(g2d::math::clamp(g, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END))
	, _b(g2d::math::clamp(b, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END))
	, _a(g2d::math::clamp(a, g2d::math::CHANNEL_BEGIN, g2d::math::CHANNEL_END))
	, _null(null)
{
}

std::ostream& g2d::math::operator<<(std::ostream& stream, const g2d::math::color& right)
{
	return stream << "color { r " << right.r() << " g " << right.g() << " b " << right.b() << " a " << right.a() << " }";
}

std::istream& g2d::math::operator>>(std::istream& stream, g2d::math::color& right)
{
	std::string garbage;
	double r;
	double g;
	double b;
	double a;

	stream >> garbage >> garbage >> garbage >> r >> garbage >> g >> garbage >> b >> garbage >> a >> garbage;

	right.set(r, g, b, a);

	return stream;
}

