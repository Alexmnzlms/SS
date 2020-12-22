#!/bin/sh
echo "Ejecutando eficiencia..."
./ejecucion_sistemas_tiempo_eficiencia.sh &

echo "Ejecutando precision..."
./ejecucion_sistemas_tiempo_precision.sh &

#wait

eitcho "Ejecutando reparadores..."
./ejecucion_reparadores.sh &

wait

echo "Ejecutando toneladas puerto..."
./ejecucion_toneladas_puerto.sh &

echo "Ejecutando comparación de sistemas..."
./ejecucion_comparacion_dos.sh &

wait
