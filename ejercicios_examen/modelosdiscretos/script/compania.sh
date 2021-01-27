#!/bin/sh

bin="../bin"

cd ..
make
cd script

simul=100000

echo -n "" > compania_data

for mod in $(seq 0 2); do
	echo "Simulando modificacion: ${mod}"
	echo ${bin}/simulacion_compania_exe ${simul} ${mod}
	$bin/simulacion_compania_exe $simul $mod #>> compania_data
	echo "-----------------------------------------------------" >> compania_data
done
