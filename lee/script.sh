#!/bin/bash

export TERM=xterm-256color
resize -s 31 114
g++ -Wall -ansi -pedantic main.cpp window.cpp piece.cpp gameUI.cpp game.cpp -lncurses -o 1010
clear
./1010
