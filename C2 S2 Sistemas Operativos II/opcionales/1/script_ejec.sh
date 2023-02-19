#el primer param es el numero de iters.
# el segundo param es el programa compilado
# el 3er param es el numero de la suma
# el 4 param es el num de hilos
function llamar_programa()                                                                         
{
       "./${2}" $3 $4 >> resultados.M_$3.T_$4.data
}

for((i = 0;i <= $1;i++));
do
        llamar_programa $1 $2 $3 $4
done

