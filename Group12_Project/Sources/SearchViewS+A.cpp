#include "../Headers/SearchViewS+A.h"
void viewScoreboard(Course B)
{
	for (int i = 0; i < B.nStudents; i++)
	{
		if (B.studentArr[i].active == false) continue;
		cout << B.studentArr[i].ID << endl;
		cout << B.studentArr[i].fullname << endl;
		cout << B.studentArr[i].gender << endl;
		printDate(cout, B.studentArr[i].birthDate);
		cout << B.board[i].midterm << endl;
		cout << B.board[i].final << endl;
		cout << B.board[i].bonus << endl;
		cout << B.board[i].total << endl;
		cout << endl;
	}
}
void SearchandViewScoreboard()
{
	Course B;
	string x = "Students", path = "./TextFiles/";
	string line;
	printf("Enter years : ");
	getline(cin, B.c_semester.year);
	printf("Enter semester : ");
	getline(cin, B.c_semester.semester);
	printf("Enter course ID: ");
	getline(cin, B.courseID);
	printf("Enter class ID: ");
	getline(cin, B.className);
	cout << endl;
	ifstream fin;
	fin.open(path + B.c_semester.year + "_" + B.c_semester.semester + "_" + B.courseID + "_" + B.className + "_" + x + ".txt");
	if (fin.fail())
	{
		printf("Failed to open this file!\n");
		return;
	}
	getline(fin, line);
	B.nWeeks = stoi(line);
	getline(fin, line);
	B.nStudents = stoi(line);
	B.studentArr = new Student[B.nStudents];
	B.board = new score[B.nStudents];
	
	for (int i = 0; i < B.nStudents; i++)
	{
		getline(fin, B.studentArr[i].ID);
		getline(fin, B.studentArr[i].fullname);
		getline(fin, line);
		B.studentArr[i].gender = line.front();
		getline(fin, line);
		B.studentArr[i].birthDate = sToDate(line);
		getline(fin, line);
		B.studentArr[i].active = stoi(line);
		getline(fin, line);
		B.board[i].midterm = stof(line);
		getline(fin, line);
		B.board[i].final = stof(line);
		getline(fin, line);
		B.board[i].bonus = stof(line);
		getline(fin, line);
		B.board[i].total = stof(line);
		for (int i = 0; i <= B.nWeeks; i++)
		{
			fin.ignore(INT_MAX, '\n');
		}

	}
	

	fin.close();
	viewScoreboard(B);
	delete[]B.studentArr;
	delete[]B.board;
}
void viewAttendance(Course B, string* classdate)
{
	for (int i = 0; i < B.nStudents; i++)
	{
		if (B.studentArr[i].active == false) continue;
		cout << B.studentArr[i].ID << endl;
		cout << B.studentArr[i].fullname << endl;
		cout << B.studentArr[i].gender << endl;
		printDate(cout, B.studentArr[i].birthDate);
		for (int j = 0; j < B.nWeeks; j++)
		{
			cout << classdate[j] << " " << *(B.checkList + i * B.nWeeks + j) << endl;
		}
		cout << endl;
	}
}
void SearchandViewAttendance()
{
	Course B;
	string x = "Students", path = "./TextFiles/";
	string line;
	printf("Enter years : ");
	getline(cin, B.c_semester.year);
	printf("Enter semester : ");
	getline(cin, B.c_semester.semester);
	printf("Enter course ID: ");
	getline(cin, B.courseID);
	printf("Enter class ID: ");
	getline(cin, B.className);
	cout << endl;
	ifstream fin;
	fin.open(path + B.c_semester.year + "_" + B.c_semester.semester + "_" + B.courseID + "_" + B.className + "_" + x + ".txt");
	if (fin.fail())
	{
		printf("Failed to open this file!\n");
		return;
	}
	getline(fin, line);
	B.nWeeks = stoi(line);
	getline(fin, line);
	B.nStudents = stoi(line);
	string* classdate = new string[B.nWeeks];
	B.checkList = new bool[B.nStudents * B.nWeeks];
	B.studentArr = new Student[B.nStudents];
	
	
	for (int i = 0; i < B.nStudents; i++)
	{
		getline(fin, B.studentArr[i].ID);
		getline(fin, B.studentArr[i].fullname);
		getline(fin, line);
		B.studentArr[i].gender = line.front();
		getline(fin, line);
		B.studentArr[i].birthDate = sToDate(line);
		getline(fin, line);
		B.studentArr[i].active = stoi(line);
		for (int i = 0; i < 4; i++)
		{
			fin.ignore(INT_MAX, '\n');
		}
		for (int j = 0; j < B.nWeeks; j++)
		{
			getline(fin, classdate[j], ' ');
			getline(fin, line);
			*(B.checkList + i * B.nWeeks + j) = stoi(line);
		}
		fin.ignore(INT_MAX, '\n');
	}
	
	fin.close();
	viewAttendance(B, classdate);
	delete[]classdate;
	delete[]B.checkList;
	delete[]B.studentArr;
}
