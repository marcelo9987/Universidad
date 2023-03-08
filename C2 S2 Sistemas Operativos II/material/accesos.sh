#!/usr/bin/env bash

#set -x

#Fucion que muestra el formato de los comandos
function muestraUso()
{
  echo ""
  echo "Uso: $0 [-c, GET/POST, -s] ruta"
  echo "Ejemplo: $0 -c access.log"
  echo ""

  exit 1
}

if [[ $# -ne 2 ]]; then
  echo "ERROR: Hacen falta exactamente 2 argumentos"
  muestraUso
fi

#Comprobacion de que los parametros puestos son correctos
if [[ ! (("$1" == "-c") || (("$1" == "GET") || ("$1" == "POST")) || ("$1" == "-s")) ]]; then
  echo "Parametros incorrectos:"
  muestraUso
fi

#Comprobación de que existe -d y se puede leer -r en el archivo
if [[ ! ( -f "$2" && -r "$2" ) ]]
then
    echo "ERROR: El archivo ($2) no existe o no tienes permisos de lectura sobre este"
    muestraUso
fi

#Seleccionamos solo las respuestas del servidor (campo 9)
#Ordenamos alfabeticabente con sort para luego usando uniq para obtener todo el conjunto de respuestas
if [[ "$1" == "-c" ]]; then
  cut -d " " -f 9 "$2" | sort | uniq
fi

#Seleccionamos sobre valor ralizaremos filtro (GET o POST)
if [[ "$1" == "GET" || "$1" == "POST" ]]; then
  #Ponemos el formato indicado por el ejercicio para la fecha
  fecha=$(date +"%h %d %H:%M:%S")
  #Con cut hacemos que solo se quede con todos los campos donde está el tipo y la respuesta
  #despues ordenamos con sort para hacer un uniq -c que nos permita ver la cantidad de ocurrencias que hay
  #con grep filtramos para que solo sean las que tengan de repuesta 200 y del tipo que nos interesan.
  #Como uniq -c da el texto justificado a la derecha es conveniente que nos deshagamos de los espacios que hay antes de poner el numero de ocurrencias con sed
  #Por ultimo usamos otro cut para quedarnos solo con el numero total de Accesos
  ACCESOS=$(cut -d " " -f 6,9 "$2" | sort | uniq -c | grep "$1 200" | sed -e 's/^[[:space:]]*//' | cut -d " " -f 1)

  printf "%s %s. Se han registrado %i accesos de tipo %s con respuesta 200." "$fecha" "$HOSTNAME" "$ACCESOS" "$1"
  echo
fi

if [[ "$1" == "-s" ]]; then
  #Con awk hacemos que sume el numero de Bytes enviados en una variable (sum) y luega imprima parte del texto pedido
  awk '{sum += $10} END {printf "%.0f KiB enviados en ", sum/1024}' "$2"
  #Haceos un -wc para que pueda contar la cantidad de peticiones que hay y luego se hace un cut para quedarnos con ese numero
  echo "$(wc -l "$2" | cut -f 1 -d " ")" peticiones.
fi

#Fucion que muestra el formato de los comandos
function muestraUso() {
  echo ""
  echo "Uso: $0 [-c, GET/POST, -s] ruta"
  echo "Ejemplo $0 -c access.log"
  echo ""

  exit 1
}
