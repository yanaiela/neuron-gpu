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
#include "csv_64MDL_process.h"
#include "csv_64_var_mapping.h"
#include "ModFilesGetter.h"
#include "Hoc_Process.h"
#include "Hoc_Exceution.h"
#include "ModToFileMap.h"
#include "csv_64T_Process.h"


#include <iostream>

/*
* Constructor.
*/
Menu::Menu(const string& hoc, const char *directory_path)
{
	dir_path = directory_path;
	hoc_file = hoc;
}

void Menu::MenuMain()
{

	// Processing the hoc file - the start of it.
	Hoc_Process hoc = Hoc_Process(hoc_file);
	hoc.Process();
	string example = hoc.GetNewHocFile();

	Hoc_Execution he = Hoc_Execution(example);
	he.Exectue();


	// TESTING
	//csv_64T_Process bla = csv_64T_Process();
	//bla.Process();

	// func - processing 64T.csv file for getting the number of departments and compartments
	{
		// Processing the global file
		csv_64_var_mapping c1 = csv_64_var_mapping(GLB, 3); // TODO - need to get the number of compartments
		csv_64_var_mapping c2 = csv_64_var_mapping(MDL64, 3);
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