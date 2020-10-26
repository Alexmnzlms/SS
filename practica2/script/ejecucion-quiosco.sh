#!/bin/sh

cd ..
make
cd script

dist_a="../data/quiosco_a.data"
dist_b="../data/quiosco_b.data"
dist_c="../data/quiosco_c.data"

echo -n "" > $dist_a
echo -n "" > $dist_b
echo -n "" > $dist_c

../bin/quiosco_exe $i 10 10 100000 a 0 >> $dist_a
../bin/quiosco_exe $i 10 10 100000 b 0 >> $dist_b
../bin/quiosco_exe $i 10 10 100000 c 0 >> $dist_c


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
