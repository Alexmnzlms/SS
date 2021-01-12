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
dt=0.1
tinic=0
tfin=60

echo "${bin}/simulacion_enfermedad_exe ${a} ${b} ${I} ${S} ${R} ${dt} ${tinic} ${tfin} -o ${data}/salida_data"
$bin/simulacion_enfermedad_exe $a $b $I $S $R $dt $tinic $tfin -o $data/salida_data

python suma.py $data/salida_data

gnuplot salida.gp
gnuplot suma.gp


mv ISR.png "../memoria/img/apartado4/ISR_5.png"
mv ISR_acumulado.png "../memoria/img/apartado4/ISR_acumulado_5.png"

a=0.0005
b=0.25

echo "${bin}/simulacion_enfermedad_exe ${a} ${b} ${I} ${S} ${R} ${dt} ${tinic} ${tfin} -o ${data}/salida_data"
$bin/simulacion_enfermedad_exe $a $b $I $S $R $dt $tinic $tfin -o $data/salida_data

python suma.py $data/salida_data

gnuplot salida.gp
gnuplot suma.gp

mv ISR.png "../memoria/img/apartado4/ISR_6.png"
mv ISR_acumulado.png "../memoria/img/apartado4/ISR_acumulado_6.png"
