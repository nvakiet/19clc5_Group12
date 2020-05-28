#include "../Headers/student.h"

bool checkin(Semester curSem, Account user) {
	string line, path, sysPath = "./TextFiles/";
	ifstream fin;
	ofstream fout;
	Course crs;

	//Ask the student to input course ID and class ID of the course
	cout << "Enter course ID you enrolled in: ";
	getline(cin, crs.courseID);
	cout << "Enter class ID of the course: ";
	getline(cin, crs.className);
	//Find the course
	path = sysPath + curSem.year + '_' + curSem.semester + '_' + crs.className + "_Schedules.txt";
	fin.open(path);
	if (emptyFile(path)) {
		cerr << "Can't find this course in the system!" << endl;
		return false;
	}
	if (!findACourseInfos(fin, crs, crs.courseID)) {
		cerr << "Can't find this course in the system!" << endl;
		return false;
	}
	fin.close();
	//Get current time and compare with course schedule (hour and minute)
	time_t now = time(nullptr);
	tm currentTime;
	localtime_s(&currentTime, &now);
	if ((currentTime.tm_hour * 60 + currentTime.tm_min) < (crs.startTime.tm_hour * 60 + crs.startTime.tm_min) || (currentTime.tm_hour * 60 + currentTime.tm_min) > (crs.endTime.tm_hour * 60 + crs.endTime.tm_min)) {
		cerr << "The current time does not match with this course's schedule" << endl;
		return false;
	}
	char buffer[11];
	strftime(buffer, 11, "%Y-%m-%d", &currentTime);
	string timestr(buffer);	//Store the current date into a string
	//Find the current date in the course attendance list and check in
		//Open the course _Students.txt to load information, open another temp.txt to rewrite the course
	path = sysPath + curSem.year + '_' + curSem.semester + '_' + crs.courseID + '_' + crs.className + "_Students.txt";
	string tempPath = sysPath + "temp.txt";
	fin.open(path);
	fout.open(tempPath);
	if (emptyFile(path) || !fout.is_open() || !fout.good()) {
		cerr << "Failed to change the attendance list of the course" << endl;
		return false;
	}
		//Transfer data from path to tempPath line by line, but change the check in value if a line has the current date
	bool checked = false;
	while (getline(fin, line)) {
		if (checked == false && line == user.username) {
			fout << line << endl;
			do {
				getline(fin, line);
				if (line.substr(0, timestr.length()) == timestr) {
					line.back() = '1';
					checked = true;
				}
				fout << line << endl;
			} while (!line.empty() && checked == false);
		}
		else fout << line << endl;
	}
	if (!checked) {
		cerr << "The current date does not match with the course's attendance list!" << endl;
		return false;
	}
	if (!fout) {
		cerr << "Failed to edit the attendance list!" << endl;
		remove(tempPath.c_str());
		return false;
	}
	fin.close();
	fout.close();
		//Remove old file and rename temp.txt to old file name
	if (remove(path.c_str()) != 0) {
		cerr << "Failed to edit the attendance list!" << endl;
		remove(tempPath.c_str());
		return false;
	}
	else if (rename(tempPath.c_str(), path.c_str()) != 0) {
		cerr << "Failed to edit the attendance list!" << endl;
		remove(tempPath.c_str());
		return false;
	}

	return true;
}