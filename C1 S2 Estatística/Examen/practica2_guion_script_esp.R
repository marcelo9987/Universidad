####################
### Ejercicio 1: ###
####################

# Introducimos los datos
satisfaccion <- c("buena", "buena", "regular", "muy buena", "mala", "buena",
                "buena", "regular", "muy mala", "buena", "muy buena", "muy buena",
                "regular", "buena", "mala", "buena", "muy buena", "muy buena", "buena",
                "regular")
# Los convertimos a factor
satisfaccion <- as.factor(satisfaccion)
satisfaccion

# Podemos consultar los niveles del factor con la funcion levels
levels(satisfaccion)
# Por defecto los ordena alfabeticamente.
# Podemos cambiar el orden manualmente
satisfaccion <- factor(satisfaccion, levels=c('muy mala', 'mala', 'regular', 'buena', 'muy buena'))
levels(satisfaccion)
satisfaccion

# Las tablas de frecuencias se construyen con table()

#--- Frecuencias absolutas
Fabs <- table(satisfaccion)
Fabs

#--- Frecuencias relativas
Frel <- table(satisfaccion)/length(satisfaccion)
Frel

# Esta variable discreta tiene un orden natural
# Asi que tiene sentido calcular las frecuencias acumuladas
#--- Frecuencias absolutas acumuladas
FabsAcum<-cumsum(Fabs)
FabsAcum

#--- Frecuencias relativas acumuladas
FrelAcum<-cumsum(Frel)
FrelAcum

# Hay veces que nos interesa tener varios vectores pegados
# para poder comparalos. Para eso estan las funciones cbind y rbind
#--- Tabla conjunta
Tabla<-cbind(Fabs,Frel,FabsAcum,FrelAcum)
Tabla


#--- Representaciones graficas
# Diagrama de barras
barplot(Fabs)   # Con frecuencias absolutas
barplot(Frel)   # Con frecuencias relativas


# Diagrama de sectores
#   Aqui da igual usar las relativas o las absolutas
pie(Fabs)
pie(Frel)

# Podemos cambiar el color de cada sector con col
pie(Fabs, col = c('black', 'red', 'blue', 'turquoise', 'green'))


###################
### Ejercicio 2 ###
###################

# Si no tienes instalado el paquete MASS, tienes que instalarlo con
#   install.packages('MASS')
# Si lo tienes instalado, cargalo con la funcion library()
library(MASS)

# En este paquete estan los datos de quine
head(quine)

# ¡Es un data.frame! Es una mezcla entre lista y matriz.
# Se puede ver el nombre de las variables de quine con names()
names(quine)

# La ayuda de R nos informa de que mide cada variable
?quine

# Si quiero acceder a la variable Sex, puedo hacerlo de dos formas
#   - Indicando el numero de columna
quine[,2]
#   - Indicando el nombre de la variable
quine$Sex
# Yo voy a usar esta ultima

# Hacemos las tablas de frecuencias para Sex y Age por separado
#   - Para la variable Sex
Fabs.sex <- table(quine$Sex)
Frel.sex <- Fabs.sex / nrow(quine)
# No tiene sentido calcular las acumuladas porque
# esta variable no tiene orden natural.
# Pegamos las frecuencias con cbind()
tab.sex <- cbind(Fabs.sex, Frel.sex)
tab.sex

#   - Para la variable Age
Fabs.age <- table(quine$Age)
Frel.age <- Fabs.age / nrow(quine)
# Aqui si tiene sentido calcular las acumuladas
Fabsac.age <- cumsum(Fabs.age)
Frelac.age <- cumsum(Frel.age)
# Pegamos todo con cbind()
tab.age <- cbind(Fabs.age, Frel.age, Fabsac.age, Frelac.age)
tab.age



# table() tambien nos permite facer tablas con dos variables
tab.con <- table(quine$Age, quine$Sex)
tab.con
# Las marginales se calculan con margin.table()
margin.table(tab.con,1) # Por filas
margin.table(tab.con,2) # Por columnas

# Tambien las podemos anhadir a la tabla original con addmargins()
tab.con <- addmargins(tab.con)
tab.con

# Para frecuencias relativas, simplemente dividimos por el numero de la mostra
tab.con.rel <- tab.con/nrow(quine)
tab.con.rel
# Siempre podemos redondear
round(tab.con.rel, 3)

# Graficas para la edad (variable categorica, va por grupos)
barplot(Fabs.age)
pie(Fabs.age)


###################
### Ejercicio 3 ###
###################

# Otros datos
head(geyser)
# Miramos la ayuda para ver lo que mide cada variable
?geyser
# Solo vamos a usar la variable duration
geyser$duration

# Los datos son continuos, y hay que tratarlos como tales.
# La representacion mas habitual es el histograma
hist(geyser$duration)
# Aqui estamos representado las frecuencias absolutas.
# Si queremos las probabilidades, podemos indicarlo con freq = FALSE
hist(geyser$duration,freq = F)

# Tambien podemos controlar el numero de cortes que hace
# para construir el histograma. Y cambiar el color de
# las barras con col
hist(geyser$duration, breaks=5)
hist(geyser$duration, breaks=10, col = 2)
hist(geyser$duration, breaks=25, col = 3)
hist(geyser$duration, breaks=50, col = 4)

# Otra representacion grafica de datos continuos es
# el diagrama de cajas
boxplot(geyser$duration)


### Medidas caracteristicas ###

# La funcion summary nos da varias juntas
summary(geyser$duration)
# Si queremos, podemos calcularlas por separado
#   - La media
mean(geyser$duration)
#   - La mediana
median(geyser$duration)
#   - Cuantiles
quantile(geyser$duration)
# Por defecto calcula
#   * el minimo
#   * el maximo
#   * los cuartiles

# Puedo calcular yo los que quiera con la opcion probs
?quantile
# Por ejemplo, vamos a calcular los deciles
prob <- seq(0, 1, by=0.1)
quantile(geyser$duration, prob)

#   - El minimo
min(geyser$duration)
#   - El maximo
max(geyser$duration)
#   - Rango
max(geyser$duration) - min(geyser$duration)
# Tambien puedo hacer
diff(range(geyser$duration))
#   - El rango intercuartilico
quantile(geyser$duration, 0.75) - quantile(geyser$duration, 0.25)
# Tambien esta la funcion IQR()
IQR(geyser$duration)


#   - La varianza y la desviacion tipica
varianza <- sum((geyser$duration - mean(geyser$duration))^2)/length(geyser$duration)
des.tip <- sqrt(varianza)
varianza
des.tip

# Las funciones var() y sd() devuelven la cuasi-varianza y cuasi-desviacion tipica
var(geyser$duration)
sd(geyser$duration)

# Si quiero calcular la varianza a partir de ellas, solo tengo que 
# multiplicar por el factor correspondiente
var(geyser$duration)*(nrow(geyser) - 1)/nrow(geyser)
sd(geyser$duration)*sqrt((nrow(geyser) - 1)/nrow(geyser))


# En el paquete moments hai funciones para calcular las medidas
# caracteristicas de forma
library(moments)
#   - Coeficiente de Asimetria
skewness(geyser$duration)
#   - Coeficiente de Kurtose
kurtosis(geyser$duration)


###################
### Ejercicio 4 ###
###################

# Separamos entre hombres y mujeres
quine.hom <- quine[quine$Sex == "M",]
quine.muj <- quine[quine$Sex == 'F',]

# Comparacion de medidas caracteristicas
#   - las medias
mean(quine.hom$Days)
mean(quine.muj$Days)
#   - las quasi-varianzas
var(quine.hom$Days)
var(quine.muj$Days)
#   - las varianzas
var(quine.hom$Days)*(nrow(quine.hom)-1)/nrow(quine.hom)
var(quine.muj$Days)*(nrow(quine.muj)-1)/nrow(quine.muj)
#   - si hacemos un summary podemos ver varias
summary(quine.hom$Days)
summary(quine.muj$Days)

# Comparacion grafica
par(mfrow=c(1,2))
hist(quine.hom$Days, main="Hombres", freq=F, col='yellow')
hist(quine.muj$Days, main="Mujeres", freq=F, col='blue')

# Para poder comparar las dos poblaciones
# hay que IGUALAR LA ESCALA DE LOS EJES
par(mfrow=c(1,2))
hist(quine.hom$Days, main="Hombres", freq=F, col='yellow', xlim=c(0,100), ylim=c(0,0.06))
hist(quine.muj$Days, main="Mujeres", freq=F, col='blue', xlim=c(0,100), ylim=c(0,0.06))


# Representamos los boxplots
par(mfrow=c(1,2))
boxplot(quine.hom$Days, ylim=c(0, 90), main="Hombres")
boxplot(quine.muj$Days, ylim=c(0, 90), main="Mujeres")

# Las mujeres tienen mas atipicos. ¿Cuales seran eses datos?
atip <- quine.muj$Days > quantile(quine.muj$Days, 0.75) + 1.5*IQR(quine.muj$Days)
# Los atipico son
quine.muj[atip,]
# Aqui hay informacion importante:
#   - Todas son aborigenes australianas
#   - Casi todas tienen problemas de aprendizaje (SL)
#   - El problema empeora con la edad: cuanto mas mayores, mas atipicos.

###################
### Ejercicio 5 ###
###################


# Los datos de airquality
?airquality
head(airquality)

# Solo nos interesa la variable Wind
x <- airquality$Wind
hist(x, main="Velocidad del viento", freq=F)
boxplot(x, main="Velocidad del viento")

# Si las queremos juntas
par(mfrow=c(1,2))
hist(x, main="Velocidad del viento", freq=F)
boxplot(x, main="Velocidad del viento")

# Los histogramas con 5, 10, 20 y 50 intervalos
par(mfrow=c(2,2))
hist(x,breaks=5)
hist(x,breaks=10)
hist(x,breaks=20)
hist(x,breaks=50)

# Hay valores atipicos?
#  - Si.
# Cuales son?
atip.arriba <- x[x > 1.5*IQR(x) + quantile(x, 0.75)]
atip.arriba
atip.abaixo <- x[x < quantile(x, 0.25) - 1.5*IQR(x)]
atip.abaixo
# Los juntamos
atip <- c(atip.abaixo, atip.arriba)
atip

###################
### Ejercicio 6 ###
###################

# Cargamos los datos:
datosIGE <- read.csv("DatosIGE.csv",sep=",",header=TRUE)
head(datosIGE)
names(datosIGE)

# Escogemos los datos correspondientes la provincia de Lugo y al anho 2019
datosnew <- datosIGE[datosIGE$CodEspazo==27 & datosIGE$CodTempo==2019,]
head(datosnew)

# Creamos una base de datos para hombres y otra para mujeres
datosHomes<-datosnew[datosnew$Sexo=="Homes",]
datosMulleres<-datosnew[datosnew$Sexo=="Mulleres",]
head(datosHomes)
head(datosMulleres)

# Definimos la variable Idade en hombres de 0 a 84 anhos
IdadeHomes <- rep(0, datosHomes$DatoN[1])
for (i in 2:85){
    IdadeHomes<-c(IdadeHomes,rep(i-1,datosHomes$DatoN[i]))
}

# Definimos la variable Idade en mujeres de 0 a 84 anhos
IdadeMulleres<-rep(0,datosMulleres$DatoN[1])
for (i in 2:85){
    IdadeMulleres<-c(IdadeMulleres,rep(i-1,datosMulleres$DatoN[i]))
}

# Representamos los histogramas para ambos grupos
par(mfrow=c(1,2))
hist(IdadeHomes,freq=F,ylim=c(0,0.02),main="Hombres")
hist(IdadeMulleres,freq=F,ylim=c(0,0.02),main="Mujeres")

# Representamos los boxplots para ambos grupos
par(mfrow=c(1,2))
boxplot(IdadeHomes,main="Hombres")
boxplot(IdadeMulleres,main="Mujeres")

# Calculamos las medidas caracteristicas de Idade en ambos grupos
summary(IdadeHomes)
summary(IdadeMulleres)
