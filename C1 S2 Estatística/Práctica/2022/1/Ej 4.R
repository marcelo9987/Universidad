#Ej 4
exer4 <- function(n)
{
  letras <- 'abcdefghijklmnñopqrstuvwxyz'
  letras <- strsplit(letras, split = '')[[1]]
  sorteo <- sample(letras,size = n,replace = 1)
  palabra <- paste (sorteo,sep='',collapse='')
  return(palabra)
}
exer4(2)
exer4(7)
exer4(100)
exer4(1*10^6)
