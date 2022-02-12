from tkinter import *



def enterPlayerShip (player):#not finished
    window = Tk()
    currentShip = 1
    ship1 = (5, 5, True) #ship array: (int1, int2, bool)
    ship2 = (-1, -1, True) #int1: x of leftmost point, from 1 to 10
    ship3 = (-1, -1, True) #int2: y of upper-most point, from 1 to 10
    ship4 = (-1, -1, True) #bool: true for horizonal, false for vertical
    ship5 = (-1, -1, True) #int1 = -1 means the ship does not exist
    window.title("Place Your Ship! - Player "+ str(player) + " for Ship " + str(currentShip))
    window.geometry("1100x600")
    window.resizable(0,0)
    can = Canvas(width=500, height=500, bg = "Blue")
    can.grid(row = 2)
    InstructionLabel = Label(window, text = "press button to change directions, press next to continue onto next ship, and submit to submit your ships", font=("Times New Roman", 15))
    InstructionLabel.grid(column = 0, row = 0)
    

    def refreshShip():
        can.create_rectangle(0, 0, 500, 500, fill = "blue")
        if (ship1[0] != -1):
            can.create_rectangle(50 * (ship1[0] - 1), 50 * (ship1[1] - 1), 50 * ship1[0], 50 * ship1[1], fill = "red")
        if (ship2[0] != -1):
            if(ship2[2]):
                can.create_rectangle(50 * (ship2[0] - 1), 50 * (ship2[1] - 1), 50 * (ship2[0] + 1), 50 * ship2[1], fill = "red")
            else:
                can.create_rectangle(50 * (ship2[0] - 1), 50 * (ship2[1] - 1), 50 * ship2[0], 50 * (ship2[1] + 1), fill = "red")
        if (ship3[0] != -1):
            if(ship3[2]):
                can.create_rectangle(50 * (ship3[0] - 1), 50 * (ship3[1] - 1), 50 * (ship3[0] + 2), 50 * ship3[1], fill = "red")
            else:
                can.create_rectangle(50 * (ship3[0] - 1), 50 * (ship3[1] - 1), 50 * ship3[0], 50 * (ship3[1] + 2), fill = "red")
        if (ship4[0] != -1):
            if(ship4[2]):
                can.create_rectangle(50 * (ship4[0] - 1), 50 * (ship4[1] - 1), 50 * (ship4[0] + 3), 50 * ship4[1], fill = "red")
            else:
                can.create_rectangle(50 * (ship4[0] - 1), 50 * (ship4[1] - 1), 50 * ship4[0], 50 * (ship4[1] + 3), fill = "red")
        if (ship5[0] != -1):
            if(ship5[2]):
                can.create_rectangle(50 * (ship5[0] - 1), 50 * (ship5[1] - 1), 50 * (ship5[0] + 4), 50 * ship5[1], fill = "red")
            else:
                can.create_rectangle(50 * (ship5[0] - 1), 50 * (ship5[1] - 1), 50 * ship5[0], 50 * (ship5[1] + 4), fill = "red")
        

    def submitClicked():
        print("ship submitted")
        window.destroy()
        
    def nextClicked():
        nonlocal currentShip
        nonlocal ship1
        nonlocal ship2
        nonlocal ship3
        nonlocal ship4
        nonlocal ship5
        print("nextClicked")
        if (currentShip == 5):
            print("Already at last ship!")
            return
        currentShip = currentShip + 1
        window.title("Place Your Ship! - Player "+ str(player) + " for Ship " + str(currentShip))
        if(currentShip == 2):
            for i in range (1, 11):
                for j in range (1, 11):
                    if(compliant(ship1, (i, j, True), ship3, ship4, ship5)):
                        ship2 = (i, j, True)
                        refreshShip()
                        return
        
        if(currentShip == 3):
            for i in range (1, 11):
                for j in range (1, 11):
                    if(compliant(ship1, ship2, (i, j, True), ship4, ship5)):
                        ship3 = (i, j, True)
                        refreshShip()
                        return

        if(currentShip == 4):
            for i in range (1, 11):
                for j in range (1, 11):
                    if(compliant(ship1, ship2, ship3, (i, j, True), ship5)):
                        ship4 = (i, j, True)
                        refreshShip()
                        return
        
        if(currentShip == 5):
            for i in range (1, 11):
                for j in range (1, 11):
                    if(compliant(ship1, ship2, ship3, ship4, (i, j, True))):
                        ship5 = (i, j, True)
                        refreshShip()
                        return
        return

    def upKey():
        nonlocal currentShip
        nonlocal ship1
        nonlocal ship2
        nonlocal ship3
        nonlocal ship4
        nonlocal ship5
        print("upKey")
        if(currentShip == 1 and compliant((ship1[0], ship1[1] - 1, ship1[2]), ship2, ship3, ship4, ship5)): ship1 = (ship1[0], ship1[1] - 1, ship1[2])
        if(currentShip == 2 and compliant(ship1, (ship2[0], ship2[1] - 1, ship2[2]), ship3, ship4, ship5)): ship2 = (ship2[0], ship2[1] - 1, ship2[2])
        if(currentShip == 3 and compliant(ship1, ship2, (ship3[0], ship3[1] - 1, ship3[2]), ship4, ship5)): ship3 = (ship3[0], ship3[1] - 1, ship3[2])
        if(currentShip == 4 and compliant(ship1, ship2, ship3, (ship4[0], ship4[1] - 1, ship4[2]), ship5)): ship4 = (ship4[0], ship4[1] - 1, ship4[2])
        if(currentShip == 5 and compliant(ship1, ship2, ship3, ship4, (ship5[0], ship5[1] - 1, ship5[2]))): ship5 = (ship5[0], ship5[1] - 1, ship5[2])
        refreshShip()

        #print(ship1)
        #print(ship2)
        #print(ship3)
        #print(ship4)
        #print(ship5)
        
    def downKey():
        nonlocal currentShip
        nonlocal ship1
        nonlocal ship2
        nonlocal ship3
        nonlocal ship4
        nonlocal ship5
        print("downKey")
        if(currentShip == 1 and compliant((ship1[0], ship1[1] + 1, ship1[2]), ship2, ship3, ship4, ship5)): ship1 = (ship1[0], ship1[1] + 1, ship1[2])
        if(currentShip == 2 and compliant(ship1, (ship2[0], ship2[1] + 1, ship2[2]), ship3, ship4, ship5)): ship2 = (ship2[0], ship2[1] + 1, ship2[2])
        if(currentShip == 3 and compliant(ship1, ship2, (ship3[0], ship3[1] + 1, ship3[2]), ship4, ship5)): ship3 = (ship3[0], ship3[1] + 1, ship3[2])
        if(currentShip == 4 and compliant(ship1, ship2, ship3, (ship4[0], ship4[1] + 1, ship4[2]), ship5)): ship4 = (ship4[0], ship4[1] + 1, ship4[2])
        if(currentShip == 5 and compliant(ship1, ship2, ship3, ship4, (ship5[0], ship5[1] + 1, ship5[2]))): ship5 = (ship5[0], ship5[1] + 1, ship5[2])
        refreshShip()

        #print(ship1)
        #print(ship2)
        #print(ship3)
        #print(ship4)
        #print(ship5)
        
    def leftKey():
        nonlocal currentShip
        nonlocal ship1
        nonlocal ship2
        nonlocal ship3
        nonlocal ship4
        nonlocal ship5
        print("leftKey")
        if(currentShip == 1 and compliant((ship1[0] - 1, ship1[1], ship1[2]), ship2, ship3, ship4, ship5)): ship1 = (ship1[0] - 1, ship1[1], ship1[2])
        if(currentShip == 2 and compliant(ship1, (ship2[0] - 1, ship2[1], ship2[2]), ship3, ship4, ship5)): ship2 = (ship2[0] - 1, ship2[1], ship2[2])
        if(currentShip == 3 and compliant(ship1, ship2, (ship3[0] - 1, ship3[1], ship3[2]), ship4, ship5)): ship3 = (ship3[0] - 1, ship3[1], ship3[2])
        if(currentShip == 4 and compliant(ship1, ship2, ship3, (ship4[0] - 1, ship4[1], ship4[2]), ship5)): ship4 = (ship4[0] - 1, ship4[1], ship4[2])
        if(currentShip == 5 and compliant(ship1, ship2, ship3, ship4, (ship5[0] - 1, ship5[1], ship5[2]))): ship5 = (ship5[0] - 1, ship5[1], ship5[2])
        refreshShip()

        #print(ship1)
        #print(ship2)
        #print(ship3)
        #print(ship4)
        #print(ship5)

    def rightKey():
        nonlocal currentShip
        nonlocal ship1
        nonlocal ship2
        nonlocal ship3
        nonlocal ship4
        nonlocal ship5
        print("rightKey")
        if(currentShip == 1 and compliant((ship1[0] + 1, ship1[1], ship1[2]), ship2, ship3, ship4, ship5)): ship1 = (ship1[0] + 1, ship1[1], ship1[2])
        if(currentShip == 2 and compliant(ship1, (ship2[0] + 1, ship2[1], ship2[2]), ship3, ship4, ship5)): ship2 = (ship2[0] + 1, ship2[1], ship2[2])
        if(currentShip == 3 and compliant(ship1, ship2, (ship3[0] + 1, ship3[1], ship3[2]), ship4, ship5)): ship3 = (ship3[0] + 1, ship3[1], ship3[2])
        if(currentShip == 4 and compliant(ship1, ship2, ship3, (ship4[0] + 1, ship4[1], ship4[2]), ship5)): ship4 = (ship4[0] + 1, ship4[1], ship4[2])
        if(currentShip == 5 and compliant(ship1, ship2, ship3, ship4, (ship5[0] + 1, ship5[1], ship5[2]))): ship5 = (ship5[0] + 1, ship5[1], ship5[2])
        refreshShip()

        #print(ship1)
        #print(ship2)
        #print(ship3)
        #print(ship4)
        #print(ship5)

    def rotKey():
        nonlocal currentShip
        nonlocal ship1
        nonlocal ship2
        nonlocal ship3
        nonlocal ship4
        nonlocal ship5
        print("rotKey")
        if(currentShip == 1 and compliant((ship1[0], ship1[1], not ship1[2]), ship2, ship3, ship4, ship5)): ship1 = (ship1[0], ship1[1], not ship1[2])
        if(currentShip == 2 and compliant(ship1, (ship2[0], ship2[1], not ship2[2]), ship3, ship4, ship5)): ship2 = (ship2[0], ship2[1], not ship2[2])
        if(currentShip == 3 and compliant(ship1, ship2, (ship3[0], ship3[1], not ship3[2]), ship4, ship5)): ship3 = (ship3[0], ship3[1], not ship3[2])
        if(currentShip == 4 and compliant(ship1, ship2, ship3, (ship4[0], ship4[1], not ship4[2]), ship5)): ship4 = (ship4[0], ship4[1], not ship4[2])
        if(currentShip == 5 and compliant(ship1, ship2, ship3, ship4, (ship5[0], ship5[1], not ship5[2]))): ship5 = (ship5[0], ship5[1], not ship5[2])
        refreshShip()

        #print(ship1)
        #print(ship2)
        #print(ship3)
        #print(ship4)
        #print(ship5)
    
    UpButton = Button (window, text = "UP", command = upKey)
    UpButton.grid(row = 1, column = 1)
    DnButton = Button (window, text = "DN", command = downKey)
    DnButton.grid(row = 1, column = 2)
    LtButton = Button (window, text = "LT", command = leftKey)
    LtButton.grid(row = 1, column = 3)
    RtButton = Button (window, text = "RT", command = rightKey)
    RtButton.grid(row = 1, column = 4)
    CgButton = Button (window, text = "DR", command = rotKey)
    CgButton.grid(row = 1, column = 5)
    NextButton = Button(window, text = "next", bg = "blue", fg = "white", command = nextClicked)
    NextButton.grid(row = 1, column = 6)
    SubmitButton = Button(window, text = "submit", bg = "red", fg = "white", command = submitClicked)
    SubmitButton.grid(row = 1, column = 7)
    refreshShip()
    window.mainloop()
    return (player, ship1, ship2, ship3, ship4, ship5)
    
def singleCompliant(shipNum, ship): # check if one ship's position compliant
    if (ship[0] == -1): return ship[1] == -1 # see if the ship is empty
    if (ship[0] < -1 or ship[0] == 0 or ship[0] > 10): return False
    if (ship[1] < -1 or ship[1] == 0 or ship[1] > 10): return False
    if (ship[2]): 
        if (not (ship[0] + shipNum - 1 < 11)): return False
    else: 
        if (not (ship[1] + shipNum - 1 < 11)): return False
    return True

def compliant(ship1, ship2, ship3, ship4, ship5):
    if((not singleCompliant(1, ship1)) or (not singleCompliant(2, ship2)) or (not singleCompliant(3, ship3)) or (not singleCompliant(4, ship4)) or (not singleCompliant(5, ship5))): return False # if a ship's position itself is not compliant, then it's not compliant
    positionTable = []
    if(ship1[0] != -1): positionTable.append((ship1[0], ship1[1]))#check if there is position overlap
    if(ship2[0] != -1):
        if(ship2[2]):
            positionTable.append((ship2[0], ship2[1]))
            positionTable.append((ship2[0] + 1, ship2[1]))
        else:
            positionTable.append((ship2[0], ship2[1]))
            positionTable.append((ship2[0], ship2[1] + 1))
    if(ship3[0] != -1):
        if(ship3[2]):
            positionTable.append((ship3[0], ship3[1]))
            positionTable.append((ship3[0] + 1, ship3[1]))
            positionTable.append((ship3[0] + 2, ship3[1]))
        else:
            positionTable.append((ship3[0], ship3[1]))
            positionTable.append((ship3[0], ship3[1] + 1))
            positionTable.append((ship3[0], ship3[1] + 2))
    if(ship4[0] != -1):
        if(ship4[2]):
            positionTable.append((ship4[0], ship4[1]))
            positionTable.append((ship4[0] + 1, ship4[1]))
            positionTable.append((ship4[0] + 2, ship4[1]))
            positionTable.append((ship4[0] + 3, ship4[1]))
        else:
            positionTable.append((ship4[0], ship4[1]))
            positionTable.append((ship4[0], ship4[1] + 1))
            positionTable.append((ship4[0], ship4[1] + 2))
            positionTable.append((ship4[0], ship4[1] + 3))
    if(ship5[0] != -1):
        if(ship5[2]):
            positionTable.append((ship5[0], ship5[1]))
            positionTable.append((ship5[0] + 1, ship5[1]))
            positionTable.append((ship5[0] + 2, ship5[1]))
            positionTable.append((ship5[0] + 3, ship5[1]))
            positionTable.append((ship5[0] + 4, ship5[1]))
        else:
            positionTable.append((ship5[0], ship5[1]))
            positionTable.append((ship5[0], ship5[1] + 1))
            positionTable.append((ship5[0], ship5[1] + 2))
            positionTable.append((ship5[0], ship5[1] + 3))
            positionTable.append((ship5[0], ship5[1] + 4))
    n = len(positionTable)
    for i in range(0, n):
        for j in range(i + 1,n):
            if(positionTable[i] == positionTable[j]): return False
    return True

enterPlayerShip(1)