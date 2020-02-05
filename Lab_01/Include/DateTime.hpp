#ifndef DATETIME_HPP
#define DATETIME_HPP

#include <ctime>
#include <iostream>
#include <string>
#include "../Include/Error.hpp"

class DateTime
{
public:
    unsigned short Years;
    unsigned char Months, Days, Hours, Minutes, Seconds;
    int Time;


    DateTime();
    DateTime(int time);
	DateTime(std::string time);
    DateTime(int year, int month, int day, int hour, int minute, int second);
    ~DateTime();

    std::string ToString();
    void SetTime(int year, int month, int day, int hour, int minute, int second);
    bool operator <(DateTime right);
    bool operator >(DateTime right);
    bool operator ==(DateTime right);
};

#endif //DATETIME_HPP
