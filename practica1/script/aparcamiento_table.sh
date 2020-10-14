#!/bin/sh

if [ $# -eq 4 ]; then
	num_veces=$1
	objetivo=$2
	vision=$3
	prob_ocupado=$4
else
	num_veces=100000
	objetivo=100
	vision=2
	prob_ocupado=0.9

fi

printf "Utilizando los siguientes valores: \n"
printf "Número de repeticiones: $num_veces\n"
printf "Posición objetivo: $objetivo\n"
printf "Visión del conductor: $vision\n"
printf "Prob. de sitio ocupado: $prob_ocupado\n"

if [ ! -e ../bin/aparcamiento_exe ]; then
	printf "Compilando binario\n"
	cd .. && make bin/aparcamiento_exe
	cd scripts
fi

echo -n "" > ../data/aparcamiento_ejecuciones_min_tabla.csv
echo -n "" > ../data/aparcamiento_ejecuciones_min.data
echo -n "" > ../data/aparcamiento_ejecuciones_min_linea.data


for i in $(seq 0 1 9); do
	echo "Ejecucion $i"
	fichero="../data/aparcamiento_${i}_${num_veces}_${objetivo}_${vision}_${prob_ocupado}.data"

	touch $fichero

	output=$(../bin/aparcamiento_exe $num_veces $objetivo $vision $prob_ocupado | grep -e inicial:\ \(\[0-9\]\*\) -e media\ \[0-9\.\]\* -o)

	printf "# Pos. I.\tMedia\tDesv. tipica\n" > $fichero

	printf "" > $fichero

	for j in $(seq 0 $objetivo); do

		unica_linea=$(echo $output | grep -e inicial:\ \($j\)\ media\ \[0-9\.\]\* -o)

		printf "$j " >> $fichero
		awk '{print $4}' <<< $unica_linea >> $fichero

	done

	awk 'END { print min} { min || min = $2; s || s = NR; if ($2 < min) {min=$2; s=NR} }' <<< cat $fichero > "../data/out/min_${i}_${num_veces}_${objetivo}_${vision}_${prob_ocupado}"

	awk 'END { print s} { min || min = $2; s || s = NR; if ($2 < min) {min=$2; s=NR} }' <<< cat $fichero > "../data/out/min_linea_${i}_${num_veces}_${objetivo}_${vision}_${prob_ocupado}"


	echo -n "${i}," >> ../data/aparcamiento_ejecuciones_min_tabla.csv
	echo -n "${i} " >> ../data/aparcamiento_ejecuciones_min.data
	echo -n "${i} " >> ../data/aparcamiento_ejecuciones_min_linea.data
	cat "../data/out/min_${i}_100000_100_2_0.9" | tr '\n' ','>> ../data/aparcamiento_ejecuciones_min_tabla.csv
	cat "../data/out/min_${i}_100000_100_2_0.9" >> ../data/aparcamiento_ejecuciones_min.data
	cat "../data/out/min_linea_${i}_100000_100_2_0.9" >> ../data/aparcamiento_ejecuciones_min_tabla.csv
	cat "../data/out/min_linea_${i}_100000_100_2_0.9" >> ../data/aparcamiento_ejecuciones_min_linea.data

done


tabla="../data/aparcamiento_ejecuciones_tabla.csv"

touch $tabla

echo -n "," > $tabla

for i in $(seq 0 1 9); do
	echo -n "$i," >> $tabla
done

echo "" >> $tabla

for i in $(seq 0 $objetivo); do

	printf "$i," >> $tabla

	for j in $(seq 0 1 9); do

		unica=$(cat "../data/aparcamiento_${j}_${num_veces}_${objetivo}_${vision}_${prob_ocupado}.data" | grep -e ^$i\ \[0-9\.\]\* -o)
#		echo $unica
#		echo "------------------------------------------------------------------"
		awk '{printf "%f,", $2}' <<< $unica >> $tabla

	done

	printf "\n" >> $tabla

done


