#Ej3
Hcts <- c(0.8,1.1,0.6,3.2,1.4,2.1,1.5,0.2,1.0,6.1)
Ocup <- c(1200,650,1060,235,1300,300,750,150,440,500)

length(Ocup)
length(Hcts)

#Diagrama de dispersion: plot()
plot(Hcts,Ocup)
zona <- c(1,1,1,2,3,2,3,3,3,2)
length(zona)
#Ahora con colorinchos
plot(Hcts,Ocup,col= zona)
media.hec <- mean(Hcts)
media.hec
abline(v=media.hec)
abline(h = mean(Ocup),col = 'blue')
