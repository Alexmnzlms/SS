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

	for j in $(seq 20 20 60); do
		echo -n "" > "../data/radares_${i}_${sig}_${j}_prob.data"
		echo -n "" > "../data/radares_${i}_${sig}_${j}_tiempo.data"
		echo -n "" > "../data/radares_${i}_${sig}_${j}.data"
	done
done

for n in {0..25}; do
	for i in $(seq 0 15 45); do
		inc=15
		sig=$(($i + $inc))

		for j in $(seq 20 20 60); do
			./ejecucion_radar.sh 5 $n $i $sig $j 365 500 >> "../data/radares_${i}_${sig}_${j}.data"
			linea=$(cat "../data/radares_${i}_${sig}_${j}.data" | grep -e ^$n, )
			echo $linea
			echo -n "${n} " >> "../data/radares_${i}_${sig}_${j}_prob.data"
			echo -n "${n} " >> "../data/radares_${i}_${sig}_${j}_tiempo.data"
			awk 'BEGIN{FS=","; OFS=" "}{print $5}' <<< $linea >> "../data/radares_${i}_${sig}_${j}_prob.data"
			awk 'BEGIN{FS=","; OFS=" "}{print $4}' <<< $linea >> "../data/radares_${i}_${sig}_${j}_tiempo.data"
		done
	done
done

tabla="../data/radares_tabla_multiple.csv"
echo -n "Numero de repuestos," > $tabla

for i in $(seq 0 15 45); do
	inc=15
	sig=$(($i + $inc))
	for j in $(seq 20 20 60); do
		echo -n "Tiempo de fallo para tiempo de reparacion de: ${i}-${sig} dias y vida util de: ${j} dias," >> $tabla
		echo -n "Probabilidad de fallo para tiempo de reparacion de: ${i}-${sig} dias y vida util de: ${j} dias," >> $tabla
	done
done
for n in {0..25}; do
	echo -n "${n}," >> $tabla
	for i in $(seq 0 15 45); do
		inc=15
		sig=$(($i + $inc))

		for j in $(seq 20 20 60); do
			tiempo=$(cat "../data/radares_${i}_${sig}_${j}_tiempo.data" | grep -e ^$n\ )
			prob=$(cat "../data/radares_${i}_${sig}_${j}_prob.data" | grep -e ^$n\ )
			awk '{printf "%f,", $2}' <<< $tiempo >> $tabla
			awk '{printf "%f,", $2}' <<< $prob >> $tabla
		done
	done
	echo "" >> $tabla
done

gnuplot radares.gp

rm -f ../data/*.data
