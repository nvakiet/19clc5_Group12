#ifndef _ALLROLES_H_
#define _ALLROLES_H_

#include "general.h"

int logIn(Account& user);//Take user inputs, pass to the account, look for the correct username and password in txt files
bool changePassword(Account& user); //Get new password from the user, edit to account and make change to the txt files
int menuMain(); //1: Login; 2: Exit program

#endif // !_ALLROLES_H_
