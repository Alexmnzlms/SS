#ifndef PAPEL
#define PAPEL

#include <vector>

class Papel{

private:
	const double LIMITJ = 1000.0;
	const double LIMITV = 300.0;
	const double EXTRAER = 300.0;
	const int PUSADO = 50;
	const int PVENDIDO = 30;
	const int MAXDIAS = 365;

	double rendimiento;
	double demanda_insatisfecha_acumulado;
	double exceso_papel_rojo_acumulado;
	double exceso_papel_verde_acumulado;
	double demanda_insatisfecha;
	double exceso_papel_rojo;
	double exceso_papel_verde;
	double cont_rojo_acumulado;
	double cont_verde_acumulado;
	double cont_rojo;
	double cont_verde;
	double procesado;
	std::vector<double> probabilidad;

public:
	Papel(double r = 1.0/3.0);
	void simular(int n_sim);

private:
	void tabla_de_propabilidad();
	int generar_probabilidad();
	void recibir_papel();
	void demanda_papel();
	void maniana();
	void tarde();
};

#endif
