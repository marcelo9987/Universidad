#apartado 1
t <- c(0,0.25,0.5,0.75)

t

#apartado 2
res1 <-0
res1 <- sum(t^2)

sin(2*pi*t)


#exercicio 1 apartado b

#inicializamos la var.
esp.vida <- c(83.2,82.5,83,83.4,82.4,81.4,81.4,81.8,81.6)
names(esp.vida) <- c('Espa??a','Francia','Italia','Suiza','Luxemburgo','B??lgica','Reino Unido','Irlanda','Portugal')
# esperanza de mida media
media <- sum(esp.vida)/length(esp.vida)
media <- mean(esp.vida)
media

#Seleccionar aquellos elementos por encima de la esperanza de vida media
esp.vida > media
esp.vida[esp.vida > media]
esp.vida[esp.vida < media]

# Exercicio 1 apartado c

#Cargamos as matrices
A <- matrix(c(1:16),ncol=4,nrow=4,byrow=TRUE )
A
B <- matrix(c(1:16),ncol=4,nrow=4)
B

B<-t(A)
B

#Producto matricial
C <- A%*%B
C

#Determinante
determinante <- det(C)
determinante
#inversa de C
?solve
solve(C)
#NON ?? INVERTIBLE
?eigen
eigen(C)
autovalores = eigen(C)$values
autovalores
#deter = pdto de autovalores
determinante
prod(autovalores)
#traza = suma de autovalores
sum(autovalores)
#tarza por un bucle
traza <- 0
for (i in 1:4)
{
  traza <- traza + C[i,i]
}
traza
#traza por diag()
sum(diag(C))
