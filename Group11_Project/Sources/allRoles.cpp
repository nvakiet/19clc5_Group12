#include "../Headers/allRoles.h"

bool logIn(Account& user) {
	//Return value: 
	// - True if username and password are found in one of the account data files
	// - False if one of the files fail to open or can't find any correct set of username and password in all files
	string fileUsername, filePassword, line;
	cout << "Enter username: ";
	cin >> user.username;
	cout << "Enter password: ";
	cin >> user.password;
	user.password = sha256(user.password);	//Hash password right after it is entered
	cout << "\nLogging in. Please wait..." << endl;

	//Check the inputs with the staff accounts
	string Path = "./TextFiles/staffAccounts.txt";
	ifstream fin;
	fin.open(Path);
	if (!fin.is_open()) {
		cerr << "Can't open data file in the path: " << Path << endl;
		cerr << "The user database may be missing!" << endl;
		return false;
	}
	if (!fin.eof()) {	//Check if file is empty
		int n;
		fin >> n;
		for (int i = 0; i < n; i++) {
			fin >> fileUsername >> filePassword;
			if (fileUsername == user.username && filePassword == user.password) {
				user.role = 1;
				fin >> user.staffProfile.fullname >> user.staffProfile.email >> user.staffProfile.gender;
				return true;
			}
			else {	//The format of the file will have a blank line after each user info so we must skip n+1 lines
				//With n = number of data fields besides username and password
				for (int j = 0; j < 4; j++)
					fin.ignore(2000, '\n');
			}
		}
	}
	fin.close();

	//Check the inputs with lecturer accounts
	Path = "./TextFiles/lecturerAccounts.txt";
	fin.open(Path);
	if (!fin.is_open()) {
		cerr << "Can't open data file in the path: " << Path << endl;
		cerr << "The user database may be missing!" << endl;
		return false;
	}
	if (!fin.eof()) {
		int n;
		fin >> n;
		for (int i = 0; i < n; i++) {
			fin >> fileUsername >> filePassword;
			if (fileUsername == user.username && filePassword == user.password) {
				user.role = 2;
				string DoB;
				fin >> user.lecturerProfile.fullname;
				fin >> user.lecturerProfile.email;
				fin >> user.lecturerProfile.academicRank;
				fin >> user.lecturerProfile.gender;
				fin >> DoB;
				user.lecturerProfile.birthDate = sToDate(DoB);
				return true;
			}
			else {
				for (int j = 0; j < 6; j++)
					fin.ignore(2000, '\n');
			}
		}
	}
	fin.close();

	//Check the inputs with student accounts
	Path = "./TextFiles/studentAccounts.txt";
	fin.open(Path);
	if (!fin.is_open()) {
		cerr << "Can't open data file in the path: " << Path << endl;
		cerr << "The user database may be missing!" << endl;
		return false;
	}
	if (!fin.eof()) {
		int n;
		fin >> n;
		for (int i = 0; i < n; i++) {
			fin >> fileUsername >> filePassword;
			if (fileUsername == user.username && filePassword == user.password) {
				user.role = 3;
				string DoB;
				fin >> user.studentProfile.fullname;
				fin >> user.studentProfile.ID;
				fin >> user.studentProfile.email;
				fin >> user.studentProfile.gender;
				fin >> DoB;
				user.studentProfile.birthDate = sToDate(DoB);
				fin >> user.studentProfile.active;
				return true;
			}
			else {
				for (int j = 0; j < 7; j++)
					fin.ignore(2000, '\n');
			}
		}
	}
	fin.close();

	//If can't find the correct username and password after scanning through all 3 files
	cerr << "The username or password you entered is incorrect!" << endl;
	user.username.clear();
	user.password.clear();
	user.role = 0;
	return false;
}