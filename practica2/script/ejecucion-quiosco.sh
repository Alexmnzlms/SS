#!/bin/sh

cd ..
make
cd script

# Ejercicio basico

x=10
mod=0

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
		../bin/quiosco_exe $x $y $v $d $mod >> "../data/quiosco_${y}_${v}_${d}.data"
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

# Primera modificación

v=10000
y=0
mod=1

for d in a b c; do
	for z in 10 100 500; do
		echo -n "" > "../data/mod_${mod}_quiosco_${z}_${d}.data"
		echo -n "" > "../data/mod_${mod}_ganancia_${z}_${d}.data"
		echo -n "" > "../data/mod_${mod}_max_ganancia_${z}_${d}.data"
	done
done

for d in a b c; do
	for z in 10 100 500; do
		../bin/quiosco_exe $x $y $v $d $mod $z >> "../data/mod_${mod}_quiosco_${z}_${d}.data"
	done
done

for d in a b c; do
	for z in 10 100 500; do
		awk '{print $6}' <<< $(cat "../data/mod_${mod}_quiosco_${z}_${d}.data") >>  "../data/mod_${mod}_ganancia_${z}_${d}.data"
	done
done

for d in a b c; do
	for z in 10 100 500; do
		awk 'END { printf "%d ", s} { max || max = $1; s || s = NR; if ($1 > max) {max=$1; s=NR} }' <<< $(cat "../data/mod_${mod}_ganancia_${z}_${d}.data") >> "../data/mod_${mod}_max_ganancia_${z}_${d}.data"
		awk 'END { print max} { max || max = $1; s || s = NR; if ($1 > max) {max=$1; s=NR} }' <<< $(cat "../data/mod_${mod}_ganancia_${z}_${d}.data") >> "../data/mod_${mod}_max_ganancia_${z}_${d}.data"
	done
done


# Segunda modificación

v=10000
mod=2

for d in a b c; do
	for z in 10 100 500; do
		for y in 1 5 10; do
			echo -n "" > "../data/mod_${mod}_quiosco_${y}_${z}_${d}.data"
			echo -n "" > "../data/mod_${mod}_ganancia_${y}_${z}_${d}.data"
			echo -n "" > "../data/mod_${mod}_max_ganancia_${y}_${z}_${d}.data"
		done
	done
done

for d in a b c; do
	for z in 10 100 500; do
		for y in 1 5 10; do
			../bin/quiosco_exe $x $y $v $d $mod $z >> "../data/mod_${mod}_quiosco_${y}_${z}_${d}.data"
		done
	done
done

for d in a b c; do
	for z in 10 100 500; do
		for y in 1 5 10; do
			awk '{print $6}' <<< $(cat "../data/mod_${mod}_quiosco_${y}_${z}_${d}.data") >>  "../data/mod_${mod}_ganancia_${y}_${z}_${d}.data"
		done
	done
done

for d in a b c; do
	for z in 10 100 500; do
		for y in 1 5 10; do
			awk 'END { printf "%d ", s} { max || max = $1; s || s = NR; if ($1 > max) {max=$1; s=NR} }' <<< $(cat "../data/mod_${mod}_ganancia_${y}_${z}_${d}.data") >> "../data/mod_${mod}_max_ganancia_${y}_${z}_${d}.data"
			awk 'END { print max} { max || max = $1; s || s = NR; if ($1 > max) {max=$1; s=NR} }' <<< $(cat "../data/mod_${mod}_ganancia_${y}_${z}_${d}.data") >> "../data/mod_${mod}_max_ganancia_${y}_${z}_${d}.data"
		done
	done
done

gnuplot quiosco.gp

rm ../data/*.data
