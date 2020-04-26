#ifndef _COURSE_H_
#define _COURSE_H_

#include "../Headers/general.h"

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


#endif // !_COURSE_H
