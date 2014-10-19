#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"

#include "FileEditFromFile.h"
#include "FileEditFromString.h"

#define DEFULT_DIR_PATH "d:/Users/Yanai/Desktop/Compiler_Project/Neuron_GPU/Hoc_Process"
#define DEFAULT_HOC_FILE "example.hoc" // Relative path.


int main()
{
	// Searching for a specific token to replace it with the full path of the output files
	FileEditFromString fs = FileEditFromString(DEFULT_DIR_PATH, "hoc_command_insert.txt", "txt", "Insert_Path", 6); 
	fs.Edit();

	string s = fs.GetEditedFile();

	// Searching for a specific token to add to this place in the file commands from another file
	FileEditFromFile fe = FileEditFromFile(s, "example.hoc", "hoc", "//ADD STUFF HERE", 1, QUIT);
	fe.Edit();

	fs.DeleteFile();
	/*Menu menu = Menu(DEFAULT_HOC_FILE, DEFULT_DIR_PATH);
	menu.MenuMain();*/
}


/************************************************************************
* Class name:
* The Input:
* The class operation:
*************************************************************************/


