#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "simulacion.h"

using namespace std;

int main(int argc, char** argv) {
	if(argc < 2){
		cerr << "Formato incorrecto" << endl;
		cerr << "bin/simulacion_enfermedad_exe -f fichero [-o] [salida] [-v]" << endl;
		cerr << "bin/simulacion_enfermedad_exe a b I S R dt tinic tfin [-o] [salida] [-v]" << endl;
		exit(0);
	}

	const int NPARAMS = 8;
	string params[NPARAMS];
	//bool verbose = false;
	bool salida = false;
	string salida_fichero = "";

	if(!strcmp(argv[1],"-f")){
		cout << "Cargando datos de fichero " << argv[2] << endl;
		fstream fi;
		fi.open(argv[2]);

		if(!fi){
			cerr << "Error abiendo el fichero " << argv[2] << endl;
			exit(0);
		} else{
			for(int i = 0; i < NPARAMS; i++){
				getline(fi, params[i], ' ');
				//cout << i << " " << params[i] << endl;
			}
		}
	} else {
		if (argc < (NPARAMS + 1)){
			cerr << "Numero de argumentos incorrecto" << endl;
			cerr << "bin/simulacion_enfermedad_exe a b I S R dt tinic tfin [salida] [-v]" << endl;
			exit(0);
		} else {
			for(int i = 0; i < NPARAMS; i++){
				params[i] = string(argv[i+1]);
			}
		}
	}

	//if(!strcmp(argv[argc-1],"-v")){
	//	verbose = true;
	//}

	if(!strcmp(argv[argc-2], "-o")){
		salida = true;
		salida_fichero = string(argv[argc-1]);
		cout << "Salida a fichero " << salida_fichero << endl;
	}

	cout << "Parametros:" << endl;
	for(int i = 0; i < NPARAMS; i++){
		cout << params[i] << " ";
	}
	cout << endl;

	double a = stod(params[0]);
	double b = stod(params[1]);
	double estado[3] = {stod(params[2]), stod(params[3]), stod(params[4])};
	double dt = stod(params[5]);
	double tinic = stod(params[6]);
	double tfin = stod(params[7]);

	Simulacion enfermedad;
	enfermedad.fijar_parametros(3,a,b,estado,dt,tinic,tfin,salida,salida_fichero);
	enfermedad.integracion(1);
}
