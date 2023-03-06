#!/usr/bin/bash

# el primer   param es el numero de iters.
# el segundo param es el programa compilado.
# el cuarto  param es el num de hilos.
# el quinto  param es la carpeta de destino.



#mkdir -p "$5"
#/usr/bin/time -p -o salida ./script_ejec.sh "$1" "$2" "$3" "$4" "$5"

echo $1 $2 $3 $4 $5


numeros=(0 1000 2000 4000 8000 16000 32000 64000 128000 256000 512000 1024000)

for i in "${numeros[@]}"
do
  echo "$i"
  mkdir -p "$5"
  /usr/bin/time -p -o $5/crono_M"$i"_"$4"T.tiempo ./script_ejec.sh "$1" "$2" "$i" "$4" "$5"
done


