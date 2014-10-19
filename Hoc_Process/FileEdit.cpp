#include "FileEdit.h"


FileEdit::FileEdit(const string& input_src,
					const string& file,
					const string& type,
					const string& token,
					int num_tokens,
					const string& closing_string)
{
	insertion = input_src;
	origin_file = file;
	file_type = type;
	search_token = token;
	num_of_tokens = num_tokens;
	closing_line = closing_string;

	NameChange();
	
	src = ifstream(origin_file, ios::binary);
	dst = ofstream(file_copy, ios::binary);
	
	if (!src.is_open() && !dst.is_open())
	{
		throw runtime_error(ERR_FO + origin_file + STR_OR + file_copy);
	}
}

// Changing the name of the origin file.
void FileEdit::NameChange()
{
	int length = origin_file.length();
	file_copy = origin_file;

	// Inserting just before the file suffix the signing of the new file (copy)
	file_copy.insert(length - file_type.length() - ONE, COPY_SUFFIX); // -1 for the point '.'
}



void FileEdit::SearchToken()
{
	// Reading the file, searching for the token.
	while (getline(src, cur_line))
	{
		string trimed_line;
		trimed_line = boost::trim_copy(cur_line);
		if (LineFit(trimed_line))
		{
			flag = true;
			break;
		}
		dst << cur_line;
	}
	
	// If it gets here, it means that it didn't find the token
	if (!flag)
	{
		throw runtime_error(ERR_MIS + search_token);
	}
}

void FileEdit::InsertROF()
{
	// Reading the content and copying it to the other file.
	while (getline(src, cur_line))
	{
		dst << cur_line;
	}
}

void FileEdit::CloseStreams()
{
	dst.close();
	src.close();
}

void FileEdit::Edit()
{
	// Searching for the tokens in the file, then copying the relevant part
	for (int i = 0; i < num_of_tokens; i++)
	{
		SearchToken();
		InsertContent();
		flag = false; // Reinitiallizing the flag.
	}

	InsertROF();

	if (!closing_line.empty())
	{
		dst << closing_line;
	}

	CloseStreams();
}

string FileEdit::GetEditedFile()
{
	return file_copy;
}


void FileEdit::DeleteNewFile()
{
	if (remove(file_copy.c_str()) != ZERO)
	{
		throw runtime_error(ERR_DEL + file_copy);
	}
}

