/*
  -------------------------------	
  |	DEVELOPED BY:				|
  |			-> YOGENDER SINGH   |
  |			-> AMIT RANA		|
  |			-> ISHA AGGARWAL	|
  -------------------------------
*/
#include"headerMain.h"
#define MAX 3
#define MIN 1
using namespace std;
static COORD pos,boxTop,boxBottom;
static CONSOLE_SCREEN_BUFFER_INFO coninfo;
static HWND console = GetConsoleWindow();
static RECT r;
static HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
static userData d;
static userStats s;
static char e = 186;
static int position = 1;
static char keyPressed = 0;
static char name[50];
static vector<userStats> statsList;
static int i = 0;
int main()
{
	sizing_the_console_window();
	firstScreen();
	system("cls");
	while (1)
	{
		system("cls");
		mainScreen(position);
		keyPressed = _getch();
		fflush(stdin);
		if (keyPressed == 80 && position != MAX)
		{
			position++;
		}
		else if (keyPressed == 72 && position != MIN)
		{
			position--;
		}
		else
		{
			position = position;
		}
		if (keyPressed == 13 && position == 1)
		{
			system("cls");
			statsDisplayFromFile();
			cout << "\n\nPressing any key will take you back to MAIN MENU." << endl;
			system("pause");
		}
		else if (keyPressed == 13 && position == 2)
		{
			firstPage(s);
			system("cls");
			char** disp = writingToArray(5, 80);
			displayText(disp, 5);			
			takingInput(d, 5);
			statsCalculator(s, d, disp, 5);
			system("cls");
			displayStats(s, d);
			cout << endl;
			writingStatsToFile(s);
			cout << endl;
			system("pause");
			system("cls");
		}
		else if (keyPressed == 13 && position == 3)
		{
			exit(0);
		}
	}
}
