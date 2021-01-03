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
tfin=15

echo "${bin}/simulacion_enfermedad_exe ${a} ${b} ${I} ${S} ${R} ${dt} ${tinic} ${tfin}-o ${data}/salida_data"
$bin/simulacion_enfermedad_exe $a $b $I $S $R $dt $tinic $tfin -o $data/salida_data

python suma.py $data/salida_data
python separar_cols.py $data/salida_data

gnuplot suma.gp
gnuplot separar_cols.gp

mv ISR_acumulado.png "../memoria/img/ISR_acumulado.png"
mv I_S.png "../memoria/img/I_S.png"

