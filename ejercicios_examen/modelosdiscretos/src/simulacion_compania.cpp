#include "compania.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv){
	int sim = atoi(argv[1]);
	
	Compania comp = Compania();
	comp.simular(sim);
}
