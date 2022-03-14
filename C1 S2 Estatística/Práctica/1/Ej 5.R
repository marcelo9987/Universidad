#Ej 5

#instalamos paquetes
install.packages(c('ggplot2','maps','usmap'))
###

library(ggplot2)
library(usmap)
library(maps)
states <- map_data("state")
# Mapa dos estados que forman os EEUU (sen Alaska e Hawaii)
ggplot(data = states) +
  geom_polygon(aes(x=long, y=lat, fill=region, group=group),
               color="white") +
  coord_fixed(1.3) +
  xlab("Lonxitude") +
  ylab("Latitude") +
  ggtitle("Estados Unidos") +
  guides(fill="none")
Jose Ameijeiras, Diego Bolón e Alejandro Saavedra 2
Práctica 1. Introdución a
Guión de prácticas
# Porcentaxe de poboación pobre por estado
povper <- statepov$pct_pov_2014[match(states$region,
                                      tolower(statepov$full))]
# Engadimos esa información ao mapa anterior
ggplot(data = states) +
  geom_polygon(aes(x=long,y=lat, fill=povper, group=group),
               color="white") +
  coord_fixed(1.3) +
  scale_fill_continuous(low = "green", high = "magenta",
                        name = "% de poboación\npobre",
                        labels = seq(10, 20, length.out = 5),
                        breaks = seq(10, 20, length.out = 5)) +
  scale_y_continuous(breaks = NULL, name = NULL) +
  scale_x_continuous(breaks = NULL, name = NULL) +
  ggtitle("Porcentaxe de poboación por debaixo\n
do umbral da pobreza") +
  theme(legend.position = "right",
        plot.title = element_text(face = "bold", size = rel(1.5),
                                  hjust = 0.5))