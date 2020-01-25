#include "..\Include\DateTime.hpp"

DateTime::DateTime()
{
    Years = 0;
    Months = 0;
    Days = 0;
    Hours = 0;
    Minutes = 0;
    Seconds = 0;
    Time = 0;
}

DateTime::DateTime(int time)
{
    
    //6 bits - x, x+2000 = year
    //4 bits - month
    //5 bits - day
    //5 bits - hours
    //6 bits - minutes
    //6 bits - seconds
    
    //unsigned char = byte

    bool bitArray[32];
    for (int i = 31; i >= 0; --i)
    {
        bitArray[31 - i] = (time >> i) & 1;
    }

    Years = 0 |
        (bitArray[0] << 5) |
        (bitArray[1] << 4) |
        (bitArray[2] << 3) |
        (bitArray[3] << 2) |
        (bitArray[4] << 1) |
        (bitArray[5] << 0);
    Years += 1999;

    Months = 0 |
        (bitArray[6] << 3) |
        (bitArray[7] << 2) |
        (bitArray[8] << 1) |
        (bitArray[9] << 0);

    Days = 0 |
        (bitArray[10] << 4) |
        (bitArray[11] << 3) |
        (bitArray[12] << 2) |
        (bitArray[13] << 1) |
        (bitArray[14] << 0);

    Hours = 0 |
        (bitArray[15] << 4) |
        (bitArray[16] << 3) |
        (bitArray[17] << 2) |
        (bitArray[18] << 1) |
        (bitArray[19] << 0);

    Minutes = 0 |
        (bitArray[20] << 5) |
        (bitArray[21] << 4) |
        (bitArray[22] << 3) |
        (bitArray[23] << 2) |
        (bitArray[24] << 1) |
        (bitArray[25] << 0);

    Seconds = 0 |
        (bitArray[26] << 5) |
        (bitArray[27] << 4) |
        (bitArray[28] << 3) |
        (bitArray[29] << 2) |
        (bitArray[30] << 1) |
        (bitArray[31] << 0);
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second)
{
    Years = year;
    Months = month;
    Days = day;
    Hours = hour;
    Minutes = minute;
    Seconds = second;

    Time = 0;
    int i, k;

    for (i = 0, k = 5; i < 6; i++, k--)
        Time |= (((Years - 1999) & (1 << k)) >> k) << 31 - i;

    for (i = 6, k = 3; i < 10; i++, k--)
        Time |= ((Months & (1 << k)) >> k) << 31 - i;

    for (i = 10, k = 4; i < 15; i++, k--)
        Time |= ((Days & (1 << k)) >> k) << 31 - i;

    for (i = 15, k = 4; i < 20; i++, k--)
        Time |= ((Hours & (1 << k)) >> k) << 31 - i;

    for (i = 20, k = 5; i < 26; i++, k--)
        Time |= ((Minutes & (1 << k)) >> k) << 31 - i;

    for (i = 26, k = 5; i < 32; i++, k--)
        Time |= ((Seconds & (1 << k)) >> k) << 31 - i;
}

DateTime::~DateTime()
{
}

std::string DateTime::ToString()
{
    auto year = std::to_string(Years);

    auto month = std::to_string(Months);
    if (month.length() == 1) month = "0" + month;

    auto day = std::to_string(Days);
    if (day.length() == 1) day = "0" + day;

    auto hour = std::to_string(Hours);
    if (hour.length() == 1) hour = "0" + hour;

    auto minute = std::to_string(Minutes);
    if (minute.length() == 1) minute = "0" + minute;

    auto second = std::to_string(Seconds);
    if (second.length() == 1) second = "0" + second;

    return year + '-' + month + '-' + day + ' ' + hour + ':' + minute + ':' + second;
}

bool DateTime::operator<(DateTime right)
{
    return false;
}

bool DateTime::operator>(DateTime right)
{
    return false;
}

bool DateTime::operator==(DateTime right)
{
    return false;
}
