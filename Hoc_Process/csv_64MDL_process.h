/**
	Class name: csv_64MDL_process
	The Input: None
	The class operation: goes over the 64mdl file and looks for every model in it.
	it make a vector that contains all the departments in the moduel, then inside that,
	match the name of the module to a set of the module inside it.
	The function is still a bit slow, probably because of the 'mod' regex that is
	being used in the process method.
	Exception: if the class doesn't find the corresponding file at the Process method,
	a runtime error will be thrown

	@author Yanai Elazar
	@last modified date: 19.10.14
*/

#include "Defs.h"

#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <iostream>

#include <regex>

#define ION "_ion"
#define MOD ".*_(\\w+) *=.*"

using namespace std;

class csv64MDL_process
{
private:
	vector < pair<string, set<string> > > g_info;
	set <string> overall_mod;
	ifstream src;
	int count;

	set<string> *exp;

	regex mod;

public:
	csv64MDL_process();

	void Process();

	vector < pair<string, set<string> > > Get_g_info();
	set <string> Get_overall_mod();
};




