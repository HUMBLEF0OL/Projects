# Snake-Game
## Building the classic snake game

Library used in the game
-	Stdio.h		for standard input and ouput
-	Stdlib.h 	for using functions like rand
-	Windows.h	for functions like sleep, and keywords like *HANDLE* and *CORD*
-	Time.h		time function which is used with rand function
-	Conio.h 	(console input an output) for using the functions like kbhit
srand() function: It is used for generating the random values. It is included in the stdlib libraray. THe parameter given to the srand is time() 
Kbhit() function: It gives a non zero value a key is pressed. It has been used to take the input from the user.
N,M are the length and width of the field of play.

**Following are the functions used program**

1. *snakeInitialization()*:
  -	Opening a highscore file to get the previous high score
  -	Setting the field to null in the beginning
  -	Setting the x,y coordinates of the snake
  -	Setting the initial state of the game (running)
  -	Setting Frog variable to zero that means no food is present in the field
  -	Setting the default direction of the movement to left
  -	Setting the score to 0
  -	Setting the movement speed to 99

2. *print()*:
  -	Defining the top border of the field with some special symbols with the help of the starting loop
  -	Displaying the current score along with the previous high score
  -	The second loop is used for printing the side borders along with the snake if it is present on that particular line
  -	The third loop is used for printing the lower section of the border
  
3. *ResetScreenPosition()*:
  - Handling the standard output with the help of handle varaible
  - Setting the new coordinates with the help of COORD variable

  (once the loop iterations is completed we have to move the cursor to the begining of the screen by clearing the previous content so that it looks like the game is          running in the same frame and for that I have used these handle an coord keywords for handling the console screen and setting the new coordinates to the starting position)
  
4. *Random()*:
  -	Srand(time(0)) is used for generating the complete random locations for food
  -	After eating the food the speed of the snake will increase
  
5. *getch_value()*:
  -	This function is used for taking the input from the keyboard

6. *movement()*:
  - This function is receiving the input from the input function and then converting the received input to lower case so that the movement can be done 
    irrespective of the capital or small letters
  -	If dir == ‘d’ then we will perform the left movement and if we have reached the border the snake will come out of the other side. 
    In the if statement we are also checking whether snake has byte itself or not if so then the game will terminate. 
    Now for eating the frog in the left direction we will increase the score by 5 and tail will be decreased by one index and the head will 
    increment by one (showing the actual movement of the snake)
  -	The same logic is repeated for every direction

7. *TailRemove()*:
  -  in the first loop checking whether a particular field value matches the tail or not if the field value matche then
     we will set that field value to 0
  -   after that shifting the tail to the next index so that when this function is called the tail will be at +1 position
  
8. *GameOver()*:
  -	‘\a’ is used for beep sound. This sound will be played when the snake bytes itself.
  -	After biting itself then screen will pause for 1500 milisec (this is done with the help of Sleep() function). After that we will clear the console 
    window and print the details like your score, whether new high score have been created or not and if the new high score is created, 
    we will save the output in the highscore file.
  -	After that a message will be printed asking the user if he want to play again or want to quite.
  
9. *main()*:
  -	The main function where everything will be complied together to function as one
  -	The loop will keep on executing until Game flag turns to 1.



