set terminal png size 1080,720
# set yrange [0:*]
# set xrange [0:100]
set key left Left
set rmargin at screen 0.90

do for [v in "100 1000 5000 10000 100000"]{
	do for [d in "a b c"]{
		set output "../memoria/img/distribucion_".d."_".v.".png"
		set title "Ganancia esperada para la distribución ".d." ".v." veces"
		set xlabel "Periodicos contratados"
		set ylabel "Ganancia esperada"
		plot for [y in "1 5 10"] "../data/quiosco/ganancia_".y."_".v."_".d.".data" with lines title "Ganancia para x = 10, y = ".y, for [y in "1 5 10"] "../data/quiosco/max_ganancia_".y."_".v."_".d.".data" using 1:2:(sprintf("(%d, %d)", $1, $2)) with labels point pt 7 offset char 1,1 notitle
	}
}

do for [d in "a b c"]{
	set output "../memoria/img/mod_1_distribucion_".d.".png"
	set title "Ganancia esperada para la distribución ".d." (modificación 1)"
	set xlabel "Periodicos contratados"
	set ylabel "Ganancia esperada"
	plot for [  z in "100 500 1000"] "../data/quiosco/mod_1_ganancia_".z."_".d.".data" with lines title "Ganancia para x = 10, z = ".z, for [  z in "100 500 1000"] "../data/quiosco/mod_1_max_ganancia_".z."_".d.".data" using 1:2:(sprintf("(%d, %d)", $1, $2)) with labels point pt 7 offset char 1,1 notitle
}

do for [d in "a b c"]{
	set output "../memoria/img/mod_2_distribucion_".d.".png"
	set title "Ganancia esperada para la distribución ".d." (modificación 2)"
	set xlabel "Periodicos contratados"
	set ylabel "Ganancia esperada"
	plot for [  z in "100 500 1000"] for [y in "1 5 10"] "../data/quiosco/mod_2_ganancia_".y."_".z."_".d.".data" with lines title "Ganancia para x = 10, y = ".y.", z = ".z, for [  z in "100 500 1000"] for [y in "1 5 10"] "../data/quiosco/mod_2_max_ganancia_".y."_".z."_".d.".data" using 1:2:(sprintf("(%d, %d)", $1, $2)) with labels point pt 7 offset char 1,1 notitle
}
