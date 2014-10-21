/**
	@name FileEdit

	A virtual class. Intended to suspport a simple and easy use and override for what ever changes that one would like
	to make to any writable file.
	The constructor saves all the variables he's being given to,
	changing the name of the original file, adding it a 'copy' string before it's suffix,
	and then opening 2 streams: the original file - for reading, and the new file that it's name was changed
	for writing.
	Note - the constructor can throw a runtime exception
	The actual editing is being done with a token that is being searched for, that was given in the constructor.
	The Edit function uses a search method that search for the token, and then calling the virtual InsertContent method
	for inserting the content in whatever way.
	If the token wasn't found - SearchToken throws a runtime error
	At last, when all the expected token were found, the rest of the original file is being copied to the new one,
	if there was a closing line in the constructor, it's being inserted
	and then closing the stream using CloseStreams.

	There is an extra method - DeleteFile - for deleting the new file that was created for keeping the folder simple.

	@author Yanai Elazar
	@last modified date: 19.10.14
*/



#ifndef FILEEDIT_H
#define FILEEDIT_H

#include <fstream>
#include <boost/algorithm/string/trim.hpp>
#include <string>
#include "Defs.h"


using namespace std;

class FileEdit
{

private:

	// Variable
	int num_of_tokens;

	// Methods
	/**
	* Taking the original file name (from the constructor), and adding it '.copy' just before the suffix
	*/
	void NameChange();

	/**
	* Looking for the token (that was inserted in the constructor).
	* Throw runtime error - if the token wasn't found
	*/
	void SearchToken();

	/**
	* Copying the rest of the original file into the new one.
	*/
	void InsertROF(); // Inserting the rest of the file content.

	/**
	* Closing the 2 streams. The method is being called in the destructor.
	*/
	void CloseStreams();

	// Unimplemented methods
	
	/**
	* Checking if the token is inside the current line.
	* @return bool
	*/
	virtual bool LineFit(const string&) = 0;

	/**
	* The actual important method that differs within the different classes.
	* Each class implement differently, but the general idea is to insert the piece of text
	* to the current location in the new edited file.
	*/
	virtual void InsertContent() = 0;

protected:

	// The flag that indicates that the token was found
	bool flag = false;

	// Streams.
	ifstream src;
	ofstream dst;

	// Used strings
	string cur_line;

	string insertion;
	string origin_file;
	string file_copy;
	string file_type;
	string search_token;
	string closing_line;


public:

	/**
	* Constructor.
	*
	* @param input_src - the input source which the content is being extracted from. It's a kind of an abstract variable.
	* @param file - the file that is being edited.
	* @param type - the type of file that is being edited
	* @param token - the token that is being searched for in the file.
	* @param num_tokens - the number of tokens that are looked for (for replace or point to add something).
	* @param closing_string - if one would like to add a line to the end of the file. this is not required, in fact, it's only
	*	in the use of the hoc file that neuron will run, for it to close automatically.
	*
	* Inside it there is a call to a method creates a new name to the file and opening 2 streams for the new file the original one.
	*
	* @throws runtime error - if the streams couldn't open.
	*/
	FileEdit(const string& input_src,
			const string& file,
			const string& type,
			const string& token,
			int num_tokens,
			const string& closing_string = EMPTY);

	/*
	* Method.
	* The actual and usefull public method. Used for the actual operation on the files. It is a concrete method,
	* but uses virtual methods inside it.
	*/
	void Edit();

	/*
	* @return string - the name (as a string) of the new, edited name of the file
	*/
	string GetEditedFile();

	/**
	* Deleting the new file that was made.
	* This method is optional, but should be used when the file is not used any more, for keeping the folders simple and clean.
	*/
	void DeleteNewFile();
};



#endif
