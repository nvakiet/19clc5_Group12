#include "../Headers/staff-course.h"

Semester getCurrentSemester() {
	time_t current = time(NULL);
	Semester curSem;
	tm timeinfo = *(localtime(&current));
	if (timeinfo.tm_mon > 7) {
		curSem.semester = "HK1";
		curSem.year = to_string(timeinfo.tm_year + 1900) + '-' + to_string(timeinfo.tm_year + 1900 + 1);
	}
	else if (timeinfo.tm_mon < 4) {
		curSem.semester = "HK2";
		curSem.year = to_string(timeinfo.tm_year + 1900 - 1) + '-' + to_string(timeinfo.tm_year + 1900);
	}
	else {
		curSem.semester = "HK3";
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
			if (!fout) return false;
			fout.close();
			return true;
		}
		else return false;
	}
	//If the file isn't empty, scan the file to check if the input is duplicate

}