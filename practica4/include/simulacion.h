#ifndef __SIMUL
#define __SIMUL

#include <string>

class Simulacion {
	private:
		int numeq;
		double* estado;
		double t;
		double dt;
		double a;
		double b;
		double tfin;
		bool modificar_salida;
		std::string fichero;

	public:
		Simulacion();
		void fijar_parametros(int numeq, double a, double b, double* estado, double dt, double tinic, double tfin, bool salida, std::string fichero);
		void integracion(int metodo);

	private:
		void one_step(int metodo, double* inp, double*out, double tt, double hh);
		void one_step_runge_kuttai(double* inp, double* out, double tt, double hh);
		void one_step_euler(double* inp, double* out, double tt, double hh);
		void derivacion(double* est, double* f, double tt);
		void salida(bool primera = false);
};

#endif
