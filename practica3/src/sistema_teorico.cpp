#include <iostream>
#include <cstdlib>
#include <cmath>
#include <iomanip>

using namespace std;

int main(int argc, char ** argv){

	float tfallo;
	float trepar;
	float tiempodeparar;
	int max;

	if( argc != 5 ){
		cerr << "Numero incorrecto de argumentos" << endl;
		cerr << "bin/sistema_tiempo_fijo repuesto tfallo trepar tiempodeparar max" << endl;
		exit(1);
	} else {
		tfallo = atoi(argv[1]);
		trepar = atoi(argv[2]);
		tiempodeparar = atoi(argv[3]);
		max = atoi(argv[4]);
	}

	float durfallos = (trepar * tiempodeparar) / (tfallo + trepar);
	float numfallos = tiempodeparar / (trepar + tfallo);

	// cout << "Duración de los fallos: " << durfallos << endl;
	// cout << "Número de fallos: " << numfallos << endl;
	for(int i = 0; i < max; i++){
		cout << i << " " << setprecision(7) << durfallos/numfallos << endl;
	}
}
