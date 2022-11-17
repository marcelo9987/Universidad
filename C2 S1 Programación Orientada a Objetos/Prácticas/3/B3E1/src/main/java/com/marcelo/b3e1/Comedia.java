package com.marcelo.b3e1;

public class Comedia extends Pelicula
{
    public Comedia(String nombre, Integer anho, Integer duracion, String director, float recaudacion)
    {
        super(nombre, anho, duracion, director, recaudacion);
    }

    @Override
    public void presupuesto()
    {
        super.presupuesto();
        this.presupuesto += this.presupuesto * 0.2f;
    }
}
