STD = -std=c++20
SRC = src
BIN = bin
INC = include
FLAGS = -std=c++17 -Wall -I/usr/include -I$(INC) -O3
FLAGS-no = -std=c++17 -Wall -I/usr/include -I$(INC)
GXX = g++ -o

all: apartado1 apartado2

apartado1: $(BIN)/sistema_tiempo_fijo_exe $(BIN)/sistema_tiempo_variable_exe $(BIN)/sistema_teorico_exe

apartado2: $(BIN)/reparadores_exe $(BIN)/separa_datos_exe $(BIN)/reparadores_BL_exe $(BIN)/reparadores_mantenimiento_exe $(BIN)/reparadores_mantenimiento_BL_exe $(BIN)/puerto_exe $(BIN)/compara_sistemas_exe $(BIN)/intervalos_de_confianza_exe

###############################################################################
$(BIN)/sistema_tiempo_fijo_exe: $(SRC)/sistema_tiempo_fijo.cpp
	$(GXX) $@ $^ $(FLAGS-no)

$(BIN)/sistema_tiempo_variable_exe: $(SRC)/sistema_tiempo_variable.cpp
	$(GXX) $@ $^ $(FLAGS-no)

$(BIN)/sistema_teorico_exe: $(SRC)/sistema_teorico.cpp
	$(GXX) $@ $^ $(FLAGS-no)
###############################################################################
###############################################################################
$(BIN)/reparadores_exe: $(SRC)/reparadores.cpp $(INC)/reparadores.h
	$(GXX) $@ $^ $(FLAGS)

$(BIN)/puerto_exe: $(SRC)/puerto.cpp $(INC)/puerto.h
	$(GXX) $@ $^ $(FLAGS)

$(BIN)/separa_datos_exe: $(SRC)/separa_datos.cpp
	$(GXX) $@ $^ $(FLAGS)

$(BIN)/reparadores_BL_exe: $(SRC)/reparadores_BL.cpp $(INC)/reparadores_BL.h
	$(GXX) $@ $^ $(FLAGS)

$(BIN)/reparadores_mantenimiento_exe: $(SRC)/reparadores_mantenimiento.cpp $(INC)/reparadores_mantenimiento.h
	$(GXX) $@ $^ $(FLAGS)

$(BIN)/reparadores_mantenimiento_BL_exe: $(SRC)/reparadores_mantenimiento_BL.cpp $(INC)/reparadores_mantenimiento_BL.h
	$(GXX) $@ $^ $(FLAGS)
###############################################################################
$(BIN)/compara_sistemas_exe: $(SRC)/compara_sistemas.cpp
	$(GXX) $@ $^ $(FLAGS)

$(BIN)/intervalos_de_confianza_exe: $(SRC)/intervalos_de_confianza.cpp
	$(GXX) $@ $^ $(FLAGS)
###############################################################################
clean:
	rm bin/*
###############################################################################
