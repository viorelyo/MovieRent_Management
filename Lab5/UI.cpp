#include "stdafx.h"
#include "UI.h"
#include <iostream>
#include <iomanip>		//used for setw()
#include <conio.h>		//used for _getch()
#include <thread>		//used for this_thread::sleep_for()
#include <chrono>		//used for chrono::milliseconds()


UI::~UI()
{
}


void UI::setMyCursor(CursorMode cursorMode)
{
	/*
	*	Set cursor mode
	*/

	if (consoleHandler == INVALID_HANDLE_VALUE)
		return;

	CONSOLE_CURSOR_INFO cursorInfo;

	switch (cursorMode)
	{
	case CURSOR_OFF:
		cursorInfo.bVisible = false;
		cursorInfo.dwSize = 10;
		break;
	case CURSOR_ON:
		cursorInfo.bVisible = TRUE;
		cursorInfo.dwSize = 10;
		break;
	case CURSOR_BIG:
		cursorInfo.bVisible = TRUE;
		cursorInfo.dwSize = 100;
		break;
	}

	SetConsoleCursorInfo(consoleHandler, &cursorInfo);
}

void UI::setColor(const WORD newColorToSet)
{
	/*
	*	Set Console Display Color to specified one
	*/

	if (consoleHandler == INVALID_HANDLE_VALUE)
		return;

	SetConsoleTextAttribute(consoleHandler, newColorToSet);
}

int UI::whereX() {
	/*
	*	Get current cursor position on X dimension
	*/

	if (consoleHandler == INVALID_HANDLE_VALUE)
		return 0;

	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	GetConsoleScreenBufferInfo(consoleHandler, &screenInfo);

	return screenInfo.dwCursorPosition.X + 1;
}

int UI::whereY() {
	/*
	*	Get current cursor position on Y dimension
	*/

	if (consoleHandler == INVALID_HANDLE_VALUE)
		return 0;

	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	GetConsoleScreenBufferInfo(consoleHandler, &screenInfo);

	return screenInfo.dwCursorPosition.Y + 1;
}

void UI::gotoxy(const int x, const int y)
{
	/*
	*	Set cursor to given position
	*/

	if (consoleHandler == INVALID_HANDLE_VALUE)
		return;

	COORD coords = { short(x - 1), short(y - 1) };
	SetConsoleCursorPosition(consoleHandler, coords);
}

void UI::clearArea(int x1, int y1, int x2, int y2) {
	int i, j;
	gotoxy(x1, y1);

	setMyCursor(CURSOR_OFF);
	for (j = y1; j <= y2; j++)
		for (i = x1; i <= x2; i++) {
			gotoxy(i, j);
			std::cout << " ";
		}

	setMyCursor(CURSOR_ON);
	//gotoxy(x, y);
}

void UI::box(int x1, int y1, int x2, int y2) {
	/*
	*	Create box with given Coordinates
	*/

	unsigned char topLeft = 201;
	unsigned char horizontalLines = 205;
	unsigned char topRight = 187;
	unsigned char verticalLines = 186;
	unsigned char bottomLeft = 200;
	unsigned char bottomRight = 188;

	int i;

	setMyCursor(CURSOR_OFF);

	gotoxy(x1, y1);			//left top corner
	std::cout << topLeft;
	for (i = x1 + 1; i < x2; i++)
		std::cout << horizontalLines;
	gotoxy(x2, y1); 		//right top corner
	std::cout << topRight;
	for (i = y1 + 1; i < y2; i++) {
		// Vertical lines
		gotoxy(x1, i);			//left vLine
		std::cout << verticalLines;
		gotoxy(x2, i);			//right vLine
		std::cout << verticalLines;
	}
	gotoxy(x1, y2);
	std::cout << bottomLeft; 	//left bottom corner
	for (i = x1 + 1; i < x2; i++)
		std::cout << horizontalLines;		//bottom line
	gotoxy(x2, y2);
	std::cout << bottomRight;			//right bottom corner

	//gotoxy(xBegin, yBegin);
	setMyCursor(CURSOR_ON);
}

void UI::showTextInBox(const std::string& shownInfo, bool newBeginKey, bool controlKey, int x1, int y1, int x2, int y2) {
	/*
	*	Show given info on the screen in specified box
	*/

	setMyCursor(CURSOR_OFF);
	box(x1, y1, x2, y2);
	x1++;
	x2--;
	y2--;
	int xBegin = whereX();
	int yBegin = whereY();

	if (newBeginKey == 1) {
		clearArea(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
		countLine = y1 + 1;
	}
	countLine++;

	gotoxy(x1 + 1, countLine);

	unsigned placeHolder = 0;
	unsigned letterCounterBegin = 0;
	unsigned letterCounterEnd = 0;
	unsigned xPixel;
	unsigned yPixel;
	bool equalityKey = false;
	bool lastLine = false;
	char letter;
	while (letterCounterBegin < shownInfo.length())
	{
		letter = shownInfo[letterCounterBegin];
		if (letter != ' ')
		{
			placeHolder = letterCounterBegin;
			while (letter != ' ' && letterCounterBegin < shownInfo.length())
			{
				letterCounterBegin++;
				letter = shownInfo[letterCounterBegin];
			};
		};

		xPixel = whereX();
		yPixel = whereY();

		if (countLine == y2 - 1 && controlKey == 0 && ((letterCounterBegin - placeHolder) >= (x2 - xPixel)))
		{
			countLine = y1 + 1;
			clearArea(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
			gotoxy(x1 + 1, countLine);
		}
		if (countLine == y2 - 1 && controlKey == 1 && ((letterCounterBegin - placeHolder) >= (x2 - xPixel)))
		{
			countLine = y1 + 1;
			setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
			getchar();
			clearArea(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
			setColor(FOREGROUND_GREEN);
			clearArea(1, 24, 80, 24);
			gotoxy(x1 + 2, countLine + 1);
		}
		if ((letterCounterBegin - placeHolder) < (x2 - xPixel))
		{
			for (;placeHolder < letterCounterBegin; placeHolder++)
				std::cout << shownInfo[placeHolder];
		}

		else if ((letterCounterBegin - placeHolder) < x2 - x1)
		{
			countLine++;
			gotoxy(x1 + 1, countLine);
			for (;placeHolder < letterCounterBegin; placeHolder++)
				std::cout << shownInfo[placeHolder];
		}
		else
		{
			for (;placeHolder < letterCounterBegin; placeHolder++)
			{
				int xPixel2 = whereX();
				if (xPixel2 == x2) {
					countLine++;
					gotoxy(x1 + 1, countLine);
				}
				std::cout << shownInfo[placeHolder];
			}

		}
		letterCounterBegin++;
		if (whereX() != x2 - 1)
			std::cout << (" ");
	}
}


void UI::showLeftSide(const std::string& shownInfo, bool newBeginKey) {
	/*
	*	Show given items as menu on the left side
	*/

	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	GetConsoleScreenBufferInfo(consoleHandler, &screenInfo);
	setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);
	showTextInBox(shownInfo, newBeginKey, 1, 5, 13, 27, 23);			//left - menu box
	setColor(screenInfo.wAttributes);
}

void UI::footerLine(const std::string& footString, int x1, int y1, int x2, int y2) {
	/*
	*	Set the text at the bottom (option)
	*/

	clearArea(x1+1, y1+1, x2-1, y2-1);
	box(x1, y1, x2, y2); 		//bottom box

	gotoxy(x1+2, y1+1);
	setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);

	char dash = 95;
	std::cout << footString << dash;
	gotoxy(whereX() - 1, whereY());
}

void UI::warningBottom(const std::string & msg, int x1, int y1, int x2, int y2)
{
	/*
	*	Set the warning text at the bottom (option)
	*/

	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	GetConsoleScreenBufferInfo(consoleHandler, &screenInfo);			//save previous state of the console

	clearArea(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
	box(x1, y1, x2, y2); 		//bottom box

	gotoxy(x1 + 2, y1 + 1);
	setColor(FOREGROUND_RED | BACKGROUND_INTENSITY);

	//Blinking error message
	char dash = 95;
	std::cout << msg << dash;
	Sleep(500);
	clearArea(x1 + 1, y1 + 1, x2 - 1, y2 - 1);
	Sleep(200);
	gotoxy(x1 + 2, y1 + 1);
	std::cout << msg << dash;
	Sleep(800);
	gotoxy(whereX() - 1, whereY());
	setColor(screenInfo.wAttributes);
}

void UI::lineBox(const std::string& footString, int x1, int y1, int x2, int y2) {
	/*
	*	Set the text at the bottom (option)
	*/

	int strLength = footString.length();
	clearArea(x1, y1, x2, y2);
	box(x1, y1, x2, y2); 		//authentification box

	strLength /= 2;
	gotoxy(x1 + 2, y1 + 1);
	setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);

	char dash = 95;
	std::cout << footString << dash;
	gotoxy(whereX() - 1, whereY());
	setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
}

void UI::showMore()
{
	/*
		Show box with All movies
		Box is created dinamically, depending on number of films
	*/

	if (ctrl.getRepo().getFilms().size() > 12) {
		setMyCursor(CURSOR_OFF);
		clearArea(1, 1, 80, 24);
		box(29, 3, 78, 6 + ctrl.getRepo().getFilms().size());

		setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);
		int Ox = 31;
		int Oy = 4;
		gotoxy(Ox, Oy);
		std::cout << std::setw(20) << "Title" << std::setw(10) << "Genre" << std::setw(7) << "Year" << std::setw(8) << "Likes";
		gotoxy(Ox, ++Oy);
		std::cout << "----------------------------------------------";

		std::vector<Film> allFilms = ctrl.getRepo().getFilms();
		for (unsigned i = 0; i < allFilms.size(); i++) {
			gotoxy(Ox, ++Oy);
			std::cout << std::setw(20) << allFilms[i].getTitle() << std::setw(10) << allFilms[i].getGenre() << std::setw(7) << allFilms[i].getYear() << std::setw(8) << allFilms[i].getLikes();
		}

		std::cin.get();
		setMyCursor(CURSOR_ON);
		setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
	}
}

void UI::movieIcon(int x, int y)
{
	/*
		Display the INTRO Movie LOGO
	*/

	unsigned char top = 223;
	unsigned char bottom = 220;
	unsigned char full = 219;

	int Ox, Oy, i, j;
	int rightBorder = 40 + x % 10 + x / 10 * 10;

	Ox = x;
	Oy = y;
	
	//BODY
	for (i = 0; i < 9; i++) {		
		gotoxy(Ox, Oy++);
		for (j = 0; j < 15; j++)	
			std::cout << full;
	}
	
	//Top of the Play Button
	Ox = x + 15;
	Oy = y;
	gotoxy(Ox, Oy);
	for (i = 0; i < 5; i++) {
		std::cout << top;
		for (j = Ox; j < rightBorder; j++)
			std::cout << full;
		Ox += 3;
		gotoxy(Ox, ++Oy);
	}
	//Bottom of the Play Button
	Ox = x + 15;
	Oy = y + 8;
	gotoxy(Ox, Oy);

	std::cout << bottom;
	for (j = Ox; j < rightBorder; j++)
		std::cout << full;
	gotoxy(Ox += 3, --Oy);

	for (i = 0; i < 2; i++) {
		std::cout << bottom << bottom;
		for (j = Ox; j < rightBorder - 1; j++)
			std::cout << full;
		gotoxy(Ox += 4, --Oy);
	}

	std::cout << bottom;
	for (j = Ox; j < rightBorder; j++)
		std::cout << full;


	//Top Part
	int partsRight = 52;

	Ox = x - 5;
	Oy = y - 5;
	gotoxy(Ox, Oy);
	for (j = 0; j < partsRight; j++)
		std::cout << full;
	gotoxy(Ox, ++Oy);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++)
			std::cout << full;
		gotoxy(Ox, ++Oy);
	}
	for (j = 0; j < partsRight; j++)
		std::cout << full;

	Ox = rightBorder + 3;
	Oy = y - 4;
	gotoxy(Ox, Oy);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++)
			std::cout << full;
		gotoxy(Ox, ++Oy);
	}
	
	//Squares
	Ox = x - 5 + 4;
	
	for (int k = 0; k < 3; k++) {
		Ox += 6;
		Oy = y - 4;

		gotoxy(Ox, Oy);
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 6; j++) 
				std::cout << full;
			gotoxy(Ox, ++Oy);
		}
		Ox += 7;
	}


	//Bottom Part
	Ox = x - 5;
	Oy = y + 9;
	gotoxy(Ox, Oy);
	for (j = 0; j < partsRight; j++)
		std::cout << full;
	gotoxy(Ox, ++Oy);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++)
			std::cout << full;
		gotoxy(Ox, ++Oy);
	}
	for (j = 0; j < partsRight; j++)
		std::cout << full;

	Ox = rightBorder + 3;
	Oy = y + 9;
	gotoxy(Ox, Oy);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
			std::cout << full;
		gotoxy(Ox, ++Oy);
	}

	//Squares
	Ox = x - 5 + 4;

	for (int k = 0; k < 3; k++) {
		Ox += 6;
		Oy = y + 9;

		gotoxy(Ox, Oy);
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 6; j++)
				std::cout << full;
			gotoxy(Ox, ++Oy);
		}
		Ox += 7;
	}


	gotoxy(x + 50, y + 15);
}

void UI::movieIconLoad(int x, int y)
{
	/*
		Hover Animation - Loading
		Copy of movieIcon function
	*/

	unsigned char top = 223;
	unsigned char bottom = 220;
	unsigned char full = 219;

	int Ox, Oy, i, j;
	int rightBorder = 40 + x % 10 + x / 10 * 10;
	int partsRight = 52;


	//Top Part
	Ox = x - 5;
	Oy = y - 5;
	gotoxy(Ox, Oy);
	for (j = 0; j < partsRight; j++)
		std::cout << full;
	Sleep(100);
	gotoxy(Ox, ++Oy);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++)
			std::cout << full;
		gotoxy(Ox, ++Oy);
		Sleep(100);
	}
	for (j = 0; j < partsRight; j++)
		std::cout << full;
	Sleep(100);

	Ox = rightBorder + 3;
	Oy = y - 4;
	gotoxy(Ox, Oy);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++)
			std::cout << full;
		gotoxy(Ox, ++Oy);
		Sleep(100);
	}

	//Squares
	Ox = x - 5 + 4;

	for (int k = 0; k < 3; k++) {
		Ox += 6;
		Oy = y - 4;

		gotoxy(Ox, Oy);
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 6; j++)
				std::cout << full;
			gotoxy(Ox, ++Oy);
			Sleep(100);
		}
		Ox += 7;
	}

	//BODY
	Ox = x;
	Oy = y;

	for (i = 0; i < 9; i++) {
		gotoxy(Ox, Oy++);
		for (j = 0; j < 15; j++)
			std::cout << full;
		Sleep(100);
	}

	//Top of the Play Button
	Ox = x + 15;
	Oy = y;
	gotoxy(Ox, Oy);
	for (i = 0; i < 5; i++) {
		std::cout << top;
		for (j = Ox; j < rightBorder; j++)
			std::cout << full;
		Ox += 3;
		gotoxy(Ox, ++Oy);
		Sleep(150);
	}
	//Bottom of the Play Button
	Ox = x + 15;
	Oy = y + 8;
	gotoxy(Ox, Oy);

	std::cout << bottom;
	for (j = Ox; j < rightBorder; j++)
		std::cout << full;
	gotoxy(Ox += 3, --Oy);
	Sleep(100);

	for (i = 0; i < 2; i++) {
		std::cout << bottom << bottom;
		for (j = Ox; j < rightBorder - 1; j++)
			std::cout << full;
		gotoxy(Ox += 4, --Oy);
		Sleep(150);
	}

	std::cout << bottom;
	for (j = Ox; j < rightBorder; j++)
		std::cout << full;
	Sleep(100);
	//Bottom Part
	Ox = x - 5;
	Oy = y + 9;
	gotoxy(Ox, Oy);
	for (j = 0; j < partsRight; j++)
		std::cout << full;
	gotoxy(Ox, ++Oy);
	Sleep(100);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++)
			std::cout << full;
		gotoxy(Ox, ++Oy);
		Sleep(100);
	}
	for (j = 0; j < partsRight; j++)
		std::cout << full;
	Sleep(100);

	Ox = rightBorder + 3;
	Oy = y + 9;
	gotoxy(Ox, Oy);
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++)
			std::cout << full;
		gotoxy(Ox, ++Oy);
	}

	//Squares
	Ox = x - 5 + 4;

	for (int k = 0; k < 3; k++) {
		Ox += 6;
		Oy = y + 9;

		gotoxy(Ox, Oy);
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 6; j++)
				std::cout << full;
			gotoxy(Ox, ++Oy);
			Sleep(100);
		}
		Ox += 7;
	}
}

void UI::landing()
{
	/*
		Assembly the Intro DRAW + ANIMATION
	*/

	setMyCursor(CURSOR_OFF);
	system("color 8B");
	movieIcon(30, 10);
	Sleep(500);

	setColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
	movieIconLoad(30, 10);
	Sleep(700);

	system("color 8B");
	setMyCursor(CURSOR_ON);
}

int UI::authentification()
{
	system("color 8B");
	clearArea(0, 0, 81, 30);
	box(26, 6, 81, 19);		//Main BOX

	int Ox = 41;			//position of LOGO
	int Oy = 7;
	gotoxy(Ox, Oy);

	std::string iconChar = "                   _      ";
	std::cout << iconChar;
	gotoxy(Ox, ++Oy);
	iconChar = "  /\\/\\   _____   _(_)_  __";
	std::cout << iconChar;
	gotoxy(Ox, ++Oy);
	iconChar = " /    \\ / _ \\ \\ / / \\ \\/ /";
	std::cout << iconChar;
	gotoxy(Ox, ++Oy);
	iconChar = "/ /\\/\\ \\ (_) \\ V /| |>  < ";
	std::cout << iconChar;
	gotoxy(Ox, ++Oy);
	iconChar = "\\/    \\/\\___/ \\_/ |_/_/\\_\\";
	std::cout << iconChar;
	gotoxy(Ox, ++Oy);

	userName = "";
	lineBox("Username: ", 41, ++Oy, 64, Oy+2);
	std::getline(std::cin, userName);
	//std::cin.ignore(); 
	Oy += 3;
	if (userName == "")
		return 0;
	else if (userName == "admin") {
		std::string pass = "";
		char ch;
		lineBox("Password: ", 41, Oy, 64, Oy + 2);		//++Oy
		ch = _getch();
		while (ch != 13) {			//13 stands for ENTER
			if (ch == '\b') {		// working backspace 
				pass.pop_back();
				std::cout << "\b \b";
			}
			else {
				pass.push_back(ch);
				std::cout << '*';
			}
			ch = _getch();
		}

		//Password VALIDATION
		while (pass != "1111") {
			setMyCursor(CURSOR_OFF);
			setColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
			std::cout << "    No!";
			Sleep(700);
			clearArea(58, Oy + 1, 63, Oy);			
			Sleep(700);
			gotoxy(57, Oy);
			std::cout << "    No!";
			setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);

			//PASSWORD INPUT
			clearArea(41, Oy, 64, Oy + 2);
			pass = "";
			lineBox("Password: ", 41, Oy, 64, Oy + 2);		//++Oy
			ch = _getch();
			while (ch != 13) {			//13 stands for ENTER
				if (ch == '\b') {		// working backspace
					pass.pop_back();
					std::cout << "\b \b";
				}
				else {
					pass.push_back(ch);
					std::cout << '*';
				}
				ch = _getch();
			}	
		}

		setMyCursor(CURSOR_OFF);
		setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		std::cout << "   yay!";
		Sleep(700);
		clearArea(58, ++Oy, 63, Oy);
		Sleep(700);
		gotoxy(57, Oy);
		std::cout << "   yay!";
		setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		return 2;			//if return 2 -> admin
	}
	else
		return 1;		//if return 1 - then authentification for user
}

int UI::admin()
{
	system("color 8B");
	clearArea(0, 0, 80, 30);
	box(5, 2, 27, 12);		//Icon BOX
	box(4, 2, 80, 24);		//Main BOX
	box(29, 3, 78, 20);		//view movies BOX

	int Ox = 6;
	int Oy = 3;
	gotoxy(Ox, Oy);
	setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);
	std::string iconChar = "   .\"\"\"-. ";
	std::cout << iconChar;
	gotoxy(Ox, ++Oy);
				iconChar = "  /      \\ ";
	std::cout << iconChar;
	gotoxy(Ox, ++Oy);
				iconChar = "  |  _..--'-.";
	std::cout << iconChar;
	gotoxy(Ox, ++Oy);
				iconChar = "  >.`__.-\"\";\"`";
	std::cout << iconChar;
	gotoxy(Ox, ++Oy);
				iconChar = " / /(     ^\\ ";
	std::cout << iconChar;
	gotoxy(Ox, ++Oy);
				iconChar = " '-`)     =|-.";
	std::cout << iconChar;
	gotoxy(Ox, ++Oy);
				iconChar = "   /`--.'--'   \\ .-.";
	std::cout << iconChar;
	gotoxy(Ox, ++Oy);
				iconChar = " .'`-._ `.\\    | J /";
	std::cout << iconChar;
	gotoxy(Ox, ++Oy);
				iconChar = "/      `--.|   \\__/";
	std::cout << iconChar;
	gotoxy(Ox, ++Oy);

	
	showLeftSide("    ADMIN    ", 1);
	showLeftSide("    -----    ");
	showLeftSide(" 0 EXIT");
	showLeftSide(" 1 ADD Movie");
	showLeftSide(" 2 UPDATE Movie");
	showLeftSide(" 3 DELETE Movie");
	showLeftSide(" 4 View All");

	
	//Show MOVIES in Box (MAX - 15)
	Ox = 31;
	Oy = 4;
	gotoxy(Ox, Oy);
	std::cout << std::setw(20) << "Title" << std::setw(10) << "Genre" << std::setw(7) << "Year" << std::setw(8) << "Likes";
	gotoxy(Ox, ++Oy);
	std::cout << "----------------------------------------------";

	std::vector<Film> allFilms = ctrl.getRepo().getFilms();
	for (unsigned i = 0; i < allFilms.size() && i <= 12; i++) {
		gotoxy(Ox, ++Oy);
		std::cout << std::setw(20) << allFilms[i].getTitle() << std::setw(10) << allFilms[i].getGenre() << std::setw(7) << allFilms[i].getYear() << std::setw(8) << allFilms[i].getLikes();
	}
	if (allFilms.size() > 12) {			//If not all films fit in the reserved box : "..." are displayed for SHOW MORE
		gotoxy(Ox, ++Oy);
		std::cout << "                    ...";
	}



	//Show BOTTOM MENU - Interaction with admin
	setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
	footerLine("$>> ", 30, 21,  76,  23);		//Option BOX
	setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);
	int option = 0;
	Ox = whereX();
	Oy = whereY();
	std::cin >> option;
	std::cin.ignore();
	setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
	while (option < 0 || option > 4) {
		setMyCursor(CURSOR_OFF);
		setColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		gotoxy(Ox + 16, Oy);
		std::cout << "No!";
		Sleep(700);
		clearArea(59, 22, 65, 22);
		Sleep(700);
		gotoxy(Ox + 16, Oy);
		std::cout << "No!";
		Sleep(700);
		setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		option = 0;
		footerLine("$>> ", 30, 21,  76,  23);		//Option BOX
		setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);
		setMyCursor(CURSOR_ON);
		std::cin >> option;
		std::cin.ignore();
		setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
	}
	
	return option;
}

void UI::menuAdminAdd()
{
	std::string title;
	std::string genre;
	std::string year;
	int Ox, Oy;


	footerLine("$Title: ", 30, 21,  76,  23);
	Ox = whereX();
	Oy = whereY();
	std::getline(std::cin, title);
	while (Validation::validateTitle(title) != 0) {
		setColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		gotoxy(Ox, Oy);
		std::cout << "Not empty!";
		Sleep(700);
		setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		footerLine("$Title: ", 30, 21,  76,  23);
		std::getline(std::cin, title);
	}

	setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
	footerLine("$Genre: ", 30, 21,  76,  23);
	Ox = whereX();
	Oy = whereY();
	std::getline(std::cin, genre);
	while (Validation::validateGenre(genre) != 0) {
		setColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		gotoxy(Ox, Oy);
		std::cout << "Not empty!";
		Sleep(700);
		setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		footerLine("$Genre: ", 30, 21,  76,  23);
		std::getline(std::cin, genre);
	}

	setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
	footerLine("$Year: ", 30, 21,  76,  23);
	Ox = whereX();
	Oy = whereY();
	std::getline(std::cin, year);
	while (Validation::validateYear(year) == -1 || Validation::validateYear(year) == -2) {
		setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		footerLine("$Year: ", 30, 21,  76,  23);
		setColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		gotoxy(Ox, Oy);
		if (Validation::validateYear(year) == -1)
			std::cout << "Between 1900 & 2025!";
		else if (Validation::validateYear(year) == -2)
			std::cout << "Number!";
		Sleep(1000);
		setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		footerLine("$Year: ", 30, 21,  76,  23);
		std::getline(std::cin, year);
	}

	if (ctrl.addFilmToRepo(title, genre, Validation::validateYear(year)) == -1)
		warningBottom(title + " exists!", 30, 21, 76, 23);
}

void UI::menuAdminUpdate()
{
	std::string title;
	std::string year;
	std::string genre;

	int Ox, Oy;

	footerLine("$Title: ", 30, 21, 76, 23);
	Ox = whereX();
	Oy = whereY();
	std::getline(std::cin, title);
	while (Validation::validateTitle(title) != 0) {
		setColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		gotoxy(Ox, Oy);
		std::cout << "Not empty!";
		Sleep(700);
		setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		footerLine("$Title: ", 30, 21, 76, 23);
		std::getline(std::cin, title);
	}

	setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
	footerLine("$Year: ", 30, 21, 76, 23);
	Ox = whereX();
	Oy = whereY();
	std::getline(std::cin, year);
	while (Validation::validateYear(year) == -1 || Validation::validateYear(year) == -2) {
		setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		footerLine("$Year: ", 30, 21, 76, 23);
		setColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		gotoxy(Ox, Oy);
		if (Validation::validateYear(year) == -1)
			std::cout << "Between 1900 & 2025!";
		else if (Validation::validateYear(year) == -2)
			std::cout << "Number!";
		Sleep(1000);
		setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		footerLine("$Year: ", 30, 21, 76, 23);
		std::getline(std::cin, year);
	}

	//Search the film
	int exists = ctrl.getRepo().findFilm(ctrl.getRepo().findByID(title, Validation::validateYear(year)));		
	if (exists == -1) {
		warningBottom(title + " doesn't exists!", 30, 21, 76, 23);
	}
	else {
		//the found film is at position = exists
		setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		footerLine("$Update option: ", 30, 21, 76, 23);
		setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		std::string updateOption;
		std::getline(std::cin, updateOption);
		if (updateOption == "")
			warningBottom("Give valid option!", 30, 21, 76, 23);
		else if (updateOption == "title") {
			footerLine("$NEW Title: ", 30, 21, 76, 23);
			Ox = whereX();
			Oy = whereY();
			std::getline(std::cin, title);
			while (Validation::validateTitle(title) != 0) {
				setColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
				gotoxy(Ox, Oy);
				std::cout << "Not empty!";
				Sleep(700);
				setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
				footerLine("$NEW Title: ", 30, 21, 76, 23);
				std::getline(std::cin, title);
			}
			//update title
			ctrl.updateFilmFromRepo(exists, title);
		}
		else if (updateOption == "genre") {
			setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
			footerLine("$NEW Genre: ", 30, 21, 76, 23);
			Ox = whereX();
			Oy = whereY();
			std::getline(std::cin, genre);
			while (Validation::validateGenre(genre) != 0) {
				setColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
				gotoxy(Ox, Oy);
				std::cout << "Not empty!";
				Sleep(700);
				setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
				footerLine("$NEW Genre: ", 30, 21, 76, 23);
				std::getline(std::cin, genre);
			}
			//update genre
			ctrl.updateFilmFromRepo(exists, "", genre);
		}
		else if (updateOption == "year") {
			setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
			footerLine("$NEW Year: ", 30, 21, 76, 23);
			Ox = whereX();
			Oy = whereY();
			std::getline(std::cin, year);
			while (Validation::validateYear(year) == -1 || Validation::validateYear(year) == -2) {
				setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
				footerLine("$NEW Year: ", 30, 21, 76, 23);
				setColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
				gotoxy(Ox, Oy);
				if (Validation::validateYear(year) == -1)
					std::cout << "Between 1900 & 2025!";
				else if (Validation::validateYear(year) == -2)
					std::cout << "Number!";
				Sleep(1000);
				setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
				footerLine("$NEW Year: ", 30, 21, 76, 23);
				std::getline(std::cin, year);
			}
			//update year
			ctrl.updateFilmFromRepo(exists, "", "", Validation::validateYear(year));
		}
	}
}

void UI::menuAdminDelete()
{
	std::string title;
	std::string year;

	int Ox, Oy;


	footerLine("$Title: ", 30, 21, 76, 23);
	Ox = whereX();
	Oy = whereY();
	std::getline(std::cin, title);
	while (Validation::validateTitle(title) != 0) {
		setColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		gotoxy(Ox, Oy);
		std::cout << "Not empty!";
		Sleep(700);
		setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		footerLine("$Title: ", 30, 21, 76, 23);
		std::getline(std::cin, title);
	}

	setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
	footerLine("$Year: ", 30, 21, 76, 23);
	Ox = whereX();
	Oy = whereY();
	std::getline(std::cin, year);
	while (Validation::validateYear(year) == -1 || Validation::validateYear(year) == -2) {
		setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		footerLine("$Year: ", 30, 21, 76, 23);
		setColor(FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		gotoxy(Ox, Oy);
		if (Validation::validateYear(year) == -1)
			std::cout << "Between 1900 & 2025!";
		else if (Validation::validateYear(year) == -2)
			std::cout << "Number!";
		Sleep(1000);
		setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		footerLine("$Year: ", 30, 21, 76, 23);
		std::getline(std::cin, year);
	}

	if (ctrl.deleteFilmFromRepo(title, Validation::validateYear(year)) == -1)
		warningBottom(title + " doesn't exists!", 30, 21, 76, 23);
}

void UI::typoEffect(const std::string & text)
{
	/*
		Effect of auto typing
	*/

	for (const auto c : text) {
		std::cout << c << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
	std::cout << std::endl;
}

void UI::dialogUser(const std::string& text1, int x1, int y1, int y2, int lines, const std::string& text2, int colorSetFirst)
{
	/*
		AI dialog box	(x2 is calculated)
		Implicit one line is printed
		If two given, the first should be the longest
	*/
	clearArea(x1, y1, 100, y2);				//max Length of a string is considered - 100
	gotoxy(x1 - 1, y2 + 1);
	std::cout << "/";

	unsigned char verticalLines = 179;
	unsigned char horizontalLines = 196;
	unsigned char topRight = 191;
	unsigned char topLeft = 218;
	unsigned char bottomRight = 217;
	unsigned char bottomLeft = 192;
	
	int x2 = text1.length() + 20;

	//dialog box
	{
		int i;

		setMyCursor(CURSOR_OFF);

		gotoxy(x1, y1);			//left top corner
		std::cout << topLeft;
		for (i = x1 + 1; i < x2; i++)
			std::cout << horizontalLines;
		gotoxy(x2, y1); 		//right top corner
		std::cout << topRight;
		for (i = y1 + 1; i < y2; i++) {
			// Vertical lines
			gotoxy(x1, i);			//left vLine
			std::cout << verticalLines;
			gotoxy(x2, i);			//right vLine
			std::cout << verticalLines;
		}
		gotoxy(x1, y2);
		std::cout << bottomLeft; 	//left bottom corner
		for (i = x1 + 1; i < x2; i++)
			std::cout << horizontalLines;		//bottom line
		gotoxy(x2, y2);
		std::cout << bottomRight;			//right bottom corner

											//gotoxy(xBegin, yBegin);
		setMyCursor(CURSOR_ON);
	}
	

	int Ox = x1 + 1;
	int Oy = y1 + 1;
	gotoxy(Ox, Oy);
	if (colorSetFirst == 1) {
		setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);	//yellow
	}
	typoEffect(text1);
	setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);	
	

	if (lines == 2) {
		gotoxy(Ox, ++Oy);
		typoEffect(text2);
	}
}

void UI::user()
{
	clearArea(1, 1, 100, 30);
	system("color 8B");
	setMyCursor(CURSOR_OFF);
	setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);
	std::string iconChar =      "       __ \n"
				                "    .\"`  `;. \n"
								"   / .---'. \\ \n"
								"   \\| .  . |/ \n"
								"   (    >   ) \n"
								"    \\  --  / \n"
								"   __)----(__ \n"
								" /` <_\__/_>  `\\ \n"
								"/       :      \\ \n";
	gotoxy(1, 2);
	std::cout << iconChar;

	int Ox = whereX();
	int Oy = whereY() + 1;

	dialogUser("Hi, " + userName + "! I'm your virtual assistant!", 18, 1, 4, 2, "Let's create your Watchlist!");
	footerLine("Hello! ", 1, 12, 20, 14);		//Option BOX
	std::cin.get();
	setMyCursor(CURSOR_ON);

	//Ask for fileTYPE
	dialogUser("Select a file type for saving your watchlist.", 18, 1, 4, 2, "Choose: [html/csv]");
	footerLine("Option: ", 1, 12, 30, 14);

	std::string option;
	setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
	std::getline(std::cin, option);
	setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);

	if (option == "html" || option == "csv")
	{
		ctrl.selectFileType(this->userName, option);
	}
	else
		warningBottom("No such option!", 1, 12, 30, 14);
}

int UI::userSetup()
{
	/*
		Main Menu for user
		User can choose multiple options [watchlist/genre/exit]
		Output : Return code of option
	*/

	std::string option;
	dialogUser("You can view your watchlist / watch by genre / EXIT", 18, 1, 4, 2, "Choose: [watchlist/genre/exit]");
	footerLine("Option :  ", 1, 12, 30, 14);		//Option BOX
	
	setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
	std::getline(std::cin, option);
	setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);

	if (option == "watchlist")
		return 1;
	else if (option == "genre")
		return 2;
	else if (option == "exit")
		return 0;
	else {
		warningBottom("No such option!", 1, 12, 30, 14);
	}
}

void UI::menuGenre()
{
	/*
		Show all movies from DB to user
		User can choose what to add to watchlist or can play the movie trailer
	*/

	WatchList creatingWatchList;		//empty WatchList for new User
	std::string option;
	dialogUser("Choose a genre: crime, thriller, comedy, drama, sci-fi, action, fantasy...", 18, 1, 4);
	footerLine("Genre :  ", 1, 12, 30, 14);		//Option BOX
	setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
	std::getline(std::cin, option);
	setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);

	std::vector<Film> foundFilms = ctrl.getFilmsGenre(option);
	std::string infoFilm;

	//check if there are films for selected genre
	if (foundFilms.size() == 0) {
		dialogUser("There are no movies of '" + option + "' genre yet!", 18, 1, 4, 2, "You can select another.");
		footerLine("OK ", 1, 12, 30, 14);
		std::cin.get();
	}
	else {
		for (unsigned i = 0; i < foundFilms.size(); i++) {
			infoFilm = foundFilms[i].getTitle() + " | " + foundFilms[i].getGenre() + " | " + std::to_string(foundFilms[i].getYear()) + " | " + std::to_string(foundFilms[i].getLikes()) + "\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
			dialogUser(infoFilm, 18, 1, 4, 2, "Do you want to watch the trailer? [y/n]", 1);			//1 is set for yellow coloring for title
			setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);

			footerLine("Option :  ", 1, 12, 30, 14);		//Option BOX
			setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);		//yellow
			std::cin >> option;
			std::cin.ignore();
			setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);

			if (option == "y")
			{
				foundFilms[i].play();
			}

			//Add Film to WatchList
			dialogUser("Do you want to add the Film to your WatchList? [y/n]", 18, 1, 4);
			setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);

			footerLine("Option :  ", 1, 12, 30, 14);		//Option BOX
			setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);		//yellow
			std::cin >> option;
			std::cin.ignore();
			setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);

			if (option == "y") {
				//Verify if the user is new one
				if (this->newCustomer == false) {
					ctrl.addFilmToWatchlist(this->userName, foundFilms[i]);      		//add the film to the watchlist of existing user
				}
				else {
					creatingWatchList.add(foundFilms[i]);			//create new WatchList
				}
			}
			dialogUser("Do you want to continue? [y/n]", 18, 1, 4);
			setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);

			footerLine("Option :  ", 1, 12, 30, 14);		//Option BOX
			setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);		//yellow
			std::cin >> option;
			std::cin.ignore();
			setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);

			if (option == "n")
				break;
		}
	}
	if (newCustomer)
		this->newWatchList = creatingWatchList;				//the watchlist of newUser is updated
}

void UI::menuWatchList()
{
	/*
		Menu, where User can view his watchlist or delete and like the films
	*/

	std::string option;

	dialogUser(this->userName + ", you can view your watchList / delete the films you have seen.", 18, 1, 4, 2, "Choose: [view/delete]");
	footerLine("Option :  ", 1, 12, 30, 14);		//Option BOX
	setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
	std::getline(std::cin, option);
	setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);


	if (option == "view") {
		WatchList temporaryWatchlist;

		if (newCustomer) {
			temporaryWatchlist = this->newWatchList;			//if user is new modify the new watchlist
		}
		else {			
			temporaryWatchlist = ctrl.getRepo().getUsers()[this->posUser].watchList;				//get the user's watchlist
		}

		if (temporaryWatchlist.getFilms().size() != 0) {
			setMyCursor(CURSOR_OFF);
			box(29, 15, 78, 19 + temporaryWatchlist.getFilms().size());

			setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);
			int Ox = 31;
			int Oy = 16;
			gotoxy(Ox, Oy);
			std::cout << std::setw(20) << "Title" << std::setw(10) << "Genre" << std::setw(7) << "Year" << std::setw(8) << "Likes";
			gotoxy(Ox, ++Oy);
			std::cout << "----------------------------------------------";

			std::vector<Film> allFilms = temporaryWatchlist.getFilms();
			for (unsigned i = 0; i < allFilms.size(); i++) {
				gotoxy(Ox, ++Oy);
				std::cout << std::setw(20) << allFilms[i].getTitle() << std::setw(10) << allFilms[i].getGenre() << std::setw(7) << allFilms[i].getYear() << std::setw(8) << allFilms[i].getLikes();
			}

			ctrl.openFileInApp();
			std::cin.get();
			setMyCursor(CURSOR_ON);
			clearArea(29, 15, 78, 19 + temporaryWatchlist.getFilms().size());
		}
		else {
			//there are no films in watchlist
			dialogUser("Your WatchList is empty!", 18, 1, 4, 2, "Please add some films!");
			clearArea(1, 12, 30, 14);
			footerLine("OK ", 1, 12, 19, 14);		//Option BOX
			std::cin.get();
		}
		
	}
	else if (option == "delete") {
		std::string title;
		std::string year;

		dialogUser("Which film do you want to delete? ", 18, 1, 4);
		footerLine("Title :  ", 1, 12, 30, 14);		//Option BOX
		int Ox = whereX();
		int Oy = whereY();
		setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		std::getline(std::cin, title);

		//Validate the input title
		while (Validation::validateTitle(title) != 0) {
			setColor(FOREGROUND_RED | BACKGROUND_INTENSITY);
			gotoxy(Ox, Oy);
			std::cout << "Not empty!";
			Sleep(700);
			setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);
			footerLine("Title :  ", 1, 12, 30, 14);
			setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
			std::getline(std::cin, title);
		}
		setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);

		setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);
		footerLine("Year :  ", 1, 12, 30, 14);		//Option BOX
		Ox = whereX();
		Oy = whereY();
		setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
		std::getline(std::cin, year);
		setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);

		//Validate year input
		while (Validation::validateYear(year) == -1 || Validation::validateYear(year) == -2) {
			setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);
			footerLine("Year :  ", 1, 12, 30, 14);
			setColor(FOREGROUND_RED | BACKGROUND_INTENSITY);
			gotoxy(Ox, Oy);
			if (Validation::validateYear(year) == -1)
				std::cout << "Btw. 1900 & 2025!";
			else if (Validation::validateYear(year) == -2)
				std::cout << "Number!";
			Sleep(1000);
			setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);
			footerLine("Year :  ", 1, 12, 30, 14);
			setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);
			std::getline(std::cin, year);
		}
		setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);

		int filmExists;
		if (this->newCustomer == false) {
			filmExists = ctrl.deleteFilmFromWatchlist(this->userName, title, Validation::validateYear(year));
		}
		else {
			filmExists = this->newWatchList.deleteFilm(ctrl.getRepo().findByID(title, Validation::validateYear(year)));
		}
		
		//Check if the film exists
		if (filmExists == 0) {

			//Increase Likes for movie
			dialogUser("Did you like the film? [y/n]", 18, 1, 4);
			setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);

			footerLine("Option :  ", 1, 12, 30, 14);		//Option BOX
			setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY);		//yellow
			std::cin >> option;
			std::cin.ignore();
			setColor(FOREGROUND_BLUE | BACKGROUND_INTENSITY);

			if (option == "y")
				ctrl.incLikes(title, Validation::validateYear(year));
		}
		else if (filmExists == -1) {
			dialogUser("The film: " + title + " | " + year + " isn't in your WatchList!", 18, 1, 4);	
			std::cin.get();
		}
	}
	else {
		warningBottom("No such option!", 1, 12, 30, 14);
	}
}


void UI::run()
{
	int option = 0;
	landing();

	while (true) {
		int whois = authentification();			//returns 0 for EXIT, 1 - USER, 2 - ADMIN

		if (whois == 0) {		
			gotoxy(52, 17);
			std::cout << "Bye!";
			Sleep(2000);
			break;
		}
		else if (whois == 1) {
			user();
			
			//verify if the user is in DB
			this->posUser = ctrl.getRepo().findUser(this->userName);

			//Create newUser 
			User newUser;
			if (posUser == -1) {
				newUser.userName = this->userName;
				this->newCustomer = true;
			}
			else
				this->newCustomer = false;

			while (true) {
				option = userSetup();
				if (option == 0) {
					//Add newUser to DB
					if (newCustomer) {
						newUser.watchList = this->newWatchList;
						ctrl.addNewUserToRepo(newUser);

						//save the new-user's Watchlist
						ctrl.setListForFileRepo(newUser.watchList.getFilms());
						ctrl.saveFile();
					}
					break;
				}
				else if (option == 1)
					menuWatchList();
				else if (option == 2)
					menuGenre();
			}
		}
		else if (whois == 2) {
			while (true) {
				option = admin();
				if (option == 0)
					break;
				else if (option == 1) {
					menuAdminAdd();
				}
				else if (option == 2) {
					menuAdminUpdate();
				}
				else if (option == 3) {
					menuAdminDelete();
				}
				else if (option == 4) {
					showMore();
				}
			}
		}
	}

	gotoxy(10, 27);
}