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

	/**
		Constructor.
		@param directory_path - The current directory where the program runs. It is used for finding the
			mod files
	*/
	Menu(const string &directory_path);
	void MenuMain();
};


#endif

