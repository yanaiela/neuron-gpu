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
	vector < pair<string, set<string>>> g_info;
	set <string> overall_mod;
	ifstream src;
	int count;

	set<string> *exp;

	regex mod;

public:
	csv64MDL_process();
	//~csv64MDL_process();

	void Process();

	vector < pair<string, set<string>>> Get_g_info();
	set <string> Get_overall_mod();
};


// Maby one day
/*
#include <regex>

// Regexes def.
dep = ("#.+"); // comment line with the department def.
//ion = (".+(_ion).+"); // ion suffix, which is not a module
ion = (".+(_ion)"); // ion suffix, which is not a module
mod = (".*_(\\w+) *=.*"); // every module regex


// Processing the info from the 64MDL file
/*void csv64MDL_process::process()
{
clock_t begin = clock(); // TODO DELETE

src.open(MDL64);

if (!src.is_open())
{
throw string("Couldn't open the 64MDL.csv file!");
}

string line;
while (getline(src, line))
{
string::iterator begin = line.begin();
string::iterator end = line.end();

// If finding a dep def.
if (regex_search(begin, end, dep))
{
set<string> s;

pair<string, set<string>> p(line.erase(0, 1), s); // Deleting the '#' char

g_info.push_back(p);
//vec.at(count).second.insert("hi");
count++;
}
// If finding an ion suffix
else if (regex_search(begin, end, ion))
{
continue;
}
// Else, assuming that I found a module
else
{
smatch match;
const string s = line;
regex_search(s.begin(), s.end(), match, mod);
g_info.at(count).second.insert(match[1]);

// Inserting to the overall set
overall_mod.insert(match[1]);
}
}

// TODO DELETE
clock_t end = clock();
double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
cout << elapsed_secs; // DELETE

// Closing the stream
src.close();
}*/

