set terminal png size 1080,720


# set output "../precision.png"
# plot for [file in "sistema-teorico sistema-t-fijo sistema-t-variable"] "../data/".file."_data" with lines title "Precision ".file


do for [unidad in "dias horas minutos segundos"]{
	set title "Precisión"
	set xlabel "Ejecución interna"
	set ylabel "Duración media de los fallos"
	set output "../precision".unidad.".png"
	plot for [file in "sistema-teorico sistema-t-fijo sistema-t-variable"] "../data/".file."-".unidad."_data" with lines title "Precision ".file." en ".unidad
}
