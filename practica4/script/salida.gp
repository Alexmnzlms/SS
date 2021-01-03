set terminal png size 960, 540
set output "ISR.png"
set datafile separator ","
set style fill solid
set xlabel ""
#set yrange [0:1000]
set title "Evolución de la Población"

plot "../data/salida_data" using 1:4 t "Número de Retirados" w lines, \
     "../data/salida_data" using 1:3 t "Número de Susceptibles" w lines, \
	  "../data/salida_data" using 1:2 t "Número de Infectados" w lines,
