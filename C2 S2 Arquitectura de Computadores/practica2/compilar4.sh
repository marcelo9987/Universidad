
#gcc "$1".c  -o "$1".out -O0 -march=native -Wall
# Ahora para permitir expansiones de shell y asi compilar varios archivos
for archivo in "$@"
do
  gcc "$archivo"  -o "${archivo%.*}".out -O0 -march=native -fopenmp -Wall -D MEDIR_CICLOS
done

