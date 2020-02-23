#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include <cmath>

enum ERROR
{
	FileDoesntExists = -1,
	FileCorrupted = -2,
	InvalidDate = -3,
	MessageNotFound = -4,
	RenamingError = -5,
};

const int MAX_ERROR = 5 + 1;
const std::string ERROR_TEXT[MAX_ERROR] =
{
    "Error doesn't exists!",	//WTF
    "File does't exists!",		//-1
    "File is corrupted!",		//-2
	"Invalid date format!",		//-3
	"Message not found!",		//-4
	"Can't rename/move file!",	//-5
};

inline std::string GetError(int id)
{
    id = std::abs(id);
    if (id >= MAX_ERROR) return ERROR_TEXT[0];
    else return ERROR_TEXT[id];
}

#endif //ERROR_HPP