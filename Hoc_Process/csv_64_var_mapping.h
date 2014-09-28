#include "Defs.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>


#define END "END_OF_SECTION"

using namespace std;


class csv_64_var_mapping
{
private:

	// Members
	map<string, vector<double>> params;
	ifstream src_glb;
	string file_name;
	int num;
	int counter;


	// Methods
	//pair<string, double> ExtrStrNNum(const string &line);
	void FindVars();
	void InsertVals();

public:

	csv_64_var_mapping(const string &src_file, int dep_num);
	//~csv_64_GLOBAL_process();

	void Process();
	map<string, vector<double>> GetMap();
};

pair<string, double> Split(const string& input, const string& separators = " = ", bool remove_empty = true);

