#include "Executive.h"
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <utility>
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
        //Play ship placement sound
        system("afplay ../sounds/shipPlace.wav");
        //Print the board with the ships so the player can see his own ship placement
        player.printBoardWShip();
    }
}

//randomly placement of ships for ai
void Executive::placeShipsAI()
{
    cout << "AI's ship placement:\nAI thinking...\n";
    this_thread::sleep_for(chrono::milliseconds(2000));

    srand(time(NULL));
    int startRow = 0, startCol = 0, orientation = 0;
    //places for all ships selected
    for (int i = 1; i <= numOfShips; i++)
    {
        //runs at least once and then check if valid placement
        do
        {
            //randomizes location
            startRow = rand()%10;
            startCol = rand()%10;
            orientation = (rand()%4)+1;
        } while (!player2.validPlace(startRow, startCol, i, orientation));
        player2.placeShip(startRow, startCol, i, orientation);
    }
    cout << "AI has placed ships\n";
    //Play ship placement sound
    system("afplay ../sounds/shipPlace.wav");
}

void Executive::hitMissile(Board &p1, Board &p2, int mode)
{
    //Update opponent for AI and 2 player modes
    string opponent = mode == 1 ? "player" + to_string(p2.getId()) : "the AI";
    if (mode == 1)
    {
        hideBoards();
        cout << "\nPress enter to start player " << p1.getId() << "'s turn...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    //Print the board without the ships
    cout << "Your board:\n";
    p1.printBoardWShip();
    cout << "Enemy's board:\n";
    p2.printBoardWOShip();
    cout << "Your Score: " << p2.getScore() << "\tOpponent Score: " << p1.getScore() << "\n\n";
    if (p1.getLog() != "")
    {
        cout << "Opponent Activity:\n" << p1.getLog() << '\n';
    }
    //Ask the user for col and idex nums
    cout << "Player " << p1.getId() << " play your move: " << endl;
    cout << "Enter the column number (A-J) of " << opponent << "'s box you want to attack : ";
    cin >> colPos;
    colPos = colPos - 65;
    cout << "Enter the row number (1-10) of " << opponent << "'s box you want to attack : ";
    cin >> rowPos;
    checkInt(rowPos);
    rowPos--;
    //clears recent activity log
    p2.clearLog();
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
    //Play firing sound
    system("afplay ../sounds/fireSound.wav");
    // If a ship is hit
    if (p2.updateBoardHit(rowPos, colPos) == true)
    {
        cout << "Hit Successful.\n";
        // If the hit caused the whole ship to sink
        if (p2.getCell(rowPos, colPos) == 'X')
        {
            cout << "Enemy ship destroyed.\n";
        }
        //Play explosion sound after ship hit
        system("afplay ../sounds/explosion.wav");
    }
    //If it is a miss
    else
    {
        cout << "Hit Missed.\n";
        //Play splash sound for miss
        system("afplay ../sounds/splash.wav");
    }
    //Print the board again after the hit without displaying the ships
    cout << "\nEnemy's updated board:\n";
    p2.printBoardWOShip();
	cout << "Your score: " << p2.getScore() << "\tOpponent Score: " << p1.getScore() << "\n\n";
    cout << "Recent Activity:\n" << p2.getLog();
    cout << "\nPress enter to end turn...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//returns coordinate pair
pair<int, int> Executive::randomHit(Board &p1)
{
    int row = 0;
    int col = 0;
    srand( time ( NULL ) );
    while ( 1 ){
        row = rand() % 10; 
        col = rand() % 10;
        if ( p1.validHit( row, col ) ){
            p1.updateBoardHit( row, col );
            //Play corresponding sounds
            switch (p1.getCell(row, col))
            {
                case 'X':
                    cout << "AI destroyed a ship\n";
                    //Play explosion sound after ship hit
                    system("afplay ../sounds/explosion.wav");
                    break;
                    
                case 'H':
                    cout << "AI hit a ship\n";
                    //Play explosion sound after ship hit
                    system("afplay ../sounds/explosion.wav");
                    break;

                case 'M':
                    cout << "AI missed\n";
                    //Play splash sound for miss
                    system("afplay ../sounds/splash.wav");
                    break;
            }
            return make_pair(row, col);
        }
    }
}

void Executive::hitMediumAI(Board &p1)
{
    static bool hit = false;
    static int row = 0, col = 0, midRow = 0, midCol = 0;
    static bool up, down, left, right;
    //Vector holding coordinates of known unsunken ships
    vector< pair<int, int> > hits = p1.getHits();
    //If nothing has been hit
    if (!hit && hits.empty())
    {
        pair<int, int> coor = randomHit(p1);
        row = coor.first;
        col = coor.second;
        midRow = row;
        midCol = col;
        up = true, down = false, left = false, right = false;
        if (p1.getCell(row, col) == 'H') hit = true;
    }
    else
    {
        //Choose a hit from the list of coordinates to sink
        if (!hit)
        {
            //Get coordinate pair
            pair<int, int> currentHit = hits.front();
            row = currentHit.first;
            col = currentHit.second;
            midRow = row;
            midCol = col;
            //Reset adjacent cells checking order
            up = true, down = false, left = false, right = false;
            hit = true;
        }
        if (up)
        {
            row = row - 1;
            //Skip over any H's to see if the ship goes further in this direction
            while (row > 0 && p1.getCell(row, col) == 'H')
            {
                row = row - 1;
            }
            //Check if the new spot is valid
            if (p1.validHit(row, col))
            {
                //Fire and determine is ship is now sunk
                p1.updateBoardHit(row, col);
                if (p1.getCell(row, col) == 'X') hit = false;
            }
            else
            {
                //Try next direction and reset row
                up = false;
                down = true;
                row = midRow;
            }
        }
        if (down)
        {
            row = row + 1;
            //Skip over any H's to see if the ship goes further in this direction
            while (row < 9 && p1.getCell(row, col) == 'H')
            {
                row = row + 1;
            }
            //Check if the new spot is valid
            if (p1.validHit(row, col))
            {
                //Fire and determine is ship is now sunk
                p1.updateBoardHit(row, col);
                if (p1.getCell(row, col) == 'X') hit = false;
            }
            else
            {
                //Try next direction and reset row
                down = false;
                left = true;
                row = midRow;
            }
        }
        if (left)
        {
            col = col - 1;
            //Skip over any H's to see if the ship goes further in this direction
            while (col > 0 && p1.getCell(row, col) == 'H')
            {
                col = col - 1;
            }
            //Check if the new spot is valid
            if (p1.validHit(row, col))
            {
                //Fire and determine is ship is now sunk
                p1.updateBoardHit(row, col);
                if (p1.getCell(row, col) == 'X') hit = false;
            }
            else
            {
                //Try next direction and reset row
                left = false;
                right = true;
                col = midCol;
            }
        }
        if (right)
        {
            col = col + 1;
            //Skip over any H's to see if the ship goes further in this direction
            while (col < 9 && p1.getCell(row, col) == 'H')
            {
                col = col + 1;
            }
            //Check if the new spot is valid
            if (p1.validHit(row, col))
            {
                //Fire and determine is ship is now sunk
                p1.updateBoardHit(row, col);
                if (p1.getCell(row, col) == 'X') hit = false;
            }
        }
        char location = p1.getCell(row, col);
        //If location is a miss, update direction to check next
        if (p1.getCell(row, col) == 'M')
        {
            if (up) {down = true, up = false;}
            else if (down) {left = true, down = false;}
            else if (left) {right = true, left = false;}
            row = midRow;
            col = midCol;
        }
        //Play corresponding sounds
        switch (location)
        {
            case 'X':
                cout << "AI destroyed a ship\n";
                //Play explosion sound after ship hit
                system("afplay ../sounds/explosion.wav");
                break;
                
            case 'H':
                cout << "AI hit a ship\n";
                //Play explosion sound after ship hit
                system("afplay ../sounds/explosion.wav");
                break;

            case 'M':
                cout << "AI missed\n";
                //Play splash sound for miss
                system("afplay ../sounds/splash.wav");
                break;
        }
    }
}

//Depending on the difficulty inserted, it will adjusts accordingly 
void Executive::hitMissileAI(Board &p1, int difficulty)
{
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "AI's turn:\n";
    cout << "AI thinking...\n";
    this_thread::sleep_for(chrono::milliseconds(1000));
    //Play firing sound
    system("afplay ../sounds/fireSound.wav");
    bool hasShot = false;
    switch( difficulty ){
        //Easy difficulty
        case 1:
            randomHit(p1);
            break;
        //Medium difficulty
        case 2:
            hitMediumAI(p1);
            break;
        //Hard difficulty
        case 3:
            for ( int i = 0 ; i < 10 ; i ++ ){
                if ( hasShot ){ break; }
                for ( int j = 0 ; j < 10 ; j ++ ){
                    if ( p1.getCell( i, j ) == 'S' ){
                        p1.updateBoardHit( i, j );
                        hasShot = true;
                        if (p1.getCell(i, j) == 'X')
                        {
                            cout << "AI destroyed a ship\n";
                            //Play explosion sound after ship hit
                            system("afplay ../sounds/explosion.wav");
                        }
                        else
                        {
                            cout << "AI hit a ship\n";
                            //Play explosion sound after ship hit
                            system("afplay ../sounds/explosion.wav");
                        }
                        break;
                    }
                }
            }
            break;
    }
}

void Executive::printWinners(Board& p1, Board& p2, int mode)
{
    //Print AI instead of Player 2 for AI mode
    string opponent2 = mode == 1 ? "Player 2" : "The AI";
    //Winning conditions
    if (p1.allShipsSunk() && !p2.allShipsSunk())
    {
        //print out board one final time if AI won
        if (mode == 2)
        {
            cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            //Print the board without the ships
            cout << "Your board:\n";
            p1.printBoardWShip();
            cout << "Enemy's board:\n";
            p2.printBoardWOShip();
            cout << "Your Score: " << p2.getScore() << "\tOpponent Score: " << p1.getScore() << "\n\n";
            cout << "Opponent Activity:\n" << p1.getLog() << '\n';
        }
        cout << opponent2 << " has won!" << endl;
    }

    else
    {
        cout << "Player 1 has won!" << endl;
    }
}

bool Executive::isGameOver(Board& p1, Board& p2)
{
    return (player1.allShipsSunk() || player2.allShipsSunk());
}


//Runs everything
void Executive::run()
{
    //Player makes a choice
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

    //AI choice
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
    //Play intro sound
    system("afplay ../sounds/intro.wav");
    //Player1 places ships
    placeShips(player1);
    cout << "Press enter to end ship placement...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    //Player 2 places ship if chosen
    if (modeChoice == 1)
    {
        hideBoards();
        placeShips(player2);
        cout << "Let's destroy some ships!" << endl;
        cout << "Press enter to end ship placement...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //Goes through the firing between players until a player wins
        do
        {
            hitMissile(player1, player2, modeChoice);
            //Exit loop if game is over
            if (isGameOver(player1, player2))
                break;
            hitMissile(player2, player1, modeChoice);
        } while (!isGameOver(player1, player2));
    }
    //AI firing
    else
    {
        cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        placeShipsAI();
        do
        {
            hitMissile(player1, player2, modeChoice);
            //Exit loop if game is over
            if (isGameOver(player1, player2))
                break;
            hitMissileAI(player1, difficultyChoice);
        } while (!isGameOver(player1, player2));
    }
    printWinners(player1, player2, modeChoice);
    //Play a victory sound to celebrate the winner(s)
    system("afplay ../sounds/victory.wav");
}