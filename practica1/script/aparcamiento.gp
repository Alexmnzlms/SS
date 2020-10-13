set terminal png size 1920,1080

set xlabel "Posición inicial (c)"
set ylabel "Distancia media al objetivo"

set output "../memoria/img/probabilidad_aparcamiento.png"
plot for [name in "0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9"] "../data/aparcamiento_100000_100_2_".name.".data" with linespoints title "Probabilidad de ocupación = ".name

set output "../memoria/img/vision_aparcamiento.png"
plot for [name in "1 2 3 4 5 6 7 8 9 10"] "../data/aparcamiento_100000_100_".name."_0.9.data" with linespoints title "Visión = ".name

set output "../memoria/img/simulaciones_aparcamiento.png"
plot for [name in "10 100 1000 10000 100000"] "../data/aparcamiento_".name."_100_2_0.9.data" with linespoints title "Número de simulaciones = ".name

set xlabel "Probabilidad de aparcamiento"
set ylabel "Distancia minima al objetivo"
set output "../memoria/img/min_probabilidad_aparcamiento.png"
plot "../data/aparcamiento_prob_min.data" with linespoints title "Distancia minima al objetivo"

set xlabel "Visión del conductor"
set ylabel "Distancia minima al objetivo"
set output "../memoria/img/min_vision_aparcamiento.png"
plot "../data/aparcamiento_vision_min.data" with linespoints title "Distancia minima al objetivo"

set xlabel "Numero de simulaciones"
set ylabel "Distancia minima al objetivo"
set output "../memoria/img/min_simulaciones_aparcamiento.png"
plot "../data/aparcamiento_veces_min.data" with linespoints title "Distancia minima al objetivo"

set xlabel "Ejecución de la simulación"
set ylabel "Distancia minima al objetivo"
set output "../memoria/img/min_ejecuciones_aparcamiento.png"
plot "../data/aparcamiento_ejecuciones_min.data" with linespoints title "Distancia minima al objetivo"

set yrange [0:100]
set xlabel "Probabilidad de aparcamiento"
set ylabel "Posición inicial (c)"
set output "../memoria/img/min_c_probabilidad_aparcamiento.png"
plot "../data/aparcamiento_prob_min_linea.data" with linespoints title "Posición (c) donde se alcanza la distancia mínima"

set yrange [0:100]
set xlabel "Visión del conductor"
set ylabel "Posición inicial (c)"
set output "../memoria/img/min_c_vision_aparcamiento.png"
plot "../data/aparcamiento_vision_min_linea.data" with linespoints title "Posición (c) donde se alcanza la distancia mínima"

set yrange [0:100]
set xlabel "Numero de simulaciones"
set ylabel "Posicion inicial (c)"
set output "../memoria/img/min_c_simulaciones_aparcamiento.png"
plot "../data/aparcamiento_veces_min_linea.data" with linespoints title "Posición (c) donde se alcanza la distancia mínima"

set yrange[0:100]
set xlabel "Ejecución de la simulación"
set ylabel "Posicion inicial (c)"
set output "../memoria/img/min_c_ejecuciones_aparcamiento.png"
plot "../data/aparcamiento_ejecuciones_min_linea.data" with linespoints title "Posicion (c) donde se alcanza la distancia mínima"
