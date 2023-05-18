#!/bin/bash
# Usa $IFS para dividir la línea que se está leyendo
# por defecto, la separación es "espacio"
echo "Lista de todos los usuarios:"
OIFS=$IFS # Salva el valor de IFS
IFS=: # /etc/passwd usa ":" para separar los campos
cat /etc/passwd | 
    while read name passwd uid gid fullname ignore
    do
        echo "$name ($fullname)"
    done
IFS=$OIFS # Recupera el $IFS original

