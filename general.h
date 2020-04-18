#ifndef _GENERAL_H_
#define _GENERAL_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
#include <ctime>
#include "sha256.h"
using namespace std;

struct date {
	unsigned int year;
	unsigned short month, day;
};

struct time {
	unsigned short hour, minute;
};

struct Account {
	string username, password;
	bool isStudent; //Check if this account belongs to a student or a staff
};

struct Student {
	string ID, lastName, firstName, gender;
	date birthDate;
};

struct Class {
	string className, courseName;
	unsigned int nStudents;
	Student* studentArr;
};
#endif // !_GENERAL_H_
