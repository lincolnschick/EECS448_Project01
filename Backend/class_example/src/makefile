battleship: main.o Executive.o Board.o
	g++ -std=c++11 -g -Wall main.o Executive.o Board.o -o battleship

main.o:
	g++ -std=c++11 -g -Wall -c main.cpp

Executive.o:
	g++ -std=c++11 -g -Wall -c Executive.cpp

Board.o:
	g++ -std=c++11 -g -Wall -c Board.cpp

clean:
	rm *.o battleship
