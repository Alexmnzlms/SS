#include <iostream>
#include "simulacion.h"

using namespace std;

void Simulacion::integracion(){
	do {
		salida();
		double* oldestado = estado;
		int metodo;
		one_step(metodo,oldestado,estado,t,dt); //sustituir por one-step-runge-kutta o por one-step-euler
		t += dt;
	} while (t < tfin);
}

void Simulacion::one_step_runge_kuttai(double* inp, double* out, double tt, double hh){
	for (int i=0; i<numeq; i++) out[i]=inp[i];
	double time = tt;
	double incr;
	double* f;
	double** k;
	for (int j = 0; j < 4; j++) {
		derivacion(out,f,time);
		for (int i = 0; i < numeq; i++){
			k[i][j]=f[i];
		}
		if(j < 2){
			incr = hh/2;
		}
		else{
			incr = hh;
		}
		time = tt + incr;
		for (int i = 0; i < numeq; i++){
			out[i] = inp[i] + k[i][j] * incr;
		}
	}
	for (int i = 0; i < numeq; i++){
		out[i] = inp[i] + hh/6 * (k[i][0] + 2*k[i][1] + 2*k[i][2] + k[i][3]);
	}
}

void Simulacion::one_step_euler(double* inp, double* out, double tt, double hh){
	double* f;
	derivacion(inp,f,tt);
	for (int i = 0; i < numeq; i++){
		out[i] = inp[i] + hh*f[i];
	}
}

void Simulacion::derivacion(double* est, double* f, double tt){
// específico para el modelo considerado
	f[0] = a*est[0]*est[1] - b*est[0];
	f[1] = -a*est[0]*est[1];
	f[2] = b*est[0];
}
void Simulacion::main() {
	fijar_parametros();
	t=tinic;
	integracion();
}

void Simulacion::salida(){

}

void Simulacion::fijar_parametros(){

}
