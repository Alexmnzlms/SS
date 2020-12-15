#!/bin/sh

if [ $# != 5 ]; then
	echo "Número incorrecto de parametros"
	echo "Necesito repuesto tfallo trepar tparar max"
	repuesto=0
	tfallo=1
	trepar=2
	tparar=100
	max=10000
	echo "Utilizando por defecto repuesto=${repuesto} tfallo=${tfallo} trepar=${trepar} tparar=${tparar} max=${max}"

else
	repuesto=$1
	tfallo=$2
	trepar=$3
	tparar=$4
	max=$5
fi

cd ..
make -B apartado1
cd script

data=../data
bin=../bin


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
	echo "${i} ${u} tfallo=${tfallo_u} trepar=${trepar_u} tparar=${tparar_u} max=${max}"
	$bin/sistema_teorico_exe $tfallo_u $trepar_u $tparar_u $max > "${data}/sistema-teorico-${u}_data"
	$bin/sistema_tiempo_fijo_exe $repuesto $tfallo_u $trepar_u $tparar_u $max > "${data}/sistema-t-fijo-${u}_data"
	$bin/sistema_tiempo_variable_exe $repuesto $tfallo_u $trepar_u $tparar_u $max > "${data}/sistema-t-variable-${u}_data"
done

echo "Generando graficos..."

gnuplot precision.gp
