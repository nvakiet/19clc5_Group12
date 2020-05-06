#include "../Headers/main.h"
int main() {
	//Account user;
	//Semester currentSemester;
	//int choice = 0; //Represent user's choice throughout the program
	//while (choice != 2) {
	//	//Show startup menu
	//	choice = menuStart();
	//	//Log into user account
	//	if (choice == 1) {
	//		if (logIn(user)) {
	//			cout << "Login successfully" << endl << "\nWelcome, user " << user.username << '!' << endl;
	//			pause();
	//		}
	//		else {
	//			cerr << "Login failed! Please try again." << endl;
	//			pause();
	//			continue;
	//		}
	//	}
	//	currentSemester = getCurrentSemester();
	//	if (updateSemester(currentSemester))
	//		cout << "The current semester has been updated!" << endl;
	//	else cerr << "Failed to update the current semester. Some functions may not work properly!" << endl;
	//	//Show main menu based on account's role
	//	//STAFF MENU
	//	while (user.role == 1) {	
	//		choice = menuStaff();
	//		//View staff profile
	//		if (choice == 1) {
	//			viewProfile(user);
	//			pause();
	//		}
	//		//Change staff password
	//		if (choice == 2) {
	//			if (changePassword(user)) {
	//				cout << "Your password has been changed successfully!" << endl;
	//				pause();
	//				continue;
	//			}
	//			else {
	//				cerr << "Failed to change password! Please try again." << endl;
	//				pause();
	//				continue;
	//			}
	//		}
	//		//CLASSES MENU
	//		if (choice == 3) {
	//			choice = 0;
	//			while (choice != 8) {
	//				choice = menuClass();
	//				if (choice == 1) {
	//					if (importClass())
	//						cout << "Import class successfully!" << endl;
	//					else cerr << "Failed to import class!" << endl;
	//					pause();
	//				}
	//				/*Do something with classes data here



	//				*/
	//			}
	//			continue;
	//		}
	//		//COURSES MENU
	//		if (choice == 4) {
	//			choice = 0;
	//			while (choice != 14) {
	//				choice = menuCourse();
	//				if (choice == 1) {
	//					viewSemesterList();
	//					pause();
	//				}
	//				if (choice == 2) {
	//					cout << "Current semester: " << endl;
	//					cout << "Academic year: " << currentSemester.year << endl;
	//					cout << "Semester: " << currentSemester.semester << endl;
	//					pause();
	//				}
	//				if (choice == 3) {
	//					if (deleteSemester()) {
	//						cout << "The semester has been deleted!" << endl;
	//						pause();
	//					}
	//					else {
	//						cerr << "Failed to delete the semester!" << endl;
	//						pause();
	//					}
	//				}
	//				/*	 DO SOMETHING WITH COURSE DATA HERE
	//				
	//				
	//				
	//				
	//				
	//				*/
	//			}
	//			continue;
	//		}
	//		//SEARCH - VIEW - EXPORT SCOREBOARD
	//		if (choice == 5) {
	//			SearchandViewScoreboard();
	//			pause();
	//		}
	//		//SEARCH - VIEW - EXPORT ATTENDANCE LIST
	//		if (choice == 6) {
	//			SearchandViewAttendance();
	//			pause();
	//		}
	//		//LOG OUT
	//		if (choice == 7) {
	//			logOut(user);
	//			cout << "The account has been logged out!" << endl;
	//			pause();
	//		}
	//	}

	//	//LECTURER MENU
	//	while (user.role == 2) {
	//		choice = menuLecturer();
	//		//View lecturer profile
	//		if (choice == 1) {
	//			viewProfile(user);
	//			pause();
	//		}
	//		//Change lecturer password
	//		if (choice == 2) {
	//			if (changePassword(user)) {
	//				cout << "Your password has been changed successfully!" << endl;
	//				pause();
	//				continue;
	//			}
	//			else {
	//				cerr << "Failed to change password! Please try again." << endl;
	//				pause();
	//				continue;
	//			}
	//		}
	//		/*	ADD FUNCTIONS FOR CHOICE 3 TO 9 HERE






	//		*/
	//		//LOG OUT
	//		if (choice == 10) {
	//			logOut(user);
	//			cout << "The account has been logged out!" << endl;
	//			pause();
	//		}
	//	}

	//	//STUDENT MENU
	//	while (user.role == 3) {
	//		choice = menuStudent();
	//		//View student profile
	//		if (choice == 1) {
	//			viewProfile(user);
	//			pause();
	//		}
	//		//Change student password
	//		if (choice == 2) {
	//			if (changePassword(user)) {
	//				cout << "Your password has been changed successfully!" << endl;
	//				pause();
	//				continue;
	//			}
	//			else {
	//				cerr << "Failed to change password! Please try again." << endl;
	//				pause();
	//				continue;
	//			}
	//		}
	//		/*	ADD FUNCTIONS FOR CHOICE 3 TO 6 HERE






	//		*/
	//		//LOG OUT
	//		if (choice == 7) {
	//			logOut(user);
	//			cout << "The account has been logged out!" << endl;
	//			pause();
	//		}
	//	}
	//}
	
addCourse();
	return 0;
}