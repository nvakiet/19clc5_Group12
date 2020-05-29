#ifndef _STAFF_CLASS_H_
#define _STAFF_CLASS_H_
#include "../Headers/general.h"
bool importClass(cmpr orderStu = ascendingID, cmpr orderAcc = ascendingUsername);
bool addStudent(cmpr orderStu = ascendingID, cmpr orderAcc = ascendingUsername);
bool removeStudent();
bool editStudent();
bool viewStudentsInClass();
bool changeClass();
#endif
