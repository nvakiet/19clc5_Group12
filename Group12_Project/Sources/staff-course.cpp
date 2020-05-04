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
	cout << "Enter start date of course (YYYY-MM-DD): ";
	cin >> get_time(&inCourse.startDate, "%Y-%m-%d");
	while (!cin) {
		cerr << "Invalid date input!" << endl;
		flushin(cin);
		cin >> get_time(&inCourse.startDate, "%Y-%m-%d");
	}
	flushin(cin);
	cout << "Enter end date of course (YYYY-MM-DD): ";
	cin >> get_time(&inCourse.endDate, "%Y-%m-%d");
	while (!cin) {
		cerr << "Invalid date input!" << endl;
		flushin(cin);
		cin >> get_time(&inCourse.endDate, "%Y-%m-%d");
	}
	flushin(cin);
	cout << "Enter day of week when course is available in shortened form (Ex: Thu, Fri): ";
	getline(cin, inCourse.classDay);
	cout << "Enter start time of class (HH:MM): ";
	cin >> get_time(&inCourse.startTime, "%H:%M");
	while (!cin) {
		cerr << "Invalid date input!" << endl;
		flushin(cin);
		cin >> get_time(&inCourse.startTime, "%H:%M");
	}
	flushin(cin);
	cout << "Enter end time of class (HH:MM): ";
	cin >> get_time(&inCourse.endTime, "%H:%M");
	while (!cin) {
		cerr << "Invalid date input!" << endl;
		flushin(cin);
		cin >> get_time(&inCourse.endTime, "%H:%M");
	}
	flushin(cin);
	cout << "Enter classroom ID: ";
	getline(cin, inCourse.room);

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
		nLecturers = stoi(line);
		userArr = new Account[nLecturers];
		for (int i = 0; i < nLecturers && sameLecturer == false; i++) {
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
		//Rewrite the userArray but with a new size and output the new lecturer account at the end
		if (sameLecturer == false) {
			fout.open(Path);
			if (!fout.is_open()) {
				cerr << "Can't update lecturer's account!" << endl;
				delete[] userArr;
				return false;
			}
			fout << nLecturers + 1 << endl;
			for (int i = 0; i < nLecturers; i++) {	//Rewrite existed accounts
				fout << userArr[i].username << endl
					<< userArr[i].password << endl
					<< userArr[i].lecturerProfile.fullname << endl
					<< userArr[i].lecturerProfile.email << endl
					<< userArr[i].lecturerProfile.academicRank << endl
					<< userArr[i].lecturerProfile.gender << endl;
				fout << endl;
			}
			fout << slackName << endl	//Update new account
				<< sha256(slackName + "_HCMUS") << endl
				<< inCourse.courseLecturer.fullname << endl
				<< inCourse.courseLecturer.email << endl
				<< inCourse.courseLecturer.academicRank << endl
				<< inCourse.courseLecturer.gender << endl;
			fout << endl;
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
	Path = inCourse.c_semester.year + '_' + inCourse.c_semester.semester + '_' + inCourse.className + "_Schedules.txt";
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
		nCourses = stoi(line);
		Course* courseArr = new Course[nCourses];
		for (int i = 0; i < nCourses; i++) {
			getline(fin, courseArr[i].courseID);
		}
		fin.close();
		delete[] courseArr;
	}
	//* Load [ClassID]_Students.txt to student array
	//* Get nWeeks and date array from startDate and endDate (including startDate and endDate in array)
	//* Save the student array to [Year]_[Semester]_[CourseID]_[ClassID]_Students.txt
	//* ^ along with default scoreboards of -1 and nWeeks and date array and default check lists of 0 for each student
	//* Make and Add struct RegCourses of each student to [Year]_[Semester]_Student Courses.txt
}