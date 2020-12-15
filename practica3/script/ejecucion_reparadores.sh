#!/bin/sh

if [ $# != 2 ]; then
	echo "Numero incorrecto de parametros"
	echo "Necesito m (numero de trabajadores) y x (tiempo de reparación)"
	exit
fi

cd ..
make -B apartado2
cd script

m=$1
x=$2
((x_m = x / m))
((m_2 = m / 2))
((x_2 = x / 2))
totalMaq=10
maqRepuesto=5
tfallo=4
tparada=365
iter=1000

echo "Parametros m=${m} x=${x} x_m=${x_m} m_2=${m_2} x_2=${x_2}"

bin=../bin
data=../data

echo "Eliminando datos anteriores..."
rm $data/reparadores*

echo "${bin}/reparadores_exe ${totalMaq} ${maqRepuesto} ${m} ${x} ${tfallo} ${tparada} ${iter}"
$bin/reparadores_exe $totalMaq $maqRepuesto $m $x $tfallo $tparada $iter >> "${data}/reparadores_${m}_${x}_data"
echo "${bin}/reparadores_exe ${totalMaq} ${maqRepuesto} 1 ${x_m} ${tfallo} ${tparada} ${iter}"
$bin/reparadores_exe $totalMaq $maqRepuesto 1 $x_m $tfallo $tparada $iter >> "${data}/reparadores_1_${x_m}_data"
echo "${bin}/reparadores_exe ${totalMaq} ${maqRepuesto} ${m_2} ${x_2} ${tfallo} ${tparada} ${iter}"
$bin/reparadores_exe $totalMaq $maqRepuesto $m_2 $x_2 $tfallo $tparada $iter >> "${data}/reparadores_${m_2}_${x_2}_data"


echo "${bin}/separa_datos_exe ${data}/reparadores_${m}_${x}_data"
$bin/separa_datos_exe "${data}/reparadores_${m}_${x}_data"
echo "${bin}/separa_datos_exe ${data}/reparadores_1_${x_m}_data"
$bin/separa_datos_exe "${data}/reparadores_1_${x_m}_data"
echo "${bin}/separa_datos_exe ${data}/reparadores_${m_2}_${x_2}_data"
$bin/separa_datos_exe "${data}/reparadores_${m_2}_${x_2}_data"



