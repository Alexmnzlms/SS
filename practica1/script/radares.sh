#!/bin/sh


for num_simuls in 1 5 10 50 100 500 1000; do
	fichero="../datos/radares_${num_simuls}.dat"
	touch $fichero
	printf "# Num. repuestos \t Num. simulaciones \t Media fallos \t Media t desproteccion \t Media \% desproteccion \t Desv. num fallos \t Desv. t desproteccion \t Desv. \% desproteccion\n" > $fichero
	for num_repuestos in {0..25}; do
		./ejecucion_radar.sh $num_repuestos $num_simuls >> $fichero
	done
done
