STD = -std=c++20
SRC = src
BIN = bin
INC = include
flags = -std=c++20 -Wall -I/usr/include -I$(INC) -g

all: apartado1

apartado1: $(BIN)/sistema_tiempo_fijo_exe $(BIN)/sistema_tiempo_variable_exe

apartado2: $(BIN)/reparadores_exe $(BIN)/puerto_exe

$(BIN)/reparadores_exe: $(SRC)/reparadores.cpp $(INC)/reparadores.h
	g++ -o $@ $^ $(flags) -O3

$(BIN)/puerto_exe: $(SRC)/puerto.cpp $(INC)/puerto.h
	g++ -o $@ $^ $(flags) -O3

$(BIN)/sistema_tiempo_fijo_exe: $(SRC)/sistema_tiempo_fijo.cpp
	g++ -o $@ $^ $(flags) -O3

$(BIN)/sistema_tiempo_variable_exe: $(SRC)/sistema_tiempo_variable.cpp
	g++ -o $@ $^ $(flags) -O3

clean:
	rm bin/*
