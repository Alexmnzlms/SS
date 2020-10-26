set terminal png size 960,540
set yrange [0:*]

set output "../memoria/img/distribucion_a.png"
set title "Ganancia esperada para la distribución a"
set xlabel "Periodicos contratados"
set ylabel "Ganancia esperada"
plot for [name in "1 5 10"] "../data/ganancia_".name."_a.data" with linespoints title "Ganancia para x = 10, y = ".name

set output "../memoria/img/distribucion_b.png"
set title "Ganancia esperada para la distribución b"
set xlabel "Periodicos contratados"
set ylabel "Ganancia esperada"
plot for [name in "1 5 10"] "../data/ganancia_".name."_b.data" with linespoints title "Ganancia para x = 10, y = ".name

set output "../memoria/img/distribucion_c.png"
set title "Ganancia esperada para la distribución c"
set xlabel "Periodicos contratados"
set ylabel "Ganancia esperada"
plot for [name in "1 5 10"] "../data/ganancia_".name."_c.data" with linespoints title "Ganancia para x = 10, y = ".name
