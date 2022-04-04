### Ej 6 ###
##apartado a)
?runif
runif(10,0,1)
runif(10)
runif(15,3,4)

##apartado b

?rnorm

# Queremos calcular P(X <= 150)
pnorm(150,160,sqrt(100))

#Calcular onde a normal é menor o igual a 160, con X = N(160,100)
pnorm(160,160,10)


## Apartado c)
datos <- rnorm(100,1,2)
datos
hist(datos)

#Debuxar a función de densidade
# dunha N(1,4)
# Con plot
x <- seq(-5,10,0.01)
fx<- dnorm(x,1,2)
plot(x,fx,type='l')

## Apartado d

x <- seq (-4,4,0.1)
plot(x,dnorm(x,0,1))
plot(x,dnorm(x,0,1),type='l') #stándar
lines(x,dnorm(x,0,sqrt(0.25)),type='l')
lines(x,dnorm(x,0,sqrt(4)),type='l')

## apartado f)
qnorm(0.5,0,1)
qnorm(0.05,0,1)
qnorm(0.8,160,sqrt(64))
