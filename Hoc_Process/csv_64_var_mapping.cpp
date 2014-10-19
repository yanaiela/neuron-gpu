#include "csv_64_var_mapping.h"


// Constructor.
csv_64_var_mapping::csv_64_var_mapping(const string &src_file, int dep_num)
{
	file_name = src_file;
	num = dep_num;
	// Initiallizing the counter to -1, so that the insertion to the stack will
	// begin from 0.
	counter = -1;
}


// The Process method that is open for the public. It is composed
// of the part that is finding all the variables and making them a vector.
// This is not very efficient, but FCK it' it runs fast enought for now...
void csv_64_var_mapping::Process()
{
	FindVars();
	InsertVals();
	
}

// Going over all the file, inserting the vars to the params (map)
void csv_64_var_mapping::FindVars()
{
	// Opening the glb file
	src.open(file_name);
	if (!src.is_open())
	{
		throw runtime_error(ERR_FO + string(file_name));
	}

	string line;

	while (getline(src, line))
	{
		// If finding a comment, that means that we passed a compartment
		if (line.front() == COMMENT_C)
			continue;

		else if (line.compare(END) == EQUALS)
			continue;

		else
		{
			string s = Split(line).first;

			// Checking if the key exists
			if (params.count(s) == 0) {

				// Creating the [double] vector for each param. initiallizing them with NaN.
				vector<double> arr(num, numeric_limits<double>::signaling_NaN());

				params.insert({ s, arr });
			}
		}
	}
	src.close();
}


// Going over the file for the second time, inserting all the values to the variables.
void csv_64_var_mapping::InsertVals()
{
	
	// Opening the glb file
	src.open(file_name);
	if (!src.is_open())
	{
		throw runtime_error(ERR_FO + string(file_name));
	}

	string line;

	while (getline(src, line))
	{
		// If finding a comment, that means that we passed a compartment
		if (line.substr(0, 1).compare(COMMENT_S) == EQUALS)
		{
			counter++;
			continue;
		}

		else if (line.compare(END) == EQUALS)
			continue;

		// In every correct line that supplies values for it's arguments,
		// extracting the vector and inserting it the value in the counter position.
		else
		{
			pair<string, double> p = Split(line);
			
			vector<double> &v = params.at(p.first);
			v[counter] = p.second;

		}
	}
	src.close();
}

// Returning the mapping.
map<string, vector<double>> csv_64_var_mapping::GetMap()
{
	return params;
}



/*
* Extracting string and number from the lines of the file.
* Returning a pair of the string and the double value.
*/
pair<string, double> Split(const string& input, const string& separators, bool remove_empty)
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

	return pair<string, double>(v.front(), atof(v.back().c_str()));
}

