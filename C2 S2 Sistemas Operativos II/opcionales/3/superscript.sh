#!/usr/bin/bash

# el primer  param es el numero de iters.
# el segundo param es el programa compilado.
# el tercer  param es el num de hilos.
# el cuarto  param es la carpeta de destino.



#mkdir -p "$4"
#/usr/bin/time -p -o salida ./script_ejec.sh "$1" "$2" "$3" "$4"

echo $1 $2 $3 $4

 #
numeros=(0 1000 2000 4000 8000 16000 32000 64000 128000 256000 512000 1024000)
#numeros=(0 1000 2000 4000 8000 16000 32000 64000 128000)# 256000 512000 1024000)

for i in "${numeros[@]}"
do
  echo "$i"
#  directorio="$4"."$2".T"$3"
  directorio="$4"
  mkdir -p "$directorio"
#  /usr/bin/time -p -o $4/crono_M"$i"_"$3"T.tiempo ./script_ejec.sh "$1" "$2" "$i" "$3" "$4"
  ./script_ejec.sh "$1" "$2" "$i" "$3" "$directorio"
done


