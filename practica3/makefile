STD = -std=c++20
SRC = src
BIN = bin
INC = include
FLAGS = -std=c++20 -Wall -I/usr/include -I$(INC) -O3
GXX = g++ -o

all: apartado1 apartado2

apartado1: $(BIN)/sistema_tiempo_fijo_exe $(BIN)/sistema_tiempo_variable_exe $(BIN)/sistema_teorico_exe

apartado2: $(BIN)/reparadores_exe

apartado3: $(BIN)/puerto_exe

$(BIN)/reparadores_exe: $(SRC)/reparadores.cpp $(INC)/reparadores.h
	$(GXX) $@ $^ $(FLAGS)

$(BIN)/puerto_exe: $(SRC)/puerto.cpp $(INC)/puerto.h
	$(GXX) $@ $^ $(FLAGS)

$(BIN)/sistema_tiempo_fijo_exe: $(SRC)/sistema_tiempo_fijo.cpp
	$(GXX) $@ $^ $(FLAGS)

$(BIN)/sistema_tiempo_variable_exe: $(SRC)/sistema_tiempo_variable.cpp
	$(GXX) $@ $^ $(FLAGS)

$(BIN)/sistema_teorico_exe: $(SRC)/sistema_teorico.cpp
	$(GXX) $@ $^ $(FLAGS)

clean:
	rm bin/*
