#include "../Headers/main.h"
int main() {
	Account user;
	string path;
	if (logIn(user))
		cout << "Welcome, " << user.username << endl;
	else cerr << "Login failed. Please try again." << endl;
	if (changePassword(user))
		cout << "Your password has been changed successfully!" << endl;
	else cerr << "Failed to change password. Please try again." << endl;
	if (logIn(user))
		cout << "Welcome, " << user.username << endl;
	else cerr << "Login failed. Please try again." << endl;
	if (importFromCSV(path))
		cout << "Successful";
	return 0;
}