#!/bin/sh

cd ..
make -B
cd script

data=../data
bin=../bin
params=../params
a=0.001
b=0.125
I=1
S=999
R=0
tinic=1
tfin=100

cont=9
for dt in 0.1 0.05 0.001 4; do

	echo "${bin}/simulacion_enfermedad_exe ${a} ${b} ${I} ${S} ${R} ${dt} ${tinic} ${tfin} -o ${data}/salida_data"
	$bin/simulacion_enfermedad_exe $a $b $I $S $R $dt $tinic $tfin -o $data/salida_data

	gnuplot salida.gp

	mv ISR.png "../memoria/img/ISR_${cont}.png"

	echo "${bin}/simulacion_enfermedad_exe ${a} ${b} ${I} ${S} ${R} ${dt} ${tinic} ${tfin} -e -o ${data}/salida_data"
	$bin/simulacion_enfermedad_exe $a $b $I $S $R $dt $tinic $tfin -e -o $data/salida_data

	gnuplot salida.gp

	mv ISR.png "../memoria/img/ISR_${cont}_e.png"

	((cont = cont + 1))
done
