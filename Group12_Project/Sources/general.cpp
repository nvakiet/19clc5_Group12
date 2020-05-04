#include "../Headers/general.h"

tm sToDate(string date_str) {
	tm date;
	resetTM(date);
	int len = date_str.length() + 1;
	char* datestr = new char[len];
	char* nextToken = nullptr;
	strcpy_s(datestr, date_str.size() + 1, date_str.c_str());
	char* token = strtok_s(datestr, "-/\n", &nextToken);
	date.tm_year = atoi(token) - 1900;
	if (token != nullptr) {
		token = strtok_s(nullptr, "-/\n", &nextToken);
		date.tm_mon = atoi(token) - 1;
	}
	if (token != nullptr) {
		token = strtok_s(nullptr, "-/\n", &nextToken);
		date.tm_mday = atoi(token);
	}
	delete[] datestr;
	return date;
}

void printDate(ostream& stream, tm date) {
	stream << setfill('0') << right << date.tm_year + 1900 << '-'
		<< setw(2) << date.tm_mon + 1 << '-' 
		<< setw(2) << date.tm_mday << endl;
}

void resetTM(tm &time) {
	time.tm_year = 0;
	time.tm_mon = 0;
	time.tm_mday = 1;
	time.tm_hour = 0;
	time.tm_min = 0;
	time.tm_sec = 0;
	time.tm_wday = 0;
	time.tm_yday = 0;
	time.tm_isdst = 0;
}

tm sToTime(string time_str) {
	tm time;
	resetTM(time);
	int len = time_str.length() + 1;
	char* timestr = new char[len];
	char* nextToken = nullptr;
	strcpy_s(timestr, time_str.size() + 1, time_str.c_str());
	char* token = strtok_s(timestr, ":\n", &nextToken);
	time.tm_hour = atoi(token);
	if (token != nullptr) {
		token = strtok_s(nullptr, ":\n", &nextToken);
		time.tm_min = atoi(token);
	}
	delete[] timestr;
	return time;
}

void printTime(ostream& stream, tm time) {
	stream << setfill('0') << right << setw(2) << time.tm_hour << ':' 
		   << setw(2) << time.tm_min << endl;
}

void flushin(istream& input) {
	input.clear();
	input.ignore(INT_MAX, '\n');
}

void pause() {
	cout << "\nPress ENTER to continue..." << endl;
	cin.ignore(INT_MAX, '\n');
}

bool emptyFile(string filePath) {
	string line;
	ifstream fin;
	bool flag = true;
	fin.open(filePath);
	if (fin.is_open() && fin.good()) {
		while (!fin.eof() && flag != false) {
			getline(fin, line);
			if (!line.empty()) flag = false;
		}
	}
	fin.close();
	return flag;
}

bool generateFile(string filePath, string init) {
	ofstream fout(filePath);
	bool flag;
	if (fout.is_open() && fout.good()) {
		fout << init;
		flag = true;
	}
	else flag = false;
	fout.close();
	return flag;
}

tm* getWeeks(tm startDate, tm endDate, int *nWeeks = nullptr) {
	//1 week in seconds = 7 * 24 * 60 * 60 = 604800 seconds
	//n weeks in seconds = nWeeks * 604800 seconds
	int secWeek = 604800; //Number of seconds in a week
	time_t begin = mktime(&startDate);
	time_t end = mktime(&endDate);
	int n = difftime(end, begin) / secWeek;	//Get number of weeks between 2 dates
	if (n < 0) return nullptr;
	if (nWeeks != nullptr) *nWeeks = n + 1; //nWeeks also counts the starting date as week 1
	tm* dateArr = new tm[n + 1]; //This array will contain start date and end date
	for (int i = 0; i <= n; i++) {
		time_t weekDate = begin + time_t(i * secWeek); //Get i next week from beginning time_t, value in seconds 
		localtime_s(&dateArr[i], &weekDate);
	}
	return dateArr;
}