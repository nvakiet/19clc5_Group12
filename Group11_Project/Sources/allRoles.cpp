#include "../Headers/allRoles.h"

bool logIn(Account& user) {
	//Return value: 
	// - True if username and password are found in one of the account data files
	// - False if one of the files fail to open or can't find any correct set of username and password in all files
	string fileUsername, filePassword;
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
		fin.ignore(2000, '\n');
		for (int i = 0; i < n; i++) {
			getline(fin, fileUsername);
			getline(fin, filePassword);
			if (fileUsername == user.username && filePassword == user.password) {
				user.role = 1;
				getline(fin, user.staffProfile.fullname);
				getline(fin, user.staffProfile.email);
				fin >> user.staffProfile.gender;
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
		fin.ignore(2000, '\n');
		for (int i = 0; i < n; i++) {
			getline(fin, fileUsername);
			getline(fin, filePassword);
			if (fileUsername == user.username && filePassword == user.password) {
				user.role = 2;
				string DoB;
				getline(fin, user.lecturerProfile.fullname);
				getline(fin, user.lecturerProfile.email);
				getline(fin, user.lecturerProfile.academicRank);
				fin >> user.lecturerProfile.gender;
				fin.ignore(2000, '\n');
				getline(fin, DoB);
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
		fin.ignore(2000, '\n');
		for (int i = 0; i < n; i++) {
			getline(fin, fileUsername);
			getline(fin, filePassword);
			if (fileUsername == user.username && filePassword == user.password) {
				user.role = 3;
				string DoB;
				getline(fin, user.studentProfile.fullname);
				getline(fin, user.studentProfile.ID);
				getline(fin, user.studentProfile.email);
				fin >> user.studentProfile.gender;
				fin.ignore(2000, '\n');
				getline(fin, DoB);
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
	string temp;
	cout << "Enter new password again: ";
	cin >> temp;
	if (temp != passwordInput) {
		cerr << "The password you re-entered does not match!" << endl;
		return false;
	}
	temp.clear();
	//Scan the correct file depending on account role
	passwordInput = sha256(passwordInput);	//Hash the new password string
	Account* userArr; //Use an array of account to temporarily store the file data
	int n;
	ifstream fin;
	ofstream fout;
	string filePath, DoB;
	switch (user.role) {
	//Staff account
	case 1:
		filePath = "./TextFiles/staffAccounts.txt";
		//Store data file into account array
		fin.open(filePath);
		if (!fin.is_open()) {
			cerr << "Can't find account data at " << filePath << endl;
			return false;
		}
		fin >> n;
		fin.ignore(2000, '\n');
		userArr = new Account[n];
		for (int i = 0; i < n; i++) {
			getline(fin, userArr[i].username);
			getline(fin, userArr[i].password);
			getline(fin, userArr[i].staffProfile.fullname);
			getline(fin, userArr[i].staffProfile.email);
			fin >> userArr[i].staffProfile.gender;
			fin.ignore(2000, '\n');	//This one is to flush the buffer
			fin.ignore(2000, '\n'); //This one is to skip the blank line
			if (userArr[i].username == user.username && userArr[i].password == user.password) {
				//Change password of the account currently logging in and the one in data file
				userArr[i].password = passwordInput;
				user.password = passwordInput;
			}
		}
		fin.close();
		//Overwrite data file with the modified array
		fout.open(filePath);
		if (!fout.is_open()) {
			cerr << "Can't find account data at " << filePath << endl;
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
		filePath = "./TextFiles/lecturerAccounts.txt";
		//Store data file into account array
		fin.open(filePath);
		if (!fin.is_open()) {
			cerr << "Can't find account data at " << filePath << endl;
			return false;
		}
		fin >> n;
		fin.ignore(2000, '\n');
		userArr = new Account[n];
		for (int i = 0; i < n; i++) {
			getline(fin, userArr[i].username);
			getline(fin, userArr[i].password);
			getline(fin, userArr[i].lecturerProfile.fullname);
			getline(fin, userArr[i].lecturerProfile.email);
			getline(fin, userArr[i].lecturerProfile.academicRank);
			fin >> userArr[i].lecturerProfile.gender;
			fin.ignore(2000, '\n');	//Flush the buffer
			getline(fin, DoB);
			userArr[i].lecturerProfile.birthDate = sToDate(DoB);
			fin.ignore(2000, '\n'); //This one is to skip the blank line
			if (userArr[i].username == user.username && userArr[i].password == user.password) {
				//Change password of the account currently logging in and the one in data file
				userArr[i].password = passwordInput;
				user.password = passwordInput;
			}
		}
		fin.close();
		//Overwrite data file with the modified array
		fout.open(filePath);
		if (!fout.is_open()) {
			cerr << "Can't find account data at " << filePath << endl;
			return false;
		}
		fout << n << endl;
		for (int i = 0; i < n; i++) {
			fout << userArr[i].username << endl
				<< userArr[i].password << endl
				<< userArr[i].lecturerProfile.fullname << endl
				<< userArr[i].lecturerProfile.email << endl
				<< userArr[i].lecturerProfile.academicRank << endl
				<< userArr[i].lecturerProfile.gender << endl
				<< userArr[i].lecturerProfile.birthDate.tm_year + 1900 << '-'
				<< userArr[i].lecturerProfile.birthDate.tm_mon + 1 << '-'
				<< userArr[i].lecturerProfile.birthDate.tm_mday << endl;
			fout << endl;
		}
		fout.close();
		//After writing, release the memory of array
		delete[] userArr;
		userArr = nullptr;
		break;

	//Student account
	case 3:
		filePath = "./TextFiles/studentAccounts.txt";
		//Store data file into account array
		fin.open(filePath);
		if (!fin.is_open()) {
			cerr << "Can't find account data at " << filePath << endl;
			return false;
		}
		fin >> n;
		fin.ignore(2000, '\n');
		userArr = new Account[n];
		for (int i = 0; i < n; i++) {
			getline(fin, userArr[i].username);
			getline(fin, userArr[i].password);
			getline(fin, userArr[i].studentProfile.fullname);
			getline(fin, userArr[i].studentProfile.ID);
			getline(fin, userArr[i].studentProfile.email);
			fin >> userArr[i].studentProfile.gender;
			fin.ignore(2000, '\n');	//Flush the buffer
			getline(fin, DoB);
			userArr[i].studentProfile.birthDate = sToDate(DoB);
			fin >> userArr[i].studentProfile.active;
			fin.ignore(2000, '\n');	//Flush the buffer
			fin.ignore(2000, '\n');	//Skip the blank line
			if (userArr[i].username == user.username && userArr[i].password == user.password) {
				//Change password of the account currently logging in and the one in data file
				userArr[i].password = passwordInput;
				user.password = passwordInput;
			}
		}
		fin.close();
		//Overwrite data file with the modified array
		fout.open(filePath);
		if (!fout.is_open()) {
			cerr << "Can't find account data at " << filePath << endl;
			return false;
		}
		fout << n << endl;
		for (int i = 0; i < n; i++) {
			fout << userArr[i].username << endl
				<< userArr[i].password << endl
				<< userArr[i].studentProfile.fullname << endl
				<< userArr[i].studentProfile.ID << endl
				<< userArr[i].studentProfile.email << endl
				<< userArr[i].studentProfile.gender << endl
				<< userArr[i].studentProfile.birthDate.tm_year + 1900 << '-'
				<< userArr[i].studentProfile.birthDate.tm_mon + 1 << '-'
				<< userArr[i].studentProfile.birthDate.tm_mday << endl
				<< userArr[i].studentProfile.active << endl;
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