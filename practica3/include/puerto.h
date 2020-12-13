#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <list>

using namespace std;

#define SUCESO_LLEGADA_BARCO 0
#define SUCESO_FIN_ATRAQUE 1
#define SUCESO_FIN_CARGA 2
#define SUCESO_FIN_DESATRAQUE 3
#define SUCESO_FIN_VIAJE_AT_BO 4
#define SUCESO_FIN_VIAJE_BO_AT 5
#define SUCESO_COMIENZO_TORMENTA 6
#define SUCESO_FIN_TORMENTA 7
#define SUCESO_FIN_SIMULACION 8

#define LIBRE 9
#define OCUPADO 10

/* Variables de estado */
typedef struct {
	int tipo;
	float tiempo;
} registro;

typedef struct {
	int suceso;
	float tiempo;
	registro reg_cola;
} suc;

float reloj;
bool tormenta;
int remolcador;
int atraques_libres;
int encola_lleg;
list<registro>	cola_llegadas;
int encola_sal;
list<registro> cola_salidas;
float tdus_at;
float tdus_lleg;
float tdus_sal;
float tdus_rem;
list<suc> lsuc;
bool parar;
suc nodo;
registro reg_cola_null;
registro reg_cola;

/* Contadores estadisticos */
float acum_lleg;
float acum_sal;
float acum_estancia[3];
int num_barcos[3];
float acum_rem_amarrado;
float acum_rem_viajando;
float acum_rem_remolcando;
float acum_at_desocupado;
float acum_at_cargando;
float acum_at_yacargado;
float **informe;
int cont_simu;

/* Parametros de entrada */
int remolcadores = 1;
int num_atraques = 3;
float tllegmin = 4.0;
float tllegmax = 18.0;
float tviajevacio = 0.25;
float tviajellenomin = 0.75;
float tviajellenomax = 1.25;
float dur_tormentamin = 2.0;
float dur_tormentamax = 6.0;
float tentre_tormentas = 48.0;
int num_tiposbarco = 3;
float frec1 = 0.25;
float frec2 = 0.25;
float frec3 = 0.50;
float tiempo_carga1min = 16.0;
float tiempo_carga2min = 21.0;
float tiempo_carga3min = 32.0;
float tiempo_carga1max = 20.0;
float tiempo_carga2max = 27.0;
float tiempo_carga3max = 40.0;
float tparada = 8760.0;

/* Funciones y procedimientos */
void inicializacion();
void temporizacion();
void suceso();
void llegada_barco();
void fin_viaje_at_bo();
void fin_atraque();
void fin_carga();
void fin_desatraque();
void fin_viaje_bo_at();
void comienzo_tormenta();
void fin_tormenta();
void fin_simulacion();
float genera_barco(float tllegmin, float tllegmax);
int genera_tipobarco();
float genera_tormenta(float tentre_tormentas);
float genera_durtormenta(float dur_tormentamin, float dur_tormentamax);
float genera_viajelleno(float tviajellenomin, float tviajellenomax);
float genera_tiempocarga(int tipo);
float generador_uniforme(float min, float max);
float generador_exponencial(float media);
int generador_discreto();
bool compare(const suc &s1, const suc &s2);
void insertar_lsuc(suc n);
bool busca_suceso(int tipo);
void generador_informes(int simulaciones);







