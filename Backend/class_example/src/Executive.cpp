#include "Executive.h"
#include <iostream>
using namespace std;

Executive::Executive() : player1(1), player2(2)
{
}

void Executive::takeNumOfShips()
{
    // Taking and validating number of ships
    cout << "BATTLESHIP!" << endl;
    cout << "Enter the number of ships you want to play with (1 to 5): ";
    cin >> numOfShips;
    // Checking for correct input
    if (numOfShips < 1 || numOfShips > 5)
    {
        do
        {
            cout << "Please enter a valid number of ships: ";
            cin >> numOfShips;
        } while (numOfShips < 1 || numOfShips > 5);
    }
}

void Executive::placeShips(Board &player)
{

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
        startRowIndex--;

        // Orient the ship in the specified direction
        cout << "How would you like to orient your ship?\n";
        cout << "Up = 1\nDown = 2\nLeft = 3\nRight = 4\n";
        cout << "Orientation: ";
        cin >> shipOrientation;
        
        //Check for bad input
        if (!player.validPlace(startRowIndex, startColIndex, i, shipOrientation))
        {
            //Keep prompting to reenter the row,col, orientation until they are valid
            do
            {
                cout << "\nShip cannot be placed at these spots. Try again\n";
                cout << "Ship #" << i << "\n";
                cout << "Starting col index (A to J): ";
                cin >> startColIndex;

                startColIndex = startColIndex - 65;
                cout << "Starting row index (1 to 10): ";
                cin >> startRowIndex;
                startRowIndex--;

                // Orient the ship in the specified direction
                cout << "How would you like to orient your ship?\n";
                cout << "Up = 1\nDown = 2\nLeft = 3\nRight = 4\n";
                cout << "Orientation: ";
                cin >> shipOrientation;

            } while (!player.validPlace(startRowIndex, startColIndex, i, shipOrientation));
        }

        player.placeShip(startRowIndex, startColIndex, i, shipOrientation);
        player.printBoardWShip();
    }
}

void Executive::hitMissile(Board &p1, Board &p2)
{
    p2.printBoardWOShip();
    cout << "Player " << p1.getId() << ": " << endl;
    cout << "Enter the column number (A-J) of player" << p2.getId() << "'s box you want to attack : ";
    cin >> colPos;
    colPos = colPos - 65;
    cout << "Enter the row number (1-10) of the player" << p2.getId() << "'s box you want to attack : ";
    cin >> rowPos;
    rowPos--;

    if(!p2.validHit(rowPos, colPos))
    {
        do
        {
            cout << "Please enter valid row and column: \n";
            cout << "Enter the column number (A-J) of player" << p2.getId() << "'s box you want to attack : ";
            cin >> colPos;
            colPos = colPos - 65;
            cout << "Enter the row number (1-10) of the player" << p2.getId() << "'s box you want to attack : ";
            cin >> rowPos;
            rowPos--;
            
        } while (!p2.validHit(rowPos, colPos));
        
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
    else
    {
        cout << "Hit Missed.\n";
    }
    p2.printBoardWOShip();
}

void Executive::run()
{
    takeNumOfShips();

    placeShips(player1);    
    placeShips(player2);

    cout << "Let's destory some ships!" << endl
         << endl;

    do
    {
        hitMissile(player1, player2);
        hitMissile(player2, player1);
    } while (!player1.allShipsSunk() && !player2.allShipsSunk());

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