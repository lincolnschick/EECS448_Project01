#include <iostream>
#include "Board.h"

using namespace std;

// Creates an empty 10x10 board of water
// INitializer list
// idNum in parameter as an alternative to a setter
Board::Board(int idNum) : m_rows(10), m_cols(10), shipOrientation(0), id(idNum)
{
	//	int m_start_row, m_end_row;
	//	int m_start_col, m_end_col;
	//	int totalShips = 1;

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
	if (orientation == 2)
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

	if (orientation == 3)
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

	if (orientation == 4)
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
	if (i < 0 || i > 9 || j < 0 || j > 9)
	{
		return false;
	}

	if (m_board[i][j] == 'X' || m_board[i][j] == 'M' )
	{
		return false;
	}
	
	
	return true;
	
}

void Board::placeShip(int i, int j, int length, int orientation)
{
	m_board[i][j] = 'S';
	int iPos = i;
	int jPos = j;
	shipOrientation = orientation;
	int shipNum = length-1;
	
	// If ship oriented up
	if (shipOrientation == 1)
	{
		shipIStart.push_back(iPos-length+1);
		shipIEnd.push_back(iPos);
		shipJStart.push_back(jPos);
		shipJEnd.push_back(jPos);

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
		shipIStart.push_back(iPos);
		shipIEnd.push_back(iPos+length-1);
		shipJStart.push_back(jPos);
		shipJEnd.push_back(jPos);

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
		shipIStart.push_back(iPos);
		shipIEnd.push_back(iPos);
		shipJStart.push_back(jPos-length+1);
		shipJEnd.push_back(jPos);

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
		shipIStart.push_back(iPos);
		shipIEnd.push_back(iPos);
		shipJStart.push_back(jPos);
		shipJEnd.push_back(jPos+length-1);

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
	if (m_board[i][j] == '.')
	{
		m_board[i][j] = 'M';
		return false;
	}

	else if (m_board[i][j] == 'S')
	{
		m_board[i][j] = 'X';
		return true;
	}
}
// invoked after ship is hit
bool Board::shipDestroyed(int i, int j)
{
	int shipNum = 0;
	for (int z = 0; z < shipIStart.size(); z++)
	{
		if (i >= shipIStart[z] && i <= shipIEnd[z] && j >= shipJStart[z] && j <= shipJEnd[z])
		{
			shipNum = z;
		}
	}

	if (shipIStart[shipNum] == shipIEnd[shipNum]) // Ship oriented horizontally
	{
		for (int z = shipJStart[shipNum]; z <= shipJEnd[shipNum]; z++)
		{
			if (m_board[i][z] == 'S')
			{
				return false;
			}
		}
		return true;
	}

	else if (shipJStart[shipNum] == shipJEnd[shipNum]) // Ship oriented vertically
	{
		for (int z = shipIStart[shipNum]; z <= shipIEnd[shipNum]; z++)
		{
			if (m_board[z][j] == 'S')
			{
				return false;
			}
		}
		return true;
	}
}

void Board::printBoardWOShip()
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
