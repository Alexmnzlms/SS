#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <chrono>
#include "generadores.h"


int main (int argc, char ** argv) {

	int veces, generador, demanda;

	if (argc != 4) {
		std::cerr << "Uso incorrecto." << std::endl;
		std::cerr << "\t Uso: bin/quiosco_tiempo_exe <n_veces>"
					 << " <generador> <demanda>" << std::endl;

		exit(-1);
	}

	veces = atoi(argv[1]);
	generador = atoi(argv[2]);
	demanda = atoi(argv[3]);


	double * tablademanda;
	int * indices;

	int aux;

	srand(time(NULL));

	if ( generador == 1 ) {
		tablademanda = construye_prop_a(100);
	} else if ( generador == 2 ) {
		tablademanda = construye_prop_b(100);
	} else if ( generador == 3 ) {
		tablademanda = construye_prop_c(100);
	} else if ( generador == 4 ) {
		indices = tabla_indices_ord(100);
		tablademanda = construye_prop_c_ord(100, indices);
	}

	auto start = std::chrono::high_resolution_clock::now();
	if (demanda == 1){
		for ( int i = 0; i < veces; i++ ) {
			aux = genera_demanda(tablademanda, 100);
		}
	} else if (demanda == 2){
		for ( int i = 0; i < veces; i++ ) {
			aux = genera_demanda_bb(tablademanda, 100);
		}
	} else if (demanda == 3){
		for ( int i = 0; i < veces; i++ ) {
			aux = genera_demanda_constante(100);
		}
	} else if (demanda == 4){
		for ( int i = 0; i < veces; i++ ) {
			aux = genera_demanda_ord(tablademanda, indices,100);
			//std::cout << aux << std::endl;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = end - start;

	std::cout << veces << "\t" << elapsed.count() << std::endl;

	return 0;

}
