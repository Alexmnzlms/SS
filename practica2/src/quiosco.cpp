#include <iostream>
#include <cstdlib>
#include "codigo-generadores.h"

using namespace std;

int main(int argc, char ** argv){

  srand(time(NULL)); //Inicializa el generador de números pseudoaleatorios

  double * tablabdemanda = construye_prop_a(100); //Construye la tabla de búsqueda

  int demanda = genera_demanda(tablabdemanda,100); //Cada vez que se necesite un
                                                  //valor del generador de demanda


}

