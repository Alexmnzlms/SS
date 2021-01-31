#ifndef COMP
#define COMP

#include <list>
#include <vector>
#include <utility>

typedef struct {
	int tipo;
	float tiempo;
} registro;

typedef struct {
	int suceso;
	float tiempo;
	registro reg_cola;
} suc;

class Compania{

private:
	const int SUCESO_DEMANDA = 1;
	const int SUCESO_EVAL = 2;
	const int SUCESO_PEDIDO = 3;
	const int SUCESO_FIN_SIMULACION = 4;
	const double K = 32;
	const double i = 3;
	const double h = 1;
	const double pi = 5;
	const std::vector<double> s {0.0,20.0,40.0,60.0};
	const std::vector<double> S {40.0,60.0,80.0,100.0};

	double reloj;
	double tparada;
	bool parar;
	double tam;
	double nivel;
	double pedido;
	double tultsuc;
	double spequena;
	double sgrande;

	double acummas;
	double acummenos;
	double acumpedido;

	suc nodo;
	registro reg_cola_null;
	registro reg_cola;
	std::list<suc> lsuc;

	std::vector<double> probabilidad;
	std::vector<std::pair<int,int>> ss;
	std::vector<std::vector<double>> costes;

	bool primera_sim;

	// Modificaciones
	int mod;

	//Mod 1
	double vendido_mes;

	//Mod 2
	bool pedido_encargado;



public:
	Compania(int m);
	void simular(int simul);

private:
	double gendem(double media);
	double genpedido(double min, double max);
	void tabla_de_propabilidad();
	int generar_probabilidad();
	double genera_tamano();
	void insertar_lsuc(suc n);
	void inicializacion();
	void temporizacion();
	void suceso();
	void demanda();
	void evaluacion();
	void llegapedido();
	void fin_simulacion();
	void generador_informes(int simul);
};

#endif
