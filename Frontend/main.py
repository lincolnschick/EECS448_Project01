from tkinter import *
import placeShip
import placeShipStart
shipNumber = placeShipStart.startScreen()#run start screen to let people enter the number of ships
player1Ships = placeShip.enterPlayerShip(1, shipNumber) #let player 1 place their ships
player2Ships = placeShip.enterPlayerShip(2, shipNumber) #let player 2 plave their ships 
ships1 = []
ships2 = []
for i in range (1, shipNumber + 1):#switch the inputs to Zhenzhou's desired vector in order to run his part of GUI. After this code, ships1 and ships2 save all positions of the ships
    ships1.append([])
    ships2.append([])
    for j in range (0, i):
        if(player1Ships[i][2]):
            ships1[i - 1].append([player1Ships[i][0] + j, player1Ships[i][1]])
        else:
            ships1[i - 1].append([player1Ships[i][0], player1Ships[i][1] + j])
        if(player2Ships[i][2]):
            ships2[i - 1].append([player2Ships[i][0] + j, player2Ships[i][1]])
        else:
            ships2[i - 1].append([player2Ships[i][0], player2Ships[i][1] + j])


        
#compliant check: len(shipsX) == shipNumber * (shipNumber + 1) / 2
#playBoard (shipNumber, ships1, ships2)
#shipsX[0] (includes 1 coordinate of (x, y)), shipsX[1] (includes 2 coordinates of (x, y)), ..., shipsX[4] (includes 5 coordinates of (x, y))
#Things after here should be Zhenzhou's part, but he refuses to coordinate, and therefore, all GUIs, including this code, are involuntarily aborted. Already reported to prof and graders
#For project 2 group members: feel free to add the player GUI with this file and my placeShip and placeShipStart python files. My part is doing well, and finishing of the second part my teammate did not make it can make it pretty good.