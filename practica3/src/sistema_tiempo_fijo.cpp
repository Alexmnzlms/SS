
inicializar generador de números pseudoaleatorios;
reloj = 0.0;
hayrepuesto = true (si s=1) o false (si s=0);
fallo = false;
reparadorlibre = true;
maquinaesperando = false;
numfallos = 0;
durfallos = 0.0;
tiempofallomaquina = reloj + generafallo(tfallo);
tiempofinreparacion = 10e30;
while (reloj <= tiempodeparar) do {
     if (reloj == tiempofallomaquina)
       {
        if (reparadorlibre == true) {
          reparadorlibre = false;
          tiempofinreparacion = reloj + generareparacion(trepar); }
        else maquinaesperando = true;
        if (hayrepuesto == true) {
          hayrepuesto = false;
          tiempofallomaquina = reloj + generafallo(tfallo); }
        else  if (fallo == false) {
                fallo = true;
                comienzofallo = reloj;
                numfallos ++;
                tiempofallomaquina = 10e30; }
       }
     if (reloj == tiempofinreparacion)
       {
        if (maquinaesperando == true) {
          maquinaesperando = false;
          tiempofinreparacion = reloj + generareparacion(trepar); }
        else {
              reparadorlibre = true;
              tiempofinreparacion = 10e30; }
        if (fallo == false) hayrepuesto = true;
        else {
              tiempofallomaquina = reloj + generafallo(tfallo);
              durfallos += reloj - comienzofallo;
              fallo = false; }
        }
     reloj ++
   }
if (fallo == true) durfallos += reloj - comienzofallo;
printf("\nDuracion media de los fallos = %f",durfallos/numfallos);
