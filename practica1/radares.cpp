/**
@brief Implementa el sistema de radares con varias simulaciones y calculo de medias y desviaciones tipicas, con incremento del tiempo variable.

NOTA: LOS VALORES PARA LA SIMULACION:

	- NUMERO DE RADARES DEL SISTEMA.
	- NUMERO DE PIEZAS DE REPUESTO.
	- TIEMPO ENTRE FALLOS (tfallo).
	- TIEMPOS DE REPARACION (vmin y vmax).
	- TIEMPO DE FIN DE SIMULACION (tiempo_total).
	- NUMERO DE SIMULACIONES

HAY QUE DARLE VALOR EN LA LINEA DE COMANDOS

*/

#include <iostream>
#include <time.h>
#include <list>
#include <math.h>
#include <stdlib.h>

using namespace std;

#define suceso_llegada 0
#define suceso_fallo 1
#define suceso_finsimulacion 2

/**
@brief Estructura que representara un suceso en el sistema y en la que se almacenan el tipo de suceso y el instante en que ocurrira.
*/
typedef struct {
	int suceso;
	float tiempo;
} Nodo;

/**
@brief Crea sucesos iniciales de fallo para cada radar, asi como el suceso fin de simulacion.
Ademas establece los valores necesarios de las variables de estado a los valores iniciales.
*/
void inicializacion();

/**
@brief Extrae de la lista de sucesos, el suceso que se producira mas proximo en el tiempo (es decir el que esta en el tope de la cola).
Ademas hace que el reloj que se actualice al instante en que ocurre el suceso.
@return Devuelve el tipo de suceso que se extrae de la lista.
*/
int temporizacion();

/**
@brief Evalua el suceso que se le pasa como parametro y llama a la funcion correspondiente.
@param suc_sig Representa al suceso que va a ocurrir a continuacion. Se evaluara y se llamara a la funcion que lo procesa.
*/
void suceso(int suc_sig);

/**
@brief Representa al suceso de llegada de un componente reparado.

Este procedimiento comprueba si habia algun radar no operativo por falta de componentes, en ese caso al llegar la pieza pasa a estar operativo y se fija el instante de tiempo en el que sucedera el siguiente fallo y se actualiza el tiempo que ha estado desprotegido el sistema. Si todos los radares estaban operativos y se produce una llegada, se dispondra de una nueva pieza de respuesto.
*/
void llegada();

/**
@brief Representa el procedimiento de fallo uno de los componentes de un radar.

Si hay piezas de repuesto disponibles se sustituira de inmediato sin que el sistema este desprotegido, y se fijara el siguiente fallo de ese componente, ademas de disponer de un repuesto menos.
En caso de no haber piezas disponiobles comienza el tiempo de desproteccion del sistema porque se dispone de un radar menos.
En cualquiera de los casos el componente averiado debe ser reparado.
*/
void fallo();

/**
@brief Procedimiento que finaliza la simulacion, dando la orden de parar y calculando los valores de salida de la simulacion
*/
void fin();

/**
@brief Compara sucesos por tiempo de ocurrencia
*/
bool compare(const Nodo &s1, const Nodo &s2);

/**
@brief  Inserta de forma ordenada un elemento en la lista de sucesos
*/
void insertar_lsuc(Nodo n);

/**
@brief Generador de datos exponencial de tiempos entre fallos. El valor que le sirve de base para calcular el nuevo tiempo de fallo es tfallo.
@return El valor real que representa el nuevo tiempo en el que se produce un fallo.
*/
float generafallo();

/**
@brief Generador de datos uniforme de tiempos de realizacion de una reparacion. Los valores que le sirven de base para calcular el tiempo de reparacion son vmin y vmax.
@return El valor real que representa el tiempo que se tarda en reparar y devolver una pieza.
*/
float generareparacion();

/* ESTE ES EL CONJUNTO DE VALORES QUE HAY QUE INICIALIZAR*/

float reloj; //marca el valor del tiempo simulado, inicialmente cero
bool parar; //Para detener la simulacion
float tfallo; //Para establecer los tiempos entre fallos.
int disponibles; //Indica el numero de piezas de respuesto que tenemos en el sistema
int total_reserva; //Indica el numero de piezas de reserva con las que se inicia la simulacion
int total_radares; //Indica el numero de radares que tenemos en el sistema.
int radares; //Indica el numero de radares operativos del sistema.
float tiempo_total; //Indica el tiempo de fin de simulacion.
float vmin, vmax; //Para establecer el intervalo de tiempo entre reparaciones.
//Indica el numero de simulaciones que se van a realizar.
int simulaciones; // numero de simulaciones


int i; //variable contadora
float inicio; //Para marcar el instante de tiempo en el que comienza la desproteccion del sistema.

float veces; // numero de veces que se rompe un radar y no hay repuestos
float media_veces = 0.0; //Indicara la media para las sucesivas simulaciones del numero de fallos sin repuestos en los radares.
float media_veces2 = 0.0;
float desv_veces = 0.0; //Indicara la desviacion tipica para las sucesivas simulaciones del numero de fallos en los radares.
float tiempo_desprotegido; // Tiempo de desproteccion del espacio aereo
float media_tiempo_desprotegido = 0.0; //Indicara la media para las sucesivas simulaciones del tiempo de desproteccion.
float media_tiempo_desprotegido2 = 0.0;
float desv_tiempo_desprotegido = 0.0; //Indicara la desviacion tipica para las sucesivas simulaciones del tiempo de desproteccion.
float porcentaje_desproteccion; // porcentaje de desproteccion sobre el total de tiempo simulado
float media_porcentaje_desproteccion = 0.0; //Indicara la media para las sucesivas simulaciones del porcentaje de desproteccion.
float media_porcentaje_desproteccion2 = 0.0;
float desv_porcentaje_desproteccion = 0.0; //Indicara la desviacion tipica para las sucesivas simulaciones del porcentaje de desproteccion.
list<Nodo> lsuc; //cola con prioridad de sucesos ordenados por el menor tiempo

/**
@brief Funcion principal.
@param argc Indica el numero de parametros que se le pasan al programa en la linea de ordenes.
@param argv Estructura que almacena los distintos parametros que se le pasan al programa en la linea de ordenes.
@return 0 en el caso de que su ejecucion sea correcta.
*/
int main(int argc, char *argv[])
{
	if ((argc != 8) && (argc != 3))
	{
		system("clear");
		cout << "Error: Numero incorrecto de parametros.\n";
		cout << "El uso correcto del programa es:\n";
		cout << "<numero de radares> <numero de repuestos> <vmin> <vmax> <tiempo fallo> <tiempo fin> <numero de simulaciones>\n" << endl;
		cout << " o tambien <numero de repuestos> <numero de simulaciones>\n" << endl;
		exit(1);
	}
	else if (argc == 8)
	      {
	      	total_radares = atoi(argv[1]);
		total_reserva = atoi(argv[2]);
		vmin = atof(argv[3]);
		vmax = atof(argv[4]);
		tfallo = atof(argv[5]);
	       	tiempo_total = atof(argv[6]);
		simulaciones = atoi(argv[7]);
	      }
	      else
	         {
	  		total_radares = 5;
			total_reserva = atoi(argv[1]);
			vmin = 15.0;
			vmax = 30.0;
			tfallo = 20.0;
			tiempo_total = 365.0;
			simulaciones = atoi(argv[2]);
		 }
	

	/* Defino una variable de tipo reloj para guardar el instante en el que comienza la ejecucion para saber al final cuanto tarda en ejecutarse */
	clock_t j,fin;
	double tiempo;
	j = clock();

	int suc_sig;

	//system("clear");
	cout << "\nSIMULANDO...\n" << endl;

	//inicializar generadores de datos
	srand(time(NULL));
	//srand(123456);

	//repito tantas veces el programa como indique simulaciones
	for(i = 0; i < simulaciones; i++)
	{
		//inicializo los datos y la lista de sucesos y simulo hasta que se produzca el suceso fin de simulacion
		inicializacion();
		while(!parar)
		{
			//inicializar generadores de datos
			suc_sig = temporizacion();
			suceso(suc_sig);
		}
		//vacio la lista de sucesos para la nueva simulacion
		while(!lsuc.empty())
			lsuc.pop_front();
	}

	//Calculo las medias y las desviaciones tipicas y las muestro por pantalla
	media_veces = media_veces / simulaciones;
	media_porcentaje_desproteccion = media_porcentaje_desproteccion / simulaciones;
	media_tiempo_desprotegido = media_tiempo_desprotegido / simulaciones;
	desv_porcentaje_desproteccion = sqrt((media_porcentaje_desproteccion2-simulaciones*media_porcentaje_desproteccion*media_porcentaje_desproteccion)/(simulaciones-1));
	desv_tiempo_desprotegido = sqrt((media_tiempo_desprotegido2-simulaciones*media_tiempo_desprotegido*media_tiempo_desprotegido)/(simulaciones-1));
	desv_veces = sqrt((media_veces2-simulaciones*media_veces*media_veces)/(simulaciones-1));

	cout << "\n\tMEDIAS:\n" << endl;
	cout << "La media del numero de fallos en los radares es: " << media_veces;
	cout << "\nLa media del tiempo de desproteccion es: " << media_tiempo_desprotegido;
	cout << "\nLa media del porcentaje de tiempo de desproteccion es: " << media_porcentaje_desproteccion;

	cout << "\n\n\tDESVIACIONES TIPICAS:\n" << endl;
	cout << "La desviacion tipica del numero de fallos en los radares es: " << desv_veces;
	cout << "\nLa desviacion tipica del tiempo de desproteccion es: " << desv_tiempo_desprotegido;
	cout << "\nLa desviacion tipica del porcentaje de tiempo de desproteccion es: " << desv_porcentaje_desproteccion;

	/* Calculamos el tiempo que tardo el programa en ejecutarse */
	fin =clock();
	fin= fin-j;
	tiempo = (double)fin/CLOCKS_PER_SEC;
	cout << "\n\nEl tiempo en realizar las " << simulaciones << " simulaciones ha sido de: " << tiempo << " segundos, con " << total_radares << " radares y " << total_reserva << " piezas, para un tiempo de parada de: " << tiempo_total << " y periodo de envio a reparacion entre " << vmin << " y " << vmax << ", y tiempos entre fallos del radar: " <<  tfallo << "\n" << endl;
}

bool compare(const Nodo &s1, const Nodo &s2)
{ return s1.tiempo < s2.tiempo; }

void insertar_lsuc(Nodo n)
{
  lsuc.push_back(n);
  // Mantener ordenada la lista por el tiempo de los sucesos
  lsuc.sort(compare);
}

void inicializacion()
{
	// Inicializacion de variables de estado
	reloj = 0.0;
	disponibles = total_reserva; //numero de componentes de repuesto
	radares = total_radares; //numero de radares (5 en principio)
	// Inicializacion de contadores estadísticos (no inicializados antes)
	veces = 0.0;
	tiempo_desprotegido = 0.0;
	porcentaje_desproteccion = 0.0;
	inicio = reloj;

	Nodo aux;
	// Inicializacion de la lista de sucesos
	for (int k=0; k<radares; k++)
	{
		aux.suceso = suceso_fallo;
		aux.tiempo = reloj + generafallo(); //generador de tiempos de vida hasta el fallo
		insertar_lsuc(aux);
	}
	aux.suceso = suceso_finsimulacion;
	aux.tiempo = tiempo_total; //tiempo de fin de simulacin
	insertar_lsuc(aux);
	parar = false;
}

//Procedimiento temporizacion;
int temporizacion()
{
	Nodo aux;
	int suc_sig;
	aux = lsuc.front();
	lsuc.pop_front();
	suc_sig = aux.suceso;
	reloj = aux.tiempo;
	return (suc_sig);
}

//Procedimiento suceso
void suceso(int suc_sig)
{
	if(suc_sig == suceso_llegada)
		llegada();
	else
	{
		if(suc_sig == suceso_fallo)
			fallo();
		else
			if(suc_sig == suceso_finsimulacion)
				fin();
	}
}

//Procedimiento llegada (de componente reparado)
void llegada()
{
	Nodo aux;
	if (radares < total_radares)
	{
		radares ++;
		aux.suceso = suceso_fallo;
		aux.tiempo = reloj + generafallo();
		insertar_lsuc(aux);
		if (radares == total_radares)
			tiempo_desprotegido += reloj - inicio;
	}
	else
		disponibles++;
}

//Procedimiento fallo (de un radar)
void fallo()
{
	Nodo aux;
	if (disponibles > 0)
	{
		disponibles --;
		aux.suceso = suceso_fallo;
		aux.tiempo = reloj+generafallo();
		insertar_lsuc(aux);
	}
	else
	{
		if (radares == total_radares)
			inicio = reloj;
		radares --;
		veces += 1;
	}
	aux.suceso = suceso_llegada;
	aux.tiempo = reloj + generareparacion();
	insertar_lsuc(aux);
}

//Procedimiento fin (equivale al generador de informes)
void fin()
{
	parar = true;
	if (radares < total_radares)
		tiempo_desprotegido += reloj-inicio;
	//calculo los resultados de esta simulacion y acumulo, para el posterior calculo de medias y desviaciones tipicas
	media_veces += veces;
	media_veces2 += veces*veces;
	media_tiempo_desprotegido += tiempo_desprotegido;
	media_tiempo_desprotegido2 += tiempo_desprotegido*tiempo_desprotegido;
	porcentaje_desproteccion = 100.0*tiempo_desprotegido/tiempo_total;
	media_porcentaje_desproteccion += porcentaje_desproteccion;
	media_porcentaje_desproteccion2 += porcentaje_desproteccion*porcentaje_desproteccion;
}

float generafallo()
{
	float u;
	u = (float) random();
	u = u/(float)(RAND_MAX+1.0); //RAND_MAX es una constante del sistema
	u = (-tfallo*log(1-u));
	return u;
}

float generareparacion()
{
	float u;
	u = (float) random();
	u = u/(float)(RAND_MAX+1.0); //RAND_MAX es una constante del sistema
	return (vmin+(vmax-vmin)*u);
}
