/**
	This class is just for getting an exe name (with it's location if needed), and executing it.
	It can get also parameters for executing it with it.

	This class uses the system built in function to execute the exe, so it could be dangerous,
	so the user should know what he's doing.
*/

#ifndef HOC_EXECUTION_H
#define HOC_EXECUTION_H

#include <iostream>
#include <string>


using namespace std;

class Exe_Execution
{
private:

	string exe;

public:

	Exe_Execution(const string &exe_path);
	Exe_Execution(const string &exe_path, const string &parameters);

	void Exectue();
};

#endif
