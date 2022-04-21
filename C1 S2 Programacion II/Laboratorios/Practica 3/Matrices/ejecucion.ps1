Write-Host "Inicio de programa";
#mingw32-make.exe

$min = Read-Host  "Mínimo"
$max = Read-Host  "Máximo"
$paso = Read-Host  "Paso"

mingw32-make.exe

.\P3_Matrices.exe $min $max $paso

$nombreMult = "tiemposMultMatrices_"+"$min"+"_"+"$max"+"_"+"$paso"+".txt"
ren "tiemposMultMatrices.txt" $nombreMult

$nombreSum = "tiemposSumaMatrices_"+"$min"+"_"+"$max"+"_"+"$paso"+".txt"
ren "tiemposMultMatrices.txt" $nombreSum
#./P3_Matrices.exe