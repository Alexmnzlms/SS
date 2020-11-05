#include <cstdlib>
#include <cstdlib>
#include <cmath>
#include <ctgmath>
#include <set>
#include <iostream>

using namespace std;

int gen_congr_ae(int a, int x, int c, int m){
	return (a*x + c) % m;
}

double gen_congr_ar(int a, double x, int c, int m){
	x = (a*x + c) / m;
	x = (x - (int)x) * m;
	return (int)x;
}

double gen_congr_arc(int a, double x, int c, int m){
	x = (a*x + c) / m;
	x = (x - (int)x) * m;
	x = (int)(x+0.5);
	return x;
}

double gen_congr_fmod(int a, double x, int c, int m){
	return fmod((a*x + c), m);
}


int main(int argc, char ** argv){

	int m = 10000;

	if(argc != 5){
		cerr << "Error, se esperaban 4 parametros" << endl;
		exit(1);
	}

	int a = atoi(argv[1]);
	int c = atoi(argv[2]);
	int x_inicial = atoi(argv[3]);
	int metodo = atoi(argv[4]);

	if(metodo > 4 || metodo < 1){
		cerr << "Metodo incorrecto" << endl;
		exit(1);
	}

	int periodo = -1;

	if(metodo == 1){
		int generado, generado_ant;
		set<int> numeros;
		bool terminado = false;
		numeros.insert(x_inicial);
		generado_ant = x_inicial;

		while(!terminado && (int)numeros.size() < m){
			generado = gen_congr_ae(a, generado_ant, c , m);
			if(numeros.find(generado) != numeros.end()){
				terminado = true;
			} else {
				numeros.insert(generado);
				generado_ant = generado;
			}
			periodo = numeros.size();
		}
	} else {
		double generado, generado_ant;
		set<double> numeros;
		bool terminado = false;
		numeros.insert(x_inicial);
		generado_ant = x_inicial;

		while(!terminado && (int)numeros.size() < m){
			if(metodo == 2){
				generado = gen_congr_ar(a, generado_ant, c, m);
			} else if (metodo == 3){
				generado = gen_congr_arc(a, generado_ant, c, m);
			} else {
				generado = gen_congr_fmod(a, generado_ant, c, m);
			}

			if(numeros.find(generado) != numeros.end()){
				terminado = true;
			} else {
				numeros.insert(generado);
				generado_ant = generado;
			}
			periodo = numeros.size();
		}
	}

	cout << x_inicial << "\t" << periodo << endl;
}
