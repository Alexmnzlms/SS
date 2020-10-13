#!/bin/sh

mkdir ../data/out

./aparcamiento_table.sh

for i in $(seq 0.1 0.1 0.9); do
	./aparcamiento.sh 100000 100 2 $i;
done

echo -n  > ../data/aparcamiento_prob_min.data
echo -n  > ../data/aparcamiento_prob_min_linea.data
for i in $(seq 0.1 0.1 0.9); do
	echo -n "${i} " >> ../data/aparcamiento_prob_min.data
	echo -n "${i} " >> ../data/aparcamiento_prob_min_linea.data
	cat "../data/out/min_100000_100_2_${i}" >> ../data/aparcamiento_prob_min.data
	cat "../data/out/min_linea_100000_100_2_${i}" >> ../data/aparcamiento_prob_min_linea.data
done

for i in $(seq 1 1 10); do
	./aparcamiento.sh 100000 100 $i 0.9;
done

echo -n  > ../data/aparcamiento_vision_min.data
echo -n  > ../data/aparcamiento_vision_min_linea.data
for i in $(seq 1 1 10); do
	echo -n "${i} " >> ../data/aparcamiento_vision_min.data
	echo -n "${i} " >> ../data/aparcamiento_vision_min_linea.data
	cat "../data/out/min_100000_100_${i}_0.9" >> ../data/aparcamiento_vision_min.data
	cat "../data/out/min_linea_100000_100_${i}_0.9" >> ../data/aparcamiento_vision_min_linea.data
done


for i in 10 100 1000 10000 100000; do
	./aparcamiento.sh $i 100 2 0.9;
done

echo -n  "" > ../data/aparcamiento_veces_min.data
echo -n  "" > ../data/aparcamiento_veces_min_linea.data
for i in 10 100 1000 10000 100000; do
	echo -n "${i} ">> ../data/aparcamiento_veces_min.data
	echo -n "${i} ">> ../data/aparcamiento_veces_min_linea.data
	cat "../data/out/min_${i}_100_2_0.9" >> ../data/aparcamiento_veces_min.data
	cat "../data/out/min_${i}_100_2_0.9" >> ../data/aparcamiento_veces_min_linea.data
done


rm -rf out ../data/out

gnuplot aparcamiento.gp
