#include <iostream>
#include "Board.h"

using namespace std;

// Creates an empty 10x10 board of water
// INitializer list
// idNum in parameter as an alternative to a setter
Board::Board(int idNum) : m_rows(10), m_cols(10), shipOrientation(0), id(idNum), score(0)
{
	m_board = new char *[m_rows];
	for (int i = 0; i < m_rows; i++)
	{
		m_board[i] = new char[m_cols];
	}
	for (int i = 0; i < m_rows; i++)
	{
		for (int j = 0; j < m_cols; j++)
		{
			m_board[i][j] = '.';
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < m_rows; i++)
	{
		delete[] m_board[i];
	}
	delete[] m_board;
}

bool Board::validPlace(int i, int j, int length, int orientation)
{
	//if starting outside board
	if (i < 0 || i > 9 || j < 0 || j > 9 )
	{
		return false;
	}
	

	//Up
	if (orientation == 1)
	{
		//if ship going outside the board
		if ((i-length+1) < 0)
		{
			return false;
		}
		//if a ship already exists
		for (int z = i-length+1; z <= i; z++)
		{
			
			if (m_board[z][j] == 'S')
			{
				return false;
			}
			
		}
		return true;
	}

	//Down
	else if (orientation == 2)
	{
		//if ship going outside the board
		if ((i+length-1) > 9)
		{
			return false;
		}
		//if a ship already exists
		for (int z = i; z <= i+length-1; z++)
		{			
			if (m_board[z][j] == 'S')
			{
				return false;
			}
			
		}
		return true;
	}

	else if (orientation == 3)
	{
		//if ship going outside the board
		if ((j-length+1) < 0)
		{
			return false;
		}
		//if a ship already exists
		for (int z = j-length+1; z <= j; z++)
		{	
			if (m_board[i][z] == 'S')
			{
				return false;
			}
			
		}
		return true;
	}

	else
	{
		//if ship going outside the board
		if ((j+length-1) > 9)
		{
			return false;
		}
		//if a ship already exists
		for (int z = j; z <= j+length-1; z++)
		{
			if (m_board[i][z] == 'S')
			{
				return false;
			}
			
		}
		return true;
	}

}

bool Board::validHit(int i, int j)
{
	//If hitting outside board
	if (i < 0 || i > 9 || j < 0 || j > 9)
	{
		return false;
	}
	//If hitting at a spot that has already been hit
	if (m_board[i][j] == 'X' || m_board[i][j] == 'M' )
	{
		return false;
	}
	
	score++;
	return true;
	
}

void Board::placeShip(int i, int j, int length, int orientation)
{
	m_board[i][j] = 'S';
	int iPos = i;
	int jPos = j;
	shipOrientation = orientation;
	
	// If ship oriented up
	if (shipOrientation == 1)
	{
		//Fill the vectors for the start and end coordinates, will be used in the shipDestroyed()
		shipIStart.push_back(iPos-length+1);
		shipIEnd.push_back(iPos);
		shipJStart.push_back(jPos);
		shipJEnd.push_back(jPos);
		//Place S for the entire length of the ship
		int shipSize = length;
		while (shipSize != 1)
		{
			m_board[iPos - 1][jPos] = 'S';
			shipSize--;
			iPos--;
		}
	}
	// If ship oriented down
	else if (shipOrientation == 2)
	{
		//Fill the vectors for the start and end coordinates
		shipIStart.push_back(iPos);
		shipIEnd.push_back(iPos+length-1);
		shipJStart.push_back(jPos);
		shipJEnd.push_back(jPos);
		//Place S for the entire length of the ship
		int shipSize = length;
		while (shipSize != 1)
		{
			m_board[iPos + 1][jPos] = 'S';
			shipSize--;
			iPos++;
		}
	}
	// If ship oriented left
	else if (shipOrientation == 3)
	{
		//Fill the vectors for the start and end coordinates
		shipIStart.push_back(iPos);
		shipIEnd.push_back(iPos);
		shipJStart.push_back(jPos-length+1);
		shipJEnd.push_back(jPos);
		//Place S for the entire length of the ship
		int shipSize = length;
		while (shipSize != 1)
		{
			m_board[iPos][jPos - 1] = 'S';
			shipSize--;
			jPos--;
		}
	}
	// If ship oriented right
	else
	{
		//Fill the vectors for the start and end coordinates
		shipIStart.push_back(iPos);
		shipIEnd.push_back(iPos);
		shipJStart.push_back(jPos);
		shipJEnd.push_back(jPos+length-1);
		//Place S for the entire length of the ship
		int shipSize = length;
		while (shipSize != 1)
		{
			m_board[iPos][jPos + 1] = 'S';
			shipSize--;
			jPos++;
		}
	}
}

bool Board::allShipsSunk()
{
	//Nested for loop that checks the whole board for any S
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

bool Board::updateBoardHit(int i, int j)
{
	//If there is no ship, then display M for miss
	if (m_board[i][j] == '.')
	{
		m_board[i][j] = 'M';
		return false;
	}
	//If there is a ship, then display X for hit
	else
	{
		m_board[i][j] = 'X';
		return true;
	}
}

// invoked after ship is hit
bool Board::shipDestroyed(int i, int j)
{
	//Check which ship has been hit, the indexes of the vector is the ship# (0-4)
	int shipNum = 0;
	for (int z = 0; z < shipIStart.size(); z++)
	{
		if (i >= shipIStart[z] && i <= shipIEnd[z] && j >= shipJStart[z] && j <= shipJEnd[z])
		{
			//Now we know which ship has been hit, and we can use it below to check if the whole ship has been sunk
			shipNum = z;
		}
	}

	 // Ship oriented horizontally
	if (shipIStart[shipNum] == shipIEnd[shipNum])
	{
		//Check if there still is any S left for that ship
		for (int z = shipJStart[shipNum]; z <= shipJEnd[shipNum]; z++)
		{
			//If an S is found, the whole ship hasn't been sunk
			if (m_board[i][z] == 'S')
			{
				return false;
			}
		}
	}

	// Ship oriented vertically
	else if (shipJStart[shipNum] == shipJEnd[shipNum]) 
	{
		//Check if there still is any S left for that ship
		for (int z = shipIStart[shipNum]; z <= shipIEnd[shipNum]; z++)
		{
			//If an S is found, the whole ship hasn't been sunk
			if (m_board[z][j] == 'S')
			{
				return false;
			}
		}
	}
	score += 10 * (shipNum+1);
	return true;
}

void Board::printBoardWOShip()
{
	int row = 01;
	//Print the col heading before printing the array
	cout << "   A B C D E F G H I J\n";
	//Print the row headings before printing the next row of the array
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

void Board::printBoardWShip()
{
	int row = 01;
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
			cout << m_board[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

char Board::getCell( int i, int j ){
	return ( m_board[ i ][ j ] );
}
