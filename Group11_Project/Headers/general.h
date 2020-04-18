#ifndef _GENERAL_H_
#define _GENERAL_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <ctime>
#include "sha256.h"
using namespace std;

struct Account {
	string username, password;
};

struct profileStaff {
	string fullname;
	bool gender = false; //False: female; True: male
};

struct profileLecturer {
	string fullname, academicRank;	//Rank: Master/PhD/Professor
	bool gender = false; //False: female; True: male
	tm birthDate;
};

struct profileStudent {
	string fullname, ID, major;
	bool gender = false; //False: female; True: male
	tm birthDate;
};

struct Student {
	string ID, lastName, firstName;
	bool gender = false; //False: female; True: male
	tm birthDate;
};

struct Class {
	string className, courseName;
	unsigned int nStudents;
	Student* studentArr;
};
#endif // !_GENERAL_H_
