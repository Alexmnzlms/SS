#include "reparadores.h"

bool compare(const suc &s1, const suc &s2){
	return s1.tiempo < s2.tiempo;
}


/* Inserta de forma ordenada un elemento en la lista de sucesos */
void insertar_lsuc(suc n){
	lsuc.push_back(n);
	// Mantener ordenada la lista por el tiempo de los sucesos
	lsuc.sort(compare);
}

/* Procedimiento temporizacion */
int temporizacion(){
	int suc_sig;
	suc_sig = lsuc.front().tipo;
	reloj = lsuc.front().tiempo;
	lsuc.pop_front();

	return suc_sig;
}


/* Procedimiento suceso */
void suceso(int suc_sig){
	switch(suc_sig){
		case FALLO_MAQUINA:
			falloMaquina();
			break;
		case FIN_REPARACION:
			finReparacion();
			break;
		case FIN_SIMULACION:
			generadorInformes();
			break;
	}
}


/* Procedimiento inicializacion */
void inicializacion()
{
	srandom(time(NULL));
	//srandom(123456);
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

	for (int i=0; i<n; i++){
		nodo.tipo = FALLO_MAQUINA;
		nodo.tiempo = reloj+generafallo(tfallo);
		insertar_lsuc(nodo);
	}

	nodo.tipo = FIN_SIMULACION;
	nodo.tiempo = reloj+tparada;
	insertar_lsuc(nodo);
}


/* Procedimiento fallo de maquina */
void falloMaquina()
{
	maqport += (reloj - tusrep) * enreparacion;
	tusrep = reloj;
	enreparacion ++;

	if (libres > 0){
		ocio += (reloj - tusocio) * libres;
		tusocio = reloj;
		libres --;
		nodo.tipo = FIN_REPARACION;
		nodo.tiempo = reloj+generareparacion(trepar);
		insertar_lsuc(nodo);
	} else{
 		encola ++;
	}

	if (repuestos > 0){
		repuestos --;
		nodo.tipo = FALLO_MAQUINA;
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
void finReparacion()
{
	maqport += (reloj - tusrep) * enreparacion;
	tusrep = reloj;
	enreparacion --;

	if (encola > 0){
		encola --;
		nodo.tipo = FIN_REPARACION;
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
		nodo.tiempo = reloj+generafallo(tfallo);
		insertar_lsuc(nodo);

		if (rotas == 0){
			durfallos += reloj - comienzofallo;
			fallo = false;
			finfalloanterior = reloj;
		}
	}
}

/* Procedimiento generador de informes */
void generadorInformes(){
	float DMF,TMEFS,NMMR,TOR,DTF;

	parar = true; //para detener la simulacion
	/* ultimas actualizaciones de contadores estadisticos */
	maqport += (reloj - tusrep) * enreparacion;
	ocio += (reloj - tusocio) * libres;
	if (fallo){
		durfallos += reloj - comienzofallo;
	}

	// Imprimir todas las medidas de rendimiento
	DMF = durfallos/numfallos;
	TMEFS = entrefallos/(numfallos-1);
	NMMR = maqport/reloj;
	TOR = 100*ocio/(reloj*reparadores);
	DTF = 100*durfallos/reloj;

	printf("\nDuracion media de los fallos = %.3f",DMF);
	printf("\nTiempo medio entre fallos del sistema = %.3f",TMEFS);
	printf("\nNumero medio de maquinas en reparacion = %.3f",NMMR);
	printf("\nPorcentaje de tiempo de ocio de los reparadores = %.3f",TOR);
	printf("\nPorcentaje de duracion total de los fallos = %.3f",DTF);
	printf("\n");
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

/* Programa principal */
int main(int argc, char *argv[]){
	int suc_sig;

	if (argc != 7){
		printf("\n\nFormato Argumentos -> totalMaq maqRepuesto reparadores trepar tfallo tparada\n\n");
		exit(1);
	}

	n = atoi(argv[1]);
	s = atoi(argv[2]);
	reparadores = atoi(argv[3]);
	trepar = atof(argv[4]);
	tfallo = atof(argv[5]);
	tparada = atoi(argv[6]);

	inicializacion();
	while(!parar){
		suc_sig = temporizacion();
		suceso(suc_sig);
	}
}
