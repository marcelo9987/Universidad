## Ejercicio 4##

library(MASS)
head(quine)

?quine

quine.mull <- quine[quine$Sex=='F',]
quine.mull

quine.hom <- quine[quine$Sex=='M',]
quine.hom

x <-  quine.hom$Days
y <- quine.mull$Days
table(x)
barplot(x)

#Imos pensar que a variable é continua
  #- Hisotgrama
par(mfrow = c(1,2))
hist(quine.hom$Days, main = 'Hombres',xlim=c(0,90),ylim=c(0,50))
hist(quine.mull$Days,main = 'Mujeres',xlim=c(0,90),ylim=c(0,50))

# -Diagrama de caja
par(mfrow = c(1,2))
boxplot(x,main="Hombres",ylim=c(0,90))
boxplot(y,main="Mujeres",ylim=c(0,90))


#Cuales son los datos atípicos de las mujeres
atip.mull <- quine.mull$Days > quantile(quine.mull$Days,0.75)+1.5*IQR(quine.mull$Days)

quine.mull[atip.mull,]


#Comparar medidas características
summary(quine.hom$Days)
summary(quine.mull$Days)
