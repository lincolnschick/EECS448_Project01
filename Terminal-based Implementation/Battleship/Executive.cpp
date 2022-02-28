#include "Executive.h"
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <time.h>
using namespace std;

//function to check for integer
void checkInt(int& n)
{
	while ( cin.fail() )
	{
		cin.clear(); // unset failbit
		
		// skip bad input up to the next newline
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		cout << "Sorry, your input did not seem to be an int. Try again: ";
		cin >> n;
	}
	
	//Flush out anything left in the stream (e.g. if they type 2.5 for an int
	//  the .5 would still be there
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//Constructor crating 
Executive::Executive() : player1(1), player2(2)
{
}

void Executive::hideBoards()
{
    for (int i = 0; i < 50; i++)
    {
        cout << "-----------------\n";
    }
}

void Executive::takeNumOfShips()
{
    // Taking and validating number of ships
    cout << "BATTLESHIP!" << endl;
    cout << "Enter the number of ships you want to play with (1 to 5): ";
    cin >> numOfShips;
    checkInt(numOfShips);
    // Checking for correct input
    if (numOfShips < 1 || numOfShips > 5)
    {
        //Keep prompting the user to enter a valid num of ships until they do
        do
        {
            cout << "Please enter a valid number of ships: ";
            cin >> numOfShips;
            checkInt(numOfShips);
        } while (numOfShips < 1 || numOfShips > 5);
    }
}

void Executive::placeShips(Board &player)
{
    player.printBoardWShip();
    // Print Menu, take start row and col
    for (int i = 1; i <= numOfShips; i++)
    {
        //Take the starting col
        cout << endl << "Player " << player.getId() << ": " << endl;
        cout << "Enter the following information: " << endl;
        cout << "Ship #" << i << "\n";
        cout << "Starting col index (A to J): ";
        cin >> startColIndex;
        //Take the staring row
        startColIndex = startColIndex - 65;
        cout << "Starting row index (1 to 10): ";
        cin >> startRowIndex;
        checkInt(startRowIndex);
        startRowIndex--;

        // Orient the ship in the specified direction
        cout << "How would you like to orient your ship?\n";
        cout << "Up = 1\nDown = 2\nLeft = 3\nRight = 4\n";
        cout << "Orientation: ";
        cin >> shipOrientation;
        checkInt(shipOrientation);
        if (shipOrientation < 1 || shipOrientation > 4)
        {
            do
            {
                cout << "PLease enter a valid orientation (1 to 4): ";
                cin >> shipOrientation;
                checkInt(shipOrientation);
            } while (shipOrientation < 1 || shipOrientation > 4);
            
        }
        
        
        //Check for bad input
        if (!player.validPlace(startRowIndex, startColIndex, i, shipOrientation))
        {
            //Keep prompting to re-enter the row,col, orientation until they are valid
            do
            {
                cout << "\nShip cannot be placed at these spots. Try again\n";
                cout << "Ship #" << i << "\n";
                cout << "Starting col index (A to J): ";
                cin >> startColIndex;

                startColIndex = startColIndex - 65;
                cout << "Starting row index (1 to 10): ";
                cin >> startRowIndex;
                checkInt(startRowIndex);
                startRowIndex--;

                // Orient the ship in the specified direction
                cout << "How would you like to orient your ship?\n";
                cout << "Up = 1\nDown = 2\nLeft = 3\nRight = 4\n";
                cout << "Orientation: ";
                cin >> shipOrientation;
                checkInt(shipOrientation);

            } while (!player.validPlace(startRowIndex, startColIndex, i, shipOrientation));
        }
        //After filtering through the bad input, once the input is valid, place the ships on the board
        player.placeShip(startRowIndex, startColIndex, i, shipOrientation);
        //Print the board with the ships so the player can see his own ship placement
        player.printBoardWShip();
    }
}

void Executive::placeShipsAI()
{
    srand(time(NULL));
    int startRow = 0, startCol = 0, orientation = 0;
    for (int i = 1; i <= numOfShips; i++)
    {
        do
        {
            startRow = rand()%10;
            startCol = rand()%10;
            orientation = (rand()%4)+1;
        } while (!player2.validPlace(startRow, startCol, i, orientation));
        player2.placeShip(startRow, startCol, i, orientation);
        // check valid ai placement
        // player2.printBoardWShip();
    }
}

void Executive::hitMissile(Board &p1, Board &p2, int mode)
{
    //Update opponent for AI and 2 player modes
    string opponent = mode == 1 ? "player" + to_string(p2.getId()) : "the AI";
    hideBoards();
    cout << "\nPress enter to start player " << p1.getId() << "'s turn...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    //Print the board without the ships
    cout << "Your board:\n";
    p1.printBoardWShip();
    cout << "Enemy's board:\n";
    p2.printBoardWOShip();
    //Ask the user for col and idex nums
    cout << "Player " << p1.getId() << " play your move: " << endl;
    cout << "Enter the column number (A-J) of " << opponent << "'s box you want to attack : ";
    cin >> colPos;
    colPos = colPos - 65;
    cout << "Enter the row number (1-10) of " << opponent << "'s box you want to attack : ";
    cin >> rowPos;
    checkInt(rowPos);
    rowPos--;

    //Check if the inputs are invalid
    //Keep prompting the user to re-enter inputs until the inputs are valids
    while (!p2.validHit(rowPos, colPos))
    {
        cout << "Please enter valid row and column: \n";
        cout << "Enter the column number (A-J) of " << opponent << "'s box you want to attack : ";
        cin >> colPos;
        colPos = colPos - 65;
        cout << "Enter the row number (1-10) of " << opponent << "'s box you want to attack : ";
        cin >> rowPos;
        checkInt(rowPos);
        rowPos--;
    }

    // If a ship is hit
    if (p2.updateBoardHit(rowPos, colPos) == true)
    {
        cout << "Hit Successful.\n";
        // If the hit caused the whole ship to sink
        if (p2.shipDestroyed(rowPos, colPos))
        {
            cout << "Enemy ship destroyed.\n";
        }
    }
    //If it is a miss
    else
    {
        cout << "Hit Missed.\n";
    }
    //Print the board again after the hit without displaying the ships
    cout << "\nEnemy's updated board:\n";
    p2.printBoardWOShip();
    //temp score location
	cout << "Score: " << p2.getScore() << '\n';
    //
    cout << "\nPress enter to end turn...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void Executive::hitMissileAI(Board &p1, int difficulty)
{

}

void Executive::run()
{
    int modeChoice = 0, difficultyChoice = 0;
    takeNumOfShips();
    do
    {
        cout << "Choose mode:\n";
        cout << "1) 2 Player\n2) AI\n";
        cout << "Choice: ";
        cin >> modeChoice;
        checkInt(modeChoice);
    } while (modeChoice < 1 || modeChoice > 2);

    if (modeChoice == 2)
    {
        do
        {
            cout << "Choose difficulty:\n";
            cout << "1) Easy\n2) Medium\n3) Hard\n";
            cout << "Choice: ";
            cin >> difficultyChoice;
            checkInt(difficultyChoice);
        } while (difficultyChoice < 1 || difficultyChoice > 3);
    }

    placeShips(player1);
    cout << "Press enter to end ship placement...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    hideBoards();
    
    if (modeChoice == 1)
    {
        placeShips(player2);
        cout << "Let's destroy some ships!" << endl;
        cout << "Press enter to end ship placement...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        do
        {
            hitMissile(player1, player2, modeChoice);
            hitMissile(player2, player1, modeChoice);
        } while (!player1.allShipsSunk() && !player2.allShipsSunk());
    }
    else
    {
        placeShipsAI();
        do
        {
            hitMissile(player1, player2, modeChoice);
            hitMissileAI(player1, difficultyChoice);
        } while (!player1.allShipsSunk() && !player2.allShipsSunk());
    }

    if (player1.allShipsSunk() && !player2.allShipsSunk())
    {
        cout << "Player 2 has won!" << endl;
    }

    else if (player2.allShipsSunk() && !player1.allShipsSunk())
    {
        cout << "Player 1 has won!" << endl;
    }

    else
    {
        cout << "It is a draw!" << endl;
    }
}