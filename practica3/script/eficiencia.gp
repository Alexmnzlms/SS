set terminal png size 1080,720


set output "../eficiencia.png"
plot for [file in "sistema-fijo sistema-variable"] "../data/tiempos_".file."_data" with lines title "Eficiencia ".file

