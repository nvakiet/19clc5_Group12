#include "../Headers/lecturer.h"
bool importScoreBoard(Semester curSem) {
	string systemPath = "./TextFiles/";
	ifstream fin;
	ofstream fout;
	int n;
	string path, ClassID, line, crsID;
	Course newScore;

	cout << "Enter csv file path (or ./TextFiles/\"Filename\".csv if the file is in TextFiles folder): ";
	cin >> path;
	flushin(cin);
	//path = "./TextFiles/2019-2020_3rd Semester_CS162_19CLC5_Scoreboard.csv";
	cout << "Enter course ID: ";
	getline(cin, newScore.courseID);
	cout << "Enter class ID of the course: ";
	getline(cin, newScore.className);

	fin.open(path);
	if (!fin.is_open()) {
		cerr << "Can't open data file in the path: " << path << endl;
		return false;
	}
	int count = 0;
	fin.ignore(INT_MAX, '\n');
	while (getline(fin, line))
		count++;
	n = count;
	newScore.nStudents = n;
	newScore.studentArr = new Student[newScore.nStudents];
	newScore.board = new score[newScore.nStudents];
	fin.close();

	fin.open(path);
	fin.ignore(INT_MAX, '\n');
	for (int i = 0; i < n; i++) {
		fin.ignore(INT_MAX, ';');
		getline(fin, newScore.studentArr[i].ID, ';');
		fin.ignore(INT_MAX, ';');
		fin.ignore(INT_MAX, ';');
		getline(fin, line,';');
		newScore.board[i].midterm = stof(line);
		getline(fin, line,';');
		newScore.board[i].final = stof(line);
		getline(fin, line,';');
		newScore.board[i].bonus = stof(line);
		getline(fin, line);
		newScore.board[i].total = stof(line);
	}
	fin.close();
	
	/*curSem.year = "2019-2020";
	curSem.semester = "3rd Semester";*/
	path = systemPath + curSem.year + '_' + curSem.semester + '_' + newScore.className + "_Schedules.txt";
	fin.open(path);
	if (!findACourseInfos(fin, newScore, newScore.courseID)) {
		cerr << "Can't find the course!" << endl;
		return false;
	}
	fin.close();
	tm* dateArr = getWeeks(newScore.startDate, newScore.endDate, &newScore.nWeeks);
	if (dateArr == nullptr || newScore.nWeeks <= 0) {
		cerr << "Error getting schedule of the course!" << endl;
		return false;
	}
	path = systemPath + curSem.year + '_' + curSem.semester + '_' + newScore.courseID + '_' + newScore.className + "_Students.txt";
	fin.open(path);
	if (emptyFile(path)) {
		cerr << "Cannot read data of this course" << endl;
		delete[] dateArr;
		delete[] newScore.studentArr;
		delete[] newScore.board;
		return false;
	}
	Course crs;
	getline(fin, line);
	crs.nWeeks = stoi(line);
	getline(fin, line);
	crs.nStudents = stoi(line);
	crs.studentArr = new Student[crs.nStudents];	
	crs.board = new score[crs.nStudents];	
	crs.checkList = new bool[crs.nWeeks * crs.nStudents]{ false };	
	for (int i = 0; i < crs.nStudents; i++) {
		getline(fin, crs.studentArr[i].ID);
		getline(fin, crs.studentArr[i].fullname);
		getline(fin, line);
		crs.studentArr[i].gender = line.front();
		getline(fin, line);
		crs.studentArr[i].birthDate = sToDate(line);
		getline(fin, line);
		crs.studentArr[i].active = stoi(line);
		getline(fin, line);
		crs.board[i].midterm = stof(line);
		getline(fin, line);
		crs.board[i].final = stof(line);
		getline(fin, line);
		crs.board[i].bonus = stof(line);
		getline(fin, line);
		crs.board[i].total = stof(line);
		for (int j = 0; j < crs.nWeeks; j++) {
			getline(fin, line);
			crs.checkList[i * crs.nWeeks + j] = line.back() - '0';
		}
		fin.ignore(INT_MAX, '\n');
	}
	fin.close();
	
	//path = systemPath + "Test_" + newScore.courseID + '_' + newScore.className + ".txt";
	
	fout.open(path);
	if (!fout.is_open() || fout.fail()) {
		cerr << "Error while importing score" << endl;
		delete[] dateArr;
		delete[] crs.studentArr;
		delete[] crs.board;
		delete[] crs.checkList;
		delete[] newScore.studentArr;
		delete[] newScore.board;
		return false;
	}
	fout << crs.nWeeks << endl
		<< crs.nStudents << endl;
	int i = 0;
	for (int j = 0; j < crs.nStudents; j++) {
		fout << crs.studentArr[j].ID << endl
			<< crs.studentArr[j].fullname << endl
			<< crs.studentArr[j].gender << endl
			<< put_time(&crs.studentArr[j].birthDate, "%Y-%m-%d") << endl
			<< crs.studentArr[j].active << endl;
		if (newScore.studentArr[i].ID == crs.studentArr[j].ID) {
			fout << newScore.board[i].midterm << endl
				<< newScore.board[i].final << endl
				<< newScore.board[i].bonus << endl
				<< newScore.board[i].total << endl;
			i++;
		}
		else {
			fout << crs.board[j].midterm << endl
				<< crs.board[j].final << endl
				<< crs.board[j].bonus << endl
				<< crs.board[j].total << endl;
		}
		for (int z = 0; z < crs.nWeeks; z++) {
			fout << put_time(&dateArr[z], "%Y-%m-%d") << ' ' << crs.checkList[j * crs.nWeeks + z] << endl;
		}
		fout << endl;
	}
	fout.close();
	delete[] dateArr;
	delete[] crs.studentArr;
	delete[] crs.board;
	delete[] crs.checkList;
	delete[] newScore.studentArr;
	delete[] newScore.board;
	return true;
}
bool editAttendance(Semester curSem, Account user) {
	string systemPath = "./TextFiles/", fileEx = "_Students.txt";
	ifstream fin;
	ofstream fout;
	int n;
	string path, line, ID, date, active, lecturer;
	Course crs;
	lecturer = user.username;
	//lecturer = "dbtien";

	cout << "Enter course ID: ";
	getline(cin, crs.courseID);
	if (!viewClasses()) {
		cout << "There are no class in the system!" << endl;
		return false;
	}
	string* classes = readClassesID("./TextFiles/Classes.txt", &n);
	cout << "Enter class ID of the course: ";
	getline(cin, crs.className);
	bool flag = false;
	for (int i = 0; i < n && flag == false; i++) {
		if (crs.className == classes[i])
			flag = true;
	}
	while (!flag) {
		cout << "Enter existing class: ";
		getline(cin, crs.className);
		for (int i = 0; i < n && flag == false; i++) {
			if (crs.className == classes[i])
				flag = true;
		}
	}
	delete[] classes;
	classes = nullptr;

	/*curSem.year = "2019-2020";
	curSem.semester = "3rd Semester";*/
	path = systemPath + curSem.year + '_' + curSem.semester + '_' + crs.className + "_Schedules.txt";
	if (emptyFile(path)) {
		cerr << "Can't find the course!" << endl;
		return false;
	}
	fin.open(path);
	if (!findACourseInfos(fin, crs, crs.courseID)) {
		cerr << "Can't find the course!" << endl;
		return false;
	}
	fin.close();

	fin.open(path);
	if (!fin.is_open()) {
		cerr << "Can't open data file in the path: " << path << endl;
		return false;
	}
	getline(fin, line);
	int nCourses = stoi(line);
	if (nCourses == 0) return false;

	bool correctAcc = false;
	for (int i = 0; i < nCourses; i++) {
		getline(fin, line);
		if (line == crs.courseID) {
			fin.ignore(INT_MAX, '\n');
			getline(fin, line);
			if (line == lecturer)
				correctAcc = true;
		}
	}
	fin.close();

	if (!correctAcc) {
		cout << "This account is not allowed to edit this course" << endl;
		return false;
	}

	cout << "Enter student ID: ";
	getline(cin, ID);
	cout << "Enter date you want to edit (YYYY-MM-DD): ";
	getline(cin, date);
	cout << "Edit attendance (0 = Absent or 1 = Attended): ";
	getline(cin, active);

	path = systemPath + curSem.year + '_' + curSem.semester + '_' + crs.courseID + '_' + crs.className + "_Students.txt";
	//path = systemPath + "Test_" + crs.courseID + '_' + crs.className + ".txt";
	fin.open(path);
	if (emptyFile(path)) {
		cerr << "Cannot read data of this course" << endl;
		return false;
	}
	fout.open("./TextFiles/Temp.txt");
	int nWeeks;
	getline(fin, line);
	nWeeks = stoi(line);
	fout << nWeeks << endl;
	while (!fin.eof()) {
		getline(fin, line);
		fout << line << endl;
		if (ID == line) {
			for (int i = 0; i < 8 + nWeeks; i++) {
				getline(fin, line);
				if (line.substr(0, 10) == date) {
					fout << line.substr(0, 11) << active << endl;
				}
				else fout << line << endl;
			}
		}
	}
	fout.close();
	fin.close();

	if (remove(path.c_str()) != 0) {
		cout << "Error deleting file" << endl;
		remove("./TextFiles/Temp.txt");
		return false;
	}
	else
		cout << "File successfully deleted" << endl;

	if (rename("./TextFiles/Temp.txt", path.c_str()) == 0)
		cout << "File successfully renamed" << endl;
	else {
		cout << "Error renaming file" << endl;
		return false;
	}

	return true;
}
bool editGrade(Semester curSem, Account user) {
	string systemPath = "./TextFiles/";
	ifstream fin;
	ofstream fout;
	int n;
	string path, line, ID, midterm, final, bonus, total, lecturer;
	Course crs;
	lecturer = user.username;
	//lecturer = "dbtien";

	cout << "Enter course ID: ";
	getline(cin, crs.courseID);
	if (!viewClasses()) {
		cout << "There are no class in the system!" << endl;
		return false;
	}
	string* classes = readClassesID("./TextFiles/Classes.txt", &n);
	cout << "Enter class ID of the course: ";
	getline(cin, crs.className);
	bool flag = false;
	for (int i = 0; i < n && flag == false; i++) {
		if (crs.className == classes[i])
			flag = true;
	}
	while (!flag) {
		cout << "Enter existing class: ";
		getline(cin, crs.className);
		for (int i = 0; i < n && flag == false; i++) {
			if (crs.className == classes[i])
				flag = true;
		}
	}
	delete[] classes;
	classes = nullptr;

	/*curSem.year = "2019-2020";
	curSem.semester = "3rd Semester";*/
	path = systemPath + curSem.year + '_' + curSem.semester + '_' + crs.className + "_Schedules.txt";
	if (emptyFile(path)) {
		cerr << "Can't find the course!" << endl;
		return false;
	}
	fin.open(path);
	if (!findACourseInfos(fin, crs, crs.courseID)) {
		cerr << "Can't find the course!" << endl;
		return false;
	}
	fin.close();

	fin.open(path);
	if (!fin.is_open()) {
		cerr << "Can't open data file in the path: " << path << endl;
		return false;
	}
	getline(fin, line);
	int nCourses = stoi(line);
	if (nCourses == 0) return false;

	bool correctAcc = false;
	for (int i = 0; i < nCourses; i++) {
		getline(fin, line);
		if (line == crs.courseID) {
			fin.ignore(INT_MAX, '\n');
			getline(fin, line);
			if (line == lecturer)
				correctAcc = true;
		}
	}
	fin.close();

	if (!correctAcc) {
		cout << "This account is not allowed to edit this course" << endl;
		return false;
	}

	cout << "Enter student ID: ";
	getline(cin, ID);

	path = systemPath + curSem.year + '_' + curSem.semester + '_' + crs.courseID + '_' + crs.className + "_Students.txt";
	//path = systemPath + "Test_" + crs.courseID + '_' + crs.className + ".txt";
	fin.open(path);
	while (!fin.eof()) {
		getline(fin, line);
		if (ID == line) {
			for (int i = 0; i < 4; i++)
				fin.ignore(INT_MAX, '\n');
			getline(fin, line);
			cout << "Current midterm score: " << line << endl;
			getline(fin, line);
			cout << "Current final score: " << line << endl;
			getline(fin, line);
			cout << "Current bonus score: " << line << endl;
			getline(fin, line);
			cout << "Current total score: " << line << endl;
			break;
		}
	}
	fin.close();

	cout << "Edit midterm: ";
	getline(cin, midterm);
	cout << "Edit final: ";
	getline(cin, final);
	cout << "Edit bonus: ";
	getline(cin, bonus);
	cout << "Edit total: ";
	getline(cin, total);

	fin.open(path);
	if (emptyFile(path)) {
		cerr << "Cannot read data of this course" << endl;
		return false;
	}
	fout.open("./TextFiles/Temp.txt");
	int nWeeks;
	getline(fin, line);
	nWeeks = stoi(line);
	fout << nWeeks << endl;
	while (!fin.eof()) {
		getline(fin, line);
		fout << line << endl;
		if (ID == line) {
			for (int i = 0; i < 4; i++) {
				getline(fin, line);
				fout << line << endl;
			}
			fout << midterm << endl
				<< final << endl
				<< bonus << endl
				<< total << endl;
			for (int i = 0; i < 4; i++)
				fin.ignore(INT_MAX, '\n');
		}
	}
	fout.close();
	fin.close();

	if (remove(path.c_str()) != 0) {
		cout << "Error deleting file" << endl;
		remove("./TextFiles/Temp.txt");
		return false;
	}
	else
		cout << "File successfully deleted" << endl;

	if (rename("./TextFiles/Temp.txt", path.c_str()) == 0)
		cout << "File successfully renamed" << endl;
	else {
		cout << "Error renaming file" << endl;
		return false;
	}

	return true;
}