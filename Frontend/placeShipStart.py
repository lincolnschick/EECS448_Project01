import cmd
from placeShip import *
from tkinter import *
def startScreen():# enter the start screen
    shipNumber = 1
    startupWindow = Tk()
    startupWindow.title("Choose ships to input!")
    startupWindow.geometry("500x200")
    startupWindow.resizable(0,0)
    number = Spinbox(startupWindow, from_=1,to=5)#ask the player to select from 1 to 5 ships
    def numberSubmission():
        nonlocal shipNumber
        shipNumber = int(number.get())#get the number the player chose
        print(type(shipNumber))
        startupWindow.destroy()
        print(shipNumber)
        return (shipNumber) #submit it
    
    submitButton = Button(startupWindow, text = "submit", command = numberSubmission) #submit button
    number.grid(row = 0, column = 0)
    submitButton.grid(row = 0, column = 1)
    startupWindow.mainloop()
    return (shipNumber) # just in case
    

