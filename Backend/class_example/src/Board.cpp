#include <iostream>
#include "Board.h"

using namespace std;

/*
Legend:
. -> Water
S -> Ship
M -> Miss
X -> Hit
*/

// Creates an empty 10x10 board of water
// Initializer list
// idNum in parameter as an alternative to a setter
Board::Board(int idNum) : m_rows(10), m_cols(10), shipOrientation(0), id(idNum)
{
	//	int m_start_row, m_end_row;
	//	int m_start_col, m_end_col;
	//	int totalShips = 1;

	//Creates an empty 2D array of length 10x10
	m_board = new char *[m_rows];
	for (int i = 0; i < m_rows; i++)
	{
		m_board[i] = new char[m_cols];
	}

	//Fills the 2D array with water
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			m_board[i][j] = '.';
		}
	}
}

//Destructor 
Board::~Board() 
{
	for (int i = 0; i < m_rows; i++)
	{
		delete[] m_board[i];
	}
	delete[] m_board;
}

//Will place ships on the board
void Board::placeShip(int i, int j, int length, int orientation)
{
	m_board[i][j] = 'S'; 
	int iPos = i;
	int jPos = j;
	shipOrientation = orientation;

	// If ship oriented up
	if (shipOrientation == 1)
	{
		int shipSize = length;
		while (shipSize != 1)
		{
			m_board[iPos - 1][jPos] = 'S';
			shipSize--;
			iPos--;
		}
	}
	// If ship oriented down
	if (shipOrientation == 2)
	{
		int shipSize = length;
		while (shipSize != 1)
		{
			m_board[iPos + 1][jPos] = 'S';
			shipSize--;
			iPos++;
		}
	}
	// If ship oriented left
	if (shipOrientation == 3)
	{
		int shipSize = length;
		while (shipSize != 1)
		{
			m_board[iPos][jPos - 1] = 'S';
			shipSize--;
			jPos--;
		}
	}
	// If ship oriented right
	if (shipOrientation == 4)
	{
		int shipSize = length;
		while (shipSize != 1)
		{
			m_board[iPos][jPos + 1] = 'S';
			shipSize--;
			jPos++;
		}
	}
}

/*
Invoked after ship is hit
Checks around the index hit to see if a part of the ship exists, if it does, then the ship isn't
destroyed completely, otherwise it is.

	m_board[i + 1][j] -> Checks Bottom of the index hit.
	m_board[i][j + 1] -> Checks Right of the index hit.
	m_board[i - 1][j] -> Checks Top of the index hit.
	m_board[i][j - 1] -> Checks Left of the index hit.

*/
bool Board::shipDestroyed(int i, int j)
{
	 
	if (i == 0 && j == 0) //Top-Left corner
	{
		if (m_board[i + 1][j] != 'S' && m_board[i][j + 1] != 'S')
		{
			return true;
		}
		return false;
	}

	else if (i == 0 && j == 9) //Top-Right corner 
	{
		if (m_board[i + 1][j] != 'S' && m_board[i][j - 1] != 'S')
		{
			return true;
		}
		return false;
	}

	else if (i == 9 && j == 0) //Bottom-Left corner
	{
		if (m_board[i][j + 1] != 'S' && m_board[i - 1][j] != 'S')
		{
			return true;
		}
		return false;
	}

	else if (i == 9 && j == 9) //Bottom-Right corner
	{
		if (m_board[i][j - 1] != 'S' && m_board[i - 1][j] != 'S')
		{
			return true;
		}
		return false;
	}

	else if (i == 0) // Top row of the grid
	{
		if (m_board[i + 1][j] != 'S' && m_board[i][j + 1] != 'S' && m_board[i][j - 1] != 'S')
		{
			return true;
		}
		return false;
	}

	else if (i == 9) //Bottom row of the grid
	{
		if (m_board[i - 1][j] != 'S' && m_board[i][j + 1] != 'S' && m_board[i][j - 1] != 'S')
		{
			return true;
		}
		return false;
	}

	else if (j == 0) //Left-most column of the grid
	{
		if (m_board[i - 1][j] != 'S' && m_board[i][j + 1] != 'S' && m_board[i + 1][j] != 'S')
		{
			return true;
		}
		return false;
	}

	else if (j == 9) //Right-most column of the grid
	{
		if (m_board[i - 1][j] != 'S' && m_board[i][j - 1] != 'S' && m_board[i + 1][j] != 'S')
		{
			return true;
		}
		return false;
	}

	else if (m_board[i + 1][j] != 'S' && m_board[i][j + 1] != 'S' && m_board[i - 1][j] != 'S' && m_board[i][j - 1] != 'S') // Checks all the other grid positions 
	{
		return true;
	}

	else
	{
		return false; //Ship wasn't destroyed completely 
	}
}

//Prints the board without showing ships on it
void Board::printBoardWOShip()
{
    int row = 1;
    cout << "   A B C D E F G H I J\n";
    for (int i = 0; i < m_rows; i++)
    {
        if (row != 10)
        {
            cout << ' ' << row << ' ';
            row++;
        }
        else
        {
            cout << row << ' ';
        }
        for (int j = 0; j < m_cols; j++)
        {
            if (m_board[i][j] == 'S')
            {
                cout << ". ";
            }
            else
            {
                cout << m_board[i][j] << ' ';
            }
        }
        cout << endl;
    }
	cout << endl;
}

//Prints the grid with ships on it.
void Board::printBoardWShip()
{
    int row = 1;
    cout << "   A B C D E F G H I J\n"; // Labelling columns as alphabets
    for (int i = 0; i < m_rows; i++)
    {
        if (row != 10)
        {
            cout << ' ' << row << ' ';
            row++; //Increments the row number
        }
        else
        {
            cout << row << ' '; //Will output row# 10
        }
        for (int j = 0; j < m_cols; j++)
        {
            cout << m_board[i][j] << ' ';
        }
        cout << endl;
    }
	cout << endl;
}

//If there is even a single 'S' on the grid then that means a ship or part of it still exists
//and all ships haven't sunk.
bool Board::allShipsSunk()
{
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			if (m_board[i][j] == 'S')
			{
				return false;
			}
		}
	}
	return true;
}

//Will update the board after it is hit.
bool Board::updateBoardHit(int i, int j)
{
	if (m_board[i][j] == '.')	//This means we hit the water and the shot was a miss
	{
		m_board[i][j] = 'M';
		return false;
	}

	else if (m_board[i][j] == 'S') //This means we hit the shit and the shot was a hit
	{
		m_board[i][j] = 'X'; //This shows that part of the ship was destroyed. 
		return true;
	}
}
