pokemon <- read.csv("pokemon.csv")
ej4_generation.fabs <- table(pokemon$GENERATION)

ej4_n <- length(pokemon$GENERATION)

ej4_generation.frel <- generation.fabs/ej4_n
ej4_generation.frel

ej4_generation.AccFabs <- cumsum(ej4_generation.fabs)

ej4_generation.AccFrel <- cumsum(ej4_generation.frel)

cbind(ej4_generation.frel,ej4_generation.fabs,ej4_generation.AccFabs,ej4_generation.AccFrel)

pie(ej4_generation.fabs)

barplot(ej4_generation.fabs)

mode(ej4_generation.fabs)
#La moda es 5
