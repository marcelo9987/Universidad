## Ejercicio 3 ##


# Imos ver como traballa R coas
# Distribucións máis coñecidas

# Discretas
#   -Con dxxx calculo a masa de probabilidade
dbinom(0,3,0.5)
dbinom(4,4,0.5)
? dbinom

#   -con pxxx calculo a función de 
#   - distribución P(x<=x)
pbinom(1,3,0.5) 
pbinom(0,3,0.5) + dbinom(1,3,0.5) 
pbinom(2,4,0.5)

# con rxxx xero valores aleatorios
# da distribución
rbinom(10,3,0.5)

# qxxx calcula la funcion cuantil
qbinom(0.5,3,0.5)
qbinom(0.55,3,0.5)


## apartado a)
rbinom(10,6,0.3)

### apartado b)

# Coa distribución
pbinom(4,6,0.3)

# Apartado c)
#P(3<=x<=5)
pbinom(5,6,0.3)-pbinom(3,6,0.3)

# Apartado d)

?rbinom
rnbinom(4,8,0.4)

#Apartado e)
rnbinom(4,8,0.6)

#apartado g)
?rpois

# calcular a posibilidade
#P(X>=4) con X = Pois(2)
1-ppois(3,2)


