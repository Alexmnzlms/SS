#!/bin/sh

cd ..
make
cd script

dist_a="../data/quiosco_a.data"
dist_b="../data/quiosco_b.data"
dist_c="../data/quiosco_c.data"

for i in $(seq 0 1 100); do
	echo -n "" > $dist_a
	echo -n "" > $dist_b
	echo -n "" > $dist_c
done

for i in $(seq 0 1 100); do
	../bin/quiosco_exe $i 10 5 1000000 a >> $dist_a
	../bin/quiosco_exe $i 10 5 1000000 b >> $dist_b
	../bin/quiosco_exe $i 10 5 1000000 c >> $dist_c
done

salida_a="../data/ganancia_a.data"
salida_b="../data/ganancia_b.data"
salida_c="../data/ganancia_c.data"

echo -n "" > $salida_a
echo -n "" > $salida_b
echo -n "" > $salida_c

awk '{print $6}' <<< $(cat $dist_a) >> $salida_a
awk '{print $6}' <<< $(cat $dist_b) >> $salida_b
awk '{print $6}' <<< $(cat $dist_c) >> $salida_c

cat $salida_a
cat $salida_b
cat $salida_c

gnuplot quiosco.gp
