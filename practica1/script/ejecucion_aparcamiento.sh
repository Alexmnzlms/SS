#!/bin/sh

mkdir ../data/out

./aparcamiento_table.sh

for i in $(seq 0.1 0.1 0.9); do
	./aparcamiento.sh 100000 100 2 $i;
done

echo -n  > ../data/aparcamiento_prob_min_tabla.csv
echo -n  > ../data/aparcamiento_prob_min.data
echo -n  > ../data/aparcamiento_prob_min_linea.data
for i in $(seq 0.1 0.1 0.9); do
	echo -n "${i}," >> ../data/aparcamiento_prob_min_tabla.csv
	echo -n "${i} " >> ../data/aparcamiento_prob_min.data
	echo -n "${i} " >> ../data/aparcamiento_prob_min_linea.data
	cat "../data/out/min_100000_100_2_${i}" | tr '\n' ',' >> ../data/aparcamiento_prob_min_tabla.csv
	cat "../data/out/min_100000_100_2_${i}" >> ../data/aparcamiento_prob_min.data
	cat "../data/out/min_linea_100000_100_2_${i}" >> ../data/aparcamiento_prob_min_tabla.csv
	cat "../data/out/min_linea_100000_100_2_${i}" >> ../data/aparcamiento_prob_min_linea.data
done

tabla="../data/aparcamiento_prob_tabla.csv"

touch $tabla

echo -n "," > $tabla

for i in $(seq 0.1 0.1 0.9); do
	echo -n "$i," >> $tabla
done

echo "" >> $tabla

for i in $(seq 0 100); do

	printf "$i," >> $tabla

	for j in $(seq 0.1 0.1 0.9); do

		unica=$(cat "../data/aparcamiento_100000_100_2_${j}.data" | grep -e ^$i\ \[0-9\.\]\* -o)
#		echo $unica
#		echo "------------------------------------------------------------------"
		awk '{printf "%f,", $2}' <<< $unica >> $tabla

	done

	printf "\n" >> $tabla

done

for i in $(seq 1 1 10); do
	./aparcamiento.sh 100000 100 $i 0.9;
done

echo -n  > ../data/aparcamiento_vision_min_tabla.csv
echo -n  > ../data/aparcamiento_vision_min.data
echo -n  > ../data/aparcamiento_vision_min_linea.data
for i in $(seq 1 1 10); do
	echo -n "${i}," >> ../data/aparcamiento_vision_min_tabla.csv
	echo -n "${i} " >> ../data/aparcamiento_vision_min.data
	echo -n "${i} " >> ../data/aparcamiento_vision_min_linea.data
	cat "../data/out/min_100000_100_${i}_0.9" | tr '\n' ',' >> ../data/aparcamiento_vision_min_tabla.csv
	cat "../data/out/min_100000_100_${i}_0.9" >> ../data/aparcamiento_vision_min.data
	cat "../data/out/min_linea_100000_100_${i}_0.9" >> ../data/aparcamiento_vision_min_tabla.csv
	cat "../data/out/min_linea_100000_100_${i}_0.9" >> ../data/aparcamiento_vision_min_linea.data
done

tabla="../data/aparcamiento_vision_tabla.csv"

touch $tabla

echo -n "," > $tabla

for i in $(seq 1 1 10); do
	echo -n "$i," >> $tabla
done

echo "" >> $tabla

for i in $(seq 0 100); do

	printf "$i," >> $tabla

	for j in $(seq 1 1 10); do

		unica=$(cat "../data/aparcamiento_100000_100_${j}_0.9.data" | grep -e ^$i\ \[0-9\.\]\* -o)
#		echo $unica
#		echo "------------------------------------------------------------------"
		awk '{printf "%f,", $2}' <<< $unica >> $tabla

	done

	printf "\n" >> $tabla

done


for i in 10 100 1000 10000 100000; do
	./aparcamiento.sh $i 100 2 0.9;
done

echo -n  "" > ../data/aparcamiento_veces_min_tabla.csv
echo -n  "" > ../data/aparcamiento_veces_min.data
echo -n  "" > ../data/aparcamiento_veces_min_linea.data
for i in 10 100 1000 10000 100000; do
	echo -n "${i}," >> ../data/aparcamiento_veces_min_tabla.csv
	echo -n "${i} " >> ../data/aparcamiento_veces_min.data
	echo -n "${i} " >> ../data/aparcamiento_veces_min_linea.data
	cat "../data/out/min_${i}_100_2_0.9" >> ../data/aparcamiento_veces_min.data
	cat "../data/out/min_${i}_100_2_0.9" | tr '\n' ',' >> ../data/aparcamiento_veces_min_tabla.csv
	cat "../data/out/min_linea_${i}_100_2_0.9" >> ../data/aparcamiento_veces_min_tabla.csv
	cat "../data/out/min_linea_${i}_100_2_0.9" >> ../data/aparcamiento_veces_min_linea.data
done

tabla="../data/aparcamiento_veces_tabla.csv"

touch $tabla

echo -n "," > $tabla

for i in 10 100 1000 10000 100000; do
	echo -n "$i," >> $tabla
done

echo "" >> $tabla


for i in $(seq 0 100); do

	printf "$i," >> $tabla

	for j in 10 100 1000 10000 100000; do

		unica=$(cat "../data/aparcamiento_${j}_100_2_0.9.data" | grep -e ^$i\ \[0-9\.\]\* -o)
#		echo $unica
#		echo "------------------------------------------------------------------"
		awk '{printf "%f,", $2}' <<< $unica >> $tabla

	done

	printf "\n" >> $tabla

done

for i in $(seq 1 1 10); do
	for j in $(seq 0.1 0.1 0.9); do
		./aparcamiento.sh 100000 100 $i $j
	done
done

echo -n "" > "../data/aparcamiento_prob_vision_distancia.data"
echo -n "" > "../data/aparcamiento_prob_vision_distancia_linea.data"
for i in $(seq 1 1 10); do
	for j in $(seq 0.1 0.1 0.9); do
		echo -n "${j} ${i} " >> "../data/aparcamiento_prob_vision_distancia.data"
		echo -n "${j} ${i} " >> "../data/aparcamiento_prob_vision_distancia_linea.data"
		cat "../data/out/min_100000_100_${i}_${j}" >> "../data/aparcamiento_prob_vision_distancia.data"
		cat "../data/out/min_linea_100000_100_${i}_${j}" >> "../data/aparcamiento_prob_vision_distancia_linea.data"
	done
done

tabla="../data/aparcamiento_prob_vision_distancia_tabla.csv"
tabla2="../data/aparcamiento_prob_vision_posicion_tabla.csv"

touch $tabla
touch $tabla2

echo -n "," > $tabla
echo -n "," > $tabla2

for i in $(seq 0.1 0.1 0.9); do
	echo -n "$i," >> $tabla
	echo -n "$i," >> $tabla2
done

echo "" >> $tabla
echo "" >> $tabla2

for i in $(seq 1 1 10); do

	printf "$i," >> $tabla
	printf "$i," >> $tabla2

	for j in $(seq 0.1 0.1 0.9); do

		unica=$(cat "../data/out/min_100000_100_${i}_${j}")
		unica2=$(cat "../data/out/min_linea_100000_100_${i}_${j}")
#		echo $unica
#		echo "------------------------------------------------------------------"
		awk '{printf "%f,", $1}' <<< $unica >> $tabla
		awk '{printf "%d,", $1}' <<< $unica2 >> $tabla2

	done

	printf "\n" >> $tabla
	printf "\n" >> $tabla2

done


rm -rf out ../data/out

gnuplot aparcamiento.gp

#rm -f ../data/*.data

