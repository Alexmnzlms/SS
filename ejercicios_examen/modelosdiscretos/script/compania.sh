#!/bin/sh

bin="../bin"

cd ..
make
cd script

simul=500000

echo -n "" > compania_data

for mod in $(seq 0 2); do
	echo "Simulando modificacion: ${mod}"
	$bin/simulacion_compania_exe $simul $mod >> compania_data
	echo "-----------------------------------------------------" >> compania_data
done
