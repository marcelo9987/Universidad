package com.marcelo.b4e1;

import java.util.HashMap;

public final class Thriller extends Accion
{
    /**
     * @param nombre      Nombre de la película.
     * @param anho        Año en el que se ha grabado la película, este debe estar comprendido entre 1895 y 2022.
     * @param duracion    Duración de la película en minutos, esta debe ser de más de 5 minutos.
     * @param director    Director de la película.
     * @param recaudacion Recaudación de la película(No puede ser negativa).
     */
    Thriller(String nombre, Integer anho, Integer duracion, Director director, HashMap<String, Float> recaudacion)
    {
        super(nombre, anho, duracion, director, recaudacion);
    }
}
