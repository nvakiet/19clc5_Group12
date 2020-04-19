#ifndef _GENERAL_H_
#define _GENERAL_H_

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <cstring>
#include <ctime>
#include "../Headers/sha256.h"
using namespace std;

struct Staff {
	string fullname;
	string email;
	bool gender; //False/0 = Female; True/1 = Male
};

struct Lecturer {
	string fullname;
	string email;
	string academicRank;//Rank: Master/PhD/Professor
	bool gender; //False/0 = Female; True/1 = Male
	tm birthDate;
};

struct Student {
	string fullname, ID, email;
	bool gender; //False/0 = Female; True/1 = Male
	tm birthDate;
	bool active; //Default state: Active = currently studying
};

struct Account {//When "role" value is changed, the corresponding profile will be loaded
	string username, password; //Password is always in hashed form
	int role; //0 = logged out; 1 = Staff; 2 = Lecturer; 3 = Student
	Staff staffProfile;
	Lecturer lecturerProfile;
	Student studentProfile;
};

struct Class {
	string className, courseName;
	unsigned int nStudents;
	Student* studentArr;	//Ptr to dynamic array of students
};

//Convert a date string with the format YYYY-MM-DD to struct tm and return the struct tm
tm sToDate(string date_str);

//Convert a time string with the format HH:MM to struct tm and return the struct tm
tm sToTime(string time_str);
struct Semester {
	string year;
	string semester;
};
//Nhap thong tin year, semester cua phan 3.1 vao text Semester.txt
#endif // !_GENERAL_H_
