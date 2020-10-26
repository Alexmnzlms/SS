#!/bin/sh

cd ..
make
cd script

for y in 1 5 10; do
	echo -n "" > "../data/quiosco_${y}_a.data"
	echo -n "" > "../data/quiosco_${y}_b.data"
	echo -n "" > "../data/quiosco_${y}_c.data"
done

for y in 1 5 10; do
../bin/quiosco_exe 10 $y 100000 a 0 >> "../data/quiosco_${y}_a.data"
../bin/quiosco_exe 10 $y 100000 b 0 >> "../data/quiosco_${y}_b.data"
../bin/quiosco_exe 10 $y 100000 c 0 >> "../data/quiosco_${y}_c.data"
done

for y in 1 5 10; do
	echo -n "" > "../data/ganancia_${y}_a.data"
	echo -n "" > "../data/ganancia_${y}_b.data"
	echo -n "" > "../data/ganancia_${y}_c.data"
done

for y in 1 5 10; do
	awk '{print $6}' <<< $(cat "../data/quiosco_${y}_a.data") >> "../data/ganancia_${y}_a.data"
	awk '{print $6}' <<< $(cat "../data/quiosco_${y}_b.data") >> "../data/ganancia_${y}_b.data"
	awk '{print $6}' <<< $(cat "../data/quiosco_${y}_c.data") >> "../data/ganancia_${y}_c.data"
done

gnuplot quiosco.gp
