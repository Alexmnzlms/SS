#!/bin/sh

cd ..
make -B
cd script

# Ejercicio basico

x=10
mod=0

for v in 100 1000 5000 10000 100000; do
	for y in 1 5 10; do
		for d in a b c; do
			echo -n "" > "../data/quiosco/quiosco_${y}_${v}_${d}.csv"
			echo -n "" > "../data/quiosco/ganancia_${y}_${v}_${d}.csv"
			echo -n "" > "../data/quiosco/max_ganancia_${y}_${v}_${d}.csv"
			echo -n "" > "../data/quiosco/max_ganancia_${d}.csv"
		done
	done
done

for v in 100 1000 5000 10000 100000; do
	for y in 1 5 10; do
		for d in a b c; do
			salida="../data/quiosco/quiosco_${y}_${v}_${d}.csv"
			echo $salida
			../bin/quiosco_exe $x $y $v $d $mod >> $salida
		done
	done
done

for v in 100 1000 5000 10000 100000; do
	for y in 1 5 10; do
		for d in a b c; do
			quiosco="../data/quiosco/quiosco_${y}_${v}_${d}.csv"
			ganancia="../data/quiosco/ganancia_${y}_${v}_${d}.csv"
			echo "${quiosco} >> ${ganancia}"
			for i in $(seq 0 1 100); do
				linea=$(cat $quiosco | grep -e "^${i} " )
				awk '{printf "%d ", $1}' <<< $linea >> $ganancia
				awk '{print $6}' <<< $linea >> $ganancia
			done
		done
	done
done

for v in 100 1000 5000 10000 100000; do
	for y in 1 5 10; do
		for d in a b c; do
			ganancia="../data/quiosco/ganancia_${y}_${v}_${d}.csv"
			max_ganancia="../data/quiosco/max_ganancia_${y}_${v}_${d}.csv"
			echo "${ganancia} >> ${max_ganancia}"
			awk 'END { printf "%d ", s-1} { max || max = $2; s || s = NR; if ($2 > max) {max=$2; s=NR} }' <<< $(cat $ganancia) >> $max_ganancia
			awk 'END { print max} { max || max = $2; s || s = NR; if ($2 > max) {max=$2; s=NR} }' <<< $(cat $ganancia) >> $max_ganancia
		done
	done
done

for v in 100 1000 5000 10000 100000; do
	for y in 1 5 10; do
		for d in a b c; do
			max_ganancia="../data/quiosco/max_ganancia_${y}_${v}_${d}.csv"
			max_ganancia_total="../data/quiosco/max_ganancia_${d}.csv"
			echo "${max_ganancia} >> ${max_ganancia_total}"
			echo -n "${d} ${v} 10 ${y} " >> $max_ganancia_total
			cat $max_ganancia >> $max_ganancia_total
		done
	done
done


# Primera modificación

v=10000
y=0
mod=1

for d in a b c; do
	for z in 100 500 1000; do
		echo -n "" > "../data/quiosco/mod_${mod}_quiosco_${z}_${d}.csv"
		echo -n "" > "../data/quiosco/mod_${mod}_ganancia_${z}_${d}.csv"
		echo -n "" > "../data/quiosco/mod_${mod}_max_ganancia_${z}_${d}.csv"
		echo -n "" > "../data/quiosco/mod_${mod}_max_ganancia_${d}.csv"
	done
done

for d in a b c; do
	for z in 100 500 1000; do
		salida="../data/quiosco/mod_${mod}_quiosco_${z}_${d}.csv"
		echo $salida
		../bin/quiosco_exe $x $y $v $d $mod $z >> $salida
	done
done

for d in a b c; do
	for z in 100 500 1000; do
		quiosco="../data/quiosco/mod_${mod}_quiosco_${z}_${d}.csv"
		ganancia="../data/quiosco/mod_${mod}_ganancia_${z}_${d}.csv"
		echo "${quiosco} >> ${ganancia}"
		for i in $(seq 0 1 100); do
			linea=$(cat $quiosco | grep -e "^${i} " )
			awk '{printf "%d ", $1}' <<< $linea >> $ganancia
			awk '{print $6}' <<< $linea >> $ganancia
		done
	done
done

for d in a b c; do
	for z in 100 500 1000; do
		ganancia="../data/quiosco/mod_${mod}_ganancia_${z}_${d}.csv"
		max_ganancia="../data/quiosco/mod_${mod}_max_ganancia_${z}_${d}.csv"
		echo "${ganancia} >> ${max_ganancia}"
		awk 'END { printf "%d ", s-1} { max || max = $2; s || s = NR; if ($2 > max) {max=$2; s=NR} }' <<< $(cat $ganancia) >> $max_ganancia
		awk 'END { print max} { max || max = $2; s || s = NR; if ($2 > max) {max=$2; s=NR} }' <<< $(cat $ganancia) >> $max_ganancia
	done
done

for d in a b c; do
	for z in 100 500 1000; do
		max_ganancia="../data/quiosco/mod_${mod}_max_ganancia_${z}_${d}.csv"
		max_ganancia_total="../data/quiosco/mod_${mod}_max_ganancia_${d}.csv"
		echo "${max_ganancia} >> ${max_ganancia_total}"
		echo -n "${d} 10 ${z} " >> $max_ganancia_total
		cat $max_ganancia >> $max_ganancia_total
	done
done



# Segunda modificación

v=10000
mod=2

for d in a b c; do
	for z in 100 500 1000; do
		for y in 1 5 10; do
			echo -n "" > "../data/quiosco/mod_${mod}_quiosco_${y}_${z}_${d}.csv"
			echo -n "" > "../data/quiosco/mod_${mod}_ganancia_${y}_${z}_${d}.csv"
			echo -n "" > "../data/quiosco/mod_${mod}_max_ganancia_${y}_${z}_${d}.csv"
			echo -n "" > "../data/quiosco/mod_${mod}_max_ganancia_${d}.csv"
		done
	done
done

for d in a b c; do
	for z in 100 500 1000; do
		for y in 1 5 10; do
			salida="../data/quiosco/mod_${mod}_quiosco_${y}_${z}_${d}.csv"
			echo $salida
			../bin/quiosco_exe $x $y $v $d $mod $z >> $salida
		done
	done
done

for d in a b c; do
	for z in 100 500 1000; do
		for y in 1 5 10; do
			quiosco="../data/quiosco/mod_${mod}_quiosco_${y}_${z}_${d}.csv"
			ganancia="../data/quiosco/mod_${mod}_ganancia_${y}_${z}_${d}.csv"
			echo "${quiosco} >> ${ganancia}"
			for i in $(seq 0 1 100); do
				linea=$(cat $quiosco | grep -e "^${i} " )
				awk '{printf "%d ", $1}' <<< $linea >> $ganancia
				awk '{print $6}' <<< $linea >> $ganancia
			done
		done
	done
done

gnuplot quiosco.gp

for d in a b c; do
	for z in 100 500 1000; do
		for y in 1 5 10; do
			ganancia="../data/quiosco/mod_${mod}_ganancia_${y}_${z}_${d}.csv"
			max_ganancia="../data/quiosco/mod_${mod}_max_ganancia_${y}_${z}_${d}.csv"
			echo "${ganancia} >> ${max_ganancia}"
			awk 'END { printf "%d ", s-1} { max || max = $2; s || s = NR; if ($2 > max) {max=$2; s=NR} }' <<< $(cat $ganancia) >> $max_ganancia
			awk 'END { print max} { max || max = $2; s || s = NR; if ($2 > max) {max=$2; s=NR} }' <<< $(cat $ganancia) >> $max_ganancia
		done
	done
done


for d in a b c; do
	for z in 100 500 1000; do
		for y in 1 5 10; do
			max_ganancia="../data/quiosco/mod_${mod}_max_ganancia_${y}_${z}_${d}.csv"
			max_ganancia_total="../data/quiosco/mod_${mod}_max_ganancia_${d}.csv"
			echo "${max_ganancia} >> ${max_ganancia_total}"
			echo -n "${d} 10 ${y} ${z} " >> $max_ganancia_total
			cat $max_ganancia >> $max_ganancia_total
		done
	done
done

gnuplot quiosco.gp

#rm ../data/quiosco/*.csv
