set terminal png size 960,540
set yrange [0:*]


do for [v in "1 100 1000 5000 10000 100000"]{
	set output "../memoria/img/distribucion_a".v.".png"
	set title "Ganancia esperada para la distribución a ".v." veces"
	set xlabel "Periodicos contratados"
	set ylabel "Ganancia esperada"
	plot for [name in "1 5 10"] "../data/ganancia_".name."_".v."_a.data" with linespoints title "Ganancia para x = 10, y = ".name

	set output "../memoria/img/distribucion_b".v.".png"
	set title "Ganancia esperada para la distribución b ".v." veces"
	set xlabel "Periodicos contratados"
	set ylabel "Ganancia esperada"
	plot for [name in "1 5 10"] "../data/ganancia_".name."_".v."_b.data" with linespoints title "Ganancia para x = 10, y = ".name

	set output "../memoria/img/distribucion_c".v.".png"
	set title "Ganancia esperada para la distribución c con ".v." veces"
	set xlabel "Periodicos contratados"
	set ylabel "Ganancia esperada"
	plot for [name in "1 5 10"] "../data/ganancia_".name."_".v."_c.data" with linespoints title "Ganancia para x = 10, y = ".name
}
