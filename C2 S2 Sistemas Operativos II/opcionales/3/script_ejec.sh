#!/usr/bin/bash

#el primer   param es el numero de iters.
# el segundo param es el programa compilado.
# el tercer  param es el numero de la suma.
# el cuarto  param es el num de hilos.
# el quinto  param es la carpeta de destino.

function llamar_programa()
{
  mkdir -p "$5"
  # shellcheck disable=SC2086
  "./${2}" $3 $4 >> $5/resultados."$1"ITERS_M_"$3".T_$4.log
}

for ((i = 0; i <= $1; i++))
do
  llamar_programa "$1" "$2" "$3" "$4" "$5"
done
