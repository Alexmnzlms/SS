#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(int argc, char ** argv){

	float tfallo;
	float trepar;
	float tiempodeparar;

	if( argc != 4 ){
		cerr << "Numero incorrecto de argumentos" << endl;
		cerr << "bin/sistema_tiempo_fijo repuesto tfallo trepar tiempodeparar" << endl;
		exit(1);
	} else {
		tfallo = atoi(argv[1]);
		trepar = atoi(argv[2]);
		tiempodeparar = atoi(argv[3]);
	}

	float durfallos = (trepar * tiempodeparar) / (tfallo + trepar);
	float numfallos = tiempodeparar / (trepar + tfallo);

	cout << "Duración de los fallos: " << durfallos << endl;
	cout << "Número de fallos: " << numfallos << endl;
	cout << "Duración media de los fallos: " << durfallos/numfallos << endl;

}
