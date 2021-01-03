set terminal png size 960, 540
set datafile separator ","

set output "I_S.png"
set title "Número de Susceptibles respecto a los Infectados"
set xlabel "Número de Infectados"
set ylabel "Número de Susceptibles"
plot "../data/salida_data_I_S_data" with lines title "Susceptibles-Infectados"
