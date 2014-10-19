#ifndef MENU_H
#define MENU_H

#include <string>

using namespace std;


class Menu
{

private:
	string dir_path;
	string hoc_file;

public:
	Menu(const string &directory_path);
	void MenuMain();
};




#endif

