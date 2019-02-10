#pragma once
#include "Film.h"
#include <vector>

class WatchList
{
public:
	WatchList();
	~WatchList();
	
	bool find(const Film& f);
	int findPos(const Film & f);
	int add(const Film& film);
	int deleteFilm(const Film& f);
	std::vector<Film> getFilms();

private:
	std::vector<Film> films;
	unsigned currentFilm;
};

