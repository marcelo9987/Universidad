package com.marcelo.b3e2;

import java.util.*;

public abstract class Pelicula
{
    /// ATRIBUTOS ///
    /**
     * Nombre de la película.
     *
     * @see com.marcelo.b3e2.Pelicula
     */
    private String nombre;

    /**
     * Año en el que se ha grabado la película.
     *
     * @see com.marcelo.b3e2.Pelicula
     */
    private Integer anho;

    /**
     * Duración de la película en minutos.
     *
     * @see com.marcelo.b3e2.Pelicula
     */
    private Integer duracion;

    /**
     * Conjunto de actores que
     * han participado en la película, donde la clave "principal" se usa para obtener el HashMap cpn el
     * conjunto de actores Principales, mientras que la clave "secundario" se usa para obtener el HashMap
     * con el conjunto de actores Secundarios. Además, un actor secundario no puede ser un actor principal
     * y viceversa.
     *
     * @see com.marcelo.b3e2.Pelicula
     */
    private HashMap<String, HashMap<String, Actor>> actores;

    /**
     * Director de la película.
     *
     * @see com.marcelo.b3e2.Pelicula
     */
    private String director;

    /**
     * Presupuesto de la película.
     *
     * @see com.marcelo.b3e2.Pelicula
     */
    protected float presupuesto;

    /**
     * Recaudación de la película
     *
     * @see com.marcelo.b3e2.Pelicula
     */
    private float recaudacion;

    /// CONSTRUCTORES ///

    /**
     * @param nombre      Nombre de la película.
     * @param anho        Año en el que se ha grabado la película, este debe estar comprendido entre 1895 y 2022.
     * @param duracion    Duración de la película en minutos, esta debe ser de más de 5 minutos.
     * @param director    Director de la película.
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
        if (recaudacion < 0)
        {
            System.out.println("ERROR: La recaudación no puede ser negativa");
            return;
        }

        this.nombre = nombre;
        this.anho = anho;
        this.duracion = duracion;
        this.director = director;
        this.recaudacion = recaudacion;
        this.actores = new HashMap<>();
        this.actores.put("principal", new HashMap<>());
        this.actores.put("secundario", new HashMap<>());
        this.presupuesto();
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
        if (anho == null || anho < 1895 || anho > 2022)
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
        if (duracion == null || duracion <= 5)
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
        if (recaudacion < 0)
        {
            System.out.println("ERROR: La recaudación no puede ser negativa");
            return;
        }
        this.recaudacion = recaudacion;
    }

    /// MÉTODOS FUNCIONALES ///

    /**
     * Da de alta a un conjunto de actores. Los argumentos del método son el rol que han jugado los actores en la
     * película (solamente puede tomar el valor de "secundario" o "principal") y un ArrayList de
     * actores. El método devuelve un boolean indicando si el actor ha sido dado de alta o no.
     *
     * @param rol     Rol de los actores en la película.
     * @param actores Actores que han participado en la película.
     * @return "true" en caso de éxito y "false" en caso de fallo. Se considerará un fallo si al menos un actor no es introducido.
     */
    public boolean darAlta(String rol, ArrayList<Actor> actores)
    {
        if (rol == null || actores == null || this.actores == null)
        {
            return false;
        }

        boolean tipoCorrectoActor = false;
        for (String tipo : Actor.TIPOS_DE_ACTORES)
        {
            if (tipo.equals(rol))
            {
                tipoCorrectoActor = true;
                break;
            }
        }
        if (!tipoCorrectoActor)
        {
            return false;
        }

        for (Actor actor : actores)
        {
            if (this.actores.get(rol).containsKey(actor.getNombre()))
            {
                return false;
            }
        }

        for (Actor actor : actores)
        {
            this.actores.get(rol).put(actor.getNombre(), actor);
            actor.getPeliculas().put(this.getNombre(), this);
        }
        this.presupuesto();

        return true;

    }

    /**
     * @param director Director del cual se buscarán los actores
     * @return Conjunto de actores que han sido dirigidos anteriormente (es decir, en otras películas)
     * por el director de la película.
     * @implNote Todos los HashMap deben recorrerse usando un iterator de claves.
     */
    public HashMap<String, Actor> actoresDirigidos(String director)
    {
        //todo: Falta comprobar que los valores no sean nulos.
        //Entiendo que se piden los actores de la película que han sido dirigidos por el director en películas ANTERIORES.
        HashMap<String, Actor> salida = new HashMap<>(0);
        HashMap<String, HashMap<String, Actor>> actoresPelicula = this.getActores();

        if (director == null || actoresPelicula == null)
        {
            return salida;
        }

        for (Iterator<String> keyIteratorTipoActor = actoresPelicula.keySet().iterator(); keyIteratorTipoActor.hasNext(); )
        {
            String tipoActor = keyIteratorTipoActor.next();
            for (Iterator<String> keyIteratorNombreActor = actoresPelicula.get(tipoActor).keySet().iterator(); keyIteratorNombreActor.hasNext(); )
            {
                String nombreActor = keyIteratorNombreActor.next();
                Actor actor = actoresPelicula.get(tipoActor).get(nombreActor);
                if (actor.getPeliculas() == null)
                {
                    continue;
                }
                for (Iterator<String> keyIteratorNombrePelicula = actor.getPeliculas().keySet().iterator(); keyIteratorNombrePelicula.hasNext(); )
                {
                    String nombrePelicula = keyIteratorNombrePelicula.next();
                    if (director.equals(actor.getPeliculas().get(nombrePelicula).getDirector()))
                    {
                        if (!actor.getPeliculas().get(nombrePelicula).equals(this))
                        {
                            salida.put(actor.getNombre(), actor);
                        }
                    }
                }

            }
        }

        return salida;
    }

    /**
     * Actores que han participado
     * en otras películas que no han sido un éxito.
     *
     * @return lista de actores que han participado
     * @implNote Los HashMap se deben recorrer con un iterator de valores.
     */
    //COMPRUÉBAME
    //todo: Revisar
    public Set<Actor> actoresFracaso()
    {
        Set<Actor> salida = new HashSet<>();
        HashMap<String, HashMap<String, Actor>> actoresPelicula = this.getActores();

        if (director == null || actoresPelicula == null)
        {
            return salida;
        }

        for (Iterator<HashMap<String, Actor>> iterator = actoresPelicula.values().iterator(); iterator.hasNext();)
        {
            HashMap<String, Actor> actoresActuales = iterator.next();
            for (Iterator<Actor> actorIterator = actoresActuales.values().iterator(); actorIterator.hasNext();)
            {
                Actor actor = actorIterator.next();

                for (Iterator<Pelicula> valueIterator = actor.getPeliculas().values().iterator(); valueIterator.hasNext();)
                {
                    Pelicula pelicula = valueIterator.next();
                    if(pelicula.equals(this))
                    {
                        continue;
                    }

                    if(!pelicula.exito())
                    {
                        salida.add(actor);
                    }
                }
            }
        }
        return salida;

    }

    /**
     * Indica si la película ha sido o no un éxito. Se considera que una
     * película es un éxito si la recaudación es mayor que el triple del presupuesto.
     *
     * @return true si la película fue un éxito y false en caso contrario.
     */
    public abstract boolean exito();
    /*
    {
        this.presupuesto();
        return this.recaudacion > 3 * this.presupuesto ? true : false;
    }*///todo: Implementar

    /**
     * calcula el presupuesto de la película como la suma del caché
     * de todos los actores más un porcentaje que dependerá del género de la película
     */
    public void presupuesto()
    {
        //t/odo: Comprobar nulidad.

        float sumaCachesActores = 0;
        if (this.actores != null)
        {
            for (HashMap<String, Actor> hashMapActores : this.actores.values())
            {
                for (Actor actor : hashMapActores.values())
                {
                    sumaCachesActores += actor.getCache();
                }
            }
        }

        this.presupuesto = sumaCachesActores;
    }

    @Override
    public String toString()
    {
        String salida = new String();
        boolean primeraCadena = true;

        salida += "{\n";
        if (this.nombre != null)
        {
            salida += "\"nombre\": \"" + this.nombre+"\"";
            primeraCadena = false;
        }

        if (this.anho !=null)
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }

            salida += "\"anho\": " + "\"" + this.anho + "\"";
            primeraCadena = false;
        }

        if(this.duracion != null)
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }

            salida += "\"duracion\": \"" + this.duracion + "\"";
            primeraCadena = false;
        }

        if(this.director != null)
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }

            salida += "\"director\": \"" + this.director + "\"";
            primeraCadena = false;
        }


        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }

            salida += "\"recaudacion\": \"" + this.recaudacion + "\"";
            primeraCadena = false;
        }


        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }

            salida += "\"presupuesto\": \"" + this.presupuesto + "\"";
            primeraCadena = false;
        }

        if (this.actores != null && !this.actores.isEmpty())
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }
            salida += "\"" + "actores" + "\"" + ": " + "[";
            boolean primeraSubCadena = true;
            boolean primeraSubSubCadena = true;

            for(Map.Entry<String, HashMap<String, Actor>> parActores: this.actores.entrySet())
            {
                primeraSubCadena=true;
                String llave = parActores.getKey();
                HashMap<String,Actor> valores = parActores.getValue();

                if(llave == null || valores==null || valores.isEmpty())
                {
                    continue;
                }
                salida+="\n{ \""+llave + "\": [";

                for(String actor: valores.keySet())
                {
                    if (primeraSubCadena == false)
                    {
                        salida += ", ";
                    }
                    salida+= "\""+actor+"\"";
                    primeraSubCadena = false;
                }
                salida+="]";
                salida+="}";
                if (primeraSubSubCadena==true)
                {
                    salida += ", ";
                    primeraSubSubCadena = false;
                }
            }
            salida += "\n]";
            primeraCadena = false;

        }

        return salida;
    }

    @Override
    public boolean equals(Object obj)
    {
        if (this == obj)
        {
            return true;
        }
        if (obj == null)
        {
            return false;
        }
        if (getClass() != obj.getClass())
        {
            return false;
        }
        if (this.nombre == null)
        {
            return false;
        }
        final Pelicula other = (Pelicula) obj;

        if (!this.nombre.equals(other.nombre))
        {
            return false;
        }

        return true;
    }

}



