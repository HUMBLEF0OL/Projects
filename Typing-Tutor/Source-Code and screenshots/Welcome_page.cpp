#include"headerMain.h"
#define MAX 3
#define MIN 1
using namespace std;
static COORD pos,boxTop,boxBottom;
static CONSOLE_SCREEN_BUFFER_INFO coninfo;
static HWND console = GetConsoleWindow();
static RECT r;
static HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
static char c = 223, d = 219, e = 186, f = 175;
void sizing_the_console_window()
{
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdOut, &coninfo);
	GetWindowRect(console, &r);
	MoveWindow(console, 100, 100, 800, 600, true);
}
void arrowHere(int realPosition, int arrowPosition)
{
	if (realPosition == arrowPosition)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "->";
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << " ";
	}
}
void goto_coor(COORD pos)
{
	SetConsoleCursorPosition(hStdOut, pos);
}
CONSOLE_SCREEN_BUFFER_INFO refresh_console_info()
{
	GetConsoleScreenBufferInfo(hStdOut, &coninfo);
	return coninfo;
}
void firstScreen()
{
	coninfo=refresh_console_info();
	pos = { (SHORT)(coninfo.srWindow.Right / 2 - 15),(SHORT)(coninfo.srWindow.Top + 5 )};
	goto_coor(pos);
	// cout << e << e << e;
	char ascii_1 = 205,ascii_2=201,ascii_3=187,ascii_4=186,ascii_5 = 200,ascii_6 = 188;
	for (int i = 1; i <= 40; i++)
	{
		if (i == 1)
		{
			cout << ascii_2;
		}
		else if (i == 40)
		{
			cout << ascii_3;
		}
		else {
			cout << ascii_1;
		}
	}
		
	cout <<endl<<endl<< "\t\t\t\t"<<ascii_4<<"\t WELCOME TO TYPING TUTOR       "<<ascii_4<<endl;
	cout << endl << "\t\t\t\t";
	for (int i = 1; i <= 40; i++)
	{
		if (i == 1)
		{
			cout << ascii_5;
		}
		else if (i == 40)
		{
			cout << ascii_6;
		}
		else {
			cout << ascii_1;
		}
	}
	cout << endl;
	coninfo = refresh_console_info();
	goto_coor(pos = { (SHORT)(coninfo.srWindow.Right / 2 - 8),(SHORT)(coninfo.dwCursorPosition.Y + 1) });
	cout << "PRESS ANY KEY TO CONTINUE";
	_getch();
}

void boxCreation()
{
	coninfo = refresh_console_info();
	//Top line
	pos = boxTop ={ (SHORT)(coninfo.srWindow.Right / 2 - 25) , (SHORT)(coninfo.srWindow.Top + 9) };
	goto_coor(pos);
	for (int j = 0; j < 50; j++)
		cout << c;
	//Bottom line
	coninfo = refresh_console_info();
	boxBottom = pos = { (SHORT)(coninfo.srWindow.Right / 2 - 25), (SHORT)(coninfo.dwCursorPosition.Y + 6) };
	goto_coor(pos);
	for (int j = 0; j < 51; j++)
		cout << c;
	//Rule Lines
	coninfo = refresh_console_info();
	goto_coor(pos = { (SHORT)(coninfo.srWindow.Right/2 - 25), (SHORT)(coninfo.dwCursorPosition.Y+1 )});
	cout << f;
	cout << "Try to type as many correct words to increase up the accuracy!";
	for (int j = 0; j < 6; j++)
	{
		goto_coor(pos = { (SHORT)(coninfo.srWindow.Right/2 - 25), (SHORT)(coninfo.srWindow.Top + 9 + j) });
		cout << d;
		goto_coor(pos = { (SHORT)(coninfo.srWindow.Right/2 + 25), (SHORT)(coninfo.srWindow.Top + 9 + j) });
		cout << d;
	}

}

void mainScreen(int position)
{
	coninfo = refresh_console_info();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	goto_coor(pos = { (SHORT)(coninfo.srWindow.Right / 2 - 13), (SHORT)(coninfo.srWindow.Top + 5) });

	cout << ">> WELCOME TO TYPING TUTOR <<";

	//settextstyle(8,HORIZ_DIR,8);
	boxCreation();
	pos = boxTop;
	goto_coor(pos);
	coninfo = refresh_console_info();
	goto_coor(pos = { (SHORT)(coninfo.srWindow.Right / 2 - 10),(SHORT)(coninfo.srWindow.Top + 10) });
	arrowHere(1, position);
	cout << "Display Previous Stats\n";
	coninfo = refresh_console_info();
	goto_coor(pos = { (SHORT)(coninfo.srWindow.Right / 2 - 6),(SHORT)(coninfo.dwCursorPosition.Y + 1 )});
	arrowHere(2, position);
	cout << "Start Typing\n";
	coninfo = refresh_console_info();
	goto_coor(pos = { (SHORT)(coninfo.srWindow.Right / 2 - 2),(SHORT)(coninfo.dwCursorPosition.Y + 1 )});
	arrowHere(3, position);
	cout << "Exit\n\n\n";
}
