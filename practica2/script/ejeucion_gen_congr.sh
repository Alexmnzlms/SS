#!/bin/sh

cd ..
make -B
cd script

for g in 2060 2061; do
	for mod in 1 2 3 4; do
		echo -n "" > "../data/gcl/gen_congr_${g}_${mod}.data"
		echo -n "" > "../data/gcl/max_gen_congr_${g}_${mod}.data"
	done
done

for g in 2060 2061; do
	for mod in 1 2 3 4; do
		for i in $(seq 0 1 9999); do
			../bin/gen_congr_exe $g 4321 $i $mod >> "../data/gcl/gen_congr_${g}_${mod}.data"
		done
	done
done

for g in 2060 2061; do
	for mod in 1 2 3 4; do
		awk 'END { printf "%d ", s-1} { max || max = $2; s || s = NR; if ($2 > max) {max=$2; s=NR} }' <<< $(cat "../data/gcl/gen_congr_${g}_${mod}.data") >> "../data/gcl/max_gen_congr_${g}_${mod}.data"
		awk 'END { print max} { max || max = $2; s || s = NR; if ($2 > max) {max=$2; s=NR} }' <<< $(cat "../data/gcl/gen_congr_${g}_${mod}.data") >> "../data/gcl/max_gen_congr_${g}_${mod}.data"
	done
done

echo -n "" > "../data/gcl/max_gen_congr.data"

for g in 2060 2061; do
	for mod in 1 2 3 4; do
		echo -n $g >> "../data/gcl/max_gen_congr.data"
		echo -n " " >> "../data/gcl/max_gen_congr.data"
		echo -n $mod >> "../data/gcl/max_gen_congr.data"
		echo -n " " >> "../data/gcl/max_gen_congr.data"
		cat "../data/gcl/max_gen_congr_${g}_${mod}.data" >> "../data/gcl/max_gen_congr.data"
	done
done
