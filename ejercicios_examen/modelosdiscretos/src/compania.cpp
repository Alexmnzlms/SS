#include "compania.h"
#include <chrono>
#include <random>
#include <iostream>

using namespace std;

bool compare(const suc &s1, const suc &s2){
	return s1.tiempo < s2.tiempo;
}

Compania::Compania(int m){
	mod = m;
}

double Compania::gendem(double media){
	float u;
	u = (float) random();
	u = (float) (u/(RAND_MAX+1.0));
	return(-media*log(1-u));
}

double Compania::genpedido(double min, double max){
	float u;
	u = (float) random();
	u = (float) (u/(RAND_MAX+1.0));
	return(min+(max-min)*u);
}

void Compania::tabla_de_propabilidad(){
	probabilidad.push_back(1.0/6.0);
	for (int i = 1; i < 3; i++){
		probabilidad.push_back(probabilidad[i-1] + 1.0/3.0);
	}
	probabilidad.push_back(probabilidad[(int)probabilidad.size() - 1] + 1.0/6.0);
}

double Compania::genera_tamano(){
	double u = genpedido(0.0, 1.0);

	bool encontrado = false;
	int prob = 0;
	for(int i = 0; i < (int)probabilidad.size() && !encontrado; i++){
		//cout << "P: " << u << ", " << probabilidad[i] << endl;
		if ( u <= probabilidad[i] ){
			prob = i;
			encontrado = true;
		}
	}
	//cout << "Probabilidad: " << u << ", " << prob << endl;
	return prob + 1;
}

void Compania::insertar_lsuc(suc n){
	lsuc.push_back(n);
	lsuc.sort(compare);
}

void Compania::inicializacion(){
	reloj = 0.0;
	tparada = 120.0;
	tam = 0.0;
	nivel = 60.0;
	pedido = 0.0;
	tultsuc = 0.0;

	acummas = 0.0;
	acummenos = 0.0;
	acumpedido = 0.0;

	vendido_mes = 0.0;

	pedido_encargado = false;

	tabla_de_propabilidad();

	while(!lsuc.empty()){
		lsuc.pop_front();
	}

	reg_cola_null.tiempo = 0.0;
	reg_cola_null.tipo = 0;
	nodo.reg_cola = reg_cola_null;
	nodo.suceso = SUCESO_FIN_SIMULACION;
	nodo.tiempo = reloj+tparada;
	insertar_lsuc(nodo);

	nodo.suceso = SUCESO_DEMANDA;
	nodo.tiempo = reloj+gendem(0.1);
	insertar_lsuc(nodo);

	nodo.suceso = SUCESO_EVAL;
	nodo.tiempo = reloj+1.0;
	insertar_lsuc(nodo);

	parar = false;

	if(ss.empty()){
		for(auto i = s.begin(); i != s.end(); ++i){
			for(auto j = S.begin(); j != S.end(); ++j){
				if( *i < *j ){
					ss.push_back(make_pair(*i, *j));
				}
			}
		}
	}
}

void Compania::temporizacion(){
	nodo = lsuc.front();
	lsuc.pop_front();
	reloj = nodo.tiempo;
}

void Compania::suceso(){
	if(nodo.suceso == SUCESO_DEMANDA){
		demanda();
	} else if(nodo.suceso == SUCESO_EVAL){
		evaluacion();
	} else if(nodo.suceso == SUCESO_PEDIDO){
		llegapedido();
	} else if(nodo.suceso == SUCESO_FIN_SIMULACION){
		fin_simulacion();
	}
}

void Compania::demanda(){
	if(mod == 0){
		if(nivel > 0){
			acummas += (reloj-tultsuc)*nivel;
		} else {
			acummenos += (reloj-tultsuc)*(-nivel);
		}
		tultsuc = reloj;
		tam = genera_tamano();
		nivel -= tam;
		nodo.suceso = SUCESO_DEMANDA;
		nodo.tiempo = reloj+gendem(0.1);
		insertar_lsuc(nodo);

	} else if (mod == 1){
		if(nivel > 0){
			acummas += (reloj-tultsuc)*nivel;
		} else {
			acummenos += (reloj-tultsuc)*(-nivel);
		}
		tultsuc = reloj;
		tam = genera_tamano();
		nivel -= tam;
		vendido_mes += tam;
		nodo.suceso = SUCESO_DEMANDA;
		nodo.tiempo = reloj+gendem(0.1);
		insertar_lsuc(nodo);

	} else if(mod == 2){
		if(nivel > 0){
			acummas += (reloj-tultsuc)*nivel;
		} else {
			acummenos += (reloj-tultsuc)*(-nivel);
		}
		tultsuc = reloj;
		tam = genera_tamano();
		nivel -= tam;
		if(nivel < spequena && !pedido_encargado){
			pedido = sgrande - nivel;
			acumpedido += K+i*pedido;
			nodo.suceso = SUCESO_PEDIDO;
			nodo.tiempo = reloj+genpedido(0.5, 1.0);
			insertar_lsuc(nodo);
			pedido_encargado = true;
		}
		nodo.suceso = SUCESO_DEMANDA;
		nodo.tiempo = reloj+gendem(0.1);
		insertar_lsuc(nodo);
	}
}

void Compania::evaluacion(){
	if(mod == 0){
		if(nivel < spequena && pedido == 0){
			pedido = sgrande - nivel;
			acumpedido += K+i*pedido;
			nodo.suceso = SUCESO_PEDIDO;
			nodo.tiempo = reloj+genpedido(0.5, 1.0);
			insertar_lsuc(nodo);
		}
		nodo.suceso = SUCESO_EVAL;
		nodo.tiempo = reloj+1.0;
		insertar_lsuc(nodo);

	} else if(mod == 1){
		pedido = vendido_mes;
		vendido_mes = 0;
		acumpedido += K+i*pedido;
		nodo.suceso = SUCESO_PEDIDO;
		nodo.tiempo = reloj+genpedido(0.5, 1.0);
		insertar_lsuc(nodo);
		nodo.suceso = SUCESO_EVAL;
		nodo.tiempo = reloj+1.0;
		insertar_lsuc(nodo);
	}
}

void Compania::llegapedido(){
	if(mod == 0 || mod == 1){
		if(nivel > 0){
			acummas += (reloj-tultsuc)*nivel;
		} else {
			acummenos += (reloj-tultsuc)*(-nivel);
		}
		tultsuc = reloj;
		nivel += pedido;
		pedido = 0;

	} else if(mod == 2){
		if(nivel > 0){
			acummas += (reloj-tultsuc)*nivel;
		} else {
			acummenos += (reloj-tultsuc)*(-nivel);
		}
		tultsuc = reloj;
		nivel += pedido;
		pedido = 0;
		pedido_encargado = false;
	}

}

void Compania::fin_simulacion(){
	parar = true;
	acummas *= h;
	acummenos *= pi;
	vector<double> acum {(acumpedido + acummas + acummenos)/reloj, acumpedido/reloj, acummas/reloj, acummenos/reloj};

	if(primera_sim){
		costes.push_back(acum);
	} else {
		int pos, i;
		pos = i = 0;
		bool encontrado = false;
		for(auto it = ss.begin(); it != ss.end() && !encontrado; ++it){
			if(it->first == spequena && it->second == sgrande){
				pos = i;
				encontrado = true;
			}
			i++;
		}
		for(int j = 0; j < (int)acum.size(); j++){
			costes[pos][j] += acum[j];
		}
	}
}

void Compania::generador_informes(int simul){
	double min_p = 0;
	double min = (costes[0][0] / simul);
	cout << "Modificacion: " << mod << endl;
	cout << "Numero de simulaciones: " << simul << endl;
	cout << "Politica Costo Total Costo de pedido Costo de mantenimiento Costo de deficit" << endl;
	for(int i = 0; i < (int)costes.size(); i++){
		cout << "(" << ss[i].first << "," << ss[i].second << ")" << " ";
		if(min > (costes[i][0] / simul)){
			min_p = i;
			min = (costes[i][0] / simul);
		}
		for(int j = 0; j < (int)costes[i].size(); j++){
			cout << (costes[i][j] / simul) << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "El minimo: "<< min << " -> configuracion (" << ss[min_p].first << "," << ss[min_p].second << ")" << endl;
}

void Compania::simular(int simul){
	primera_sim = true;
	for(int sim = 0; sim < simul; sim++){
		if(sim > 0 && primera_sim){
			primera_sim = false;
		}
		for(auto i = s.begin(); i != s.end(); ++i){
			for(auto j = S.begin(); j != S.end(); ++j){
				if( *i < *j ){
					spequena = *i;
					sgrande = *j;
					inicializacion();
					while(!parar){
						temporizacion();
						suceso();
					}
				}
			}
		}
	}
	generador_informes(simul);
}
