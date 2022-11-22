package com.marcelo.b3e2;

import java.util.HashMap;

public abstract class Comedia extends Pelicula
{
    public Comedia(String nombre, Integer anho, Integer duracion, Director director, HashMap<String, Float> recaudacion)
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
        return this.recaudacionTotal() > this.getPresupuesto();
    }
}
