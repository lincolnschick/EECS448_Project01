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
    //Checking for correct input
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
        //player.printBoardWShip();
        cout << endl << "Player " << player.getId() << ": " << endl;
        cout << "Enter the following information: " << endl;
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
    

        // Check if index is valid, all our water, can fit the entire length
        /*

        */

        // Invoke the place ship function
        player.placeShip(startRowIndex, startColIndex, i, shipOrientation);

        player.printBoardWShip(); 
    }
}