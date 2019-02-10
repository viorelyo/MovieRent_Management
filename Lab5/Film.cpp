#include "stdafx.h"
#include "Film.h"
#include <Windows.h>
#include <algorithm>	//used for replace()


Film::Film()
{
	title = "";
	year = 0;
}

Film::Film(const std::string & title, const std::string & genre, unsigned year)
{
	this->title = title;
	this->genre = genre;
	this->year = year;
	this->likes = 0;
	this->trailer = "https://www.google.com/search?q=" + title + "+trailer" + "&btnI=Search";		//url parameter for I'm Feeling Lucky
	std::replace(trailer.begin(), trailer.end(), ' ', '+');				// replace all ' ' to '+'  :needed for url request
}


Film::~Film()
{
}

std::string Film::getTitle() const
{
	return this->title;
}

std::string Film::getGenre() const
{
	return this->genre;
}

unsigned Film::getYear() const
{
	return this->year;
}

unsigned Film::getLikes() const
{
	return this->likes;
}

std::string Film::getTrailer() const
{
	return this->trailer;
}

void Film::setTitle(const std::string & title)
{
	this->title = title;

	this->trailer = "https://www.google.com/search?q=" + title + "+trailer" + "&btnI=Search";		//url parameter for I'm Feeling Lucky
	std::replace(trailer.begin(), trailer.end(), ' ', '+');				// replace all ' ' to '+'  :needed for url request
}

void Film::setGenre(const std::string & genre)
{
	this->genre = genre;
}

void Film::setYear(const unsigned year)
{
	this->year = year;
}

void Film::incLikes()
{
	this->likes += 1;
}

void Film::play()
{
	this->trailer = "https://www.google.com/search?q=" + title + "+trailer" + "&btnI=Search";		//url parameter for I'm Feeling Lucky
	std::replace(trailer.begin(), trailer.end(), ' ', '+');				// replace all ' ' to '+'  :needed for url request

	ShellExecuteA(NULL, NULL, "chrome.exe", this->trailer.c_str(), NULL, SW_SHOWMAXIMIZED);
}
