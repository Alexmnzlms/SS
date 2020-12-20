#!/bin/sh

data=../data
bin=../bin

cd ..
make -B apartado1
cd script

repuesto=1
tfallo=2
trepar=2
tparar=10000000
max=1
efi=1

echo -n "" > "${data}/tiempos_sistema-fijo_data"
echo -n "" > "${data}/tiempos_sistema-variable_data"

for i in $(seq 100 10000 $tparar); do
	echo $i
	$bin/sistema_tiempo_fijo_exe $repuesto $tfallo $trepar $i $max $efi >> "${data}/tiempos_sistema-fijo_data"
	$bin/sistema_tiempo_variable_exe $repuesto $tfallo $trepar $i $max $efi >> "${data}/tiempos_sistema-variable_data"
done

echo "Generando graficas..."

gnuplot eficiencia.gp
