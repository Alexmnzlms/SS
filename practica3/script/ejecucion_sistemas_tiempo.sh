#!/bin/sh

cd ..
make -B apartado1
cd script

data=../data
bin=../bin

trepar=2
tfallo=1
tparar=100
repuesto=0
max=10000

#$bin/sistema_teorico_exe $tfallo $trepar $tparar $max > $data/sistema-teorico_data
#$bin/sistema_tiempo_fijo_exe $repuesto $tfallo $trepar $tparar $max > $data/sistema-t-fijo_data
#$bin/sistema_tiempo_variable_exe $repuesto $tfallo $trepar $tparar $max > $data/sistema-t-variable_data

for i in $(seq 1 4); do
	if [ $i == 2 ]; then
		u=horas
		((trepar_u = trepar * 24))
		((tfallo_u = tfallo * 24))
		((tparar_u = tparar * 24))
	elif [ $i == 3 ]; then
		u=minutos
		((trepar_u = trepar * 24 * 60))
		((tfallo_u = tfallo * 24 * 60))
		((tparar_u = tparar * 24 * 60))
	elif [ $i == 4 ]; then
		u=segundos
		((trepar_u = trepar * 24 * 3600))
		((tfallo_u = tfallo * 24 * 3600))
		((tparar_u = tparar * 24 * 3600))
	else
		u=dias
		((trepar_u = trepar))
		((tfallo_u = tfallo))
		((tparar_u = tparar))
	fi
	echo "${i} ${u} ${trepar_u} ${tfallo_u} ${tparar_u}"
	$bin/sistema_teorico_exe $tfallo_u $trepar_u $tparar_u $max > "${data}/sistema-teorico-${u}_data"
	$bin/sistema_tiempo_fijo_exe $repuesto $tfallo_u $trepar_u $tparar_u $max > "${data}/sistema-t-fijo-${u}_data"
	$bin/sistema_tiempo_variable_exe $repuesto $tfallo_u $trepar_u $tparar_u $max > "${data}/sistema-t-variable-${u}_data"
done

echo "Generando graficos..."

gnuplot precision.gp
