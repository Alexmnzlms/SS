set terminal png size 1920,1080

set xlabel ""
set ylabel ""
set output "../memoria/img/radares_prob_fallo.png"
plot for [name in "1 5 10 50 100 500 1000"] "../data/radares_".name."_prob.data" with linespoints title "Probabilidad de fallo con ".name." simulaciones"

set xlabel ""
set ylabel ""
set output "../memoria/img/radares_tiempo_fallo.png"
plot for [name in "1 5 10 50 100 500 1000"] "../data/radares_".name."_tiempo.data" with linespoints title "Tiempo medio de fallo con ".name." simulaciones"
