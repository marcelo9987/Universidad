package com.marcelo.b3e2;

public class ComediaNegra extends Comedia
{


    public ComediaNegra(String nombre, Integer anho, Integer duracion, String director, float recaudacion)
    {
        super(nombre, anho, duracion, director, recaudacion);
    }

    /**
     * @return devuelve si la película ha sido un éxito(true) o no (false)
     */
    @Override
    public boolean exito()
    {
        this.presupuesto();
        return this.getRecaudacion() > 3 * this.presupuesto ? true : false;
    }
}
