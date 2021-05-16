#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<cstring>
#include<ctime>
#include<vector>
#include<stdlib.h>
#include<string>
#include<conio.h>
#include<windows.h>

//structure for maintaining start time, end time of session and user input
struct userData
{
	time_t start_time;
	time_t end_time;
	char** input;
};
// structure for maintaining the records of the user that will be save in stats file
struct userStats
{
	char name[50];
	time_t timeTaken;
	float speed;
	float accuracy;
};

//Function to write into array
char** writingToArray(int , int);

//Function which will display the text to be typed
void displayText(char** disp, int rows);

//Function which will take the typed input
void takingInput(userData& d, int r);

//Function to calculate stats form userData 
void statsCalculator(userStats& s, userData& d, char** disp, int r);

//Function to display stats of user from userStats and userData
void displayStats(userStats& s, userData& d);

//Function to resize the console windoe
void sizing_the_console_window();

//Function to display the first page of Typing tutor
void firstScreen();

//Function to go to particular position on console
void goto_coor(COORD pos);

//Function to refresh console info
CONSOLE_SCREEN_BUFFER_INFO refresh_console_info();

//Function to create a box of 6x50 dimension
void boxCreation();

//Function to highlight the menu item
void arrowHere(int realPosition, int arrowPosition);

//Function to display Welcome Screen of tutor
void mainScreen(int position);

//Function to take userName input
void firstPage(userStats& s);

//function to read Previous Stats
void statsDisplayFromFile();

//Function to write Players Data to file
void writingStatsToFile(userStats &temp);
