SRC = src
BIN = bin
INCLUDE = include
GXX = g++
FLAGS = -I/usr/include -I$(INCLUDE) -Wall -std=c++17 -O3

$(BIN)/simulacion_enfermedad_exe: $(SRC)/simulacion_enfermedad.cpp $(SRC)/simulacion.cpp $(INCLUDE)/simulacion.h
	$(GXX) -o $@ $^ $(FLAGS)
