#include <papel.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv){

	if(argc != 4){
		cout << "Formato incorrecto: bin/simulacion_papel_exe n_sim p_obtenido p_total" << endl;
		exit(-1);
	}

	int n_sim = atoi(argv[1]);
	double p_obtenido = atof(argv[2]);
	double p_total = atof(argv[3]);

	Papel fabrica = Papel(p_obtenido/p_total);

	fabrica.simular(n_sim);
}
