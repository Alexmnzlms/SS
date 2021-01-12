#!/bin/sh

cd ..
make -B
cd script

data=../data
bin=../bin
params=../params
a=0.001
b=0.125
I=500
S=500
R=0
dt=0.1
tinic=0
tfin=60

echo "${bin}/simulacion_enfermedad_exe ${a} ${b} ${I} ${S} ${R} ${dt} ${tinic} ${tfin} -o ${data}/salida_data"
$bin/simulacion_enfermedad_exe $a $b $I $S $R $dt $tinic $tfin -o $data/salida_data

python suma.py $data/salida_data

gnuplot salida.gp
gnuplot suma.gp


mv ISR.png "../memoria/img/apartado5/ISR_7.png"
mv ISR_acumulado.png "../memoria/img/apartado5/ISR_acumulado_7.png"

I=1
S=499
R=500

echo "${bin}/simulacion_enfermedad_exe ${a} ${b} ${I} ${S} ${R} ${dt} ${tinic} ${tfin} -o ${data}/salida_data"
$bin/simulacion_enfermedad_exe $a $b $I $S $R $dt $tinic $tfin -o $data/salida_data

python suma.py $data/salida_data

gnuplot salida.gp
gnuplot suma.gp

mv ISR.png "../memoria/img/apartado5/ISR_8.png"
mv ISR_acumulado.png "../memoria/img/apartado5/ISR_acumulado_8.png"
