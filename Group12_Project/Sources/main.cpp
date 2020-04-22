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
				cout << "Login successfully" << endl << "Welcome, user " << user.username << '!' << endl;
				pause();
			}
			else {
				cerr << "Login failed! Please try again." << endl;
				pause();
				continue;
			}
		}
		//Show main menu based on account's role
		//Program functions for staff accounts
		while (user.role == 1) {
			choice = menuStaff();
		}
	}

	return 0;
}