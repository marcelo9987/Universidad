#Ej 1
#a)
schoolYears <- read.csv("schoolyears.csv")

schoolYr <- schoolYears$SchoolYr

schoolYr.n <- NROW(schoolYr)

schoolYr.media <- mean(schoolYr)

schooYr.mediana <- median(schoolYr)

schoolYr.var <- var(schoolYr) * ((schoolYr.n-1)/schoolYr.n) 

schoolYr.sd <- sqrt(schoolYr.var)

#b)
install.packages("moments") #lo uso para sacar el skewness (coef de asimetría)
library(moments)

hist(schoolYr, col="blue",main="Diagrama de caja", xlab="Escolarización esperada / país")
schoolYr.asimetria <- skewness(schoolYr)
print(schoolYr.asimetria)
#agostino.test(schoolYr)
# Como el coef de asimetría da muy cerca de 0 (0.00398) podemos afirmar que es simétrica (o muy poco asimétrica)

#c)
boxplot(schoolYr, col="blue",main="Diagrama de caja", xlab="Escolarización esperada / país")

schoolYr.datos_atipicos <- schoolYr > quantile(schoolYr, 0.75) + 1.5*IQR(schoolYr) | schoolYr < quantile(schoolYr, 0.25) - 1.5*IQR(schoolYr)
#sí, hay 2 datos atípicos

paisesAtipicos <- schoolYears$Country[schoolYr.datos_atipicos]

print("los paises con datos atípicos son:")
sprintf("%s: %g", paisesAtipicos, schoolYears$SchoolYr[schoolYr.datos_atipicos])


#d)
plot(schoolYears$logGDPperCap,schoolYr)
#si, ...
cor(schoolYears$logGDPperCap,schoolYr)
# como es mayor que 0 y cercano a 1, hay una fuerte correlación positiva (a más x, más y)

#e)
schoolYr.reg <- lm(schoolYr~schoolYears$logGDPperCap)
plot(schoolYears$logGDPperCap,schoolYr)
abline(schoolYr.reg,col="red",lwd=2)
sprintf("Los coeficientes de la recta de regresión son:")
schoolYr.reg$coefficients



