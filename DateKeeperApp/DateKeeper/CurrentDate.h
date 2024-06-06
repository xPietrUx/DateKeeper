#include "pch.h"
#pragma once

class CurrentDate {
public:
    int day;
    int month;
    int year;

    CurrentDate();
    CurrentDate(int d, int m, int y);
    static CurrentDate getCurrentDate();
};
