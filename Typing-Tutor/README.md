# Typing tutor
### It is a console based application to test your typing skills. This application is designed specifically for windows operating system.

Following are the source files of the project
* headerMain.h
* Welcome_page.cpp
* engine.cpp
* TypingTutorMain.cpp

## FILE: headerMain.h:
This file hold all the libraries and declaration of the global functions.

* CONSOLE_SCREEN_BUFFER_INFO refresh_console_info();
* void boxCreation();
* void arrowHere(int realPosition, int arrowPosition);
* void mainScreen(int position);
* void firstPage(userStats& s);
* void storeData(userStats& s,userStats* );
* void readUserStats(userStats*);
* void writingStatsToFile(userStats*);
* void statsDisplay(userStats*);

_The above metioned are some of the functions that are declared in the header file_

* #pragma once
* #include< fstream>
* #include< cstring>
* #include< ctime>
* #include< vector>
* #include< string>
* #include< conio.h>
* #include<windows.h>

_The above metioned are some of the libraries listed in the header file_

## FILE: Welcome_page.cpp:
This source file contains front page and navigation menu of the application. It contains the user interface of the application.

_Following are the functions used along with their functionaltiy:_

* __sizing_the_console_window()__
 This function is used for resizing the console window, so that every time the application executes it open in a fixed size window. Following are the windows api function used for achieving this task-
    * GetStDHandle -> for retreiving the handle to the standard output stream
    * GetConsoleScreenBufferInfo -> for retreving all the console properties like coordinates, text attributes, window size.
    * GetWindowRect -> will give us the pointer(handle) to the windows
    * MoveWindow -> this function uses the pointer which we got from the preivous function to resize the window. Along with the pointer this function will take the new dimensions as the parameter.
* __arrowHere()__
This function is used for changing the text attributes(changing the color and placing a arrow at the begining) for the menu item which is currently selected.
* __goto_coor()__
This used for changing the coordinates. This function is used thorughout the souce file with the same functionality. It uses-
    * SetConsoleCursorPosition() -> move to the new positio. This function receives the HANDLE and new coordinates as the arguments.
* __refresh_console_info()__
This the function that will hold all the values of the CONSOLE_SCREEN_BUFFER_INFO structure, and for this purpose it uses-
    * GetConsoleScreenBufferInfo() -> for receiving all the information of that structure and it returns a pointer to CONSOLE_SCREEN_BUFFER_INFO structure.
* __firstScreen()__
The purpose of this function is to manage the welcome screen(the first screen that the user will encounter).
* __boxCreation()__
The main objective of this function is to draw a box like structure around the menu list.
* __mainScreen()__
It contains all the menu list to nagivate to different section of the application. 

## FILE: engine.cpp
The file contain the core logic of the program. Displaying the typing content, taking user input, storing user data and displaying it back are some of the basic functionality of this file. Following are the functions defined in this file.

* __createArray()__
Used for creating a 2-D array of 10 X 80. This function have no direct calls but is directly used by various functions.
* __readFromFile()__
This is where we are reading the content of the sample text file which is the source of information that will be displayed.For storing all the data of text file, a vector is used and a temporary string type variable is used for reading a particular line from that file.
* __writingToArray()__
This function is for storing some specific lines(that will be displayed) in the array.
* __displayText()__
For displaying the array that is created in the previous function.
* __takingInput()__
The objective of this function is to note down the starting time, ending time an the user input and all the details will be saved in a structure with the name _UserData_ is used.
* __statsCalculator()__
This is where we compare the user data with the origianl data and based on the calculation-> speed,accuracy, and time taken is determined.
* __displayStats()__
This function will display the performance report of the user and for displaying the time it will call another function by the name -> _displayTime()_.
* __storeData()__
This function is the link between the user data structure and the output file data. _writingStatsToFile()_ fucntion is followed by this function._writingStatsToFile()_ will actually write the data back to the database file.
*__readUserStats()__
If a user wants to see the previous stats or his performance. He will indirectly call this function. This function will read all the data from the stats file and then _statsDisplay()_ function will be called to display the stats on the console window.

## FILE: TypingTutorMain.cpp
This is the main file that will integrate an use all other file of the project.
Following is the functionality of the __main()__ function.

 -> First of all this file will call the  __sizing_the_console_window()__ to resize the application window.

 -> It will read the previous stats of the users.

 -> Then the user input will be recorded and based on that the desired opertion will be performed.

 This main function will keep on executing until the user select  the exti option. After selecting that option the program will terminate.
