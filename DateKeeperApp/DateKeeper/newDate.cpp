#include "pch.h"
#include "newDate.h"

std::tm newDate(int year, int month, int day) {
	std::tm time_in = { 0, 0, 0, day - 1, month - 1, year - 1900 };
	std::mktime(&time_in);
	return time_in;
}