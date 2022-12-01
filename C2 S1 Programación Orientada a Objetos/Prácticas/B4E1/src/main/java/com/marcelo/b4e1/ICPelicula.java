package com.marcelo.b4e1;

import java.util.HashMap;

public interface ICPelicula
{
    String getNombre();


    Integer getAnho();


    void setAnho(Integer anho);


    Integer getDuracion();

    void setDuracion(Integer duracion);


    HashMap<String, HashMap<String, Actor>> getActores();


    Director getDirector();


    float getPresupuesto();


    HashMap<String, Float> getRecaudacion();


    void setRecaudacion(HashMap<String, Float> recaudacion);


}
