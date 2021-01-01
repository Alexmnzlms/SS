set terminal png size 1400, 600
set output "with_lines.png"
set datafile separator ","
set style fill solid
set xlabel ""
set yrange [0:1000]

set style line 1 linetype 1 pointtype 0 linewidth 1 linecolor 1
set style line 2 linetype 2 pointtype 0 linewidth 1 linecolor 2
set style line 3 linetype 3 pointtype 0 linewidth 1 linecolor 3

plot 'salida_data_sum' using 1:4 t "R" w filledcurves x1 linestyle 3, 'salida_data_sum' using 1:3 t "S" w filledcurves x1 linestyle 2, 'salida_data_sum' using 1:2 t "I" w filledcurves x1 linestyle 1,
