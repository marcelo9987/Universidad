#1)
# carga archivo
datos <- read.csv("espvida.csv")
#a)
# media:
espVida.media <- mean(datos$espvida)
espVida.media
#mediana
espVida.mediana <- median(datos$espvida)
espVida.mediana

# varianza:
espVida.varianza <- sum((datos$espvida - mean(datos$espvida))^2)/length(datos$espvida)
espVida.varianza

# desviacion típica
espVida.desviacionTip <- sqrt(espVida.varianza)
espVida.desviacionTip

#b)
#Diagrama de cajas:
boxplot(datos$gastosan)
# Sí, hay datos atípicos.
datosAtipicos <- datos[(datos$gastosan  > quantile(datos$gastosan, 0.75) + 1.5*IQR(datos$gastosan)),]
datosAtipicos
# Los datos Atípicos son de Estados unidos.
#c)
#Diagrama de dispersión:
plot(datos$gastosan,datos$espvida)
# Parecen tener una relación directa.
# coeficiente de correlación:
corcoef <- cor(datos$gastosan,datos$espvida)
corcoef
# AL ser positivo, el coeficiente de correlación indica que la relación es directamente proporcional,
# es decir, que uno incrementa con el otro de forma porporcional.



#2)
#a)
# P(x=2)
resultado1<- dbinom(2,10,0.167)
resultado1
# 0.2909414

#P (x<=3)
resultado2 <- sum(dbinom(0:3, 10, 0.167))
resultado2
# 0.9298372

# P(5<X<=10)
resultado3 <- sum(dbinom(6:10, 10, 0.167))
resultado3
# 0.002464314
#b)
  #P(X<=1.96)
resultado21 <- sum(dnorm(0:1.96,0,1))
resultado21
# 0.640913

#P(X<=-0.5)
resultado22 <- dnorm(0:-0.5,0,1)
resultado22
# 0.3989423

# P(-3<=X<=3)
resultado23 <- sum(dnorm(-3:3, 0, 1))
resultado23
#0.9997

#P(X=>-1.5)
resultado24 <- sum(dnorm(0:-1.5,0,1))
resultado24
#0.640913

#a)
media <- mean(swiss$Fertility)
confianza <- 0.95
alfa <- 1-confianza


z <- qnorm(1-alfa/2,mean=0,sd=10)


des_est <- 10/sqrt(n)
des_est

intervalo_inferior <- media-z*des_est
intervalor_superior <- media+z*des_est
intervalo <- c(inf, sup)
intervalo

# el intervalo es (-130.9455,271.2306)

#b)

Fertilidad <- swiss$Fertility

# tamaño de la muestra
n <- length(Fertilidad)
n
# media de la muestra
media <- mean(Fertilidad)
media
# Cuasidesviación estándar
cuasidstd <- sd(Fertilidad)
desv_std <- cuasidstd/sqrt(n)
desv_std

# 95%
nivel <- 0.95
alfa <- 1-nivel


t <- qt(1 - alfa/2, df = n - 1)
inf <- media-t*desv_std
sup <- media+t*desv_std
intervalo <- c(inf, sup)
intervalo
# el intervalo es: (66.47485,73.81025)

# c)
nivel <- 0.97
alfa <- 1-nivel

quant1 <- qchisq(alfa/2, df = n-1)
quant2 <- qchisq(1 - alfa/2, df = n-1)
inf <- (n-1)*var(Fertilidad)/quant2
sup <- (n-1)*var(Fertilidad)/quant1
intervalo_varianza=c(inf, sup)
intervalo_varianza


intervalo_ <- sqrt(intervalo_varianza)
intervalo_
# intervalo de confianza: (10.18306,16.09595)

# 4:
#a)
tabla.frecAbs <- table(mtcars$cyl)
tabla.frecRel <-table(mtcars$cyl)/length(mtcars$cyl)
tabla.frecAbsAcc <- cumsum(tabla.frecAbs)
tabla.frecRelAcc <- cumsum(tabla.frecRel)
Tabla<-cbind(tabla.frecAbs,tabla.frecRel,tabla.frecAbsAcc,tabla.frecRelAcc)
Tabla

#b)
# diagrama de sectores:
pie(tabla.frecAbs)
pie(tabla.frecRel)
# diagrama de barras:
barplot(tabla.frecAbs)
barplot(tabla.frecRel)
# La moda es 8, ya que es el valor que más se repite
