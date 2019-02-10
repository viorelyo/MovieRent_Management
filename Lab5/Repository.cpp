#include "stdafx.h"
#include "Repository.h"


Repository::~Repository()
{
}

void Repository::addFilm(const Film & f)
{
	int foundPos = findFilm(f);
	if (foundPos == -1) {
		films.push_back(f);
		//return 0;				//0 - succesfully added
	}
	//else
	//{
	//	//return -1;				//-1 - is in DB
	//	throw FilmNotFound();
	//}
	
}

int Repository::deleteFilm(const Film & f)
{
	int foundPos = findFilm(f);
	if (foundPos != -1) {
		films.erase(films.begin() + foundPos);
		return 0;				//0 - succesfully deleted
	}
	else
	{
		//return -1;				//-1 - isn't in DB
		throw FilmNotFound();
	}
}

void Repository::updateFilm(unsigned pos, const std::string & newTitle, const std::string & newGenre, const unsigned newYear)
{
	if (newTitle != "") {
		films[pos].setTitle(newTitle);
		return;
	}
	if (newGenre != "") {
		films[pos].setGenre(newGenre);
		return;
	}
	if (newYear != 0) {
		films[pos].setYear(newYear);
		return;
	}
}

std::vector<Film> Repository::getFilms() const
{
	return films;
}

int Repository::findFilm(const Film & f)
{
	unsigned i;
	for (i = 0; i < films.size(); i++) {
		if (films[i].getTitle() == f.getTitle() && films[i].getYear() == f.getYear())
			return i;
	}
	return -1;
}

Film Repository::findByID(const std::string & title, unsigned year)
{
	for (unsigned i = 0; i < films.size(); i++)
		if (films[i].getTitle() == title && films[i].getYear() == year)
			return films[i];
	return Film();		//if there is no such film, returns empty film
}

void Repository::incLikes(const Film& f)
{
	int foundPos = findFilm(f);
	films[foundPos].incLikes();
}

int Repository::findUser(const std::string& userName)
{
	int found = -1;

	for (unsigned i = 0; i < users.size(); i++)
		if (users[i].userName == userName) {
			found = i;
			break;
		}
	return found;
}

void Repository::addUser(const User & u)
{
	users.push_back(u);
}

std::vector<User>& Repository::getUsers()
{
	return users;
}

int Repository::deleteUsersFilmFromWatchlist(const std::string& userName, const Film& f)
{
	try {
		int foundPos = findUser(userName);
		return users[foundPos].watchList.deleteFilm(f);
	}
	catch (FilmInWatchlist& e)
	{
		throw FilmInWatchlist();
	}
}

int Repository::addUsersFilmToWatchlist(const std::string & userName, const Film & f)
{
	try {
		int foundPos = findUser(userName);
		//return users[foundPos].watchList.add(f);
		users[foundPos].watchList.add(f);
	}
	catch (FilmInWatchlist& e) 
	{
		throw FilmInWatchlist();
	}
}
