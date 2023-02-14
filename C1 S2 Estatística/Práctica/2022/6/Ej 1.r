#ejercicio 1

# Generar 500 muestras de una N(160,64)
# de tamaño n = 100

#o tamaño de mostras
n<-100

#O num de mostras
rep <- 500
# Os parámetros
mu<- 160
sigma<-8

est <- 1:rep
# O bucle
for(i in 1:rep)
{
  #xero nha mostra normal
  x<- rnorm(n,mu,sigma)
  #Gardo o valor do estadístico
  # para esta mostra
  est[i] <- (mean(x) - mu)/(sigma/sqrt(n))

}
#histograma de est
hist(est,freq=FALSE)
#debuxo a densiadade da normal estandar
# por encima de N(0,1)
x <- seq( min(est), max(est), by=0.01)
lines(x, dnorm(x,0,1))

