#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

using namespace std;

class Board
{
	private:
		char** m_board;
		int m_rows, m_cols;
		int shipOrientation;
		int id;
		int score;
		vector<int> shipIStart;
		vector<int> shipJStart;
		vector<int> shipIEnd;
		vector<int> shipJEnd;
	public:

		//Initializes all privates members, id is passed in the constructor to define the id to be 1 or 2 (player 1 or player 2)
		Board(int idNum);
		//Deallocates the 2D array
		~Board();
		bool validPlace(int i, int j, int length, int orientation);
		bool validHit(int i, int j);
		//Places all the S for a ship on the array,	doesn't check for valid input	
		void placeShip(int i, int j, int length, int orientation);
		//Check if all the ships of the user are sunk 
		bool allShipsSunk();
		//Update users board after being hit and returns true if it is a hit
		bool updateBoardHit(int i, int j);
		//Check if a ship is fully destroyed and returns a bool
		bool shipDestroyed(int i, int j);
		//Print the board with the ships
		void printBoardWShip();
		//Print the board without the ships
		void printBoardWOShip();
		//Returns the id of the player (to indicate if it is player 1 or player 2)
		int getId() {return id;}
		//Returns the score of the player
		int getScore() {return score;}



};
#endif
