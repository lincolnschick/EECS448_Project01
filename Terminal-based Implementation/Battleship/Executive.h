#ifndef EXECUTIVE_H
#define EXECUTIVE_H

#include "Board.h"

class Executive
{
private:
    Board player1;
    Board player2;
    int numOfShips;
    int startRowIndex;
    char startColIndex;
    int shipOrientation;
    char colPos;
	int rowPos;
    //Prints lines to hide other player's board
    void hideBoards();
    void placeShipsAI();
    //Handles AI medium hitting
    void hitMediumAI(Board &p1);
    //Handles AI hitting boards and updating arrays
    void hitMissileAI(Board &p1, int difficulty);
    //Prints the winner(s)
    void printWinners(Board& p1, Board& p2, int mode);
    //Returns if the game is over
    bool isGameOver(Board& p1, Board& p2);
    pair<int, int> randomHit(Board &p1);
    
public:
    //Initializes the private members
    Executive();
    //Prompts the players with the initial menus, asks for # of ships to play with
    void takeNumOfShips();
    //Prompts the players with the menu, asks for coordinates to place the ships at and places them on the array
    void placeShips(Board& player);
    //Prompts the players with the menu, asks for coordinates to hit at, and updates the array
    void hitMissile(Board& p1, Board& p2, int mode); //returns true if any player destorys all boats
    //Calls all the Executive methods to execute 
    void run();
};
#endif