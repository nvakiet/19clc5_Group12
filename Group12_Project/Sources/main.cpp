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
			currentSemester = getCurrentSemester();
			if (updateSemester(currentSemester))
				cout << "The current semester has been updated!" << endl;
			else cerr << "Failed to update the current semester. Some functions may not work properly!" << endl;
		}
		//Show main menu based on account's role
		//STAFF MENU
		while (user.role == 1) {
			choice = menuStaff(currentSemester);
			//View staff profile
			if (choice == 1) {
				viewProfile(user);
				pause();
				continue;
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
					choice = menuClass(currentSemester);
					//Import student list of a class from csv file, sort the student list
					if (choice == 1) {
						if (importClass())
							cout << "Import class successfully!" << endl;
						else cerr << "Failed to import class!" << endl;
						pause();
						continue;
					}
					//Add a student to a class manually
					if (choice == 2) {
						if (addStudent())
							cout << "The student has been added successfully!" << endl;
						else cerr << "Failed to add the student!" << endl;
						pause();
						continue;
					}
					//Edit a student info, can reset password for student and change state between Active - Inactive
					if (choice == 3) {
						if (editStudent())
							cout << "The student's info has been edited successfully!" << endl;
						else cerr << "Failed to edit the student's info!" << endl;
						pause();
						continue;
					}
					//Remove a student from a class and also the student account, permanently
					if (choice == 4) {
						if (removeStudent())
							cout << "The student has been removed successfully!" << endl;
						else cerr << "Failed to remove the student!" << endl;
						pause();
						continue;
					}
					//Change student from class A to class B
					if (choice == 5) {
						if (changeClass(currentSemester))
							cout << "The student's class has been changed successfully!" << endl;
						else cerr << "Failed to change the student's class!" << endl;
						pause();
						continue;
					}
					//View a list of all imported classes
					if (choice == 6) {
						if (!viewClasses()) cerr << "Can't find list of classes! Please try to import a class first!" << endl;
						pause();
						continue;
					}
					//View student list of a class
					if (choice == 7) {
						if (!viewStudentsInClass()) cerr << "There's no student list available! Please import a class first!" << endl;
						pause();
						continue;
					}
				}
				continue;
			}
			//COURSES MENU
			if (choice == 4) {
				choice = 0;
				while (choice != 12) {
					choice = menuCourse(currentSemester);
					//View list of semester in the program
					if (choice == 1) {
						viewSemesterList();
						pause();
						continue;
					}
					//Delete a semester
					if (choice == 2) {
						if (deleteSemester()) cout << "The semester has been deleted!" << endl;
						else cerr << "Failed to delete the semester!" << endl;
						pause();
						continue;
					}
					//Import courses of a class in the current semester from csv file
					if (choice == 3) {
						if (importCourse(currentSemester)) cout << "The course list has been imported successfully!" << endl;
						else cerr << "Failed to import the course list! Please check the data in your file." << endl;
						pause();
						continue;
					}
					//Add a course manually
					if (choice == 4) {
						if (addCourse(currentSemester)) cout << "The course has been added successfully!" << endl;
						else cerr << "Failed to add the course! Please check the input data." << endl;
						pause();
						continue;
					}
					//Edit a course info (Excluding Semester infos, course ID and class ID of the course)
					if (choice == 5) {
						if (editCourse())
							cout << "The course has been edited successfully!" << endl;
						else cerr << "Failed to edit the course!" << endl;
						pause();
						continue;
					}
					//Remove a course from the system (complete remove the student list file)
					if (choice == 6) {
						if (removeCourse())
							cout << "The course has been successfully removed from the system!" << endl;
						else cerr << "Failed to completely remove to course!" << endl;
						pause();
						continue;
					}
					//Remove a student from the course
					if (choice == 7) {
						if (removeCourseStudent(currentSemester))
							cout << "The student has been removed from the course!" << endl;
						else cerr << "Failed to remove the student from the course!" << endl;
						pause();
						continue;
					}
					//Add a student to the course
					if (choice == 8) {
						if (addCourseStudent(currentSemester))
							cout << "The student has been added to the course!" << endl;
						else cerr << "Failed to add the student to the course!" << endl;
						pause();
						continue;
					}
					//View list of courses
					if (choice == 9) {
						ListOfCourse(currentSemester);
						pause();
						continue;
					}
					//View list of students of a course
					if (choice == 10) {
						viewStudentofAcourse(currentSemester);
						pause();
						continue;
					}
					//View all lecturer accounts
					if (choice == 11) {
						viewLecture();
						pause();
						continue;
					}
				}
				continue;
			}
			//SEARCH - VIEW - EXPORT SCOREBOARD
			if (choice == 5) {
				SearchandViewScoreboard();
				pause();
				continue;
			}
			//SEARCH - VIEW - EXPORT ATTENDANCE LIST
			if (choice == 6) {
				SearchandViewAttendance();
				pause();
				continue;
			}
			//LOG OUT
			if (choice == 7) {
				logOut(user);
				cout << "The account has been logged out!" << endl;
				pause();
				continue;
			}
		}

		//LECTURER MENU
		while (user.role == 2) {
			cout << "Current semester: " << currentSemester.year << " - " << currentSemester.semester << endl;
			choice = menuLecturer(currentSemester);
			//View lecturer profile
			if (choice == 1) {
				viewProfile(user);
				pause();
				continue;
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
			//View list of courses
			if (choice == 3) {
				ListOfCourse(currentSemester);
				pause();
				continue;
			}
			//View list of students of a course
			if (choice == 4) {
				viewStudentofAcourse(currentSemester);
				pause();
				continue;
			}
			//SEARCH - VIEW - EXPORT ATTENDANCE LIST
			if (choice == 5) {
				SearchandViewAttendance();
				pause();
				continue;
			}
			//Edit an attendance
			if (choice == 6) {
				if (editAttendance(currentSemester, user)) cout << "The attendance list of this course has been successfully edited!" << endl;
				else cerr << "Failed to edit the attendance list of this course!" << endl;
				pause();
				continue;
			}
			//Import a scoreboard
			if (choice == 7) {
				if (importScoreBoard(currentSemester, user)) cout << "The scoreboard has been successfully imported!" << endl;
				else cerr << "Failed to import the scoreboard!" << endl;
				pause();
				continue;
			}
			//Edit the grades of a student
			if (choice == 8) {
				if (editGrade(currentSemester, user)) cout << "The course grades of this student has been successfully edited!" << endl;
				else cerr << "Failed to edit the course grades of this student!" << endl;
				pause();
				continue;
			}
			//SEARCH - VIEW - EXPORT SCOREBOARD
			if (choice == 9) {
				SearchandViewScoreboard();
				pause();
				continue;
			}
			//LOG OUT
			if (choice == 10) {
				logOut(user);
				cout << "The account has been logged out!" << endl;
				pause();
				continue;
			}
		}

		//STUDENT MENU
		while (user.role == 3) {
			cout << "Current semester: " << currentSemester.year << " - " << currentSemester.semester << endl;
			choice = menuStudent(currentSemester);
			//View student profile
			if (choice == 1) {
				viewProfile(user);
				pause();
				continue;
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
			//Student check in
			if (choice == 3) {
				if (checkin(currentSemester, user))
					cout << "Check in successfully!" << endl;
				else cerr << "Failed to check in!" << endl;
				pause();
				continue;
			}
			//View check in result
			if (choice == 4) {
				if (!viewcheckin(user, currentSemester))
					cerr << "Failed to get information!" << endl;
				pause();
				continue;
			}
			//View student's schedule
			if (choice == 5) {
				viewSchedules(user, currentSemester);
				pause();
				continue;
			}
			//View student's scoreboard
			if (choice == 6) {
				if (!viewscore(user))
					cerr << "Failed to get information!" << endl;
				pause();
				continue;
			}
			//Logout
			if (choice == 7) {
				logOut(user);
				cout << "The account has been logged out!" << endl;
				pause();
				continue;
			}
		}

	}

	return 0;
}