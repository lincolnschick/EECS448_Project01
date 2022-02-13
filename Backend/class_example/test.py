#!/usr/bin/python3

from class_example import Board

player1 = Board(1)
player1.placeShip(1, 1, 1, 2)
player2 = Board(2)
player2.placeShip(1, 1, 3, 2)
player1.printBoardWShip()
