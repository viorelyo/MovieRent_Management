#include "stdafx.h"
#include "FileTypes.h"
#include <Windows.h>


std::vector<Film> CSVFileReader::read(std::ifstream & file)
{
	std::string title;
	std::string genre;
	std::string year;
	std::vector<Film> all;

	while (!file.eof())
	{
		std::getline(file, title, ',');
		std::getline(file, genre, ',');
		std::getline(file, year);

		Film f(title, genre, std::stoi(year));
		//std::cout << title << " " << genre << " " << year << std::endl;
		all.push_back(f);
	}
	all.pop_back();

	return all;
}

void CSVFileWriter::write(std::ofstream& file, const std::vector<Film>& v)
{
	for (unsigned i = 0; i < v.size(); i++) {
		file << v[i].getTitle() << "," << v[i].getGenre() << "," << std::to_string(v[i].getYear()) << "\n";
	}
}

void CSVFileWriter::open(const std::string & filename)
{
	ShellExecuteA(NULL, NULL, "Excel.exe", filename.c_str(), NULL, SW_SHOWMAXIMIZED);
}


void HTMLFileWriter::write(std::ofstream & file, const std::vector<Film>& v)
{
	file << spawnHTMLHeader();

	for (unsigned i = 0; i < v.size(); i++)
		file << spawnNewRow(v[i]);

	file << spawnHTMLFooter();
}

void HTMLFileWriter::open(const std::string & filename)
{
	ShellExecuteA(NULL, NULL, "chrome.exe", filename.c_str(), NULL, SW_SHOWMAXIMIZED);
}


std::string HTMLFileWriter::spawnHTMLHeader()
{
	std::string header = "<!DOCTYPE html> \
						<html lang=\"en\"> \
						<head> \
							<title>Watchlist</title> \
							<meta charset=\"UTF-8\"> \
							<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \
						<!--===============================================================================================-->	 \
							<link rel=\"icon\" type=\"image/png\" href=\"images/icons/play.ico\"/> \
						<!--===============================================================================================--> \
							<link rel=\"stylesheet\" type=\"text/css\" href=\"vendor/bootstrap/css/bootstrap.min.css\"> \
						<!--===============================================================================================--> \
							<link rel=\"stylesheet\" type=\"text/css\" href=\"fonts/font-awesome-4.7.0/css/font-awesome.min.css\"> \
						<!--===============================================================================================--> \
							<link rel=\"stylesheet\" type=\"text/css\" href=\"vendor/animate/animate.css\"> \
						<!--===============================================================================================--> \
							<link rel=\"stylesheet\" type=\"text/css\" href=\"vendor/select2/select2.min.css\"> \
						<!--===============================================================================================--> \
							<link rel=\"stylesheet\" type=\"text/css\" href=\"vendor/perfect-scrollbar/perfect-scrollbar.css\"> \
						<!--===============================================================================================--> \
							<link rel=\"stylesheet\" type=\"text/css\" href=\"css/util.css\"> \
							<link rel=\"stylesheet\" type=\"text/css\" href=\"css/main.css\"> \
						<!--===============================================================================================--> \
						</head> \
						<body> \
							 \
							<div class=\"limiter\"> \
								<div class=\"container-table100\"> \
									<div class=\"wrap-table100\"> \
										<div class=\"table100 ver1 m-b-110\"> \
											<div class=\"table100-head\"> \
												<table> \
													<thead> \
														<tr class=\"row100 head\"> \
															<th class=\"cell100 column1\">Title</th> \
															<th class=\"cell100 column2\">Genre</th> \
															<th class=\"cell100 column3\">Year</th> \
															<th class=\"cell100 column4\">Likes</th> \
															<th class=\"cell100 column5\">Trailer</th> \
														</tr> \
													</thead> \
												</table> \
											</div>\
		<div class = \"table100-body js-pscroll\"> \
						<table> \
							<tbody> ";
	return header;
}

std::string HTMLFileWriter::spawnHTMLFooter()
{
	std::string footer = "							</tbody> \
													</table> \
												</div> \
											</div> \
										</div> \
									</div> \
								</div> \
							<!--===============================================================================================-->	 \
								<script src=\"vendor/jquery/jquery-3.2.1.min.js\"></script> \
							<!--===============================================================================================--> \
								<script src=\"vendor/bootstrap/js/popper.js\"></script> \
								<script src=\"vendor/bootstrap/js/bootstrap.min.js\"></script> \
							<!--===============================================================================================--> \
								<script src=\"vendor/select2/select2.min.js\"></script> \
							<!--===============================================================================================--> \
								<script src=\"vendor/perfect-scrollbar/perfect-scrollbar.min.js\"></script> \
								<script> \
									$('.js-pscroll').each(function(){ \
										var ps = new PerfectScrollbar(this); \
								\
										$(window).on('resize', function(){ \
											ps.update(); \
										}) \
									}); \
											\
										\
								</script> \
							<!--===============================================================================================--> \
								<script src=\\\"js / main.js\\\"></script> \
							</body> \
							</html>";

	return footer;
}

std::string HTMLFileWriter::spawnNewRow(const Film & f)
{
	std::string newRow = "<tr class=\"row100 body\"> \
									<td class=\"cell100 column1\">" + f.getTitle() + "</td> \
									<td class=\"cell100 column2\">" + f.getGenre() + "</td> \
									<td class=\"cell100 column3\">" + std::to_string(f.getYear()) + "</td> \
									<td class=\"cell100 column4\">" + std::to_string(f.getLikes()) + "</td> \
									<td class=\"cell100 column5\"><a href =\"" + f.getTrailer() + "\">" + f.getTitle() + "</a></td> \
								</tr> ";

	return newRow;
}
