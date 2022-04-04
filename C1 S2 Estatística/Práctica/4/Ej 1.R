### Exercicio 1 ###
## a)

# O soporte:
x <- 1:6
# A masa de probabilidade
Mx <- c(11/36, 9/36, 7/36, 5/36, 3/36,1/36)
# A función de distribución
# Para cada x devolve P(X<=x)
Distx <- cumsum(Mx)
Mx
Distx

# Representamos estas funcións en R
#     -A masa de probabilidade
# Cun díagrama de barras
barplot(Mx,main = 'a',names=1:6,ylab='probabilidade')

#cun plot
plot(x,Mx)

# A función de distribución
# F(x) = P(X <= x)
plot(
  x, 
  Distx,
  type='s',
  xlim=c(0.5,6.5),
  ylim=c(0,1)
  )
segments(0.5,0,1,0)
segments(1,0,1,Mx[1])
segments(6,1,6.5,1)

### Apartado b)
#media
x
Mx
mean (Mx)
x[1]*Mx[1]*x[2]*Mx[2]+...
Ex<-sum(x*Mx)
#varianza
Varx <- sum((x-Ex)^2 * Mx)
Varx
# Coa outra fórmula
Var2x <-sum(x^2*Mx) - Ex^2
