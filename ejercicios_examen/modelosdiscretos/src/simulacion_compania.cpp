#include "compania.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv){
	int sim = atoi(argv[1]);
	int mod = atoi(argv[2]);

	Compania comp = Compania(mod);
	comp.simular(sim);
}
