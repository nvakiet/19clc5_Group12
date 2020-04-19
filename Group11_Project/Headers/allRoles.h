#ifndef _ALLROLES_H_
#define _ALLROLES_H_

#include "../Headers/general.h"

//Takes user inputs, passes data from file to account, compares with input
//If input strings and datas from file are the same, then loads the profile corresponding with user's role to account
//True = logged in successfully
bool logIn(Account& user);	

////Asks user to re-input old password, if correct then asks user to input new password twice
////If both times are the same then starts scanning account files according to "role" value
////As we scan through the file, load the data into a single linked list
////If the username is found, load the new password to the linked list instead
////Output contents in linked list to the account file in truncate mode
////True: password changed successfully
//bool changePassword(Account& user);
//
////Prints Startup menu to the screen, take user's choice and return the choice back to the system
// //1: Login; 2: Exit program
////Menu loop break condition: when choose exit
//int menuStart();
//
////Prints main menu for Academic Staff user
////Menu loop break condition: when user role is changed to 0 by logOut function
//int menuStaff();
//
////Prints main menu for Lecturer user
////Menu loop break condition: when user role is changed to 0 by logOut function
//int menuLecturer();
//
////Prints main menu for Student user
////Menu loop break condition: when user role is changed to 0 by logOut function
//int menuStudent();
//
////Prints Class menu
////Menu loop break condition: When user choice is "Back to main menu"
//int menuClass();
//
////Prints Course menu
////Menu loop break condition: When user choice is "Back to main menu"
//int menuCourse();
//
////Prints Scoreboard menu
////Menu loop break condition: When user choice is "Back to main menu"
//int menuScoreboard();
//
////Prints Attendance List menu
////Menu loop break condition: When user choice is "Back to main menu"
//int menuAttendanceList();
//
////Simply prints out the profile stored in the account currently logging in
////The profile printed out will be depended on the "role" value
//void viewProfile(Account user);
//
////Asks user for confirmation first
////If the user surely wants to log out then reset the account to blank state, set the account role to 0
////Return true: Logged out successfully, return to Startup menu
//bool logOut(Account& user);

#endif // !_ALLROLES_H_
