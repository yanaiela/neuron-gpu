#include "Exe_Execution.h"

// Constructor.
Exe_Execution::Exe_Execution(const string &exe_path)
{
	exe = exe_path;
}

// Constructor with parameters.
Exe_Execution::Exe_Execution(const string &exe_path, const string &parameters)
{
	string param = parameters;

	// adding the params to the current exe path
	exe = exe_path + " " + param.c_str();

}

// Execution method.
void Exe_Execution::Exectue()
{
	// Executing the exe (with parameters or not).
	system(exe.c_str());

}

