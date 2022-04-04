### Ej 2 ###

# A función de densidade
fdens <- function(x)
{
  return((3/4)*(1-x^2))
}

# Comprobamos que integra 1
integrate(fdens,-1,1)

# A función de distribución
Fdist <- function(x)
{
  return((3/4)*x-x^3/4+1/2)
}
Fdist(1)
Fdist(-1)

# Debuxamos as funcións
#     - A de densidade
x <- seq(-1,1,by=0.01)
fdens(x)
plot(x,fdens(x),type='l', main= 'Función de densidade',xlab='x',ylab='Densidade')

#     - A de distribución
plot(x,Fdist(x),type='l')

### Apartado c)

# A P(-0.5 <= x <=1)
# Coa fórmula: 
#P(-0.5 <= x <=1) =  P(X <= 1)- P(X < -0.5)
Fdist(1)-Fdist(-0.5)

# A media: E(x)
f_med <- function(x)
{
  return(x*fdens(x))
}
Ex <- integrate(f_med,-1,1)
Ex

# x tiene varios valores
names(Ex)

fvar <- function(x)
{
  return((x-Ex$value)^2*fdens(x))
}
fvar(0)
# A varianza:
integrate(fvar,-1,1)
