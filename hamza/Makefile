CXX=g++
RM=rm -f
CPPFLAGS=-Wall -pedantic -ansi
FLAGS=-lncurses
SRC=main.cpp window.cpp piece.cpp gameUI.cpp game.cpp
OBJ=$(SRC:.cpp=.o)

all: a b $(SRC) 
	$(CXX) $(CPPFLAGS) $(SRC) $(FLAGS) -o 1010 

a:SHELL:=/bin/bash
a:
	export TERM=xterm-256color

b:SHELL:=/bin/bash
b:
	resize -s 31 114

clean:
	$(RM) $(OBJ)

distclean: clean
	$(RM) 1010
