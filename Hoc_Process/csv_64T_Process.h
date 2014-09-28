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


public:
	csv_64T_Process();

	void Process();



};


#endif

