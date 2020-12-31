#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

int main(int argc, char* argv[]){

	ifstream f1,f2;
	f1.open(argv[1]);
	f2.open(argv[2]);


	if(!f1 || !f2){
		cerr << "Error al abrir el archivo" << endl;
		exit(1);
	}

	float n1, n2;
	int mejor1, mejor2;
	mejor1 = mejor2 = 0;

	for(int cont = 0; cont < 100; cont++){
		f1 >> n1;
		f2 >> n2;

		if(n1 < n2){
			mejor1++;
		} else {
			mejor2++;
		}
	}

	cout << "Resultados de la comparacion con los sistemas 1 (" << argv[1] << ") y 2 (" << argv[2] << ")" << endl;
	cout << "El sistema 1 es preferible un " << mejor1 << "% de veces" << endl;
	cout << "El sistema 2 es preferible un " << mejor2 << "% de veces" << endl;
	cout << endl;
}

