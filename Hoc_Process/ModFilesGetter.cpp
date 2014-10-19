#include "ModFilesGetter.h"

// The suffix that is being looked for.
// In this case, it's the definition of the file.


/************************************************************************
* Class name: ModFilesGetter
* The Input: None
* The class operation: Requires the 'dirent.h' header file.. from :
* 'http://www.softagalleria.net/download/dirent/'
* Operating relatively to the current folder.
* The FindFiles method finds all the files in the current dir (and not folders),
* although this can be changes easily.
*************************************************************************/


/*
* Constructor. opening the dir, and checking it's valid and that
* it was opened correctly
*/
ModFilesGetter::ModFilesGetter(const char *path)
{
	dp = opendir(path); // For current dir.

	if (dp == NULL)
		throw runtime_error(ERR_DIR);
}

/*
* Destructor.
*/
ModFilesGetter::~ModFilesGetter()
{
	delete(ep);
}

void ModFilesGetter::FindFiles()
{
	while (ep = readdir(dp))
	{
		// If it's another lib
		if (ep->d_name[0] == '.')
			continue;

		if (ends_with(ep->d_name, SUFFIX_MOD))
		{
			files.push_back(ep->d_name);
		}
	}
	(void)closedir(dp);
}

// Returning the vector with all the relevant files
vector<string> ModFilesGetter::GetFilesFromDir()
{
	return files;
}


/*---------------
// Other Funcs...
---------------*/

/*
* The function that does that suffix check
*/
bool ends_with(string const &a, string const &b) {
	auto len = b.length();
	auto pos = a.length() - len;
	if (pos < 0)
		return false;
	auto pos_a = &a[pos];
	auto pos_b = &b[0];
	while (*pos_a)
	if (*pos_a++ != *pos_b++)
		return false;
	return true;
}
