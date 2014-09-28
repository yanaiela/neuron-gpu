#include "Hoc_Process.h"

#include <boost/algorithm/string/trim.hpp>


/************************************************************************
* Class name: Hoc_Process
* The Input: The entire path of the hoc file with the file iteself (or, if the 
* file is in the exe folder, it can be only the name of the file itself).
* The class operation: making a copy of the file, changing it's name, adding
* a few lines of code at a preposition, and at the end of the file adding 
* a command that make it close when end to process.
*************************************************************************/


// Public methods:

// Constructor
Hoc_Process::Hoc_Process(const string& path)
{
	orig_hoc_path = path;
	NameChange();
}

/*
* Copying from the first file to the second one it's content.
* There should be a comment in the original file: '//ADD STUFF HERE\r'
* from this line and further, i'm inserting another text file content
* which are matlab code for the neuron to operate. 
*/
void Hoc_Process::Process()
{
	ifstream src(orig_hoc_path, ios::binary);
	ofstream dst(new_hoc_path, ios::binary);

	// Reading the file, searching for the INSERT_DATA token.
	bool flag = false;
	if (src.is_open() && dst.is_open())
	{
		string line;
		while (getline(src, line))
		{
			// When finding the coresponding line.
			
			string trimed_line;
			trimed_line = boost::trim_copy(line); // new 23.09.14
			if (trimed_line.compare(INSERT_DATA) == EQUALS)
			{
				dst << line;
				flag = true;
				break;
			}
			dst << line;
		}
	}
	// If getting to the end of file, and didn't find the token
	// it means that there's a problem (missing part)
	if (!flag)
	{
		// TODO optional make an Exception class, which would alert of missing info.
		throw runtime_error(ERR_MIS + orig_hoc_path);
		
	}

	// Opening a stream for the text file, where the matlab commands are found.
	ifstream insrt_file(INSERT_FILE, ios::binary); // It assumes that the INSERT_FILE is found in the same folder

	if (insrt_file.is_open())
	{
		string line;
		while (getline(insrt_file, line))
		{
			dst << line;
		}
		insrt_file.close(); // Closing the stream
	}

	// Inserting the rest of the original file content
	string line;
	while (getline(src, line))
	{
		dst << line;
	}

	/* Adding a quit command to the new file
	 for the neuron to close after it's done */
	dst << QUIT;

	src.close();
	dst.close();
}

string Hoc_Process::GetNewHocFile()
{
	return new_hoc_path;
}



// Private methods:

void Hoc_Process::NameChange()
{
	int length = orig_hoc_path.length();
	new_hoc_path = orig_hoc_path;

	// Inserting just before the hoc file suffix (.hoc) the signing of the new file
	new_hoc_path.insert(length - SUFFIX_LENGTH, ADDSUFFIX);
}


