#!/bin/sh

cd ..
make -B bin/simulacion_lago2especiespeces_exe
cd script

for i in 100 500 1000 5000 10000 50000; do
	for j in 10 50 100 500 1000; do
		echo -n "" > "../data/lago_10950_${i}_${j}.data"
	done

done
for i in 100 500 1000 5000 10000 50000; do
	for j in 10 50 100 500 1000; do
		echo 10950 $i $j | ../bin/simulacion_lago2especiespeces_exe >> "../data/lago_10950_${i}_${j}.data"
	done
done

gnuplot peces.gp
