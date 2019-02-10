#pragma once
#include <Windows.h>
#include <string>
#include "Controller.h"
#include "Validation.h"

class UI
{
public:
	UI(const Controller& c) : ctrl(c) {}
	~UI();
	void run();
private:
	Controller ctrl;

	HANDLE consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);
	enum CursorMode
	{
		CURSOR_ON,
		CURSOR_OFF,
		CURSOR_BIG
	};
	int countLine = 1;			

	std::string userName;
	WatchList newWatchList;
	bool newCustomer = false;
	int posUser;
	

	void setMyCursor(CursorMode cursorMode);
	void setColor(const WORD newColorToSet);
	int whereX();
	int whereY();
	void gotoxy(const int x, const int y);
	void clearArea(int x1, int y1, int x2, int y2);
	void box(int x1, int y1, int x2, int y2);
	void showTextInBox(const std::string& shownInfo, bool newBeginKey, bool controlKey, int x1, int y1, int x2, int y2);
	void showLeftSide(const std::string& shownInfo, bool newBeginKey = 0);
	void footerLine(const std::string& footString, int x1, int y1, int x2, int y2);
	void warningBottom(const std::string& msg, int x1, int y1, int x2, int y2);
	void lineBox(const std::string& footString, int x1, int y1, int x2, int y2);
	void showMore();
	void movieIcon(int, int);
	void movieIconLoad(int, int);
	void landing();
	int authentification();
	int admin();
	void menuAdminAdd();
	void menuAdminUpdate();
	void menuAdminDelete();
	void typoEffect(const std::string& text);
	void dialogUser(const std::string& text1, int x1, int y1, int y2, int lines = 1, const std::string& text2 = "", int colorSetFirst = 0);
	void user();
	int userSetup();
	void menuGenre();
	void menuWatchList();
};

