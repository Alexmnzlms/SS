#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
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
if ((temp = (double*) malloc(n*sizeof(double))) == NULL)
  {
   fputs("Error reservando memoria para generador uniforme\n",stderr);
   exit(1);
  }
temp[0] = 1.0/n;
for (i=1;i<n;i++)
  temp[i] = temp[i-1]+1.0/n;
return temp;
}


double* construye_prop_b(int n) //Construye la tabla de búsqueda de
                               //tamaño n para la distribución de
                               //la demanda del apartado (b).
{
int i, max;
double* temp;
if ((temp = (double*) malloc(n*sizeof(double))) == NULL)
  {
   fputs("Error reservando memoria para generador proporcional\n",stderr);
   exit(1);
  }
max = (n/2)*(n+1);
temp[0] = n*1.0/max;
for (i=1;i<n;i++)
  temp[i] = temp[i-1]+(double)(n-i)/max;
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
for (i=1;i<(n/2);i++)
  temp[i] = temp[i-1]+(double)i/max;
for (i=(n/2);i<n;i++)
  temp[i] = temp[i-1]+(double)(n-i)/max;
return temp;
}

int genera_demanda(double* tabla,int tama) // Genera un valor de la
        // distribución de la demanda codificada en tabla, por el
        // método de tablas de búsqueda.
        // tama es el tamaño de la tabla, 100 en nuestro caso particular
{
int i;
double u = uniforme();
i = 0;
while((i<tama) && (u>=tabla[i]))
  i++;
return i;
}
