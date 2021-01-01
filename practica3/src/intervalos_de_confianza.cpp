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

	float n1, n2, nresta[100];
	float suma = 0;

	for(int i = 0; i < 100; i++){
		f1 >> n1;
		f2 >> n2;
		nresta[i] = n1 - n2;

		suma += nresta[i];
	}
	float media = suma / 100;

	float varianza = 0.0;

	for(int j = 0; j < 100; j++){
		varianza += ((nresta[j] + media) * (nresta[j] + media));
	}

	varianza = varianza / 100;

	float t_student = 1.6604;

	float sup = media + t_student * sqrt(varianza/100);
	float inf = media - t_student * sqrt(varianza/100);

	cout << "Intervalos de confianza para " << argv[1] << " y " << argv[2] << endl;
	cout << "Media: " << media << endl;
	cout << "Varianza: " << varianza << endl;
	cout << "Intervalo: [" << inf << ", " << sup <<  "]" << endl;
}
