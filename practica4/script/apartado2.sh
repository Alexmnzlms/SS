#!/bin/sh

cd ..
make -B
cd script

data=../data
bin=../bin
params=../params
a=0.001
b=0.125
I=10
S=90
R=0
dt=0.1
tinic=0
tfin=30

for i in $(seq 1 2); do

	echo "${bin}/simulacion_enfermedad_exe ${a} ${b} ${I} ${S} ${R} ${dt} ${tinic} ${tfin}-o ${data}/salida_data"
	$bin/simulacion_enfermedad_exe $a $b $I $S $R $dt $tinic $tfin -o $data/salida_data

	gnuplot salida.gp

	mv ISR.png "../memoria/img/ISR_${i}.png"

	((S  = S + 100))
done

a=0.0001
b=0.05
I=100
S=200
R=0

for i in $(seq 3 4); do

	echo "${bin}/simulacion_enfermedad_exe ${a} ${b} ${I} ${S} ${R} ${dt} ${tinic} ${tfin}-o ${data}/salida_data"
	$bin/simulacion_enfermedad_exe $a $b $I $S $R $dt $tinic $tfin -o $data/salida_data

	gnuplot salida.gp

	mv ISR.png "../memoria/img/ISR_${i}.png"

	((S  = S + 600))
done
