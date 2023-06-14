#!/bin/bash
# $1 va a ser el archivo a guardar. Este se guardará en formato csv

#Selecciono solo una parte del nombre del archivo
nombreFinalArchivo=$(echo "$1" | cut -d'_' -f 1 --complement | grep -o -P '(?<=apartado).*' | sed 's/.out/.csv/')

#Limpiamos el archivo
printf "" > "$nombreFinalArchivo"

#Agregamos los encabezados
printf "N; f; Ciclos\n" >> "$nombreFinalArchivo"
#hacerlo $2-1 veces
for veces in $(eval echo {0..$(($2-1))})
do
	for N in 250 500 750 1000 1500 2000 2550 3000
	do
#	  printf "$N;________" >> "$1".csv

	  #hacerlo para 1,2,4,8,12,16,20,24,28,32 hilos
	  for hilos in 1 2 4 8 12 16 20 24 28 32
	  do
	    printf "$N;$hilos;" >> "$nombreFinalArchivo"
		  ./"$1" $N $hilos >> "$nombreFinalArchivo"
		done
	done
done

sort -t';' -k1n -k2n -k3n "$nombreFinalArchivo" -o "$nombreFinalArchivo"
cat "$nombreFinalArchivo" | tr '.' ',' > "$nombreFinalArchivo".tmp
mv "$nombreFinalArchivo".tmp "$nombreFinalArchivo"
