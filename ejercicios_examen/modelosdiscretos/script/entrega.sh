#!/bin/sh

cd ../memoria
make
cp ./memoria.pdf ../Memoria_EjercicioModelosDiscretos_AlejandroManzanaresLemus.pdf
cd ..

mkdir codigo-fuente
mkdir codigo-fuente/bin

cp -r src codigo-fuente
cp -r include codigo-fuente
cp -r script codigo-fuente
rm codigo-fuente/script/*_data
rm codigo-fuente/script/entrega.sh

cp makefile codigo-fuente/makefile

zip -r EjercicioModelosDiscretos_AlejandroManzanaresLemus.zip codigo-fuente Memoria_EjercicioModelosDiscretos_AlejandroManzanaresLemus.pdf

rm -rf codigo-fuente
# rm Memoria_Practica4_AlejandroManzanaresLemus.pdf
