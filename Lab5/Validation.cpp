#include "stdafx.h"
#include "Validation.h"


int Validation::validateTitle(const std::string & title)
{
	if (title == "")
		return -1;
	return 0;
}

int Validation::validateGenre(const std::string & genre)
{
	if (genre == "")
		return -1;
	return 0;
}

int Validation::validateYear(const std::string & year)
{
	int yearNumber; 
	try
	{
		yearNumber = std::stoi(year);
	}
	catch (const std::invalid_argument& e)
	{
		return -2;		//-2 : is not a number
	}

	if (yearNumber < 1900 || yearNumber > 2025)
		return -1;
	
	return yearNumber;		//successfully
}
