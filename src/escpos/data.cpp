#include "../../includes/escpos/data.h"

std::map<std::string, g2d::escpos::data*> g2d::escpos::data::static_data_map = std::map<std::string, g2d::escpos::data*>();

g2d::escpos::data::data(const std::string& id)
	: std::pair<std::string, std::string>("","")
	, _id(id)
{
	// empty constructor.
}

g2d::escpos::data g2d::escpos::data::matching(std::string to_match)
{
	// check if we need to initialize the map.
	if (static_data_map.empty())
	{
		g2d::escpos::data::initialize();
	}

	auto result = static_data_map.find(to_match);

	if (result == static_data_map.end())
	{
		throw -1;
	}
	else
	{
		return *result->second;
	}
}

void g2d::escpos::data::initialize()
{
    // first we load the underline font thingy.
    static_data_map["__"] = new g2d::escpos::data("__");
    static_data_map["__"]->first = g2d::escpos::UNDERLINE_2_DOT;
    static_data_map["__"]->second = g2d::escpos::UNDERLINE_OFF;

    static_data_map[".."] = new g2d::escpos::data("..");
    static_data_map[".."]->first = g2d::escpos::UNDERLINE_1_DOT;
    static_data_map[".."]->second = g2d::escpos::UNDERLINE_OFF;

    static_data_map["**"] = new g2d::escpos::data("**");
    static_data_map["**"]->first = g2d::escpos::BOLD_ON;
    static_data_map["**"]->second = g2d::escpos::BOLD_OFF;

    static_data_map["FA"] = new g2d::escpos::data("FA");
    static_data_map["FA"]->first = g2d::escpos::FONT_A;
    static_data_map["FA"]->second = g2d::escpos::RESET;

    static_data_map["FB"] = new g2d::escpos::data("FB");
    static_data_map["FB"]->first = g2d::escpos::FONT_B;
    static_data_map["FB"]->second = g2d::escpos::RESET;
}
