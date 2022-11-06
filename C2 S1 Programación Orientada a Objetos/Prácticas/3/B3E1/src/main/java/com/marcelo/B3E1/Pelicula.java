package com.marcelo.B3E1;

import java.util.ArrayList;
import java.util.HashMap;

public class Pelicula
{
    public static final String TIPOS_DE_ACTORES[]={"principal","secundario"};
    /// ATRIBUTOS ///
    /**
     * Nombre de la película.
     *
     * @see com.marcelo.B3E1.Pelicula
     */
    private String nombre;

    /**
     * Año en el que se ha grabado la película.
     *
     * @see com.marcelo.B3E1.Pelicula
     */
    private Integer anho;

    /**
     * Duración de la película en minutos.
     *
     * @see com.marcelo.B3E1.Pelicula
     */
    private Integer duracion;

    /**
     * Conjunto de actores que
     * han participado en la película, donde la clave "principal" se usa para obtener el HashMap cpn el
     * conjunto de actores principales, mientras que la clave "secundario" se usa para obtener el HashMap
     * con el conjunto de actores secundarios. Además, un actor secundario no puede ser un actor principal
     * y viceversa.
     *
     * @see com.marcelo.B3E1.Pelicula
     */
    private HashMap<String, HashMap<String, Actor>> actores;

    /**
     * Director de la película.
     *
     * @see com.marcelo.B3E1.Pelicula
     */
    private String director;

    /**
     * Presupuesto de la película.
     *
     * @see com.marcelo.B3E1.Pelicula
     */
    private float presupuesto;

    /**
     * Recaudación de la película
     *
     * @see com.marcelo.B3E1.Pelicula
     */
    private float recaudacion;

    /// CONSTRUCTORES ///

    /**
     *
     * @param nombre Nombre de la película.
     * @param anho Año en el que se ha grabado la película, este debe estar comprendido entre 1895 y 2022.
     * @param duracion  Duración de la película en minutos, esta debe ser de más de 5 minutos.
     * @param director Director de la película.
     * @param recaudacion Recaudación de la película(No puede ser negativa).
     */
    Pelicula(String nombre, Integer anho, Integer duracion, String director, float recaudacion)
    {
        if (nombre == null || anho == null || duracion == null || director == null)
        {
            System.out.println("ERROR: Argumento nulo, no se ha podido crear el objeto");
            return;
        }

        if (anho < 1895 || anho > 2022)
        {
            System.out.println("ERROR: Película fuera del rango temporal, no se ha podido crear el objeto");
            return;
        }
        if (duracion <= 5)
        {
            System.out.println("ERROR: Las peliculas han de ser de más de 5min, no se ha podido crear el objeto");
            return;
        }
        if(recaudacion<0)
        {
            System.out.println("ERROR: La recaudación no puede ser negativa");
            return;
        }

        this.nombre = nombre;
        this.anho = anho;
        this.duracion = duracion;
        this.director = director;
        this.recaudacion = recaudacion;
    }
    /// GETTERS & SETTERS ///

    public String getNombre()
    {
        return nombre;
    }

    public Integer getAnho()
    {
        return anho;
    }

    public void setAnho(Integer anho)
    {
        if (anho < 1895 || anho > 2022)
        {
            System.out.println("ERROR: Película fuera del rango temporal.");
            return;
        }
        this.anho = anho;
    }

    public Integer getDuracion()
    {
        return duracion;
    }

    public void setDuracion(Integer duracion)
    {
        if (duracion <= 5)
        {
            System.out.println("ERROR: Las peliculas han de ser de más de 5min.");
            return;
        }
        this.duracion = duracion;
    }

    public HashMap<String, HashMap<String, Actor>> getActores()
    {
        return actores;
    }

    public String getDirector()
    {
        return director;
    }

    public float getPresupuesto()
    {
        return presupuesto;
    }

    public float getRecaudacion()
    {
        return recaudacion;
    }

    public void setRecaudacion(float recaudacion)
    {
        if(recaudacion<0)
        {
            System.out.println("ERROR: La recaudación no puede ser negativa");
            return;
        }
        this.recaudacion = recaudacion;
    }

    /// MÉTODOS FUNCIONALES ///

    /**
     *  Da de alta a un conjunto de actores. Los argumentos del método son el rol que han jugado los actores en la
     *     película (solamente puede tomar el valor de "secundario" o "principal") y un ArrayList de
     *     actores. El método devuelve un boolean indicando si el actor ha sido dado de alta o no.
     * @param rol Rol de los actores en la película.
     * @param actores Actores que han participado en la película.
     * @return "true" en caso de éxito y "false" en caso de fallo.
     */
    public boolean darAlta(String rol, ArrayList<Actor> actores)
    {
        if(rol==null || actores==null)
        {
            return false;
        }

        boolean tipoCorrectoActor = false;
        for(String tipo:TIPOS_DE_ACTORES)
        {
            if(tipo.equals(rol))
            {
                tipoCorrectoActor=true;
                break;
            }
        }
        if(!tipoCorrectoActor)
        {
            return false;
        }


    }

}
