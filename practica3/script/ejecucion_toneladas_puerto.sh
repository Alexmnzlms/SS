#!/bin/sh

cd ..
make apartado2
cd script

bin=../bin
data=../data
n_sim=10000

rm $data/carga_total_data

for mod in $(seq 0 4); do
	echo "Ejecutando ${n_sim} simulaciones con la modificacion ${mod}..."
	echo -n "Modificacion ${mod} -> " >> "${data}/carga_total_data"
	$bin/puerto_exe $n_sim $mod | grep "Carga total:" >> "${data}/carga_total_data"
done
