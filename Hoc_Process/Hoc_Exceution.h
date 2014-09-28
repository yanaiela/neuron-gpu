#ifndef HOC_EXECUTION_H
#define HOC_EXECUTION_H

#include <iostream>
#include <string>


#define NRN_PATH "C:\\nrn73w64\\bin64\\nrniv.exe %s" // TODO maby to get the path in the constructor.
#define MAX_PATH_LENGHT 1000

using namespace std;



class Hoc_Execution
{
private:

	// Memebers
	string hoc_file;
	string nrn;

public:

	Hoc_Execution(const string &hoc_path, const string &nrn_path = NRN_PATH);

	void Exectue();

};

#endif
