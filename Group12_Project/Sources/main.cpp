#include "../Headers/main.h"
int main() {
	Account user;
	Semester currentSemester;
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
				continue;
			}
		}
		currentSemester = getCurrentSemester();
		if (updateSemester(currentSemester))
			cout << "The current semester has been updated!" << endl;
		else cerr << "Failed to update the current semester. Some functions may not work properly!" << endl;
		//Show main menu based on account's role
		//STAFF MENU
		while (user.role == 1) {
			cout << "Current semester: " << currentSemester.year << " - " << currentSemester.semester << endl;
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
					continue;
				}
				else {
					cerr << "Failed to change password! Please try again." << endl;
					pause();
					continue;
				}
			}
			//CLASSES MENU
			if (choice == 3) {
				choice = 0;
				while (choice != 8) {
					choice = menuClass();
					if (choice == 1) {
						if (importClass())
							cout << "Import class successfully!" << endl;
						else cerr << "Failed to import class!" << endl;
						pause();
					}
					if (choice == 2) {
						if (addStudent())
							cout << "The student has been added successfully!" << endl;
						else cerr << "Failed to add the student!" << endl;
						pause();
					}
					if (choice == 3) {
						if (editStudent())
							cout << "The student's info has been edited successfully!" << endl;
						else cerr << "Failed to edit the student's info!" << endl;
						pause();
					}
					if (choice == 4) {
						if (removeStudent())
							cout << "The student has been removed successfully!" << endl;
						else cerr << "Failed to remove the student!" << endl;
						pause();
					}
					/*Do something with classes data here



					*/
				}
				continue;
			}
			//COURSES MENU
			if (choice == 4) {
				choice = 0;
				while (choice != 12) {
					choice = menuCourse();
					if (choice == 1) {
						viewSemesterList();
						pause();
					}
					if (choice == 2) {
						if (deleteSemester()) {
							cout << "The semester has been deleted!" << endl;
							pause();
						}
						else {
							cerr << "Failed to delete the semester!" << endl;
							pause();
						}
					}
					if (choice == 3) {
						if (importCourse()) {
							cout << "The course list has been imported successfully!" << endl;
							pause();
						}
						else {
							cerr << "Failed to import the course list! Please check the data in your file." << endl;
							pause();
						}
					}
					if (choice == 4) {
						if (addCourse()) {
							cout << "The course has been added successfully!" << endl;
							pause();
						}
						else {
							cerr << "Failed to add the course! Please check the input data." << endl;
							pause();
						}
					}
					/*	 DO SOMETHING WITH COURSE DATA HERE
					
					
					*/
				}
				continue;
			}
			//SEARCH - VIEW - EXPORT SCOREBOARD
			if (choice == 5) {
				SearchandViewScoreboard();
				pause();
			}
			//SEARCH - VIEW - EXPORT ATTENDANCE LIST
			if (choice == 6) {
				SearchandViewAttendance();
				pause();
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
			cout << "Current semester: " << currentSemester.year << " - " << currentSemester.semester << endl;
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
					continue;
				}
				else {
					cerr << "Failed to change password! Please try again." << endl;
					pause();
					continue;
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
			cout << "Current semester: " << currentSemester.year << " - " << currentSemester.semester << endl;
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
					continue;
				}
				else {
					cerr << "Failed to change password! Please try again." << endl;
					pause();
					continue;
				}
			}
			//View check in result
			if (choice == 4) {
				if (!viewcheckin(user))
					cerr << "Failed to get information!" << endl;
				pause();
			}
			//View student's scoreboard
			if (choice == 6) {
				if (!viewscore(user))
					cerr << "Failed to get information!" << endl;
				pause();
			}
			//Logout
			if (choice == 7) {
				logOut(user);
				cout << "The account has been logged out!" << endl;
				pause();
			}
		}

	}

	return 0;
}