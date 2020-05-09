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
bool addStudent() {
	string systemPath = "./TextFiles/", fileEx = "_Students.txt";
	ifstream fin;
	ofstream fout;
	string ClassID, line, DoB;

	Student* newStu = new Student;

	cout << "Enter ID of the class: ";
	getline(cin, ClassID);
	cout << "Enter student ID: ";
	getline(cin, newStu->ID);
	cout << "Enter student fullname: ";
	getline(cin, newStu->fullname);
	cout << "Enter student gender: ";
	getline(cin, line);
	newStu->gender = line.front();
	cout << "Enter student birthdate: ";
	getline(cin, line);
	newStu->birthDate = sToDate(line);
	//tao acc moi
	//string path1 = "./TextFiles/Students.txt";
	string path1 = "./TextFiles/Test-student.txt";
	//neu chua co file
	if (emptyFile(path1)) {
		fout.open(path1);
		if (!fout.is_open()) {
			cerr << "Cannot open file " << path1;
			return false;
		}
		fout << 1 << endl;
		fout << newStu->ID << endl;
		char temp[9];
		strftime(temp, 9, "%Y%m%d", &newStu->birthDate);
		DoB.assign(temp);
		fout << sha256(DoB) << endl
			<< newStu->fullname << endl
			<< ClassID << endl
			<< newStu->gender << endl;
		printDate(fout, newStu->birthDate);
		fout << 1 << endl;
		fout << endl;
		fout.close();
	}
	else //neu co file
	{
		fin.open(path1);
		if (!fout.is_open()) {
			cerr << "Cannot open file " << path1;
			return false;
		}
		int n1;
		getline(fin, line);
		n1 = stoi(line);
		Account* oldStu;
		oldStu = new Account[n1];

		for (int i = 0; i < n1; i++) {
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

		bool flag1 = false;
		for (int i = 0; i < n1; i++) {
			if (newStu->ID == oldStu[i].username)
				flag1 = true;
		}
		fout.open(path1);
		if (!fout.is_open()) {
			cerr << "Cannot open file " << path1;
			return false;
		}
		fout << n1 + 1 << endl;
		for (int j = 0; j < n1; j++) {
			fout << oldStu[j].username << endl
				<< oldStu[j].password << endl
				<< oldStu[j].studentProfile.fullname << endl
				<< oldStu[j].studentProfile.classID << endl
				<< oldStu[j].studentProfile.gender << endl;
			printDate(fout, oldStu[j].studentProfile.birthDate);
			fout << oldStu[j].studentProfile.active << endl;
			fout << endl;
		}
		if (!flag1) {
			fout << newStu->ID << endl;
			char temp[9];
			strftime(temp, 9, "%Y%m%d", &newStu->birthDate);
			DoB.assign(temp);
			fout << sha256(DoB) << endl
				<< newStu->fullname << endl
				<< ClassID << endl
				<< newStu->gender << endl;
			printDate(fout, newStu->birthDate);
			fout << 1 << endl;
			fout << endl;
		}
		fout.close();
		delete[] oldStu;
		oldStu = nullptr;
	}
	//add vo file classes
	string path2 = "./TextFiles/Classes.txt";
	bool flag2 = false;
	if (emptyFile(path2)) {
		fout.open(path2);
		if (!fout.is_open()) {
			cerr << "Cannot open file " << path2;
			return false;
		}
		fout << 1 << endl
			<< ClassID << endl;
		fout.close();
	}
	else {
		int n2;
		fin.open(path2);
		if (!fin.is_open()) {
			cerr << "Cannot open file " << path2;
			return false;
		}
		getline(fin, line);
		n2 = stoi(line);

		Class* classes;
		classes = new Class[n2];

		for (int i = 0; i < n2; i++)
			getline(fin, classes[i].className);
		fin.close();

		for (int i = 0; i < n2; i++) {
			if (ClassID == classes[i].className)
				flag2 = true;
		}
		//chua co class 
		if (flag2 == false) {
			fout.open(path2);
			if (!fout.is_open()) {
				cerr << "Cannot open file " << path2;
				return false;
			}
			fout << n2 + 1 << endl;
			for (int i = 0; i < n2; i++)
				fout << classes[i].className << endl;
			fout << ClassID << endl;
			fout.close();
		}
		delete[] classes;
		classes = nullptr;
		//co class
		if (flag2 == true) {
			//string path3 = systemPath + ClassID + "_Students.txt";
			string path3 = "./TextFiles/Test-19CLC5.txt";
			fin.open(path3);
			if (!fin.is_open()) {
				cerr << "Cannot open file " << path3;
				return false;
			}
			int n3;
			getline(fin, line);
			n3 = stoi(line);
			Student* oldStu = new Student[n3];

			for (int i = 0; i < n3; i++) {
				getline(fin, oldStu[i].ID);
				getline(fin, oldStu[i].fullname);
				getline(fin, line);
				oldStu[i].gender = line.front();
				getline(fin, line);
				oldStu[i].birthDate = sToDate(line);
				getline(fin, line);
				oldStu[i].active = stoi(line);
				fin.ignore(INT_MAX, '\n');
			}
			fin.close();

			fout.open(path3);
			if (!fout.is_open()) {
				cerr << "Cannot open file " << path3;
				return false;
			}
			fout << n3 + 1 << endl;
			for (int i = 0; i < n3; i++) {
				fout << oldStu[i].ID << endl
					<< oldStu[i].fullname << endl
					<< oldStu[i].gender << endl;
				printDate(fout, oldStu[i].birthDate);
				fout << oldStu[i].active << endl;
				fout << endl;
			}
			fout << newStu->ID << endl
				<< newStu->fullname << endl
				<< newStu->gender << endl;
			printDate(fout, newStu->birthDate);
			fout << 1 << endl;
			fout << endl;

			fout.close();
			delete[] oldStu;
			oldStu = nullptr;
		}
	}
	delete newStu;
	newStu = nullptr;
	return true;
}
bool removeStudent() {
	string systemPath = "./TextFiles/", fileEx = "_Students.txt";
	ifstream fin;
	ofstream fout;
	string ClassID, ID, line, DoB;

	cout << "Enter classID: ";
	getline(cin, ClassID);
	cout << "Enter student ID: ";
	getline(cin, ID);
	// in danh sach ma lop
	//string path1 = systemPath + ClassID + "_Students.txt";
	string path1 = "./TextFiles/Test-19CLC5.txt";
	fin.open(path1);
	if (!fin.is_open()) {
		cerr << "Cannot open file " << path1;
		return false;
	}
	int n1;
	getline(fin, line);
	n1 = stoi(line);
	Student* oldStu = new Student[n1];

	for (int i = 0; i < n1; i++) {
		getline(fin, oldStu[i].ID);
		getline(fin, oldStu[i].fullname);
		getline(fin, line);
		oldStu[i].gender = line.front();
		getline(fin, line);
		oldStu[i].birthDate = sToDate(line);
		getline(fin, line);
		oldStu[i].active = stoi(line);
		fin.ignore(INT_MAX, '\n');
	}
	fin.close();

	bool* flag1 = new bool[n1] {false};
	for (int i = 0; i < n1 && flag1[i] == false; i++) {
		if (ID == oldStu[i].ID)
			flag1[i] = true;
		else flag1[i] = false;
	}
	fout.open(path1);
	if (!fout.is_open()) {
		cerr << "Cannot open file " << path1;
		return false;
	}
	fout << n1 - 1 << endl;
	for (int i = 0; i < n1; i++) {
		if (!flag1[i]) {
			fout << oldStu[i].ID << endl
				<< oldStu[i].fullname << endl
				<< oldStu[i].gender << endl;
			printDate(fout, oldStu[i].birthDate);
			fout << oldStu[i].active << endl;
			fout << endl;
		}
	}
	fout.close();
	delete[] flag1;
	flag1 = nullptr;
	delete[] oldStu;
	oldStu = nullptr;

	//string path2 = "./TextFiles/Students.txt";
	string path2 = "./TextFiles/Test-student.txt";
	fin.open(path2);
	if (!fin.is_open()) {
		cerr << "Cannot open file " << path2;
		return false;
	}
	int n2;
	getline(fin, line);
	n2 = stoi(line);
	Account* oldAcc = new Account[n2];

	for (int i = 0; i < n2; i++) {
		getline(fin, oldAcc[i].username);
		getline(fin, oldAcc[i].password);
		getline(fin, oldAcc[i].studentProfile.fullname);
		getline(fin, oldAcc[i].studentProfile.classID);
		getline(fin, line);
		oldAcc[i].studentProfile.gender = line.front();
		getline(fin, line);
		oldAcc[i].studentProfile.birthDate = sToDate(line);
		getline(fin, line);
		oldAcc[i].studentProfile.active = stoi(line);
		fin.ignore(INT_MAX, '\n');
	}
	fin.close();

	bool* flag2 = new bool[n2] {false};
	for (int i = 0; i < n2 && flag2[i] == false; i++) {
		if (ID == oldAcc[i].username)
			flag2[i] = true;
		else flag2[i] = false;
	}
	fout.open(path2);
	if (!fout.is_open()) {
		cerr << "Cannot open file " << path2;
		return false;
	}
	fout << n2 - 1 << endl;
	for (int i = 0; i < n2; i++) {
		if (!flag2[i]) {
			fout << oldAcc[i].username << endl
				<< oldAcc[i].password << endl
				<< oldAcc[i].studentProfile.fullname << endl
				<< oldAcc[i].studentProfile.classID << endl
				<< oldAcc[i].studentProfile.gender << endl;
			printDate(fout, oldAcc[i].studentProfile.birthDate);
			fout << oldAcc[i].studentProfile.active << endl;
			fout << endl;
		}
	}
	fout.close();
	delete[] flag2;
	flag2 = nullptr;
	delete[] oldAcc;
	oldAcc = nullptr;
	return true;
}
bool editStudent() {
	string systemPath = "./TextFiles/", fileEx = "_Students.txt";
	ifstream fin;
	ofstream fout;
	string ClassID, ID, line, DoB, newID, newName, newGender, newDoB, newActive;

	cout << "Enter student ID: ";
	getline(cin, ID);
	cout << "Enter class ID: ";
	getline(cin, ClassID);

	//string path1 = "./TextFiles/Students.txt";
	string path1 = "./TextFiles/Test-student.txt";
	fin.open(path1);

	if (!fin.is_open()) {
		cerr << "Cannot open file " << path1;
		return false;
	}
	int n1;
	getline(fin, line);
	n1 = stoi(line);
	Account* oldStu = new Account[n1];

	for (int i = 0; i < n1; i++) {
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

	bool* flag1 = new bool[n1] { false };
	for (int i = 0; i < n1; i++) {
		if (ID == oldStu[i].username)
			flag1[i] = true;
		else flag1[i] = false;
	}
	for (int i = 0; i < n1; i++) {
		if (flag1[i] == true) {
			cout << "Student ID: " << oldStu[i].username << endl;
			cout << "Fullname: " << oldStu[i].studentProfile.fullname << endl;
			cout << "Class ID: " << oldStu[i].studentProfile.classID << endl;
			cout << "Gender: " << oldStu[i].studentProfile.gender << endl;
			cout << "BirthDate: "
				<< setfill('0') << right << oldStu[i].studentProfile.birthDate.tm_year + 1900 << '-'
				<< setw(2) << oldStu[i].studentProfile.birthDate.tm_mon + 1 << '-'
				<< setw(2) << oldStu[i].studentProfile.birthDate.tm_mday << endl;
			cout << "Active: " << oldStu[i].studentProfile.active << endl << endl;
			cout << "Enter new data" << endl;
			cout << "Student ID: ";
			getline(cin, oldStu[i].username);
			newID = oldStu[i].username;
			cout << "Fullname: ";
			getline(cin, oldStu[i].studentProfile.fullname);
			newName = oldStu[i].studentProfile.fullname;
			cout << "Gender: ";
			getline(cin, line);
			newGender = line.front();
			oldStu[i].studentProfile.gender = line.front();
			cout << "BirthDate: ";
			getline(cin, line);
			newDoB = line;
			oldStu[i].studentProfile.birthDate = sToDate(line);
			cout << "Active: ";
			getline(cin, line);
			newActive = line;
			oldStu[i].studentProfile.active = stoi(line);
		}
	}
	fout.open(path1);
	if (!fout.is_open()) {
		cerr << "Cannot open file " << path1;
		return false;
	}
	fout << n1 << endl;
	for (int i = 0; i < n1; i++) {
		fout << oldStu[i].username << endl
			<< oldStu[i].password << endl
			<< oldStu[i].studentProfile.fullname << endl
			<< oldStu[i].studentProfile.classID << endl
			<< oldStu[i].studentProfile.gender << endl;
		printDate(fout, oldStu[i].studentProfile.birthDate);
		fout << oldStu[i].studentProfile.active << endl;
		fout << endl;
	}
	fout.close();
	delete[] oldStu;
	oldStu = nullptr;

	//string path2 = systemPath + ClassID + "_Students.txt";
	string path2 = "./TextFiles/Test-19CLC5.txt";
	fin.open(path2);
	if (!fin.is_open()) {
		cerr << "Cannot open file " << path2;
		return false;
	}
	int n2;
	getline(fin, line);
	n2 = stoi(line);
	Student* students = new Student[n2];

	for (int i = 0; i < n2; i++) {
		getline(fin, students[i].ID);
		getline(fin, students[i].fullname);
		getline(fin, line);
		students[i].gender = line.front();
		getline(fin, line);
		students[i].birthDate = sToDate(line);
		getline(fin, line);
		students[i].active = stoi(line);
		fin.ignore(INT_MAX, '\n');
	}
	fin.close();


	fout.open(path2);
	if (!fout.is_open()) {
		cerr << "Cannot open file " << path2;
		return false;
	}
	fout << n2 << endl;
	bool* flag2 = new bool[n2] { false };
	for (int i = 0; i < n2; i++) {
		if (ID == students[i].ID)
			flag2[i] = true;
		else flag2[i] = false;
	}
	for (int i = 0; i < n2; i++) {
		if (flag2[i]) {
			fout << newID << endl
				<< newName << endl
				<< newGender << endl
				<< newDoB << endl
				<< newActive << endl;
			fout << endl;
		}
		else {
			fout << students[i].ID << endl
				<< students[i].fullname << endl
				<< students[i].gender << endl;
			printDate(fout, students[i].birthDate);
			fout << students[i].active << endl;
			fout << endl;
		}
	}
	fout.close();

	delete[] students;
	students = nullptr;
	delete[] flag1;
	flag1 = nullptr;
	return true;
}