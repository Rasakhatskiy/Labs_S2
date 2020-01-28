#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include <cmath>

enum ERROR 
{
    FileDoesntExists = -1,
    FileCorrupted = -2
};

int MAX_ERROR = 2;
std::string[] ERROR_TEXT=
{
    "Error doesn't exists!",
    "File does't exists!",
    "File is corrupted!"
}

std::string GetError(int id)
{
    id = std::abs(id);
    if (id > MAX_ERROR) return ERROR_TEXT[0];
    else return ERROR_TEXT[id];
}

#endif //ERROR_HPP