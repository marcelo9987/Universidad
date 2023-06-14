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
		printf "$N;" >> "$nombreFinalArchivo"
		./"$1" $N >> "$nombreFinalArchivo"
	done
done

sort -t';' -k1n -k2n -k3n "$nombreFinalArchivo" -o "$nombreFinalArchivo"
cat "$nombreFinalArchivo" | tr '.' ',' > "$nombreFinalArchivo".tmp
mv "$nombreFinalArchivo".tmp "$nombreFinalArchivo"
