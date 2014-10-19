#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"
// Relevant includes of classes being used
#include "FileEditFromFile.h"
#include "FileEditFromString.h"
#include "csv_64MDL_process.h"
#include "csv_64_var_mapping.h"
#include "ModFilesGetter.h"
#include "Exe_Execution.h"
#include "ModToFileMap.h"
#include "csv_64T_Process.h"

#include <iostream>


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




/*
* Constructor.
*/
Menu::Menu(const string &directory_path)
{
	dir_path = directory_path;
}

void Menu::MenuMain()
{
	/**  Pre processing. Taking care of files that are being used in the activity of neuron. */
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
		// The hoc execution using neuron
		Exe_Execution hoc_exe = Exe_Execution(NRN_PATH);
		hoc_exe.AddParams(hoc_file);
		hoc_exe.Exectue();


		// After the hoc executiong, this file is not needed anymore
		file_edit_ff.DeleteNewFile();
	}

	// TESTING
	//csv_64T_Process bla = csv_64T_Process();
	//bla.Process;

	// TODO: func - processing 64T.csv file for getting the number of departments and compartments for the next step (instead of the magic number '3')
	{
		// Processing the global and 64mdl files
		csv_64_var_mapping c1 = csv_64_var_mapping(GLB, 3); // TODO - need to get the number of compartments
		csv_64_var_mapping c2 = csv_64_var_mapping(MDL64, 3); // - " -
		c1.Process();
		map<string, vector<double>> ff = c1.GetMap();

		c2.Process();
		map<string, vector<double>> ff2 = c2.GetMap();
	}


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