
do for [i in "100 500 1000 5000 10000 50000"] {
	do for [j in "10 50 100 500 1000"]{
		set key out
		set lmargin at screen 0.1
		set rmargin at screen 0.9

		set terminal pngcairo size 1920,1080
		set output "../memoria/img/lago_10950_".i."_".j.".png"
		set title "Simulación del lago con ".i." peces pequeños y ".j." peces grandes durante 30 años."
		set xlabel "Tiempo en días"

		set multiplot
			set key left
			set ytics nomirror
			set ylabel "N. peces pequeños"
			set y2label ""
			plot "../data/lago_10950_".i."_".j.".data" using 1:2 with lines lt 1 title "Pequeños"

			unset ytics
			set y2tics
			set key right
			set y2label "N. peces grandes"
			set ylabel ""
			plot "../data/lago_10950_".i."_".j.".data" using 1:3 with lines axis x1y2 lt 2 title "Grandes"

		unset multiplot


	}

}
