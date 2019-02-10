#pragma once
#include <string>

class Validation
{
public:
	static int validateTitle(const std::string& title);
	static int validateGenre(const std::string& genre);
	static int validateYear(const std::string& year);
};

