// Lab5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "UI.h"
#include <iostream>
#include <cassert>
#include "FileRepository.h"


void Tests()
{
	FileRepository repo;
	repo.setDB("test.csv");

	User u;
	u.userName = "tester";
	repo.addUser(u);
	repo.init_html("testerr.html");

	Controller ctrl(repo);

	ctrl.addFilmToRepo("Sherlock", "crime", 2008);
	ctrl.addFilmToRepo("V for Vendetta", "thriller", 2005);

	assert(ctrl.getRepo().getFilms().size() == 2);
	
	ctrl.updateFilmFromRepo(0, "Sherlock Holmes");
	assert(ctrl.getRepo().getFilms()[0].getTitle() == "Sherlock Holmes");
	ctrl.updateFilmFromRepo(0, "", "comedy");
	assert(ctrl.getRepo().getFilms()[0].getGenre() == "comedy");
	ctrl.updateFilmFromRepo(0, "", "", 2020);
	assert(ctrl.getRepo().getFilms()[0].getYear() == 2020);
	

	assert(ctrl.getFilmsGenre("thriller").size() == 1);

	ctrl.incLikes("Sherlock Holmes", 2020);
	assert(ctrl.getRepo().getFilms()[0].getLikes() == 1);

	ctrl.deleteFilmFromRepo("Sherlock Holmes", 2020);
	assert(ctrl.getRepo().getFilms().size() == 1);

	assert(ctrl.addFilmToRepo("V for Vendetta", "thriller", 2005) == -1);
	assert(ctrl.deleteFilmFromRepo("Sherlock Holmes", 2020) == -1);
	
	Film f2("V for Vendetta", "thriller", 2005);
	assert(ctrl.addFilmToWatchlist("tester", f2) == 0);
	assert(ctrl.addFilmToWatchlist("tester", f2) == -1);

	assert(ctrl.deleteFilmFromWatchlist("tester", "V for Vendetta", 2005) == 0);
	assert(ctrl.deleteFilmFromWatchlist("tester", "V for Vendetta", 2005) == -1);

	assert(Validation::validateTitle("") == -1);
	assert(Validation::validateGenre("") == -1);
	assert(Validation::validateYear("1700") == -1);
	assert(Validation::validateYear("test") == -2);
	assert(Validation::validateTitle("Test") == 0);
	assert(Validation::validateGenre("test") == 0);
	assert(Validation::validateYear("2016") == 2016);


	try
	{
		ctrl.getRepo().addFilm(f2);
	}
	catch (FilmNotFound& e)
	{
		assert(e.what() == "The Film isn't in Repository.");
	}

	Film f5("Westworld", "drama", 2016);
	try
	{
		ctrl.getRepo().deleteFilm(f5);
	}
	catch (FilmNotFound& e)
	{
		assert(e.what() == "The Film isn't in Repository.");
	}
	try
	{
		ctrl.getRepo().deleteUsersFilmFromWatchlist("tester", f5);
	}
	catch (FilmInWatchlist& e)
	{
		assert(e.what() == "The Film isn't in Watchlist.");
	}

	f5.setGenre("newTest");
	assert(f5.getGenre() == "newTest");
	f5.setYear(2020);
	assert(f5.getYear() == 2020);

	assert(repo.getUsers().size() == 1);
}



int main()
{
	//Tests();

	FileRepository repo;
	repo.setDB("DB.csv");
	repo.init_html("Db.html");
	repo.load_from_file();
	repo.setVectorToFile(repo.getFilms());
	repo.open();

	Film f1("Sherlock", "crime", 2008);
	Film f2("V for Vendetta", "thriller", 2005);
	Film f3("Inception", "thriller", 2010);
	Film f4("Game of Thrones", "drama", 2019);
	Film f5("Westworld", "drama", 2016);
	Film f6("Avengers", "action", 2012);
	Film f7("Wonder Woman", "fantasy", 2017);
	Film f8("Annihilation", "action", 2018);
	Film f9("Blade Runner 2049", "thriller", 2017);
	Film f10("True Detective", "crime", 2015);
	Film f11("True Detective", "crime", 2016);
	Film f12("True Detective", "crime", 2017);
	Film f13("True Detective", "crime", 2018);
	Film f14("True Detective", "crime", 2019);
	Film f15("True Detective", "crime", 2010);
	
	repo.add(f1);
	repo.add(f2);
	repo.add(f3);
	repo.add(f4);
	repo.add(f5);
	repo.add(f6);
	repo.add(f7);
	repo.add(f8);
	repo.add(f9);
	repo.add(f10);
	repo.add(f11);
	repo.add(f12);
	repo.add(f13);
	repo.add(f14);
	repo.add(f15);

	
	
	User u;
	u.userName = "viorel";
	repo.addUser(u);
	

	Controller ctrl(repo);


	UI ui(ctrl);
	ui.run();

    return 0;
}



