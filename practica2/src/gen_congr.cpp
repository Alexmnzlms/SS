#include <cstdlib>
#include <cmath>
#include <ctgmath>
#include <iostream>

using namespace std;

int gen_congr_am(int a, int x, int c, int m){
	return (a*x + c) % m;
}

int gen_congr_ar(int a, double x, int c, int m){
	x = (a*x + c) / m;
	x =(x - (int)x) * m;
	return x;
}

int gen_congr_arc(int a, double x, int c, int m){
	x = (a*x + c) / m;
	x = (x - (int)x) * m;
	x = (int)(x+0.5);
	return x;
}

int gen_congr_fmod(int a, double x, int c, int m){
	return fmod((a*x + c), m);
}

bool comp_double(double a, double b){
	double resta = a - b;
	double epsilon = 0.000000001;
	if (resta <= epsilon && resta >= -epsilon){
		return true;
	} else {
		return false;
	}
}

int main(int argc, char ** argv){

	if(argc != 5){
		cerr << "Error, se esperaban 4 parametros" << endl;
		exit(1);
	}

	int a = atoi(argv[1]);
	int c = atoi(argv[2]);
	int m = atoi(argv[3]);
	int metodo = atoi(argv[4]);

	if(metodo > 4 || metodo < 1){
		cerr << "Metodo incorrecto" << endl;
		exit(1);
	}

	if(metodo == 0){
		int* numeros = new int [m];

	} else {
		double* numeros = new double[m];
	}
}
