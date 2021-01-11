#ifndef __SIMUL
#define __SIMUL

#include <string>
#include <vector>

using namespace std;

class Simulacion {
	private:
		int numeq;
		vector<double> estado;
		double t;
		double dt;
		double a;
		double b;
		double tfin;
		bool modificar_salida;
		string fichero;

	public:
		Simulacion();
		void fijar_parametros(int numeq, double a, double b, vector<double> estado, double dt, double tinic, double tfin, bool salida, string fichero);
		void integracion(int metodo);

	private:
		void one_step(int metodo, vector<double> inp, vector<double>& out, double tt, double hh);
		void one_step_runge_kuttai(vector<double> inp, vector<double>& out, double tt, double hh);
		void one_step_euler(vector<double> inp, vector<double>& out, double tt, double hh);
		void derivacion(vector<double> est, vector<double>& f, double tt);
		void salida(bool primera = false);
};

#endif
