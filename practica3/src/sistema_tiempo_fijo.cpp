#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <chrono>

using namespace std;

// bin/sistema_tiempo_fijo hayrepuesto tfallo trepar tiempodeparar
int generar(float media){
	float u = (float) random();
	u = (float) (u/(RAND_MAX+1.0));
	float n = (-media * log(1-u));
	int ent = ceil(n);
	if (ent == 0){
		ent++;
	}
	return ent;
}


int main(int argc, char ** argv){
	bool hayrepuesto;
	int tfallo;
	int trepar;
	int tiempodeparar;
	int max;
	float durfallos_media = 0.0;
	bool efi;

	if( argc != 7 ){
		cerr << "Numero incorrecto de argumentos" << endl;
		cerr << "bin/sistema_tiempo_fijo repuesto tfallo trepar tiempodeparar max efi" << endl;
		exit(1);
	} else {
		if(atoi(argv[1]) == 0){
			hayrepuesto = false;
		} else if(atoi(argv[1]) == 1){
			hayrepuesto = true;
		} else {
			cerr << "Repuesto solo puede ser 0 o 1" << endl;
			exit(1);
		}
		tfallo = atoi(argv[2]);
		trepar = atoi(argv[3]);
		tiempodeparar = atoi(argv[4]);
		max = atoi(argv[5]);
		if(atoi(argv[6]) == 0){
			efi = false;
		} else {
			efi = true;
		}
	}

	//srandom(18);
	srandom(1);

	auto start = std::chrono::high_resolution_clock::now();

	for(int i = 1; i <= max; i++){
		int reloj = 0;
		bool fallo = false;
		bool reparadorlibre = true;
		bool maquinaesperando = false;
		float numfallos = 0.0;
		float durfallos = 0.0;
		int tiempofinreparacion = 1000000000;
		int comienzofallo = 0;


		int tiempofallomaquina = reloj + generar(tfallo);

		while (reloj <= tiempodeparar){

			if(reloj == tiempofallomaquina){
				if(reparadorlibre){
					reparadorlibre = false;
					tiempofinreparacion = reloj + generar(trepar);
				} else {
					maquinaesperando = true;
				}
				if(hayrepuesto){
					hayrepuesto = false;
					tiempofallomaquina = reloj + generar(tfallo);
				} else if(!fallo){
					fallo = true;
					comienzofallo = reloj;
					numfallos++;
					tiempofallomaquina = 1000000000;
				}
			}
			if(reloj == tiempofinreparacion){
				if(maquinaesperando){
					maquinaesperando = false;
					tiempofinreparacion = reloj + generar(trepar);
				} else {
					reparadorlibre = true;
					tiempofinreparacion = 1000000000;
				}
				if(!fallo){
					hayrepuesto = true;
				} else {
					tiempofallomaquina = reloj + generar(tfallo);
					durfallos += reloj - comienzofallo;
					fallo = false;
				}
			}
			reloj++;

		}
		if(fallo){
			durfallos += reloj - comienzofallo;
		}

		// cout << "Duración de los fallos: " << durfallos << endl;
		// cout << "Número de fallos: " << numfallos << endl;
		durfallos_media += (durfallos/numfallos);

		if(!efi){
			cout << i << " " << setprecision(7) << durfallos_media/i << endl;
		}
	}

	auto finish = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> elapsed = finish - start;

	if(efi){
		cout << tiempodeparar << " " << elapsed.count() << endl;;
	}

}
