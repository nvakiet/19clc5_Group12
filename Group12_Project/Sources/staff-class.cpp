#include "../Headers/staff-class.h"

bool importClass() {
	string systemPath = "./TextFiles/", fileEx = "_Students.txt";
	cout << "Enter csv file path: ";

	ifstream fin;
	string path;
	cin >> path;
	flushin(cin);
	fin.open(path);

	int n;
	string DoB, sex, ClassID, line, No, lastname, firstname;
	cout << "Enter class ID: ";
	cin >> ClassID;
	flushin(cin);
	cout << "Enter number of students in the class: ";
	cin >> n;
	flushin(cin);

	Student* newStu;
	newStu = new Student[n];

	if (!fin.is_open()) {
		cerr << "Can't open data file in the path: " << path << endl;
		return false;
	}
	fin.ignore(INT_MAX, '\n');
	for (int i = 0; i < n; i++) {
		getline(fin, No, ';');
		getline(fin, newStu[i].ID, ';');
		getline(fin, lastname, ';');
		getline(fin, firstname, ';');
		newStu[i].fullname = lastname + " " + firstname;
		getline(fin, sex, ';');
		newStu[i].gender = sex.front();
		getline(fin, DoB);
		newStu[i].birthDate = sToDate(DoB);

	}
	fin.close();
	/*
	string path2 = "./TextFiles/Students.txt";
	fin.open(path2);

	if (!fin.is_open()) {
		cerr << "Can't open data file in the path: " << path2 << endl;
		if (generateFile(path2, "")) {
			cout << "A new file has been generated!" << endl;
			cout << "Some data may be lost. The program will continue." << endl;
			cout << endl;
			fin.clear();
			fin.open(path2);
		}
		else {
			cerr << "Failed to generate a new data file" << endl;
			return false;
		}
	}
	if (!emptyFile(path2)) {
		int n2;
		getline(fin, line);
		n2 = stoi(line);
		Account* user;
		user = new Account[n2];
		for (int i = 0; i < n2; i++) {
			getline(fin, user[i].username);
			fin.ignore(INT_MAX, '\n');
			fin.ignore(INT_MAX, '\n');
			fin.ignore(INT_MAX, '\n');
			fin.ignore(INT_MAX, '\n');
			fin.ignore(INT_MAX, '\n');
			fin.ignore(INT_MAX, '\n');
			fin.ignore(INT_MAX, '\n');
		}
		fin.close();

		ofstream fout;
		fout.open(path2, ios::app);
		if (!fout.is_open()) {
			cerr << "Cannot open file";
			return false;
		}
		fout << endl;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n2; j++) {
				if (newStu[i].ID == user[j].username)
					break;
				fout << newStu[i].ID << endl
					<< setfill('0') << right << newStu[i].birthDate.tm_year + 1900
					<< setw(2) << newStu[i].birthDate.tm_mon + 1
					<< setw(2) << newStu[i].birthDate.tm_mday << endl
					<< newStu[i].fullname << endl
					<< ClassID << endl
					<< newStu[i].gender << endl;
				printDate(fout, newStu[i].birthDate);
				fout << 1 << endl;
				fout << endl;
			}
		fout.close();
		delete[] user;
		user = nullptr;
	}
	*/
	string path3 = "./TextFiles/Classes.txt";
	fin.open(path3);
	if (!fin.is_open()) {
		cerr << "Can't open data file in the path: " << path3 << endl;
		if (generateFile(path3, "")) {
			cout << "A new file has been generated!" << endl;
			cout << "Some data may be lost. The program will continue." << endl;
			cout << endl;
			fin.clear();
			fin.open(path3);
		}
		else {
			cerr << "Failed to generate a new data file" << endl;
			return false;
		}
	}
	if (!emptyFile(path3)) {
		int n3;
		getline(fin, line);
		n3 = stoi(line);
		Class* classes;
		classes = new Class[n];
		for (int i = 0; i < n3; i++)
			getline(fin, classes[i].className);
		fin.close();

		for (int i = 0; i < n3; i++) {
			if (ClassID == classes[i].className) {
				int choice;
				cerr << "The class already existed. Overwrite?" << endl
					<< "1.Yes" << endl
					<< "0.No" << endl;
				cin >> choice;
				while (!cin || choice < 0 || choice > 1) {
					flushin(cin);
					cerr << "Invalid input!" << endl;
					cout << "--> ENTER A NUMBER FOR YOUR CHOICE: ";
					cin >> choice;
				}
				if (choice == 1) {
					ofstream fout;
					fout.open(systemPath + ClassID + "_Students.txt");
					if (!fout.is_open()) {
						cerr << "Cannot open file";
						return false;
					}
					fout << n << endl;
					for (int i = 0; i < n; i++) {
						fout << newStu[i].ID << endl
							<< setfill('0') << right << newStu[i].birthDate.tm_year + 1900
							<< setw(2) << newStu[i].birthDate.tm_mon + 1
							<< setw(2) << newStu[i].birthDate.tm_mday << endl
							<< newStu[i].fullname << endl
							<< ClassID << endl
							<< newStu[i].gender << endl;
						printDate(fout, newStu[i].birthDate);
						fout << 1 << endl;
						fout << endl;
					}
					fout.close();
					return true;
				}
				if (choice == 0) {
					cerr << "Import cancelled";
					return false;
				}
			}
			ofstream fout;
			fout.open(systemPath + ClassID + "_Students.txt", ios::app);
			if (!fout.is_open()) {
				cerr << "Cannot open file";
				return false;
			}
			fout << n << endl;
			for (int i = 0; i < n; i++) {
				fout << newStu[i].ID << endl
					<< setfill('0') << right << newStu[i].birthDate.tm_year + 1900
					<< setw(2) << newStu[i].birthDate.tm_mon + 1
					<< setw(2) << newStu[i].birthDate.tm_mday << endl
					<< newStu[i].fullname << endl
					<< ClassID << endl
					<< newStu[i].gender << endl;
				printDate(fout, newStu[i].birthDate);
				fout << 1 << endl;
				fout << endl;
			}
			fout.close();
		}
	}
	delete[] newStu;
	newStu = nullptr;
	return true;
}