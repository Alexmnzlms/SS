#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

// Definition of additional mathematicals functions
#define sq(X) {int aux=X; (X)*(X); }
#define dec(X) pow(10, X )
#define ctg(X) (1.0/tan(X))
#define actg(X) atan(1.0/(X))
#define sqn(X,Y) pow( X, 1.0/(Y) )
#define lgn(X,Y)  (log(Y)/log(X))


// Variables for time control
double _t = 0.0;
double _tinicio = 0.0;
double _tfin = 0.0;
double _inc_t = 0.0;
int _tcom = 1;

// Variables of Parameters
double __A = 0.0667;
double __B = 1.0E7;
double __C = 0.0222;
double __D = 1.0E7;
double __E = 36000.0;
double __F = 10.0;


// Vectors of model's variables
double *  __x = new double[1];
double *  __y = new double[1];

double *  x_aux = new double[1];
double *  y_aux = new double[1];

int pesca;
double proporcion;
int periodo;


// Functions for variables higher derivative calculation

// Function for calculation of x's higher derivative
double f1 ( double *  __x, double *  __y, double _t ){
	return ( ( ( __A ) * ( __x[0] ) ) * ( ( 1.0 ) - ( ( __x[0] ) / ( __B ) ) ) ) - ( ( __F ) * ( __y[0] ) ) ;
}

// Function for calculation of y's higher derivative
double f2 ( double *  __x, double *  __y, double _t ){
	return ( ( __C ) * ( __y[0] ) ) * ( ( ( __x[0] ) / ( __D ) ) - ( ( __y[0] ) / ( __E ) ) ) ;
}

// Function with Runge-Kutta of 4º order algorithm implementation for model.
void  resolver (double _t0, double _tf, double * _res ){
//		double *  x_aux = new double[1];
//		double *  y_aux = new double[1];
	double k1[2][1];
	double k2[2][1];
	double k3[2][1];
	double k4[2][1];

	double h = _inc_t ;

	for(_t=_t0; _t<(_tf-10e-8); _t+=_inc_t){
//		for(_t=_t0; _t<_tf; _t+=_inc_t){
//cout.precision(20);
//cout << " tactual " << _t << " tfin es " << _tf << endl;
//cout.precision(3);
		x_aux[0] = __x[0];
		y_aux[0] = __y[0];
		k1[0][0] = h * f1( __x, __y,_t );
		k1[1][0] = h * f2( __x, __y,_t );

// PREVIO CODIGO DE K2
		__x[0] = (x_aux[0]+k1[0][0] / 2);
		__y[0] = (y_aux[0]+k1[1][0] / 2);

// CODIGO DE K2
		k2[0][0] = h * f1( __x, __y,_t + (h/2) );
		k2[1][0] = h * f2( __x, __y,_t + (h/2) );

// PREVIO CODIGO DE K3
		__x[0] = (x_aux[0]+k2[0][0] / 2);
		__y[0] = (y_aux[0]+k2[1][0] / 2);

// CODIGO DE K3
		k3[0][0] = h * f1( __x, __y,_t + (h/2) );
		k3[1][0] = h * f2( __x, __y,_t + (h/2) );

// PREVIO CODIGO DE K4
		__x[0] = (x_aux[0]+k3[0][0]);
		__y[0] = (y_aux[0]+k3[1][0]);

// CODIGO DE K4
		k4[0][0] = h * f1( __x, __y,_t + h);
		k4[1][0] = h * f2( __x, __y,_t + h);

// CODIGO FINAL
		__x[0] = x_aux[0];
		__x[0] += (k1[0][0]+2*k2[0][0]+2*k3[0][0]+k4[0][0])/6;
		__y[0] = y_aux[0];
		__y[0] += (k1[1][0]+2*k2[1][0]+2*k3[1][0]+k4[1][0])/6;
		if (__x[0]<0.0) __x[0] = 0.0;
		if (__y[0]<0.0) __y[0] = 0.0;
	}
//cout << " termino el bucle de t= " << _tf << endl;
//		delete  x_aux;
//		delete  y_aux;
	_res[0] = _t;
	_res[1] = __x[0];
	_res[2] = __y[0];
}

// Main: execution (with text interface) of the model's simulation.
int main(int argc, char * argv[]){

  if(argc != 3){
    pesca = 0;
    periodo = 1;
    proporcion = 0.0;
  } else {
    pesca = 0;
    periodo = atoi(argv[1]);
    proporcion = stod(argv[2]);
  }
//	cerr << " tinicio => ";
//	cin >> _tinicio;
//	cout << " tinicio " << _tinicio << endl;
	_tinicio = 0.0;

//	cerr << " tfin => ";
//	cin >> _tfin;
//	cout << " tfin " << _tfin << endl;
	cerr << " Duracion de la simulacion => ";
	cin >> _tfin;

//	cerr << " Incremento de tiempo, inc_t => ";
//	cin >> _inc_t;
//	if(_inc_t <= 0.0){
//		cerr << "Error: _int_t <= 0.0" << endl ;
//		exit(0);
//	}
//	cout << " inc_t " << _inc_t << endl;
	_inc_t = 0.1;

//	cerr << " Intervalo de comunicacion, tcom => ";
//	cin >> _tcom;
//	if(_tcom <= 0){
//		cerr << "Error: _tcom < 1" << endl ;
//		exit(0);
//	}
//	cout << " tcom " << _tcom << endl;
	_tcom = 10;

	cerr << " Numero inicial de peces pequeños, x(0) => ";
	cin >> __x[0];
//	cout << " x(0) "<< __x[0] << endl;


	cerr << " Numero inicial de peces grandes, y(0) => ";
	cin >> __y[0];
//	cout << " y(0) "<< __y[0] << endl;

/*
	cerr << " A_inic => ";
	cin >> __A;
	cout << " A " << __A << endl;

	cerr << " B_inic => ";
	cin >> __B;
	cout << " B " << __B << endl;

	cerr << " C_inic => ";
	cin >> __C;
	cout << " C " << __C << endl;

	cerr << " D_inic => ";
	cin >> __D;
	cout << " D " << __D << endl;

	cerr << " E_inic => ";
	cin >> __E;
	cout << " E " << __E << endl;

	cerr << " F_inic => ";
	cin >> __F;
	cout << " F " << __F << endl;
*/
	double inc = _inc_t*_tcom;
	double * aux = new double[2];
	cout << "\tt\tx\ty" << endl;
	cout << "\t" << _tinicio << "\t" << __x[0]<< "\t" << __y[0]<< endl;

	for(double t=_tinicio ; t < (_tfin-10e-8) ; t += inc ){
		resolver( t, t + inc, aux );
      if((int)t % periodo == 0 && (int)t > 0 && __y[0] > 0){
        __y[0]*= (1.0 - proporcion);
        pesca += (proporcion*__y[0]);
      }
		cout << "\t" << aux[0]<< "\t" << aux[1]<< "\t" << aux[2]<< endl;
	}
   cout << "Pesca = " << pesca << endl;
   cout << "Periodo= " << periodo << endl;
   cout << "Proprocion= " << proporcion << endl;
}


