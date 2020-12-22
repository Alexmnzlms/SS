#!/bin/sh

cd ..
make apartado2
cd script

bin=../bin
data=../data

for sim in 1 5 10 25 50 100 500; do
	for mod in 0 3 4; do
		echo -n "" > "${data}/puerto_${mod}_${sim}_data"
		echo -n "" > "${data}/puerto_${mod}_confianza_data"
	done
done
echo -n "" > $data/comparacion_sistemas_data

for sim in 1 5 10 25 50 100 500; do
	echo "Ejecutando con ${sim} simulaciones..."
	for vez in $(seq 1 100); do
		echo "Iteración: ${vez}"
		for mod in 0 3 4; do
			$bin/puerto_exe $sim $mod | grep "llegadas:" | grep -o "[0-9]\+\.[0-9]\+" | head -1 >> "${data}/puerto_${mod}_${sim}_data"
		done
	done
done


for sim in 1 5 10 25 50 100 500; do
	for mod in 3 4; do
		echo "Comparando 0 con ${mod} con ${sim} simulaciones"
		$bin/compara_sistemas_exe "${data}/puerto_0_${sim}_data" "${data}/puerto_${mod}_${sim}_data" >> $data/comparacion_sistemas_data
	done
done

for i in $(seq 0 99); do
	echo "Iteracion ${i}"
	for mod in 0 3 4; do
		$bin/puerto_exe 1 $mod | grep "llegadas:" | grep -o "[0-9]\+\.[0-9]\+" | head -1 >> "${data}/puerto_${mod}_confianza_data"
	done
	sleep 1
done


for mod in 0 3 4; do
	$bin/intervalos_de_confianza_exe "${data}/puerto_${mod}_confianza_data" >> "${data}/intervalo_confianza_${mod}_data"
done
