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
	string Path = "./TextFiles/Staffs.txt";
	ifstream fin;
	fin.open(Path);
	if (!fin.is_open()) {
		cerr << "Can't open data file in the path: " << Path << endl;
		if (generateFile(Path, "")) {
			cout << "A new file has been generated!" << endl;
			cout << "Some data may be lost. The program will continue." << endl;
			cout << endl;
			fin.clear();
			fin.open(Path);
		}
		else {
			cerr << "Failed to generate a new data file" << endl;
			return false;
		}
	}
	if (!emptyFile(Path)) {
		int n;
		getline(fin, line);
		n = stoi(line);
		for (int i = 0; i < n; i++) {
			getline(fin, fileUsername);
			getline(fin, filePassword);
			if (fileUsername == user.username && filePassword == user.password) {
				user.role = 1;
				getline(fin, user.staffProfile.fullname);
				getline(fin, user.staffProfile.email);
				getline(fin, line);
				user.staffProfile.gender = line.front(); //Get first character of the gender string 'F' or 'M'
				return true;
			}
			else {	//The format of the file will have a blank line after each user info so we must skip n+1 lines
				//With n = number of data fields besides username and password
				for (int j = 0; j < 4; j++)
					fin.ignore(INT_MAX, '\n');
			}
		}
	}
	fin.close();

	//Check the inputs with lecturer accounts
	Path = "./TextFiles/Lecturers.txt";
	fin.open(Path);
	if (!fin.is_open()) {
		cerr << "Can't open data file in the path: " << Path << endl;
		if (generateFile(Path, "")) {
			cout << "A new file has been generated!" << endl;
			cout << "Some data may be lost. The program will continue." << endl;
			cout << endl;
			fin.clear();
			fin.open(Path);
		}
		else {
			cerr << "Failed to generate a new data file" << endl;
			return false;
		}
	}
	if (!emptyFile(Path)) {
		int n;
		getline(fin, line);
		n = stoi(line);
		for (int i = 0; i < n; i++) {
			getline(fin, fileUsername);
			getline(fin, filePassword);
			if (fileUsername == user.username && filePassword == user.password) {
				user.role = 2;
				getline(fin, user.lecturerProfile.fullname);
				getline(fin, user.lecturerProfile.email);
				getline(fin, user.lecturerProfile.academicRank);
				getline(fin, line);
				user.staffProfile.gender = line.front(); //Get first character of the gender string 'F' or 'M'
				getline(fin, line);
				user.lecturerProfile.birthDate = sToDate(line);
				return true;
			}
			else {
				for (int j = 0; j < 6; j++)
					fin.ignore(INT_MAX, '\n');
			}
		}
	}
	fin.close();

	//Check the inputs with student accounts
	Path = "./TextFiles/Students.txt";
	fin.open(Path);
	if (!fin.is_open()) {
		cerr << "Can't open data file in the path: " << Path << endl;
		if (generateFile(Path, "")) {
			cout << "A new file has been generated!" << endl;
			cout << "Some data may be lost. The program will continue." << endl;
			cout << endl;
			fin.clear();
			fin.open(Path);
		}
		else {
			cerr << "Failed to generate a new data file" << endl;
			return false;
		}
	}
	if (!emptyFile(Path)) {
		int n;
		getline(fin, line);
		n = stoi(line);
		for (int i = 0; i < n; i++) {
			getline(fin, fileUsername);
			getline(fin, filePassword);
			if (fileUsername == user.username && filePassword == user.password) {
				user.role = 3;
				getline(fin, user.studentProfile.fullname);
				getline(fin, user.studentProfile.classID);
				getline(fin, line);
				user.staffProfile.gender = line.front(); //Get first character of the gender string 'F' or 'M'
				getline(fin, line);
				user.studentProfile.birthDate = sToDate(line);
				getline(fin, line);
				user.studentProfile.active = stoi(line);
				user.studentProfile.ID = user.username;
				return true;
			}
			else {
				for (int j = 0; j < 6; j++)
					fin.ignore(INT_MAX, '\n');
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

bool changePassword(Account& user) {
	string passwordInput;
	//Get old password
	cout << "Enter current password: ";
	cin >> passwordInput;
	if (sha256(passwordInput) != user.password) {
		cerr << "The password you entered is incorrect!" << endl;
		return false;
	}
	//Get new password
	cout << "Enter new password (Minimum length: 8 characters): ";
	cin >> passwordInput;
	if (passwordInput.length() < 8) {
		cerr << "The password must be at least 8 characters long!" << endl;
		return false;
	}
	//Get new password once more time
	string line;
	cout << "Enter new password again: ";
	cin >> line;
	if (line != passwordInput) {
		cerr << "The password you re-entered does not match!" << endl;
		return false;
	}
	//Scan the correct file depending on account role
	passwordInput = sha256(passwordInput);	//Hash the new password string
	Account* userArr; //Use an array of account to temporarily store the file data
	int n;
	ifstream fin;
	ofstream fout;
	string Path;
	switch (user.role) {
	//Staff account
	case 1:
		Path = "./TextFiles/Staffs.txt";
		//Store data file into account array
		fin.open(Path);
		if (!fin.is_open() || emptyFile(Path)) {
			cerr << "Can't access account database at " << Path << endl;
			return false;
		}
		getline(fin, line);
		n = stoi(line);
		userArr = new Account[n];
		for (int i = 0; i < n; i++) {
			getline(fin, userArr[i].username);
			getline(fin, userArr[i].password);
			getline(fin, userArr[i].staffProfile.fullname);
			getline(fin, userArr[i].staffProfile.email);
			getline(fin, line);
			user.staffProfile.gender = line.front(); //Get first character of the gender string 'F' or 'M'
			fin.ignore(INT_MAX, '\n'); //This one is to skip the blank line
			if (userArr[i].username == user.username && userArr[i].password == user.password) {
				//Change password of the account currently logging in and the one in data file
				userArr[i].password = passwordInput;
				user.password = passwordInput;
			}
		}
		fin.close();
		//Overwrite data file with the modified array
		fout.open(Path);
		if (!fout.is_open()) {
			cerr << "Can't access account database at " << Path << endl;
			return false;
		}
		fout << n << endl;
		for (int i = 0; i < n; i++) {
			fout << userArr[i].username << endl
				<< userArr[i].password << endl
				<< userArr[i].staffProfile.fullname << endl
				<< userArr[i].staffProfile.email << endl
				<< userArr[i].staffProfile.gender << endl;
			fout << endl;
		}
		fout.close();
		//After writing, release the memory of array
		delete[] userArr;
		userArr = nullptr;
		break;

	//Lecturer account
	case 2:
		Path = "./TextFiles/Lecturers.txt";
		//Store data file into account array
		fin.open(Path);
		if (!fin.is_open() || emptyFile(Path)) {
			cerr << "Can't access account database at " << Path << endl;
			return false;
		}
		getline(fin, line);
		n = stoi(line);
		userArr = new Account[n];
		for (int i = 0; i < n; i++) {
			getline(fin, userArr[i].username);
			getline(fin, userArr[i].password);
			getline(fin, userArr[i].lecturerProfile.fullname);
			getline(fin, userArr[i].lecturerProfile.email);
			getline(fin, userArr[i].lecturerProfile.academicRank);
			getline(fin, line);
			user.staffProfile.gender = line.front(); //Get first character of the gender string 'F' or 'M'
			getline(fin, line);
			userArr[i].lecturerProfile.birthDate = sToDate(line);
			fin.ignore(INT_MAX, '\n'); //This one is to skip the blank line
			if (userArr[i].username == user.username && userArr[i].password == user.password) {
				//Change password of the account currently logging in and the one in data file
				userArr[i].password = passwordInput;
				user.password = passwordInput;
			}
		}
		fin.close();
		//Overwrite data file with the modified array
		fout.open(Path);
		if (!fout.is_open()) {
			cerr << "Can't access account database at " << Path << endl;
			return false;
		}
		fout << n << endl;
		for (int i = 0; i < n; i++) {
			fout << userArr[i].username << endl
				<< userArr[i].password << endl
				<< userArr[i].lecturerProfile.fullname << endl
				<< userArr[i].lecturerProfile.email << endl
				<< userArr[i].lecturerProfile.academicRank << endl
				<< userArr[i].lecturerProfile.gender << endl;
			printDate(fout, userArr[i].lecturerProfile.birthDate);
			fout << endl;
		}
		fout.close();
		//After writing, release the memory of array
		delete[] userArr;
		userArr = nullptr;
		break;

	//Student account
	case 3:
		Path = "./TextFiles/Students.txt";
		//Store data file into account array
		fin.open(Path);
		if (!fin.is_open() || emptyFile(Path)) {
			cerr << "Can't access account database at " << Path << endl;
			return false;
		}
		getline(fin, line);
		n = stoi(line);
		userArr = new Account[n];
		for (int i = 0; i < n; i++) {
			getline(fin, userArr[i].username);
			getline(fin, userArr[i].password);
			getline(fin, userArr[i].studentProfile.fullname);
			getline(fin, userArr[i].studentProfile.classID);
			getline(fin, line);
			user.staffProfile.gender = line.front(); //Get first character of the gender string 'F' or 'M'
			getline(fin, line);
			userArr[i].studentProfile.birthDate = sToDate(line);
			getline(fin, line);
			userArr[i].studentProfile.active = stoi(line);
			fin.ignore(INT_MAX, '\n');	//Skip the blank line
			if (userArr[i].username == user.username && userArr[i].password == user.password) {
				//Change password of the account currently logging in and the one in data file
				userArr[i].password = passwordInput;
				user.password = passwordInput;
			}
		}
		fin.close();
		//Overwrite data file with the modified array
		fout.open(Path);
		if (!fout.is_open()) {
			cerr << "Can't access account database at " << Path << endl;
			return false;
		}
		fout << n << endl;
		for (int i = 0; i < n; i++) {
			fout << userArr[i].username << endl
				<< userArr[i].password << endl
				<< userArr[i].studentProfile.fullname << endl
				<< userArr[i].studentProfile.classID << endl
				<< userArr[i].studentProfile.gender << endl;
			printDate(fout, userArr[i].studentProfile.birthDate);
			fout << userArr[i].studentProfile.active << endl;
			fout << endl;
		}
		fout.close();
		//After writing, release the memory of array
		delete[] userArr;
		userArr = nullptr;
		break;
	}
	return true;
}

int menuStart() {
	cout << string(50, '*') << endl;
	cout << string(12, ' ') << "STUDENT MANAGEMENT SYSTEM" << string(12, ' ') << endl;
	cout << string(50, '*') << endl;
	cout << "1 - LOGIN" << endl;
	cout << "2 - EXIT" << endl;
	cout << "--> CHOICE: ";
	string input;
	getline(cin, input);
	int choice = stoi(input);
	if (choice > 0 && choice < 3)
		return choice;
	else {
		cerr << "Invalid option. Please try again." << endl;
		return 0;
	}
}

int menuStaff() {
	cout << string(50, '*') << endl;
	cout << string(16, ' ') << "MAIN MENU - STAFF" << string(16, ' ') << endl;
	cout << string(50, '*') << endl;
	cout << "1 - ACCOUNT PROFILE" << endl;
	cout << "2 - CHANGE PASSWORD" << endl;
	cout << "3 - MENU: CLASS" << endl;
	cout << "4 - MENU: COURSE" << endl;
	cout << "5 - MENU: SCOREBOARD" << endl;
	cout << "6 - MENU: ATTENDANCE LIST" << endl;
	cout << "7 - LOG OUT" << endl;
	string input;
	getline(cin, input);
	int choice = stoi(input);
	if (choice > 0 && choice < 8)
		return choice;
	else {
		cerr << "Invalid option. Please try again." << endl;
		return 0;
	}
}