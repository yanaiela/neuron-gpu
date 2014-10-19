#include "FileEditFromString.h"


void FileEditFromString::InsertContent()
{
	string line = cur_line;

	// Getting the location of the token.
	int index = line.find(search_token);

	// Replacing the token with the insertion string.
	line.replace(index, search_token.length(), insertion);

	dst << line;
}

