#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>
#include <cmath>

enum ERROR 
{
    FileDoesntExists = -1,
    FileCorrupted = -2
};

const int MAX_ERROR = 3;
const std::string ERROR_TEXT[MAX_ERROR] =
{
    "Error doesn't exists!",
    "File does't exists!",
    "File is corrupted!"
};

inline std::string GetError(int id)
{
    id = std::abs(id);
    if (id >= MAX_ERROR) return ERROR_TEXT[0];
    else return ERROR_TEXT[id];
}

#endif //ERROR_HPP