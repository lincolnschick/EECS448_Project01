
from tkinter import *
import tkinter.font as Font
from functools import partial
# from helpfunctions import *
# import entry_menu

def build_board(player):
    p1_showboard = []
    p1_playboard = []
    p2_showboard = []
    p2_playboard = []
    for i in range(11):
        cells = []
        #text="A B C D E F G H I J"
        for j in range(11):
            #text="1 2 3 4 5 6 7 8 9 10"
            if i == 0 and j == 0:
                cell_p1_s = Label(battle_board, width=2, height=1, font=cell_font, fg="black", bg="black")
            elif i == 0:
                cell_p1_s = Label(battle_board, text = chr(96+j), width=2, height=1, font=cell_font, fg="black", bg="white")
            elif j == 0:
                cell_p1_s = Label(battle_board, text = i, width=2, height=1, font=cell_font, fg="black", bg="white")
            else:
                cell_p1_s = Button(battle_board, text ='0', width=2, height=1, font=showboard_font, fg= "white", bg="sky blue",command= p1_turn)
            cells.append(cell_p1_s)
        p1_showboard.append(list(cells))
    for i in range(11):
        cells = []
        #text="A B C D E F G H I J"
        for j in range(11):
            #text="1 2 3 4 5 6 7 8 9 10"
            if i == 0 and j == 0:
                cell_p1_p = Label(battle_board, width=2, height=1, font=cell_font, fg="black", bg="black")
            elif i == 0:
                cell_p1_p = Label(battle_board, text = chr(96+j), width=2, height=1, font=cell_font, fg="black", bg="white")
            elif j == 0:
                cell_p1_p = Label(battle_board, text = i, width=2, height=1, font=cell_font, fg="black", bg="white")
            else:
                cell_p1_p = Button(battle_board, text ='0', width=2, height=1, font=cell_font, bg="orange", activebackground="blue",command= p1_turn)
            cells.append(cell_p1_p)
        p1_playboard.append(list(cells))
    for i in range(11):
        cells = []
        #text="A B C D E F G H I J"
        for j in range(11):
            #text="1 2 3 4 5 6 7 8 9 10"
            if i == 0 and j == 0:
                cell_p2_s = Label(battle_board, width=2, height=1, font=cell_font, fg="black", bg="black")
            elif i == 0:
                cell_p2_s = Label(battle_board, text = chr(96+j), width=2, height=1, font=cell_font, fg="black", bg="white")
            elif j == 0:
                cell_p2_s = Label(battle_board, text = i, width=2, height=1, font=cell_font, fg="black", bg="white")
            else:
                cell_p2_s = Button(battle_board, text ='0', width=2, height=1, font=showboard_font, fg= "white", bg="sky blue",command= p1_turn)
            cells.append(cell_p2_s)
        p2_showboard.append(list(cells))
    for i in range(11):
        cells = []
        #text="A B C D E F G H I J"
        for j in range(11):
            #text="1 2 3 4 5 6 7 8 9 10"
            if i == 0 and j == 0:
                cell_p2_p = Label(battle_board, width=2, height=1, font=cell_font, fg="black", bg="black")
            elif i == 0:
                cell_p2_p = Label(battle_board, text = chr(96+j), width=2, height=1, font=cell_font, fg="black", bg="white")
            elif j == 0:
                cell_p2_p = Label(battle_board, text = i, width=2, height=1, font=cell_font, fg="black", bg="white")
            else:
                cell_p2_p = Button(battle_board, text ='0', width=2, height=1, font=cell_font, bg="orange", activebackground="blue",command= p1_turn)
            cells.append(cell_p2_p)
        p2_playboard.append(list(cells))


    if player == "p1 show":
        label_p1 = Label(battle_board, text="Player 1", font=cell_font, fg="white", bg="red")
        label_p1.grid(row=0, column=4, columnspan=10)
        label_p1_b = Label(battle_board, text="Your board", font=cell_font, fg="white", bg="red")
        label_p1_b.grid(row=1, column=4, columnspan=10)
        for row in range(11):
            for col in range(11):
                p1_showboard[row][col].grid(row=3 + row, column=4 + col)
    if player == "p1 play":
        label_p1_p = Label(battle_board, text="Enemy board", font=cell_font, fg="white", bg="red")
        label_p1_p.grid(row=108, column=4, columnspan=10)
        for row in range(11):
            for col in range(11):
                p1_playboard[row][col].grid(row=110 + row, column=4 + col)

    if player == "p2 show":
        label_p2 = Label(battle_board, text="Player 2", font=cell_font, fg="white", bg="blue")
        label_p2.grid(row=0, column=17, columnspan=10)
        label_p2_b = Label(battle_board, text="Your board", font=cell_font, fg="white", bg="blue")
        label_p2_b.grid(row=1, column=17, columnspan=10)
        for row in range(11):
            for col in range(11):
                p2_showboard[row][col].grid(row=3 + row, column=17 + col)

    if player == "p2 play":
        label_p2_p = Label(battle_board, text="Enemy board", font=cell_font, fg="white", bg="blue")
        label_p2_p.grid(row=108, column=17, columnspan=10)
        for row in range(11):
            for col in range(11):
                p2_playboard[row][col].grid(row=110 + row, column=17 + col)
# def mid_edge():
#     for i in range(10):
#         Label(battle_board, font=cell_font, bg="black").grid(row=1 + i, column=14)


def ship_labels():
    Label(battle_board, textvariable=p1_Ready, font=cell_font, fg="red", bg="Black").grid(row=0, column=0)
    Label(battle_board, textvariable=p2_Ready, font=cell_font, fg="red", bg="Black").grid(row=0, column=15)

    Button(battle_board, text="Set Ship", font=cell_font, fg="Red", bg="white",command = lambda:p1_isReady()).grid(row=4, column=0)
    Button(battle_board, text="Set Ship", font=cell_font, fg="Blue", bg="white",command = lambda:p2_isReady()).grid(row=4, column=15)

p1_onhit = False
def p1_isReady():
    global p1_onhit
    if p1_onhit == False:
        p1_onhit = True
        p1_Ready.set('Ready')
    else:
        p1_onhit = False
        p1_Ready.set('Waiting')

p2_onhit = False
def p2_isReady():
    global p2_onhit
    if p2_onhit == False:
        p2_onhit = True
        p2_Ready.set('Ready')
    else:
        p2_onhit = False
        p2_Ready.set('Waiting')

p1_switch = False
def p1_turn():
    global p1_switch
    if p1_switch == False:
        p1_switch = True
        cell_p1_s["fg"]="sky blue"
        cell_p1_p["fg"]="orange"
        cell_p2_s["fg"]="sky blue"
        cell_p2_p["fg"]="orange"
    else:
        p1_switch = False
        cell_p1_s["fg"]="white"
        cell_p1_p["fg"]="black"
        cell_p2_s["fg"]="white"
        cell_p2_p["fg"]="black"

def nextPage():
    battle_board.destroy()




battle_board = Tk()
# battle_board.wm_title("BATTLESHIPS"+str(entry_menu.ship_Num))
battle_board.configure(background='black')
cell_font = Font.Font(size=12, weight='normal')
showboard_font = Font.Font(size=11, weight='normal')
cell_p1_s = Label(battle_board, width=2, height=1, font=cell_font, fg="black", bg="black")
cell_p1_p = Label(battle_board, width=2, height=1, font=cell_font, fg="black", bg="black")
cell_p2_s = Label(battle_board, width=2, height=1, font=cell_font, fg="black", bg="black")
cell_p2_p = Label(battle_board, width=2, height=1, font=cell_font, fg="black", bg="black")
p1_Ready = StringVar()
p2_Ready = StringVar()
p1_Ready.set("Waiting")
p2_Ready.set("Waiting")

build_board("p1 play")
build_board("p1 show")

build_board("p2 play")
build_board("p2 show")
ship_labels()
battle_board.mainloop()
