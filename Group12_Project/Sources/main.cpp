#include "../Headers/main.h"
int main() {
	Account user;
	int choice = 0; //Represent user's choice throughout the program
	while (choice != 2) {
		//Show startup menu
		choice = menuStart();
		//Log into user account
		if (choice == 1) {
			if (logIn(user)) {
				cout << "Login successfully" << endl << "\nWelcome, user " << user.username << '!' << endl;
				pause();
			}
			else {
				cerr << "Login failed! Please try again." << endl;
				pause();
			}
		}

		//Show main menu based on account's role
		//STAFF MENU
		while (user.role == 1) {	
			choice = menuStaff();
			//View staff profile
			if (choice == 1) {
				viewProfile(user);
				pause();
			}
			//Change staff password
			if (choice == 2) {
				if (changePassword(user)) {
					cout << "Your password has been changed successfully!" << endl;
					pause();
				}
				else {
					cerr << "Failed to change password! Please try again." << endl;
					pause();
				}
			}
			//CLASSES MENU
			if (choice == 3) {
				choice = 0;
				while (choice != 8) {
					choice = menuClass();
					/*Do something with classes data here



					*/
				}
				continue;
			}
			//COURSES MENU
			if (choice == 4) {
				choice = 0;
				while (choice != 14) {
					choice = menuCourse();
					/*Do something with courses data here



					*/
				}
				continue;
			}
			//SCOREBOARD MENU
			if (choice == 5) {
				choice = 0;
				while (choice != 3) {
					choice = menuScoreboard();
					/*Do something with course scoreboards data here



					*/
				}
				continue;
			}
			//ATTENDANCE LIST MENU
			if (choice == 6) {
				choice = 0;
				while (choice != 3) {
					choice = menuAttendanceList();
					/*Do something with course attendance data here


					*/
				}
				continue;
			}
			//LOG OUT
			if (choice == 7) {
				logOut(user);
				cout << "The account has been logged out!" << endl;
				pause();
			}
		}

		//LECTURER MENU
		while (user.role == 2) {
			choice = menuLecturer();
			//View lecturer profile
			if (choice == 1) {
				viewProfile(user);
				pause();
			}
			//Change lecturer password
			if (choice == 2) {
				if (changePassword(user)) {
					cout << "Your password has been changed successfully!" << endl;
					pause();
				}
				else {
					cerr << "Failed to change password! Please try again." << endl;
					pause();
				}
			}
			/*	ADD FUNCTIONS FOR CHOICE 3 TO 9 HERE






			*/
			//LOG OUT
			if (choice == 10) {
				logOut(user);
				cout << "The account has been logged out!" << endl;
				pause();
			}
		}

		//STUDENT MENU
		while (user.role == 3) {
			choice = menuStudent();
			//View student profile
			if (choice == 1) {
				viewProfile(user);
				pause();
			}
			//Change student password
			if (choice == 2) {
				if (changePassword(user)) {
					cout << "Your password has been changed successfully!" << endl;
					pause();
				}
				else {
					cerr << "Failed to change password! Please try again." << endl;
					pause();
				}
			}
			/*	ADD FUNCTIONS FOR CHOICE 3 TO 6 HERE






			*/
			//LOG OUT
			if (choice == 7) {
				logOut(user);
				cout << "The account has been logged out!" << endl;
				pause();
			}
		}
	}

	return 0;
}