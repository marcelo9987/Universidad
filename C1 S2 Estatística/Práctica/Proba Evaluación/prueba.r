datos <- read.csv("schoolyears.csv")
### Ejercico 1 ###
## a)
#Media:
media <- mean(datos$SchoolYr)
#Varianza:
nSY <- length(datos$SchoolYr)
varianza <- (sum((datos$SchoolYr-media)^2))/length(datos$SchoolYr)
# Desviación típica:
desv_std <- sqrt(varianza)

## b)
#histograma:
hist(datos$SchoolYr)

#instalo módulo
install.packages(c("moments"))
library(moments)

asimetría <- skewness((datos$SchoolYr))

# Como o coeficiente de asimetría é mayor que 0,
# o histograma está lixeiramente inclinado á dereita

#c)
#diag. de cajas:
boxplot(datos$SchoolYr)
li <- max(min(datos$SchoolYr),quantile(datos$SchoolYr,0.25)-1.5*(quantile(datos$SchoolYr,0.75) - quantile(datos$SchoolYr,0.25)))
lu <- min(max(datos$SchoolYr),quantile(datos$SchoolYr,0.75)+1.5*(quantile(datos$SchoolYr,0.75) - quantile(datos$SchoolYr,0.25)))

datosAtipicos <- datos[datos$SchoolYr>lu | datos$SchoolYr < li,]
datosAtipicos

#sí, se corresponden con Australia y Nigería

#d)
plot(x=datos$logGDPperCap,y=datos$SchoolYr)
#sí, a mayor GDP, mas años de escolarización
corrCoef <- cor(datos$logGDPperCap,datos$SchoolYr)
# al ser positivo el coeficiente, la relación es positiva, una crecerá con la otra.
reg <- lm(datos$SchoolYr~datos$logGDPperCap)
abline(reg)

### Ejercicio 2: ###
##a)
#P(X=3)
dbinom(3,15,0.3)
#P(X<=10)
probabilidad <-0
for (i in 0:10)
{
  probabilidad <- probabilidad + dbinom(i,15,0.3)
}
probabilidad
#P(2<=X><=11