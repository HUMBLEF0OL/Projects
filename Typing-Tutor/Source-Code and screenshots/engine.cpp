#include"headerMain.h"
using namespace std;
static HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
static CONSOLE_SCREEN_BUFFER_INFO coninfo;
static COORD pos;
static int i = 0;
//a function that is use for creating 2-D arrays
static char **createArray(int r = 10, int c = 80)
{
    //creating a 2-d array of 'r' rows;
    char **arr = new char *[r];
    for (int i = 0; i < r; i++)
    {
        //allocating the space for each row
        arr[i] = new char[c];
    }
    return arr;
}

//creating a function to read the data from the file and returns a vector
static void readFromFile(vector<string>& original)
{
    //creating a string that will hold the content of the current line from the file
    string current;
    //input stream variable_name
    ifstream file;
    file.open("sample.txt", ios::in);
    while (!file.eof())
    {
        //taking a line from the file and storing it in the vector
        getline(file, current);
        original.push_back(current);
    }
    file.close();
}

//this function is used for storing the required content of the vector in the disp array
char** writingToArray(int r = 10, int c = 80)
{ 
	vector<string> original;
	//a local vector that will store that content which we are getting from readFromFile() function
    readFromFile(original);
    //creating a disp array that will be used to display the content to be type on the screen
    char **disp = createArray(r, 81);
    int random_line;
    // for completely random number generator using srand
    srand(time(0));
    for (int i = 0; i < r; i++)
    {
        //here original.size() will return the total number of rows of the vector
        random_line = 1 + rand() % (original.size() - 1);
        for (int j = 0; j < c; j++)
        {
            //storing the content of the required vector lines in the disp array
            disp[i][j] = original[random_line][j];
            disp[i][80] = NULL; //setting the last character to be null
        }
    }
    return disp;
}

// for displaying the content of the disp array on the console
void displayText(char **disp, int rows)
{
	cout << "\n\n\n";
    for (int i = 0; i < rows; i++)
    {
		coninfo = refresh_console_info();
		pos = { coninfo.srWindow.Left + 5,coninfo.dwCursorPosition.Y };
		goto_coor(pos);
        // this will display a total of 81 characters (the last character being null character)
        for (int j = 0; j < strlen(disp[i]); j++)
        {
            cout << disp[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

//function for taking the input from the user
// here we will use userData structure
void takingInput(userData &d, int r)
{
    //creating a array where the user input will be stored
    // here d is the structure variable
    d.input = createArray(10, 81);
    cout << endl;
	coninfo = refresh_console_info();
	pos = { coninfo.srWindow.Left + 5,coninfo.dwCursorPosition.Y };
	goto_coor(pos);
    system("pause");
	cout << endl;
	coninfo = refresh_console_info();
	pos = { coninfo.srWindow.Right / 2 - 6,coninfo.dwCursorPosition.Y };
	goto_coor(pos);
    cout << "-> Start typing <-" << endl
         << endl;
	d.start_time = time(NULL); // initializing it to the present time
	cin.ignore(100, '\n');
	fflush(stdin);
    for (int i = 0; i < r; i++)
    {
		coninfo = refresh_console_info();
		pos = { coninfo.srWindow.Left + 5,coninfo.dwCursorPosition.Y };
		goto_coor(pos);
        cin.get(d.input[i], 81);
        //ignoring the content of buffer(here it will ignore extra 100 characters) before taking the new input
        cin.ignore(100, '\n');
        fflush(stdin);
    }
    d.end_time = time(NULL);
}

void statsCalculator(userStats &s, userData &d, char **disp, int r)
{
    float correct_counter = 0;
    float invalid_counter = 0;
    s.timeTaken = difftime(d.end_time, d.start_time);
    int charCounter = 0;
    float timeInMinutes = ((float)s.timeTaken) / 60;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < strlen(disp[i]); j++)
        {
            if (d.input[i][j] == disp[i][j])
            {
                correct_counter++;
            }
            else
            {
                invalid_counter++;
            }
        }
        charCounter += strlen(d.input[i]);
    }
    s.accuracy = (correct_counter * 100) / (correct_counter + invalid_counter);
    s.speed = ((float)charCounter) / (6 * timeInMinutes);
}

static void displayTime(time_t t)
{
    tm *tPtr = localtime(&t);
    cout << (tPtr->tm_hour) << " : " << (tPtr->tm_min) << " : " << (tPtr->tm_sec);
}

void displayStats(userStats &s, userData &d)
{
	cout << endl;
	coninfo = refresh_console_info();
	pos = { coninfo.srWindow.Right / 2 - 9,coninfo.dwCursorPosition.Y };
	goto_coor(pos);
    cout <<" PERFORMANCE REPORT "<< endl
         << endl;
    cout << "Test started at ->";
    displayTime(d.start_time);
	cout << endl;
    cout << "\nTest ended at ->";
    displayTime(d.end_time);
	cout << endl;
    cout << "\nTotal time taken to finish test -> " << s.timeTaken << " seconds" << endl;
    cout << "\nSpeed: " << s.speed << "wpm" << endl;
    cout << "\nAccuracy: " << s.accuracy << "%" << endl;
}

void firstPage(userStats& s)
{
	system("cls");
	coninfo = refresh_console_info();
	pos = { coninfo.srWindow.Right / 2 - 7,coninfo.srWindow.Bottom / 2 - 1 };
	goto_coor(pos);
	cout << "ENTER USERNAME -> " << endl;
	coninfo = refresh_console_info();
	pos = { coninfo.srWindow.Right / 2 - 5,coninfo.dwCursorPosition.Y + 1 };
	goto_coor(pos);
	fflush(stdin);
	cin.get(s.name,'\n');
}

void writingStatsToFile(userStats& temp)
{
	fstream file;
	file.open("Data.bin", ios::out|ios::app|ios::binary);
	if (file.is_open())
	{		
		file.write(reinterpret_cast<char*>(&temp), sizeof(temp));
	}
	else
	{
		cout << "\nError while opening the file.";
	}
	file.close();
}

static void statsDisplay(userStats &data)
{
    cout << "\t\t" << data.name << "\t\t";
	cout <<data.timeTaken <<"\t\t";
    cout << data.speed << "\t\t";
	cout <<data.accuracy << endl;
}

void statsDisplayFromFile()
{
	fstream file;
	userStats temp;
    cout << endl<<"\t        NAME\t" << "TIME TAKEN(seconds)\t" << "SPEED(wpm)\t" << "ACCURACY\t" << endl<<endl;
	file.open("Data.bin", ios::in| ios::binary);
	if (file.is_open())
	{
		while (1)
		{
			/*
			reinterpret_cast is used for converting one pointer type to another
			here we are converting a structure pointer to a char pointer
			(&temp),sizeof(userstats)-> temp is a struct pointer that goes up to the total size(one record) of the structure 
			based on the char pointer that we got we will iterates to that and display the stats!
            		*/
			file.read(reinterpret_cast<char*>(&temp), sizeof(userStats));
			if (file.eof())
				break;
			statsDisplay(temp);			
		}
	}
	else
	{
		cout << "\n\t\t\t\t\t~NO RECORD FOUND!";
	}
	file.close();
}

