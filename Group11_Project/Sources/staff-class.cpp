#include "../Headers/staff-class.h"
bool importFromCSV(string& path) {

	cout << "Enter csv file path: ";	//./TextFiles/19CLC10-student.csv
	cin >> path;
	ifstream fin;
	fin.open("./TextFiles/19CLC10-student.csv");

	if (!fin.is_open()) {
		cerr << "Cannot open file";
		return false;
	}

	int count=0;
	string DoB, sex, line;

	while (getline(fin, line))
		count++;

	Account* newUser;
	newUser = new Account[count];
	for (int i = 0; i < count; i++) {
		getline(fin, newUser[i].studentProfile.ID, ';');
		getline(fin, newUser[i].studentProfile.fullname, ';');
		getline(fin, sex, ';');
		if (sex == "1")
			newUser[i].studentProfile.gender = 1;
		else newUser[i].studentProfile.gender = 0;

		getline(fin, DoB);
		newUser[i].studentProfile.birthDate = sToDate(DoB);
	}
	fin.close();

	ofstream fout;
	fout.open("./TextFiles/Test.txt", ios::app);

	if (!fout.is_open()) {
		cerr << "Cannot open file";
		return false;
	}

	for (int i = 0; i < count; i++) {
		newUser[i].username = newUser[i].studentProfile.ID;

		string newyyyy = to_string(newUser[i].studentProfile.birthDate.tm_year + 1900);
		string newmm = to_string(newUser[i].studentProfile.birthDate.tm_mon + 1);
		string newdd = to_string(newUser[i].studentProfile.birthDate.tm_mday);

		string newpass = newyyyy + newmm + newdd;
		newUser[i].password = newpass;

		newUser[i].studentProfile.active = true;

		fout << newUser[i].username << endl
		     << newUser[i].password << endl
			 << newUser[i].studentProfile.fullname << endl
			 << newUser[i].studentProfile.gender << endl
		     << newUser[i].studentProfile.birthDate.tm_year + 1900 << '-'
			 << newUser[i].studentProfile.birthDate.tm_mon + 1 << '-'
			 << newUser[i].studentProfile.birthDate.tm_mday << endl
			 << newUser[i].studentProfile.active << endl;
		fout << endl;
	}
	fout.close();
	delete[] newUser;
	newUser = nullptr;

	return true;
}