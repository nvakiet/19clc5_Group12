#include "../Headers/main.h"
int main() {
	Account user;
	if (logIn(user))
		cout << "Welcome, " << user.username << endl;
	else cout << "Login failed. Please try again." << endl;
	return 0;
}