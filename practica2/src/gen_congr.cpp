#include <cstdlib>
#include <cmath>
#include <ctgmath>
#include <iostream>

using namespace std;

int gen_congr_ae(int a, int x, int c, int m){
	return (a*x + c) % m;
}

double gen_congr_ar(int a, double x, int c, int m){
	x = (a*x + c) / m;
	x = (x - (int)x) * m;
	return x;
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

bool comp_double(double a, double b){
	double resta = a - b;
	resta = abs(resta);
	double epsilon = 0.0001;
	if (resta < epsilon){
		cout << "Iguales: " << a << " " << b << endl;
		return true;
	} else {
		cout << "Distintos: " << a << " " << b << endl;
		return false;
	}
}

bool entero_en_vector(int* vector, int tam, int num){
	bool encontrado = false;
	for(int i = 0; i < tam && !encontrado; i++){
		if(vector[i] == num){
			encontrado = true;
		}
	}

	return encontrado;
}

bool real_en_vector(double* vector, int tam, double num){
	bool encontrado = false;
	for(int i = 0; i < tam && !encontrado; i++){
		if(comp_double(vector[i],num)){
			encontrado = true;
		}
	}

	return encontrado;
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

	int periodo = 0;
	int generados = 0;

	if(metodo == 1){
		int generado;
		int* numeros = new int [m];
		bool terminado = false;
		numeros[generados] = x_inicial;
		generados++;

		while(!terminado && generados <= m){
			generado = gen_congr_ae(a, numeros[generados-1], c , m);
			if(entero_en_vector(numeros, generados, generado)){
				periodo = generados;
				terminado = true;
			} else {
				numeros[generados] = generado;
				generados++;
			}
			cout << generado << endl;
	}
	} else {
		double generado;
		double* numeros = new double[m];
		bool terminado = false;
		numeros[generados] = x_inicial;
		generados++;

		while(!terminado && generados <= m){
			if(metodo == 2){
				generado = gen_congr_ar(a, numeros[generados-1], c, m);
			} else if (metodo == 3){
				generado = gen_congr_arc(a, numeros[generados-1], c, m);
			} else {
				generado = gen_congr_fmod(a, numeros[generados-1], c, m);
			}

			if(real_en_vector(numeros, generados, generado)){
				periodo = generados;
				terminado = true;
			} else {
				numeros[generados] = generado;
				generados++;
			}
			cout << generado << endl;
		}
	}

	cout << x_inicial << "\t" << periodo << endl;
}
