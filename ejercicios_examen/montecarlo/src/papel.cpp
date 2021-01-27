#include <papel.h>
#include <cmath>
#include <chrono>
#include <random>
#include <iostream>

using namespace std;

double uniforme(){
	int t = random();
	double f = ((double)RAND_MAX+1.0);

	return (double)t/f;
}

Papel::Papel(double r){
	rendimiento = r;
	demanda_insatisfecha_acumulado = 0.0;
	exceso_papel_rojo_acumulado = 0.0;
	exceso_papel_verde_acumulado = 0.0;
	cont_rojo_acumulado = 0.0;
	cont_verde_acumulado = 0.0;
}

void Papel::tabla_de_propabilidad(){
	probabilidad.push_back(1.0/6.0);
	for (int i = 1; i < 6; i++){
		probabilidad.push_back(probabilidad[i-1] + 1.0/6.0);
	}
}

int Papel::generar_probabilidad(){
	double u = uniforme();

	bool encontrado = false;
	int prob = 0;
	for(int i = 0; i < (int)probabilidad.size() && !encontrado; i++){
		if ( u <= probabilidad[i] ){
			prob = i;
			encontrado = true;
		}
	}
	return prob;
}

void Papel::recibir_papel(){
	int prob = generar_probabilidad();
	int papel = (150 + prob*PUSADO);
	cont_rojo += papel;

	if(cont_rojo > LIMITJ){
		exceso_papel_rojo += (cont_rojo - LIMITJ);
		cont_rojo = LIMITJ;
	}
}

void Papel::demanda_papel(){
	int prob = generar_probabilidad();
	int papel = (30 + prob*PVENDIDO);
	if(papel > cont_verde){
		cont_verde = 0;
		demanda_insatisfecha += (papel - cont_verde);
	} else {
		cont_verde -= papel;
	}

}

void Papel::maniana(){
	if(cont_rojo > EXTRAER){
		procesado = EXTRAER;
		cont_rojo -= EXTRAER;
	} else {
		procesado = cont_rojo;
		cont_rojo = 0;
	}

	procesado *= rendimiento;

	cont_verde += procesado;
	if(cont_verde > LIMITV){
		exceso_papel_verde += (cont_verde - LIMITV);
		cont_verde = LIMITV;
	}
}

void Papel::tarde(){
	recibir_papel();
	demanda_papel();
}

void Papel::simular(int n_sim){
	for (int s = 0; s < n_sim; s++){
		cont_rojo = 300.0;
		cont_verde = 0.0;
		exceso_papel_rojo = 0.0;
		exceso_papel_verde = 0.0;
		demanda_insatisfecha = 0.0;
		tabla_de_propabilidad();

		for(int i = 0; i < MAXDIAS; i++){
			maniana();
			tarde();
			cont_rojo_acumulado += cont_rojo;
			cont_verde_acumulado += cont_verde;
		}

		exceso_papel_rojo_acumulado += exceso_papel_rojo;
		exceso_papel_verde_acumulado += exceso_papel_verde;
		demanda_insatisfecha_acumulado += demanda_insatisfecha;
	}

	cont_rojo_acumulado /= (n_sim*MAXDIAS);
	cont_verde_acumulado /= (n_sim*MAXDIAS);
	exceso_papel_rojo_acumulado /= n_sim;
	exceso_papel_verde_acumulado /= n_sim;
	demanda_insatisfecha_acumulado /= n_sim;

	cout << "Numero de simulaciones: " << n_sim << endl;
	cout << "Kg de papel usado / dia (media): " << cont_rojo_acumulado << endl;
	cout << "Kg de papel reciclado / dia (media): " << cont_verde_acumulado << endl;
	cout << "Kg de papel usado excedido / año (media): " << exceso_papel_rojo_acumulado << endl;
	cout << "Kg de papel reciclado excedido / año (media) : " << exceso_papel_verde_acumulado << endl;
	cout << "Demanda de papel reciclado insatisfecha / año (media): " << demanda_insatisfecha_acumulado << endl;
}
