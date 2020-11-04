#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include "generadores.h"


int main (int argc, char ** argv) {

	int x, y, veces, modificacion, z;

	char distribucion;

	if (argc != 6 && argc != 7) {
		std::cerr << "Uso incorrecto." << std::endl;
		std::cerr << "\t Uso: bin/quiosco <x> <y> <n_veces> <distribucion> <modificacion> <z>" << std::endl;

		exit(-1);
	}

	x = atoi(argv[1]);
	y = atoi(argv[2]);
	veces = atoi(argv[3]);
	distribucion = argv[4][0];
	modificacion = atoi(argv[5]);

	if (modificacion != 0)
		z = atoi(argv[6]);

	double * tablademanda;

	int demanda;

	double sum, sum2, ganancia, gananciaesperada, desviaciont;

	for ( int s = 0; s <= 100; s++ ){
		sum = sum2 = 0.0;
		srand(time(NULL));

		if ( distribucion == 'a' ) {
			tablademanda = construye_prop_a(100);

		} else if ( distribucion == 'b' ) {
			tablademanda = construye_prop_b(100);

		} else if ( distribucion == 'c' ) {
			tablademanda = construye_prop_c(100);

		} else {
			std::cerr << "Distribucion incorrecta, debe ser a, b o c" << std::endl;
			exit(-2);
		}


		for ( int i = 0; i < veces; i++ ) {
			demanda = genera_demanda(tablademanda, 100);


			if ( modificacion == 0 ) {
				if (s > demanda)
					ganancia = demanda * x - (s - demanda) * y;
				else
					ganancia = s * x;

			} else if ( modificacion == 1 ) {
				if ( s > demanda )
					ganancia = demanda * x - z;
				else
					ganancia = s * x;

			} else if ( modificacion == 2 ) {
				if ( s > demanda )
					ganancia = demanda * std::min(z,(s-demanda)*y);
				else
					ganancia = s * x;

			} else {
				ganancia = 0;
			}

			sum += ganancia;
			sum2 += ganancia * ganancia;

		}

		gananciaesperada = sum / veces;

		desviaciont = sqrt( (sum2 - veces * gananciaesperada * gananciaesperada) / (veces-1) );


		std::cout << s << " " << x << " " << y << " " << veces
					 << " " << distribucion << " " << gananciaesperada
					 << " " << desviaciont << std::endl;

	}

	return 0;

}
