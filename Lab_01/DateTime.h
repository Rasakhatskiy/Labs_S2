#ifndef DATETIME_H
#define DATETIME_H

#include <ctime>
#include <iostream>
#include <string>

class DateTime
{
public:
    unsigned short Years;
    unsigned char Months, Days, Hours, Minutes, Seconds;
    int Time;


    DateTime();
    DateTime(int time);
    DateTime(int year, int month, int day, int hour, int minute, int second);
    ~DateTime();

    std::string ToString();
    void SetTime(int year, int month, int day, int hour, int minute, int second);
    bool operator <(DateTime right);
    bool operator >(DateTime right);
    bool operator ==(DateTime right);
};

#endif //DATETIME_H
