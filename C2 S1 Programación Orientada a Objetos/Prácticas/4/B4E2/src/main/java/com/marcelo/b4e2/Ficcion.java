package com.marcelo.b4e2;

import java.util.HashMap;

public final class Ficcion extends Accion
{
    /**
     * @param nombre      Nombre de la película.
     * @param anho        Año en el que se ha grabado la película, este debe estar comprendido entre 1895 y 2022.
     * @param duracion    Duración de la película en minutos, esta debe ser de más de 5 minutos.
     * @param director    Director de la película.
     * @param recaudacion Recaudación de la película(No puede ser negativa).
     */
    Ficcion(String nombre, Integer anho, Integer duracion, Director director, HashMap<String, Float> recaudacion) throws ExcepcionPelicula
    {
        super(nombre, anho, duracion, director, recaudacion);
    }

    @Override
    public boolean exito()
    {
        // Entiendo que un 300% mayor quiere decir que es 4 veces más
        if (recaudacionTotal() <= (1.00 + 3.00) * this.getPresupuesto())
        {
            return false;
        } else
        {
            float recaudacion_FR = this.getRecaudacion().containsKey("Francia") ? this.getRecaudacion().get("Francia") : 0;
            float recaudacion_IT = this.getRecaudacion().containsKey("Italia") ? this.getRecaudacion().get("Italia") : 0;
            float recaudacion_DE = this.getRecaudacion().containsKey("Alemania") ? this.getRecaudacion().get("Alemania") : 0;
            float recaudacion_UK = this.getRecaudacion().containsKey("Reino Unido") ? this.getRecaudacion().get("Reino Unido") : 0;

            float sumaCachesActores = this.getSumaCachesActores();

            if (recaudacion_FR >= 0.2 * sumaCachesActores && recaudacion_IT >= 0.2 * sumaCachesActores && recaudacion_DE >= 0.2 * sumaCachesActores && recaudacion_UK >= 0.2 * sumaCachesActores)
            {
                return true;
            } else
            {
                return false;
            }
        }

    }


}
