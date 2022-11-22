package com.marcelo.b3e2;

import java.util.HashMap;

public abstract class Terror extends Pelicula
{
    /**
     * @param nombre      Nombre de la película.
     * @param anho        Año en el que se ha grabado la película, este debe estar comprendido entre 1895 y 2022.
     * @param duracion    Duración de la película en minutos, esta debe ser de más de 5 minutos.
     * @param director    Director de la película.
     * @param recaudacion Recaudación de la película(No puede ser negativa).
     */
    Terror(String nombre, Integer anho, Integer duracion, Director director,  HashMap<String, Float> recaudacion)
    {
        super(nombre, anho, duracion, director, recaudacion);
    }

    @Override
    //70% de la suma del caché de todos los actores.
    public void presupuesto()
    {
        super.presupuesto();
        this.presupuesto += this.presupuesto * 0.7f;
    }

    /**
     * Indica si la película ha sido o no un éxito. Se considera que una
     * película es un éxito si la recaudación es mayor que el triple del presupuesto.
     *
     * @return true si la película fue un éxito y false en caso contrario.
     */
    @Override
    public boolean exito()
    {
        float sumaCachesActores = 0;
        if (this.getActores() !=  null)
        {
            for (HashMap<String, Actor> hashMapActores : this.getActores().values())
            {
                for (Actor actor : hashMapActores.values())
                {
                    sumaCachesActores += actor.getCache();
                }
            }
        }

        return this.recaudacionTotal() > sumaCachesActores;
    }


}
