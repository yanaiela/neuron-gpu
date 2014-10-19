#ifndef FILEEDITFROMSTRING
#define FILEEDITFROMSTRING

#include "FileEdit.h"
#include <vector>
#include <boost\algorithm\string.hpp>


class FileEditFromString : public FileEdit
{
private:

	virtual bool LineFit(const string& line)
	{
		return boost::algorithm::contains(line, search_token);
	}

	// The actual implemented inserting method.
	void InsertContent();

public:

	// Just passing all variables to the father class - FileEdit
	FileEditFromString(const string& input_string,
						const string& file,
						const string& type, 
						const string& token, 
						int num_tokens)
						: FileEdit(input_string, file, type, token, num_tokens) {}

};


#endif