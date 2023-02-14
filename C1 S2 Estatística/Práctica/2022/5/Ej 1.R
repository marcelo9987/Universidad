# cargo os datos en R
datos <- read.csv('datos_practica5.csv')
head(datos)

# Os datos da primeira columna
x1 <- datos$x1
x1

hist(x1)

# A media
media <- mean(x1)

# A desviación típica
destip <- sqrt(2)

# O tamaño da mostra
n <- length(x1)

# Calculamos o cuantil
# P(X<=Z) = 0.95
z <- qnorm(0.95, 0,1)
z

# O intervalo de confianza para
# a media con nievel 90%
inf <- media - z*destip/sqrt(n)
inf

sup <- media+z*destip/sqrt(n)
sup
sup > media
inf < media

intervalox1 <- c(inf,sup)
intervalox1


#
head(datos)
# A segunda mostra
x2 <- datos$x2

# a media
media <-mean(x2)

#cuasidesviaciontipica
s <- sd(x2)
s
#o num de datos
n<-length(x2)

# O cuantil da T que verífica
# P(T <= t)0.95
t <- qt(0.975,n-1)
t
# Intervalo de confianza para la media para nivel
# de confianza del 95 %
inf <- media - t*s/sqrt(n)
inf

sup <- media + t*s/sqrt(n)
sup

inf<media
sup>media

intervalox2 <- c(inf,sup)
intervalox2


# A mostra x3
x3 <- datos$x3
x3
#cuasi varianza
s<-var(x3)
# o tamaño da mpstra
n <-length(x3)
n
# os cuantis de chi cuadrado
# - P(X<=q1)=0.0115
q1<- qchisq(0.015,n-1)
q1

# -P(X<=q2)=0.985
q2 <- qchisq(.985,n-1)
q2

#intervalo de confianza para la varianza
#con nivel 97%
inf <- ((n-1)/q2)*s2