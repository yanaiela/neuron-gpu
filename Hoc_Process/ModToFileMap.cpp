#include "ModToFileMap.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <boost/algorithm/string/trim_all.hpp>

using namespace boost::algorithm;

/************************************************************************
* Class name: ModToFileMap
* The Input: a const reference to the vector with all the files (in this
* case, mod files) that are being inspected.
* The class operation: entering every file from the vector (assuming they
* are in the initial library, looking for a specific keyword, then pairing the
* suffix that was found to the mod file name.
* NOTICE: Assuming that the definition of the suffix isn't inside a comment block.
*************************************************************************/

string Split(const string& input, const string& separators, bool remove_empty = true);


ModToFileMap::ModToFileMap(const vector<string> &files_vec)
{
	vec = files_vec;
}


/*
* Inspecting all the mod files from the vector. Not checking the branching file,
* every other file, sending him to the FindSuffix method to find it's suffix.
*/
void ModToFileMap::Process()
{
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		// Ignoring from the branching file.
		if (vec[i].compare(BRANCHING) == EQUALS)
		{
			continue;
		}
		try {
			string s = FindSuffix(vec[i]);
			
			// If found a match (correct suffix name in the file)
			pair<string, string> p = { s, vec[i] };
			mod_files_map.push_back(p);
			
		}
		catch (runtime_error re)
		{
			cout << ERR_FILE << vec[i] << endl;
			cout << re.what() << endl; // Printing the error.
		}
	}
}


/*
* Opens a mod file, read it, until getting to the wanted row
* extracting the suffix name and returning it.
* Assuming that: the suffix decleration won't be inside of a comment,
* the place it is in will be like SEARCH1 / SEARCH2,
* there is actually a correct suffix.
*
* Thworing a runtime exception if not finding the file
*/
string ModToFileMap::FindSuffix(string cur_mod)
{
	// Opening the stream
	ifstream mod(cur_mod);
	if (!mod.is_open())
	{
		throw runtime_error(ERR_FO + cur_mod);
	}

	string line;
	bool flag = false; //flag for finding the keyword 
	// Finding the line in the file with the neuron header.
	while (getline(mod, line))
	{
		// If finding any line with the NEURON key work in it.
		if (line.find(SEARCH) != string::npos)
		{
			// triming all spaces, (including inner spaces, - filling with empty char)
			if ((trim_fill_copy(line, EMPTY).find(SEARCH1) == EQUALS))
			{
				flag = true;
				break;
			}
		}
	}
	// If the Neuron line was found, looking now for the SUFFIX
	if (flag)
	{
		while (getline(mod, line))
		{
			trim_all(line);
			if (line.find(Y_SUFFIX) == EQUALS)
			{
				return Split(line, Y_SPACE); // Assuming there is a space between the SUFFIX and it's name
			}
		}
		
		// If the suffix wasn't found, throwing a runtime error.
		throw runtime_error(ERR_MIS + string(Y_SUFFIX));
	}
	else // If the Neuron line wasn't found
	{
		throw runtime_error(ERR_MIS + string(SEARCH));
	}
}

// Return a vector of the mapping.
vector<pair<string, string>> ModToFileMap::GetMap()
{
	return mod_files_map;
}


string Split(const string& input, const string& separators, bool remove_empty)
{
	vector<string> v;
	ostringstream word;
	for (size_t n = 0; n < input.size(); ++n)
	{
		if (string::npos == separators.find(input[n]))
			word << input[n];
		else
		{
			if (!word.str().empty() || !remove_empty)
				v.push_back(word.str());
			word.str("");
		}
	}
	if (!word.str().empty() || !remove_empty)
		v.push_back(word.str());

	return string(v.back());
}