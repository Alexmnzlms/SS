#!/bin/sh

cd ..
make
cd script
for v in 100 1000 5000 10000 100000; do
	for y in 1 5 10; do
		for d in a b c; do
			echo -n "" > "../data/quiosco_${y}_${v}_${d}.data"
			echo -n "" > "../data/ganancia_${y}_${v}_${d}.data"
			echo -n "" > "../data/max_ganancia_${y}_${v}_${d}.data"
		done
	done
done

for v in 100 1000 5000 10000 100000; do
	for y in 1 5 10; do
		for d in a b c; do
		../bin/quiosco_exe 10 $y $v $d 0 >> "../data/quiosco_${y}_${v}_${d}.data"
		done
	done
done

for v in 100 1000 5000 10000 100000; do
	for y in 1 5 10; do
		for d in a b c; do
			awk '{print $6}' <<< $(cat "../data/quiosco_${y}_${v}_${d}.data") >> "../data/ganancia_${y}_${v}_${d}.data"
		done
	done
done

for v in 100 1000 5000 10000 100000; do
	for y in 1 5 10; do
		for d in a b c; do
			awk 'END { printf "%d ", s} { max || max = $1; s || s = NR; if ($1 > max) {max=$1; s=NR} }' <<< $(cat "../data/ganancia_${y}_${v}_${d}.data") >> "../data/max_ganancia_${y}_${v}_${d}.data"
			awk 'END { print max} { max || max = $1; s || s = NR; if ($1 > max) {max=$1; s=NR} }' <<< $(cat "../data/ganancia_${y}_${v}_${d}.data") >> "../data/max_ganancia_${y}_${v}_${d}.data"
		done
	done
done

rm ../data/*.data

gnuplot quiosco.gp
