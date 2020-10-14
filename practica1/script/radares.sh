#!/bin/sh


for num_simuls in 1 5 10 50 100 500 1000; do
	fichero="../data/radares_${num_simuls}.csv"
	touch $fichero
	printf "Num. repuestos,Num. simulaciones,Media fallos,Media t desproteccion,Media %% desproteccion,Desv. num fallos,Desv. t desproteccion,Desv %% desproteccion\n" > $fichero
	for num_repuestos in {0..25}; do
		./ejecucion_radar.sh $num_repuestos $num_simuls >> $fichero
	done
	echo -n "" > "../data/radares_${num_simuls}_tiempo.data"
	echo -n "" > "../data/radares_${num_simuls}_prob.data"
done

for i in 1 5 10 50 100 500 1000; do
	for j in {0..25}; do
		echo -n "${j} " >> "../data/radares_${i}_tiempo.data"
		echo -n "${j} " >> "../data/radares_${i}_prob.data"
		linea=$(cat "../data/radares_${i}.csv" | grep -e ^$j, )
		awk 'BEGIN{FS=","; OFS=" "}{print $4}' <<< $linea >> "../data/radares_${i}_tiempo.data"
		awk 'BEGIN{FS=","; OFS=" "}{print $5}' <<< $linea >> "../data/radares_${i}_prob.data"
	done
done

for i in $(seq 0 15 45); do
	inc=15
	sig=$(($i + $inc))

	for j in $(seq 0 20 60); do
		./ejecucion_radar.sh 5 5 $i $sig $j 365 1000 >> "../data/radares_1000_${i}_${sig}_${j}.data"
	done
done

gnuplot radares.gp
