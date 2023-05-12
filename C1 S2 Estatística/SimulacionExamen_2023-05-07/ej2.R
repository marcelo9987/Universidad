#2)

#a)
#P(X = 3)
dbinom(3, 15, 0.3)

#P(X <= 10)
pbinom(10, 15, 0.3)

#P(2 <= X <= 11)
sum(dbinom(2:11, 15, 0.3))

# P(X >= 5) = 1 - P(X < 5)
1 - pbinom(4, 15, 0.3)

#b)
rnbinom(10, 3, 0.5)

#c)
#P(X >= 0) = 1 - P( X < 0) 
1 - pnorm(0, 0, 5)

#P(x<=3)
pnorm(3, 0, 5)

#P(-1 <= X <= 1)
pnorm(1, 0, 5) - pnorm(-1, 0, 5)

#P(X >= 4) = 1 - P(X < 4)
1 - pnorm(4, 0, 5)

#d)
qt(0.8, 5)

#e)
plot(-5:7, dnorm( -5:7, 1, sqrt(2) ) )
# La densidad de la normal por encima

mu <- 1
sigma2 <- 2
x <- seq(-5, 7, by = 0.1)
lines(x, dnorm(x, mu, sqrt(sigma2)), col = 2)
