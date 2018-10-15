/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* prog4nshah213hpate86.cpp
*     Description: This program is similar to program 2, where we had to create a traffic game using consol. This time around,
*                  we must create a graphical traffic game using prebuilt functions of QT-Creator. We used knowledge of arrays from
*                  improvised version of program 2 in this program. For this program we had to display specific error messages and in
*                  specific order. However, we were unable to check for error number “3. Attempt is made to move a piece on top of another piece.  Please retry.”
*
* Class: Program #4 - Graphical Traffic for CS 141, Fall 2017.
* Lab: Tue, 10 AM and Tue, 1 PM
* TA: Margi Ghandhi and Abhinav Kumar.
* System: Visual Studio 2017 on Windows 10
* Author: Harhsil Patel and Nemil Shah
*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


#include <iostream>
#include <cctype>      // for toupper()
#include <fstream>
#include "gobjects.h"
using namespace std;


// Display ID info
void displayIDInfo()
{
    cout << "Author:  Harshil Patel and Nemil Shah" << endl;
    cout << "Lab:     Tue 10am & Tue 1pm" << endl;
    cout << "Program: #4, Graphical Traffic" << endl;
    cout << endl;
}//end displayIDInfo()
 //--------------------------------------------------------------------

 // Display Instructions
void displayInstructions()
{
    cout << "Welcome to the graphical traffic game!               " << endl
        << "                                                      " << endl
        << "Move the vehicles so that the Red car (RR) can exit   " << endl
        << "the board to the right. Each move should be of the    " << endl
        << "of the form:   CDN   where:                           " << endl
        << "   C  is the vehicle to be moved                      " << endl
        << "   D  is the direction (u=up, d=down, l=left or r=right)" << endl
        << "   N  is the number of squares to move it             " << endl
        << "For example GR2  means move the G vehicle to the right" << endl
        << "2 squares.  Lower-case input such as   gr2  is also   " << endl
        << "accepted.  Enter 'reset' to reset board, or 'exit' to exit.  " << endl << endl;
}//end displayInstructions()
 //--------------------------------------------------------------------

// ReadFile function to read the file. Also used when the program is reseted
void readFile(char vehicleRead[], char directionRead[], int xPositionRead[], int yPositionRead[],
              int lengthRead[], string color[], int xlocationConvert[], int ylocationConvert[],
              int sizeReadConvert[], int &howManyVehicles, const int num, int temp1[], int temp2[])
{
        // Start Reading file ---------------------------------------------------------------
        ifstream inputFileStream;
        inputFileStream.open("board.txt");

        if(!inputFileStream.is_open())
        {
            cout << "Could not find input file board.txt.  Exiting..." << endl;
            exit( -1);
        }

        inputFileStream >> howManyVehicles;

        // For loop to read all possible 8 vehicle details
        for( int i=0; i<howManyVehicles; i++)
        {
            inputFileStream >> vehicleRead[i] >> directionRead[i] >> xPositionRead[i] >> yPositionRead[i] >> lengthRead[i];

            // Assignes spesific color to color[] array
            switch(vehicleRead[i])
            {
                case 'G': color[i]="green";  break;
                case 'Y': color[i]="yellow"; break;
                case 'M': color[i]="magenta"; break;
                case 'R': color[i]="red"; break;
                case 'B': color[i]="blue"; break;
                case 'O': color[i]="orange"; break;
                case 'C': color[i]="cyan"; break;
                case 'P': color[i]="pink"; break;
             }

            //set of algorithms that convers Row(1-6) and Column(1-6) from board.txt to x and y cordinates that QT understands
            xlocationConvert[i]= 30+40*(yPositionRead[i]-1);
            ylocationConvert[i]=30+40*(xPositionRead[i]-1);
            sizeReadConvert[i]=30+40*(lengthRead[i]-1);
            if(directionRead[i] == 'H')
            {
               temp1[i] = sizeReadConvert[i];
               temp2[i] = num;
            }
            else if(directionRead[i] == 'V')
            {
                temp1[i] = num;
                temp2[i] = sizeReadConvert[i];
            }
       }
       inputFileStream.close();  // Close the file
       // Stop Reading file ------------------------------------------------------------------
}


int main()
{

    displayIDInfo();        // Display ID info
    displayInstructions();  // Display game instructions

// **********************Creates the basic board*******************************

    // Create a graphics window, which will be used to draw graphical shapes
       GWindow graphicsWindow(300, 300);  // Size of the window
       graphicsWindow.setWindowTitle("CS 141 prog 4: Graphical Traffic"); // Title of the graphical window

       // Create Board outline
       GRect *boardRectangle = new GRect(10, 10, 270, 270);
       boardRectangle->setFilled(true);
       boardRectangle->setColor("DARKGRAY");
       graphicsWindow.add( boardRectangle);

       // Create Inner playing surface
       GRect *innerRectangle = new GRect(20, 20, 250, 250);
       innerRectangle->setFilled(true);
       innerRectangle->setColor("GRAY");
       graphicsWindow.add(innerRectangle);

       // Create Exit opining playing surface
       GRect *exitRectangle = new GRect(270, 100, 10, 50);
       exitRectangle->setFilled(true);
       exitRectangle->setColor("LIGHTGRAY");
       graphicsWindow.add(exitRectangle);

       // Create Verticle lines
       /*
       Vertical lines:
            20,20, 10,250, "lightGray"
            60,20, 10,250, "lightGray"
           100,20, 10,250, "lightGray"
           140,20, 10,250, "lightGray"
           180,20, 10,250, "lightGray"
           220,20, 10,250, "lightGray"
           260,20, 10,250, "lightGray"*/

      int vertivleLineInc = 20;
      for(int lineCount = 0; lineCount < 7; lineCount++)
      {
          GRect *verticleLineRectangle = new GRect(vertivleLineInc, 20, 10, 250);
          verticleLineRectangle->setFilled(true);
          verticleLineRectangle->setColor("LIGHTGRAY");
          graphicsWindow.add(verticleLineRectangle);
          vertivleLineInc = vertivleLineInc +40;
      }
       // Create Horizontal lines
       /* Horizontal lines:
           20,20, 250,10, "lightGray"
           20,60, 250,10, "lightGray"
          20,100, 250,10, "lightGray"
          20,140, 250,10, "lightGray"
          20,180, 250,10, "lightGray"
          20,220, 250,10, "lightGray"
          20,260, 250,10, "lightGray"  */

      int horizontal =20;
      for(int lineCount = 0; lineCount < 7; lineCount++)
      {
          GRect *horizontalLineRectangle = new GRect(20, horizontal, 250, 10);
          horizontalLineRectangle->setFilled(true);
          horizontalLineRectangle->setColor("LIGHTGRAY");
          graphicsWindow.add(horizontalLineRectangle);
          horizontal = horizontal + 40;
      }

      char vehicleRead[8]= {' '}; // Cars (G,Y,M,R.......)
      char directionRead[8] = {' '}; // Direction (U,D,R,L)
      int xPositionRead[8] = {0}; // Row
      int yPositionRead[8] = {0}; // Column

      int lengthRead[8] = {0}; // Length
      string color[8] = {" "}; // Full color name

      int xlocationConvert[8] = {0}; // Converted xPosition of 8 possible cars
      int ylocationConvert[8] = {0}; // Converted yPosition of 8 possible cars
      int sizeReadConvert[8] = {0};

      int howManyVehicles = 0;

      const int num = 30;

      int temp1[8] = {0};
      int temp2[8] = {0};

      bool winbool = false;  //Used as a switch to perform specific task when user wins
      bool resetbool = false; // when user resets the board
      bool exitbool = false; // when user exits the baord

      string userInput;  // User input
      int counter = 1; //user move count

      bool resetCheck = true; // bool for read and write file

      // Reads the initial file
      readFile(vehicleRead, directionRead, xPositionRead, yPositionRead,
               lengthRead, color, xlocationConvert, ylocationConvert,
               sizeReadConvert, howManyVehicles, num, temp1, temp2);

      // Default while loop, useful when reseting the board. specifically when writting and reading that written file.
      while (resetCheck)
      {
        // Horizontal Green car
        GRect *green = new GRect(xlocationConvert[0], ylocationConvert[0],  temp1[0], temp2[0]);
        green->setFilled(true);
        green->setColor(color[0]);
        graphicsWindow.add(green);

        // Vertical Yellow car
        GRect *yellow  = new GRect(xlocationConvert[1], ylocationConvert[1], temp1[1], temp2[1]);
        yellow->setFilled(true);
        yellow->setColor(color[1]);
        graphicsWindow.add(yellow);

        // Vertical Megenta car
        GRect *magenta  = new GRect(xlocationConvert[2], ylocationConvert[2], temp1[2], temp2[2]);
        magenta->setFilled(true);
        magenta->setColor(color[2]);
        graphicsWindow.add(magenta);

        // Horizontal Red car
        GRect *red = new GRect(xlocationConvert[3], ylocationConvert[3],  temp1[3], temp2[3]);
        red->setFilled(true);
        red->setColor(color[3]);
        graphicsWindow.add(red);

        // Vertical Blue car
        GRect *blue  = new GRect(xlocationConvert[4], ylocationConvert[4], temp1[4], temp2[4]);
        blue->setFilled(true);
        blue->setColor(color[4]);
        graphicsWindow.add(blue);

        // Vertical Orange car
        GRect *orange  = new GRect(xlocationConvert[5], ylocationConvert[5], temp1[5], temp2[5]);
        orange->setFilled(true);
        orange->setColor(color[5]);
        graphicsWindow.add(orange);

        // Horizontal Cyan car
        GRect *cyan = new GRect(xlocationConvert[6], ylocationConvert[6],  temp1[6], temp2[6]);
        cyan->setFilled(true);
        cyan->setColor(color[6]);
        graphicsWindow.add(cyan);

        // Horizontal Pink car
        GRect *pink = new GRect(xlocationConvert[7], ylocationConvert[7],  temp1[7], temp2[7]);
        pink->setFilled(true);
        pink->setColor(color[7]);
        graphicsWindow.add(pink);

        // Main While loop to perform moves
        while(red->getX() != 190)
        {
            cout << counter<< ". Your move -> ";
            cin >> userInput; // user input

            // If user wants to exit
            if(userInput == "exit")
            {
                cout<<" Thank you for playing" << endl;
                exitbool = true;
                break;
            }

            // If user wants to reset the board
            if(userInput == "reset")
            {
                counter++;
                resetbool = true;
                graphicsWindow.remove(green);
                graphicsWindow.remove(yellow);
                graphicsWindow.remove(magenta);
                graphicsWindow.remove(red);
                graphicsWindow.remove(blue);
                graphicsWindow.remove(orange);
                graphicsWindow.remove(cyan);
                graphicsWindow.remove(pink);
                for (int i = 0; i < 8; i++)
                {
                    vehicleRead[i]= ' ';
                    directionRead[i] = ' ';
                    xPositionRead[i] = 0;
                    yPositionRead[i] = 0;
                    lengthRead[i] = 0;
                    color[i] = "red";
                    xlocationConvert[i] = 0;
                    ylocationConvert[i] = 0;
                    sizeReadConvert[i] = 0;
                    howManyVehicles = 0;
                    temp1[i] = 0;
                    temp2[i] = 0;
                }

                // ----------------Start writing a file-------------------------------
                ofstream outputFileStream;
                outputFileStream.open("board.txt");

                if(!outputFileStream.is_open())
                {
                    cout << "Could not find output file board.txt.  Exiting..." << endl;
                    exit( -1);
                }

                cout << "Enter number of pieces to be placed on the new board: ";
                cin >> howManyVehicles;
                cout << "For each piece write in the color letter, direction, starting row, starting column, and length below" << endl;

                for( int i=0; i<howManyVehicles; i++)
                {
                    cin >> vehicleRead[i] >> directionRead[i] >> xPositionRead[i] >> yPositionRead[i] >> lengthRead[i];
                }

                outputFileStream << howManyVehicles;
                for( int i=0; i<howManyVehicles; i++)
                {
                    outputFileStream << vehicleRead[i] << " " << directionRead[i] << " " << xPositionRead[i] << " " << yPositionRead[i] << " " << lengthRead[i] << endl;
                }

                outputFileStream.close();
                // ----------------Stop writing a file-------------------------------
                readFile(vehicleRead, directionRead, xPositionRead, yPositionRead,
                         lengthRead, color, xlocationConvert, ylocationConvert,
                         sizeReadConvert, howManyVehicles, num, temp1, temp2);
                counter = 1; // resets Counter
                break;
            }

            //Convert first two entry of user input to Capital letters and last to an number
            userInput.at(0) = toupper(userInput.at(0));
            userInput.at(1) = toupper(userInput.at(1));
            userInput.at(2) = userInput.at(2) - '0';

            // Switch for each case of 8 possible cars
            // Each case are similer only x or y are being added or takenoff depending on oriantation of the Car (V or H)
            switch(userInput.at(0))
            {
                    // Case for car Green,
                    case 'G': if(userInput.at(1)=='R')
                              {
                                counter++; // Increments Counter by 1
                                int numMove = 0; // keeps track of move made, and if piece reaches the edge and moves are still left then it will use numMove to undo the moves

                                // If user wants to move 2 units then it will repeat 2 times
                                for(int i=1;i<=userInput.at(2); i++)
                                {
                                    numMove = numMove + 1;

                                    // Error check to make sure the piece does not leave the board
                                    if(green->getX()==190)
                                    {
                                        cout<<" Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
                                        for(int i=numMove-1;i>0; i--)
                                        {
                                            green->move(-40,0); // undoes the steps if piece is off the edge
                                        }
                                        break;
                                    }
                                    else // Makes a move if no error encounter
                                    {
                                        green->move(40,0);
                                    }
                                 }
                              }
                              else if(userInput.at(1)=='L')
                              {
                                    counter++; // Increments Counter by 1
                                    int numMove = 0; // keeps track of move made, and if piece reaches the edge and moves are still left then it will use numMove to undo the moves

                                    // If user wants to move 2 units then it will repeat 2 times
                                    for(int i=1;i<=userInput.at(2); i++)
                                    {
                                        numMove = numMove + 1;

                                        // Error check to make sure the piece does not leave the board
                                        if(green->getX()==30)
                                        {
                                            cout<<" Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
                                            for(int i=numMove-1;i>0; i--)
                                            {
                                                green->move(40,0); // undoes the steps if piece is off the edge
                                            }
                                            break;
                                        }
                                        else // Makes a move if no error encounter
                                        {
                                            green->move(-40,0);
                                        }
                                    }

                              }
                              //Error if user tries to move horizontal car anywhere other then right or left
                              else if((userInput.at(1)!='R') || (userInput.at(1)!='L'))
                              {
                                    counter++; // Increments Counter by 1
                                    cout<< "Attempt was made to move a piece in the wrong direction.  Please retry." << endl;
                              }
                              break;
                    //END OF case 'G'--------------------------------------------------------------------------------------------------

                    case 'R': if(userInput.at(1)=='R')
                              {
                                    counter++;
                                    int numMove = 0;
                                    for(int i=1;i<=userInput.at(2); i++)
                                    {
                                        numMove = numMove + 1;
                                        if(red->getX()==190)
                                        {
                                            cout<<" Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
                                            for(int i=numMove-1;i>0; i--)
                                            {
                                                red->move(-40,0);
                                            }
                                            break;
                                        }
                                        else
                                        {
                                            red->move(40,0);
                                        }
                                    }
                              }
                              else if(userInput.at(1)=='L')
                              {
                                    counter++;
                                    int numMove = 0;
                                    for(int i=1;i<=userInput.at(2); i++)
                                    {
                                        numMove = numMove + 1;
                                        if(red->getX()==30)
                                        {
                                            cout<<" Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
                                            for(int i=numMove-1;i>0; i--)
                                            {
                                                red->move(40,0);
                                            }
                                            break;
                                        }
                                        else
                                        {
                                            red->move(-40,0);
                                        }
                                    }
                              }
                              else if((userInput.at(1)!='R') || (userInput.at(1)!='L'))
                              {
                                    counter++;
                                    cout<< "Attempt was made to move a piece in the wrong direction.  Please retry." << endl;
                              }
                              break;
                    //END OF case 'R'--------------------------------------------------------------------------------------------------

                    case 'C': if(userInput.at(1)=='R')
                              {
                                    counter++;
                                    int numMove = 0;
                                    for(int i=1;i<=userInput.at(2); i++)
                                    {
                                        numMove = numMove + 1;
                                        if(cyan->getX()==190)
                                        {
                                            cout<<" Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
                                            for(int i=numMove-1;i>0; i--)
                                            {
                                                cyan->move(-40,0);
                                            }
                                            break;
                                        }
                                        else
                                        {
                                            cyan->move(40,0);
                                        }

                                    }
                              }
                              else if(userInput.at(1)=='L')
                              {
                                    counter++;
                                    int numMove = 0;
                                    for(int i=1;i<=userInput.at(2); i++)
                                    {
                                        numMove = numMove + 1;
                                        if(cyan->getX()==30)
                                        {
                                            cout<<" Attempt is made to move a piece off the edge of the board.  Please retry." << endl;

                                            for(int i=numMove-1;i>0; i--)
                                            {
                                                cyan->move(40,0);
                                            }
                                            break;
                                        }
                                        else
                                        {
                                            cyan->move(-40,0);
                                        }
                                    }
                              }
                              else if((userInput.at(1)!='R') || (userInput.at(1)!='L'))
                              {
                                    counter++;
                                    cout<< "Attempt was made to move a piece in the wrong direction.  Please retry." << endl;
                              }
                              break;
                    //END OF case 'C'--------------------------------------------------------------------------------------------------

                    case 'P': if(userInput.at(1)=='R')
                              {
                                    counter++;
                                    int numMove = 0;
                                    for(int i=1;i<=userInput.at(2); i++)
                                    {
                                        numMove = numMove + 1;
                                        if(pink->getX()==150)
                                        {
                                            cout<<" Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
                                            for(int i=numMove-1;i>0; i--)
                                            {
                                                pink->move(-40,0);
                                            }
                                            break;
                                        }
                                        else
                                        {
                                            pink->move(40,0);
                                        }
                                    }
                              }
                              else if(userInput.at(1)=='L')
                              {
                                    counter++;
                                    int numMove = 0;
                                    for(int i=1;i<=userInput.at(2); i++)
                                    {
                                        numMove = numMove + 1;
                                        if(pink->getX()==30)
                                        {
                                            cout<<" Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
                                            for(int i=numMove-1;i>0; i--)
                                            {
                                                pink->move(40,0);
                                            }
                                            break;
                                        }
                                        else
                                        {
                                            pink->move(-40,0);
                                        }
                                    }
                              }
                              else if((userInput.at(1)!='R') || (userInput.at(1)!='L'))
                              {
                                    counter++;
                                    cout<< "Attempt was made to move a piece in the wrong direction.  Please retry." << endl;
                              }
                              break;

                     // All vertical cars now
                     //END OF case 'P'--------------------------------------------------------------------------------------------------

                    case 'Y': if(userInput.at(1)=='D')
                              {
                                    counter++;
                                    int numMove = 0;
                                    for(int i=1;i<=userInput.at(2); i++)
                                    {
                                        numMove = numMove + 1;
                                        if(yellow->getY()==150)
                                        {
                                            cout<<" Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
                                            for(int i=numMove-1;i>0; i--)
                                            {
                                                yellow->move(0,-40);
                                            }
                                            break;
                                        }
                                        else
                                        {
                                            yellow->move(0,40);
                                        }
                                    }
                              }
                              else if(userInput.at(1)=='U')
                              {
                                    counter++;
                                    int numMove = 0;
                                    for(int i=1;i<=userInput.at(2); i++)
                                    {
                                        numMove = numMove + 1;
                                        if(yellow->getY()==30)
                                        {
                                            cout<<" Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
                                            for(int i=numMove-1;i>0; i--)
                                            {
                                                yellow->move(0,40);
                                            }
                                            break;
                                        }
                                        else
                                        {
                                            yellow->move(0,-40);
                                        }
                                    }
                              }
                              else if((userInput.at(1)!='U') || (userInput.at(1)!='D'))
                              {
                                    counter++;
                                    cout<< "Attempt was made to move a piece in the wrong direction.  Please retry." << endl;
                              }
                              break;
                    //END OF case 'Y'--------------------------------------------------------------------------------------------------

                    case 'M': if(userInput.at(1)=='D')
                              {
                                    counter++;
                                    int numMove = 0;
                                    for(int i=1;i<=userInput.at(2); i++)
                                    {
                                        numMove = numMove + 1;
                                        if(magenta->getY()==150)
                                        {
                                            cout<<" Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
                                            for(int i=numMove-1;i>0; i--)
                                            {
                                                magenta->move(0,-40);
                                            }
                                            break;
                                        }
                                        else
                                        {
                                            magenta->move(0,40);
                                        }
                                    }
                              }
                              else if(userInput.at(1)=='U')
                              {
                                    counter++;
                                    int numMove = 0;
                                    for(int i=1;i<=userInput.at(2); i++)
                                    {
                                        numMove = numMove + 1;
                                        if(magenta->getY()==30)
                                        {
                                            cout<<" Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
                                            for(int i=numMove-1;i>0; i--)
                                            {
                                                magenta->move(0,40);
                                            }
                                            break;
                                        }
                                        else
                                        {
                                            magenta->move(0,-40);
                                        }
                                    }
                              }
                              else if((userInput.at(1)!='U') || (userInput.at(1)!='D'))
                              {
                                    counter++;
                                    cout<< "Attempt was made to move a piece in the wrong direction.  Please retry." << endl;
                              }
                              break;
                    //END OF case 'M'--------------------------------------------------------------------------------------------------

                    case 'B': if(userInput.at(1)=='D')
                              {
                                    counter++;
                                    int numMove = 0;
                                    for(int i=1;i<=userInput.at(2); i++)
                                    {
                                        numMove = numMove + 1;
                                        if(blue->getY()==150)
                                        {
                                            cout<<" Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
                                            for(int i=numMove-1;i>0; i--)
                                            {
                                                blue->move(0,-40);
                                            }
                                            break;
                                        }
                                        else
                                        {
                                            blue->move(0,40);
                                        }
                                    }
                              }
                              else if(userInput.at(1)=='U')
                              {
                                    counter++;
                                    int numMove = 0;
                                    for(int i=1;i<=userInput.at(2); i++)
                                    {
                                        numMove = numMove + 1;
                                        if(blue->getY()==30)
                                        {
                                            cout<<" Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
                                            for(int i=numMove-1;i>0; i--)
                                            {
                                                blue->move(0,40);
                                            }
                                            break;
                                        }
                                        else
                                        {
                                            blue->move(0,-40);
                                        }
                                    }
                              }
                              else if((userInput.at(1)!='U') || (userInput.at(1)!='D'))
                              {
                                    counter++;
                                    cout<< "Attempt was made to move a piece in the wrong direction.  Please retry." << endl;
                              }
                              break;
                    //END OF case 'B'--------------------------------------------------------------------------------------------------

                    case 'O': if(userInput.at(1)=='D')
                              {
                                    counter++;
                                    int numMove = 0;
                                    for(int i=1;i<=userInput.at(2); i++)
                                    {
                                        numMove = numMove + 1;
                                        if(orange->getY()==190)
                                        {
                                            cout<<" Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
                                            for(int i=numMove-1;i>0; i--)
                                            {
                                                orange->move(0,-40);
                                            }
                                            break;
                                        }
                                        else
                                        {
                                            orange->move(0,40);
                                        }
                                    }
                              }
                              else if(userInput.at(1)=='U')
                              {
                                    counter++;
                                    int numMove = 0;
                                    for(int i=1;i<=userInput.at(2); i++)
                                    {
                                        numMove = numMove + 1;
                                        if(orange->getY()==30)
                                        {
                                            cout<<" Attempt is made to move a piece off the edge of the board.  Please retry." << endl;
                                            for(int i=numMove-1;i>0; i--)
                                            {
                                                orange->move(0,40);
                                            }
                                            break;
                                        }
                                        else
                                        {
                                            orange->move(0,-40);
                                        }
                                    }
                              }
                              else if((userInput.at(1)!='U') || (userInput.at(1)!='D'))
                              {
                                    counter++;
                                    cout<< "Attempt was made to move a piece in the wrong direction.  Please retry." << endl;
                              }
                              break;
                    //END OF case 'O'--------------------------------------------------------------------------------------------------

                    // Error check if user enters a car that is not a part of the board
                    default:  cout << "User input is not one of the valid color or action items.  Please retry."<< endl; counter++; continue;
            }
            // If the red car is at wining postion then breaks out of the "main" while loop
            if(red->getX() ==190)
            {
                break;
            }
        }
        //If the red car is at wining postion then breaks out of the "default" while loop
        if(red->getX() ==190)
        {
            cout << "*** Congratulations, you did it! ***" << endl;
            cout << "Exiting in 10 seconds" << endl;
            winbool = true;
            break;
        }

        // Breaks out of the "main" while loop if the user input was exit. Was triggered True in If Statement Ln.269
        if(exitbool)
        {
            break;
        }

        // Continue and repeate the whole "main" loop if the file is rested by the user
        if(resetbool)
        {
            continue;
        }
     }

     // waits 10 Sec. before the program closes itself
     if(winbool)
     {
        pause(10000);
     }
     graphicsWindow.requestFocus();
     graphicsWindow.close();
     exitGraphics();

    return 0;
}
