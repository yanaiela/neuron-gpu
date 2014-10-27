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

#include "csv_64PP_Process.h"

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
	

	/**  Preprocessing. Taking care of files that are being used in the activity of neuron. */
	
	// Searching for a specific token to replace it with the full path of the output files
	FileEditFromString file_edit_fs = FileEditFromString(DEFULT_DIR_PATH, DEFAULT_HOC_COMMANDS_FILE, TXT, TKN_PATH, 6);
	file_edit_fs.Edit();

	string hoc_edit = file_edit_fs.GetEditedFile();

	// Searching for a specific token to add to this place in the file commands from another file
	FileEditFromFile file_edit_ff = FileEditFromFile(hoc_edit, DEFAULT_HOC_FILE, HOC, TKN_HOC_INSRT, 1, QUIT);
	file_edit_ff.Edit();

	file_edit_fs.DeleteNewFile();


	string hoc_file = file_edit_ff.GetEditedFile();
	// The hoc execution using neuron
	Exe_Execution hoc_exe = Exe_Execution(NRN_PATH, hoc_file);
	hoc_exe.Exectue();


	// After the hoc execution, this file is not needed anymore
	file_edit_ff.DeleteNewFile();
	//////////////////////////

	csv_64T_Process t64 = csv_64T_Process();
	t64.Process();
	vector<float> vec = t64.GetCompParams();


	//int n_seg_mat[3] = { 2, 29, 29 }; // TODO - this is temporary, until getting it from the T process.

	//int comp_segs_ind_arr[3][2] = { 0 };
	//int seg_ind = 1;

	//for (int i = 0; i < 3; i++)
	//{
	//	seg_ind += 1;
	//	comp_segs_ind_arr[i][0] = seg_ind;
	//	seg_ind = seg_ind + n_seg_mat[i] - 1;
	//	comp_segs_ind_arr[i][1] = seg_ind;
	//	seg_ind += 1;
	//}

	//csv_64PP_Process csv64 = csv_64PP_Process(n_seg_mat, comp_segs_ind_arr);
	//csv64.Process();
	// TESTING UNTIL HERE

	
	// Processing the global and 64mdl files
	csv_64_var_mapping glb64 = csv_64_var_mapping(GLB, vec.size());
	csv_64_var_mapping mdl64 = csv_64_var_mapping(MDL64, vec.size());
	glb64.Process();
	map<string, vector<double>> glb_params = glb64.GetMap();

	mdl64.Process();
	map<string, vector<double>> mdl_params = mdl64.GetMap();
	//////////////////////////


	//Finding the files in the dir
	ModFilesGetter files_getter = ModFilesGetter(dir_path.c_str());
	files_getter.FindFiles();
	vector<string> files_vec = files_getter.GetFilesFromDir();

	// Mod files.
	
	ModToFileMap mtf = ModToFileMap(files_vec);
	mtf.Process();

	vector<pair<string, string>> mod2files = mtf.GetMap();
	////////////////////

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

