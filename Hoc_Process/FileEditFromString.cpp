#include "FileEditFromString.h"



void FileEditFromString::InsertContent()
{
	string line = cur_line;

	int i = line.find(search_token);
	line.replace(i, search_token.length(), insertion);

	dst << line;
}