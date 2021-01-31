SRC = src
BIN = bin
INCLUDE = include
GXX = g++
FLAGS = -I/usr/include -I$(INCLUDE) -Wall -std=c++17 -O3

$(BIN)/simulacion_papel_exe: $(SRC)/simulacion_papel.cpp $(SRC)/papel.cpp $(INCLUDE)/papel.h
	$(GXX) -o $@ $^ $(FLAGS)
