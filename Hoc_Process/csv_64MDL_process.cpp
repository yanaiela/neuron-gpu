#include "csv_64MDL_process.h"




/*
* The process function takes much too long 
* it's probably a matter of the regex or the function
* that use it
*/

// Constructor
csv64MDL_process::csv64MDL_process()
{
	count = -1; // Assuming the count in the vector is starting from 0.

	mod = MOD; // every module regex
}


vector<pair<string, set<string>>> csv64MDL_process::Get_g_info()
{
	return g_info;
}

set<string> csv64MDL_process::Get_overall_mod()
{
	return overall_mod;
}

// Processing the info from the 64MDL file
void csv64MDL_process::Process()
{
	clock_t begin = clock(); // TODO DELETE

	src.open(MDL64);

	if (!src.is_open())
	{
		throw runtime_error(ERR_FO + string(MDL64));
	}

	string line;
	while (getline(src, line))
	{
		string::iterator begin = line.begin();
		string::iterator end = line.end();

		// If finding a dep def (comment).
		if (line.front() == COMMENT_C)
		{
			set<string> s;

			pair<string, set<string>> p(line.erase(0, 1), s); // Deleting the '#' char

			g_info.push_back(p);
			count++;
		}
		// If finding an ion suffix
		else if (line.find(ION) != string::npos)
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

	{ // TODO DELETE
		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		cout << elapsed_secs;
	}

	// Closing the stream
	src.close();
}




