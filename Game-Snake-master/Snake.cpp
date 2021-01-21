#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<string>
#include<time.h>
#include<iostream>
using namespace std;
#define consoleWidth 80
#define consoleHeight 20
struct ToaDo
{
	int x, y;
};
ToaDo Head, Tail, Body;
ToaDo TD[401];
int demTD = 0, demV = 90;
int DoDai = 2, CheckAnV = 0, CheckV = 0, ktDoAnV = 0;
int DiemNew = 0, DiemOLD = 0, DiemV = 0;
ToaDo DoAn, DoAnV;
int doKho = 100;
int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	return coninfo.dwCursorPosition.X;
}
int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
	return coninfo.dwCursorPosition.Y;
}
void gotoxy(short int x, short int y)
{
	static HANDLE  h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x,y };
	SetConsoleCursorPosition(h, c);
}
void SetTeColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0; wAttributes |= color;
	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void ThongTin()
{
	SetTeColor(13);
	gotoxy(15, 2);
	cout << "Moi Thong Tin Chi Tiet Vui Long Lien He: ";
	SetTeColor(14);
	cout << "\n\t\t\t=>For Boi Group<=";
	cout << "\n\n";
}
void Reset();
void intro();
void Menu();
void Menu_Chon(int chon, int choncu);
void Xuat_Diem();
int DieuKhien(int n, int x, int y);
void DiNgangPhai(int x, int y);
void DiLen(int x, int y);
void DiXuong(int x, int y);
void DiNgangTrai(int x, int y);
void Xoa_Tail(ToaDo cuoi);
ToaDo ViTriDau();
bool Check_Snake_Die();
void In_Do_An(ToaDo DoAn);
void Xoa_Do_An(ToaDo& DoAn);
void Tao_Do_An();
void Tao_Do_An_Dac_Biet();
void Khung();
void GameOver(char Text, int x, int y);
int main()
{
	Menu();
	system("cls");
	Khung();
	srand(unsigned int(time(NULL)));
	gotoxy(2, 10);
	Head = ViTriDau();
	Body = Head;
	Body.x = 1;
	TD[0] = Body;
	TD[1] = Head;
	Tao_Do_An();
	DiNgangPhai(Head.x, Head.y);
}
int DieuKhien(int n, int x, int y)
{
	SetTeColor(1); // mau cua ran va bang diem luc choi
	if (DiemNew > DiemOLD)
	{
		Tao_Do_An();
		DiemOLD = DiemNew;
		ktDoAnV = 0;
	}
	if (DiemNew != 0 && DiemNew % 5 == 0 && CheckV == 0 && ktDoAnV == 0) //diemnew la diem cua ban
	{
		Tao_Do_An_Dac_Biet();
		CheckV = 1;
	}
	if (CheckV == 1)
	{
		demV--; //demV la dem so buoc cua snake 
	}
	if (CheckV == 0 || demV == 0)
	{
		demV = 90;
		Xoa_Do_An(DoAnV);
		CheckV = 0;
		ktDoAnV = 1;
	}
	Xuat_Diem(); //xuat score 
	if (Check_Snake_Die() == true) //check kiem tra chet hay chua
		if (_kbhit())
		{
			int a = _getch();
			if (n == 4 || n == 2)
			{
				if (a == 115)
					DiXuong(x, y);
				if (a == 119)
					DiLen(x, y);
			}
			if (n == 1 || n == 3)
			{
				if (a == 100)
					DiNgangPhai(x, y);
				if (a == 97)
					DiNgangTrai(x, y);
			}
			if (a == 112)
			{
				gotoxy(1, 21);
				cout << "                 ";
				while (1)
				{
					if (_kbhit())
					{
						int p = _getch();
						if (p == 112)
							break;
						if (p == 27)
						{
							Reset();
							main();
						}
					}
					gotoxy(10, 21);
					Sleep(100);
					SetTeColor(15);
					cout << "Dang tam dung, bam P de tiep tuc -- Bam ESC de quay lai MENU";
					gotoxy(10, 21);
					Sleep(100);
					cout << "                                                            ";
				}

			}
			// s = 115     == 1 
			// a = 97		== 2
			// w = 119		== 3
			// d = 100		== 4
		}
	// GAME OVER
	if (Check_Snake_Die() == false)
	{
		system("cls");
		SetTeColor(12); // mau game over
		GameOver('G', 10, 2);
		GameOver('A', 20, 2);
		GameOver('M', 28, 2);
		GameOver('E', 38, 2);
		GameOver('O', 48, 2);
		GameOver('V', 58, 2);
		GameOver('E', 67, 2);
		GameOver('R', 75, 2);
		cout << "\n\n\t\t\t\t    Diem cua ban la : " << DiemNew + DiemV << endl;
		char tmp;		SetTeColor(15);
		cout << "\n\t\t\t    ===Bam ENTER de bat dau game moi===\n\t\t\t\t===Bam ESC de thoat Game===";
		while (1)
		{
			tmp = _getch();
			if (tmp == 13)
			{
				Reset();
				main();
			}
			if (tmp == 27)
			{
				cout << endl;
				cout << "Dang roi Game" << endl;
				cout << "Thoat trong 3s";
				Sleep(3000);
				exit(1);
			}
		}
		exit(1);
	}
	return 0;
}
void DiNgangPhai(int x, int y)
{
	while (1)
	{
		Sleep(doKho);
		gotoxy(++x, y);
		putchar(219);
		if (x == DoAn.x && y == DoAn.y)
		{
			DiemNew++;
			DoDai++;
			doKho -= 3;
			putchar(7);
			goto daira;
		}
		if (x == DoAnV.x && y == DoAnV.y)
		{
			CheckAnV = 1;
			CheckV = 0;
			DiemV += demV;
			ktDoAnV = 1;
		}
		Xoa_Tail(TD[0]);
		for (int i = 0; i < DoDai - 1; i++)
			TD[i] = TD[i + 1];
	daira:;
		gotoxy(x, y);
		Head = ViTriDau();
		TD[DoDai - 1] = Head;
		DieuKhien(4, x, y);
	}
}
void DiNgangTrai(int x, int y)
{
	int dem = 0;
	while (1)
	{
		Sleep(doKho);
		gotoxy(--x, y);
		putchar(219);
		if (x == DoAn.x && y == DoAn.y)
		{
			DiemNew++;
			DoDai++;
			putchar(7);
			doKho -= 3;
			goto daira;
		}
		if (x == DoAnV.x && y == DoAnV.y)
		{
			CheckAnV = 1;
			CheckV = 0;
			DiemV += demV;
			ktDoAnV = 1;
		}
		Xoa_Tail(TD[0]);
		for (int i = 0; i < DoDai - 1; i++)
			TD[i] = TD[i + 1];
	daira:;
		gotoxy(x, y);
		Head = ViTriDau();
		TD[DoDai - 1] = Head;
		DieuKhien(4, x, y);
	}
}
void DiLen(int x, int y)
{
	while (1)
	{
		Sleep(doKho);
		gotoxy(x, --y);
		putchar(219);
		if (x == DoAn.x && y == DoAn.y)
		{
			DiemNew++;
			DoDai++;
			putchar(7);
			doKho -= 3;
			goto daira;
		}
		if (x == DoAnV.x && y == DoAnV.y)
		{
			CheckAnV = 1;
			CheckV = 0;
			DiemV += demV;
			ktDoAnV = 1;
		}
		Xoa_Tail(TD[0]);
		for (int i = 0; i < DoDai - 1; i++)
			TD[i] = TD[i + 1];
	daira:;
		gotoxy(x, y);
		Head = ViTriDau();
		TD[DoDai - 1] = Head;
		DieuKhien(3, x, y);
	}
}
void DiXuong(int x, int y)
{
	while (1)
	{
		Sleep(doKho);
		gotoxy(x, ++y);
		putchar(219);
		if (x == DoAn.x && y == DoAn.y)
		{
			DiemNew++;
			DoDai++;
			putchar(7); //tao am thanh an moi
			doKho -= 3;
			goto daira;
		}
		if (x == DoAnV.x && y == DoAnV.y)
		{
			CheckAnV = 1;
			CheckV = 0;
			DiemV += demV;
			ktDoAnV = 1;
		}
		Xoa_Tail(TD[0]);
		for (int i = 0; i < DoDai - 1; i++)
			TD[i] = TD[i + 1];
	daira:;
		gotoxy(x, y);
		Head = ViTriDau();
		TD[DoDai - 1] = Head;
		DieuKhien(3, x, y);
	}
}
ToaDo ViTriDau()
{
	ToaDo Dau;
	Dau.x = wherex();
	Dau.y = wherey();
	return Dau;
}
// moi binh thuong
void Tao_Do_An()
{
	int check = 0;
	do
	{
		DoAn.x = 2 + rand() % 76;
		DoAn.y = 2 + rand() % 18;
		for (int i = 0; i < DoDai; i++)
		{
			if (TD[i].x == DoAn.x && TD[i].y == DoAn.y)
			{
				check = 1;
				break;
			}
		}
		if (check == 0)
		{
			SetTeColor(6);
			In_Do_An(DoAn);
		}
	} while (check == 1);
}
// moi dac biet
void Tao_Do_An_Dac_Biet()
{
	int check = 0;
	do
	{
		DoAnV.x = 2 + rand() % 76; // Tao toa do moi dac biet ngau nhien
		DoAnV.y = 2 + rand() % 18;
		if (DoAnV.x == DoAn.x && DoAnV.y == DoAn.y) // kiem tra do an dac biet co trung voi do an thuong khong
		{
			check = 1;
			continue;
		}
		for (int i = 0; i < DoDai; i++)
		{
			if (TD[i].x == DoAnV.x && TD[i].y == DoAnV.y)
			{
				check = 1;
				break;
			}
		}
		if (check == 0)
		{
			SetTeColor(4);
			In_Do_An(DoAnV);
		}
	} while (check == 1);
}
void In_Do_An(ToaDo DoAn)
{
	gotoxy(DoAn.x, DoAn.y);
	cout << "O";
	SetTeColor(1);
}
void Xoa_Do_An(ToaDo& DoAn)
{
	gotoxy(DoAn.x, DoAn.y);
	DoAn.x = 0;
	DoAn.y = 0;
}
void Xuat_Diem()
{
	gotoxy(1, 22);
	cout << "Bam P de tam dung" << endl;
	gotoxy(1, 23);
	cout << "DIEM CUA BAN LA: " << DiemNew + DiemV;
}
void Xoa_Tail(ToaDo cuoi)
{
	gotoxy(cuoi.x, cuoi.y);
	cout << " ";
}
// kiem tra chet
bool Check_Snake_Die()
{
	if (Head.x == 0 || Head.x == 80 || Head.y == 1 || Head.y == 20) // ch?m tu?ng 
		return false; // da chet
	for (int i = 0; i < DoDai - 1; i++)
		if (TD[i].x == Head.x && TD[i].y == Head.y)  // ch?m thân
			return false; //da chet
	return true;// chua chet
}
void intro()//thong tin
{
	system("cls");
	SetTeColor(12);
	ThongTin();
	SetTeColor(15);
	cout << "\t\t===Bam ENTER de quay lai MENU=== ";
	char enter;
	while (1)
	{
		enter = _getch();
		if (enter == 13)
			break;
	}
	Menu();
}
void Khung()
{
	SetTeColor(5);
	// tuong phai
	for (int i = 1; i <= consoleHeight; i++)
	{
		gotoxy(consoleWidth, i);
		putchar(3);
	}
	// tuong duoi
	for (int i = 0; i < consoleWidth; i++)
	{
		gotoxy(i, consoleHeight);
		putchar(3);
	}
	// tuong trai
	for (int i = 2; i < consoleHeight; i++)
	{
		gotoxy(0, i);
		putchar(3);
	}
	// tuong tren
	for (int i = 0; i < consoleWidth; i++)
	{
		gotoxy(i, 1);
		putchar(3);
	}
}// Ham tao khung 

void GameOver(char Text, int x, int y)
{
	if (Text == 65 || Text == 97)
	{
		gotoxy(x, y);     cout << "   00  ";     Sleep(20);
		gotoxy(x, y + 1); cout << " 00  00";     Sleep(20);
		gotoxy(x, y + 2); cout << " 00  00";     Sleep(20);
		gotoxy(x, y + 3); cout << " 000000";     Sleep(20);
		gotoxy(x, y + 4); cout << " 00  00";     Sleep(20);
	}
	else if (Text == 69 || Text == 101)
	{
		gotoxy(x, y);     cout << " 000000";     Sleep(20);
		gotoxy(x, y + 1); cout << " 00    ";     Sleep(20);
		gotoxy(x, y + 2); cout << " 000000";     Sleep(20);
		gotoxy(x, y + 3); cout << " 00    ";     Sleep(20);
		gotoxy(x, y + 4); cout << " 000000";     Sleep(20);
	}
	else if (Text == 82 || Text == 114)
	{
		gotoxy(x, y);     cout << " 0000000";   Sleep(20);
		gotoxy(x, y + 1); cout << " 00    00";   Sleep(20);
		gotoxy(x, y + 2); cout << " 00 000 ";    Sleep(20);
		gotoxy(x, y + 3); cout << " 00  00  ";   Sleep(20);
		gotoxy(x, y + 4); cout << " 00    00";   Sleep(20);
	}

	else if (Text == 77 || Text == 109)
	{
		gotoxy(x, y);     cout << " 00    00";  Sleep(20);
		gotoxy(x, y + 1); cout << " 000  000";  Sleep(20);
		gotoxy(x, y + 2); cout << " 00 00 00";  Sleep(20);
		gotoxy(x, y + 3); cout << " 00    00";  Sleep(20);
		gotoxy(x, y + 4); cout << " 00    00";  Sleep(20);
	}

	else if (Text == 71 || Text == 103)
	{
		gotoxy(x, y);     cout << "  000000";     Sleep(20);
		gotoxy(x, y + 1); cout << " 00     ";     Sleep(20);
		gotoxy(x, y + 2); cout << " 00   000";     Sleep(20);
		gotoxy(x, y + 3); cout << " 00    0";     Sleep(20);
		gotoxy(x, y + 4); cout << "  000000";     Sleep(20);
	}
	else if (Text == 79 || Text == 111)
	{
		gotoxy(x, y);     cout << "  00000";     Sleep(20);
		gotoxy(x, y + 1); cout << " 00   00";     Sleep(20);
		gotoxy(x, y + 2); cout << " 00   00";     Sleep(20);
		gotoxy(x, y + 3); cout << " 00   00";     Sleep(20);
		gotoxy(x, y + 4); cout << "  00000";     Sleep(20);
	}
	else if (Text == 86 || Text == 118)
	{
		gotoxy(x, y);     cout << "00    00";   Sleep(20);
		gotoxy(x, y + 1); cout << "00    00";   Sleep(20);
		gotoxy(x, y + 2); cout << "00    00";    Sleep(20);
		gotoxy(x, y + 3); cout << " 00  00";   Sleep(20);
		gotoxy(x, y + 4); cout << "   00";   Sleep(20);
	}

}
// ve chu SNAKE
void DrawingText(char Text, int x, int y)
{
	if (Text == 65 || Text == 97)
	{
		gotoxy(x, y);     cout << "   00  ";     Sleep(40);
		gotoxy(x, y + 1); cout << " 00  00";     Sleep(40);
		gotoxy(x, y + 2); cout << " 00  00";     Sleep(40);
		gotoxy(x, y + 3); cout << " 000000";     Sleep(40);
		gotoxy(x, y + 4); cout << " 00  00";     Sleep(40);
	}
	else if (Text == 69 || Text == 101)
	{
		gotoxy(x, y);     cout << " 000000";     Sleep(40);
		gotoxy(x, y + 1); cout << " 00    ";     Sleep(40);
		gotoxy(x, y + 2); cout << " 000000";     Sleep(40);
		gotoxy(x, y + 3); cout << " 00    ";     Sleep(40);
		gotoxy(x, y + 4); cout << " 000000";     Sleep(40);
	}
	else if (Text == 75 || Text == 107)
	{
		gotoxy(x, y);     cout << "00    00";   Sleep(40);
		gotoxy(x, y + 1); cout << "00   00 ";   Sleep(40);
		gotoxy(x, y + 2); cout << "00 00  ";    Sleep(40);
		gotoxy(x, y + 3); cout << "00  00  ";   Sleep(40);
		gotoxy(x, y + 4); cout << "00    00";   Sleep(40);
	}

	else if (Text == 78 || Text == 110)
	{
		gotoxy(x, y);     cout << "00     00";  Sleep(40);
		gotoxy(x, y + 1); cout << "00 0   00";  Sleep(40);
		gotoxy(x, y + 2); cout << "00  0  00";  Sleep(40);
		gotoxy(x, y + 3); cout << "00   0 00";  Sleep(40);
		gotoxy(x, y + 4); cout << "00     00";  Sleep(40);
	}

	else if (Text == 83 || Text == 115)
	{
		gotoxy(x, y);     cout << " 000000";     Sleep(40);
		gotoxy(x, y + 1); cout << " 00    ";     Sleep(40);
		gotoxy(x, y + 2); cout << " 000000";     Sleep(40);
		gotoxy(x, y + 3); cout << "     00";     Sleep(40);
		gotoxy(x, y + 4); cout << " 000000";     Sleep(40);
	}

}
void Menu()
{
	system("cls");
	int chon = 1, choncu = 0; // bien chon là bien chon chuc nang , choncu la vi tri mui ten cu in de khoang trang lên trong ham menuchon().
	SetTeColor(11);
	DrawingText('S', 10, 2);
	DrawingText('N', 19, 2);
	DrawingText('A', 29, 2);
	DrawingText('K', 38, 2);
	DrawingText('E', 47, 2);
	SetTeColor(10);
	gotoxy(28, 8);
	cout << "Play Game" << endl;
	gotoxy(29, 9);
	cout << "Do Kho" << endl;
	gotoxy(28, 10);
	cout << "Huong Dan";
	gotoxy(28, 11);
	cout << "Thong Tin\n";
	Menu_Chon(1, 0); // ham in mui ten 
	while (1)
	{
		char phim;
		if (_kbhit())
		{
			phim = _getch();
			if (phim == 13) // phim Enter thoat while 
				break;
			if (phim == 80) // di xuong 
			{
				if (chon < 4) // tranh loi an nhieu lan 
				{
					chon++;
					choncu = chon - 1;
					Menu_Chon(chon, choncu);
				}
			}
			if (phim == 72) // di len 
			{
				if (chon > 1) // tranh loi an nhieu lan 
				{
					chon--;
					choncu = chon + 1;
					Menu_Chon(chon, choncu);
				}
			}
		}
	}
	if (chon == 1) // chon = 1 thi choi game nen dung ham menu().
		return;
	if (chon == 2)
	{
		system("cls");
		char chondokho;
		cout << "Bam 1 2 3 chon muc do: " << endl;
		cout << "1.De" << endl;
		cout << "2.Binh Thuong" << endl;
		cout << "3.Kho" << endl;

		do
		{
			chondokho = _getch();
			if (chondokho < 49 || chondokho > 51)
				cout << "Do kho khong ton tai,vui long chon lai." << endl;
		} while (chondokho < 49 || chondokho > 51);
		system("cls");
		if (chondokho == 49)
		{
			doKho = 150;
			cout << "Da chon muc do DE" << endl;
		}
		if (chondokho == 50)
		{
			doKho = 90;
			cout << "Da chon muc do BINH THUONG" << endl;
		}
		if (chondokho == 51)
		{
			doKho = 40;
			cout << "Da chon muc do KHO" << endl;
		}
		SetTeColor(15);
		cout << "\n\t\t\t\t ===Bam ENTER de choi game===" << endl;
		cout << "\t\t\t\t===Bam ESC de quay lai MENU===" << endl;
		char enter;
		while (1)
		{
			enter = _getch();
			if (enter == 27)// phim 27 là phim ESC (Thoat while chay ham menu()).
				break;
			if (enter == 13)// phim 13 là Enter dung ham menu() quay lai ham main chay ham tao khung.
				return;
		}
		Menu();
	}
	if (chon == 3)
	{
		system("cls");
		cout << "- Dung 4 phim 'W', 'A', 'S', 'D' de dieu khien con ran, co gang an nhieu moi nhat co the. Ran an cang nhieu toc do cang tang." << endl;
		cout << "- Khi an duoc 5 moi binh thuong thi se xuat hien con moi dac biet ton tai trong 90 buoc di cua con ran." << endl;
		cout << "- An moi dac biet se duoc nhieu diem hon moi binh thuong. An cang nhanh, diem cang cao." << endl;
		cout << "- Nhan phim P de dung game." << endl;
		SetTeColor(15);
		cout << "\n\t\t\t\t===Bam ENTER de quay lai=== " << endl;
		char enter;
		while (1)
		{
			enter = _getch();
			if (enter == 13)
				break;
		}
		Menu();
	}
	if (chon == 4)
	{
		intro();
	}
}
void Menu_Chon(int chon, int choncu)
{
	if (chon == 1)
	{
		if (choncu == 2)
		{
			gotoxy(20, 9);
			cout << "  ";
			gotoxy(42, 9);
			cout << "  ";
		}
		gotoxy(20, 8);
		cout << "->";
		gotoxy(42, 8);
		cout << "<-";
	}
	if (chon == 2)
	{
		if (choncu == 1)
		{
			gotoxy(20, 8);
			cout << "  ";
			gotoxy(42, 8);
			cout << "  ";
		}
		if (choncu == 3)
		{
			gotoxy(20, 10);
			cout << "  ";
			gotoxy(42, 10);
			cout << "  ";
		}
		gotoxy(20, 9);
		cout << "->";
		gotoxy(42, 9);
		cout << "<-";
	}
	if (chon == 3)
	{
		if (choncu == 2)
		{
			gotoxy(20, 9);
			cout << "  ";
			gotoxy(42, 9);
			cout << "  ";
		}
		if (choncu == 4)
		{
			gotoxy(20, 11);
			cout << "  ";
			gotoxy(42, 11);
			cout << "  ";
		}
		gotoxy(20, 10);
		cout << "->";
		gotoxy(42, 10);
		cout << "<-";
	}
	if (chon == 4)
	{
		if (choncu == 3)
		{
			gotoxy(20, 10);
			cout << "  ";
			gotoxy(42, 10);
			cout << "  ";
		}
		gotoxy(20, 11);
		cout << "->";
		gotoxy(42, 11);
		cout << "<-";
	}
}// Ham ve mui ten 
void Reset()
{
	demTD = 0;
	demV = 90;
	DoDai = 2;
	CheckAnV = 0;
	CheckV = 0;
	ktDoAnV = 0;
	DiemNew = 0;
	DiemOLD = 0;
	DiemV = 0;
	doKho = 100;
}