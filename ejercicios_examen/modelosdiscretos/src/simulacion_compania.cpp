#include "compania.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv){

	if(argc != 3){
		cout << "Formato incorrecto: bin/simulacion_compania_exe n_sim mod" << endl;
		exit(-1);
	}

	int sim = atoi(argv[1]);
	int mod = atoi(argv[2]);

	Compania comp = Compania(mod);
	comp.simular(sim);
}
