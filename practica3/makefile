STD = -std=c++20
SRC = src
BIN = bin
INC = include
flags = -std=c++20 -Wall -I/usr/include -I$(INC)

all:	$(BIN)/reparadores_exe $(BIN)/puerto_exe

$(BIN)/reparadores_exe: $(SRC)/reparadores.cpp $(INC)/reparadores.h
	g++ -o $@ $^ $(flags) -O3

$(BIN)/puerto_exe: $(SRC)/puerto.cpp $(INC)/puerto.h
	g++ -o $@ $^ $(flags) -O3
