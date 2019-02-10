#pragma once
#include <string>


class Film
{
public:
	Film();
	Film(const std::string& title, const std::string& genre, unsigned year);
	~Film();

	std::string getTitle() const;
	std::string getGenre() const;
	unsigned getYear() const;
	unsigned getLikes() const;
	std::string getTrailer() const;

	void setTitle(const std::string&);
	void setGenre(const std::string&);
	void setYear(const unsigned);
	void incLikes();
	
	void play();

private:
	std::string title;
	std::string genre;
	unsigned year;
	unsigned likes;
	std::string trailer;
};

