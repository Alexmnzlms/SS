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

fichero="../datos/aparcamiento_${num_veces}_${objetivo}_${vision}_${prob_ocupado}.data"

touch $fichero


if [ ! -e ../bin/aparcamiento ]; then
	printf "Compilando binario\n"
	cd .. && make bin/aparcamiento
	cd scripts
fi

output=$(../bin/aparcamiento $num_veces $objetivo $vision $prob_ocupado | grep -e inicial:\ \(\[0-9\]\*\) -e media\ \[0-9\.\]\* -e desv.tipica\ \[0-9\.\]\* -o)

printf "# Pos. I.\tMedia\tDesv. tipica\n" > $fichero


for i in {0..100}; do

	unica_linea=$(echo $output | grep -e inicial:\ \($i\)\ media\ \[0-9\.\]\*\ desv.tipica\ \[0-9\.\]\* -o)

	printf "$i\t" >> $fichero
	awk '{print $4,"\t",$6}' <<< $unica_linea >> $fichero

done
