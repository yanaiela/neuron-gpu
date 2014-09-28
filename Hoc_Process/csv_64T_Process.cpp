#include "csv_64T_Process.h"
#include <boost/range/algorithm/count.hpp>
#include <boost/algorithm/string.hpp>

csv_64T_Process::csv_64T_Process()
{

}

void csv_64T_Process::Process()
{
	src.open(T64);

	if (!src.is_open())
	{
		throw runtime_error(ERR_FO + string(T64));
	}

	string line;

	// Skipping the first lines
	for (int i = 0; i < 3; i++)
	{
		getline(src, line);
	}

	bool readTopo = true;

	vector<int> apos; // apostrophe
	vector<string> type;
	vector<int> breaks;
	vector<int> dashes;

	while (line.size() > 0 && readTopo)
	{
		int aposInd = line.find(APOSTROPHE) + ONE;
		int breaksInd[2];
		breaksInd[FIRST] = line.find(BREAKS) + ONE; // first occurrence
		breaksInd[SECOND] = line.rfind(BREAKS) + ONE; // second occurrence (from the end)
		int dash = boost::count(line, DASH) - 1; // -1 for the end of the line (doesn't count)
		
		if (NOT_FOUND != breaksInd[FIRST]) // if found any |
		{
			if (NOT_FOUND == aposInd)
			{
				apos.push_back(ZERO);
				type.push_back(boost::trim_copy(line.substr(breaksInd[SECOND] + 1))); // Pushing to the end of the vector the type.
				breaks.push_back(breaksInd[SECOND]);
				dashes.push_back(dash);
			}

			else
			{
				apos.push_back(aposInd);
				type.push_back(boost::trim_copy(line.substr(breaksInd[FIRST] + 1)));
				breaks.push_back(breaksInd[FIRST]);
				dashes.push_back(dash);
			}

		}
		else
		{
			readTopo = false;
		}
		getline(src, line);

	}

	vector<int> origApos = apos;
	vector<int> origDashes = dashes;
	dashes.clear();

	//cout << dashes.size();

	vector<int> q; // check if int
	q.push_back(1);

}