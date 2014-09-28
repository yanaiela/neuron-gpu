#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"

#define DEFULT_DIR_PATH "d:\\Users\\Yanai\\Desktop\\Compiler_Project\\Neuron_GPU\\Hoc_Process"
#define DEFAULT_HOC_FILE "example.hoc" // Relative path.


int main()
{
	Menu menu = Menu(DEFAULT_HOC_FILE, DEFULT_DIR_PATH);
	menu.MenuMain();
}


/************************************************************************
* Class name:
* The Input:
* The class operation:
*************************************************************************/


