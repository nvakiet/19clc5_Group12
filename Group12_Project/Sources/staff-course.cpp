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