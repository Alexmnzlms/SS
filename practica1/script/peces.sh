#!/bin/sh

cd ..
make -B bin/simulacion_lago2especiespeces_exe
cd script

for i in 100 500 1000 5000 10000 50000; do
	for j in 10 50 100 500 1000; do
		echo -n "" > "../data/lago_${i}_${j}.data"
	done

done
for i in 100 500 1000 5000 10000 50000; do
	for j in 10 50 100 500 1000; do
		echo 3650 $i $j | ../bin/simulacion_lago2especiespeces_exe >> "../data/lago_${i}_${j}.data"
	done
done
for i in 30 60 180 365; do
	for j in 0.1 0.3 0.5 0.9; do
		echo -n "" > "../data/pesca_${i}_${j}.data"
	done
done

for i in 30 60 180 365; do
	for j in 0.1 0.3 0.5 0.9; do
		echo 3650 50000 100 | ../bin/simulacion_lago2especiespeces_exe $i $j >> "../data/pesca_${i}_${j}.data"
	done
done

echo -n "" > "../data/pesca.csv"
for i in 30 60 180 365; do
	for j in 0.1 0.3 0.5 0.9; do
	pesca=$(cat "../data/pesca_${i}_${j}.data"| grep -e Pesca)
	echo -n "${i},${j}," >> "../data/pesca.csv"
	awk '{print $3}' <<< $pesca >> "../data/pesca.csv"
	done
done

gnuplot peces.gp

rm ../data/*.data
