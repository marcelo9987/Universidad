#!/usr/bin/env bash

#Este script llama al script ejecutartiempos.sh para ejecutar los programas  de la version 2 y 3 con el param 11
# Ahora para permitir expansiones de shell y asi compilar varios archivos
for archivo in "$@"
do
  #hay que detectar si es apartado2 o apartado3 y usar ejecutartiempos.sh y si es apartado4 usar ejecutartiempos4.sh
  if [[ $archivo == *"apartado2"* ]]; then
    ./ejecutartiempos.sh "$archivo" 11
  elif [[ $archivo == *"apartado3"* ]]; then
    ./ejecutartiempos.sh "$archivo" 11
  elif [[ $archivo == *"apartado4"* ]]; then
    ./ejecutartiempos4.sh "$archivo" 11
  elif [[ $archivo == *"apartado1"* ]]; then
    ./ejecutartiempos.sh "$archivo" 11
  fi
done


