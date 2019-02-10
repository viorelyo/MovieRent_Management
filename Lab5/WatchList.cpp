#include "stdafx.h"
#include "WatchList.h"
#include "MyExceptions.h"


WatchList::WatchList()
{
	this->currentFilm = 0;
}

WatchList::~WatchList()
{
}

bool WatchList::find(const Film & f)
{
	bool found = false;

	for (unsigned i = 0; i < films.size(); i++)
		if (films[i].getTitle() == f.getTitle() && films[i].getYear() == f.getYear()) {
			found = true;
			break;
		}
	return found;
}

int WatchList::findPos(const Film & f)
{
	int found = -1;

	for (unsigned i = 0; i < films.size(); i++)
		if (films[i].getTitle() == f.getTitle() && films[i].getYear() == f.getYear()) {
			found = i;
			break;
		}
	return found;
}

int WatchList::add(const Film & film)
{
	if (find(film) == false) {
		this->films.push_back(film);
		return 0;
	}
	else {
		//return -1;
		throw FilmInWatchlist();
	}
}

int WatchList::deleteFilm(const Film & f)
{
	int pos = findPos(f);
	if (pos != -1) {
		this->films.erase(films.begin() + pos);
		
		return 0;      //successful
	}
	else {
		//return -1;     //the film isn't in watchlist
		throw FilmInWatchlist();
	}
}

std::vector<Film> WatchList::getFilms()
{
	return films;
}

