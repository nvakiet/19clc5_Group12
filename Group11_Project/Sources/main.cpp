#include "../Headers/main.h"
int main() {
	Account user;
	int choice = 0; //Represent user's choice throughout the program
	while (choice = menuStart() != 2) {
		//Log into user account
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
	return 0;
}