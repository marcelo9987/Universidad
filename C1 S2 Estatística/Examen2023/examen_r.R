### Ejercicio 1 ###

# Primero cargo los datos del csv CalidadAireMadrid2013.csv
datos <- read.csv("CalidadAireMadrid2013.csv", header = TRUE)

#a)
#Calculo la media de la variable O3
O3.media <- mean(datos$O3)
#Imprimo la media
print(O3.media)

#Calcúlo los cuartiles de la variable O3
O3.cuartiles <- quantile(datos$O3)
# Imprimo los cuartiles
print(O3.cuartiles)

#b)
# Hago dos diagramas de caja de la radiación solar en función de si la temporada es Fria o Calida
boxplot(datos$O3 ~ datos$temporada, xlab = "Temporada", ylab = "O3", main = "O3 en función de la temporada")

# Se puede observar que en la temporada Calida hay una mayor concentración de O3 que en la temporada Fria.
# Esto se ve en la caja de arriba, en la que la mediana (la línea negra) esta ubicada en 70, muy por encima de la mediana de la caja hermana.
# Se pueden ver que hay datos atípicos en la temporada Fria, ya que hay puntos por encima de la caja superior.

#c)
#Hacer un diagrama de dispersión de rswm2 (x) contra O3(y)
plot(datos$rswm2, datos$O3, xlab = "rswm2", ylab = "O3")
# Se puede apreciar que estan relacionados de forma que a mayor radiación solar, mayor concentración del nivel de ozono

#Procedo a calcular el coeficiente de correlación para comprobar la relación
rswm2_O3 <- cor(datos$rswm2, datos$O3)
print(rswm2_O3)
# Como el coeficiente de correlación es positivo y cercano a 1, se puede ver que existe una relación lineal positiva entre ellos.

#Calculo la recta de regresión de los datos
recta <- lm(datos$O3 ~ datos$rswm2)
#Dibujo la recta de regresión en el diagrama de dispersión en forma de línea roja.
abline(recta, col = "red")

### Ejercicio 2 ###

#a)
# Primero voy a meter los datos de 'zona' en una variable
zona <- datos$zona

# Ahora voy a calcular las frecuencias absolutas de zona
zona.freq_abs <- table(zona)

# Ahora procedo a la variable 'n'
n <- length(zona)

# Ahora calculo las frecuencias relativas de zona
zona.freq_rel <- zona.freq_abs / n

#Creo una tabla con las frecuencias absolutas y relativas
zona.freq <- cbind(zona.freq_abs, zona.freq_rel)
print(zona.freq)

#b)
#Procedo a crear los dos diagramas

# Diagrama de sectores
pie(zona.freq_abs, labels = names(zona.freq_abs), main = "Zonas de Madrid", col = rainbow(length(zona.freq_abs)))

#diagrama de barras
barplot(zona.freq_rel, main = "Zonas de Madrid", col = rainbow(length(zona.freq_abs)))

# La(s) moda(s) son Corredor Henares y Urbana Sur, ya que son las que tienen mayor frecuencia absoluta.

### Ejercicio 3 ###

#El resultado obtenido de un intervalo de confianza es el rango en el que sabemos con x confianza en el que va a estar el resultado a nuestra pregunta

#a)
#cargo el paquete LearningStats para poder hacer los intervalos de confianza
library(LearningStats)

#IC95 para la media de O3
a3_sigma_cuadrado <- 250
a3_sigma <- sqrt(a3_sigma_cuadrado)

Mean.CI(datos$O3, sigma = a3_sigma, conf.level = 0.95)
#El resultado obtenido es: 50.18408, 60.81347

#b)
#IC95 para la media de O3 con varianza(sigma) desconocida
Mean.CI(datos$O3, conf.level = 0.95)
#El resultado obtenido es: 49.35264, 61.64491

#c)
#IC99 para la varianza de O3
variance.CI(datos$O3, conf.level = 0.99)
#No, el valor 400 no se encuentra dentro del intervalo de confianza, por lo que no podemos asegurar que la varianza pueda ser 400.


### Ejercicio 4 ###

#a)
#La distribución es tal que X~Pois(2)

#P(X == 2)
dpois(2, lambda = 2)
#El resultado es 0.2706706

#P(X <= 2)
ppois(2, lambda = 2)
#El resultado es 0.6766764

#P(1 < X <= 5)
ppois(5, lambda = 2) - ppois(1, lambda = 2)
#El resultado es 0.5774305

#P(X >= 1) = 1 - P(X == 0)
1 - dpois(0, lambda = 2)
#El resultado es 0.8646647

#b)
#Calcular la mediana de una xi cuadrado con 10 grados de libertad
qchisq(0.5, df = 10)
#El resultado es 9.341818

#c)
#Represento la función de densidad de una N(10,4) y N(7,1).

#Para ello, primero creo un vector con los valores de x que quiero representar
x <- seq(3, 15, 0.1)

# Guardo en dos variables las funciones de densidad de las dos normales
dnorm10 <- dnorm(x, mean = 10, sd = 2)
dnorm7 <- dnorm(x, mean = 7, sd = 1)

#Represento las dos funciones de densidad en un mismo gráfico
plot(x, dnorm10, type = 'l', col = 'blue', ylim = c(0, 0.4), xlim = c(3, 15), main = "Distribuciones:")
lines(x, dnorm7, col = 'red')


# XXXXXXXXXXXXXXX #
