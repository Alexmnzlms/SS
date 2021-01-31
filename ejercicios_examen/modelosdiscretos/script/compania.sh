#!/bin/sh

bin="../bin"

cd ..
make
cd script

simul=100000

for mod in $(seq 0 2); do
	echo -n "" > "compania_${mod}_data"
done

for mod in $(seq 0 2); do
	echo "Simulando modificacion: ${mod}"
	echo ${bin}/simulacion_compania_exe ${simul} ${mod}
	$bin/simulacion_compania_exe $simul $mod >> "compania_${mod}_data" &
done

wait
