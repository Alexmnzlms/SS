set terminal png size 1920,1080

set xlabel ""
set ylabel ""
set output "../memoria/img/radares_prob_fallo.png"
plot for [name in "1 5 10 50 100 500 1000"] "../data/radares_".name."_prob.data" with linespoints title "Probabilidad de fallo con ".name." simulaciones"

set xlabel ""
set ylabel ""
set output "../memoria/img/radares_tiempo_fallo.png"
plot for [name in "1 5 10 50 100 500 1000"] "../data/radares_".name."_tiempo.data" with linespoints title "Tiempo medio de fallo con ".name." simulaciones"

set xlabel ""
set ylabel ""
set output "../memoria/img/radares_tiempo_fallo.png"
plot for [name in "1 5 10 50 100 500 1000"] "../data/radares_".name."_tiempo.data" with linespoints title "Tiempo medio de fallo con ".name." simulaciones"

set xlabel ""
set ylabel ""
set output "../memoria/img/radares_tiempo_multiple.png"
plot for [name in "20 40 60"] "../data/radares_0_15_".name."_tiempo.data" with linespoints title "Tiempo de fallo tr=0-15 y vu=".name
set output "../memoria/img/radares_tiempo_multiple.png"
replot for [name in "20 40 60"] "../data/radares_15_30_".name."_tiempo.data" with linespoints title "Tiempo de fallo tr=15-30 y vu=".name
set output "../memoria/img/radares_tiempo_multiple.png"
replot for [name in "20 40 60"] "../data/radares_30_45_".name."_tiempo.data" with linespoints title "Tiempo de fallo tr=30-45 y vu=".name
set output "../memoria/img/radares_tiempo_multiple.png"
replot for [name in "20 40 60"] "../data/radares_45_60_".name."_tiempo.data" with linespoints title "Tiempo de fallo tr=45-60 y vu=".name

set xlabel ""
set ylabel ""
set output "../memoria/img/radares_prob_multiple.png"
plot for [name in "20 40 60"] "../data/radares_0_15_".name."_prob.data" with linespoints title "Probabilidad de fallo tr=0-15 y vu=".name
set output "../memoria/img/radares_prob_multiple.png"
replot for [name in "20 40 60"] "../data/radares_15_30_".name."_prob.data" with linespoints title "Probabilidad de fallo tr=15-30 y vu=".name
set output "../memoria/img/radares_prob_multiple.png"
replot for [name in "20 40 60"] "../data/radares_30_45_".name."_prob.data" with linespoints title "Probabilidad de fallo tr=30-45 y vu=".name
set output "../memoria/img/radares_prob_multiple.png"
replot for [name in "20 40 60"] "../data/radares_45_60_".name."_prob.data" with linespoints title "Probabilidad de fallo tr=45-60 y vu=".name
