#!/bin/sh

if [ ! -e ../bin/radares ]; then
	printf "Compilando ../bin/radares\n"
	cd ..
	make bin/radares
	cd scripts
fi

if [ $# -eq 2 ]; then
	num_repuestos=$1
	num_simulaciones=$2
elif [ $# -eq 7 ]; then
	num_radares=$1
	num_repuestos=$2
	vmin=$3
	vmax=$4
	tiempo_fallo=$5
	tiempo_fin=$6
	num_simulaciones=$7
else
	../bin/radares
	exit
fi


ejecucion=$(../bin/radares $@)


medias=$(echo $ejecucion | grep -o -e media\ \[a-z\:\ \]\*\ \[0-9\.\]\*)


media_fallos=$(echo $medias | awk '{print $10}')
media_t_desproteccion=$(echo $medias | awk '{print $17}')
media_p_desproteccion=$(echo $medias | awk '{print $26}')




desv=$(echo $ejecucion | grep -o -e desviacion\ \[a-z\:\ \]\*\ \[0-9\.\]\*)

desv_num_fallos=$(echo $desv | awk '{print $11}')
desv_t_desproteccion=$(echo $desv | awk '{print $19}')
desv_p_desproteccion=$(echo $desv | awk '{print $29}')

is_num_regex='^[+-]?[0-9]+([.][0-9]+)?$'

if ! [[ $desv_num_fallos =~ $is_num_regex ]]; then
	desv_num_fallos=0
fi

if ! [[ $desv_t_desproteccion =~ $is_num_regex ]]; then
	desv_t_desproteccion=0
fi

if ! [[ $desv_p_desproteccion =~ $is_num_regex ]]; then
	desv_p_desproteccion=0
fi

printf "$num_repuestos\t$num_simulaciones\t$media_fallos\t$media_t_desproteccion\t$media_p_desproteccion\t$desv_num_fallos\t$desv_t_desproteccion\t$desv_p_desproteccion\n"



