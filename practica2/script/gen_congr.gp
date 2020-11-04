set terminal png size 960,540

set output "../memoria/img/gen_congr_2060.png"
set title "Periodos para el gcl (2060x + 4321) mod m"
set xlabel "Valor inicial x_n"
set ylabel "Periodo encontrado"
plot for [mod in "1 2 3 4"] "../data/gen_congr_2060_".mod.".data" with lines title "Forma de calculo tipo ".mod

set output "../memoria/img/gen_congr_2061.png"
set title "Periodos para el gcl (2061x + 4321) mod m"
set xlabel "Valor inicial x_n"
set ylabel "Periodo encontrado"
plot for [mod in "1 2 3 4"] "../data/gen_congr_2061_".mod.".data" with lines title "Forma de calculo tipo ".mod
