#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"

/**/
#include <vld.h> // FOR LEAKS

#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG
//_crtBreakAlloc = 144; // should be inside the file. prefare at the start, when it finds the number of allocation, it will break there
/**/

// Relevant includes of classes being used
#include "FileEditFromFile.h"
#include "FileEditFromString.h"
#include "csv_64MDL_process.h"
#include "csv_64_var_mapping.h"
#include "ModFilesGetter.h"
#include "Hoc_Exceution.h"
#include "ModToFileMap.h"
#include "csv_64T_Process.h"

#include <iostream>


/*
* Constructor.
*/
Menu::Menu(const string &directory_path)
{
	dir_path = directory_path;
}

void Menu::MenuMain()
{
	// Searching for a specific token to replace it with the full path of the output files
	FileEditFromString file_edit_fs = FileEditFromString(DEFULT_DIR_PATH, DEFAULT_HOC_COMMANDS_FILE, TXT, TKN_PATH, 6);
	file_edit_fs.Edit();

	string str = file_edit_fs.GetEditedFile();

	// Searching for a specific token to add to this place in the file commands from another file
	FileEditFromFile file_edit_ff = FileEditFromFile(str, DEFAULT_HOC_FILE, HOC, TKN_HOC_INSRT, 1, QUIT);
	file_edit_ff.Edit();

	file_edit_fs.DeleteNewFile();


	string hoc_file = file_edit_ff.GetEditedFile();
	Hoc_Execution hoc_exe = Hoc_Execution(hoc_file);
	hoc_exe.Exectue();


	// TESTING
	//csv_64T_Process bla = csv_64T_Process();
	//bla.Process;

	// func - processing 64T.csv file for getting the number of departments and compartments
	{
		// Processing the global file
		csv_64_var_mapping c1 = csv_64_var_mapping(GLB, 3); // TODO - need to get the number of compartments
		csv_64_var_mapping c2 = csv_64_var_mapping(MDL64, 3); // - " -
		c1.Process();
		map<string, vector<double>> ff = c1.GetMap();

		c2.Process();
		map<string, vector<double>> ff2 = c2.GetMap();
	}

	//cout << "hi";

	//Finding the files in the dir
	vector<string> v;
	ModFilesGetter fg = ModFilesGetter(dir_path.c_str());
	fg.FindFiles();
	v = fg.GetFilesFromDir();

	ModToFileMap mtf = ModToFileMap(v);
	mtf.Process();

	vector<pair<string, string>> vv = mtf.GetMap();

	


	// Processing the MDL file
	csv64MDL_process s = csv64MDL_process();
	try {

	s.Process();
	vector < pair<string, set<string>>> p = s.Get_g_info();
	}
	catch (runtime_error re)
	{
	cerr << re.what();

	}

	

	_CrtDumpMemoryLeaks();
}