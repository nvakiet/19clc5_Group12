#include "../Headers/SearchViewS+A.h"


void CSVScoreboard(Course B)
{

	string y = "Students", path = "./TextFiles/";
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
		fout << "[NO]" << ";" << "[ID]" << ";" << "[First Name]" << ";" << "[Last Name]" << ";" << "[Gender]" << ";" << "[BirthDate]" << ";" << "[Midterm]" << ";" << "[Final]" << ";" << "[Bonus]" << ";" << "[Total]" << endl;
		for (int i = 0; i < B.nStudents; i++)
		{
			size_t found = B.studentArr[i].fullname.find_last_of(" ");
			fout << z << ";" << B.studentArr[i].ID << ";" << B.studentArr[i].fullname.substr(0, found) << ";" << B.studentArr[i].fullname.substr(found + 1) << ";" << B.studentArr[i].gender << ";";
			fout << setfill('0') << right << B.studentArr[i].birthDate.tm_year + 1900 << '-'
				<< setw(2) << B.studentArr[i].birthDate.tm_mon + 1 << '-'
				<< setw(2) << B.studentArr[i].birthDate.tm_mday;
			fout << ";" << B.board[i].midterm << ";" << B.board[i].final << ";" << B.board[i].bonus << ";" << B.board[i].total << "\n";
			z++;
		}
		fout.close();
		cout << "Export successfully!" << endl;
	}
}
void CSVAttendance(Course B, string*& classdate)
{
	string y = "Students", path = "./TextFiles/";
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
		fout << "[NO]" << ";" << "[ID]" << ";" << "[First Name]" << ";" << "[Last Name]" << ";" << "[Gender]" << ";" << "[BirthDate]";
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
	cout << string(116, '-') << "\n";
	cout << "|" << center("Student ID", 15) << "|" << center("S.Name", 18) << "|"
		<< center("S.Gender", 10) << "|" << center("S.BirthDate", 13) << "|"
		<< center("Active", 10) << "|"
		<< center("Mid Term", 10) << "|" << center("Final", 10) << "|"
		<< center("Bonus", 10) << "|" << center("Total", 10) << "|" << endl;
	cout << string(116, '-') << "\n";
	for (int i = 0; i < B.nStudents; i++)
	{
		getline(fin, line);
		B.studentArr[i].ID = line;
		cout << "|" << center(line, 15) << "|";

		getline(fin, line);
		B.studentArr[i].fullname = line;
		cout << center(line, 18) << "|";

		getline(fin, line);
		B.studentArr[i].gender = line.front();
		cout << center(line, 10) << "|";

		getline(fin, line);
		B.studentArr[i].birthDate = sToDate(line);
		cout << center(line, 13) << "|";

		getline(fin, line);
		B.studentArr[i].active = stoi(line);
		cout << center(line, 10) << "|";

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
		cout << string(116, '-') << "\n";
	}
	fin.close();

	CSVScoreboard(B);
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
			cout << classdate[j] << " ";
			if (*(B.checkList + i * B.nWeeks + j) == true) cout << "Attended" << endl;
			else cout << "X" << endl;
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
	CSVAttendance(B, classdate);
	delete[]classdate;
	delete[]B.checkList;
	delete[]B.studentArr;
}
bool viewcheckin(Account user)
{
	string ID = user.studentProfile.ID;//Truyen thong tin ID vao bien ID
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
			for (int j = 0; j < B.nWeeks; j++)
			{
				cout << classdate[j] << " ";
				if (*(B.checkList + i * B.nWeeks + j) == true) cout << "Attended" << endl;
				else cout << "X" << endl;
			}
			cout << endl;
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
			for (int i = 0; i < 4; i++)
				fin.ignore(INT_MAX, '\n');
			getline(fin, line);
			cout << "Mid : " << line << endl;
			getline(fin, line);
			cout << "Final : " << line << endl;
			getline(fin, line);
			cout << "Bonus : " << line << endl;
			getline(fin, line);
			cout << "Total : " << line << endl;
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
	string ID = user.studentProfile.ID;
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
	for (int i = 0; i < n; i++)
	{
		getline(fin, line);
		if (line == ID)
		{
			cout << "=======SCHEDULES======= " << endl;
			for (int j = 0; j < 2; j++)
				fin.ignore(INT_MAX, '\n');
			getline(fin, line);
			int t = stoi(line);
			for (int j = 0; j < t; j++)
			{
				string courseID, classID;
				getline(fin, courseID, ' ');
				getline(fin, classID);
				ifstream f;

				f.open("./TextFiles/" + year + "_" + s + "_" + classID + "_" + h + ".txt");
				getline(f, line);
				int num = stoi(line);
				for (int i = 0; i < num; i++)
				{
					getline(f, line);
					if (line == courseID)
					{
						cout << line << endl;
						getline(f, line);
						cout << line << endl;
						for (int i = 0; i < 5; i++)
							f.ignore(INT_MAX, '\n');

						getline(f, line);
						cout << "Start date : " << line;
						getline(f, line);
						cout << "  End date : " << line << endl;
						getline(f, line);
						cout << "Day of week : " << line << endl;
						getline(f, line);
						cout << "Start time : " << line;
						getline(f, line);
						cout << "  End time : " << line << endl;
						getline(f, line);
						cout << "Room : " << line << endl;
						cout << endl;
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
			for (int i = 0; i < 6; i++)
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
	for (int i = 0; i < n; i++)
	{
		fout.ignore(INT_MAX, '\n');
		fout.ignore(INT_MAX, '\n');
		getline(fout, line);
		cout << "Lecturer name : " << line << endl;
		getline(fout, line);
		cout << "Email : " << line << endl;
		getline(fout, line);
		cout << "Academic degree: " << line << endl;
		getline(fout, line);
		cout << "Gender : " << line << endl;
		fout.ignore(INT_MAX, '\n');
		cout << endl;
	}
	fout.close();

}
void ListOfCourse(Semester curS)
{
	string sem = curS.semester;
	string h = "2019-2020";
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
	cin >> y;
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
	cout << std::string(178, '-') << "\n";
	cout << "|" << center("C.ID", 10) << "|" << center("C.Name", 30) << "|"
		<< center("L.ShortN", 10) << "|" << center("L.Name", 15) << "|"
		<< center("L.Email", 25) << "|" << center("L.Degree", 15) << "|"
		<< center("L.Gender", 10) << "|" << center("S.Date", 10) << "|"
		<< center("E.Date", 10) << "|" << center("DoW", 5) << "|"
		<< center("S.Time", 10) << "|" << center("E.Time", 10) << "|"
		<< center("Room", 5) << "|" << endl;
	cout << std::string(178, '-') << "\n";
	for (int i = 0; i < x; i++)
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
		cout << center(line, 25) << "|";
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
		cout << center(line, 5) << "|";
		cout << endl;
		cout << std::string(178, '-') << "\n";
		fin.ignore(INT_MAX, '\n');
	}

	fin.close();
}