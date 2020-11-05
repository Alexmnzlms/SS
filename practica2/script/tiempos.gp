set terminal png size 960,540

set output "../memoria/img/tiempos_a.png"
plot for [n in "1 2 3"] "../data/tiempos_1_".n.".data" with lines title "Forma numero ".n

set output "../memoria/img/tiempos_b.png"
plot for [n in "1 2"] "../data/tiempos_2_".n.".data" with lines title "Forma numero ".n

set output "../memoria/img/tiempos_c.png"
plot for [n in "1 2"] "../data/tiempos_3_".n.".data" with lines title "Forma numero ".n
set output "../memoria/img/tiempos_c.png"
replot "../data/tiempos_4_4.data" with lines title "Forma numero 4"
