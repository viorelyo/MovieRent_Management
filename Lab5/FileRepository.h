#pragma once
#include "Repository.h"
#include "iFileManager.h"
#include "FileTypes.h"
#include <iostream>
#include <memory>


class FileRepository : public Repository
{
public:
	FileRepository() : Repository() 
	{
		iFileSaver.reset(new CSVFileWriter);
		iFileReader.reset(new CSVFileReader);
		this->vectorInitialized = false;
	}
	FileRepository(const FileRepository& other) {
		films = other.films;
		users = other.users;
		filename = other.filename;
		this->iFileReader = std::move(other.iFileReader);
		this->iFileSaver = std::move(other.iFileSaver);
		this->iFileWriterr = std::move(other.iFileWriterr);
		this->mainFilename = other.mainFilename;
	}
	FileRepository& operator = (FileRepository &other) {			//copy constructor
		films = other.films;
		users = other.users;
		filename = other.filename;
		mainFilename = other.mainFilename;
	}
	
	~FileRepository();
	void setDB(const std::string& mainFilename)
	{
		this->mainFilename = mainFilename;
	}
	void init_csv(const std::string& filename);
	void init_html(const std::string& filename);

	void setVectorToFile(const std::vector<Film>& v);
	void add(const Film& f);
	void update(unsigned pos, const std::string& newTitle, const std::string& newGenre, const unsigned newYear);
	void remove(const Film & f);
	void addWatchList(const std::string & userName, const Film & f);
	void deleteFromWatchlist(const std::string& userName, const Film& f);

	void load_from_file();
	void open();
	void save_file();
private:
	std::string mainFilename;
	std::string filename;
	bool vectorInitialized;
	std::vector<Film> vectorToSaveToFile;
	std::shared_ptr<iFileReader> iFileReader;
	std::shared_ptr<iFileWriter> iFileWriterr;
	std::shared_ptr<iFileWriter> iFileSaver;
};







