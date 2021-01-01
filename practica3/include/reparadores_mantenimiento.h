#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <set>
#include <algorithm>

using namespace std;

#define FALLO_MAQUINA 0
#define FIN_REPARACION 1
#define FIN_SIMULACION 2
#define MANTENIMIENTO 3
#define FIN_MANTENIMIENTO 4

typedef struct {
	int tipo;
	float tiempo;
} suc;

// Variables exogenas:
int	n;
int	s;
int	reparadores;
float trepar;
float tfallo;
int	tparada;
int	trevision;
int	tmantmin;
int	tmantmax;

// Variables de estado:
float reloj;
int	rotas;
int	repuestos;
bool	fallo;
int	libres;
int	encola;
int	enreparacion;
bool parar;
list<suc> lsuc;
float comienzofallo;
float finfalloanterior;
float tusocio;
float tusrep;
suc nodo;

// Contadores estadisticos
int	numfallos;
float durfallos;
float entrefallos;
float maqport;
float ocio;

//Varibles de iteración
int i;
int iter;

//Variables de informe
float DMF, TMEFS, NMMR, TOR, DTF;

/* Funciones y procedimientos */
void inicializacion();
// gestion de lista de sucesos
int temporizacion();
int temporizacion_maquina();
bool compare(const suc &s1, const suc &s2);
void insertar_lsuc(suc n);
void eliminar_lsuc(int t);
// sucesos
void suceso(int suc_sig);
void falloMaquina();
void finReparacion();
void mantenimiento();
void finMantenimiento();
void generadorInformes();
// generadores de datos
float generafallo(float media);
float generareparacion(float media);
float generaruniforme(float min, float max);

void print_lsuc(int n);

