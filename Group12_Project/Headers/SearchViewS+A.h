#ifndef _SearchViewSA_H_
#define _SearchViewSA_H_
#include "../Headers/general.h"
void SearchandViewScoreboard();
void SearchandViewAttendance();
void CSVScoreboard(Course B);
void CSVAttendance(Course B, string*& classdate);
bool viewcheckin(Account user, Semester cursem);
bool viewscore(Account user);
void viewSchedules(Account user, Semester curSem);
void viewLecture();
void ListOfCourse(Semester curS);
void viewStudentofAcourse(Semester cursem);
#endif // !_SearchViewS+A_H_
