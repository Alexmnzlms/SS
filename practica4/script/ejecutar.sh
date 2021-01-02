#!/bin/sh

cd ..
make -B
cd script

data=../data
bin=../bin
params=../params

echo "${bin}/simulacion_enfermedad_exe -f ${params}/parametros -o ${data}/salida_data"
$bin/simulacion_enfermedad_exe -f $params/parametros -o $data/salida_data

python suma.py $data/salida_data
python separar_cols.py $data/salida_data

gnuplot suma.gp
gnuplot separar_cols.gp
