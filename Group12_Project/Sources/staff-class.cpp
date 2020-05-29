#include "../Headers/staff-class.h"
bool importClass(cmpr orderStu, cmpr orderAcc) {
	string systemPath = "./TextFiles/", fileEx = "_Students.txt";
	ifstream fin;
	ofstream fout;
	int n;
	string path, DoB, sex, ClassID, line, lastname, firstname;
	cout << "Enter csv file path (or ./TextFiles/\"Filename\".csv if the file is in TextFiles folder): ";
	cin >> path;
	flushin(cin);
	viewClasses();
	cout << "Enter new class ID: ";
	cin >> ClassID;
	flushin(cin);
	//Get number of student in the csv file
	fin.open(path);
	if (!fin.is_open()) {
		cerr << "Can't open data file in the path: " << path << endl;
		return false;
	}
	fin.ignore(INT_MAX, '\n');
	while (getline(fin, line)) {
		n = stoi(line.substr(0, line.find_first_of(';', 0)));
	}
	fin.close();

	Student* newStu;
	newStu = new Student[n];
	//Read the csv
	fin.open(path);
	if (!fin.is_open()) {
		cerr << "Can't open data file in the path: " << path << endl;
		delete[] newStu;
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

	//Sort the student array
	sortStudent(newStu, 0, n - 1, orderStu);

	//Register students
	string path2 = "./TextFiles/Students.txt";
	//Case 1: if Students.txt is empty, paste all students to the file
	if (emptyFile(path2)) {
		fout.open(path2);
		if (!fout.is_open()) {
			cerr << "Cannot open file" << endl;
			delete[] newStu;
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
		Account* accStu;
		accStu = new Account[n2 + n];
		for (int i = 0; i < n2; i++) {
			getline(fin, accStu[i].username);
			getline(fin, accStu[i].password);
			getline(fin, accStu[i].studentProfile.fullname);
			getline(fin, accStu[i].studentProfile.classID);
			getline(fin, line);
			accStu[i].studentProfile.gender = line.front();
			getline(fin, line);
			accStu[i].studentProfile.birthDate = sToDate(line);
			getline(fin, line);
			accStu[i].studentProfile.active = stoi(line);
			fin.ignore(INT_MAX, '\n');
		}
		fin.close();

		//Get new number of student accounts and add new student accounts to the account array
		int newN2 = n2 + n;
		for (int i = 0; i < n; i++) {
			accStu[n2 + i].username = newStu[i].ID;
			char temp[9];
			strftime(temp, 9, "%Y%m%d", &newStu[i].birthDate);
			DoB.assign(temp);
			accStu[n2 + i].password = sha256(DoB);
			accStu[n2 + i].studentProfile.fullname = newStu[i].fullname;
			accStu[n2 + i].studentProfile.classID = ClassID;
			accStu[n2 + i].studentProfile.gender = newStu[i].gender;
			accStu[n2 + i].studentProfile.birthDate = newStu[i].birthDate;
			accStu[n2 + i].studentProfile.active = newStu[i].active;
		}

		//Sort the account array before output to file
		sortAccount(accStu, 0, newN2 - 1, orderAcc);

		//Save account array to the file
		fout.open(path2);
		if (!fout.is_open()) {
			cerr << "Cannot open file";
			delete[] accStu;
			delete[] newStu;
			return false;
		}
		fout << newN2 << endl;
		for (int j = 0; j < newN2; j++) {
			fout << accStu[j].username << endl
				<< accStu[j].password << endl
				<< accStu[j].studentProfile.fullname << endl
				<< accStu[j].studentProfile.classID << endl
				<< accStu[j].studentProfile.gender << endl;
			printDate(fout, accStu[j].studentProfile.birthDate);
			fout << accStu[j].studentProfile.active << endl;
			fout << endl;
		}
		fout.close();
		delete[] accStu;
		accStu = nullptr;
	}

	//Update Classes.txt
	string path3 = "./TextFiles/Classes.txt";
	bool flag = false; //Flag to check if the class already existed
	if (emptyFile(path3)) {
		fout.open(path3);
		if (!fout.is_open()) {
			cerr << "Cannot open file";
			delete[] newStu;
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
				delete[] newStu;
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
		}
		if (choice == 0) {
			cerr << "Import stopped!" << endl;
			delete[] newStu;
			return false;
		}
	}
	//If the class is new
	if (flag == false) {
		fout.open(systemPath + ClassID + "_Students.txt");
		if (!fout.is_open()) {
			cerr << "Cannot open file" << endl;
			delete[] newStu;
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
	}
	delete[] newStu;
	newStu = nullptr;
	return true;
}
bool addStudent(cmpr orderStu, cmpr orderAcc) {
	string systemPath = "./TextFiles/", fileEx = "_Students.txt";
	ifstream fin;
	ofstream fout;
	string line, DoB;
	int choice;

	Student newStu;
	string path = "./TextFiles/Classes.txt";
	if (!viewClasses()) return false;
	cout << "Enter ID of the class: ";
	getline(cin, newStu.classID);
	int n;
	string* classesID = readClassesID(path, &n);
	bool flag = false;
	for (int i = 0; i < n && flag == false; i++) {
		if (newStu.classID == classesID[i])
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
				cerr << "Cannot open file " << path << endl;
				delete[] classesID;
				return false;
			}
			fout << n + 1 << endl;
			for (int i = 0; i < n; i++)
				fout << classesID[i] << endl;
			fout << newStu.classID << endl;
			fout.close();
		}
	}
	delete[] classesID;
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
	//Create new account
	bool sameID = false;
	string path1 = "./TextFiles/Students.txt";
	if (emptyFile(path1)) {
		fout.open(path1);
		if (!fout.is_open()) {
			cerr << "Can't register student account!" << endl;
			return false;
		}
		fout << 1 << endl;
		fout << newStu.ID << endl;
		char temp[9];
		strftime(temp, 9, "%Y%m%d", &newStu.birthDate);
		line.assign(temp);
		fout << sha256(line) << endl
			<< newStu.fullname << endl
			<< newStu.classID << endl
			<< newStu.gender << endl;
		printDate(fout, newStu.birthDate);
		fout << 1 << endl;
		fout << endl;
		fout.close();
	}
	else {
		fin.open(path1);
		int nStu;
		getline(fin, line);
		nStu = stoi(line);
		Account* accStu;
		accStu = new Account[nStu + 1];
		for (int i = 0; i < nStu; i++) {
			getline(fin, accStu[i].username);
			getline(fin, accStu[i].password);
			getline(fin, accStu[i].studentProfile.fullname);
			getline(fin, accStu[i].studentProfile.classID);
			getline(fin, line);
			accStu[i].studentProfile.gender = line.front();
			getline(fin, line);
			accStu[i].studentProfile.birthDate = sToDate(line);
			getline(fin, line);
			accStu[i].studentProfile.active = stoi(line);
			fin.ignore(INT_MAX, '\n');
		}
		fin.close();

		for (int i = 0; i < nStu && sameID == false; i++) {
			if (newStu.ID == accStu[i].username)
				sameID = true;
		}
		fout.open(path1);
		if (!fout.is_open()) {
			cerr << "Can't register student account!" << endl;
			delete[] accStu;
			accStu = nullptr;
			return false;
		}
		if (!sameID) {
			accStu[nStu].username = newStu.ID;
			char temp[9];
			strftime(temp, 9, "%Y%m%d", &newStu.birthDate);
			line.assign(temp);
			accStu[nStu].password = sha256(line);
			accStu[nStu].studentProfile = newStu;
			sortAccount(accStu, 0, nStu, orderAcc);	//Sort the array in ascending order before output to the file
			fout << nStu + 1 << endl;
		}
		else fout << nStu << endl;
		for (int j = 0; j < nStu + 1; j++) {
			if (j == nStu && sameID == true) break;
			fout << accStu[j].username << endl
				<< accStu[j].password << endl
				<< accStu[j].studentProfile.fullname << endl
				<< accStu[j].studentProfile.classID << endl
				<< accStu[j].studentProfile.gender << endl;
			printDate(fout, accStu[j].studentProfile.birthDate);
			fout << accStu[j].studentProfile.active << endl;
			fout << endl;
		}
		fout.close();
		delete[] accStu;
		accStu = nullptr;
	}
	//Add to the class student list
	string path2 = systemPath + newStu.classID + "_Students.txt";
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
		sameID = false;
		bool addedStu = false;
		int n3;
		getline(fin, line);
		n3 = stoi(line) + 1;
		Student* oldStu = new Student[n3];
		for (int i = 0; i < n3; i++) {
			getline(fin, oldStu[i].ID);
			if (oldStu[i].ID == newStu.ID) {
				sameID = true;
				break;
			}
			getline(fin, oldStu[i].fullname);
			getline(fin, line);
			oldStu[i].gender = line.front();
			getline(fin, line);
			oldStu[i].birthDate = sToDate(line);
			getline(fin, line);
			oldStu[i].active = stoi(line);
			fin.ignore(INT_MAX, '\n');
			if (addedStu == false) {
				if (i < n3 - 1 && (*orderStu)(&newStu, &oldStu[i])) {
					oldStu[i + 1] = oldStu[i];
					oldStu[i] = newStu;
					addedStu = true;
					i++;
				}
				else if (i == n3 - 1) {
					oldStu[i] = newStu;
					addedStu = true;
				}
			}
		}
		fin.close();

		if (!sameID) {
			fout.open(path2);
			if (!fout.is_open()) {
				cerr << "Cannot open file " << path2;
				delete[] oldStu;
				oldStu = nullptr;
				return false;
			}
			fout << n3 << endl;
			for (int i = 0; i < n3; i++) {
				fout << oldStu[i].ID << endl
					<< oldStu[i].fullname << endl
					<< oldStu[i].gender << endl;
				printDate(fout, oldStu[i].birthDate);
				fout << oldStu[i].active << endl;
				fout << endl;
			}
			fout.close();
		}
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
	cout << endl;
	string path = systemPath + ClassID + "_Students.txt";
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
		cout << "Student ID: " << oldStu[i].ID << endl
			<< "Student name: " << oldStu[i].fullname << endl
			<< "Student gender: " << oldStu[i].gender << endl
			<< "Student birthdate: " << setfill('0') << right << oldStu[i].birthDate.tm_year + 1900 << '-'
			<< setw(2) << oldStu[i].birthDate.tm_mon + 1 << '-'
			<< setw(2) << oldStu[i].birthDate.tm_mday << endl;
		cout << "Status: ";
		if (oldStu[i].active) cout << "Active" << endl;
		else cout << "Inactive" << endl;
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
	int choice;

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
	string path1 = systemPath + ClassID + "_Students.txt";
	fin.open(path1);
	if (emptyFile(path1)) {
		cerr << "Can't read student data in this class!" << endl;
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

	string path2 = "./TextFiles/Students.txt";
	fin.open(path2);
	if (emptyFile(path2)) {
		cerr << "Cannot read students data from Students.txt" << endl;
		return false;
	}
	int n2;
	getline(fin, line);
	n2 = stoi(line);
	if (n2 == 0) return false;
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

	cout << "Enter new class ID: ";
	getline(cin, newClass);
	bool flag2 = false;
	for (int i = 0; i < n && flag2 == false; i++) {
		if (newClass == classes[i])
			flag2 = true;
	}
	if (flag2) {
		cout << "Do you want to exchage the students of 2 classes? Choose 1 or 0" << endl;
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
			cout << "Cancelled";
			return false;
		}
		if (choice == 1) {
			string path3 = systemPath + newClass + "_Students.txt";
			fin.open(path3);
			if (emptyFile(path3)) {
				cerr << "Can't read student data in this class!" << endl;
				return false;
			}
			int n3;
			getline(fin, line);
			n3 = stoi(line);
			if (n3 == 0) return false;
			Student* oldStu2 = new Student[n3];

			for (int i = 0; i < n3; i++) {
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

			fout.open(path3);
			if (!fout.is_open()) {
				cerr << "Cannot open file " << path3;
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
			fout << n3 << endl;
			for (int i = 0; i < n3; i++) {
				fout << oldStu2[i].ID << endl
					<< oldStu2[i].fullname << endl
					<< oldStu2[i].gender << endl;
				printDate(fout, oldStu2[i].birthDate);
				fout << oldStu2[i].active << endl;
				fout << endl;
			}
			fout.close();
			
			fout.open(path2);
			if (!fout.is_open()) {
				cerr << "Cannot open Students.txt" << endl;
				delete[] oldAcc;
				oldAcc = nullptr;
				return false;
			}
			fout << n2 << endl;
			for (int i = 0; i < n2; i++) {
				if (ClassID == oldAcc[i].studentProfile.classID) {
					fout << oldAcc[i].username << endl
						<< oldAcc[i].password << endl
						<< oldAcc[i].studentProfile.fullname << endl
						<< newClass << endl
						<< oldAcc[i].studentProfile.gender << endl;
					printDate(fout, oldAcc[i].studentProfile.birthDate);
					fout << oldAcc[i].studentProfile.active << endl;
					fout << endl;
				}
				if (newClass == oldAcc[i].studentProfile.classID) {
					fout << oldAcc[i].username << endl
						<< oldAcc[i].password << endl
						<< oldAcc[i].studentProfile.fullname << endl
						<< ClassID << endl
						<< oldAcc[i].studentProfile.gender << endl;
					printDate(fout, oldAcc[i].studentProfile.birthDate);
					fout << oldAcc[i].studentProfile.active << endl;
					fout << endl;
				}
				if (newClass != oldAcc[i].studentProfile.classID && ClassID != oldAcc[i].studentProfile.classID) {
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

			delete[] oldStu2;
			oldStu2 = nullptr;
		}
	}
	if (!flag2) {
		cout << "The class does not exist. Create new? Choose 1 or 0" << endl;
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
			cout << "Cancelled";
			return false;
		}
		if (choice == 1) {
			string path4 = "./TextFiles/Classes.txt";
			fout.open(path4);
			if (!fout.is_open()) {
				cerr << "Cannot open file " << path4;
				delete[] classes;
				return false;
			}
			fout << n + 1 << endl;
			for (int i = 0; i < n; i++)
				fout << classes[i] << endl;
			fout << newClass << endl;
			fout.close();

			string path5 = systemPath + newClass + "_Students.txt";
			fout.open(path5);
			if (!fout.is_open()) {
				cerr << "Cannot open file " << path5;
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

			string path6 = systemPath + ClassID + "_Students.txt";
			fout.open(path6);
			if (!fout.is_open()) {
				cerr << "Cannot open file " << path6;
				return false;
			}
			fout << 0;
			fout.close();

			fout.open(path2);
			if (!fout.is_open()) {
				cerr << "Cannot open Students.txt" << endl;
				delete[] oldAcc;
				oldAcc = nullptr;
				return false;
			}
			fout << n2 << endl;
			for (int i = 0; i < n2; i++) {
				if (ClassID == oldAcc[i].studentProfile.classID) {
					fout << oldAcc[i].username << endl
						<< oldAcc[i].password << endl
						<< oldAcc[i].studentProfile.fullname << endl
						<< newClass << endl
						<< oldAcc[i].studentProfile.gender << endl;
					printDate(fout, oldAcc[i].studentProfile.birthDate);
					fout << oldAcc[i].studentProfile.active << endl;
					fout << endl;
				}
				else {
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
	}
	delete[] oldAcc;
	oldAcc = nullptr;
	delete[] classes;
	classes = nullptr;
	delete[] oldStu1;
	oldStu1 = nullptr;
	return true;
}