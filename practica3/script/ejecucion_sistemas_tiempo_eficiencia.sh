#!/bin/sh

data=../data
bin=../bin

cd ..
make apartado1
cd script

if [ $# != 3 ]; then
	echo "Número incorrecto de parametros"
	echo "Necesito repuesto tfallo trepar tparar max"
	repuesto=0
	tfallo=1
	trepar=2
	tparar=10000000
	max=1
	efi=1
	echo "Utilizando por defecto repuesto=${repuesto} tfallo=${tfallo} trepar=${trepar} tparar=${tparar} max=${max}"

else
	repuesto=$1
	tfallo=$2
	trepar=$3
	tparar=10000000
	max=1
	efi=1
fi


#repuesto=1
#tfallo=2
#trepar=2
#tparar=10000000
#max=1
#efi=1

echo -n "" > "${data}/tiempos_sistema-fijo_data"
echo -n "" > "${data}/tiempos_sistema-variable_data"

echo "Ejecutando eficiencia..."
for i in $(seq 100 10000 $tparar); do
	$bin/sistema_tiempo_fijo_exe $repuesto $tfallo $trepar $i $max $efi >> "${data}/tiempos_sistema-fijo_data"
	$bin/sistema_tiempo_variable_exe $repuesto $tfallo $trepar $i $max $efi >> "${data}/tiempos_sistema-variable_data"
done

echo "Generando graficas..."

gnuplot eficiencia.gp
