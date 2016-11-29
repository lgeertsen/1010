++=g++
FLAGS=-Wall -pedantic -ansi -lncurses
SRC=main.cpp window.cpp piece.cpp gameUI.cpp
OBJ=$(SRC:.cpp=.o)

all:${OBJ}
	${++} -o 1010 ${OBJ}

%.o:%.cpp
	${++} $< -o $@ ${FLAGS}

