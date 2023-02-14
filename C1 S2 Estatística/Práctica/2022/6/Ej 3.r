# Xerar un t de Student a partir
# dunha normal e unha chi cuadrado

# Os grados de liberdade
df <- 5
# Os tamaños da mostra
ns <- c(50,100,1000,5000)
for (n in ns)
{
  #A mostra normal estandar
  norm <- rnorm(0,1)
  # A chi cuadrado
  chi <- rchisq(n,df)
  # a mostra de t de student
  t <- norm/sqrt(chi/df)
  # O histograma da mostra t

  # a densidade de T ten 5 graos de liberdade
  x <- seq(min(t),max(t),by=0.01)
  lines(x,dt(x,df=10),colr='red')
}
hist(t,freq=FALSE)