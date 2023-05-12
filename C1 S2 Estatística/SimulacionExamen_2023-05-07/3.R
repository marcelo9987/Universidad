# Ejercicio 3
library(LearningStats)
pokemon <- read.csv("pokemon.csv")

#a)
sigma_cuadrado <- 920
sigma <- sqrt(sigma_cuadrado)

#IC95 para la media de ATK

Mean.CI(pokemon$ATK, sigma=sigma, conf.level = 0.95)


#b)
Mean.CI(pokemon$ATK, conf.level = 0.95)

#c)
variance.CI(pokemon$ATK,conf.level = 0.99)
