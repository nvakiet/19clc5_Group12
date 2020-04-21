#include "../Headers/staff-class.h"
bool importClassCSV(string& path) /* <--- Ko can tham so o day, chi nhung ham chay ngam hay tinh toan trong chuong trinh moi can*/ {
	//^^^^^^^^^^Da doi lai ten ham cho ro rang chuc nang, nhu the code se clean hon
	cout << "Enter csv file path: ";	//./TextFiles/19CLC10-student.csv <- file csv co the o bat cu dau tren may nguoi dung import vao
	//T dem file csv ra khoi folder project de gia su truong hop file no co the o bat cu duong dan nao
	cin >> path; //Nhu tren, neu da keu nguoi dung nhap vao thi ko can tham so
	ifstream fin;
	fin.open("./TextFiles/19CLC10-student.csv" ); //.open(path), vi nguoi dung da nhap duong dan cua minh vao path

	if (!fin.is_open()) {
		cerr << "Cannot open file";
		return false;
	}
	//  vvvvv Ko phai class nao cung co n = 3
	int n = 3;	//Nen keu nguoi dung tu nhap si so lop n va ten lop de code thuan tien hon, li do se noi o duoi
	string DoB, sex;
//	vvvvvvv Nen su dung struct Student vi du lieu nhap vao chi thuoc ve Student, goi struct account se ton them memory cho cac members khac ngoai student
	Account* newUser;
	newUser = new Account[n];

	//Cac file csv thuc te luon co tieu de moi cot, nen phai skip 1 hang roi moi doc file vao mang
	for (int i = 0; i < n; i++) {
		//Tham khao lai cac field thong tin da duoc edit trong file csv
		getline(fin, newUser[i].studentProfile.ID, ';'); //<-- VS cua t bao warning o dong nay: loi C6385 - Reading invalid data from 'newUser'
		getline(fin, newUser[i].studentProfile.fullname, ';');
		getline(fin, sex, ';');
		if (sex == "1")
			newUser[i].studentProfile.gender = 1;
		else newUser[i].studentProfile.gender = 0;

		getline(fin, DoB);
		newUser[i].studentProfile.birthDate = sToDate(DoB);
	}
	fin.close();
	/* Cac viec can lam trong ham nay sau khi load tu cai file csv vao mang 
	Viec 1: Load them 1 mang student tu file Students.txt:
	- Khi load thi skip dong password va dong trong o cuoi moi 1 student, con dong username cung la ID cua student
	- n duoc de o dong dau cua file nay;
	- Sau khi load vao mang thu 2 xong, doi chieu students cua 2 mang voi nhau
	- Neu co student nao trong mang load tu file csv co ID (ko dc so sanh bang ten) KO trung voi tat ca ben Students.txt thi:
		+ Mo lai file Students.txt bang ofstream, che do append
		+ LUU Y XU LY TRUONG HOP LAN CHAY DAU TIEN KO CO FILE STUDENTS.TXT/FILE RONG VI CHUA CO DANG KI STUDENT NAO
		+ TRU FILE STAFFS.TXT RA THI CAC FILE CON LAI KO DC TU TAO TU BEN NGOAI DE CHUONG TRINH HOAT DONG TRONG MOI TRUONG HOP
		+ Luu thong tin student do tu mang CSV vao Students.txt
		+ Dong username dung ID;
		+ Dong password se dung birthDate cua student;
		+ Password dung ham sha256 de bao ve mat khau + code trong ham printDate cua file general.cpp nhung bo may dau '-' ra
		+ Ko print lai ID vi da co o username
		+ Co the tham khao code o switch case 3 tu ham changePassword de tranh xung dot thong tin giua 2 ham
	
	Viec 2: Kiem tra xem ten lop nguoi dung nhap vao co bi trung trong Classes.txt ko
	- Dong dau cua Classes.txt la n so class da duoc nap vao he thong thanh file .txt
	- Neu ten lop bi trung thi hoi nguoi dung co muon overwrite file csv voi class dang co trong he thong ko:
		+ Neu nguoi dung chon co thi in het mang student da load tu file csv vao file txt trong he thong
		+ Neu chon ko, thong bao tien trinh import bi huy, tra ve false
	- Neu ten lop ko bi trung thi in mang student cua file csv vao file .txt moi nhu binh thuong
	- Viec in thong tin student co the tham khao code trong case 3 cua ham changePassword
	- LUU Y: XUYEN SUOT HAM NAY LUON SU DUNG MANG STUDENT, KO DUNG GI TOI STRUCT ACCOUNT
	- LUU Y XU LY TRUONG HOP LAN CHAY DAU TIEN KO CO FILE CLASSES.TXT/FILE RONG VI CHUA CO IMPORT CLASS NAO
		TRU FILE STAFFS.TXT RA THI CAC FILE CON LAI KO DC TU TAO TU BEN NGOAI DE CHUONG TRINH HOAT DONG TRONG MOI TRUONG HOP
	- LUU Y: CU PHAP TEN CUA FILE .TXT MOI TAO KHI IMPORT LA "[Ten class nhap hoi dau ham]_Students.txt"
		VD: fout.open(systemPath + classID + "_Students.txt")
		Co the dat 1 bien string systemPath = "./TextFiles/" va 1 bien string fileEx = "_Students.txt" neu thich
	*/
	ofstream fout;
	fout.open("./TextFiles/Test.txt", ios::app);

	if (!fout.is_open()) {
		cerr << "Cannot open file";
		return false;
	}

	for (int i = 0; i < n; i++) {
		newUser[i].username = newUser[i].studentProfile.ID;

		string newyyyy = to_string(newUser[i].studentProfile.birthDate.tm_year + 1900);
		string newmm = to_string(newUser[i].studentProfile.birthDate.tm_mon + 1);// MM va DD phai co so 0 o truoc neu be hon 10
		string newdd = to_string(newUser[i].studentProfile.birthDate.tm_mday);
		// ^ Neu chi de truyen vao Students.txt lam password thi tham khao code trong ham printDate cua file general.cpp
		// nhung bo dau '-' ra
		string newpass = newyyyy + newmm + newdd;
		newUser[i].password = newpass;

		newUser[i].studentProfile.active = true;

		fout << newUser[i].username << endl
		     << newUser[i].password << endl
			 << newUser[i].studentProfile.fullname << endl
			 << newUser[i].studentProfile.gender << endl
		     << newUser[i].studentProfile.birthDate.tm_year + 1900 << '-'
			 << newUser[i].studentProfile.birthDate.tm_mon + 1 << '-'
			 << newUser[i].studentProfile.birthDate.tm_mday << endl
			 << newUser[i].studentProfile.active << endl;
		fout << endl;
	}
	fout.close();
	delete[] newUser;
	newUser = nullptr;

	return true;
}