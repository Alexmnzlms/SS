#include "reparadores_mantenimiento.h"

bool compare(const suc &s1, const suc &s2){
	return s1.tiempo < s2.tiempo;
}


/* Inserta de forma ordenada un elemento en la lista de sucesos */
void insertar_lsuc(suc n){
	lsuc.push_back(n);
	// Mantener ordenada la lista por el tiempo de los sucesos
	lsuc.sort(compare);
}

void eliminar_lsuc(int t, int m){
	bool encontrado = false;
	for(auto it = lsuc.begin(); it != lsuc.end() && !encontrado; ++it){
		if(it->tipo == t && it->maquina == m){
			encontrado = true;
			it = lsuc.erase(it);
		}
	}
}

/* Procedimiento temporizacion */
int temporizacion(){
	int suc_sig;
	suc_sig = lsuc.front().tipo;
	reloj = lsuc.front().tiempo;

	return suc_sig;
}

int temporizacion_maquina(){
	int maq;
	maq = lsuc.front().maquina;
	lsuc.pop_front();

	return maq;
}


/* Procedimiento suceso */
void suceso(int suc_sig,int maquina){
	switch(suc_sig){
		case FALLO_MAQUINA:
			falloMaquina(maquina);
			break;
		case FIN_REPARACION:
			finReparacion(maquina);
			break;
		case FIN_SIMULACION:
			generadorInformes();
			break;
		case MANTENIMIENTO:
			mantenimiento();
			break;
		case FIN_MANTENIMIENTO:
			finMantenimiento(maquina);
			break;
	}
}


/* Procedimiento inicializacion */
void inicializacion()
{
	//srandom(time(NULL));
	reloj = 0.0;
	parar = false;
	rotas = 0;
	repuestos = s;
	fallo = false;
	libres = reparadores;
	encola = 0;
	enreparacion = 0;
	numfallos = 0;
	durfallos = 0.0;
	entrefallos = 0.0;
	finfalloanterior=0.0;
	maqport = 0.0;
	ocio = 0.0;
	tusocio = reloj;
	tusrep = reloj;

	lsuc.clear();

	for (int i=0; i<n; i++){
		nodo.tipo = FALLO_MAQUINA;
		nodo.maquina = i;
		nodo.tiempo = reloj+generafallo(tfallo);
		insertar_lsuc(nodo);
	}

	nodo.tipo = FIN_SIMULACION;
	nodo.maquina = -1;
	nodo.tiempo = reloj+tparada;
	insertar_lsuc(nodo);

	nodo.tipo = MANTENIMIENTO;
	nodo.maquina = -1;
	nodo.tiempo = reloj+trevision;
	insertar_lsuc(nodo);
}


/* Procedimiento fallo de maquina */
void falloMaquina(int m)
{
	maqport += (reloj - tusrep) * enreparacion;
	tusrep = reloj;
	enreparacion ++;

	if (libres > 0){
		ocio += (reloj - tusocio) * libres;
		tusocio = reloj;
		libres --;
		nodo.tipo = FIN_REPARACION;
		nodo.maquina = m;
		nodo.tiempo = reloj+generareparacion(trepar);
		insertar_lsuc(nodo);
	} else{
 		encola ++;
	}

	if (repuestos > 0){
		repuestos --;
		nodo.tipo = FALLO_MAQUINA;
		nodo.maquina = m;
		nodo.tiempo = reloj+generafallo(tfallo);
		insertar_lsuc(nodo);
	} else {
		rotas ++;
		if (!fallo){
			fallo = true;
			comienzofallo = reloj;
			numfallos ++;
			if (numfallos > 1){
				entrefallos += reloj - finfalloanterior;
			}
		}
	}
}


/* Procedimiento fin de reparacion */
void finReparacion(int m)
{
	maqport += (reloj - tusrep) * enreparacion;
	tusrep = reloj;
	enreparacion --;

	if (encola > 0){
		encola --;
		nodo.tipo = FIN_REPARACION;
		nodo.maquina = m;
		nodo.tiempo = reloj+generareparacion(trepar);
		insertar_lsuc(nodo);
	} else {
		ocio += (reloj - tusocio) * libres;
		tusocio = reloj;
		libres ++;
	}

	if (rotas == 0){
		repuestos ++;
	}
	else {
		rotas --;
		nodo.tipo = FALLO_MAQUINA;
		nodo.maquina = m;
		nodo.tiempo = reloj+generafallo(tfallo);
		insertar_lsuc(nodo);

		if (rotas == 0){
			durfallos += reloj - comienzofallo;
			fallo = false;
			finfalloanterior = reloj;
		}
	}
}

void mantenimiento(){
	int minimo = min(libres, n-rotas);
	set<int> numeros_aleatorios;
	int n_aleatorio;

	if(minimo > 0){
		if(libres < (n-rotas)){
			for(int i = 0; i < libres; i++){
				n_aleatorio = random() % (n-rotas);
				while(numeros_aleatorios.find(n_aleatorio) != numeros_aleatorios.end()){
					n_aleatorio = random() % (n-rotas);
				}
				numeros_aleatorios.insert(n_aleatorio);
			}
			for(auto it = numeros_aleatorios.begin(); it != numeros_aleatorios.end(); ++it){
				nodo.tipo = FIN_MANTENIMIENTO;
				nodo.maquina = (*it);
				nodo.tiempo = reloj+generaruniforme(tmantmin, tmantmax);
				insertar_lsuc(nodo);
				eliminar_lsuc(FALLO_MAQUINA, *it);
			}
			libres = 0;
		} else {
			for(int i = 0; i < (n-rotas); i++){
				nodo.tipo = FIN_MANTENIMIENTO;
				nodo.maquina = i;
				nodo.tiempo = reloj+generaruniforme(tmantmin,tmantmax);
				insertar_lsuc(nodo);
				eliminar_lsuc(FALLO_MAQUINA, i);
			}
			libres -= (n-rotas);
		}
	}

	nodo.tipo = MANTENIMIENTO;
	nodo.maquina = -1;
	nodo.tiempo = reloj+trevision;
	insertar_lsuc(nodo);
}

void finMantenimiento(int m){

	if(encola > 0){
		encola--;
		nodo.tipo = FIN_REPARACION;
		nodo.maquina = m;
		nodo.tiempo = reloj+generareparacion(trepar);
		insertar_lsuc(nodo);
	}

	nodo.tipo = FALLO_MAQUINA;
	nodo.maquina = m;
	nodo.tiempo = reloj+generafallo(tfallo);
	insertar_lsuc(nodo);
}

/* Procedimiento generador de informes */
void generadorInformes(){

	parar = true; //para detener la simulacion
	/* ultimas actualizaciones de contadores estadisticos */
	maqport += (reloj - tusrep) * enreparacion;
	ocio += (reloj - tusocio) * libres;
	if (fallo){
		durfallos += reloj - comienzofallo;
	}

	// Imprimir todas las medidas de rendimiento
	DMF += durfallos/numfallos;
	TMEFS += entrefallos/(numfallos-1);
	NMMR += maqport/reloj;
	TOR += 100*ocio/(reloj*reparadores);
	DTF += 100*durfallos/reloj;

	//printf("\nDuracion media de los fallos = %.3f",DMF/i);
	//printf("\nTiempo medio entre fallos del sistema = %.3f",TMEFS/i);
	//printf("\nNumero medio de maquinas en reparacion = %.3f",NMMR/i);
	//printf("\nPorcentaje de tiempo de ocio de los reparadores = %.3f",TOR/i);
	//printf("\nPorcentaje de duracion total de los fallos = %.3f",DTF/i);
	//printf("\n");
	printf("\n%.3f",DMF/i);
	printf("\n%.3f",TMEFS/i);
	printf("\n%.3f",NMMR/i);
	printf("\n%.3f",TOR/i);
	printf("\n%.3f",DTF/i);
	//printf("\n");
}

/* generadores de datos */
float generador_exponencial(float media){
	float u;
	u = (float) random();
	u = u/(float)(RAND_MAX+1.0);

	return(-media*log(1-u));
}

// Generador de tiempo de fallo (exponencial)
float generafallo(float media){
	return generador_exponencial(media);
}

// Generador de tiempo de reparacion (exponencial)
float generareparacion(float media){
	return generador_exponencial(media);
}

float generaruniforme(float min, float max){
	float u;
	u = (float) random();
	u = (float) (u/(RAND_MAX+1.0));
	return(min+(max-min)*u);
}

void print_lsuc(int n){
	int i = 0;
	printf("----------------------------------------------------------------\n");
	for(auto it = lsuc.begin(); it != lsuc.end(); ++it,i++){
		printf("[ n=%d i=%d tipo=%d maquina=%d tiempo=%0.3f ]\n", n, i, it->tipo, it->maquina, it->tiempo);;
	}
	printf("----------------------------------------------------------------\n");
}

/* Programa principal */
int main(int argc, char *argv[]){
	int suc_sig;
	int maq;

	if (argc != 11){
		printf("\n\nFormato Argumentos -> totalMaq maqRepuesto reparadores trepar tfallo tparada iter trevision tmantmin tmantmax\n\n");
		exit(1);
	}

	n = atoi(argv[1]);
	s = atoi(argv[2]);
	reparadores = atoi(argv[3]);
	trepar = atof(argv[4]);
	tfallo = atof(argv[5]);
	tparada = atoi(argv[6]);
	iter = atoi(argv[7]);
	trevision = atoi(argv[8]);
	tmantmin = atoi(argv[9]);
	tmantmax = atoi(argv[10]);

	DMF = 0;
	TMEFS = 0;
	NMMR = 0;
	TOR = 0;
	DTF = 0;

	srandom(123456);

	for(i = 1; i <= iter; i++){
	inicializacion();
	int cont = 0;
		while(!parar){
			//print_lsuc(cont);
			cont++;
			suc_sig = temporizacion();
			maq = temporizacion_maquina();
			suceso(suc_sig,maq);
		}
	}
}
