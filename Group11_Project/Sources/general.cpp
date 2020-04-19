#include "../Headers/general.h"

tm sToDate(string date_str) {
	tm date;
	date.tm_year = stoi(date_str.substr(0, 4)) - 1900;
	date.tm_mon = stoi(date_str.substr(5, 2)) - 1;
	date.tm_mday = stoi(date_str.substr(8, 2));
	return date;
}

tm sToTime(string time_str) {
	tm time;
	time.tm_hour = stoi(time_str.substr(0, 2));
	time.tm_min = stoi(time_str.substr(3, 2));
	return time;
}