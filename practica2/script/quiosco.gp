set terminal png size 1920,1080
set yrange [0:*]
set output "../memoria/img/prueba.png"
set xlabel "Periodicos contratados"
set ylabel "Ganancia esperada"
plot for [name in "a b c"] "../data/ganancia_".name.".data" with linespoints title "Ganancia para distribución ".name
