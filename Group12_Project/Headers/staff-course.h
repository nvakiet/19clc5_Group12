#ifndef _COURSE_H_
#define _COURSE_H_

#include "../Headers/general.h"

typedef bool (*insertOrder)(string, string, string);

//Get current time from the system
//Convert it to tm structure
//If tm_mon > 7 (September-December), it's 1st semester, year: current year - next year
//If tm_mon < 4 (January-April), it's 2nd semester, year: last year - current year
//Otherwise, it's 3rd semester, year: last year - current year
Semester getCurrentSemester();

//Update a semester to Semesters.txt
bool updateSemester(Semester newSem);

//Delete a semester from Semesters.txt
bool deleteSemester();

//Print content of Semesters.txt to the screen
void viewSemesterList();

//Get inputs from user and import those information to the system
bool addCourse(Semester curSem);

//Parameter version to use with importCourse function
bool addCourse(Course inCourse, string slackName);

//Import course data from csv file to the system
bool importCourse(Semester curSem);

//Remove a regCourse
bool removeRegCourse(string path, string courseID, string classID);

//Delete a course in the program: delete info file, delete regCourse file, delete student list of course
bool removeCourse();

//Edit a course: No edit of courseID and class ID allowed
//If the edited lecturer is new, register their account
//If edit start/end date and start/end time, reset the attendance list and make change to student list of this course
bool editCourse();

//Add a student to the course
//This should only be used before the semester (first day of course) starts, because new student will have default scores and attendance
bool addCourseStudent(Semester curSem, void* checkOrder = insAscID);

//Remove a student from the course
//Completely remove the student from the student list of the course, and remove the course from the student's enrolling course list
bool removeCourseStudent(Semester curSem);

#endif // !_COURSE_H
