#pragma once
#include "iFileManager.h"


class CSVFileWriter : public iFileWriter
{
public:
	void write(std::ofstream& file, const std::vector<Film>& v);
	void open(const std::string& filename);
};

class CSVFileReader : public iFileReader
{
public:
	std::vector<Film> read(std::ifstream& file);
};


class HTMLFileWriter : public iFileWriter
{
public:
	void write(std::ofstream& file, const std::vector<Film>& v);
	void open(const std::string& filename);
private:
	std::string spawnHTMLHeader();
	std::string spawnHTMLFooter();
	std::string spawnNewRow(const Film& f);
};

