#ifndef __SIMUL
#define __SIMUL

class Simulacion {
	private:
		int numeq;
		double* estado;
		double t;
		double dt;
		double a;
		double b;
		double tinic;
		double tfin;

	public:
		void main();
		void fijar_parametros();

	private:
		void integracion();
		void one_step(int metodo, double* inp, double*out, double tt, double hh);
		void one_step_runge_kuttai(double* inp, double* out, double tt, double hh);
		void one_step_euler(double* inp, double* out, double tt, double hh);
		void derivacion(double* est, double* f, double tt);
		void salida();
};


#endif
