set terminal png size 960, 540
set output "ISR_acumulado.png"
set datafile separator ","
set style fill solid
set xlabel ""
#set yrange [0:1000]
set title "Evolución de la Población acumulada"
set style line 1 linetype 1 pointtype 0 linewidth 1 linecolor 5
set style line 2 linetype 2 pointtype 0 linewidth 1 linecolor 2
set style line 3 linetype 3 pointtype 0 linewidth 1 linecolor 4

plot "../data/salida_data_sum" using 1:4 t "Población Retirada" w filledcurves x1 linestyle 3, \
     "../data/salida_data_sum" using 1:3 t "Población Susceptible" w filledcurves x1 linestyle 2, \
	  "../data/salida_data_sum" using 1:2 t "Población Infectada" w filledcurves x1 linestyle 1,
