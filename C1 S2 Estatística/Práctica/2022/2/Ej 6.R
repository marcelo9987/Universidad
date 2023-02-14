## Ejercicio 6 ##

datosIGE <- read.csv('datosIGE.csv')

#Quedamonos cos datos de Lugo en 2019
datos2019 <- datosIGE[datosIGE$CodTempo == 2019,]
datos2019
datosLugo <- datos2019[datos2019$CodEspazo == 27,]
head(datosLugo)
datosLugoHomes <- datosLugo[datosLugo$Sexo == 'Homes',]
idadeHomes <- rep(0, 973)
idadeHomes <- 0
for (i in 2:nrow(datosLugoHomes))
{
  idadehomes <- c(idadeHomes,rep(i - 1,datosLugoHomes$DatoN[i]))
}
head(idadeHomes)
