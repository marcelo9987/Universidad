package com.marcelo.b4e2;

import java.util.HashMap;

public interface ICPelicula
{
    String getNombre();


    Integer getAnho();


    void setAnho(Integer anho) throws ExcepcionPelicula;


    Integer getDuracion();

    void setDuracion(Integer duracion) throws ExcepcionPelicula;


    HashMap<String, HashMap<String, IActor>> getActores();


    IDirector getDirector();


    float getPresupuesto();


    HashMap<String, Float> getRecaudacion();


    void setRecaudacion(HashMap<String, Float> recaudacion);


}
