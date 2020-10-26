#!/bin/sh

cd ..
make
cd script
for v in 1 100 1000 5000 10000 100000; do
	for y in 1 5 10; do
		echo -n "" > "../data/quiosco_${y}_${v}_a.data"
		echo -n "" > "../data/quiosco_${y}_${v}_b.data"
		echo -n "" > "../data/quiosco_${y}_${v}_c.data"
	done
done

for v in 1 100 1000 5000 10000 100000; do
	for y in 1 5 10; do
	../bin/quiosco_exe 10 $y $v a 0 >> "../data/quiosco_${y}_${v}_a.data"
	../bin/quiosco_exe 10 $y $v b 0 >> "../data/quiosco_${y}_${v}_b.data"
	../bin/quiosco_exe 10 $y $v c 0 >> "../data/quiosco_${y}_${v}_c.data"
	done
done

for v in 1 100 1000 5000 10000 100000; do
	for y in 1 5 10; do
		echo -n "" > "../data/ganancia_${y}_${v}_a.data"
		echo -n "" > "../data/ganancia_${y}_${v}_b.data"
		echo -n "" > "../data/ganancia_${y}_${v}_c.data"
	done
done

for v in 1 100 1000 5000 10000 100000; do
	for y in 1 5 10; do
		awk '{print $6}' <<< $(cat "../data/quiosco_${y}_${v}_a.data") >> "../data/ganancia_${y}_${v}_a.data"
		awk '{print $6}' <<< $(cat "../data/quiosco_${y}_${v}_b.data") >> "../data/ganancia_${y}_${v}_b.data"
		awk '{print $6}' <<< $(cat "../data/quiosco_${y}_${v}_c.data") >> "../data/ganancia_${y}_${v}_c.data"
	done
done
gnuplot quiosco.gp
