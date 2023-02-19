#!/bin/bash

muestraUso()
{
    echo ""
    echo "Uso:     $0 ORIGEN DESTINO"
    echo "Ejemplo: $0 conference ~/videos/agrupados_por_sala"
    echo ""

    exit 1
}

if [[ $# -ne 2 ]]
then
    echo "ERROR: Hacen falta exactamente 2 argumentos"
    muestraUso
fi

dir_origen=$1

if [[ ! ( -d $dir_origen && -r $dir_origen ) ]]
then
    echo "ERROR: El directorio origen ($dir_origen) no existe o no tienes permisos de lectura sobre este" 
    muestraUso
fi

dir_destino_base=$2

if [[ ! ( -d $dir_destino_base && -w $dir_destino_base ) ]]
then
    echo "ERROR: El directorio destino ($dir_destino_base) no existe o no tienes permisos de escritura sobre este" 
    muestraUso
fi

cd $dir_origen

fechas_distintas=$(for original_file_name in *; do printf "%s\n" "${original_file_name:8:10}"; done | sort -u)

cd - > /dev/null

if [[ -z $fechas_distintas ]]
then
    echo "No se encontraron ficheros a copiar."
    exit 2
else
    echo "Se crearán directorios para las siguientes fechas: "$fechas_distintas
fi

mkdir -p "$dir_destino_base"/s{20..50}

for fecha in $fechas_distintas 
do
  mkdir -p "$dir_destino_base"/s{20..50}/$fecha
done


OIFS=$IFS

for original_file_path in $dir_origen/* 
do
    original_file_name=$(basename "$original_file_path")
    IFS="_@." ; read sala num_sala fecha hora calidad <<< $original_file_name ; IFS=$OIFS 
    #echo s $sala n $num_sala f $fecha h $hora c $calidad
    
    subdir_destino="s$num_sala/$fecha/$calidad"
    nombre_destino="charla_${num_sala}_at_$hora.$calidad"
   
    if [ ! -d "$dir_destino_base/$subdir_destino" ] 
    then
      mkdir -p "$dir_destino_base/$subdir_destino"
    fi 
    
    echo "$original_file_path" \=\> "$dir_destino_base/$subdir_destino/$nombre_destino"
    cp -f "$original_file_path" "$dir_destino_base/$subdir_destino/$nombre_destino"
    #echo "------------------------------------------------------------------"
done


exit 0

