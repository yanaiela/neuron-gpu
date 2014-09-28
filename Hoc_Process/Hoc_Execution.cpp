#define _CRT_SECURE_NO_WARNINGS

#include "Hoc_Exceution.h"


// Constructor.
Hoc_Execution::Hoc_Execution(const string &hoc_path, const string &nrn_path)
{
	hoc_file = hoc_path;
	nrn = nrn_path;
}


// TODO possible: make a method that parse the NRN_PATH take the input
// and add the %s to the end of it (for the sprintf function will work).

void Hoc_Execution::Exectue()
{
	// Converting string to a char array with the 
	char path_and_params[MAX_PATH_LENGHT] = { 0 };
	const char *s = hoc_file.c_str();

	sprintf(path_and_params, NRN_PATH, s);

	// Executing the edited hoc file with neuron (nrniv.exe)
	system(path_and_params);
	//delete(s);
	//system("C:\\nrn73w64\\bin64\\nrniv.exe example.copy.hoc");
}

