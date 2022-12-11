package com.marcelo.b4e2;

import java.util.HashMap;

public abstract class Comedia extends Pelicula
{
    public Comedia(String nombre, Integer anho, Integer duracion, Director director, HashMap<String, Float> recaudacion) throws ExcepcionPelicula
    {
        super(nombre, anho, duracion, director, recaudacion);
    }

    @Override
    public void presupuesto()
    {
        super.presupuesto();
        this.presupuesto += this.presupuesto * 0.2f;
    }

    @Override
    public boolean exito()
    {
        if(this.recaudacionTotal() > this.getPresupuesto())
        {
            return true;
        }else
        {
            return false;
        }
    }
}
