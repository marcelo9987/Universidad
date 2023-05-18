#!/bin/bash

#set -x

muestraUso()
{
    echo ""
    echo "Uso:     $0 ORIGEN DESTINO"
    echo "Ejemplo: $0 conference ~/videos/agrupados_por_sala"
    echo ""

    exit 1
}

# $# es el número de params. Y se comprueba que los dos parámetros necesarios sean introducidos.
if [[ $# -ne 2 ]]
then
    echo "ERROR: Hacen falta exactamente 2 argumentos"
    muestraUso
fi

#establece en dir_origen el parametro 1, que es el origen de los datos
dir_origen=$1

#Comprobación de que existe -d y se puede leer -r en el archivo
if [[ ! ( -d "$dir_origen" && -r "$dir_origen" ) ]]
then
    echo "ERROR: El directorio origen ($dir_origen) no existe o no tienes permisos de lectura sobre este"
    muestraUso
fi

# Almacenamos el segundo parám en dir_destino_base y después comprobamos existencia -d y accesibilidad (escritura -w)
dir_destino_base="$2"

if [[ ! ( -d "$dir_destino_base" && -w "$dir_destino_base" ) ]]
then
    echo "ERROR: El directorio destino ($dir_destino_base) no existe o no tienes permisos de escritura sobre este"
    muestraUso
fi

#volvemos al directorio de origen
cd "$dir_origen" || (echo "ERROR";exit)

# Para todos los archivos en el directorio, coge las fechas (chars. de 8 a 18) y unifica el formato
fechas_distintas=$(for original_file_name in *; do printf "%s\n" "${original_file_name:8:10}"; done | sort -u)

#Vuelve al directorio previo e imprime la salida a un archivo nulo (así no emite ruido a la consola)
cd - > /dev/null

#Comprueba si la variable fechas_distintas está vacía. Si lo está imprime error y finaliza. Si no lo esta, continua la ejecucion
if [[ -z "$fechas_distintas" ]]
then
    echo "No se encontraron ficheros a copiar."
    exit 2
else
    echo "Se crearán directorios para las siguientes fechas: ""$fechas_distintas"
fi

#crea directorios para todas las salas, creando los directorios padre si no existen (-p)
mkdir -p "$dir_destino_base"/s{20..50}

#Creamos los directorios con las fechas y sus calidades
for fecha in $fechas_distintas
do
  mkdir -p "$dir_destino_base"/s{20..50}/"$fecha"
  mkdir -p "$dir_destino_base"/s{20..50}/"$fecha/Full HD"
  mkdir -p "$dir_destino_base"/s{20..50}/"$fecha/HD"
  mkdir -p "$dir_destino_base"/s{20..50}/"$fecha/4K"
  mkdir -p "$dir_destino_base"/s{20..50}/"$fecha/8K"
done

# Creamos OIFS para guardar el IFS (internal field separator) antiguo
OIFS=$IFS

#Por cada archivo en origen:
for original_file_path in "$dir_origen"/*
do
  #Coger solo el nombre de archivo(basename)
    original_file_name=$(basename "$original_file_path")
    # Decirle a bash que separe campos por separados por "_@."
    #Después la función read, separa original_file_name en sala num_sala fecha hora calidad y despues reseteamos el IFS
    IFS="_@." ; read sala num_sala fecha hora calidad <<< "$original_file_name" ; IFS=$OIFS

#   if [ ! -d "$dir_destino_base/$subdir_destino" ]
#   then
#     mkdir -p "$dir_destino_base/$subdir_destino"
#   fi

#   Creamos estas variables para poder copiar los archivos y son respectivamente su posicion y nombre
    subdir_destino="s$num_sala/$fecha/$calidad"
    nombre_destino="charla_${num_sala}_at_$hora.$calidad"

    #imprimimos la operación
    echo "$original_file_path" \=\> "$dir_destino_base/$subdir_destino/$nombre_destino"
    #LLevamos a cabo la copia. Si ya existe, sobreescribe
    cp -f "$original_file_path" "$dir_destino_base/$subdir_destino/$nombre_destino"
done


exit 0

