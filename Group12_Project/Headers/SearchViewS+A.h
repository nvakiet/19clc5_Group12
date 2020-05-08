#ifndef _SearchViewSA_H_
#define _SearchViewSA_H_
#include "../Headers/general.h"
void viewScoreboard(Course B);
void viewAttendance(Course B, string* classdate);
void SearchandViewScoreboard();
void SearchandViewAttendance();
void CSVScoreboard(Course B);
void CSVAttendance(Course B, string*& classdate);
bool viewcheckin(Account user);
bool viewscore(Account user);
#endif // !_SearchViewS+A_H_
