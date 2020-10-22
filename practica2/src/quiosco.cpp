#include <iostream>
#include <cstdlib>
#include <cmath>
#include "codigo-generadores.h"

using namespace std;

int main(int argc, char ** argv){

  int s, x, y, veces;
  char distribucion;

  if(argc != 6){
    cerr << "Uso incorrecto bin/quiosco_exe <valor de s> <valor de x> <valor de y> <numero de veces> <distribucion>" << endl;
    exit(1);
  } else {
    s = atoi(argv[1]);
    x = atoi(argv[2]);
    y = atoi(argv[3]);
    veces = atoi(argv[4]);
    distribucion = argv[5][0];
  }


  srand(time(NULL)); //Inicializa el generador de números pseudoaleatorios
  double* tablademanda;

  if(distribucion == 'a'){
    tablademanda = construye_prop_a(100); //Construye la tabla de búsqueda
  } else if(distribucion == 'b'){
    tablademanda = construye_prop_b(100); //Construye la tabla de búsqueda
  } else if(distribucion == 'c'){
    tablademanda = construye_prop_c(100); //Construye la tabla de búsqueda
  } else {
    cerr << "Distribución incorrecta, debe ser a b o c" << endl;
    exit(1);
  }

  int demanda; //Cada vez que se necesite un
               //valor del generador de demanda
  double sum, sum2, ganancia, gananciaesperada, desviaciont;

  sum=0.0; sum2=0.0;
  for (int i=0; i<veces; i++){
    demanda=genera_demanda(tablademanda,100);
    if (s>demanda) ganancia=demanda*x-(s-demanda)*y;
    else ganancia=s*x;
    sum+=ganancia;
    sum2+=ganancia*ganancia;
  }
  gananciaesperada=sum/veces;
  desviaciont=sqrt((sum2-veces*gananciaesperada*gananciaesperada)/(veces-1));


  cout << s << " " << x << " " << y << " " << veces << " " << distribucion << " " << gananciaesperada << " " << desviaciont << endl;
}

