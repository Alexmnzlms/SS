set terminal png size 1080,720

set output "./demanda.png"
set ylabel "Kg de papel reciclado no vendido"
set xlabel "Kg de papel reciclado obtenido por 30 kg de papel usado"

plot "./demanda_data" with lines title "Demanda de papel reciclado no satisfecha"
