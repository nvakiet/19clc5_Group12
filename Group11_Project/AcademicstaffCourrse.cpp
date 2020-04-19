#include "../Headers/.h"
void inputSemester(ofstream& fin, int x) {
	Semester a;
	int* i = &x;
	int x1 = *i;
	cout << "Years: ";
	getline(cin, a.year);
	cout << "Semester : ";
	getline(cin, a.semester);
	fin.open(". / TextFiles / Semester.txt", ios::app);
	fin << x1 << endl;
	fin << a.year << endl;
	fin << a.semester << endl;
	fin.close();
	*i += 1;
}