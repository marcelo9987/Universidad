## Ejercicio 5 ##
datos <- airquality


#viento

par(mfrow=c(1,1))

#Histograma
hist(datos$Wind)

#Diagrama de cajas
boxplot(datos$Wind)

#Diagrama de dispersión
plot(datos$Wind)

#Número de intervalos del histograma
hist(airquality$Wind,breaks=5,col='blue')
hist(airquality$Wind,breaks=10,col='red')
hist(airquality$Wind,breaks=15,col='yellow')
hist(airquality$Wind,breaks=20,col='white')
par(mfrow=c(2,2))

# Hay datos atipicos

atip <- airquality$Wind > quantile(airquality$Wind,0.75) + 1.5*IQR(airquality$Wind)

airquality[atip,]

#es mayor la media que la mediana
mean(airquality$Wind)
median(airquality$Wind)

