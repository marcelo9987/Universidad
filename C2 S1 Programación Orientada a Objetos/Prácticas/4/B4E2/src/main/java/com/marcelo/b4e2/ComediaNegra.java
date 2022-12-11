package com.marcelo.b4e2;

import java.util.HashMap;

public final class ComediaNegra extends Comedia
{
    public ComediaNegra(String nombre, Integer anho, Integer duracion, Director director, HashMap<String, Float> recaudacion) throws ExcepcionPelicula
    {
        super(nombre, anho, duracion, director, recaudacion);
    }

}
