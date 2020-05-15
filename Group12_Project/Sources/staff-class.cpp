#include "../Headers/staff-class.h"
bool importClass() {
	string systemPath = "./TextFiles/", fileEx = "_Students.txt";
	ifstream fin;
	ofstream fout;
	int n;
	string path, DoB, sex, ClassID, line, lastname, firstname;
	cout << "Enter csv file path (or ./TextFiles/\"Filename\".csv if the file is in TextFiles folder): ";
	cin >> path;
	flushin(cin);
	fin.open(path);
	viewClasses();
	cout << "Enter new class ID: ";
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
		string* classes = readClassesID(path3, &n3);
		//Check if the same classID
		for (int i = 0; i < n3 && flag == false; i++) {
			if (ClassID == classes[i])
				flag = true;
		}
		//If not the same classID, update to Classes.txt
		if (flag == false) {
			fout.open(path3);
			fout << n3 + 1 << endl;
			for (int i = 0; i < n3; i++)
				fout << classes[i] << endl;
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
	int choice;

	Student newStu;
	string path = "./TextFiles/Classes.txt";
	if (!viewClasses()) return false;
	cout << "Enter ID of the class: ";
	getline(cin, ClassID);
	int n;
	string* classesID = readClassesID(path, &n);
	bool flag = false;
	for (int i = 0; i < n && flag == false; i++) {
		if (ClassID == classesID[i])
			flag = true;
	}
	if (!flag) {
		cout << "Class does not exist, create new? Choose 1 or 0:" << endl;
		cout << "1.Yes" << endl;
		cout << "0.No" << endl;
		cin >> choice;
		while (!cin || choice < 0 || choice > 1) {
			flushin(cin);
			cerr << "Invalid input!" << endl;
			cout << "--> ENTER A NUMBER FOR YOUR CHOICE: ";
			cin >> choice;
		}
		flushin(cin);
		if (choice == 0) {
			cout << "Cancelled" << endl;
			return false;
		}
		if (choice == 1) {
			fout.open(path);
			if (!fout.is_open()) {
				cerr << "Cannot open file " << path;
				delete[] classesID;
				return false;
			}
			fout << n + 1 << endl;
			for (int i = 0; i < n; i++)
				fout << classesID[i] << endl;
			fout << ClassID << endl;
			fout.close();
			delete[] classesID;
		}
	}
	cout << "Enter student ID: ";
	getline(cin, newStu.ID);
	cout << "Enter student fullname: ";
	getline(cin, newStu.fullname);
	cout << "Enter student gender (Male/Female): ";
	getline(cin, line);
	newStu.gender = line.front();
	cout << "Enter student birthdate (YYYY-MM-DD): ";
	cin >> get_time(&newStu.birthDate, "%Y-%m-%d");
	if (!cin) {
		cerr << "Invalid input." << endl;
		flushin(cin);
		cout << "BirthDate (YYYY-MM-DD): ";
		cin >> get_time(&newStu.birthDate, "%Y-%m-%d");
	}
	flushin(cin);
	//tao acc moi
	string path1 = "./TextFiles/Students.txt";
	//neu chua co file
	if (emptyFile(path1)) {
		fout.open(path1);
		if (!fout.is_open()) {
			cerr << "Cannot open file " << path1;
			return false;
		}
		fout << 1 << endl;
		fout << newStu.ID << endl;
		char temp[9];
		strftime(temp, 9, "%Y%m%d", &newStu.birthDate);
		DoB.assign(temp);
		fout << sha256(DoB) << endl
			<< newStu.fullname << endl
			<< ClassID << endl
			<< newStu.gender << endl;
		printDate(fout, newStu.birthDate);
		fout << 1 << endl;
		fout << endl;
		fout.close();
	}
	else //neu co file
	{
		fin.open(path1);
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
		for (int i = 0; i < n1 && flag1 == false; i++) {
			if (newStu.ID == oldStu[i].username)
				flag1 = true;
		}
		fout.open(path1);
		if (!fout.is_open()) {
			cerr << "Cannot open file " << path1;
			delete[] oldStu;
			oldStu = nullptr;
			return false;
		}
		if (!flag1) fout << n1 + 1 << endl;
		else fout << n1 << endl;
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
			fout << newStu.ID << endl;
			char temp[9];
			strftime(temp, 9, "%Y%m%d", &newStu.birthDate);
			DoB.assign(temp);
			fout << sha256(DoB) << endl
				<< newStu.fullname << endl
				<< ClassID << endl
				<< newStu.gender << endl;
			printDate(fout, newStu.birthDate);
			fout << 1 << endl;
			fout << endl;
		}
		fout.close();
		delete[] oldStu;
		oldStu = nullptr;
	}
	//Add vao danh sach sv cua class
	string path2 = systemPath + ClassID + "_Students.txt";
	if (emptyFile(path2)) {
		fout.open(path2);
		if (!fout.is_open()) {
			cerr << "Cannot open file " << path2;
			return false;
		}
		fout << 1 << endl;
		fout << newStu.ID << endl
			<< newStu.fullname << endl
			<< newStu.gender << endl;
		printDate(fout, newStu.birthDate);
		fout << 1 << endl;
		fout << endl;
		fout.close();
	}
	else {
		fin.open(path2);
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

		fout.open(path2);
		if (!fout.is_open()) {
			cerr << "Cannot open file " << path2;
			delete[] oldStu;
			oldStu = nullptr;
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
		fout << newStu.ID << endl
			<< newStu.fullname << endl
			<< newStu.gender << endl;
		printDate(fout, newStu.birthDate);
		fout << 1 << endl;
		fout << endl;
		fout.close();
		delete[] oldStu;
		oldStu = nullptr;
	}
	return true;
}
bool removeStudent() {
	string systemPath = "./TextFiles/", fileEx = "_Students.txt";
	ifstream fin;
	ofstream fout;
	string ClassID, ID, line, DoB;
	if (!viewClasses()) return false;
	int n;
	string* classes = readClassesID("./TextFiles/Classes.txt", &n);
	cout << "Enter class ID: ";
	getline(cin, ClassID);
	bool flag = false;
	for (int i = 0; i < n && flag == false; i++) {
		if (ClassID == classes[i])
			flag = true;
	}
	while (!flag) {
		cout << "Enter existing class: ";
		getline(cin, ClassID);
		for (int i = 0; i < n && flag == false; i++) {
			if (ClassID == classes[i])
				flag = true;
		}
	}
	delete[] classes;
	classes = nullptr;
	cout << "Enter student ID: ";
	getline(cin, ID);

	string path1 = systemPath + ClassID + "_Students.txt";
	fin.open(path1);
	if (emptyFile(path1)) {
		cerr << "Can't read student data in this class!" << endl;
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

	//Kt ID co ton tai ko
	bool flag1 = false;
	for (int i = 0; i < n1 && flag1 == false; i++) {
		if (ID == oldStu[i].ID)
			flag1 = true;
	}
	if (flag1 == false) {
		cerr << "ID does not exist" << endl;
		delete[] oldStu;
		oldStu = nullptr;
		return false;
	}
	if (n1 == 1) generateFile(path1, "");
	else {
		fout.open(path1);
		if (!fout.is_open()) {
			cerr << "Cannot open file " << path1;
			delete[] oldStu;
			oldStu = nullptr;
			return false;
		}
		fout << n1 - 1 << endl;
		for (int i = 0; i < n1; i++) {
			if (ID != oldStu[i].ID) {
				fout << oldStu[i].ID << endl
					<< oldStu[i].fullname << endl
					<< oldStu[i].gender << endl;
				printDate(fout, oldStu[i].birthDate);
				fout << oldStu[i].active << endl;
				fout << endl;
			}
		}
	}
	fout.close();
	delete[] oldStu;
	oldStu = nullptr;

	string path2 = "./TextFiles/Students.txt";
	fin.open(path2);
	if (emptyFile(path2)) {
		cerr << "Cannot read students data from Students.txt" << endl;
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

	//KT ID co trong file ko
	bool flag2 = false;
	for (int i = 0; i < n2 && flag2 == false; i++) {
		if (ID == oldAcc[i].username)
			flag2 = true;
	}
	if (flag2 == false) {
		cerr << "ID does not exist in Students.txt" << endl;
		delete[] oldAcc;
		oldAcc = nullptr;
		return false;
	}
	if (n2 == 1) generateFile(path2, "");
	else {
		fout.open(path2);
		if (!fout.is_open()) {
			cerr << "Cannot open Students.txt" << endl;
			delete[] oldAcc;
			oldAcc = nullptr;
			return false;
		}
		fout << n2 - 1 << endl;
		for (int i = 0; i < n2; i++) {
			if (ID != oldAcc[i].username) {
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
	}
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

	string path1 = "./TextFiles/Students.txt";
	fin.open(path1);
	if (emptyFile(path1)) {
		cerr << "Cannot read students data from Students.txt" << endl;
		return false;
	}
	int n1;
	getline(fin, line);
	n1 = stoi(line);
	Account* oldAcc = new Account[n1];
	for (int i = 0; i < n1; i++) {
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

	//KT ID co trong file ko
	bool flag1 = false;
	for (int i = 0; i < n1 && flag1 == false; i++) {
		if (ID == oldAcc[i].username)
			flag1 = true;
	}
	if (flag1 == false) {
		cerr << "ID does not exist in Students.txt" << endl;
		delete[] oldAcc;
		oldAcc = nullptr;
		return false;
	}
	for (int i = 0; i < n1; i++) {
		if (ID == oldAcc[i].username) {
			cout << "Student ID: " << oldAcc[i].username << endl;
			cout << "Fullname: " << oldAcc[i].studentProfile.fullname << endl;
			cout << "Class ID: " << oldAcc[i].studentProfile.classID << endl;
			ClassID = oldAcc[i].studentProfile.classID;
			cout << "Gender: " << oldAcc[i].studentProfile.gender << endl;
			cout << "BirthDate: ";
			printDate(cout, oldAcc[i].studentProfile.birthDate);
			cout << "Active: " << oldAcc[i].studentProfile.active << endl;
			cout << endl;
			cout << "Enter new data" << endl;
			cout << "- Student ID: ";
			getline(cin, oldAcc[i].username);
			newID = oldAcc[i].username;
			cout << "- Fullname: ";
			getline(cin, oldAcc[i].studentProfile.fullname);
			newName = oldAcc[i].studentProfile.fullname;
			cout << "- Gender(Male/Female): ";
			getline(cin, line);
			newGender = line.front();
			oldAcc[i].studentProfile.gender = line.front();
			cout << "- BirthDate (YYYY-MM-DD): ";
			cin >> get_time(&oldAcc[i].studentProfile.birthDate, "%Y-%m-%d");
			if (!cin) {
				cerr << "Invalid input." << endl;
				flushin(cin);
				cout << "- BirthDate (YYYY-MM-DD): ";
				cin >> get_time(&oldAcc[i].studentProfile.birthDate, "%Y-%m-%d");
			}
			flushin(cin);
			char temp[11];
			strftime(temp, 11, "%Y-%m-%d", &oldAcc[i].studentProfile.birthDate);
			newDoB.assign(temp);
			cout << "- Active (0 = Inactive/1 = Active): ";
			getline(cin, line);
			newActive = line;
			oldAcc[i].studentProfile.active = stoi(line);
			cout << "Do you want to reset the student's account password to default? (1. Yes/0. No)" << endl;
			cout << "Enter a number for your choice: ";
			int c;
			cin >> c;
			if (!cin || c < 0 || c > 1) {
				cerr << "Invalid input." << endl;
				flushin(cin);
				cout << "Enter a number for your choice: ";
				cin >> c;
			}
			flushin(cin);
			if (c == 1) {
				strftime(temp, 9, "%Y%m%d", &oldAcc[i].studentProfile.birthDate);
				oldAcc[i].password = sha256(temp);
				cout << "The student's account password has been reset to YYYYMMDD of their birthdate." << endl;
			}
			break;
		}
	}
	fout.open(path1);
	if (!fout.is_open()) {
		cerr << "Cannot open file " << path1;
		delete[] oldAcc;
		oldAcc = nullptr;
		return false;
	}
	fout << n1 << endl;
	for (int i = 0; i < n1; i++) {
		fout << oldAcc[i].username << endl
			<< oldAcc[i].password << endl
			<< oldAcc[i].studentProfile.fullname << endl
			<< oldAcc[i].studentProfile.classID << endl
			<< oldAcc[i].studentProfile.gender << endl;
		printDate(fout, oldAcc[i].studentProfile.birthDate);
		fout << oldAcc[i].studentProfile.active << endl;
		fout << endl;
	}
	fout.close();
	delete[] oldAcc;
	oldAcc = nullptr;

	string path2 = systemPath + ClassID + "_Students.txt";
	fin.open(path2);
	if (emptyFile(path2)) {
		cerr << "Can't read student data in this class!" << endl;
		return false;
	}
	int n2;
	getline(fin, line);
	n2 = stoi(line);
	Student* oldStu = new Student[n1];
	for (int i = 0; i < n2; i++) {
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

	//Kt ID co ton tai ko
	bool flag2 = false;
	for (int i = 0; i < n2 && flag2 == false; i++) {
		if (ID == oldStu[i].ID)
			flag2 = true;
	}
	if (flag2 == false) {
		cerr << "ID does not exist in this class" << endl;
		delete[] oldStu;
		oldStu = nullptr;
		return false;
	}
	fout.open(path2);
	if (!fout.is_open()) {
		cerr << "Cannot open file " << path2 << endl;
		delete[] oldStu;
		oldStu = nullptr;
		return false;
	}
	fout << n2 << endl;
	for (int i = 0; i < n2; i++) {
		if (ID == oldStu[i].ID) {
			fout << newID << endl
				<< newName << endl
				<< newGender << endl
				<< newDoB << endl
				<< newActive << endl;
			fout << endl;
		}
		else {
			fout << oldStu[i].ID << endl
				<< oldStu[i].fullname << endl
				<< oldStu[i].gender << endl;
			printDate(fout, oldStu[i].birthDate);
			fout << oldStu[i].active << endl;
			fout << endl;
		}
	}
	fout.close();
	delete[] oldStu;
	oldStu = nullptr;
	return true;
}
string* readClassesID(string path, int *nClasses = nullptr) {
	ifstream fin;
	ofstream fout;
	string line;
	fin.open(path);
	if (emptyFile(path)) return nullptr;
	int n;
	getline(fin, line);
	n = stoi(line);
	if (n == 0) return nullptr;
	string* classID = new string[n];
	for (int i = 0; i < n; i++) {
		getline(fin, classID[i]);
	}
	fin.close();
	if (nClasses != nullptr) *nClasses = n;
	return classID;
}
bool viewClasses() {
	ifstream fin;
	ofstream fout;
	string line;

	string path = "./TextFiles/Classes.txt";
	int n;
	string* classID = readClassesID(path, &n);
	if (classID == nullptr) {
		cerr << "Can't get data for list of classes from Classes.txt!" << endl;
		return false;
	}
	cout << "Available classes: " << endl;
	for (int i = 0; i < n; i++)
		cout << "- " << classID[i] << endl;

	delete[] classID;;
	return true;
}
bool viewStudentsInClass() {
	string systemPath = "./TextFiles/", fileEx = "_Students.txt";
	ifstream fin;
	ofstream fout;
	string ClassID, line, DoB;
	if (!viewClasses()) return false;
	cout << "Enter class ID: ";
	getline(cin, ClassID);
	string path = systemPath + ClassID + "_students.txt";
	/*string path = "./Textfiles/test-19clc5.txt";*/
	fin.open(path);
	if (!fin.is_open()) {
		cerr << "Cannot open file " << path;
		return false;
	}
	if (emptyFile(path)) return false;
	int n;
	getline(fin, line);
	n = stoi(line);
	if (n == 0) return false;
	Student* oldStu = new Student[n];

	for (int i = 0; i < n; i++) {
		getline(fin, oldStu[i].ID);
		getline(fin, oldStu[i].fullname);
		getline(fin, line);
		oldStu[i].gender = line.front();
		getline(fin, DoB);
		oldStu[i].birthDate = sToDate(DoB);
		getline(fin, line);
		oldStu[i].active = stoi(line);
		fin.ignore(INT_MAX, '\n');
	}
	fin.close();

	for (int i = 0; i < n; i++) {
		cout << oldStu[i].ID << endl
			<< oldStu[i].fullname << endl
			<< oldStu[i].gender << endl
			<< setfill('0') << right << oldStu[i].birthDate.tm_year + 1900 << '-'
			<< setw(2) << oldStu[i].birthDate.tm_mon + 1 << '-'
			<< setw(2) << oldStu[i].birthDate.tm_mday << endl
			<< oldStu[i].active << endl;
		cout << endl;
	}
	delete[] oldStu;
	oldStu = nullptr;
	return true;
}
bool changeClass() {
	string systemPath = "./TextFiles/", fileEx = "_Students.txt";
	ifstream fin;
	ofstream fout;
	string ClassID, ID, line, DoB, newClass;

	viewClasses();
	cout << "Enter class ID: ";
	getline(cin, ClassID);
	cout << "Enter new class ID: ";
	getline(cin, newClass);

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
	if (n1 == 0) return false;
	Student* oldStu1 = new Student[n1];

	for (int i = 0; i < n1; i++) {
		getline(fin, oldStu1[i].ID);
		getline(fin, oldStu1[i].fullname);
		getline(fin, line);
		oldStu1[i].gender = line.front();
		getline(fin, DoB);
		oldStu1[i].birthDate = sToDate(DoB);
		getline(fin, line);
		oldStu1[i].active = stoi(line);
		fin.ignore(INT_MAX, '\n');
	}
	fin.close();

	//string path2 = systemPath + ClassID + "_Students.txt";
	string path2 = "./TextFiles/Test-19CLC7.txt";
	fin.open(path2);
	if (!fin.is_open()) {
		cerr << "Cannot open file " << path2;
		return false;
	}
	int n2;
	getline(fin, line);
	n2 = stoi(line);
	if (n2 == 0) return false;
	Student* oldStu2 = new Student[n2];

	for (int i = 0; i < n2; i++) {
		getline(fin, oldStu2[i].ID);
		getline(fin, oldStu2[i].fullname);
		getline(fin, line);
		oldStu2[i].gender = line.front();
		getline(fin, DoB);
		oldStu2[i].birthDate = sToDate(DoB);
		getline(fin, line);
		oldStu2[i].active = stoi(line);
		fin.ignore(INT_MAX, '\n');
	}
	fin.close();

	fout.open(path2);
	if (!fout.is_open()) {
		cerr << "Cannot open file " << path2;
		return false;
	}
	fout << n1 << endl;
	for (int i = 0; i < n1; i++) {
		fout << oldStu1[i].ID << endl
			<< oldStu1[i].fullname << endl
			<< oldStu1[i].gender << endl;
		printDate(fout, oldStu1[i].birthDate);
		fout << oldStu1[i].active << endl;
		fout << endl;
	}
	fout.close();

	fout.open(path1);
	if (!fout.is_open()) {
		cerr << "Cannot open file " << path1;
		return false;
	}
	fout << n2 << endl;
	for (int i = 0; i < n2; i++) {
		fout << oldStu2[i].ID << endl
			<< oldStu2[i].fullname << endl
			<< oldStu2[i].gender << endl;
		printDate(fout, oldStu2[i].birthDate);
		fout << oldStu2[i].active << endl;
		fout << endl;
	}
	fout.close();

	delete[] oldStu1;
	oldStu1 = nullptr;
	delete[] oldStu2;
	oldStu2 = nullptr;
	return true;
}