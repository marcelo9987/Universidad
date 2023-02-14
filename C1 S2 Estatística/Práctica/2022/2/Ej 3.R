library(MASS)
?geyser
head(geyser)

#Representación gráfica dos datos
#   - Histograma
hist(geyser$duration)
hist(geyser$duration,freq=FALSE)
rug(geyser$duration)
abline(v = mean(geyser$duration),col='red',lty = 2)
hist(geyser$duration,breaks=4)
nrow(geyser)

#- Diagrama de cajas y bigotes
boxplot(geyser)

#-As medidas características
#- A media
mean(geyser$duration)
#- A mediana
median(geyser$duration)
#- Cuantiles
quantile(geyser$duration)

#Podo escoller eu as probabilidades
?quantile
seq(0,1,0.25)
probs <- seq(0,1,0.1)
# de 10 en 10%
quantile(geyser$duration,probs)
#15%
quantile(geyser$duration,0.15)


# - O máximo e o mínimo
quantile(geyser$duration, 0)
quantile(geyser$duration, 1)
min(geyser$duration)
max(geyser$duration)
#     - O rango
geyser$duration.range <- max(geyser$duration)-min(geyser$duration)
#Rango Interquartílico
quantile(geyser$duration,0.75)-quantile(geyser$duration,.25)
IQR(geyser$duration)
# - varianza e desviacion típica
varianza <- 1/length(geyser$duration) * sum( (geyser$duration - mean(geyser$duration))^2 )
varianza

sd <- sqrt(varianza)
sd

#Hai funcións en R para facer isto
var(geyser$duration)
sd(geyser$duration)
#Pasar de cuasi-varianza a varianza
varianza2 <- var(geyser$duration)*((length(geyser$duration)-1) / length(geyser$duration))
sd2 <- sqrt(varianza2)                      
sd2

install.packages('moments')
library('moments')
#    -Asimetría
skewness(geyser$duration)
# -kurtosis
kurtosis(geyser$duration)

#A función summmary calcula varias funciones características
summary(geyser$duration)
