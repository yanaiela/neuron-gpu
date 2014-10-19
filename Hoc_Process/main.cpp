#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"
#include "Defs.h"
#include "FileEditFromFile.h"
#include "FileEditFromString.h"




int main()
{
	/*
	// Searching for a specific token to replace it with the full path of the output files
	FileEditFromString fs = FileEditFromString(DEFULT_DIR_PATH, DEFAULT_HOC_COMMANDS_FILE, TXT, TKN_PATH, 6);
	fs.Edit();

	string st = fs.GetEditedFile();

	// Searching for a specific token to add to this place in the file commands from another file
	FileEditFromFile fe = FileEditFromFile(st, DEFAULT_HOC_FILE, HOC, TKN_HOC_INSRT, 1, QUIT);
	fe.Edit();

	*/
	Menu menu = Menu(DEFULT_DIR_PATH);
	menu.MenuMain();
	
}


/************************************************************************
* Class name:
* The Input:
* The class operation:
*************************************************************************/


