#include "../Headers/staff-course.h"

Semester getCurrentSemester() {
	time_t current = time(NULL);
	Semester curSem;
	tm timeinfo;
	localtime_s(&timeinfo, &current);
	if (timeinfo.tm_mon > 7) {
		curSem.semester = "1st Semester";
		curSem.year = to_string(timeinfo.tm_year + 1900) + '-' + to_string(timeinfo.tm_year + 1900 + 1);
	}
	else if (timeinfo.tm_mon < 4) {
		curSem.semester = "2nd Semester";
		curSem.year = to_string(timeinfo.tm_year + 1900 - 1) + '-' + to_string(timeinfo.tm_year + 1900);
	}
	else {
		curSem.semester = "3rd Semester";
		curSem.year = to_string(timeinfo.tm_year + 1900 - 1) + '-' + to_string(timeinfo.tm_year + 1900);
	}
	return curSem;
}

bool updateSemester(Semester newSem) {
	string path = "./TextFiles/Semesters.txt";
	//If the file hasn't been created or is empty
	if (emptyFile(path)) {
		//Write the semester as first entry to the file
		ofstream fout;
		fout.open(path);
		if (fout.is_open()) {
			fout << 1 << endl;
			fout << newSem.year << endl;
			fout << newSem.semester << endl;
			fout << endl;
			fout.close();
			return true;
		}
		else return false;
	}
	//If the file isn't empty, scan the file to check if the input is duplicate
	bool dup = false;
	int n;
	Semester *fileSem;
	string line;
	ifstream fin;
	fin.open(path);	//We already check if file can be opened in emptyFile function
	getline(fin, line);
	n = stoi(line);
	fileSem = new Semester[n + 1];
	for (int i = 0; i < n && dup == false; i++) {
		getline(fin, fileSem[i].year);
		getline(fin, fileSem[i].semester);
		fin.ignore(INT_MAX, '\n'); //Skip the blank line
		if (fileSem[i].year == newSem.year && fileSem[i].semester == newSem.semester)
			dup = true; //If the input semester already existed, break the loop
	}
	if (!fin) {
		delete[] fileSem;
		return false;
	}
	fin.close();
	if (dup) {	//If duplicate, consider function successfully "updated" the semester list
		delete[] fileSem;
		return true;	//True because the semester is already "updated"
	}
	//If not duplicate, rewrite the semester list with a new semester array
	fileSem[n].year = newSem.year;
	fileSem[n].semester = newSem.semester;
	n++;
	ofstream fout;
	fout.open(path);
	if (!fout.is_open()) {
		cerr << "Unable to delete. Please try again." << endl;
		delete[] fileSem;
		return false;
	}
	else {
		fout << n << endl;
		for (int i = 0; i < n; i++) {
			fout << fileSem[i].year << endl;
			fout << fileSem[i].semester << endl;
			fout << endl;
		}
	}
	delete[] fileSem;
	fout.close();
	return true;
}

bool deleteSemester() {
	Semester inputSem;
	cout << "Enter academic year (Example: 2018-2019): ";
	getline(cin, inputSem.year);
	cout << "Enter semester (1st/2nd/3rd Semester): ";
	getline(cin, inputSem.semester);
	string path = "./TextFiles/Semesters.txt";
	//If the file hasn't been created or is empty
	if (emptyFile(path)) return false;
	//If the file isn't empty, scan the file to check if the input is duplicate
	int n;
	Semester* fileSem;
	string line;
	ifstream fin;
	fin.open(path);	//We already check if file can be opened in emptyFile function
	getline(fin, line);
	n = stoi(line);
	fileSem = new Semester[n];
	for (int i = 0; i < n;) {
		getline(fin, fileSem[i].year);
		getline(fin, fileSem[i].semester);
		fin.ignore(INT_MAX, '\n'); //Skip the blank line
		if (fileSem[i].year == inputSem.year && fileSem[i].semester == inputSem.semester)
			n--; //Reduce number of semesters by 1, the semester the user wants to delete won't be loaded to the array
		else i++;
	}
	if (!fin) {
		delete[] fileSem;
		return false;
	}
	fin.close();
	//Rewrite the file with the new array not containing the semester the user wants to delete
	ofstream fout;
	fout.open(path);
	if (!fout.is_open()) {
		cerr << "Unable to delete. Please try again." << endl;
		delete[] fileSem;
		return false;
	}
	else {
		fout << n << endl;
		for (int i = 0; i < n; i++) {
			fout << fileSem[i].year << endl;
			fout << fileSem[i].semester << endl;
			fout << endl;
		}
	}
	delete[] fileSem;
	fout.close();
	return true;
}

void viewSemesterList() {
	string path = "./TextFiles/Semesters.txt";
	if (emptyFile(path)) {
		cout << "No semester has been recorded yet!" << endl;
		return;
	}
	int n;
	Semester* fileSem;
	string line;
	ifstream fin;
	fin.open(path);	//We already check if file can be opened in emptyFile function
	getline(fin, line);
	n = stoi(line);
	if (n == 0) {
		cout << "No semester has been recorded yet!" << endl;
		return;
	}
	fileSem = new Semester[n];
	for (int i = 0; i < n; i++) {
		getline(fin, fileSem[i].year);
		getline(fin, fileSem[i].semester);
		fin.ignore(INT_MAX, '\n'); //Skip the blank line
	}
	if (!fin) {
		cerr << "Can't load the semester list!" << endl;
		delete[] fileSem;
		return;
	}
	fin.close();
	//Print the semester array to the screen
	cout << string(20, '=') << " ALL SEMESTERS " << string(20, '=') << endl;
	cout << string(33, '-') << endl;
	cout << '|' << center("Academic Year", 15) << '|' << center("Semester", 15) << '|' << endl;
	cout << string(33, '-') << endl;
	for (int i = 0; i < n; i++) {
		cout << '|' << center(fileSem[i].year, 15) << '|' << center(fileSem[i].semester, 15) << '|' << endl;
		cout << string(33, '-') << endl;
	}
	delete[] fileSem;
}

bool addCourse(Semester curSem) {
	//To do list:
	//* Read inputs from user and store to a Course structure
	ifstream fin;
	ofstream fout;
	string line, slackName;
	Course inCourse;
	inCourse.c_semester = curSem;
	cout << "Enter course ID: ";
	getline(cin, inCourse.courseID);
	cout << "Enter course name: ";
	getline(cin, inCourse.courseName);
	int n;
	viewClasses();
	string* classes = readClassesID("./TextFiles/Classes.txt", &n);
	cout << "Enter class ID: ";
	getline(cin, inCourse.className);
	bool flag = false;
	for (int i = 0; i < n && flag == false; i++) {
		if (inCourse.className == classes[i])
			flag = true;
	}
	while (!flag) {
		cout << "Enter existing class: ";
		getline(cin, inCourse.className);
		for (int i = 0; i < n && flag == false; i++) {
			if (inCourse.className == classes[i])
				flag = true;
		}
	}
	delete[] classes;
	classes = nullptr;
	cout << "Enter lecturer username: ";
	getline(cin, slackName);
	cout << "Enter lecturer's full name: ";
	getline(cin, inCourse.courseLecturer.fullname);
	cout << "Enter lecturer's email: ";
	getline(cin, inCourse.courseLecturer.email);
	cout << "Enter lecturer's academic degree (Master/PhD/Professor): ";
	getline(cin, inCourse.courseLecturer.academicRank);
	cout << "Enter lecturer's gender (M/F): ";
	getline(cin, line);
	inCourse.courseLecturer.gender = line.front();
	resetTM(inCourse.startDate);
	cout << "Enter start date of course (YYYY-MM-DD): ";
	cin >> get_time(&inCourse.startDate, "%Y-%m-%d");
	while (!cin) {
		cerr << "Invalid date input!" << endl;
		flushin(cin);
		cout << "Enter start date of course (YYYY-MM-DD): ";
		cin >> get_time(&inCourse.startDate, "%Y-%m-%d");
	}
	flushin(cin);
	resetTM(inCourse.endDate);
	cout << "Enter end date of course (YYYY-MM-DD): ";
	cin >> get_time(&inCourse.endDate, "%Y-%m-%d");
	while (!cin) {
		cerr << "Invalid date input!" << endl;
		flushin(cin);
		cout << "Enter end date of course (YYYY-MM-DD): ";
		cin >> get_time(&inCourse.endDate, "%Y-%m-%d");
	}
	flushin(cin);
	cout << "Enter day of week when course is available in shortened form (Ex: Thu, Fri): ";
	getline(cin, inCourse.classDay);
	resetTM(inCourse.startTime);
	cout << "Enter start time of class (HH:MM): ";
	cin >> get_time(&inCourse.startTime, "%H:%M");
	while (!cin) {
		cerr << "Invalid time input!" << endl;
		flushin(cin);
		cout << "Enter start time of class (HH:MM): ";
		cin >> get_time(&inCourse.startTime, "%H:%M");
	}
	flushin(cin);
	resetTM(inCourse.endTime);
	cout << "Enter end time of class (HH:MM): ";
	cin >> get_time(&inCourse.endTime, "%H:%M");
	while (!cin) {
		cerr << "Invalid time input!" << endl;
		flushin(cin);
		cout << "Enter end time of class (HH:MM): ";
		cin >> get_time(&inCourse.endTime, "%H:%M");
	}
	flushin(cin);
	cout << "Enter classroom number: ";
	getline(cin, inCourse.room);
	cout << endl;
	//* Register lecturer account in Lecturers.txt
	cout << "Registering lecturer's account if it's new..." << endl;
	string Path = "./TextFiles/Lecturers.txt";
	if (emptyFile(Path)) {
		//If Lecturers.txt hasn't been created or is empty
		fout.open(Path);
		if (!fout.is_open()) {
			cerr << "Can't update lecturer account!" << endl;
			return false;
		}
		fout << 1 << endl;
		fout << slackName << endl
			<< sha256(slackName + "_HCMUS") << endl
			<< inCourse.courseLecturer.fullname << endl
			<< inCourse.courseLecturer.email << endl
			<< inCourse.courseLecturer.academicRank << endl
			<< inCourse.courseLecturer.gender << endl;
		fout << endl;
		fout.close();
		cout << "Lecturer's account has been created!" << endl;
	}
	else {
		//Store data file into account array and check if the lecturer account has been created before
		fin.open(Path);
		Account* userArr;
		int nLecturers;
		bool sameLecturer = false; //Flag to check if it's new account
		getline(fin, line);
		nLecturers = stoi(line) + 1;
		userArr = new Account[nLecturers];
		for (int i = 0; i < nLecturers - 1 && sameLecturer == false; i++) {
			getline(fin, userArr[i].username);
			getline(fin, userArr[i].password);
			getline(fin, userArr[i].lecturerProfile.fullname);
			getline(fin, userArr[i].lecturerProfile.email);
			getline(fin, userArr[i].lecturerProfile.academicRank);
			getline(fin, line);
			userArr[i].lecturerProfile.gender = line.front(); //Get first character of the gender string 'F' or 'M'
			fin.ignore(INT_MAX, '\n'); //This one is to skip the blank line
			if (userArr[i].username == slackName && userArr[i].lecturerProfile.fullname == inCourse.courseLecturer.fullname)
				sameLecturer = true;
		}
		fin.close();
		//Input new lecturer as last element in the array and write new array to file
		if (sameLecturer == false) {
			userArr[nLecturers - 1].username = slackName;
			userArr[nLecturers - 1].password = sha256(slackName + "_HCMUS");
			userArr[nLecturers - 1].lecturerProfile = inCourse.courseLecturer;
			sortAccount(userArr, 0, nLecturers - 1);
			fout.open(Path);
			if (!fout.is_open()) {
				cerr << "Can't update lecturer's account!" << endl;
				delete[] userArr;
				return false;
			}
			fout << nLecturers << endl;
			for (int i = 0; i < nLecturers; i++) {	//Rewrite existed accounts
				fout << userArr[i].username << endl
					<< userArr[i].password << endl
					<< userArr[i].lecturerProfile.fullname << endl
					<< userArr[i].lecturerProfile.email << endl
					<< userArr[i].lecturerProfile.academicRank << endl
					<< userArr[i].lecturerProfile.gender << endl;
				fout << endl;
			}
			fout.close();
			cout << "Lecturer's account has been created!" << endl;
		}
		else cout << "The lecturer's account already existed." << endl;
		//After reading and writing, release the memory of array
		delete[] userArr;
		userArr = nullptr;
	}

	//* Add course info to [Year]_[Semester]_[ClassID]_Schedules.txt
	cout << "Updating course info..." << endl;
	Path = "./TextFiles/" + inCourse.c_semester.year + '_' + inCourse.c_semester.semester + '_' + inCourse.className + "_Schedules.txt";
	if (emptyFile(Path)) {
		//If the file hasn't been created or is empty
		fout.open(Path);
		if (!fout.is_open()) {
			cerr << "Can't update course info!" << endl;
			return false;
		}
		fout << 1 << endl;
		fout << inCourse.courseID << endl
			<< inCourse.courseName << endl
			<< slackName << endl
			<< inCourse.courseLecturer.fullname << endl
			<< inCourse.courseLecturer.email << endl
			<< inCourse.courseLecturer.academicRank << endl
			<< inCourse.courseLecturer.gender << endl;
		printDate(fout, inCourse.startDate);
		printDate(fout, inCourse.endDate);
		fout << inCourse.classDay << endl;
		printTime(fout, inCourse.startTime);
		printTime(fout, inCourse.endTime);
		fout << inCourse.room << endl;
		fout << endl;
		fout.close();
		cout << "Course info has been updated!" << endl;
	}
	else {
		fin.open(Path);
		int nCourses;
		//Load the existed courses to an array
		getline(fin, line);
		nCourses = stoi(line) + 1;
		Course* courseArr = new Course[nCourses];
		string* slack = new string[nCourses];
		for (int i = 0; i < nCourses - 1; i++) {
			getline(fin, courseArr[i].courseID);
			getline(fin, courseArr[i].courseName);
			getline(fin, slack[i]);
			getline(fin, courseArr[i].courseLecturer.fullname);
			getline(fin, courseArr[i].courseLecturer.email);
			getline(fin, courseArr[i].courseLecturer.academicRank);
			getline(fin, line);
			courseArr[i].courseLecturer.gender = line.front();
			getline(fin, line);
			courseArr[i].startDate = sToDate(line);
			getline(fin, line);
			courseArr[i].endDate = sToDate(line);
			getline(fin, courseArr[i].classDay);
			getline(fin, line);
			courseArr[i].startTime = sToTime(line);
			getline(fin, line);
			courseArr[i].endTime = sToTime(line);
			getline(fin, courseArr[i].room);
			fin.ignore(INT_MAX, '\n');
		}
		fin.close();
		//Add the new course as last element in array
		courseArr[nCourses - 1] = inCourse;
		slack[nCourses - 1] = slackName;
		//Write new array to the file
		fout.open(Path);
		if (!fout.is_open()) {
			cerr << "Can't update the course info!" << endl;
			delete[] courseArr;
			delete[] slack;
			return false;
		}
		fout << nCourses << endl;
		for (int i = 0; i < nCourses; i++) {
			fout << courseArr[i].courseID << endl
				<< courseArr[i].courseName << endl
				<< slack[i] << endl
				<< courseArr[i].courseLecturer.fullname << endl
				<< courseArr[i].courseLecturer.email << endl
				<< courseArr[i].courseLecturer.academicRank << endl
				<< courseArr[i].courseLecturer.gender << endl;
			printDate(fout, courseArr[i].startDate);
			printDate(fout, courseArr[i].endDate);
			fout << courseArr[i].classDay << endl;
			printTime(fout, courseArr[i].startTime);
			printTime(fout, courseArr[i].endTime);
			fout << courseArr[i].room << endl;
			fout << endl;
		}
		delete[] courseArr;
		courseArr = nullptr;
		delete[] slack;
		slack = nullptr;
		fout.close();
		cout << "Course info has been updated!" << endl;
	}

	//* Load [ClassID]_Students.txt to student array
	cout << "Loading student list of the class..." << endl;
	Path = "./TextFiles/" + inCourse.className + "_Students.txt";
	int nInactive = 0;
	if (emptyFile(Path)) {
		cerr << "Can't find student list of " << inCourse.className << ". Please import the class first!" << endl;
		return false;
	}
	else {
		fin.open(Path);
		getline(fin, line);
		inCourse.nStudents = stoi(line);
		inCourse.studentArr = new Student[inCourse.nStudents];
		for (int i = 0; i < inCourse.nStudents; i++) {
			getline(fin, inCourse.studentArr[i].ID);
			getline(fin, inCourse.studentArr[i].fullname);
			getline(fin, line);
			inCourse.studentArr[i].gender = line.front();
			getline(fin, line);
			inCourse.studentArr[i].birthDate = sToDate(line);
			getline(fin, line);
			inCourse.studentArr[i].active = stoi(line);
			fin.ignore(INT_MAX, '\n');
			if (inCourse.studentArr[i].active == false)
				nInactive++;
		}
		fin.close();
	}
	cout << "Student list has been loaded!" << endl;

	//* Get nWeeks and date array from startDate and endDate (including startDate and endDate in array)
	cout << "Loading dates between start date and end date of the course..." << endl;
	tm* dateArr = getWeeks(inCourse.startDate, inCourse.endDate, &inCourse.nWeeks);
	if (dateArr == nullptr) {
		cerr << "Can't calculate dates between starting date and ending date of the course!" << endl;
		delete[] inCourse.studentArr;
		return false;
	}
	cout << "Date list has been loaded!" << endl;

	//* Save the student array to [Year]_[Semester]_[CourseID]_[ClassID]_Students.txt
	//  ^ along with default scoreboards of -1 and nWeeks and date array and default check lists of 0 for each student
	cout << "Generating default student list for the course..." << endl;
	Path = "./TextFiles/" + inCourse.c_semester.year + '_' + inCourse.c_semester.semester + '_' + inCourse.courseID + '_' + inCourse.className + "_Students.txt";
	if (emptyFile(Path)) {
		fout.open(Path);
		if (!fout.is_open()) {
			cerr << "Can't generate the student list!" << endl;
			delete[] inCourse.studentArr;
			delete[] dateArr;
			return false;
		}
		fout << inCourse.nWeeks << endl
			<< inCourse.nStudents << endl;
		for (int i = 0; i < inCourse.nStudents; i++) {
			fout << inCourse.studentArr[i].ID << endl
				<< inCourse.studentArr[i].fullname << endl
				<< inCourse.studentArr[i].gender << endl;
			printDate(fout, inCourse.studentArr[i].birthDate);
			fout << inCourse.studentArr[i].active << endl;
			for (int j = 0; j < 4; j++)
				fout << -1 << endl;
			for (int j = 0; j < inCourse.nWeeks; j++)
				fout << put_time(&dateArr[j], "%Y-%m-%d") << " 0" << endl;
			fout << endl;
		}
		fout.close();
		cout << "The student list for this course has been generated!" << endl;
	}
	else {
		cout << "The student list for this course already existed. Do you want to overwrite it with a new default list?" << endl;
		cout << "1. Yes / 0. No" << endl;
		int choice;
		cout << "Enter a number for your choice: ";
		cin >> choice;
		if (!cin || choice < 0 || choice > 1) {
			cerr << "Invalid input!" << endl;
			flushin(cin);
			cout << "Enter a number for your choice: ";
			cin >> choice;
		}
		flushin(cin);
		if (choice == 0) {
			cout << "The process has been stopped!" << endl;
			delete[] inCourse.studentArr;
			delete[] dateArr;
			return false;
		}
		if (choice == 1) {
			fout.open(Path);
			if (!fout.is_open()) {
				cerr << "Can't generate the student list!" << endl;
				delete[] inCourse.studentArr;
				delete[] dateArr;
				return false;
			}
			fout << inCourse.nWeeks << endl
				<< inCourse.nStudents << endl;
			for (int i = 0; i < inCourse.nStudents; i++) {
				fout << inCourse.studentArr[i].ID << endl
					<< inCourse.studentArr[i].fullname << endl
					<< inCourse.studentArr[i].gender << endl;
				printDate(fout, inCourse.studentArr[i].birthDate);
				fout << inCourse.studentArr[i].active << endl;
				for (int j = 0; j < 4; j++)
					fout << -1 << endl;
				for (int j = 0; j < inCourse.nWeeks; j++)
					fout << put_time(&dateArr[j], "%Y-%m-%d") << " 0" << endl;
				fout << endl;
			}
			fout.close();
			cout << "The student list for this course has been generated!" << endl;
		}
	}

	//* Add this course to register course list of each student in [Year]_[Semester]_Student Courses.txt
	cout << "Adding this course to Enrolled Courses list of each student in this class by default..." << endl;
	Path = "./TextFiles/" + inCourse.c_semester.year + '_' + inCourse.c_semester.semester + "_Student Courses.txt";
		//If the file hasn't been created
	if (emptyFile(Path)) {
		fout.open(Path);
		if (!fout.is_open()) {
			cerr << "Can't add this course to the list!" << endl;
			delete[] inCourse.studentArr;
			delete[] dateArr;
			return false;
		}
		fout << inCourse.nStudents - nInactive << endl;
		for (int i = 0; i < inCourse.nStudents; i++) {
			if (inCourse.studentArr[i].active == false) continue; //Inactive students won't be registered with the course
			fout << inCourse.studentArr[i].ID << endl
				<< inCourse.studentArr[i].fullname << endl
				<< inCourse.className << endl
				<< 1 << endl
				<< inCourse.courseID << ' ' << inCourse.className << endl;
			fout << endl;
		}
		fout.close();
		cout << "The course has been added to the students' Courses list." << endl;
	}
	else {
		//If the file already existed, load it to an array of RegCourses
		int nReg; //Number of students recorded in the file
		bool addedClass = false; //Flag to check if the class are already recorded
		bool* sameCourse; //Flag to check if a recorded student already enrolled in the same course of different class
		fin.open(Path);
		getline(fin, line);
		nReg = stoi(line);
		RegCourses* regStudents = new RegCourses[nReg];
		sameCourse = new bool[nReg] {false}; //This flag uses the same iterator as regStudents to check the recorded students
		for (int i = 0; i < nReg; i++) {
			getline(fin, regStudents[i].studentID);
			getline(fin, regStudents[i].studentName);
			getline(fin, regStudents[i].studentClass);
			if (regStudents[i].studentClass == inCourse.className) addedClass = true;
			getline(fin, line);
			regStudents[i].nCourses = stoi(line);
			regStudents[i].courseID = new string[regStudents[i].nCourses];
			regStudents[i].classID = new string[regStudents[i].nCourses];
			for (int j = 0; j < regStudents[i].nCourses; j++) {
				getline(fin, regStudents[i].courseID[j], ' ');
				getline(fin, regStudents[i].classID[j]);
				//In case the student is in this class but already enrolled in the same course of another class
				if (regStudents[i].courseID[j] == inCourse.courseID) sameCourse[i] = true;
			}
			fin.ignore(INT_MAX, '\n');
		}
		fin.close();

		//Write new course to the Enrolled Courses list of the recorded students
		fout.open(Path);
		if (addedClass == false) {
			//If the class hasn't been record
			fout << nReg + inCourse.nStudents - nInactive << endl;
			for (int i = 0; i < nReg; i++) {	//Output existed regStudents
				fout << regStudents[i].studentID << endl
					<< regStudents[i].studentName << endl
					<< regStudents[i].studentClass << endl
					<< regStudents[i].nCourses << endl;
				for (int j = 0; j < regStudents[i].nCourses; j++)
					fout << regStudents[i].courseID[j] << ' ' << regStudents[i].classID[j] << endl;
				fout << endl;
			}
			for (int i = 0; i < inCourse.nStudents; i++) {	//Add studentArr of this class with a new course
				if (inCourse.studentArr[i].active == false) continue; //Inactive students won't be registered with the course
				fout << inCourse.studentArr[i].ID << endl
					<< inCourse.studentArr[i].fullname << endl
					<< inCourse.className << endl
					<< 1 << endl
					<< inCourse.courseID << ' ' << inCourse.className << endl;
				fout << endl;
			}
		}
		if (addedClass == true) {
			//If the class has been recorded
			fout << nReg << endl;
			for (int i = 0; i < nReg; i++) {	//Output existed regStudents
				fout << regStudents[i].studentID << endl
					<< regStudents[i].studentName << endl
					<< regStudents[i].studentClass << endl;
				if (regStudents[i].studentClass == inCourse.className && sameCourse[i] == false) {
					//If it's the student in the class and they haven't enrolled in the course
					fout << regStudents[i].nCourses + 1 << endl;
					fout << inCourse.courseID << ' ' << inCourse.className << endl;
				}
				else fout << regStudents[i].nCourses << endl;
				for (int j = 0; j < regStudents[i].nCourses; j++)
					fout << regStudents[i].courseID[j] << ' ' << regStudents[i].classID[j] << endl;
				fout << endl;
			}
		}
		fout.close();
		cout << "The course has been added to the students' Enrolled Courses list!" << endl;
		//REMEMBER TO DELETE THE ARRAY INSIDE EACH STRUCT ELEMENT AND THE STRUCT ARRAY ITSELF
		delete[] sameCourse;
		for (int i = 0; i < nReg; i++) {
			delete[] regStudents[i].classID;
			delete[] regStudents[i].courseID;
		}
		delete[] regStudents;
	}
	//Function only returns true after all processes are done, student array of input class and date array are deleted 
	delete[] inCourse.studentArr;
	delete[] dateArr;
	return true;
}

bool addCourse(Course inCourse, string slackName) {
	ifstream fin;
	ofstream fout;
	string line;
	//* Register lecturer account in Lecturers.txt
	string Path = "./TextFiles/Lecturers.txt";
	if (emptyFile(Path)) {
		//If Lecturers.txt hasn't been created or is empty
		fout.open(Path);
		if (!fout.is_open()) {
			cerr << "Can't update lecturer account!" << endl;
			return false;
		}
		fout << 1 << endl;
		fout << slackName << endl
			<< sha256(slackName + "_HCMUS") << endl
			<< inCourse.courseLecturer.fullname << endl
			<< inCourse.courseLecturer.email << endl
			<< inCourse.courseLecturer.academicRank << endl
			<< inCourse.courseLecturer.gender << endl;
		fout << endl;
		fout.close();
	}
	else {
		//Store data file into account array and check if the lecturer account has been created before
		fin.open(Path);
		Account* userArr;
		int nLecturers;
		bool sameLecturer = false; //Flag to check if it's new account
		getline(fin, line);
		nLecturers = stoi(line) + 1;
		userArr = new Account[nLecturers];
		for (int i = 0; i < nLecturers - 1 && sameLecturer == false; i++) {
			getline(fin, userArr[i].username);
			getline(fin, userArr[i].password);
			getline(fin, userArr[i].lecturerProfile.fullname);
			getline(fin, userArr[i].lecturerProfile.email);
			getline(fin, userArr[i].lecturerProfile.academicRank);
			getline(fin, line);
			userArr[i].lecturerProfile.gender = line.front(); //Get first character of the gender string 'F' or 'M'
			fin.ignore(INT_MAX, '\n'); //This one is to skip the blank line
			if (userArr[i].username == slackName && userArr[i].lecturerProfile.fullname == inCourse.courseLecturer.fullname)
				sameLecturer = true;
		}
		fin.close();
		//Input new lecturer as last element in the array and write new array to file
		if (sameLecturer == false) {
			userArr[nLecturers - 1].username = slackName;
			userArr[nLecturers - 1].password = sha256(slackName + "_HCMUS");
			userArr[nLecturers - 1].lecturerProfile = inCourse.courseLecturer;
			sortAccount(userArr, 0, nLecturers - 1);
			fout.open(Path);
			if (!fout.is_open()) {
				cerr << "Can't update lecturer's account!" << endl;
				delete[] userArr;
				return false;
			}
			fout << nLecturers << endl;
			for (int i = 0; i < nLecturers; i++) {	//Rewrite existed accounts
				fout << userArr[i].username << endl
					<< userArr[i].password << endl
					<< userArr[i].lecturerProfile.fullname << endl
					<< userArr[i].lecturerProfile.email << endl
					<< userArr[i].lecturerProfile.academicRank << endl
					<< userArr[i].lecturerProfile.gender << endl;
				fout << endl;
			}
			fout.close();
		}
		//After reading and writing, release the memory of array
		delete[] userArr;
		userArr = nullptr;
	}

	//* Add course info to [Year]_[Semester]_[ClassID]_Schedules.txt
	Path = "./TextFiles/" + inCourse.c_semester.year + '_' + inCourse.c_semester.semester + '_' + inCourse.className + "_Schedules.txt";
	if (emptyFile(Path)) {
		//If the file hasn't been created or is empty
		fout.open(Path);
		if (!fout.is_open()) {
			cerr << "Can't update course info!" << endl;
			return false;
		}
		fout << 1 << endl;
		fout << inCourse.courseID << endl
			<< inCourse.courseName << endl
			<< slackName << endl
			<< inCourse.courseLecturer.fullname << endl
			<< inCourse.courseLecturer.email << endl
			<< inCourse.courseLecturer.academicRank << endl
			<< inCourse.courseLecturer.gender << endl;
		printDate(fout, inCourse.startDate);
		printDate(fout, inCourse.endDate);
		fout << inCourse.classDay << endl;
		printTime(fout, inCourse.startTime);
		printTime(fout, inCourse.endTime);
		fout << inCourse.room << endl;
		fout << endl;
		fout.close();
	}
	else {
		fin.open(Path);
		int nCourses;
		//Load the existed courses to an array
		getline(fin, line);
		nCourses = stoi(line) + 1;
		Course* courseArr = new Course[nCourses];
		string* slack = new string[nCourses];
		for (int i = 0; i < nCourses - 1; i++) {
			getline(fin, courseArr[i].courseID);
			getline(fin, courseArr[i].courseName);
			getline(fin, slack[i]);
			getline(fin, courseArr[i].courseLecturer.fullname);
			getline(fin, courseArr[i].courseLecturer.email);
			getline(fin, courseArr[i].courseLecturer.academicRank);
			getline(fin, line);
			courseArr[i].courseLecturer.gender = line.front();
			getline(fin, line);
			courseArr[i].startDate = sToDate(line);
			getline(fin, line);
			courseArr[i].endDate = sToDate(line);
			getline(fin, courseArr[i].classDay);
			getline(fin, line);
			courseArr[i].startTime = sToTime(line);
			getline(fin, line);
			courseArr[i].endTime = sToTime(line);
			getline(fin, courseArr[i].room);
			fin.ignore(INT_MAX, '\n');
		}
		fin.close();
		//Add the new course as last element in array
		courseArr[nCourses - 1] = inCourse;
		slack[nCourses - 1] = slackName;
		//Write new array to the file
		fout.open(Path);
		if (!fout.is_open()) {
			cerr << "Can't update the course info!" << endl;
			delete[] courseArr;
			delete[] slack;
			return false;
		}
		fout << nCourses << endl;
		for (int i = 0; i < nCourses; i++) {
			fout << courseArr[i].courseID << endl
				<< courseArr[i].courseName << endl
				<< slack[i] << endl
				<< courseArr[i].courseLecturer.fullname << endl
				<< courseArr[i].courseLecturer.email << endl
				<< courseArr[i].courseLecturer.academicRank << endl
				<< courseArr[i].courseLecturer.gender << endl;
			printDate(fout, courseArr[i].startDate);
			printDate(fout, courseArr[i].endDate);
			fout << courseArr[i].classDay << endl;
			printTime(fout, courseArr[i].startTime);
			printTime(fout, courseArr[i].endTime);
			fout << courseArr[i].room << endl;
			fout << endl;
		}
		delete[] courseArr;
		courseArr = nullptr;
		delete[] slack;
		slack = nullptr;
		fout.close();
	}

	//* Load [ClassID]_Students.txt to student array
	Path = "./TextFiles/" + inCourse.className + "_Students.txt";
	int nInactive = 0;
	if (emptyFile(Path)) {
		cerr << "Can't find student list of " << inCourse.className << ". Please import the class first!" << endl;
		return false;
	}
	else {
		fin.open(Path);
		getline(fin, line);
		inCourse.nStudents = stoi(line);
		inCourse.studentArr = new Student[inCourse.nStudents];
		for (int i = 0; i < inCourse.nStudents; i++) {
			getline(fin, inCourse.studentArr[i].ID);
			getline(fin, inCourse.studentArr[i].fullname);
			getline(fin, line);
			inCourse.studentArr[i].gender = line.front();
			getline(fin, line);
			inCourse.studentArr[i].birthDate = sToDate(line);
			getline(fin, line);
			inCourse.studentArr[i].active = stoi(line);
			fin.ignore(INT_MAX, '\n');
			if (inCourse.studentArr[i].active == false)
				nInactive++;
		}
		fin.close();
	}

	//* Get nWeeks and date array from startDate and endDate (including startDate and endDate in array)
	tm* dateArr = getWeeks(inCourse.startDate, inCourse.endDate, &inCourse.nWeeks);
	if (dateArr == nullptr) {
		cerr << "Can't calculate dates between starting date and ending date of the course!" << endl;
		delete[] inCourse.studentArr;
		return false;
	}

	//* Save the student array to [Year]_[Semester]_[CourseID]_[ClassID]_Students.txt
	//  ^ along with default scoreboards of -1 and nWeeks and date array and default check lists of 0 for each student
	Path = "./TextFiles/" + inCourse.c_semester.year + '_' + inCourse.c_semester.semester + '_' + inCourse.courseID + '_' + inCourse.className + "_Students.txt";
	if (emptyFile(Path)) {
		fout.open(Path);
		if (!fout.is_open()) {
			cerr << "Can't generate the student list!" << endl;
			delete[] inCourse.studentArr;
			delete[] dateArr;
			return false;
		}
		fout << inCourse.nWeeks << endl
			<< inCourse.nStudents << endl;
		for (int i = 0; i < inCourse.nStudents; i++) {
			fout << inCourse.studentArr[i].ID << endl
				<< inCourse.studentArr[i].fullname << endl
				<< inCourse.studentArr[i].gender << endl;
			printDate(fout, inCourse.studentArr[i].birthDate);
			fout << inCourse.studentArr[i].active << endl;
			for (int j = 0; j < 4; j++)
				fout << -1 << endl;
			for (int j = 0; j < inCourse.nWeeks; j++)
				fout << put_time(&dateArr[j], "%Y-%m-%d") << " 0" << endl;
			fout << endl;
		}
		fout.close();
	}
	else {
		cout << "The student list for this course already existed. Do you want to overwrite it with a new default list?" << endl;
		cout << "1. Yes / 0. No" << endl;
		int choice;
		cout << "Enter a number for your choice: ";
		cin >> choice;
		if (!cin || choice < 0 || choice > 1) {
			cerr << "Invalid input!" << endl;
			flushin(cin);
			cout << "Enter a number for your choice: ";
			cin >> choice;
		}
		flushin(cin);
		if (choice == 0) {
			cout << "The process has been stopped!" << endl;
			delete[] inCourse.studentArr;
			delete[] dateArr;
			return false;
		}
		if (choice == 1) {
			fout.open(Path);
			if (!fout.is_open()) {
				cerr << "Can't generate the student list!" << endl;
				delete[] inCourse.studentArr;
				delete[] dateArr;
				return false;
			}
			fout << inCourse.nWeeks << endl
				<< inCourse.nStudents << endl;
			for (int i = 0; i < inCourse.nStudents; i++) {
				fout << inCourse.studentArr[i].ID << endl
					<< inCourse.studentArr[i].fullname << endl
					<< inCourse.studentArr[i].gender << endl;
				printDate(fout, inCourse.studentArr[i].birthDate);
				fout << inCourse.studentArr[i].active << endl;
				for (int j = 0; j < 4; j++)
					fout << -1 << endl;
				for (int j = 0; j < inCourse.nWeeks; j++)
					fout << put_time(&dateArr[j], "%Y-%m-%d") << " 0" << endl;
				fout << endl;
			}
			fout.close();
		}
	}

	//* Add this course to register course list of each student in [Year]_[Semester]_Student Courses.txt
	Path = "./TextFiles/" + inCourse.c_semester.year + '_' + inCourse.c_semester.semester + "_Student Courses.txt";
	//If the file hasn't been created
	if (emptyFile(Path)) {
		fout.open(Path);
		if (!fout.is_open()) {
			cerr << "Can't add this course to the list!" << endl;
			delete[] inCourse.studentArr;
			delete[] dateArr;
			return false;
		}
		fout << inCourse.nStudents - nInactive << endl;
		for (int i = 0; i < inCourse.nStudents; i++) {
			if (inCourse.studentArr[i].active == false) continue; //Inactive students won't be registered with the course
			fout << inCourse.studentArr[i].ID << endl
				<< inCourse.studentArr[i].fullname << endl
				<< inCourse.className << endl
				<< 1 << endl
				<< inCourse.courseID << ' ' << inCourse.className << endl;
			fout << endl;
		}
		fout.close();
	}
	else {
		//If the file already existed, load it to an array of RegCourses
		int nReg; //Number of students recorded in the file
		bool addedClass = false; //Flag to check if the class are already recorded
		bool* sameCourse; //Flag to check if a recorded student already enrolled in the same course of different class
		fin.open(Path);
		getline(fin, line);
		nReg = stoi(line);
		RegCourses* regStudents = new RegCourses[nReg];
		sameCourse = new bool[nReg] {false}; //This flag uses the same iterator as regStudents to check the recorded students
		for (int i = 0; i < nReg; i++) {
			getline(fin, regStudents[i].studentID);
			getline(fin, regStudents[i].studentName);
			getline(fin, regStudents[i].studentClass);
			if (regStudents[i].studentClass == inCourse.className) addedClass = true;
			getline(fin, line);
			regStudents[i].nCourses = stoi(line);
			regStudents[i].courseID = new string[regStudents[i].nCourses];
			regStudents[i].classID = new string[regStudents[i].nCourses];
			for (int j = 0; j < regStudents[i].nCourses; j++) {
				getline(fin, regStudents[i].courseID[j], ' ');
				getline(fin, regStudents[i].classID[j]);
				//In case the student is in this class but already enrolled in the same course of another class
				if (regStudents[i].courseID[j] == inCourse.courseID) sameCourse[i] = true;
			}
			fin.ignore(INT_MAX, '\n');
		}
		fin.close();

		//Write new course to the Enrolled Courses list of the recorded students
		fout.open(Path);
		if (addedClass == false) {
			//If the class hasn't been record
			fout << nReg + inCourse.nStudents - nInactive << endl;
			for (int i = 0; i < nReg; i++) {	//Output existed regStudents
				fout << regStudents[i].studentID << endl
					<< regStudents[i].studentName << endl
					<< regStudents[i].studentClass << endl
					<< regStudents[i].nCourses << endl;
				for (int j = 0; j < regStudents[i].nCourses; j++)
					fout << regStudents[i].courseID[j] << ' ' << regStudents[i].classID[j] << endl;
				fout << endl;
			}
			for (int i = 0; i < inCourse.nStudents; i++) {	//Add studentArr of this class with a new course
				if (inCourse.studentArr[i].active == false) continue; //Inactive students won't be registered with the course
				fout << inCourse.studentArr[i].ID << endl
					<< inCourse.studentArr[i].fullname << endl
					<< inCourse.className << endl
					<< 1 << endl
					<< inCourse.courseID << ' ' << inCourse.className << endl;
				fout << endl;
			}
		}
		if (addedClass == true) {
			//If the class has been recorded
			fout << nReg << endl;
			for (int i = 0; i < nReg; i++) {	//Output existed regStudents
				fout << regStudents[i].studentID << endl
					<< regStudents[i].studentName << endl
					<< regStudents[i].studentClass << endl;
				if (regStudents[i].studentClass == inCourse.className && sameCourse[i] == false) {
					//If it's the student in the class and they haven't enrolled in the course
					fout << regStudents[i].nCourses + 1 << endl;
					fout << inCourse.courseID << ' ' << inCourse.className << endl;
				}
				else fout << regStudents[i].nCourses << endl;
				for (int j = 0; j < regStudents[i].nCourses; j++)
					fout << regStudents[i].courseID[j] << ' ' << regStudents[i].classID[j] << endl;
				fout << endl;
			}
		}
		fout.close();
		//REMEMBER TO DELETE THE ARRAY INSIDE EACH STRUCT ELEMENT AND THE STRUCT ARRAY ITSELF
		delete[] sameCourse;
		for (int i = 0; i < nReg; i++) {
			delete[] regStudents[i].classID;
			delete[] regStudents[i].courseID;
		}
		delete[] regStudents;
	}
	//Function only returns true after all processes are done, student array of input class and date array are deleted 
	delete[] inCourse.studentArr;
	delete[] dateArr;
	return true;
}

bool importCourse(Semester curSem) {
	ifstream fin;
	ofstream fout;
	string line, lecturerUsername, csvPath;
	Course inCourse;
	cout << "Enter csv file path: ";
	getline(cin, csvPath);
	inCourse.c_semester = curSem;
	if (emptyFile(csvPath)) {
		cerr << "Can't find data in the path you entered!" << endl;
		return false;
	}
	else {
		fin.open(csvPath);
		fin.ignore(INT_MAX, '\n'); //Ignore the first row that contains the column titles
		while (getline(fin, line, ';')) {
			getline(fin, inCourse.courseID, ';');
			getline(fin, inCourse.courseName, ';');
			getline(fin, inCourse.className, ';');
			getline(fin, lecturerUsername, ';');
			getline(fin, inCourse.courseLecturer.fullname, ';');
			getline(fin, inCourse.courseLecturer.email, ';');
			getline(fin, inCourse.courseLecturer.academicRank, ';');
			getline(fin, line, ';');
			inCourse.courseLecturer.gender = line.front();
			getline(fin, line, ';');
			inCourse.startDate = sToDate(line);
			getline(fin, line, ';');
			inCourse.endDate = sToDate(line);
			getline(fin, inCourse.classDay, ';');
			getline(fin, line, ';');
			inCourse.startTime = sToTime(line);
			getline(fin, line, ';');
			inCourse.endTime = sToTime(line);
			getline(fin, inCourse.room);
			cout << "\nAdding course " << inCourse.courseID << " of class " << inCourse.className << " ..." << endl;
			if (!addCourse(inCourse, lecturerUsername)) {
				cerr << "Can't add a course of this file to the program!" << endl;
				return false;
			}
			else cout << "Course " << inCourse.courseID << " of class " << inCourse.className << " has been added!" << endl;
		}
		fin.close();
		return true;
	}
}

void readRegCourses(ifstream& fin, RegCourses*& regStudents, int& nReg) {
	string line;
	getline(fin, line);
	nReg = stoi(line);
	if (nReg == 0) {
		regStudents = nullptr;
		return;
	}
	regStudents = new RegCourses[nReg];
	for (int i = 0; i < nReg; i++) {
		getline(fin, regStudents[i].studentID);
		getline(fin, regStudents[i].studentName);
		getline(fin, regStudents[i].studentClass);
		getline(fin, line);
		regStudents[i].nCourses = stoi(line);
		if (regStudents[i].nCourses != 0) {
			regStudents[i].courseID = new string[regStudents[i].nCourses];
			regStudents[i].classID = new string[regStudents[i].nCourses];
			for (int j = 0; j < regStudents[i].nCourses; j++) {
				getline(fin, regStudents[i].courseID[j], ' ');
				getline(fin, regStudents[i].classID[j]);
			}
		}
		fin.ignore(INT_MAX, '\n');
	}
}

bool removeRegCourse(string path, string courseID, string classID) {
	ifstream fin;
	ofstream fout;
	RegCourses* reg = nullptr;
	int nReg;
	fin.open(path);
	if (emptyFile(path)) {
		cerr << "Can't access the list of student courses!" << endl;
		return false;
	}
	readRegCourses(fin, reg, nReg);
	fin.close();

	if (reg != nullptr) {
		fout.open(path);
		if (!fout.is_open() || fout.fail()) {
			cerr << "Error while rewriting the Student Courses!" << endl;
			return false;
		}
		fout << nReg << endl;
		for (int i = 0; i < nReg; i++) {
			bool haveCourse = false;	//Flag to check if the student enrolled in the removed course
			fout << reg[i].studentID << endl;
			fout << reg[i].studentName << endl;
			fout << reg[i].studentClass << endl;
			//Scan the course list of student i to check if they have the course
			for (int j = 0; j < reg[i].nCourses && haveCourse == false; j++) {
				if (reg[i].courseID[j] == courseID && reg[i].classID[j] == classID)
					haveCourse = true;
			}
			//Print the new course list if they have the course
			if (haveCourse) fout << reg[i].nCourses - 1 << endl;
			else fout << reg[i].nCourses << endl;
			for (int j = 0; j < reg[i].nCourses; j++) {
				if (reg[i].courseID[j] != courseID || reg[i].classID[j] != classID)
					fout << reg[i].courseID[j] << ' ' << reg[i].classID[j] << endl;
			}
			fout << endl;
		}
		fout.close();
		
		//Delete reg array after everything is done
		for (int i = 0; i < nReg; i++) {
			if (reg[i].nCourses != 0) {
				delete[] reg[i].courseID;
				delete[] reg[i].classID;
			}
		}
		delete[] reg;
		return true;
	}
	return false; //If no reg array
}

void readCoursesInfos(ifstream& fin, string*& slack, Course*& courseArr, int& nCourses) {
	string line;
	getline(fin, line);
	nCourses = stoi(line);
	if (nCourses == 0) {
		slack = nullptr;
		courseArr = nullptr;
		return;
	}
	courseArr = new Course[nCourses];
	slack = new string[nCourses];
	for (int i = 0; i < nCourses; i++) {
		getline(fin, courseArr[i].courseID);
		getline(fin, courseArr[i].courseName);
		getline(fin, slack[i]);
		getline(fin, courseArr[i].courseLecturer.fullname);
		getline(fin, courseArr[i].courseLecturer.email);
		getline(fin, courseArr[i].courseLecturer.academicRank);
		getline(fin, line);
		courseArr[i].courseLecturer.gender = line.front();
		getline(fin, line);
		courseArr[i].startDate = sToDate(line);
		getline(fin, line);
		courseArr[i].endDate = sToDate(line);
		getline(fin, courseArr[i].classDay);
		getline(fin, line);
		courseArr[i].startTime = sToTime(line);
		getline(fin, line);
		courseArr[i].endTime = sToTime(line);
		getline(fin, courseArr[i].room);
		fin.ignore(INT_MAX, '\n');
	}
}

bool findACourseInfos(ifstream& fin, Course &crs, string crsID, string* lecturerAcc) {
	string line;
	getline(fin, line);
	int nCourses = stoi(line);
	if (nCourses == 0) return false;
	for (int i = 0; i < nCourses; i++) {
		getline(fin, crs.courseID);
		if (crs.courseID == crsID) {
			getline(fin, crs.courseName);
			if (lecturerAcc != nullptr) getline(fin, *lecturerAcc);
			else fin.ignore(INT_MAX, '\n');
			getline(fin, crs.courseLecturer.fullname);
			getline(fin, crs.courseLecturer.email);
			getline(fin, crs.courseLecturer.academicRank);
			getline(fin, line);
			crs.courseLecturer.gender = line.front();
			getline(fin, line);
			crs.startDate = sToDate(line);
			getline(fin, line);
			crs.endDate = sToDate(line);
			getline(fin, crs.classDay);
			getline(fin, line);
			crs.startTime = sToTime(line);
			getline(fin, line);
			crs.endTime = sToTime(line);
			getline(fin, crs.room);
			return true;
		}
		else {
			for (int j = 0; j < 13; j++)
				fin.ignore(INT_MAX, '\n');
		}
	}
	return false;
}

bool removeCourse() {
	ifstream fin;
	ofstream fout;
	Course target;
	cout << "ENTER THE INFO TO FIND THE COURSE: " << endl;
	viewSemesterList();
	cout << "- Academic year: ";
	getline(cin, target.c_semester.year);
	cout << "- Semester: ";
	getline(cin, target.c_semester.semester);
	if (!viewClasses()) {
		cout << "There are no class in the system!" << endl;
		return false;
	}
	int n;
	string* classes = readClassesID("./TextFiles/Classes.txt", &n);
	cout << "Enter class ID: ";
	getline(cin, target.className);
	bool flag = false;
	for (int i = 0; i < n && flag == false; i++) {
		if (target.className == classes[i])
			flag = true;
	}
	while (!flag) {
		cout << "Enter existing class: ";
		getline(cin, target.className);
		for (int i = 0; i < n && flag == false; i++) {
			if (target.className == classes[i])
				flag = true;
		}
	}
	delete[] classes;
	classes = nullptr;
	cout << "- Course ID: ";
	getline(cin, target.courseID);
	//Remove the course recorded in the student enrollment list
	string path = "./TextFiles/" + target.c_semester.year + '_' + target.c_semester.semester + "_Student Courses.txt";
	if (!removeRegCourse(path, target.courseID, target.className)) {
		cerr << "Can't remove the course recorded in the student enrollment list!" << endl;
		return false;
	}
	//Remove course info
	path = "./TextFiles/" + target.c_semester.year + '_' + target.c_semester.semester + '_' + target.className + "_Schedules.txt";
	fin.open(path);
	if (emptyFile(path)) {
		cerr << "Can't access course data of this class!" << endl;
		return false;
	}
	int nCourses;
	string* slack;
	Course* courseArr;
	readCoursesInfos(fin, slack, courseArr, nCourses);
	fin.close();
	bool haveCourse = false;
	if (slack != nullptr && courseArr != nullptr) {
		for (int i = 0; i < nCourses && haveCourse == false; i++) {
			if (courseArr[i].courseID == target.courseID)
				haveCourse = true;
		}
	}
	if (haveCourse == true) {
		if (nCourses - 1 == 0) {
			if (remove(path.c_str()) != 0) {
				cerr << "Can't delete the course info!" << endl;
				return false;
			}
		}
		else {
			fout.open(path);
			if (!fout.is_open() || fout.fail()) {
				cerr << "Can't rewrite the course data of this class!" << endl;
				return false;
			}
			fout << nCourses - 1 << endl;
			for (int i = 0; i < nCourses; i++) {
				if (courseArr[i].courseID != target.courseID) {
					fout << courseArr[i].courseID << endl
						<< courseArr[i].courseName << endl
						<< slack[i] << endl
						<< courseArr[i].courseLecturer.fullname << endl
						<< courseArr[i].courseLecturer.email << endl
						<< courseArr[i].courseLecturer.academicRank << endl
						<< courseArr[i].courseLecturer.gender << endl;
					printDate(fout, courseArr[i].startDate);
					printDate(fout, courseArr[i].endDate);
					fout << courseArr[i].classDay << endl;
					printTime(fout, courseArr[i].startTime);
					printTime(fout, courseArr[i].endTime);
					fout << courseArr[i].room << endl;
					fout << endl;
				}
			}
			fout.close();
		}
	}
	else {
		cout << "The course does not exist in this class!" << endl;
		return false;
	}
	if (slack != nullptr && courseArr != nullptr) {
		delete[] slack;
		delete[] courseArr;
	}
	//Remove student list of this course
	path = "./TextFiles/" + target.c_semester.year + '_' + target.c_semester.semester + '_' + target.courseID + '_' + target.className + "_Students.txt";
	if (remove(path.c_str()) != 0) {
		cerr << "Can't delete the student list of this course!" << endl;
		return false;
	}
	//If everything is done successfully
	return true;
}

bool editCourse() {
	ifstream fin;
	ofstream fout;
	Semester sem;
	string inputCourseID, inputClassID, line;
	cout << "ENTER THE INFO TO FIND THE COURSE: " << endl;
	viewSemesterList();
	cout << "- Academic year: ";
	getline(cin, sem.year);
	cout << "- Semester: ";
	getline(cin, sem.semester);
	if (!viewClasses()) {
		cout << "There are no class in the system!" << endl;
		return false;
	}
	int n;
	string* classes = readClassesID("./TextFiles/Classes.txt", &n);
	cout << "Enter class ID: ";
	getline(cin, inputClassID);
	bool flag = false;
	for (int i = 0; i < n && flag == false; i++) {
		if (inputClassID == classes[i])
			flag = true;
	}
	while (!flag) {
		cout << "Enter existing class: ";
		getline(cin, inputClassID);
		for (int i = 0; i < n && flag == false; i++) {
			if (inputClassID == classes[i])
				flag = true;
		}
	}
	delete[] classes;
	classes = nullptr;
	cout << "- Course ID: ";
	getline(cin, inputCourseID);
	//Load the courses info
	string path = "./TextFiles/" + sem.year + '_' + sem.semester + '_' + inputClassID + "_Schedules.txt";
	fin.open(path);
	if (emptyFile(path)) {
		cerr << "Can't access course data of this class!" << endl;
		return false;
	}
	int nCourses;
	string* slack;
	Course* courseArr;
	readCoursesInfos(fin, slack, courseArr, nCourses);
	fin.close();
	if (slack == nullptr && courseArr == nullptr) {
		cerr << "There's no course recorded for this class!" << endl;
		return false;
	}
	//Find the course to edit
	int cpos = -1;
	for (int i = 0; i < nCourses && cpos == -1; i++) {
		if (inputCourseID == courseArr[i].courseID)
			cpos = i;
	}
	if (cpos == -1) {
		cerr << "Can't find the course!" << endl;
		delete[] courseArr;
		return false;
	}
	int choice = 0;
	while (choice != 4) {
		//View current info
		cout << "\n* Current course info *" << endl;
		cout << "Course name: " << courseArr[cpos].courseName << endl;
		cout << "Lecturer's account: " << slack[cpos] << endl;
		cout << "Lecturer's name: " << courseArr[cpos].courseLecturer.fullname << endl;
		cout << "Lecturer's email: " << courseArr[cpos].courseLecturer.email << endl;
		cout << "Lecturer's degree: " << courseArr[cpos].courseLecturer.academicRank << endl;
		cout << "Lecturer's gender (M = Male/F = Female): " << courseArr[cpos].courseLecturer.gender << endl;
		cout << "Course dates (YYYY-MM-DD): " << put_time(&courseArr[cpos].startDate, "%Y-%m-%d") << " - " << put_time(&courseArr[cpos].endDate, "%Y-%m-%d") << endl;
		cout << "Course time (HH:MM): " << put_time(&courseArr[cpos].startTime, "%H:%M") << " - " << put_time(&courseArr[cpos].endTime, "%H:%M") << endl;
		cout << "Course Day of Week: " << courseArr[cpos].classDay << endl;
		cout << "Course room: " << courseArr[cpos].room << endl;
		//Select info to edit
		cout << "\nSelect what you want to edit:" << endl;
		cout << "1 - Course name and room" << endl;
		cout << "2 - Course lecturer" << endl;
		cout << "3 - Course schedule (WARNING: THIS WILL RESET THE ATTENDANCE LIST OF THE COURSE)" << endl;
		cout << "4 - Stop editing and Save all changes" << endl;
		cout << "Enter a number for your choice: ";
		cin >> choice;
		while (!cin || choice < 1 || choice > 4) {
			cerr << "Invalid input!" << endl;
			flushin(cin);
			cout << "Enter a number for your choice: ";
			cin >> choice;
		}
		flushin(cin);
		if (choice == 1) {
			cout << "Enter new course name: ";
			getline(cin, courseArr[cpos].courseName);
			cout << "Enter new course room: ";
			getline(cin, courseArr[cpos].room);
		}
		if (choice == 2) {
			Lecturer inputLecturer;
			cout << "Enter lecturer account: ";
			getline(cin, slack[cpos]);
			cout << "Enter lecturer full name: ";
			getline(cin, inputLecturer.fullname);
			string LecturerPath = "./TextFiles/Lecturers.txt";
			if (emptyFile(LecturerPath)) {
				//If Lecturers.txt hasn't been created or is empty
				fout.open(LecturerPath);
				if (!fout.is_open()) {
					cerr << "Can't update lecturer account!" << endl;
					delete[] courseArr;
					return false;
				}
				fout << 1 << endl;
				fout << slack[cpos] << endl
					<< sha256(slack[cpos] + "_HCMUS") << endl
					<< inputLecturer.fullname << endl
					<< inputLecturer.email << endl
					<< inputLecturer.academicRank << endl
					<< inputLecturer.gender << endl;
				fout << endl;
				fout.close();
			}
			else {
				//Store data file into account array and check if the lecturer account has been created before
				fin.open(LecturerPath);
				Account* userArr;
				int nLecturers;
				bool sameLecturer = false; //Flag to check if it's new account
				getline(fin, line);
				nLecturers = stoi(line) + 1;
				userArr = new Account[nLecturers];
				for (int i = 0; i < nLecturers - 1 && sameLecturer == false; i++) {
					getline(fin, userArr[i].username);
					getline(fin, userArr[i].password);
					getline(fin, userArr[i].lecturerProfile.fullname);
					getline(fin, userArr[i].lecturerProfile.email);
					getline(fin, userArr[i].lecturerProfile.academicRank);
					getline(fin, line);
					userArr[i].lecturerProfile.gender = line.front(); //Get first character of the gender string 'F' or 'M'
					fin.ignore(INT_MAX, '\n'); //This one is to skip the blank line
					if (userArr[i].username == slack[cpos] && userArr[i].lecturerProfile.fullname == inputLecturer.fullname) {
						cout << "\n\nThe lecturer's account is available in the system. Proceed to load account info to the course..." << endl;
						sameLecturer = true;
						//If lecturer already has an account, load that account to the course info
						inputLecturer = userArr[i].lecturerProfile;
					}
				}
				fin.close();
				//Input new lecturer as last element in the array and write new array to file
				if (sameLecturer == false) {
					cout << "Detected a new lecturer. Please enter new information for this lecturer's account." << endl;
					cout << "Enter new lecturer email: ";
					getline(cin, inputLecturer.email);
					cout << "Enter new lecturer degree (Master/PhD/Professor): ";
					getline(cin, inputLecturer.academicRank);
					cout << "Enter new lecturer gender (Male/Female): ";
					getline(cin, line);
					inputLecturer.gender = line.front();
					userArr[nLecturers - 1].username = slack[cpos];
					userArr[nLecturers - 1].password = sha256(slack[cpos] + "_HCMUS");
					userArr[nLecturers - 1].lecturerProfile = inputLecturer;
					fout.open(LecturerPath);
					if (!fout.is_open()) {
						cerr << "Can't update lecturer's account!" << endl;
						delete[] courseArr;
						delete[] userArr;
						return false;
					}
					fout << nLecturers << endl;
					for (int i = 0; i < nLecturers; i++) {	//Rewrite existed accounts and new account
						fout << userArr[i].username << endl
							<< userArr[i].password << endl
							<< userArr[i].lecturerProfile.fullname << endl
							<< userArr[i].lecturerProfile.email << endl
							<< userArr[i].lecturerProfile.academicRank << endl
							<< userArr[i].lecturerProfile.gender << endl;
						fout << endl;
					}
					fout.close();
				}
				//After reading and writing, release the memory of array
				delete[] userArr;
				userArr = nullptr;
			}
			courseArr[cpos].courseLecturer = inputLecturer;
		}
		if (choice == 3) {
			cout << "Enter new start date of course (YYYY-MM-DD): ";
			cin >> get_time(&courseArr[cpos].startDate, "%Y-%m-%d");
			if (!cin) {
				cerr << "Invalid input!" << endl;
				flushin(cin);
				cout << "Enter new start date of course (YYYY-MM-DD): ";
				cin >> get_time(&courseArr[cpos].startDate, "%Y-%m-%d");
			}
			flushin(cin);
			cout << "Enter new end date of course (YYYY-MM-DD): ";
			cin >> get_time(&courseArr[cpos].endDate, "%Y-%m-%d");
			if (!cin) {
				cerr << "Invalid input!" << endl;
				flushin(cin);
				cout << "Enter new end date of course (YYYY-MM-DD): ";
				cin >> get_time(&courseArr[cpos].endDate, "%Y-%m-%d");
			}
			flushin(cin);
			cout << "Enter new course day of week (Shorten form: Thu, Fri,...): ";
			getline(cin, courseArr[cpos].classDay);
			cout << "Enter new start time of course (HH:MM): ";
			cin >> get_time(&courseArr[cpos].startTime, "%H:%M");
			if (!cin) {
				cerr << "Invalid input!" << endl;
				flushin(cin);
				cout << "Enter new start time of course (HH:MM): ";
				cin >> get_time(&courseArr[cpos].startTime, "%H:%M");
			}
			flushin(cin);
			cout << "Enter new end time of course (HH:MM): ";
			cin >> get_time(&courseArr[cpos].endTime, "%H:%M");
			if (!cin) {
				cerr << "Invalid input!" << endl;
				flushin(cin);
				cout << "Enter new start time of course (HH:MM): ";
				cin >> get_time(&courseArr[cpos].endTime, "%H:%M");
			}
			flushin(cin);
			tm* dateArr = getWeeks(courseArr[cpos].startDate, courseArr[cpos].endDate, &courseArr[cpos].nWeeks);
			if (dateArr == nullptr) {
				cerr << "Can't get dates between the new start date and end date!" << endl;
				delete[] courseArr;
				return false;
			}
			string StudentPath = "./TextFiles/" + sem.year + '_' + sem.semester + '_' + inputCourseID + '_' + inputClassID + "_Students.txt";
			fin.open(StudentPath);
			if (emptyFile(path)) {
				cerr << "Can't find the attendance list of this course!" << endl;
				delete[] courseArr;
				delete[] dateArr;
				return false;
			}
			int oldWeeks;
			getline(fin, line);
			oldWeeks = stoi(line);
			getline(fin, line);
			courseArr[cpos].nStudents = stoi(line);
			courseArr[cpos].studentArr = new Student[courseArr[cpos].nStudents];
			courseArr[cpos].board = new score[courseArr[cpos].nStudents];
			for (int i = 0; i < courseArr[cpos].nStudents; i++) {
				getline(fin, courseArr[cpos].studentArr[i].ID);
				getline(fin, courseArr[cpos].studentArr[i].fullname);
				getline(fin, line);
				courseArr[cpos].studentArr[i].gender = line.front();
				getline(fin, line);
				courseArr[cpos].studentArr[i].birthDate = sToDate(line);
				getline(fin, line);
				courseArr[cpos].studentArr[i].active = stoi(line);
				getline(fin, line);
				courseArr[cpos].board[i].midterm = stof(line);
				getline(fin, line);
				courseArr[cpos].board[i].final = stof(line);
				getline(fin, line);
				courseArr[cpos].board[i].bonus = stof(line);
				getline(fin, line);
				courseArr[cpos].board[i].total = stof(line);
				for (int j = 0; j < oldWeeks + 1; j++)
					fin.ignore(INT_MAX, '\n');
			}
			fin.close();

			fout.open(StudentPath);
			if (!fout.is_open() || fout.fail()) {
				cout << "Failed to reset the attendance list!" << endl;
				delete[] courseArr[cpos].studentArr;
				delete[] courseArr[cpos].board;
				delete[] courseArr;
				delete[] dateArr;
				return false;
			}
			fout << courseArr[cpos].nWeeks << endl;
			fout << courseArr[cpos].nStudents << endl;
			for (int i = 0; i < courseArr[cpos].nStudents; i++) {
				fout << courseArr[cpos].studentArr[i].ID << endl
					<< courseArr[cpos].studentArr[i].fullname << endl
					<< courseArr[cpos].studentArr[i].gender << endl
					<< put_time(&courseArr[cpos].studentArr[i].birthDate, "%Y-%m-%d") << endl
					<< courseArr[cpos].studentArr[i].active << endl
					<< courseArr[cpos].board[i].midterm << endl
					<< courseArr[cpos].board[i].final << endl
					<< courseArr[cpos].board[i].bonus << endl
					<< courseArr[cpos].board[i].total << endl;
				for (int j = 0; j < courseArr[cpos].nWeeks; j++)
					fout << put_time(&dateArr[j], "%Y-%m-%d") << " 0" << endl;
				fout << endl;
			}
			fout.close();
			delete[] courseArr[cpos].studentArr;
			delete[] courseArr[cpos].board;
			delete[] dateArr;
		}
	}
	//Rewrite the course info file
	fout.open(path);
	if (!fout.is_open() || fout.fail()) {
		cerr << "Can't update course info!" << endl;
		delete[] courseArr;
		return false;
	}
	fout << nCourses << endl;
	for (int i = 0; i < nCourses; i++) {
		fout << courseArr[i].courseID << endl
			<< courseArr[i].courseName << endl
			<< slack[i] << endl
			<< courseArr[i].courseLecturer.fullname << endl
			<< courseArr[i].courseLecturer.email << endl
			<< courseArr[i].courseLecturer.academicRank << endl
			<< courseArr[i].courseLecturer.gender << endl
			<< put_time(&courseArr[i].startDate, "%Y-%m-%d") << endl
			<< put_time(&courseArr[i].endDate, "%Y-%m-%d") << endl
			<< courseArr[i].classDay << endl
			<< put_time(&courseArr[i].startTime, "%H:%M") << endl
			<< put_time(&courseArr[i].endTime, "%H:%M") << endl
			<< courseArr[i].room << endl;
		fout << endl;
	}
	fout.close();
	delete[] courseArr;
	return true;
}

bool addCourseStudent(Semester curSem, cmpr orderStu, cmpr orderAcc) {
	string line, path;
	string sysPath = "./TextFiles/";
	ifstream fin;
	ofstream fout;
	Course crs;
	Student newStu;
	//- Get current semester from the system, course ID and course class from user
	crs.c_semester = curSem;
	cout << "Enter course ID: ";
	getline(cin, crs.courseID);
	cout << "Enter class ID of the course: ";
	getline(cin, crs.className);
	//- Find and load the course info
	path = sysPath + curSem.year + '_' + curSem.semester + '_' + crs.className + "_Schedules.txt";
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
	//- Get student ID and ask if the student is from an existed class or a class not in the system
	cout << "Enter student ID: ";
	getline(cin, newStu.ID);
	if (!viewClasses()) cout << "There's currently no class in the system!" << endl;
	cout << "Enter student class ID (Enter \"0\" if the student isn't from any existing class): ";
	getline(cin, newStu.classID);
	//- If they are from an existed class: Go the the class' student list and load the student infos
	bool foundStu = false;
	if (newStu.classID != "0") {
		path = sysPath + newStu.classID + "_Students.txt";
		if (emptyFile(path)) {
			cerr << "Can't find the student!" << endl;
			return false;
		}
		fin.open(path);
		getline(fin, line);
		int nStu = stoi(line);
		for (int i = 0; i < nStu && foundStu == false; i++) {
			getline(fin, line);
			if (line == newStu.ID) {
				getline(fin, newStu.fullname);
				getline(fin, line);
				newStu.gender = line.front();
				getline(fin, line);
				newStu.birthDate = sToDate(line);
				getline(fin, line);
				newStu.active = stoi(line);
				foundStu = true;
			}
			else {
				for (int j = 0; j < 5; j++)
					fin.ignore(INT_MAX, '\n');
			}
		}
		fin.close();
		if (foundStu == false) {
			cerr << "Can't find the student!" << endl;
			return false;
		}
	}
	//- If they are not from any class in the system:
	//		+ If found their account, load the student info from their account
	//		+ If can't find their account, take student info from user input (student class = 0) and create new account
	else {
		//Register student account
		path = sysPath + "Students.txt";
		if (emptyFile(path)) {
			fout.open(path);
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
			fin.open(path);
			int nStu;
			getline(fin, line);
			nStu = stoi(line);
			Account* oldStu;
			oldStu = new Account[nStu + 1];
			for (int i = 0; i < nStu; i++) {
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

			bool sameID = false;
			for (int i = 0; i < nStu && sameID == false; i++) {
				if (newStu.ID == oldStu[i].username) {
					newStu.fullname = oldStu[i].studentProfile.fullname;
					newStu.gender = oldStu[i].studentProfile.gender;
					newStu.birthDate = oldStu[i].studentProfile.birthDate;
					newStu.active = oldStu[i].studentProfile.active;
					sameID = true;
				}
			}
			fout.open(path);
			if (!fout.is_open()) {
				cerr << "Can't register student account!" << endl;
				delete[] oldStu;
				oldStu = nullptr;
				return false;
			}
			if (!sameID) {
				cout << "Enter student full name: ";
				getline(cin, newStu.fullname);
				cout << "Enter student gender (Male/Female): ";
				getline(cin, line);
				newStu.gender = line.front();
				cout << "Enter student birth date (YYYY-MM-DD): ";
				cin >> get_time(&newStu.birthDate, "%Y-%m-%d");
				if (!cin) {
					cerr << "Invalid input!" << endl;
					flushin(cin);
					cout << "Enter student birth date (YYYY-MM-DD): ";
					cin >> get_time(&newStu.birthDate, "%Y-%m-%d");
				}
				flushin(cin);
				newStu.active = true;
				oldStu[nStu].username = newStu.ID;
				char temp[9];
				strftime(temp, 9, "%Y%m%d", &newStu.birthDate);
				line.assign(temp);
				oldStu[nStu].password = sha256(line);
				oldStu[nStu].studentProfile = newStu;
				sortAccount(oldStu, 0, nStu, orderAcc);	//Sort the array in ascending order before output to the file
				fout << nStu + 1 << endl;
			}
			else fout << nStu << endl;
			for (int j = 0; j < nStu + 1; j++) {
				if (j == nStu && sameID == true) break;
				fout << oldStu[j].username << endl
					<< oldStu[j].password << endl
					<< oldStu[j].studentProfile.fullname << endl
					<< oldStu[j].studentProfile.classID << endl
					<< oldStu[j].studentProfile.gender << endl;
				printDate(fout, oldStu[j].studentProfile.birthDate);
				fout << oldStu[j].studentProfile.active << endl;
				fout << endl;
			}
			fout.close();
			delete[] oldStu;
			oldStu = nullptr;
		}
	}
	//- Load the course students to an array: if new student id is inbetween student i-1 and i, push student i to i+1 and place new student at i
	tm* dateArr = getWeeks(crs.startDate, crs.endDate, &crs.nWeeks);
	if (dateArr == nullptr || crs.nWeeks <= 0) {
		cerr << "Error getting schedule of the course!" << endl;
		return false;
	}
	path = sysPath + curSem.year + '_' + curSem.semester + '_' + crs.courseID + '_' + crs.className + "_Students.txt";
	if (emptyFile(path)) {
		fout.open(path);
		if (!fout.is_open() || fout.fail()) {
			cerr << "Error while adding new student entry to the course files!" << endl;
			delete[] dateArr;
			return false;
		}
		fout << crs.nWeeks << endl
			<< 1 << endl
			<< newStu.ID << endl
			<< newStu.fullname << endl
			<< newStu.gender << endl
			<< put_time(&newStu.birthDate, "%Y-%m-%d") << endl
			<< newStu.active << endl;
		for (int i = 0; i < 4; i++)
			fout << -1 << endl;
		for (int i = 0; i < crs.nWeeks; i++)
			fout << put_time(&dateArr[i], "%Y-%m-%d") << " 0" << endl;
		fout << endl;
		fout.close();
		delete[] dateArr;
	}
	else {
		foundStu = false;
		bool insertedStu = false;
		fin.open(path);
		fin.ignore(INT_MAX, '\n'); //Skip line contains nWeeks
		getline(fin, line);
		crs.nStudents = stoi(line) + 1;
		crs.studentArr = new Student[crs.nStudents];	//1D arr
		crs.board = new score[crs.nStudents];	//1D arr, default value of all scores is -1
		crs.checkList = new bool[crs.nWeeks * crs.nStudents]{false};	//2D arr, default value of all elements is false
		for (int i = 0; i < crs.nStudents; i++) {
			getline(fin, crs.studentArr[i].ID);
			if (crs.studentArr[i].ID == newStu.ID) {
				foundStu = true;	//Do not allow adding a duplicate student
				break;
			}
			getline(fin, crs.studentArr[i].fullname);
			getline(fin, line);
			crs.studentArr[i].gender = line.front();
			getline(fin, line);
			crs.studentArr[i].birthDate = sToDate(line);
			getline(fin, line);
			crs.studentArr[i].active = stoi(line);
			if (insertedStu == false) {
				//If there's a spot to insert newStu in the array
				if (i < crs.nStudents - 1 && (*orderStu)(&newStu, &crs.studentArr[i])) {
					crs.studentArr[i + 1] = crs.studentArr[i];
					crs.studentArr[i] = newStu;
					insertedStu = true;
					i++;
				}
				//If there's no spot, insert at the end of array
				else if (i == crs.nStudents - 1) {
					crs.studentArr[i] = newStu;
					insertedStu = true;
					break;
				}
			}
			//Load scoreboard and attendance list of student i (i will be updated after insertion)
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

		//Rewrite the course student file
		if (!foundStu) {
			fout.open(path);
			if (!fout.is_open() || fout.fail()) {
				cerr << "Error while adding new student entry to the course files!" << endl;
				delete[] dateArr;
				delete[] crs.studentArr;
				delete[] crs.board;
				delete[] crs.checkList;
				return false;
			}
			fout << crs.nWeeks << endl
				<< crs.nStudents << endl;
			for (int i = 0; i < crs.nStudents; i++) {
				fout << crs.studentArr[i].ID << endl
					<< crs.studentArr[i].fullname << endl
					<< crs.studentArr[i].gender << endl
					<< put_time(&crs.studentArr[i].birthDate, "%Y-%m-%d") << endl
					<< crs.studentArr[i].active << endl;
				fout << crs.board[i].midterm << endl
					<< crs.board[i].final << endl
					<< crs.board[i].bonus << endl
					<< crs.board[i].total << endl;
				for (int j = 0; j < crs.nWeeks; j++) {
					fout << put_time(&dateArr[j], "%Y-%m-%d") << ' ' << crs.checkList[i * crs.nWeeks + j] << endl;
				}
				fout << endl;
			}
			fout.close();
		}
		delete[] dateArr;
		delete[] crs.studentArr;
		delete[] crs.board;
		delete[] crs.checkList;
	}

	//- Load Student Courses file to array of RegCourses:
	path = sysPath + curSem.year + '_' + curSem.semester + "_Student Courses.txt";
	if (emptyFile(path)) {
		fout.open(path);
		if (!fout.is_open() || fout.fail()) {
			cerr << "Can't register the student course list!" << endl;
			return false;
		}
		fout << 1 << endl
			<< newStu.ID << endl
			<< newStu.fullname << endl
			<< newStu.classID << endl
			<< 1 << endl
			<< crs.courseID << ' ' << crs.className << endl;
		fout << endl;
		fout.close();
	}
	else {
		foundStu = false;
		RegCourses* arrStu;
		int nReg;
		fin.open(path);
		readRegCourses(fin, arrStu, nReg);
		fin.close();
		bool* haveCourse = new bool[nReg] {false};
		//Scan the array for newStu, and check if the newStu already has this course
		for (int i = 0; i < nReg && foundStu == false; i++) {
			if (newStu.ID == arrStu[i].studentID) foundStu = true;
			if (foundStu == true) {
				for (int j = 0; j < arrStu[i].nCourses && haveCourse[i] == false; j++) {
					if (arrStu[i].courseID[j] == crs.courseID && arrStu[i].classID[j] == crs.className)
						haveCourse[i] = true;
				}
			}
		}
		fout.open(path);
		if (!fout.is_open() || fout.fail()) {
			cerr << "Can't register the student course list!" << endl;
			for (int i = 0; i < nReg; i++) {
				delete[] arrStu[i].courseID;
				delete[] arrStu[i].classID;
			}
			delete[] arrStu;
			delete[] haveCourse;
			return false;
		}
		//	+ If new student is already in the file: find the student in the array and add the course to their course list
		if (foundStu) {
			fout << nReg << endl;
			for (int i = 0; i < nReg; i++) {
				fout << arrStu[i].studentID << endl
					<< arrStu[i].studentName << endl
					<< arrStu[i].studentClass << endl;
				if (arrStu[i].studentID == newStu.ID && haveCourse[i] == false) {
					fout << arrStu[i].nCourses + 1 << endl;
					fout << crs.courseID << ' ' << crs.className << endl;
				}
				else fout << arrStu[i].nCourses << endl;
				for (int j = 0; j < arrStu[i].nCourses; j++) {
					fout << arrStu[i].courseID[j] << ' ' << arrStu[i].classID[j] << endl;
				}
				fout << endl;
			}
		}
		//	+ If new student is not in the file: add a new student to the array with 1 course (this course)
		else {
			fout << nReg + 1 << endl;
			for (int i = 0; i < nReg; i++) {
				fout << arrStu[i].studentID << endl
					<< arrStu[i].studentName << endl
					<< arrStu[i].studentClass << endl;
				fout << arrStu[i].nCourses << endl;
				for (int j = 0; j < arrStu[i].nCourses; j++) {
					fout << arrStu[i].courseID[j] << ' ' << arrStu[i].classID[j] << endl;
				}
				fout << endl;
			}
			fout << newStu.ID << endl
				<< newStu.fullname << endl
				<< newStu.classID << endl
				<< 1 << endl
				<< crs.courseID << ' ' << crs.className << endl;
			fout << endl;
		}
		fout.close();
		for (int i = 0; i < nReg; i++) {
			delete[] arrStu[i].courseID;
			delete[] arrStu[i].classID;
		}
		delete[] arrStu;
		delete[] haveCourse;
	}
	//If everything has been done successfully
	return true;
}

bool removeCourseStudent(Semester curSem) {
	string line, path;
	string sysPath = "./TextFiles/";
	ifstream fin;
	ofstream fout;
	Course crs;
	string stuID;
	//- Get current semester from the system, course ID and course class from user
	crs.c_semester = curSem;
	cout << "Enter course ID: ";
	getline(cin, crs.courseID);
	if (!viewClasses()) {
		cout << "There's currently no class in the system!" << endl;
		return false;
	}
	cout << "Enter class ID of the course: ";
	getline(cin, crs.className);
	//- Find and load the course info
	path = sysPath + curSem.year + '_' + curSem.semester + '_' + crs.className + "_Schedules.txt";
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
	//- Get student ID to remove the student
	cout << "Enter student ID: ";
	getline(cin, stuID);
	//- Load the student list of the course
	tm* dateArr = getWeeks(crs.startDate, crs.endDate, &crs.nWeeks);
	if (dateArr == nullptr || crs.nWeeks <= 0) {
		cerr << "Error getting schedule of the course!" << endl;
		return false;
	}
	path = sysPath + curSem.year + '_' + curSem.semester + '_' + crs.courseID + '_' + crs.className + "_Students.txt";
	if (emptyFile(path)) {
		cerr << "Can't get the student list of this course!" << endl;
		delete[] dateArr;
		return false;
	}
	else {
		fin.open(path);
		fin.ignore(INT_MAX, '\n'); //Skip line contains nWeeks
		getline(fin, line);
		crs.nStudents = stoi(line);
		crs.studentArr = new Student[crs.nStudents];	//1D arr
		crs.board = new score[crs.nStudents];	//1D arr, default value of all scores is -1
		crs.checkList = new bool[crs.nWeeks * crs.nStudents]{ false };	//2D arr, default value of all elements is false
		for (int i = 0; i < crs.nStudents; i++) {
			getline(fin, crs.studentArr[i].ID);
			if (crs.studentArr[i].ID == stuID) {
				//If the student being read is the removal target, then do not load into the array
				i--;
				crs.nStudents--;
				for (int j = 0; j < 9 + crs.nWeeks; j++)
					fin.ignore(INT_MAX, '\n');
			}
			else {
				getline(fin, crs.studentArr[i].fullname);
				getline(fin, line);
				crs.studentArr[i].gender = line.front();
				getline(fin, line);
				crs.studentArr[i].birthDate = sToDate(line);
				getline(fin, line);
				crs.studentArr[i].active = stoi(line);
				//Load scoreboard and attendance list of student i (i will be updated after insertion)
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
		}
		fin.close();

		//Rewrite the course student file
		fout.open(path);
		if (!fout.is_open() || fout.fail()) {
			cerr << "Error while rewriting student list to the course files!" << endl;
			delete[] dateArr;
			delete[] crs.studentArr;
			delete[] crs.board;
			delete[] crs.checkList;
			return false;
		}
		fout << crs.nWeeks << endl
			<< crs.nStudents << endl;
		for (int i = 0; i < crs.nStudents; i++) {
			fout << crs.studentArr[i].ID << endl
				<< crs.studentArr[i].fullname << endl
				<< crs.studentArr[i].gender << endl
				<< put_time(&crs.studentArr[i].birthDate, "%Y-%m-%d") << endl
				<< crs.studentArr[i].active << endl;
			fout << crs.board[i].midterm << endl
				<< crs.board[i].final << endl
				<< crs.board[i].bonus << endl
				<< crs.board[i].total << endl;
			for (int j = 0; j < crs.nWeeks; j++) {
				fout << put_time(&dateArr[j], "%Y-%m-%d") << ' ' << crs.checkList[i * crs.nWeeks + j] << endl;
			}
			fout << endl;
		}
		fout.close();
		delete[] dateArr;
		delete[] crs.studentArr;
		delete[] crs.board;
		delete[] crs.checkList;
	}

	//Load regCourse and remove the course from the student's Enrolling Course list
	path = sysPath + curSem.year + '_' + curSem.semester + "_Student Courses.txt";
	if (emptyFile(path)) {
		cerr << "Can't remove the course from the student's Enrolling Course list!" << endl;
		return false;
	}
	else {
		RegCourses* arrStu;
		int nReg;
		fin.open(path);
		readRegCourses(fin, arrStu, nReg);
		fin.close();
		bool* haveCourse = new bool[nReg] {false};
		//Scan the array for stuID, and check if the stuID already has this course
		for (int i = 0; i < nReg; i++) {
			if (stuID == arrStu[i].studentID) {
				for (int j = 0; j < arrStu[i].nCourses && haveCourse[i] == false; j++) {
					if (arrStu[i].courseID[j] == crs.courseID && arrStu[i].classID[j] == crs.className)
						haveCourse[i] = true;
				}
				break;	//Stop scanning the array after the removal student is found
			}
		}
		fout.open(path);
		if (!fout.is_open() || fout.fail()) {
			cerr << "Can't rewrite the student course list!" << endl;
			for (int i = 0; i < nReg; i++) {
				delete[] arrStu[i].courseID;
				delete[] arrStu[i].classID;
			}
			delete[] arrStu;
			delete[] haveCourse;
			return false;
		}
		fout << nReg << endl;
		for (int i = 0; i < nReg; i++) {
			fout << arrStu[i].studentID << endl
				<< arrStu[i].studentName << endl
				<< arrStu[i].studentClass << endl;
			if (arrStu[i].studentID == stuID && haveCourse[i] == true) {
				fout << arrStu[i].nCourses - 1 << endl;
			}
			else fout << arrStu[i].nCourses << endl;
			for (int j = 0; j < arrStu[i].nCourses; j++) {
				if (arrStu[i].courseID[j] != crs.courseID || arrStu[i].classID[j] != crs.className)
					fout << arrStu[i].courseID[j] << ' ' << arrStu[i].classID[j] << endl;
			}
			fout << endl;
		}
		fout.close();
		for (int i = 0; i < nReg; i++) {
			delete[] arrStu[i].courseID;
			delete[] arrStu[i].classID;
		}
		delete[] arrStu;
		delete[] haveCourse;
	}
	return true;
}