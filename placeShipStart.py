from placeShip import *
from tkinter import *
def startScreen():
    startupWindow = Tk()
    startupWindow.title("Choose ships to input!")
    startupWindow.geometry("200x200")
    startupWindow.resizable(0,0)
    number = Spinbox(startupWindow, from_=1,to=5)
    def numberSubmission():
        shipNumber = int(number.get())
        print(type(shipNumber))
        startupWindow.destroy()
        print(shipNumber)
        return (enterPlayerShip(1,shipNumber), enterPlayerShip(2, shipNumber))
    
    submitButton = Button(startupWindow, text = "submit", command = numberSubmission)
    number.grid(row = 0, column = 0)
    submitButton.grid(row = 0, column = 1)
    startupWindow.mainloop()
    
    

