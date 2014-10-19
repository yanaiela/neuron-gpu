#ifndef FILEDITFROMFILE_H
#define FILEDITFROMFILE_H

#include "Defs.h"
#include "FileEdit.h"

class FileEditFromFile : public FileEdit
{

private:

	string closing_line;

	/**
	* Opening a stream of the file that will be inserted, then just copying it as is to the 
	* place in the file that is being edited.
	*/
	void InsertContent();
	
	// Implementation
	virtual bool LineFit(const string& line)
	{
		return (line.compare(search_token) == EQUALS);
	}


public:

	// Just passing all variables to the father class - FileEdit
	FileEditFromFile(const string& input_file,
		const string& file,
		const string& type,
		const string& token,
		int num_tokens,
		const string& closing_string = EMPTY)
		: FileEdit(input_file, file, type, token, num_tokens, closing_string) {}




};



#endif

