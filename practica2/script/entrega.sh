#!/bin/sh

cd ../memoria
make
cp ./demo.pdf ../Memoria_Practica2_AlejandroManzanaresLemus.pdf
cd ..

mkdir codigo-fuente
mkdir codigo-fuente/bin

cp -r src codigo-fuente
cp -r include codigo-fuente
cp README codigo-fuente

cp makefile codigo-fuente/makefile

zip -r Practica2_AlejandroManzanaresLemus.zip codigo-fuente Memoria_Practica2_AlejandroManzanaresLemus.pdf

rm -rf codigo-fuente
rm Memoria_Practica2_AlejandroManzanaresLemus.pdf
