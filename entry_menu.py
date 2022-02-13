
from tkinter import *
    # global menu
    # window = tk.Toplevel(menu)
menu = Tk()
menu.geometry('400x300')
menu.title('BATTLESHIPS')
menu['bg']='black'

title_F = ("Times bold", 25)
f = ("Times bold", 14)
ship_Num = 1
ship_Num_Str = StringVar()
ship_Num_Str.set("number of ships:"+str(ship_Num))
def enter_game():
    menu.destroy()
    import play_game
def place_Ship():

    import placeShip
def set_ship_num():
    global ship_Num
    if ship_Num < 5:
        ship_Num += 1
    else:
        ship_Num = 1
    ship_Num_Str.set("number of ships:"+str(ship_Num))


aibg_Color = False

def change_ai_bg():
    global aibg_Color
    if aibg_Color == False:
        aibg_Color = True
        ai_b["fg"]="red"
    else:
        aibg_Color = False
        ai_b["fg"]="black"

Label(menu, text="Battleship", padx=20, pady=20, bg='sky blue', font=title_F).pack(expand=True, fill=BOTH)
Label(menu, textvariable = ship_Num_Str, padx=20, pady=20, bg='sky blue', font=title_F).pack(expand=True, fill=BOTH)
Button(menu, text="Enter", font=f, command=enter_game).pack(expand=TRUE, fill=X, side=BOTTOM)
Button(menu, text="Set Number of ship(demo)", font=f, command=set_ship_num).pack(fill=X, expand=TRUE)
Button(menu, text="place ship", font=f, command=place_Ship).pack(fill=X, expand=TRUE)
ai_b = Button(menu, text="play with evil AI(demo)", font=f, fg ='black', command=change_ai_bg )
ai_b.pack(fill=X, expand=TRUE)
menu.mainloop()
