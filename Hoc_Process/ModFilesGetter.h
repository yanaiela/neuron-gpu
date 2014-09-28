#ifndef MODFILESGETTER_H
#define MODFILESGETTER_H

#include "Defs.h"	

#include <Windows.h>

#include <string>
#include <vector>

#include <sys/types.h>
#include <dirent.h>

#define CUR_DIR "./"

using namespace std;


class ModFilesGetter {

private:
	
	DIR *dp;
	struct dirent *ep;
	vector<string> files;

public:
	ModFilesGetter(const char *path = CUR_DIR);
	~ModFilesGetter();

	void FindFiles();
	vector<string> GetFilesFromDir();
};

bool ends_with(string const &a, string const &b);

#endif
