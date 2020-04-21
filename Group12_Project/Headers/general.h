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

struct score {
	float midterm = 0;
	float final = 0;
	float bonus = 0;
	float total = 0;
};

struct Staff {
	string fullname;
	string email;
	char gender = 'M'; //'F' for female and 'M' for male
};

struct Lecturer {
	string fullname;
	string email;
	string academicRank;//Rank: Master/PhD/Professor
	char gender = 'M'; //'F' for female and 'M' for male
	tm birthDate;
};

struct Student {
	string fullname, ID, classID;
	char gender = 'M'; //'F' for female and 'M' for male
	tm birthDate;
	bool active = true; //Default state: Active = currently studying
};

struct Account {//When "role" value is changed, the corresponding profile will be loaded
	string username, password; //Password is always in hashed form
	int role = 0; //0 = logged out; 1 = Staff; 2 = Lecturer; 3 = Student
	Staff staffProfile;
	Lecturer lecturerProfile;
	Student studentProfile;
};

struct Class {
	string className;
	int nStudents = 0;
	Student* studentArr = nullptr;	//Ptr to dynamic array of students
};

struct Semester {	//Semester info from SemesterList
	string year;	//Academic year "YearA-YearB"
	string semester;//First or Second or Third semester
};

struct Course {
	Semester c_semester;
	string courseID, courseName;
	Class courseClass;
	Lecturer courseLecturer;
	tm startDate, endDate;
	int nWeeks = 0; //number of weeks of a course = (endDate - startDate)/7
	string classDay;
	tm startTime, endTime;
	string room;
};

struct scoreBoard {
	Course courseInfo; //Also contains an array of students in a class
	score* board = nullptr;	//This array will use the same indices/iterators as the student array
};

struct attendanceList {
	Course courseInfo;
	bool* checkList; //2D array of size nStudents * nWeeks; True = on class - False = absent
};
//Convert a date string with the format YYYY-MM-DD to struct tm and return the struct tm
tm sToDate(string date_str);

//Convert a time string with the format HH:MM to struct tm and return the struct tm
tm sToTime(string time_str);

//Print struct tm in date YYYY-MM-DD format
void printDate(ostream& stream, tm date);

//Print struct tm in time HH:MM format
void printTime(ostream &stream, tm time);

//flush the input stream to not cause error for getline
void flushin(istream& input);

//Semi-pause the program until user hit ENTER
void pause();
#endif // !_GENERAL_H_
