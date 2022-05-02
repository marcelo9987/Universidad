#Exericio 2

# O numero de mostras
rep <- 500

# Os parametros da normal
mu <-3
sigma<- 1/2
# O tamaño da mostra(0,10,20,50)
n <- 5

est <- 1:rep

for (i in 1:rep)
{
  # Xerar os datos N(3,0.25)
  x <- rnorm(n,mu,sigma)
  # calcular o estadístico
  est[i] <- (n-1) * var(x)/sigma^2
}

# o histograma de est
hist(est,freq=FALSE)

# A funcion de densidade
# dunha chi cuadrado de n-1 grados de lib.
x<-seq(min(est),max(est),by=0.01)
lines(x,dchisq(x,n-1),col='red')


