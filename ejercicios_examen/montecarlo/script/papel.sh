#!/bin/sh

bin="../bin"

cd ..
make
cd script

simul=100000
total=30

echo -n "" > demanda_data

echo "Simulando 1000000 años..."
$bin/simulacion_papel_exe 1000000 1 3 > contenedores_data

for obtenido in $(seq 10 1 $total); do
	echo "Simulando con rendimiento ${obtenido}/${total}"
	simulacion=$($bin/simulacion_papel_exe $simul $obtenido $total | grep -e "Demanda")
	echo $simulacion
	demanda=$(echo "${simulacion}" | awk '{print $9}')
	echo "${obtenido} ${demanda}" >> demanda_data
done

gnuplot papel.gp
