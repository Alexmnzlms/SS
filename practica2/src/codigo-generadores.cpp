#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "codigo-generadores.h"

double uniforme() //Genera un número uniformemente distribuido en el
						//intervalo [0,1) a partir de uno de los generadores
						//disponibles en C. Lo utiliza el generador de demanda
{
	int t = random();
	double f = ((double)RAND_MAX+1.0);

	return (double)t/f;
}

double* construye_prop_a(int n) //Construye la tabla de búsqueda de
										 //tamaño n para la distribución de
										 //la demanda del apartado (a).
{
	int i;
	double* temp;
	if ((temp = (double*) malloc(n*sizeof(double))) == NULL){
		fputs("Error reservando memoria para generador uniforme\n",stderr);
		exit(1);
	}
	temp[0] = 1.0/n;

	for (i=1;i<n;i++){
		temp[i] = temp[i-1]+1.0/n;
	}

	return temp;
}


double* construye_prop_b(int n) //Construye la tabla de búsqueda de
										 //tamaño n para la distribución de
										 //la demanda del apartado (b).
{
	int i, max;
	double* temp;
	if ((temp = (double*) malloc(n*sizeof(double))) == NULL){
		fputs("Error reservando memoria para generador proporcional\n",stderr);
		exit(1);
	}
	max = (n/2)*(n+1);
	temp[0] = n*1.0/max;

	for (i=1;i<n;i++){
		temp[i] = temp[i-1]+(double)(n-i)/max;
	}

	return temp;
}

double* construye_prop_c(int n) //Construye la tabla de búsqueda de
										 //tamaño n para la distribución de
										 //la demanda del apartado (c).
{
	int i, max;
	double* temp;
	if ((temp = (double*) malloc(n*sizeof(double))) == NULL)
	{
		fputs("Error reservando memoria para generador triangular\n",stderr);
		exit(1);
	}
	max = n*n/4;
	temp[0] = 0.0;

	for (i=1;i<(n/2);i++){
		temp[i] = temp[i-1]+(double)i/max;
	}

	for (i=(n/2);i<n;i++){
		temp[i] = temp[i-1]+(double)(n-i)/max;
	}

	return temp;
}

int genera_demanda(double* tabla,int tama) // Genera un valor de la
		  // distribución de la demanda codificada en tabla, por el
		  // método de tablas de búsqueda.
		  // tama es el tamaño de la tabla, 100 en nuestro caso particular
{
	int i = 0;
	double u = uniforme();

	while((i<tama) && (u>=tabla[i])){
		i++;
	}

	return i;
}

double* construye_prop_c_ord(int n) //Construye la tabla de búsqueda de
										 //tamaño n para la distribución de
										 //la demanda del apartado (c).
{
	int i, max;
	double* temp;
	if ((temp = (double*) malloc(n*sizeof(double))) == NULL)
	{
		fputs("Error reservando memoria para generador triangular\n",stderr);
		exit(1);
	}
	max = n*n/4;
	temp[0] = 0.0;

	for (i=1;i<(n/2);i++){
		temp[i] = (double)i/max;
	}

	for (i=(n/2);i<n;i++){
		temp[i] = (double)(n-i)/max;
	}

	return temp;
}

int genera_demanda_ord(double* tabla,int tama) // Genera un valor de la
		  // distribución de la demanda codificada en tabla, por el
		  // método de tablas de búsqueda.
		  // tama es el tamaño de la tabla, 100 en nuestro caso particular
{
	int i = 0;
	double u = uniforme();

	int* indices = new int [tama];
	int mid = (tama / 2);
	int max = mid - 1;

	indices[0] = 0;
	indices[1] = mid;

	int p = 2;
	for(int j = 1; j < max; j++){
		indices[p] = mid - j;
		p++;
		indices[p] = mid + j;
		p++;
	}

	double* tabla_ord = new double [tama];

	tabla_ord[0] = 0;
	for(int k = 1; k < tama; k++){
		tabla_ord[k] = tabla_ord[k-1] + tabla[k];
	}

	while((i<tama) && (u>=tabla_ord[i])){
		i++;
	}

	return indices[i];
}

int genera_demanda_bb(double* tabla, int tama){
	int a, b, i;
	double u = uniforme();

	a = 1;
	b = tama;

	while(a <= b){
		i = (a + b) / 2;
		if(u < tabla[i]){
			if(i == 1){
				return i;
			} else if (tabla[i -1] <= u){
				return i;
			} else {
				b = i - 1;
			}
		} else {
			a = i + 1;
		}
	}

	return 0;
}

int genera_demanda_constante(int tama){
	double u = uniforme();

	return u * tama;
}
