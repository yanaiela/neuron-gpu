#ifndef MODTOFILEMAP
#define MODTOFILEMAP

#include "Defs.h"

#include <string>
#include <map>
#include <vector>

#define SEARCH "NEURON"
#define SEARCH1 "NEURON{"

using namespace std;


class ModToFileMap {

private:

	vector<string> vec;
	vector<pair<string, string>> mod_files_map;

	// Methods
	string FindSuffix(string cur_mod);

public:
	ModToFileMap(const vector<string> &files_vec);
	void Process();
	
	vector<pair<string, string>> GetMap();
};

#endif
