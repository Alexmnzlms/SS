set terminal png size 1400, 600
set datafile separator ","

do for [p1 in "I R S"]{
	do for [p2 in "I R S"]{
		set output p1."_".p2.".png"
		set xlabel p1
		set ylabel p2
		plot "../data/salida_data_".p1."_".p2."_data" with lines title p1."-".p2
	}
}
