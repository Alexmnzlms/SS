#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

int main(int argc, char* argv[]){

	ifstream fi;
	fi.open(argv[1]);

	if(!fi){
		cerr << "Error al abrir el archivo" << endl;
		exit(1);
	}

	float n[100];
	float suma = 0;

	for(int i = 0; i < 100; i++){
		fi >> n[i];
		suma += n[i];
	}
	float media = suma / 100;

	float varianza = 0.0;

	for(int j = 0; j < 100; j++){
		varianza += ((n[j] + media) * (n[j] + media));
	}

	varianza = varianza / 100;

	float t_student = 1.6604;

	float sup = media + t_student * sqrt(varianza/100);
	float inf = media - t_student * sqrt(varianza/100);

	cout << "Media: " << media << endl;
	cout << "Varianza: " << varianza << endl;
	cout << "Intervalo: [" << inf << ", " << sup <<  "]" << endl;
}
