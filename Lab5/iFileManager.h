#pragma once
#include <vector>
#include <fstream>
#include "Film.h"


struct iFileReader
{
	virtual std::vector<Film> read(std::ifstream& file) = 0;
};

struct iFileWriter
{
	virtual void write(std::ofstream& file, const std::vector<Film>& vec) = 0;
	virtual void open(const std::string& filename) = 0;
};
