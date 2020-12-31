#!/bin/sh

cd ../memoria
make
cp ./demo.pdf ../Memoria_Practica3_AlejandroManzanaresLemus.pdf
cd ..

mkdir codigo-fuente
mkdir codigo-fuente/bin
mkdir codigo-fuente/data

cp -r src codigo-fuente
cp -r include codigo-fuente
cp -r script codigo-fuente
rm codigo-fuente/script/entrega.sh

cp makefile codigo-fuente/makefile

zip -r Practica3_AlejandroManzanaresLemus.zip codigo-fuente Memoria_Practica3_AlejandroManzanaresLemus.pdf

rm -rf codigo-fuente
rm Memoria_Practica3_AlejandroManzanaresLemus.pdf
