#include "pch.h"
#include "CurrentDate.h"
#include <ctime>
#include <iostream>

CurrentDate::CurrentDate() : day(0), month(0), year(0) {}

CurrentDate::CurrentDate(int d, int m, int y) : day(d), month(m), year(y) {}

CurrentDate CurrentDate::getCurrentDate() {
    std::time_t now = std::time(nullptr);
    std::tm localTime;

    if (localtime_s(&localTime, &now) != 0) {
        return CurrentDate();
    }

    int day = localTime.tm_mday;
    int month = localTime.tm_mon + 1;
    int year = localTime.tm_year + 1900;

    return CurrentDate(day, month, year);
}