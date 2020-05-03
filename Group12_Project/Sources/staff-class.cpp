#include "../Headers/staff-class.h"

bool importClass() {
	string systemPath = "./TextFiles/", fileEx = "_Students.txt";
	ifstream fin;
	ofstream fout;
	int n;
	string path, DoB, sex, ClassID, line, lastname, firstname;
	cout << "Enter csv file path: ";
	cin >> path;
	flushin(cin);
	fin.open(path);
	cout << "Enter class ID: ";
	cin >> ClassID;
	flushin(cin);
	cout << "Enter number of students in the class: ";
	cin >> n;
	flushin(cin);

	Student* newStu;
	newStu = new Student[n];
	//Read the csv
	if (!fin.is_open()) {
		cerr << "Can't open data file in the path: " << path << endl;
		return false;
	}
	fin.ignore(INT_MAX, '\n');
	for (int i = 0; i < n; i++) {
		fin.ignore(INT_MAX, ';');
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

	//Register students
	string path2 = "./TextFiles/Students.txt";
	//Case 1: if Students.txt is empty, paste all students to the file
	if (emptyFile(path2)) {
		fout.open(path2);
		if (!fout.is_open()) {
			cerr << "Cannot open file";
			return false;
		}
		fout << n << endl;
		for (int i = 0; i < n; i++) {
			fout << newStu[i].ID << endl;
			char temp[9];
			strftime(temp, 9, "%Y%m%d", &newStu[i].birthDate);
			DoB.assign(temp);
			fout << sha256(DoB) << endl
				<< newStu[i].fullname << endl
				<< ClassID << endl
				<< newStu[i].gender << endl;
			printDate(fout, newStu[i].birthDate);
			fout << 1 << endl;
			fout << endl;
		}
		fout.close();
	}
	//Case 2: if not
	else {
		//Load the Students.txt file to an account array
		fin.open(path2);
		int n2;
		getline(fin, line);
		n2 = stoi(line);
		Account* oldStu;
		oldStu = new Account[n2];
		for (int i = 0; i < n2; i++) {
			getline(fin, oldStu[i].username);
			getline(fin, oldStu[i].password);
			getline(fin, oldStu[i].studentProfile.fullname);
			getline(fin, oldStu[i].studentProfile.classID);
			getline(fin, line);
			oldStu[i].studentProfile.gender = line.front();
			getline(fin, line);
			oldStu[i].studentProfile.birthDate = sToDate(line);
			getline(fin, line);
			oldStu[i].studentProfile.active = stoi(line);
			fin.ignore(INT_MAX, '\n');
		}
		fin.close();

		//Get new number of student accounts and check whether a student is already registered
		int newN2 = n2 + n;
		bool* sameStudent = new bool[n] {false};
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n2 && sameStudent[i] == false; j++) {
				if (newStu[i].ID == oldStu[j].username) {
					sameStudent[i] = true;
					newN2--;
				}
				else sameStudent[i] = false;
			}
		}

		//Save old accounts and new unique accounts to the file
		fout.open(path2);
		if (!fout.is_open()) {
			cerr << "Cannot open file";
			return false;
		}
		fout << newN2 << endl;
		for (int j = 0; j < n2; j++) {
			//Save old accounts
			fout << oldStu[j].username << endl
				<< oldStu[j].password << endl
				<< oldStu[j].studentProfile.fullname << endl
				<< oldStu[j].studentProfile.classID << endl
				<< oldStu[j].studentProfile.gender << endl;
			printDate(fout, oldStu[j].studentProfile.birthDate);
			fout << oldStu[j].studentProfile.active << endl;
			fout << endl;
		}
		for (int i = 0; i < n; i++) {
			//Save new accounts if student is not the same
			if (!sameStudent[i]){
				fout << newStu[i].ID << endl;
				char temp[9];
				strftime(temp, 9, "%Y%m%d", &newStu[i].birthDate);
				DoB.assign(temp);
				fout << sha256(DoB) << endl
				<<	newStu[i].fullname << endl
				<< ClassID << endl
				<< newStu[i].gender << endl;
			printDate(fout, newStu[i].birthDate);
			fout << 1 << endl;
			fout << endl;
			}
		}
		fout.close();
		delete[] oldStu;
		delete[] sameStudent;
		oldStu = nullptr;
		sameStudent = nullptr;
	}

	//Update Classes.txt
	string path3 = "./TextFiles/Classes.txt";
	bool flag = false; //Flag to check if the class already existed
	if (emptyFile(path3)) {
		fout.open(path3);
		if (!fout.is_open()) {
			cerr << "Cannot open file";
			return false;
		}
		fout << 1 << endl
			<< ClassID << endl;
		fout.close();
	}
	else {
		int n3;
		fin.open(path3);
		getline(fin, line);
		n3 = stoi(line);
		Class* classes;
		classes = new Class[n3];
		for (int i = 0; i < n3; i++)
			getline(fin, classes[i].className);
		fin.close();

		//Check if the same classID
		for (int i = 0; i < n3 && flag == false; i++) {
			if (ClassID == classes[i].className)
				flag = true;
		}
		//If not the same classID, update to Classes.txt
		if (flag == false) {
			fout.open(path3);
			fout << n3 + 1 << endl;
			for (int i = 0; i < n3; i++)
				fout << classes[i].className << endl;
			fout << ClassID << endl;
			fout.close();
		}
		delete[] classes;
		classes = nullptr;
	}

	//Import the student array to a txt file
	//Case 1: If the class already existed
	if (flag == true) {
		int choice;
		cerr << "The class already existed. Overwrite?" << endl
			<< "1.Yes" << endl
			<< "0.No" << endl;
		cout << "Enter 1 or 0: ";
		cin >> choice;
		while (!cin || choice < 0 || choice > 1) {
			flushin(cin);
			cerr << "Invalid input!" << endl;
			cout << "--> ENTER A NUMBER FOR YOUR CHOICE: ";
			cin >> choice;
		}
		flushin(cin);
		if (choice == 1) {
			fout.open(systemPath + ClassID + "_Students.txt");
			if (!fout.is_open()) {
				cerr << "Cannot open file" << endl;
				return false;
			}
			fout << n << endl;
			for (int i = 0; i < n; i++) {
				fout << newStu[i].ID << endl
					<< newStu[i].fullname << endl
					<< newStu[i].gender << endl;
				printDate(fout, newStu[i].birthDate);
				fout << 1 << endl;
				fout << endl;
			}
			fout.close();
			return true;
		}
		if (choice == 0) {
			cerr << "Import stopped!" << endl;
			return false;
		}
	}
	//If the class is new
	if (flag == false) {
		fout.open(systemPath + ClassID + "_Students.txt");
		if (!fout.is_open()) {
			cerr << "Cannot open file" << endl;
			return false;
		}
		fout << n << endl;
		for (int i = 0; i < n; i++) {
			fout << newStu[i].ID << endl
				<< newStu[i].fullname << endl
				<< newStu[i].gender << endl;
			printDate(fout, newStu[i].birthDate);
			fout << 1 << endl;
			fout << endl;
		}
		fout.close();
		return true;
	}
	delete[] newStu;
	newStu = nullptr;
	return true;
}