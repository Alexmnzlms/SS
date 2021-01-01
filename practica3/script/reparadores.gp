set terminal png size 1080,720

do for [medren in "dmf dtf nmmr tmefs tor"]{
	set title medren
	set xlabel "Ejecuciones"
	set ylabel medren
	set output "../reparadores_".medren.".png"
	plot for [m in "10 5 1 0"] for [s in "20 2 10 0"] "../data/reparadores_".m."_".s."_data_".medren."_data" with lines title medren." con m=".m." y x=".s
}
