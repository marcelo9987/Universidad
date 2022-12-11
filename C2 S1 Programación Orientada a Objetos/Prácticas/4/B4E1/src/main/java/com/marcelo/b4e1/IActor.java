package com.marcelo.b4e1;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Set;

public interface IActor extends IParticipante
{
    String getNombre();
    
    ArrayList<String> getDeseos();
    
    void setDeseos(ArrayList<String> deseos);
    
    HashMap<String, IPelicula> getPeliculas();
    
    float getCache();
    
    void setCache(float cache);
    
    Set<IPelicula> peliculasDeGenero(String genero);
    
    ArrayList<IPelicula> peliculasFracaso(String genero);
    
    int importancia(String tipoParticipacion);
    
    float totalGanancias();
    
    Set<String> deseosNoCumplidos();
    
    /**
     * Función que determina si el actor se encuentra entre el reparto de la película.
     * Formal: nombre ∈ pelicula? True:False .
     * @param nombre
     * @param pelicula
     * @return
     */
    static boolean participa(String nombre, IPelicula pelicula)
    {
        if(nombre==null || pelicula == null || pelicula.getActores() == null)
        {
            return false;
        }
        return pelicula.getActores().containsKey(nombre);
    }
    
    
}
