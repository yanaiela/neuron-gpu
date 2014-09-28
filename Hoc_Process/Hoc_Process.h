#ifndef HOC_PROCESS_H
#define HOC_PROCESS_H

#include "Defs.h"


#include <fstream>
#include <ostream>

#include <iostream>
#include <string>

using namespace std;

#define SUFFIX_LENGTH 4
#define ADDSUFFIX ".copy"
#define EQUALS 0
#define INSERT_DATA "//ADD STUFF HERE"
#define INSERT_FILE "hoc_command_insert.txt"


#define QUIT "quit()"

class Hoc_Process
{
private:

	// Members
	string orig_hoc_path;
	string new_hoc_path;

	// Methods
	void NameChange();

public:
	Hoc_Process(const string& path);

	void Process();
	string GetNewHocFile();
};

#endif
