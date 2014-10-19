#include "FileEditFromFile.h"

void FileEditFromFile::InsertContent()
{
	// Opening a stream for the text file, where the matlab (or hoc??) commands are found.
	ifstream insrt_file(insertion, ios::binary);

	if (insrt_file.is_open())
	{
		// Insert the last line that we stopped with.
		dst << cur_line;

		// Inserting the whole insertion file to the working file.
		string line;
		while (getline(insrt_file, line))
		{
			dst << line;
		}

		// Closing the stream of the insertion file.
		insrt_file.close();
	}
}

