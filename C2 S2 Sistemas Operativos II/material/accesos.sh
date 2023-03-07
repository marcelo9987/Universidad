#!/usr/bin/env bash
#filename="access.log"

if [[ $# -ne 2 ]]; then
  echo "ERROR: Hacen falta exactamente 2 argumentos"
  #muestraUso
  #TODO: implementar muestraUso
  exit 1
fi

if [[ !  ( ($1 == "-c") || ( ($1 == "GET") || ($1 == "POST") ) )  ]]; then
  #TODO: Hacer algo
  echo "implementame"
  exit 1
fi

if [[ $1 == "-c" ]]; then
  cut -d " " -f 9 log/access.log | sort | uniq
fi

if [[ $1 == "GET" || $1 == "POST" ]]; then
    fecha=$(date +"%h %d %H:%M:%S")
    #ACCESOS=$(cut -d " " -f 6,9 log/access.log | sort |uniq -c | grep "$1 200" | cut -d " " -f 3)
    ACCESOS=$(cut -d " " -f 6,9 log/access.log | sort | uniq -c | grep "$1 200" | sed -e 's/^[[:space:]]*//' | cut -d " " -f 1)

    printf "%s %s. Se han registrado %i accesos de tipo %s con respuesta 200." "$fecha" "$HOSTNAME" "$ACCESOS" "$1";echo
fi
#uniq -c |