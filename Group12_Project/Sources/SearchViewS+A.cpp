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
	printf("Enter course Name: ");
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
				cout << classdate[j] << " " << *(B.checkList + i * B.nWeeks + j) << endl;
			}
			cout << endl;
			return true;//co hoc sinh de xuat ra
		}
		else
		{
			for (int i = 0; i < 19; i++)
				fin.ignore(INT_MAX, '\n');
		}
	}
	return false;//khong co hoc sinh de xuat ra;
	fin.close();
	delete[]classdate;
	delete[]B.checkList;
	delete[]B.studentArr;
}
bool viewscore(Account user)
{
	Course B;
	string x = "Students", path = "./TextFiles/";
	string line;
	string ID=user.studentProfile.ID;
	printf("Enter years : ");
	getline(cin, B.c_semester.year);
	printf("Enter semester : ");
	getline(cin, B.c_semester.semester);
	printf("Enter course ID: ");
	getline(cin, B.courseID);
	printf("Enter course Name: ");
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
			for (int i = 0; i < 3; i++)
				fin.ignore(INT_MAX, '\n');
			getline(fin, line);
			cout << "Mid : " << line << endl;
			getline(fin, line);
			cout << "Final : " << line << endl;
			getline(fin, line);
			cout << "Bonus : " << line << endl;
			getline(fin, line);
			cout << "Total : " << line << endl;

			return true;
		}
		else
		{
			for (int i = 0; i < 19; i++)
				fin.ignore(INT_MAX, '\n');
		}
	}
	return false;//khong co hoc sinh de xuat ra;
	fin.close();
	delete[]B.studentArr;
}
