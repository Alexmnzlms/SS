#!/bin/sh

cd ..
make -B
cd script

echo -n "" > "../data/tiempos_1_1.data"
echo -n "" > "../data/tiempos_2_1.data"
echo -n "" > "../data/tiempos_3_1.data"
echo -n "" > "../data/tiempos_1_2.data"
echo -n "" > "../data/tiempos_2_2.data"
echo -n "" > "../data/tiempos_3_2.data"
echo -n "" > "../data/tiempos_1_3.data"
echo -n "" > "../data/tiempos_4_4.data"

for v in $(seq 1000 1000 1000000); do
	echo $v
	../bin/quiosco_tiempos_exe $v 1 1 >> "../data/tiempos_1_1.data" &
	../bin/quiosco_tiempos_exe $v 2 1 >> "../data/tiempos_2_1.data" &
	../bin/quiosco_tiempos_exe $v 3 1 >> "../data/tiempos_3_1.data" &
	wait
	../bin/quiosco_tiempos_exe $v 1 2 >> "../data/tiempos_1_2.data" &
	../bin/quiosco_tiempos_exe $v 2 2 >> "../data/tiempos_2_2.data" &
	../bin/quiosco_tiempos_exe $v 3 2 >> "../data/tiempos_3_2.data" &
	wait
	../bin/quiosco_tiempos_exe $v 1 3 >> "../data/tiempos_1_3.data" &
	../bin/quiosco_tiempos_exe $v 4 4 >> "../data/tiempos_4_4.data" &
	wait
done

gnuplot tiempos.gp

