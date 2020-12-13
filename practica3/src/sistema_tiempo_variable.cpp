#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>

using namespace std;

float generar(float media){
	float u = (float) random();
	u = (float) (u/(RAND_MAX+1.0));
	return (-media * log(1-u));
}

// bin/sistema_tiempo_fijo hayrepuesto tfallo trepar tiempodeparar

int main(int argc, char ** argv){

	bool hayrepuesto;
	float tfallo;
	float trepar;
	float tiempodeparar;
	int max;
	float durfallos_media = 0.0;

	if( argc != 6 ){
		cerr << "Numero incorrecto de argumentos" << endl;
		cerr << "bin/sistema_tiempo_variable repuesto tfallo trepar tiempodeparar max" << endl;
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
	}

	srandom(18);
	//srandom(1);

	for(int i = 1; i <= max; i++){

		float reloj = 0.0;
		bool fallo = false;
		bool reparadorlibre = true;
		bool maquinaesperando = false;
		float numfallos = 0.0;
		float durfallos = 0.0;
		float tiempofinreparacion = 1000000000.0;
		float comienzofallo = 0.0;

		float tiempofallomaquina = reloj + generar(tfallo);

		while (reloj <= tiempodeparar){
			/*
			cout << "Reloj "<< reloj << endl;
			cout << "Tiempofallomaquina " << tiempofallomaquina << endl;
			cout << "Tiempofinreparacion " << tiempofinreparacion << endl;
			cout << "Reparadorlibre " << reparadorlibre << endl;
			cout << "Maquinaesperando " << maquinaesperando << endl;
			cout << "Hayrepuesto " << hayrepuesto << endl;
			cout << "Fallo " << fallo << endl;
			cout << "Durfallos " << durfallos << endl;
			cout << "Numfallos " << numfallos << endl;
			cout << "------" << endl;
			*/
			reloj = min(tiempofallomaquina,tiempofinreparacion);
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
	/*
			cout << "Tiempofallomaquina " << tiempofallomaquina << endl;
			cout << "Tiempofinreparacion " << tiempofinreparacion << endl;
			cout << "Reparadorlibre " << reparadorlibre << endl;
			cout << "Maquinaesperando " << maquinaesperando << endl;
			cout << "Hayrepuesto " << hayrepuesto << endl;
			cout << "Fallo " << fallo << endl;
			cout << "Durfallos " << durfallos << endl;
			cout << "Numfallos " << numfallos << endl;
			cout << "-----------------------------------------" << endl;
	*/
		}
		if(fallo){
			durfallos += reloj - comienzofallo;
		}
		// cout << "Duración de los fallos: " << durfallos << endl;
		// cout << "Número de fallos: " << numfallos << endl;
		durfallos_media += (durfallos/numfallos);
		cout << i << " " << setprecision(7) << durfallos_media/i << endl;
	}
}

