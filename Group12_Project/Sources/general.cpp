#include "../Headers/general.h"

tm sToDate(string date_str) {
	tm date;
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
	stream << date.tm_year + 1900 << '-' 
		<< setfill('0') << setw(2) << date.tm_mon + 1 << '-' 
		<< setfill('0') << setw(2) << date.tm_mday << endl;
}

tm sToTime(string time_str) {
	tm time;
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
	stream << setfill('0') << setw(2) << time.tm_hour << ':' 
		<< setfill('0') << setw(2) << time.tm_min << endl;
}

void flushin(istream& input) {
	input.clear();
	input.ignore(INT_MAX, '\n');
}

void pause() {
	cout << "Press ENTER to continue..." << endl;
	flushin(cin);
	cin.get();
}

bool emptyFile(string filePath) {
	string line;
	ifstream fin;
	bool flag;
	fin.open(filePath);
	if (fin.is_open() && fin.good()) {
		while (!fin.eof()) {
			getline(fin, line);
			if (!line.empty())
				flag = false;
		}
	}
	fin.close();
	flag = true;
	return flag;
}

bool generateFile(string filePath, string init) {
	ofstream fout(filePath);
	bool flag;
	if (fout.is_open() && fout.good()) {
		fout << init << endl;
		flag = true;
	}
	else flag = false;
	fout.close();
	return flag;
}