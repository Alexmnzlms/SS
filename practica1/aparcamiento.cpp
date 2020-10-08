
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
// #include <list>

using namespace std;

float distanciaacumulada,distancia2,distanciamedia,desvtipica;
float prob_ocupada;
long vez,j; //contadores
bool stop,plazalibre;
long posicion_inicial,posicion,destino,aparca,vision,distancia,veces;
long cuantosmepuedopasar,distanciaactual;
long distrib[2000];
long posicion_mejor;
float distancia_mejor;

bool generar_dato(){
float u;
  u = (float) random();
  u = u/(float)(RAND_MAX+1.0);
  if (u<prob_ocupada)
   return (false);
  else return (true);
}//generar_dato


/* Programa principal */
int main(int argc, char *argv[])
{
  if(argc == 1)
   {
    veces=100000;
    destino = 100;
    vision = 2;
    prob_ocupada = 0.9;
   }
  else if(argc != 5)
	{
         printf("\nFormato Argumentos -> <numero de iteraciones> <posicion de destino>  <numero de posiciones a la vista> <probabilidad de plaza ocupada>\n");
	 exit(1);
	}
       else
          {
           sscanf(argv[1],"%d",&veces);
	   sscanf(argv[2],"%d",&destino);
	   sscanf(argv[3],"%d",&vision);
	   sscanf(argv[4],"%f",&prob_ocupada);
	  }

//srandom(123456);
srandom(time(NULL));
distancia_mejor =10e30;
posicion_mejor = -1;

//posicion_inicial=80;
//veces=100000;
//destino = 100;
//vision = 2;
//prob_ocupada = 0.9;

for (posicion_inicial=0; posicion_inicial<(destino+1); posicion_inicial++) //prueba las distintas posiciones donde empezar a aparcar
{
distanciaacumulada = 0.0;
distancia2 = 0.0;
for (j=posicion_inicial; j<(2*destino); j++)
  distrib[j] = 0;
for (vez=0; vez<veces; vez++) //repite el proceso de buscar aparcamiento "veces" veces
 {
  stop = false;
  for (posicion=posicion_inicial; !stop; posicion+=(vision+1)) //si no se aparca en las posiciones posicion..posicion+vision se salta a posicion+vision+1.
   {
    if (posicion <= (destino-vision))
      for (j=0; ((!stop) && (j<(vision+1))); j++)
        {
         plazalibre = generar_dato();
         if (plazalibre) //intento aparcar lo mas cerca de destino, miro lo mas lejos posible hacia adelante
	  {
	   aparca = posicion+vision-j;
	   distancia = destino-aparca;
	   stop = true;
	  }// if
	}// for j
    else if (posicion < destino) // en ese caso es (destino-vision < posicion < destino)
                                 //veo la posicion de destino
	  {
	   plazalibre = generar_dato();
           if (plazalibre) //si está libre la plaza destino, aparco alli
	    {
	     aparca = destino;
	     distancia = 0;
	     stop = true;
	    }// if
	   else //intento aparcar lo mas cerca de destino, a izquierda y derecha
	      {
	       distanciaactual = destino-posicion; //hay ese numero de posibilidades a la izquierda de destino
	       cuantosmepuedopasar = vision-distanciaactual; //hay ese numero de posibilidades a la derecha de destino
	       if (cuantosmepuedopasar < distanciaactual) //hay mas plazas a izquierda
	        {
		 for (j=1; ((!stop)&&(j<(cuantosmepuedopasar+1))); j++)
		   {
		    plazalibre = generar_dato();
                    if (plazalibre) // aparca a la izquierda
	             {
	              aparca = destino-j;
	              distancia = j;
	              stop = true;
	             }// if
		    else
		       {
		        plazalibre = generar_dato();
                        if (plazalibre) // aparca a la derecha
	                 {
	                  aparca = destino+j;
	                  distancia = j;
	                  stop = true;
	                 }// if
		       }// else
		   }// for j
		 if (!stop) //no he aparcado, tengo que mirar las posiciones restantes a la izquierda, empezando por la mas cercana a destino
		  for (j=(cuantosmepuedopasar+1); ((!stop)&&(j<(distanciaactual+1))); j++)
		    {
		     plazalibre = generar_dato();
                     if (plazalibre) // aparca a la izquierda
	              {
	               aparca = destino-j;
	               distancia = j;
	               stop = true;
	              }// if
		    }// for j
		}// if cuantosmepuedopasar
	       else // en ese caso distanciaactual <= cuantosmepuedopasar, hay mas plazas a la derecha
	          {
	       	   for (j=1; ((!stop)&&(j<(distanciaactual+1))); j++)
		     {
		      plazalibre = generar_dato();
                      if (plazalibre) // aparca a la izquierda
	               {
	                aparca = destino-j;
	                distancia = j;
	                stop = true;
	               }// if
		      else
		         {
		          plazalibre = generar_dato();
                          if (plazalibre) // aparca a la derecha
	                   {
	                    aparca = destino+j;
	                    distancia = j;
	                    stop = true;
	                   }// if
			 }// else 
		     }// for j
		   if (!stop) //no he aparcado, tengo que mirar las posiciones restantes a la derecha, empezando por la mas cercana a destino
		    for (j=(distanciaactual+1); ((!stop)&&(j<(cuantosmepuedopasar+1))); j++)
		      {
		       plazalibre = generar_dato();
                       if (plazalibre) // aparca a la derecha
	                {
	                 aparca = destino+j;
	                 distancia = j;
	                 stop = true;
	                }// if
		      }// for j
		  }// else	
	      }// else
	  }// if posicion < destino    
         else // en ese caso es (posicion >= destino), me estoy pasando
           for (j=0; ((!stop)&&(j<(vision+1))); j++)
            {
             plazalibre = generar_dato();
             if (plazalibre) //intento aparcar lo mas cerca de destino, la posicion mas pequeña posible
	      {
	       aparca = posicion+j;
	       distancia = aparca-destino;
	       stop = true;
	      }// if
	   }// for j
   }// for posicion
  distanciaacumulada += distancia;
  distancia2 += distancia*distancia;
  distrib[aparca]++;
 }//for vez
distanciamedia = distanciaacumulada/veces;
desvtipica = sqrt((distancia2-veces*distanciamedia*distanciamedia)/(veces-1));
if (distanciamedia < distancia_mejor)
 {
  distancia_mejor = distanciamedia;
  posicion_mejor = posicion_inicial;
 }

printf("\nINFORME PARCIAL->Posicion inicial: (%d)",posicion_inicial);
//  for (j=posicion_inicial; j<(2*destino); j++)
//    if (distrib[j]!=0)
//     printf("\nVeces que aparca en cada posicion: %d %d",j,distrib[j]);
//  printf("\n");
  printf("\nDistancia al punto de destino: media %f, desv.tipica %f",distanciamedia,desvtipica);
//  printf("\nDesviacion tipica: %f",desvtipica);
}
printf("\n\nINFORME ->");
  //printf("\n");
  printf("\nNumero de veces que se repite: (%d)",veces);
  printf("\nPosicion destino: (%d)",destino);
  printf("\nAlcance: (%d)",vision);
  printf("\nProbabilidad de plaza ocupada: (%f) ",prob_ocupada);
  printf("\n\nMejor posicion inicial: %d ",posicion_mejor);
  printf("\nMejor distancia: %f ",distancia_mejor);

//  printf("\nOJO con RAND_MAX: %f %d %d",(float)RAND_MAX+1,RAND_MAX+1,RAND_MAX);
  printf("\n");
//return 0;
}
