/**
	Menu class. This is the actually the main the runs.
*/

#ifndef MENU_H
#define MENU_H

#include <string>

using namespace std;

class Menu
{

private:
	string dir_path;

public:
	Menu(const string &directory_path);
	void MenuMain();
};


#endif

