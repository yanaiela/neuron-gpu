

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
	Menu(const string &directory_path = "d:/Users/Yanai/Desktop/Compiler_Project/Writing_To_Hoc/Writing_To_Hoc");
	void MenuMain();
};




#endif