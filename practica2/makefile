STD = -std=c++20
SRC = src
BIN = bin
INC = include
flags = -std=c++20 -Wall -I/usr/include -I$(INC)

all:	$(BIN)/quiosco_exe $(BIN)/quiosco_tiempos_exe $(BIN)/gen_congr_exe

$(BIN)/quiosco_exe: $(SRC)/quiosco.cpp $(SRC)/generadores.cpp $(INC)/generadores.h
	g++ -o $@ $^ $(flags) -O3

$(BIN)/quiosco_tiempos_exe: $(SRC)/quiosco_tiempos.cpp $(SRC)/generadores.cpp $(INC)/generadores.h
	g++ -o $@ $^ $(flags)

$(BIN)/gen_congr_exe: $(SRC)/gen_congr.cpp
	g++ -o $@ $^ $(flags) -O3
