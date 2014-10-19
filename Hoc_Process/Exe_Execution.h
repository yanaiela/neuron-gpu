#ifndef HOC_EXECUTION_H
#define HOC_EXECUTION_H

#include <iostream>
#include <string>


using namespace std;



class Exe_Execution
{
private:

	// Memebers
	string exe;

	

public:

	Exe_Execution(const string &exe_path);
	void AddParams(const string &params);
	void Exectue();

};

#endif
