/**
	This class was built from the getNsegsMat function in matlab.
	I still have only a small clue of whats going here, and there is some part that needs to be completed 
	(I can do that only with some more complicated examples - hoc files).
	There is a little bug that comes from the VS - the numbers that are being read from the 64T file can't be
	scanned precisely like they appear in the original file. It causes a small difference.

	@author Yanai Elazar
	@last modified date: 
*/

#ifndef CSV_64T_PROCESS_H
#define CSV_64T_PROCESS_H

#include "Defs.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#define APOSTROPHE '`'
#define BREAKS '|'
#define DASH '-'

using namespace std;

class csv_64T_Process
{
private:

	ifstream src;

	vector<vector<float> > comp_params;

	int GetCompIndex(vector<string> types, string compt_name);

public:
	csv_64T_Process();

	void Process();

	vector<float> GetCompParams();



};


#endif

