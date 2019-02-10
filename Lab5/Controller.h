#pragma once
#include "FileRepository.h"
#include <string>


class Controller
{
public:
	Controller(FileRepository& r) : repo(r) {}
	~Controller();
	FileRepository getRepo() const;

	int addFilmToRepo(const std::string& title, const std::string& genre, unsigned year);
	void updateFilmFromRepo(unsigned pos, const std::string & newTitle = "", const std::string & newGenre = "", const unsigned newYear = 0);
	int deleteFilmFromRepo(const std::string& title, unsigned year);

	std::vector<Film> getFilmsGenre(const std::string& genre) const;
	void incLikes(const std::string& title, unsigned year);

	void addNewUserToRepo(const User& u);
	int deleteFilmFromWatchlist(const std::string& userName, const std::string& title, unsigned year);
	int addFilmToWatchlist(const std::string& userName, const Film&);

	void selectFileType(const std::string& userName, const std::string& fileType);
	void setListForFileRepo(const std::vector<Film>& v);
	void saveFile();
	void openFileInApp();
private:
	FileRepository repo;
};

