/**
	@name csv_64_var_mapping

	The Input: the number of departments
	The class operation: The class main activity is to  go over the Global and the MDL file and to map all
	of the variables of the file to a vector of their values arranged by their department arrangment.
	Overall the algo runs over the file twice, which is not very efficient but it is sufficient for now....

	 @author Yanai Elazar
	 @last modified date: 19.10.14
*/


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
	ifstream src;
	string file_name;
	int num;
	int counter;


	// Methods
	void FindVars();
	void InsertVals();

public:

	csv_64_var_mapping(const string &src_file, int dep_num);

	void Process();
	map<string, vector<double>> GetMap();
};

pair<string, double> Split(const string& input, const string& separators = " = ", bool remove_empty = true);

