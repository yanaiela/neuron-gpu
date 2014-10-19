#include "FileEditFromFile.h"

void FileEditFromFile::InsertContent()
{
	// Opening a stream for the text file, where the matlab commands are found.
	ifstream insrt_file(insertion, ios::binary); // It assumes that the insertion file is found in the same folder

	if (insrt_file.is_open())
	{
		// Insert the last line that we stopped with.
		dst << cur_line;

		string line;
		while (getline(insrt_file, line))
		{
			dst << line;
		}
		insrt_file.close(); // Closing the stream
	}
}

