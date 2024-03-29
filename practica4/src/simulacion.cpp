#include <iostream>
#include <fstream>
#include "simulacion.h"

using namespace std;

Simulacion::Simulacion(){
}

void Simulacion::integracion(int metodo){
	do {
		vector<double> oldestado(estado);
		one_step(metodo,oldestado,estado,t,dt); //sustituir por one-step-runge-kutta o por one-step-euler
		t += dt;
		salida();
	} while (t < tfin);
}

void Simulacion::one_step(int metodo, vector<double> inp, vector<double>& out, double tt, double hh){
	if(metodo == 1){
		one_step_runge_kuttai(inp, out, tt, hh);
	} else if (metodo == 2) {
		one_step_euler(inp, out, tt, hh);
	}
}

void Simulacion::one_step_runge_kuttai(vector<double> inp, vector<double>& out, double tt, double hh){
	double time = tt;
	double incr;
	vector<double> f(numeq,0.0);
	vector<vector<double>> k(numeq);
	for(int i = 0; i < numeq; i++){
		k[i].resize(4);
	}
	for(int i = 0; i < numeq; i++){
		for(int j = 0; j < 4; j++){
			k[i][j] = 0.0;
		}
	}

	for (int i = 0; i < numeq; i++){
		out[i] = inp[i];
	}
	time = tt;
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

void Simulacion::one_step_euler(vector<double> inp, vector<double>& out, double tt, double hh){
	vector<double> f(numeq,0.0);
	derivacion(inp,f,tt);
	for (int i = 0; i < numeq; i++){
		out[i] = inp[i] + hh*f[i];
	}
}

void Simulacion::derivacion(vector<double> est, vector<double>& f, double tt){
// específico para el modelo considerado
	f[0] = a*est[0]*est[1] - b*est[0];
	f[1] = -a*est[0]*est[1];
	f[2] = b*est[0];
}


void Simulacion::salida(bool primera){
	if(!modificar_salida){
		cout << t << "," << estado[0] << "," << estado[1] << "," << estado[2] << endl;
	} else {
		ofstream fo;
		if(primera){
			fo.open(fichero);
		} else {
			fo.open(fichero,std::ios::app);
		}
		fo << t << "," << estado[0] << "," << estado[1] << "," << estado[2] << endl;
		fo.close();
	}
}

void Simulacion::fijar_parametros(int numeq, double a, double b, vector<double> estado, double dt, double tinic, double tfin, bool salida, string fichero){
	this->numeq = numeq;
	this->a = a;
	this->b = b;
	this->estado = estado;
	this->dt = dt;
	this->t = tinic;
	this->tfin = tfin;
	this->modificar_salida = salida;
	this->fichero = fichero;
	this->salida(true);
}
