install.packages('MASS')
library('MASS')
quine
head(quine)
?quine
quine$Sex

# As táboas de frecuencia para a idade absoluta
Fabs.age <- table(quine$Age)
Fabs.age

# A relativa
Frel.age <- Fabs.age/length(quine$Age)
Frel.age

Frel.age <- Fabs.age/nrow(quine$Age)
Frel.age

#As táboas para o sexo
#Absoluta
Fabs.sexo <- table(quine$Sex)
Fabs.sexo
#Relativa
Frel.sexo <- Fabs.sexo/length(quine$Sex)
Frel.sexo

#a taboa de continxencia para sexo e idade
Tab.con <- table(quine$Sex,quine$Age)
Tab.con

#A táboa de continxencia relativa
Tab.con/length(quine$Sex)

margin.table(Tab.con, 1)
margin.table(Tab.con, 2)

#Pegar marxinais á táboa orixinal
Tab.con <- addmargins(Tab.con)
Tab.con

#En frecuencias relativas
Tab.con/length(quine$Age)
# Redondeo
round(Tab.con/length(quine$Sex),3)


#Representamos gráficamente a idadade
barplot(Fabs.age)

#gráfico de sectores
pie(Fabs.age,col=4:8)

geyser
