SRC = src
BIN = bin
INCLUDE = include
GXX = g++
FLAGS = -I/usr/include -I$(INCLUDE) -Wall -std=c++17 -O3

$(BIN)/simulacion_compania_exe: $(SRC)/simulacion_compania.cpp $(SRC)/compania.cpp $(INCLUDE)/compania.h
	$(GXX) -o $@ $^ $(FLAGS)
