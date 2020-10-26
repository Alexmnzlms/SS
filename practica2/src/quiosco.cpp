#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include "codigo-generadores.h"

using namespace std;

int main(int argc, char ** argv){

  int x, y, veces, modificacion, z;
  char distribucion;

  if(argc != 6 && argc != 7){
    cerr << "Uso incorrecto bin/quiosco_exe <valor de x> <valor de y> <numero de veces> <distribucion> <modificacion> <valor de z>" << endl;
    exit(1);
  } else {
    x = atoi(argv[1]);
    y = atoi(argv[2]);
    veces = atoi(argv[3]);
    distribucion = argv[4][0];
    modificacion = atoi(argv[5]);
    if(modificacion != 0) z = atoi(argv[6]);
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

  for (int s = 0; s <= 100; s++){
    sum = sum2 =0.0;
    for (int i = 0; i < veces; i++){
      demanda = genera_demanda(tablademanda,100);
      switch(modificacion){
        case 0:
          if (s > demanda) ganancia = demanda*x - (s - demanda)*y;
          else ganancia = s*x;
          break;
        case 1:
          if (s > demanda) ganancia = demanda*x - z;
          else ganancia = s*x;
          break;
        case 2:
          if (s > demanda) ganancia = demanda*x - min(z, (s-demanda)*y);
          else ganancia = s*x;
          break;
        default:
          ganancia = 0;
          break;
      }
    sum += ganancia;
    sum2 += ganancia*ganancia;
    }
  gananciaesperada = sum/veces;
  desviaciont = sqrt((sum2-veces*gananciaesperada*gananciaesperada)/(veces-1));


  cout << s << " " << x << " " << y << " " << veces
       << " " << distribucion << " " << gananciaesperada
       << " " << desviaciont << endl;
  }
}

