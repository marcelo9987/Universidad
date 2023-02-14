#cargo los datos
  datos <- read.csv('pokemon.csv')
  head(pokemon)

#Nos interesan los datos de la variable ataque
  datos$ATK
  summary(datos$ATK)  
  table
  
#dado el gran numero de datos
#la tratamos como continua.
  
#- Histograma
  
  hist(datos$ATK)
  
#- Diagrama de cajas
  boxplot(datos$ATK)

  
### Cuales son los pokemons con un ataque atípico
attip <- datos$ATK > (quantile(datos$ATK,0.75)+ 1.5*IQR(datos$ATK))
attip  
#Devuelve los pokemons con un ataque atípico
datos[attip,]

### Medidas características
summary(datos$ATK)

### Coeficiente de asimetría
library(moments)
skewness(datos$ATK)

### Ahora con la defensa

# Histograma
hist(datos$DEF,main="Histograma defensa")

#Diagrama de bigotes
boxplot(datos$DEF)

#datos Atípicos

qqatip <- datos$DEF > (quantile(datos$DEF,0.75)+ 1.5*IQR(datos$DEF))
datos[qqatip,]

#medidas características
skewness(datos$DEF)

############################

x <- datos$ATK
y <- datos$DEF

# Diagrama de dispersión
plot(x,y,main="Diagrama de dispersión",xlab="ATK",ylab="DEF",pch=20)
?plot

#A covarianza
covarianza <- 1/nrow(datos) * sum((x-mean(x))*(y-mean(y)))
nrow(datos)
covarianza

#A función cov
cov(x,y)
covarianza2 <- cov(x,y)* (nrow(datos)-1)/nrow(datos)
covarianza2

#Varianza ataque
var.ATK <- var(x)*(nrow(datos)-1)/nrow(datos)

#Varianza defensa
var.DEF <- var(y)*(nrow(datos)-1)/nrow(datos)

#Coeficiente de correlación
r <- covarianza/sqrt(var.ATK*var.DEF)
r

#A función cor
cor(x,y)
  #Esta no la hay que corregir

# Calculamos la recta de regresión
b <- covarianza / var.ATK
b
a <- mean(y)- b*mean(x)
a

abline(a = a,b = b,col ='blue',lwd=2)

#canto se dispersan os valores de defensa
a+b*50
a+b*100
a+b*x[1]
y[1]
y[1] - (a + b*x[1])
y[2] - (a + b*x[2])
residuos<- y - (a + b*x)


#datos atipicos dos residuos
max(residuos)
residuos
atip1.reg <- residuos == max(residuos)
datos[atip1.reg,]

atip2.reg <- residuos == min(residuos)
datos[atip2.reg, ]

#la función lm()
modelo <- lm(y~x)
modelo
a
b

#names()
names(modelo)
modelo$coefficients
modelo$residuals
modelo$residuals == y - modelo$fitted.values


all(modelo$residuals == y - modelo$fitted.values)

###
summary(modelo)
r^2
plot(x,y)
abline(modelo,col='red')

