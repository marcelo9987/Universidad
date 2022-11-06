package com.marcelo.B3E1;

import java.util.*;

public class Actor
{
    /// ATRIBUTOS ///
    private String nombre;
    private ArrayList<String> deseos;
    private HashMap<String, Pelicula> peliculas;
    private float cache;

    /// CONSTRUCTORES ///
    void Pelicula(String nombre, ArrayList<String> deseos, float cache)
    {
        if (nombre == null)
        {
            System.out.println("ERROR: Argumento nulo, no se ha podido crear el objeto");
            return;
        }
        if (cache < 0)
        {
            System.out.println("ERROR: El cache no puede ser negativa");
            return;
        }
        this.nombre = nombre;
        this.deseos = deseos;
        this.cache = cache;
        this.peliculas = new HashMap<>();
    }

    void Pelicula(String nombre, float cache)
    {
        if (nombre == null)
        {
            System.out.println("ERROR: Argumento nulo, no se ha podido crear el objeto");
            return;
        }
        if (cache < 0)
        {
            System.out.println("ERROR: El cache no puede ser negativa");
            return;
        }
        this.nombre = nombre;
        this.cache = cache;
        this.peliculas = new HashMap<>();

    }

    /* GETTERS & SETTERS */

    public String getNombre()
    {
        return nombre;
    }


    public ArrayList<String> getDeseos()
    {
        return deseos;
    }

    public void setDeseos(ArrayList<String> deseos)
    {
        this.deseos = deseos;
    }

    public HashMap<String, Pelicula> getPeliculas()
    {
        return peliculas;
    }

    public float getCache()
    {
        return cache;
    }

    public void setCache(float cache)
    {
        if (cache < 0)
        {
            System.out.println("ERROR: El cache no puede ser negativa");
            return;
        }
        this.cache = cache;
    }
    /// MÉTODOS FUNCIONALES ///

    /**
     * introduce una pelicula
     * en la que ha participado el actor.
     *
     * @param pelicula Pelicula a introducir.
     */
    public void introducirPelicula(Pelicula pelicula)
    {
        if (pelicula == null || this.peliculas.containsKey(pelicula.getNombre()))
        {
            return;
        }
        this.getPeliculas().put(pelicula.getNombre(), pelicula);
    }

    /**
     * Devuelve las
     * películas de un determinado género en las que ha participado el actor.
     *
     * @param genero genero a buscar
     * @return Películas del genero especificado
     */
    public Set<Pelicula> peliculasDeGenero(String genero)
    {
        //PENDIENTE
        Collection<Pelicula> todasLasPeliculas = this.peliculas.values();

        Set<Pelicula> salida = new HashSet<>();
        for(Pelicula pelicula:todasLasPeliculas)
        {

        }
    }
}
