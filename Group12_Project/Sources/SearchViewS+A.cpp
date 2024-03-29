#include "../Headers/SearchViewS+A.h"


void CSVScoreboard(Course B)
{

	string y = "Scoreboard", path = "./TextFiles/";
	int x;
	int z = 1;//De luu tru thu tu hoc sinh
	cout << "Do you want to export this file to CSV ? (1: Yes/0 : No) : ";
	cin >> x;
	while (!cin || x < 0 || x > 1) {
		flushin(cin);
		cerr << "Invalid input!" << endl;
		cout << "--> ENTER A NUMBER FOR YOUR CHOICE: ";
		cin >> x;
	}
	cout << endl;
	flushin(cin);
	if (x == 1)
	{
		ofstream fout;
		fout.open(path +B.c_semester.year + "_" + B.c_semester.semester + "_" + B.courseID + "_" + B.className + "_" + y + ".csv");
		fout << "NO" << ";" << "ID" << ";" << "First Name" << ";" << "Last Name" << ";" << "Midterm" << ";" << "Final" << ";" << "Bonus" << ";" << "Total" << endl;
		for (int i = 0; i < B.nStudents; i++)
		{
			size_t found = B.studentArr[i].fullname.find_last_of(" ");
			fout << z << ";" << B.studentArr[i].ID << ";" << B.studentArr[i].fullname.substr(0, found) << ";" << B.studentArr[i].fullname.substr(found + 1) << ";";
			fout << B.board[i].midterm << ";" << B.board[i].final << ";" << B.board[i].bonus << ";" << B.board[i].total << "\n";
			z++;
		}
		fout.close();
		cout << "Export successfully!" << endl;
	}
}
void CSVAttendance(Course B, string*& classdate)
{
	string y = "Attendance", path = "./TextFiles/";
	int x;
	int z = 1;//De luu tru thu tu hoc sinh
	cout << "Do you want to export this file to CSV ? (1: Yes/0 : No) : ";
	cin >> x;
	while (!cin || x < 0 || x > 1) {
		flushin(cin);
		cerr << "Invalid input!" << endl;
		cout << "--> ENTER A NUMBER FOR YOUR CHOICE: ";
		cin >> x;
	}
	cout << endl;
	flushin(cin);
	if (x == 1)
	{
		ofstream fout;
		fout.open(path +B.c_semester.year + "_" + B.c_semester.semester + "_" + B.courseID + "_" + B.className + "_" + y + ".csv");
		fout << "NO" << ";" << "ID" << ";" << "First Name" << ";" << "Last Name" << ";" << "Gender" << ";" << "BirthDate";
		for (int i = 0; i < B.nWeeks; i++)
			fout << ";" << classdate[i];
		fout << endl;
		for (int i = 0; i < B.nStudents; i++)
		{

			size_t found = B.studentArr[i].fullname.find_last_of(" ");
			fout << z << ";" << B.studentArr[i].ID << ";" << B.studentArr[i].fullname.substr(0, found) << ";" << B.studentArr[i].fullname.substr(found + 1) << ";" << B.studentArr[i].gender << ";";
			fout << setfill('0') << right << B.studentArr[i].birthDate.tm_year + 1900 << '-'
				<< setw(2) << B.studentArr[i].birthDate.tm_mon + 1 << '-'
				<< setw(2) << B.studentArr[i].birthDate.tm_mday;
			for (int j = 0; j < B.nWeeks; j++)
			{
				fout << ";" << *(B.checkList + i * B.nWeeks + j);
			}
			fout << "\n";
			z++;
		}
		fout.close();
		cout << "Export successfully!" << endl;
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
	cout << string(128, '-') << "\n";
	cout << "|" << center("Student ID", 15) << "|" << center("S.Name", 30) << "|"
		<< center("S.Gender", 10) << "|" << center("S.BirthDate", 13) << "|"
		<< center("Active", 10) << "|"
		<< center("Mid Term", 10) << "|" << center("Final", 10) << "|"
		<< center("Bonus", 10) << "|" << center("Total", 10) << "|" << endl;
	cout << string(128, '-') << "\n";
	for (int i = 0; i < B.nStudents; i++)
	{
		getline(fin, line);
		B.studentArr[i].ID = line;
		cout << "|" << center(line, 15) << "|";

		getline(fin, line);
		B.studentArr[i].fullname = line;
		cout << center(line, 30) << "|";

		getline(fin, line);
		B.studentArr[i].gender = line.front();
		cout << center(line, 10) << "|";

		getline(fin, line);
		B.studentArr[i].birthDate = sToDate(line);
		cout << center(line, 13) << "|";

		getline(fin, line);
		B.studentArr[i].active = stoi(line);
		if (B.studentArr[i].active) cout << center("Active", 10) << "|";
		else cout << center("Inactive", 10) << "|";

		getline(fin, line);
		B.board[i].midterm = stof(line);
		cout << center(line, 10) << "|";

		getline(fin, line);
		B.board[i].final = stof(line);
		cout << center(line, 10) << "|";

		getline(fin, line);
		B.board[i].bonus = stof(line);
		cout << center(line, 10) << "|";

		getline(fin, line);
		B.board[i].total = stof(line);
		cout << center(line, 10) << "|";

		cout << endl;
		for (int i = 0; i <= B.nWeeks; i++)
		{
			fin.ignore(INT_MAX, '\n');
		}
		cout << string(128, '-') << "\n";
	}
	fin.close();

	CSVScoreboard(B);
	delete[]B.studentArr;
	delete[]B.board;
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
	
	
	string* DoB = new string[B.nStudents];
	cout << string(54 + B.nWeeks * 14, '-') << "\n";
	cout << "|" << center("ID", 10) << "|" << center("Name", 30) << "|"
		<< center("DoB", 10) << "|";

	for (int i = 0; i < B.nStudents; i++)
	{
		getline(fin, B.studentArr[i].ID);
		getline(fin, B.studentArr[i].fullname);
		getline(fin, line);
		B.studentArr[i].gender = line.front();

		getline(fin, line);
		DoB[i] = line;
		B.studentArr[i].birthDate = sToDate(line);

		getline(fin, line);
		B.studentArr[i].active = stoi(line);
		for (int i = 0; i < 4; i++)
		{
			fin.ignore(INT_MAX, '\n');
		}
		for (int j = 0; j < B.nWeeks; j++)
		{
			getline(fin, line, ' ');
			classdate[j] = line;

			getline(fin, line);
			*(B.checkList + i * B.nWeeks + j) = stoi(line);

		}
		fin.ignore(INT_MAX, '\n');

	}
	for (int i = 0; i < B.nWeeks; i++)
	{

		cout << center(classdate[i], 13) << "|";
	}

	cout << endl;
	cout << string(54 + B.nWeeks * 14, '-') << "\n";
	for (int i = 0; i < B.nStudents; i++)
	{

		cout << "|" << center(B.studentArr[i].ID, 10) << "|"
			<< center(B.studentArr[i].fullname, 30) << "|"
			<< center(DoB[i], 10) << "|";
		for (int j = 0; j < B.nWeeks; j++)
		{
			if (B.checkList[i * B.nWeeks + j]) cout << center("Attended", 13) << '|';
			else cout << center("X", 13) << '|';
		}
		cout << endl;
		cout << string(54 + B.nWeeks * 14, '-') << "\n";
	}
	fin.close();

	CSVAttendance(B, classdate);
	delete[]classdate;
	delete[]B.checkList;
	delete[]B.studentArr;
	delete[]DoB;
	
}
bool viewcheckin(Account user,Semester cursem)
{
	string ID = user.studentProfile.ID;//Truyen thong tin ID vao bien ID
	Course B;
	string x = "Students", path = "./TextFiles/";
	string line;
	B.c_semester = cursem;
	printf("Enter course ID: ");
	getline(cin, B.courseID);
	printf("Enter class ID: ");
	getline(cin, B.className);
	ifstream fin;
	fin.open(path + B.c_semester.year + "_" + B.c_semester.semester + "_" + B.courseID + "_" + B.className + "_" + x + ".txt");
	if (fin.fail())
	{
		printf("Failed to open this file!\n");
		return false;
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
		if (B.studentArr[i].ID == ID)
		{
			for (int i = 0; i < 8; i++)
				fin.ignore(INT_MAX, '\n');
			for (int j = 0; j < B.nWeeks; j++)
			{
				getline(fin, classdate[j], ' ');
				getline(fin, line);
				*(B.checkList + i * B.nWeeks + j) = stoi(line);
			}
			cout << string(B.nWeeks * 14, '-') << "\n";
			cout << "|";
			for (int i = 0; i < B.nWeeks; i++)
			{
				cout << center(classdate[i], 13) << "|";
			}
			cout << endl;
			cout << string(B.nWeeks * 14, '-') << "\n";
			cout << "|";
			for (int j = 0; j < B.nWeeks; j++)
			{

				if (*(B.checkList + i * B.nWeeks + j) == true) cout << center("Attended", 13) << "|";
				else cout << center("X", 13) << "|";
			}
			cout << endl;
			cout << string(B.nWeeks * 14, '-') << "\n";
			fin.close();
			delete[]classdate;
			delete[]B.checkList;
			delete[]B.studentArr;
			return true;//co hoc sinh de xuat ra
		}
		else
		{
			for (int i = 0; i < 9 + B.nWeeks; i++)
				fin.ignore(INT_MAX, '\n');
		}
	}
	fin.close();
	delete[]classdate;
	delete[]B.checkList;
	delete[]B.studentArr;
	return false;//khong co hoc sinh de xuat ra;
}
bool viewscore(Account user)
{
	Course B;
	string x = "Students", path = "./TextFiles/";
	string line;
	string ID = user.studentProfile.ID;
	printf("Enter years : ");
	getline(cin, B.c_semester.year);
	printf("Enter semester : ");
	getline(cin, B.c_semester.semester);
	printf("Enter course ID: ");
	getline(cin, B.courseID);
	printf("Enter class ID: ");
	getline(cin, B.className);
	ifstream fin;
	fin.open(path + B.c_semester.year + "_" + B.c_semester.semester + "_" + B.courseID + "_" + B.className + "_" + x + ".txt");
	if (fin.fail())
	{
		printf("Failed to open this file!\n");
		return false;
	}
	getline(fin, line);
	B.nWeeks = stoi(line);
	getline(fin, line);
	B.nStudents = stoi(line);
	B.studentArr = new Student[B.nStudents];
	for (int i = 0; i < B.nStudents; i++)
	{
		getline(fin, B.studentArr[i].ID);
		if (B.studentArr[i].ID == ID)
		{
			cout << " " << string(44, '-') << "\n";
			cout << "|" << center("Mid", 10) << "|" << center("Final", 10) << "|"
				<< center("Bonus", 10) << "|" << center("Total", 10) << "|" << endl;
			for (int i = 0; i < 4; i++)
				fin.ignore(INT_MAX, '\n');
			cout << " " << string(44, '-') << "\n";
			cout << "|";
			getline(fin, line);
			cout << center(line, 10) << "|";
			getline(fin, line);
			cout << center(line, 10) << "|";
			getline(fin, line);
			cout << center(line, 10) << "|";
			getline(fin, line);
			cout << center(line, 10) << "|";
			cout << endl;
			cout << " " << string(44, '-') << "\n";
			fin.close();
			delete[]B.studentArr;
			return true;
		}
		else
		{
			for (int i = 0; i < 9 + B.nWeeks; i++)
				fin.ignore(INT_MAX, '\n');
		}
	}
	fin.close();
	delete[]B.studentArr;
	return false;//khong co hoc sinh de xuat ra;

	fin.close();
}
void viewSchedules(Account user, Semester curSem)
{
	Course B;
	string ID;
	string s = curSem.semester;
	string year = curSem.year;
	string line;
	ifstream fin;
	string x = "Student Courses";
	string h = "Schedules";
	fin.open("./TextFiles/" + year + "_" + s + "_" + x + ".txt");
	if (fin.fail())
	{
		printf("Failed to open this file!\n");
		return;
	}
	getline(fin, line);
	int n = stoi(line);
	bool foundStu = false;
	for (int i = 0; i < n && foundStu == false; i++)
	{
		getline(fin, ID);
		for (int j = 0; j < 2; j++)
			fin.ignore(INT_MAX, '\n');
		getline(fin, line);
		int t = stoi(line);
		if (user.username == ID)
		{
			foundStu = true;
			string courseID, classID;
			ifstream f;
			cout << "				=======SCHEDULES======= " << endl;
			cout << string(155, '-') << endl;
			cout << "|" << center("Course ID", 15) << "|" << center("Course Name", 30) << "|"
				<< center("Class", 10) << "|"
				<< center("S.Date", 15) << "|" << center("E.Date", 15) << "|"
				<< center("DoW", 15) << "|" << center("S.Time", 15) << "|"
				<< center("E.Time", 15) << "|" << center("Room", 15) << "|" << endl;
			cout << string(155, '-') << endl;
			for (int j = 0; j < t; j++)
			{
				getline(fin, courseID, ' ');
				getline(fin, classID);
				f.open("./TextFiles/" + year + "_" + s + "_" + classID + "_" + h + ".txt");
				getline(f, line);
				int num = stoi(line);
				for (int i = 0; i < num; i++)
				{
					getline(f, line);
					if (line == courseID)
					{
						cout << '|' << center(courseID, 15) << '|';
						getline(f, line);
						cout << center(line, 30) << '|';
						cout << center(classID, 10) << '|';
						for (int i = 0; i < 5; i++)
							f.ignore(INT_MAX, '\n');
						getline(f, line);
						cout << center(line, 15) << "|";
						getline(f, line);
						cout << center(line, 15) << "|";
						getline(f, line);
						cout << center(line, 15) << "|";
						getline(f, line);
						cout << center(line, 15) << "|";
						getline(f, line);
						cout << center(line, 15) << "|";
						getline(f, line);
						cout << center(line, 15) << "|" << endl;
						cout << string(155, '-') << endl;
						break;
					}
					else
					{
						for (int i = 0; i < 13; i++)
							f.ignore(INT_MAX, '\n');
					}
				}
				f.close();
			}

		}
		else
		{
			for (int i = 0; i < t+1; i++)
				fin.ignore(INT_MAX, '\n');
		}
	}
	fin.close();

	return;
}
void viewLecture()
{
	cout << "		======== Lecturers ========" << endl;
	string line;
	ifstream fout;
	fout.open("./TextFiles/Lecturers.txt");
	if (fout.fail())
	{
		printf("Failed to open the file Lecturers.txt!\n");
		return;
	}
	getline(fout, line);
	int n = stoi(line);
	cout << " " << string(103, '-') << "\n";
	cout << "|" << center("L.Name", 40) << "|" << center("Email", 40) << "|"
		<< center("Degree", 10) << "|" << center("Gender", 10) << "|" << endl;
	cout << " " << string(103, '-') << "\n";
	for (int i = 0; i < n; i++)
	{
		fout.ignore(INT_MAX, '\n');
		fout.ignore(INT_MAX, '\n');

		getline(fout, line);
		cout << "|" << center(line, 40) << "|";
		getline(fout, line);
		cout << center(line, 40) << "|";
		getline(fout, line);
		cout << center(line, 10) << "|";
		getline(fout, line);
		cout << center(line, 10) << "|";
		fout.ignore(INT_MAX, '\n');
		cout << endl;
		cout << " " << string(103, '-') << "\n";
	}
	fout.close();

}
void ListOfCourse(Semester curS)
{
	string sem = curS.semester;
	string h = curS.year;
	string line;
	cout << "Here is the list of class  " << endl;
	ifstream fout;
	fout.open("./TextFiles/Classes.txt");
	getline(fout, line);
	int n = stoi(line);
	for (int i = 0; i < n; i++)
	{
		getline(fout, line);
		cout << line << endl;
	}
	fout.close();
	cout << "Enter your class : ";
	string y;
	getline(cin, y);
	ifstream fin;
	fin.open("./TextFiles/"+h+"_"+sem+"_" + y + "_Schedules.txt");
	if (fin.fail())
	{
		printf("Failed to open this file!\n");
		return;
	}
	int x;
	getline(fin, line);
	x = stoi(line);
	cout << std::string(219, '-') << "\n";
	cout << "|" << center("C.ID", 10) << "|" << center("C.Name", 40) << "|"
		<< center("L.ShortN", 10) << "|" << center("L.Name", 30) << "|"
		<< center("L.Email", 30) << "|" << center("L.Degree", 15) << "|"
		<< center("L.Gender", 10) << "|" << center("S.Date", 10) << "|"
		<< center("E.Date", 10) << "|" << center("DoW", 5) << "|"
		<< center("S.Time", 10) << "|" << center("E.Time", 10) << "|"
		<< center("Room", 15) << "|" << endl;
	cout << std::string(219, '-') << "\n";
	for (int i = 0; i < x; i++)
	{
		getline(fin, line);
		cout << "|" << center(line, 10) << "|";
		getline(fin, line);
		cout << center(line, 40) << "|";
		getline(fin, line);
		cout << center(line, 10) << "|";
		getline(fin, line);
		cout << center(line, 30) << "|";
		getline(fin, line);
		cout << center(line, 30) << "|";
		getline(fin, line);
		cout << center(line, 15) << "|";
		getline(fin, line);
		cout << center(line, 10) << "|";
		getline(fin, line);
		cout << center(line, 10) << "|";
		getline(fin, line);
		cout << center(line, 10) << "|";
		getline(fin, line);
		cout << center(line, 5) << "|";
		getline(fin, line);
		cout << center(line, 10) << "|";
		getline(fin, line);
		cout << center(line, 10) << "|";
		getline(fin, line);
		cout << center(line, 15) << "|";
		cout << endl;
		cout << std::string(219, '-') << "\n";
		fin.ignore(INT_MAX, '\n');
	}

	fin.close();
}
void viewStudentofAcourse(Semester cursem)
{
	string line;
	string sem = cursem.semester;
	string year = cursem.year;
	string classID;
	string courseID;
	printf("Enter course ID : ");
	getline(cin, courseID);
	printf("Enter class ID : ");
	getline(cin, classID);
	ifstream fin;
	fin.open("./TextFiles/"+year + "_" + sem + "_" + courseID + "_" + classID + "_" + "Students.txt");
	if (fin.fail())
	{
		printf("Failed to open this file!\n");
		return;
	}
	getline(fin, line);
	int nWeeks = stoi(line);
	getline(fin, line);
	int n = stoi(line);
	cout << "	       ======== Students of Course " << courseID << " =======" << endl;
	cout << string(10 + 30 + 10 + 15 + 10 + 6, '-') << endl;
	cout << '|' << center("Student ID", 10) << '|'
		<< center("Full name", 30) << '|'
		<< center("Gender", 10) << '|'
		<< center("Birth Date", 15) << '|'
		<< center("Status", 10) << '|' << endl;
	cout << string(10 + 30 + 10 + 15 + 10 + 6, '-') << endl;
	for (int i = 0; i < n; i++)
	{
		getline(fin, line);
		cout << "|" << center(line, 10) << "|";
		getline(fin, line);
		cout << center(line, 30) << "|";
		getline(fin, line);
		cout << center(line, 10) << "|";
		getline(fin, line);
		cout << center(line, 15) << "|";
		getline(fin, line);
		if (stoi(line) == 1) cout << center("Active", 10) << '|' << endl;
		else cout << center("Inactive", 10) << '|' << endl;
		for (int i = 0; i < 5 + nWeeks; i++)
			fin.ignore(INT_MAX, '\n');
		cout << string(10 + 30 + 10 + 15 + 10 + 6, '-') << endl;
	}
	fin.close();
}