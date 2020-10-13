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

fichero="../data/aparcamiento_${num_veces}_${objetivo}_${vision}_${prob_ocupado}.data"

touch $fichero


if [ ! -e ../bin/aparcamiento_exe ]; then
	printf "Compilando binario\n"
	cd .. && make bin/aparcamiento_exe
	cd scripts
fi

#output=$(../bin/aparcamiento_exe $num_veces $objetivo $vision $prob_ocupado | grep -e inicial:\ \(\[0-9\]\*\) -e media\ \[0-9\.\]\* -e desv.tipica\ \[0-9\.\]\* -o)

output=$(../bin/aparcamiento_exe $num_veces $objetivo $vision $prob_ocupado | grep -e inicial:\ \(\[0-9\]\*\) -e media\ \[0-9\.\]\* -o)

#../bin/aparcamiento_exe $num_veces $objetivo $vision $prob_ocupado

#echo $output

printf "# Pos. I.\tMedia\tDesv. tipica\n" > $fichero

printf "" > $fichero

for i in $(seq 0 $objetivo); do

#	unica_linea=$(echo $output | grep -e inicial:\ \($i\)\ media\ \[0-9\.\]\*\ desv.tipica\ \[0-9\.\]\* -o)

	unica_linea=$(echo $output | grep -e inicial:\ \($i\)\ media\ \[0-9\.\]\* -o)

#	echo $unica_linea
#	echo \n

	printf "$i\t" >> $fichero
	awk '{print $4}' <<< $unica_linea >> $fichero

done

awk 'END { print min} { min || min = $2; s || s = NR; if ($2 < min) {min=$2; s=NR} }' <<< cat $fichero > "../data/out/min_${num_veces}_${objetivo}_${vision}_${prob_ocupado}"

awk 'END { print s} { min || min = $2; s || s = NR; if ($2 < min) {min=$2; s=NR} }' <<< cat $fichero > "../data/out/min_linea_${num_veces}_${objetivo}_${vision}_${prob_ocupado}"
