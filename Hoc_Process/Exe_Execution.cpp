#define _CRT_SECURE_NO_WARNINGS

#include "Exe_Execution.h"
#include "Defs.h"


// Constructor.
Exe_Execution::Exe_Execution(const string &exe_path)
{
	exe = exe_path;
}


void Exe_Execution::Exectue()
{
	// Executing the exe with parameters or not.
	system(exe.c_str());

}

void Exe_Execution::AddParams(const string &parameters)
{
	string param = parameters;

	// adding the params to the current exe path
	exe = exe + " " + param.c_str();

}