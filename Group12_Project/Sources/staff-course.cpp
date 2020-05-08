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
	cout << "Here's the semester list: " << endl;
	for (int i = 0; i < n; i++) {
		cout << "Academic Year: " << fileSem[i].year << endl;
		cout << "Semester: " << fileSem[i].semester << endl;
		cout << endl;
	}
	delete[] fileSem;
}

bool addCourse() {
	//To do list:
	//* Read inputs from user and store to a Course structure
	ifstream fin;
	ofstream fout;
	string line, slackName;
	Course inCourse;
	cout << "Enter academic year (Year A - Year B): ";
	getline(cin, inCourse.c_semester.year);
	cout << "Enter semester: ";
	getline(cin, inCourse.c_semester.semester);
	cout << "Enter course ID: ";
	getline(cin, inCourse.courseID);
	cout << "Enter course name: ";
	getline(cin, inCourse.courseName);
	cout << "Enter class ID of the course: ";
	getline(cin, inCourse.className);
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

	//* Update to Semesters.txt
	if (updateSemester(inCourse.c_semester))
		cout << "Semesters.txt has been updated!" << endl;
	else {
		cerr << "Can't update semester!" << endl;
		return false;
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
		cout << "Course info has been updated!" << endl;
	}

	//* Load [ClassID]_Students.txt to student array
	cout << "Loading student list of the class..." << endl;
	Path = "./TextFiles/" + inCourse.className + "_Students.txt";
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
		fout << inCourse.nStudents << endl;
		for (int i = 0; i < inCourse.nStudents; i++) {
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
			fout << nReg + inCourse.nStudents << endl;
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

	//* Update to Semesters.txt
	if (updateSemester(inCourse.c_semester))
		cout << "Semesters.txt has been updated!" << endl;
	else {
		cerr << "Can't update semester!" << endl;
		return false;
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
		fout << inCourse.nStudents << endl;
		for (int i = 0; i < inCourse.nStudents; i++) {
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
		fout << nReg + inCourse.nStudents << endl;
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

bool importCourse() {
	ifstream fin;
	ofstream fout;
	string line, lecturerUsername, csvPath;
	Course inCourse;
	cout << "Enter csv file path: ";
	getline(cin, csvPath);
	cout << "Enter academic year for these courses: ";
	getline(cin, inCourse.c_semester.year);
	cout << "Enter semester for these courses: ";
	getline(cin, inCourse.c_semester.semester);
	if (emptyFile(csvPath)) {
		cerr << "Can't find data in the path you entered!" << endl;
		return false;
	}
	else {
		fin.open(csvPath);
		fin.ignore(INT_MAX, '\n'); //Ignore the first row that contains the column titles
		while (!fin.eof()) {
			fin.ignore(INT_MAX, ';'); //Ignore "No." column
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
			else cout << "\nCourse " << inCourse.courseID << " of class " << inCourse.className << " has been added!" << endl;
		}
		fin.close();
		return true;
	}
}

