#include "puerto.h"


bool compare(const suc &s1, const suc &s2)
{ return s1.tiempo < s2.tiempo; }


/* Inserta de forma ordenada un elemento en la lista de sucesos */
void insertar_lsuc(suc n)
{
  lsuc.push_back(n);

  // Mantener ordenada la lista por el tiempo de los sucesos
  lsuc.sort(compare);
}


/* Busca un suceso y lo extrae si existe */
bool busca_suceso(int tipo)
{
  int encontrado = false;
  list<suc>::iterator itr;

  for(itr=lsuc.begin(); itr!=lsuc.end() && encontrado==false; )
  	{
	if(((suc)(*itr)).suceso == tipo)
		{
		encontrado = true;
		nodo = *itr; 
		itr = lsuc.erase(itr);
		}
	else itr++;
	}
  return encontrado;
}


/* Procedimiento inicializacion */
void inicializacion()
{
  int i;

  // inicializacion de variables de estado
  reloj = 0.0;
  tormenta = false;
  remolcador = LIBRE;
  atraques_libres = num_atraques;
  encola_lleg = 0;
  while(!cola_llegadas.empty()) {cola_llegadas.pop_front();}
  encola_sal = 0;
  while(!cola_salidas.empty()) {cola_salidas.pop_front();}
  tdus_at = 0.0;
  tdus_lleg = 0.0;
  tdus_sal = 0.0;
  tdus_rem = 0.0;

  // inicializacion de contadores estad�ticos
  acum_lleg = 0.0;
  acum_sal = 0.0;
  for (i=0; i<num_tiposbarco; i++)
     {
     acum_estancia[i] = 0.0;
     num_barcos[i] = 0;
     }
  acum_rem_amarrado = 0.0;
  acum_rem_viajando = 0.0;
  acum_rem_remolcando = 0.0;
  acum_at_desocupado = 0.0;
  acum_at_cargando = 0.0;
  acum_at_yacargado = 0.0;

  // inicializacion de la lista de sucesos
  while(!lsuc.empty()) {lsuc.pop_front();}
  reg_cola_null.tiempo = 0.0;
  reg_cola_null.tipo = num_tiposbarco;//para rellenar los datos intiles de lsuc
  nodo.reg_cola = reg_cola_null;
  nodo.suceso = SUCESO_FIN_SIMULACION;
  nodo.tiempo = reloj+tparada;
  insertar_lsuc(nodo);
  nodo.suceso = SUCESO_LLEGADA_BARCO;
  nodo.tiempo = reloj+genera_barco(tllegmin,tllegmax);
  insertar_lsuc(nodo);
  nodo.suceso = SUCESO_COMIENZO_TORMENTA;
  nodo.tiempo = reloj+genera_tormenta(tentre_tormentas);
  insertar_lsuc(nodo);

  parar=false;
}


/* Procedimiento temporizacion */
void temporizacion()
{
  nodo = lsuc.front();
  lsuc.pop_front();
  reloj = nodo.tiempo;
}


/* Procedimiento suceso */
void suceso()
{
  switch(nodo.suceso)
  	{
	case SUCESO_LLEGADA_BARCO: llegada_barco(); break;
	case SUCESO_FIN_ATRAQUE: fin_atraque(); break;
	case SUCESO_FIN_CARGA: fin_carga(); break;
	case SUCESO_FIN_DESATRAQUE: fin_desatraque(); break;
	case SUCESO_FIN_VIAJE_AT_BO: fin_viaje_at_bo(); break;
	case SUCESO_FIN_VIAJE_BO_AT: fin_viaje_bo_at(); break;
	case SUCESO_COMIENZO_TORMENTA: comienzo_tormenta(); break;
	case SUCESO_FIN_TORMENTA: fin_tormenta(); break;
	case SUCESO_FIN_SIMULACION: fin_simulacion(); break;
	}
}


/* Peocedimiento llegada barco */
void llegada_barco()
{
  int tipobarco;
  
  nodo.suceso = SUCESO_LLEGADA_BARCO;
  nodo.tiempo = reloj+genera_barco(tllegmin,tllegmax);
  nodo.reg_cola = reg_cola_null;
  insertar_lsuc(nodo); //programa la prxima llegada
  acum_lleg += (reloj-tdus_lleg)*encola_lleg;
  tdus_lleg = reloj;
  encola_lleg ++;
  tipobarco = genera_tipobarco(); //determina qu�tipo de barco acaba de llegar;
  reg_cola.tiempo = reloj;
  reg_cola.tipo = tipobarco;
  cola_llegadas.push_back(reg_cola);
  if ((tormenta == false) && (remolcador == LIBRE) && (atraques_libres > 0))
    //el remolcador va por el barco
    {
    acum_rem_amarrado += reloj-tdus_rem;
    tdus_rem = reloj;
    remolcador = OCUPADO;
    nodo.suceso = SUCESO_FIN_VIAJE_AT_BO;
    nodo.tiempo = reloj+tviajevacio;
    nodo.reg_cola = reg_cola_null;
    insertar_lsuc(nodo); //programa la llegada del remolcador a la bocana
    }
}


/* Procedimiento fin_viaje_at_bo */
void fin_viaje_at_bo()
{
  acum_rem_viajando += reloj-tdus_rem;
  tdus_rem = reloj;
  acum_lleg += (reloj-tdus_lleg)*encola_lleg;
  tdus_lleg = reloj;
  encola_lleg --;
  reg_cola = cola_llegadas.front();
  cola_llegadas.pop_front();
  nodo.suceso = SUCESO_FIN_ATRAQUE;
  nodo.tiempo = reloj+genera_viajelleno(tviajellenomin,tviajellenomax);
  nodo.reg_cola = reg_cola;
  insertar_lsuc(nodo); //programa la llegada del remolcador a los puntos de atraque con un barco
}


/* Procedimiento fin de atraque */
void fin_atraque()
{
  acum_rem_remolcando += reloj-tdus_rem;
  tdus_rem = reloj;
  acum_at_desocupado += (reloj-tdus_at)*atraques_libres;
  acum_at_yacargado += (reloj-tdus_at)*encola_sal;
  acum_at_cargando += (reloj-tdus_at)*(num_atraques-atraques_libres-encola_sal);
  tdus_at = reloj;
  atraques_libres --;
  nodo.suceso = SUCESO_FIN_CARGA;
  nodo.tiempo = reloj+genera_tiempocarga(nodo.reg_cola.tipo);
  insertar_lsuc(nodo); //programa la finalizacin de la operacion de carga
  if (tormenta == false)
     if (encola_sal > 0) //se desatracar�un barco
        {
        acum_sal += (reloj-tdus_sal)*encola_sal;
        tdus_sal = reloj;
        encola_sal --;
        atraques_libres ++;
        reg_cola = cola_salidas.front();
	cola_salidas.pop_front();
        nodo.suceso = SUCESO_FIN_DESATRAQUE;
        nodo.tiempo = reloj+genera_viajelleno(tviajellenomin,tviajellenomax);
        nodo.reg_cola = reg_cola;
        insertar_lsuc(nodo);
        }
     else if ((atraques_libres > 0) && (encola_lleg > 0))
             { //el remolcador va por un barco a la bocana
             nodo.suceso = SUCESO_FIN_VIAJE_AT_BO;
             nodo.tiempo = reloj+tviajevacio;
             nodo.reg_cola = reg_cola_null;
             insertar_lsuc(nodo);
             }
          else remolcador = LIBRE;
  else remolcador = LIBRE;
}


/* Procedimiento fin de carga */
void fin_carga()
{
  acum_sal += (reloj-tdus_sal)*encola_sal;
  tdus_sal = reloj;
  acum_at_desocupado += (reloj-tdus_at)*atraques_libres;
  acum_at_yacargado += (reloj-tdus_at)*encola_sal;
  acum_at_cargando += (reloj-tdus_at)*(num_atraques-atraques_libres-encola_sal);
  tdus_at = reloj;
  if ((remolcador == LIBRE) && (tormenta == false)) //comienza a desatracar el barco
     {
     acum_rem_amarrado += reloj-tdus_rem;
     tdus_rem = reloj;
     remolcador = OCUPADO;
     atraques_libres ++;
     nodo.suceso = SUCESO_FIN_DESATRAQUE;
     nodo.tiempo = reloj+genera_viajelleno(tviajellenomin,tviajellenomax);
     insertar_lsuc(nodo);
     }
  else
     {
     cola_salidas.push_back(nodo.reg_cola);
     encola_sal ++;
     }
}


/* Procedimiento fin desatraque */
void fin_desatraque()
{
  acum_rem_remolcando += reloj-tdus_rem;
  tdus_rem = reloj;
  acum_estancia[nodo.reg_cola.tipo] += reloj-nodo.reg_cola.tiempo;
  num_barcos[nodo.reg_cola.tipo] ++;
  if ((encola_lleg > 0) && (tormenta == false)) //comienza a atracar un barco
     {
     acum_lleg += (reloj-tdus_lleg)*encola_lleg;
     tdus_lleg = reloj;
     encola_lleg --;
     reg_cola = cola_llegadas.front();
     cola_llegadas.pop_front();
     nodo.suceso = SUCESO_FIN_ATRAQUE;
     nodo.tiempo = reloj+genera_viajelleno(tviajellenomin,tviajellenomax);
     nodo.reg_cola = reg_cola;
     insertar_lsuc(nodo);
     }
  else
     { //hay tormenta o no hay barcos esperando: el remolcador se vuelve a los puntos de atraque
     nodo.suceso = SUCESO_FIN_VIAJE_BO_AT;
     nodo.tiempo = reloj+tviajevacio;
     nodo.reg_cola = reg_cola_null;
     insertar_lsuc(nodo);
     }
}


/* Procedimiento fin_viaje_bo_at */
void fin_viaje_bo_at()
{
  acum_rem_viajando += reloj-tdus_rem;
  tdus_rem = reloj;
  if (tormenta == false)
     if (encola_sal > 0) //comienza a desatracar un barco
        {
        acum_sal += (reloj-tdus_sal)*encola_sal;
        tdus_sal = reloj;
        acum_at_desocupado += (reloj-tdus_at)*atraques_libres;
        acum_at_yacargado += (reloj-tdus_at)*encola_sal;
        acum_at_cargando += (reloj-tdus_at)*(num_atraques-atraques_libres-encola_sal);
        tdus_at = reloj;
        encola_sal --;
        atraques_libres ++;
        reg_cola = cola_salidas.front();
	cola_salidas.pop_front(); 
        nodo.suceso = SUCESO_FIN_DESATRAQUE;
        nodo.tiempo = reloj+genera_viajelleno(tviajellenomin,tviajellenomax);
        nodo.reg_cola = reg_cola;
        insertar_lsuc(nodo);
        }
     else if ((atraques_libres > 0) && (encola_lleg > 0))
             { //el remolcador va por un barco
             nodo.suceso = SUCESO_FIN_VIAJE_AT_BO;
             nodo.tiempo = reloj+tviajevacio;
             nodo.reg_cola = reg_cola_null;
             insertar_lsuc(nodo);
             }
          else remolcador = LIBRE;
  else remolcador = LIBRE;
}


/* Procedimiento comienzo de tormenta */
void comienzo_tormenta()
{
  float tmediavuelta;

  tormenta = true;
  nodo.suceso = SUCESO_FIN_TORMENTA;
  nodo.tiempo = reloj+genera_durtormenta(dur_tormentamin,dur_tormentamax);
  nodo.reg_cola = reg_cola_null;
  insertar_lsuc(nodo);
  //busca si existe un suceso de ese tipo, si existe lo extrae y si no devuelve null
  if (busca_suceso(SUCESO_FIN_VIAJE_AT_BO))
    {
    tmediavuelta = tviajevacio-nodo.tiempo+reloj;
    nodo.suceso = SUCESO_FIN_VIAJE_BO_AT;
    nodo.tiempo = reloj+tmediavuelta;
    nodo.reg_cola = reg_cola_null;
    insertar_lsuc(nodo);
   }
}


/* Procedimiento fin de tormenta */
void fin_tormenta()
{
  tormenta = false;
  nodo.suceso = SUCESO_COMIENZO_TORMENTA;
  nodo.tiempo = reloj+genera_tormenta(tentre_tormentas);
  nodo.reg_cola = reg_cola_null;
  insertar_lsuc(nodo);
  if (remolcador == LIBRE) //con los datos actuales esto siempre ocurrira     
    if (encola_sal > 0) //comienza a desatracar un barco
       {
        acum_sal += (reloj-tdus_sal)*encola_sal;
        tdus_sal = reloj;
        acum_at_desocupado += (reloj-tdus_at)*atraques_libres;
        acum_at_yacargado += (reloj-tdus_at)*encola_sal;
        acum_at_cargando += (reloj-tdus_at)*(num_atraques-atraques_libres-encola_sal);
        tdus_at = reloj;
        encola_sal --;
        atraques_libres ++;
        acum_rem_amarrado += reloj-tdus_rem;
        tdus_rem = reloj;
        remolcador = OCUPADO;
        reg_cola = cola_salidas.front();
	cola_salidas.pop_front();
        nodo.suceso = SUCESO_FIN_DESATRAQUE;
        nodo.tiempo = reloj+genera_viajelleno(tviajellenomin,tviajellenomax);
        nodo.reg_cola = reg_cola;
        insertar_lsuc(nodo);
       }
     else if ((atraques_libres > 0) && (encola_lleg > 0))
             { //el remolcador va por un barco
             acum_rem_amarrado += reloj-tdus_rem;
             tdus_rem = reloj;
             remolcador = OCUPADO;
             nodo.suceso = SUCESO_FIN_VIAJE_AT_BO;
             nodo.tiempo = reloj+tviajevacio;
             nodo.reg_cola = reg_cola_null;
             insertar_lsuc(nodo);
             }
}


/* Procedimiento fin de simulacion */
void fin_simulacion()
{
  int i;

  parar=true;
  acum_at_desocupado += (reloj-tdus_at)*atraques_libres;
  acum_at_yacargado += (reloj-tdus_at)*encola_sal;
  acum_at_cargando += (reloj-tdus_at)*(num_atraques-atraques_libres-encola_sal);
  acum_lleg += (reloj-tdus_lleg)*encola_lleg;
  acum_sal += (reloj-tdus_sal)*encola_sal;
  if (remolcador == LIBRE) acum_rem_amarrado += reloj-tdus_rem;
  else
     {
     if( busca_suceso(SUCESO_FIN_VIAJE_AT_BO)) acum_rem_viajando += reloj-tdus_rem;
     else
        {
        if (busca_suceso(SUCESO_FIN_VIAJE_BO_AT)) acum_rem_viajando += reloj-tdus_rem;
        else acum_rem_remolcando += reloj-tdus_rem;
        }
     }
  //printf("\nNumero medio de barcos en cola de llegadas = %f",acum_lleg/reloj);
  informe[cont_simu][0] = acum_lleg/reloj;
  //printf("\nNumero medio de barcos en cola de salidas = %f",acum_sal/reloj);
  informe[cont_simu][1] = acum_sal/reloj;
  for (i=0; i<num_tiposbarco; i++)
     informe[cont_simu][2+i] = acum_estancia[i]/num_barcos[i];
     //printf("\nTiempo medio de estancia en puerto (tipo %d) = %f",i,acum_estancia[i]/num_barcos[i]);
  //printf("\nPorcentaje de tiempo remolcador desocupado = %f",100*acum_rem_amarrado/reloj);
  informe[cont_simu][5] = 100*acum_rem_amarrado/reloj;
  //printf("\nPorcentaje de tiempo remolcador viajando vacio = %f",100*acum_rem_viajando/reloj);
  informe[cont_simu][6] = 100*acum_rem_viajando/reloj;
  //printf("\nPorcentaje de tiempo remolcador remolcando barcos = %f",100*acum_rem_remolcando/reloj);
  informe[cont_simu][7] = 100*acum_rem_remolcando/reloj;
  //printf("\nPorcentaje de tiempo puntos de atraque libres = %f",100*acum_at_desocupado/(reloj*num_atraques));
  informe[cont_simu][8] = 100*acum_at_desocupado/(reloj*num_atraques);
  //printf("\nPorcentaje de tiempo puntos de atraque ocupados sin cargar = %f",100*acum_at_yacargado/(reloj*num_atraques));
  informe[cont_simu][9] = 100*acum_at_yacargado/(reloj*num_atraques);
  //printf("\nPorcentaje de tiempo puntos de atraque ocupados cargando = %f",100*acum_at_cargando/(reloj*num_atraques));
  informe[cont_simu][10] = 100*acum_at_cargando/(reloj*num_atraques);
}


/* El generador de informes se encarga de calcular la media y desviacion tipica de los valores obtenidos */
void generador_informes(int simulaciones)
{
  float media[11], dt[11];
  int i,j;
  
  for(j=0; j<11; j++)
  	{
  	media[j] = 0;
  	for(i=0; i<simulaciones; i++)
  		media[j] += informe[i][j];
  	media[j] /= simulaciones;

  	dt[j] = 0;
  	for(i=0; i<simulaciones; i++)
		dt[j] += informe[i][j] * informe[i][j];
  	dt[j] = sqrt((dt[j]-simulaciones*media[j]*media[j]) / (simulaciones-1.0));
	}
	
  printf("\n\nINFORME ->");
  printf("\n\nNumero medio de barcos en cola de llegadas: media(%f), dt(%f)",media[0],dt[0]);
  printf("\nNumero medio de barcos en cola de salidas: media(%f), dt(%f)",media[1],dt[1]);
  for (i=0; i<num_tiposbarco; i++)
     printf("\nTiempo medio de estancia en puerto (tipo %d): media(%f), dt(%f)",i,media[2+i],dt[2+i]);
  printf("\nPorcentaje de tiempo remolcador desocupado: media(%f), dt(%f)",media[5],dt[5]);
  printf("\nPorcentaje de tiempo remolcador viajando vacio: media(%f), dt(%f)",media[6],dt[6]);
  printf("\nPorcentaje de tiempo remolcador remolcando barcos: media(%f), dt(%f)",media[7],dt[7]);
  printf("\nPorcentaje de tiempo puntos de atraque libres: media(%f), dt(%f)",media[8],dt[8]);
  printf("\nPorcentaje de tiempo puntos de atraque ocupados sin cargar: media(%f), dt(%f)",media[9],dt[9]);
  printf("\nPorcentaje de tiempo puntos de atraque ocupados cargando: media(%f), dt(%f)\n\n",media[10],dt[10]);
}


/* Generadores de datos */
// Generador de tiempos entre llegadas de barcos al puerto (uniforme)
float genera_barco(float tllegmin, float tllegmax)
{ return generador_uniforme(tllegmin, tllegmax); }

// Generador de tipos de barco (discreto)
int genera_tipobarco()
{ return generador_discreto(); }

// Generador de tormentas (tiempo entre fin de una y comienzo de otra) (exponencial)
float genera_tormenta(float tentre_tormentas)
{ return generador_exponencial(tentre_tormentas); }

// Generador de duraciones de tormentas (uniforme)
float genera_durtormenta(float dur_tormentamin, float dur_tormentamax)
{ return generador_uniforme(dur_tormentamin, dur_tormentamax); }

// Generador de tiempos de viaje del remolcador remolcando (uniforme)
float genera_viajelleno(float tviajellenomin, float tviajellenomax)
{ return generador_uniforme(tviajellenomin, tviajellenomax); }

// Generador de tiempos de carga (uniforme)
float genera_tiempocarga(int tipo)
{
  if(tipo==0) return generador_uniforme(tiempo_carga1min, tiempo_carga1max);
  else if(tipo==1) return generador_uniforme(tiempo_carga2min, tiempo_carga2max);
  else return generador_uniforme(tiempo_carga3min, tiempo_carga3max);
}


float generador_uniforme(float min, float max)
{
  float u;
  u = (float) random();
  u = (float) (u/(RAND_MAX+1.0));
  return(min+(max-min)*u);
}

float generador_exponencial(float media)
{
  float u;
  u = (float) random();
  u = (float) (u/(RAND_MAX+1.0));
  return(-media*log(1-u));
}

int generador_discreto()
{
  float u;
  u = (float) random();
  u = (float) (u/(RAND_MAX+1.0));
  if (u < frec1) return(0);
  else if (u < (frec1+frec2)) return(1);
  else return(2);
}


/* Programa principal */
int main(int argc, char *argv[])
{
  int i, simulaciones;
  
  if(argc != 2)
  	{
	printf("\n\nFormato Argumentos -> <numero_simulaciones>\n\n");
	exit(1);
	}
	
  sscanf(argv[1],"%d",&simulaciones);

  informe = (float **) malloc (simulaciones*sizeof(float *));
  for(i=0; i<simulaciones; i++)
  	informe[i] = (float *) malloc (11*sizeof(float));

  srandom(time(NULL));
  //srandom(123456);

  for(cont_simu=0; cont_simu<simulaciones; cont_simu++)
  	{
	printf("\nSimulacion %d ...",cont_simu);
  	inicializacion();
  	while(parar==false)
		{
		temporizacion();
		suceso();
		}
	}
  generador_informes(simulaciones);
	
  for(i=0; i<simulaciones; i++)
  	free(informe[i]);
  free(informe);
}
