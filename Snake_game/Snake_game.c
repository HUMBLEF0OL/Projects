// DEVELOPED BY AMIT RANA
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define N 20 // width of the field
#define M 40 // height of the field

int i, j, Field[N][M]; // field of play
int x, y;              // coordinates of snake
int Gy, Head, Tail;    //Gy is the temp variable for snake body ; head and tail pointer of snake
int Game;              // game status
int Frogs;
int a, b; // coordinates of the frog
int var, dir, score, HighScore, Speed;

FILE *f;

void snakeInitialization()
{
    f = fopen("highscore.txt", "r");
    fscanf(f, "%d", &HighScore);
    fclose(f);

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            Field[i][j] = 0; // initially setting null value to each coordinate of the field
        }
    }

    x = N / 2;
    y = M / 2; // initial coordinates of the snake
    Gy = y;    //Gy is the temporary variable for printing the body of the snake
    Head = 5;
    Tail = 1;
    Game = 0;
    Frogs = 0; //initially number of forgs will be 0
    dir = 'd';
    score = 0, Speed = 99; //intial speed will be 99 an score will be 0

    for (i = 0; i < Head; i++)
    {
        Gy++;
        Field[x][Gy - Head] = i + 1; //setting the values for the body of the snake
    }
}

void print()
{
    for (i = 0; i <= M + 1; i++)
    {
        if (i == 0)
        {
            printf("\t\t\t\t%c", 201);
        }
        else if (i == M + 1)
        {
            printf("%c", 187);
        }
        else
        {
            printf("%c", 205);
        }
    }

    printf("\n");

    for (i = 0; i < N; i++)
    {
        printf("\t\t\t\t%c", 186);

        for (j = 0; j < M; j++)
        {
            if (Field[i][j] == 0)
                printf(" ");
            if (Field[i][j] > 0 && Field[i][j] != Head)
            {
                printf("%c", 219); // printing the body of the snake excluding head
            }
            if (Field[i][j] == Head)
                printf("%c", 254); //printing the head of the snake
            if (Field[i][j] == -1)
                printf("%c", 15); //printing the frog on the screen
            if (j == M - 1)
                printf("%c\n", 186);
        }
    }

    for (i = 0; i <= M + 1; i++)
    {
        if (i == 0)
        {
            printf("\t\t\t\t%c", 200);
        }
        else if (i == M + 1)
        {
            printf("%c", 188);
        }
        else
        {
            printf("%c", 205);
        }
    }
    printf("\n\n");

    for (i = 0; i <= M + 1; i++)
    {
        if (i == 0)
        {
            printf("\t\t\t\t%c", 201);
        }
        else if (i == M + 1)
        {
            printf("%c", 187);
        }
        else
        {
            printf("%c", 205);
        }
    }
    printf("\n");
    printf("\t\t\t\t%c     CURRENT SCORE: %d HIGH SCORE: %d   %c\n", 186, score, HighScore, 186);
    for (i = 0; i <= M + 1; i++)
    {
        if (i == 0)
        {
            printf("\t\t\t\t%c", 200);
        }
        else if (i == M + 1)
        {
            printf("%c", 188);
        }
        else
        {
            printf("%c", 205);
        }
    }
}
void ResetScreenPosition()
{
    // handle is used for handling some sort of problems
    HANDLE hOut; // hOut is a hanle type variable, that provides the hanle to the console of our program
    //(hanle-Is sort of like a reference. Usually an integer or pointer value that refers to some object, )
    // COORD-coordinates (gives - coordinates of a character cell in a console screen)
    COORD Position;                         // creating a Position variable of COORD type for taking coordinate input
    hOut = GetStdHandle(STD_OUTPUT_HANDLE); //hOut is used for handling the standard output of our program
    //setting the new coordinates of our program
    Position.X = 0;
    Position.Y = 0;
    //setting the Console cursor position with the help of hout to position coordiantes
    SetConsoleCursorPosition(hOut, Position);
}

void Random()
{
    srand(time(0));      //creating the complete random values with help of sran function using time
    a = 1 + rand() % 18; //x coordinates of the frog
    b = 1 + rand() % 38; //y coordinates of the frog
    // if there is no frog on the screen and that particular field is empty(i.e snake is not present at that location) then
    if (Frogs == 0 && Field[a][b] == 0)
    {
        // we will set a frog to 1
        Field[a][b] = -1; // setting the fiel index to -1 to represent that the location is occupied now
        Frogs = 1;
        //increasing the speed
        if (Speed > 10 && score != 0)
            Speed = Speed - 5;
    }
}

int get_value()
{
    if (_kbhit())
        return _getch();
    else
        return -1; //returning nothing
}

void movement()
{
    var = get_value();
    var = tolower(var);
    // abs(dir-var)>5 means that in order to change the direction then the difference between the ASCII value must be
    // greater than 5 that means
    // when moving in w direction we will not be able to move in s direction as w-s<5
    // similarly a-d<5
    // so by doing that we can ensure that the movement is done in the correct direction
    if (((var == 'd' || var == 'a') || (var == 'w' || var == 's')) && (abs(dir - var) > 5))
        dir = var;
    //right movement
    if (dir == 'd')
    {
        y++; // incrementing the y coordinate
        if (y == M - 1)
            y = 0; //when the snake reaches the border it shoul come out from other side
        if (Field[x][y] != 0 && Field[x][y] != -1)
            GameOver();        //condition when snake bytes itself
        if (Field[x][y] == -1) //when snake eats the foot
        {
            Frogs = 0;  // setting the food to 0 (as at that point no food will be present on the screen)
            score += 5; // increaing the score by 5
            Tail -= 1;  // increasing the length of the snake by decreasing the tail elngth
        }
        Head++;             //incremementing the head
        Field[x][y] = Head; // increasing the length of the snake
    }

    //left movement
    if (dir == 'a')
    {
        y--;
        if (y == 0)
            y = M - 1;
        if (Field[x][y] != 0 && Field[x][y] != -1)
            GameOver();
        if (Field[x][y] == -1)
        {
            Frogs = 0;
            score += 5;
            Tail -= 1;
        }
        Head++;
        Field[x][y] = Head;
    }

    //upward movement
    if (dir == 'w')
    {
        x--;
        if (x == -1)
            x = N - 1;
        if (Field[x][y] != 0 && Field[x][y] != -1)
            GameOver();
        if (Field[x][y] == -1)
        {
            Frogs = 0;
            score += 5;
            Tail -= 1;
        }
        Head++;
        Field[x][y] = Head;
    }

    if (dir == 's')
    {
        x++;
        if (x == N - 1)
            x = 0;
        if (Field[x][y] != 0 && Field[x][y] != -1)
            GameOver();
        if (Field[x][y] == -1)
        {
            Frogs = 0;
            score += 5;
            Tail -= 1;
        }
        Head++;
        Field[x][y] = Head;
    }
}
// managing the tail of the snake
void TailRemove()
{
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            // checking whether a particular field value matches the tail or not
            if (Field[i][j] == Tail)
            {
                // if the field value matche then we will set that field value to 0
                Field[i][j] = 0;
            }
        }
    }
    //shifting the tail to the next index
    // so that when this function is called the tail will be at +1 position
    Tail++;
}

void GameOver()
{
    printf("\a");
    Sleep(1500); //wait for 1500 mili second
    system("Cls");

    if (score > HighScore)
    {
        for (i = 0; i <= M + 1; i++)
        {
            if (i == 0)
            {
                printf("\t\t\t\t%c", 201);
            }
            else if (i == M + 1)
            {
                printf("%c", 187);
            }
            else
            {
                printf("%c", 205);
            }
        }
        printf("\n");
        printf("\t\t\t\t%c CONGRATULATIONS NEW HIGH REGISTERED! -> %d   %c\n", 186, score, 186);
        for (i = 0; i <= M + 1; i++)
        {
            if (i == 0)
            {
                printf("\t\t\t\t%c", 200);
            }
            else if (i == M + 1)
            {
                printf("%c", 188);
            }
            else
            {
                printf("%c", 205);
            }
        }
    }
    printf("\n");
    system("pause");
    f = fopen("highscore.txt", "w");
    fprintf(f, "%d", score);
    fclose(f);

    system("Cls");
    printf("\n\n\n\n\n\t\t\t\t**************");
    printf("\n\t\t\t\t!! GAME OVER !!\n\n");
    printf("\t\t\t\t YOUR SCORE : %d \n\n", score);
    printf("\t\t\tPress ENTER to play again or ESC to exit ... \n");

    while (1)
    {
        var = get_value();
        if (var == 13)
        {
            Game = 0; // when enter key is pressed
            snakeInitialization();
            break;
        }
        else if (var == 27)
        {
            Game = 1; // when escape key is pressed
            break;
        }
    }
    system("Cls");
}
void main()
{
    do
    {
        for (i = 0; i < 60; i++)
        {
            if (i == 0)
            {
                printf("\t\t\t\t%c", 201);
            }
            else if (i == 59)
            {
                printf("%c", 187);
            }
            else
            {
                printf("%c", 205);
            }
        }

        printf("\n");
        printf("\t\t\t\t%c  Welcome to the Snake game.(Developed by - AMIT RANA)    %c\n", 186, 186);
        printf("\t\t\t\t%c               PRESS ANY KEY TO CONTINUE...               %c\n", 186, 186);
        for (i = 0; i < 60; i++)
        {
            if (i == 0)
            {
                printf("\t\t\t\t%c", 200);
            }
            else if (i == 59)
            {
                printf("%c", 188);
            }
            else
            {
                printf("%c", 205);
            }
        }
        getch();
        printf("\n\n\t\t\t\t\t      %c%c%c%c%c%c GAME INSTRUCTIONS %c%c%c%c%c%c\n", 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178, 178);

        printf("\n\n\t\t\t      -> Use 'w' for UPWARD MOVEMENT"
               "\n\n\t\t\t      -> Use 's' for DOWNWARD MOVEMENT"
               "\n\n\t\t\t      -> Use 'a' for LEFT MOVEMENT"
               "\n\n\t\t\t      -> Use 'd' for RIGHT MOVEMENT"
               "\n\n\t\t\t      -> You will be provided foods at the several coordinates of the \n\t\t\t\t screen which you have to eat. "
               "\n\n\t\t\t      -> Everytime you eat a food the length of the snake will \n\t\t\t\t be increased by 1 element along with speed and thus the score.");
        printf("\n\n\n");

        for (i = 0; i < 60; i++)
        {
            if (i == 0)
            {
                printf("\t\t\t\t%c", 201);
            }
            else if (i == 59)
            {
                printf("%c", 187);
            }
            else
            {
                printf("%c", 205);
            }
        }
        printf("\n");
        printf("\t\t\t\t%c         Press any key to play an 'Esc' to quite...       %c\n", 186, 186);
        for (i = 0; i < 60; i++)
        {
            if (i == 0)
            {
                printf("\t\t\t\t%c", 200);
            }
            else if (i == 59)
            {
                printf("%c", 188);
            }
            else
            {
                printf("%c", 205);
            }
        }
        if (getch() == 27)
            exit(0);
        Sleep(1500);
        system("cls");
        snakeInitialization();

        while (Game == 0)
        {
            print();
            ResetScreenPosition();
            Random();
            movement();
            TailRemove();
            Sleep(Speed);
        }
    } while (1);
}
