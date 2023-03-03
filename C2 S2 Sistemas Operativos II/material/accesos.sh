#!/usr/bin/env bash
#filename="access.log"

if [[ $# -ne 2 ]]; then
  echo "ERROR: Hacen falta exactamente 2 argumentos"
  #muestraUso
  #TODO: implementar muestraUso
fi

if [[ ! (($1 == "-c") || ($1 == "GET/POST")) ]]; then
  #TODO: Hacer algo
  echo "implementame"
fi

if [[ $1 == "-c" ]]; then
  cut -d " " -f 9 log/access.log | sort | uniq
fi

if [[ $1 == "GET" || $1 == "POST" ]]; then
    fecha=$(date +"%h %d %H:%M:%S")
    # TODO: Hacer cosas
    printf "%s %s. Se han registrado %d accesos de tipo  con respuesta %d" $fecha $HOSTNAME;echo
fi
