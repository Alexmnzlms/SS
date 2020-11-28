#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

// bin/sistema_tiempo_fijo hayrepuesto tfallo trepar tiempodeparar

int main(int argc, char ** argv){
	int reloj = 0;
	bool fallo = false;
	bool reparadorlibre = true;
	bool maquinaesperando = false;
	float numfallos = 0.0;
	float durfallos = 0.0;
	int tiempofinreparacion = 1000000000;
	int comienzofallo = 0;
	bool hayrepuesto;
	int tfallo;
	int trepar;
	int tiempodeparar;

	if( argc != 5 ){
		cerr << "Numero incorrecto de argumentos" << endl;
		cerr << "bin/sistema_tiempo_fijo repuesto tfallo trepar tiempodeparar" << endl;
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
	}

	int tiempofallomaquina = reloj + tfallo;

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
		if(reloj == tiempofallomaquina){
			if(reparadorlibre){
				reparadorlibre = false;
				tiempofinreparacion = reloj + trepar;
			} else {
				maquinaesperando = true;
			}
			if(hayrepuesto){
				hayrepuesto = false;
				tiempofallomaquina = reloj + tfallo;
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
				tiempofinreparacion = reloj + trepar;
			} else {
				reparadorlibre = true;
				tiempofinreparacion = 1000000000;
			}
			if(!fallo){
				hayrepuesto = true;
			} else {
				tiempofallomaquina = reloj + tfallo;
				durfallos += reloj - comienzofallo;
				fallo = false;
			}
		}
		reloj++;
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
	cout << "Duración de los fallos: " << durfallos << endl;
	cout << "Número de fallos: " << numfallos << endl;
	cout << "Duración media de los fallos: " << durfallos/numfallos << endl;
}
