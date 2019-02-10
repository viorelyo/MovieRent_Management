#pragma once
#include "Film.h"
#include "WatchList.h"
#include "MyExceptions.h"
#include <vector>


struct User {
	std::string userName;
	WatchList watchList;
};

class Repository
{
public:
	Repository() { }
	~Repository();


	void addFilm(const Film& f);
	int deleteFilm(const Film& f);
	void updateFilm(unsigned pos, const std::string& newTitle, const std::string& newGenre, const unsigned newYear);
	std::vector<Film> getFilms() const;
	int findFilm(const Film& f);
	Film findByID(const std::string & title, unsigned year);
	void incLikes(const Film&);

	int findUser(const std::string& userName);
	void addUser(const User& u);
	std::vector<User>& getUsers();
	int deleteUsersFilmFromWatchlist(const std::string& userName, const Film& f);
	int addUsersFilmToWatchlist(const std::string& userName, const Film& f);
protected:
	std::vector<Film> films;
	std::vector<User> users;
};

