set terminal png size 1080,720
set key left Left

set output "../memoria/img/tiempos_a.png"
set title "Tiempos para la distribución a"
set xlabel "Numero de ejecuciones"
set ylabel "Tiempo en segundos"
plot for [n in "1 2 3"] "../data/tiempo/tiempos_1_".n.".data" with lines title "Forma numero ".n

set output "../memoria/img/tiempos_b.png"
set title "Tiempos para la distribución b"
set xlabel "Numero de ejecuciones"
set ylabel "Tiempo en segundos"
plot for [n in "1 2"] "../data/tiempo/tiempos_2_".n.".data" with lines title "Forma numero ".n

set output "../memoria/img/tiempos_c.png"
set title "Tiempos para la distribución c"
set xlabel "Numero de ejecuciones"
set ylabel "Tiempo en segundos"
plot for [n in "1 2"] "../data/tiempo/tiempos_3_".n.".data" with lines title "Forma numero ".n
set output "../memoria/img/tiempos_c.png"
replot "../data/tiempo/tiempos_4_4.data" with lines title "Forma numero 4"
