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

	string output[5];
	output[0] = string(argv[1]) + "_dmf";
	output[1] = string(argv[1]) + "_tmefs";
	output[2] = string(argv[1]) + "_nmmr";
	output[3] = string(argv[1]) + "_tor";
	output[4] = string(argv[1]) + "_dtf";

	ofstream fo[5];
	for(int f = 0; f < 5; f++){
		fo[f].open(output[f]);
	}

	int i = 1;
	string linea;
	float num;

	while(!fi.eof()){
		for(int f = 0; f < 5; f++){
			fi >> linea;
			if(linea == "-nan"){
				num = 0.0;
			} else {
				num = stof(linea);
			}
			fo[f] << i << " " << num << endl;
			i++;
		}
	}

	for(int f = 0; f < 5; f++){
		fo[f].close();
	}
	fi.close();
}

