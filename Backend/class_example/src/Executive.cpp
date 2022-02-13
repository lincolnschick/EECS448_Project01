#include "Executive.h"
#include <iostream>
using namespace std;

//Call player objects, passing 1 and 2, to give them ids 1 and 2
Executive::Executive() : player1(1), player2(2)
{
}

void Executive::takeNumOfShips()
{
    // Taking and validating number of ships
    cout << "BATTLESHIP!" << endl;
    cout << "Enter the number of ships you want to play with (1 to 5): ";
    cin >> numOfShips;
    //Checking for correct input
    if (numOfShips < 1 || numOfShips > 5)
    {
        //Keep prompting the user to enter a valid number of ships until their input is > 1 or < 5
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
        //Player #
        cout << endl << "Player " << player.getId() << ": " << endl;
        cout << "Enter the following information: " << endl;
        cout << "Ship #" << i << "\n";
        //Take start col index, a char, and convert it to int by subtracting 65 
        cout << "Starting col index (A to J): ";
        cin >> startColIndex;
        startColIndex = startColIndex - 65;
        //Take start row index and decrement to count for the 0th row
        cout << "Starting row index (1 to 10): ";
        cin >> startRowIndex;
        startRowIndex--;

        // Orient the ship in the specified direction
         cout << "How would you like to orient your ship?\n";
         cout << "Up = 1\nDown = 2\nLeft = 3\nRight = 4\n";
         cout << "Orientation: ";
         cin >> shipOrientation;
    

        // Check if index is valid, all our water, can fit the entire length
        /*

        */

        // Invoke the place ship function
        player.placeShip(startRowIndex, startColIndex, i, shipOrientation);

        player.printBoardWShip(); 
    }
}

void Executive::hitMissile(Board &p1, Board &p2)
{
    //Take col position, a char, and subtact 65 to convert to an int
    cout << "Player " << p1.getId() << ": " << endl;
    cout << "Enter the column number (A-J) of player" << p2.getId()<<"'s box you want to attack : ";
    cin >> colPos;
    colPos = colPos - 65;
    //Take row position and decrement to count for the 0th row
    cout << "Enter the row number (1-10) of the player" << p2.getId()<< "'s box you want to attack : ";
    cin >> rowPos;
    rowPos--;

    /*
        hit validation
    */

    //If a ship is hit
    if (p2.updateBoardHit(rowPos, colPos) == true)
    {
        cout << "Hit Successful.\n";
        //If the hit caused the whole ship to sink
        if (p2.shipDestroyed(rowPos, colPos))
        {
            cout << "Enemy ship destroyed.\n";
        }
    }
    else
    {
        cout << "Hit Missed.\n";
    }
    //Print the board without displaying ships after the hit
    p2.printBoardWOShip();
}

void Executive::run()
{
    //Take number of ships input from user
    takeNumOfShips();
    //Place ships for the 1st player
    placeShips(player1);
    //Place ships for the 2nd player
    placeShips(player2);

    cout << "Let's destory some ships!" << endl << endl;

    //Fire missile until either player's all ships are sunk
    do
    {
        //Player 1 fires at player 2
        hitMissile(player1, player2);
        //Player 2 fires at player 1
        hitMissile(player2, player1);
    } while (!player1.allShipsSunk() && !player2.allShipsSunk());

    //If player 1's all ship have sunk
    if (player1.allShipsSunk() && !player2.allShipsSunk())
    {
        cout << "Player 2 has won!" << endl;
    }
    //If player 2's all ship have sunk
    else if (player2.allShipsSunk() && !player1.allShipsSunk())
    {
        cout << "Player 1 has won!" << endl;
    }
    //If both player's ships are sunk
    else 
    {
        cout << "It is a draw!" << endl;
    }
}