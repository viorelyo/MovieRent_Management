#pragma once
#include <exception>


class FilmNotFound : public std::exception
{
public:
	const char* what() const throw()
	{
		return "The Film isn't in Repository.";
	}
};


class FilmInWatchlist : public std::exception
{
public:
	const char* what() const throw()
	{
		return "The Film isn't in Watchlist.";
	}
};