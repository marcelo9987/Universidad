
function llamar_programa()                                                                         
{
       "./${2}" $3 $4 >> resultados.data
}

for((i = 0;i <= $1;i++));
do
        llamar_programa $1 $2 $3 $4
done

