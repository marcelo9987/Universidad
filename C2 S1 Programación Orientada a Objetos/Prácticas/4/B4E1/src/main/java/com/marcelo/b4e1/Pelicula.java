package com.marcelo.b4e1;

import java.util.*;

public abstract class Pelicula implements IPelicula
{
    public static final Set<String> TIPOS_DE_PELICULAS_FINALES = new HashSet<>(Arrays.asList(
            "ComediaRomantica",
            "Parodia",
            "ComediaNegra",
            "Robos",
            "Guerra",
            "Ficcion",
            "Thriller",
            "TerrorGotico",
            "Zombies",
            "Psicologico"));

    /// ATRIBUTOS ///
    /**
     * Nombre de la película.
     *
     * @see com.marcelo.b4e1.Pelicula
     */
    private String nombre;

    /**
     * Año en el que se ha grabado la película.
     *
     * @see com.marcelo.b4e1.Pelicula
     */
    private Integer anho;

    /**
     * Duración de la película en minutos.
     *
     * @see com.marcelo.b4e1
     */
    private Integer duracion;

    /**
     * Conjunto de actores que
     * han participado en la película, donde la clave "principal" se usa para obtener el HashMap cpn el
     * conjunto de actores Principales, mientras que la clave "secundario" se usa para obtener el HashMap
     * con el conjunto de actores Secundarios. Además, un actor secundario no puede ser un actor principal
     * y viceversa.
     *
     * @see com.marcelo.b4e1.Pelicula
     */
    private HashMap<String, HashMap<String, IActor>> actores;

    /**
     * Director de la película.
     *
     * @see com.marcelo.b4e1.Director
     */
    private IDirector director;

    /**
     * Presupuesto de la película.
     *
     * @see com.marcelo.b4e1.Pelicula
     */
    protected float presupuesto;

    /**
     * Recaudación de la película
     *
     * @see com.marcelo.b4e1.Pelicula
     */
    private HashMap<String, Float> recaudacion;

    /// CONSTRUCTORES ///

    /**
     * @param nombre      Nombre de la película.
     * @param anho        Año en el que se ha grabado la película, este debe estar comprendido entre 1895 y 2022.
     * @param duracion    Duración de la película en minutos, esta debe ser de más de 5 minutos.
     * @param director    Director de la película.
     * @param recaudacion Recaudación de la película.
     */
    Pelicula(String nombre, Integer anho, Integer duracion, IDirector director, HashMap<String, Float> recaudacion)
    {
        if (nombre == null)
        {
            System.out.println("AVISO: Nombre nulo, el objeto podrá tener inconsistencias");
        }

        this.nombre = nombre;

        if (anho == null || anho < 1895 || anho > 2022)
        {
            System.out.println("AVISO: Año de la película fuera del rango temporal, no se guardará el año de creación");
        } else
        {
            this.anho = anho;
        }

        if (duracion == null || duracion <= 5)
        {
            System.out.println("AVISO: Las películas han de ser de más de 5min, no se guardará este dato");
        } else
        {
            this.duracion = duracion;
        }

        if (director == null)
        {
            System.out.println("AVISO: Director nulo, el objeto podrá tener inconsistencias");
        } else
        {
            this.director = director;
        }


        this.recaudacion = new HashMap<>();

        if (recaudacion == null)
        {
            System.out.println("AVISO: La recaudación recibida no es válida, no se guardará este dato.");

        } else
        {
            for (Map.Entry<String, Float> recaudacionIndividual : recaudacion.entrySet())
            {
                if (recaudacionIndividual.getValue() == null)
                {
                    System.out.println("AVISO: La recaudación es nula");
                    continue;
                }
                if (recaudacionIndividual.getValue() <= 0)
                {
                    System.out.println("AVISO: La recaudación es menor o igual a 0");
                    continue;
                }
                this.recaudacion.put(recaudacionIndividual.getKey(), recaudacionIndividual.getValue());
            }
        }

        this.actores = new HashMap<>();
        this.actores.put("principal", new HashMap<>());
        this.actores.put("secundario", new HashMap<>());

        this.presupuesto();
    }

    /// GETTERS & SETTERS ///

    @Override
    public String getNombre()
    {
        return nombre;
    }
    
    @Override
    public Integer getAnho()
    {
        return anho;
    }
    
    @Override
    public void setAnho(Integer anho)
    {
        if (anho == null || anho < 1895 || anho > 2022)
        {
            System.out.println("ERROR: Película fuera del rango temporal.");
            return;
        }
        this.anho = anho;
    }
    
    @Override
    public Integer getDuracion()
    {
        return duracion;
    }
    
    @Override
    public void setDuracion(Integer duracion)
    {
        if (duracion == null || duracion <= 5)
        {
            System.out.println("ERROR: Las peliculas han de ser de más de 5min.");
            return;
        }
        this.duracion = duracion;
    }
    
    @Override
    public HashMap<String, HashMap<String, IActor>> getActores()
    {
        return this.actores;
    }
    
    @Override
    public IDirector getDirector()
    {
        return director;
    }
    
    @Override
    public float getPresupuesto()
    {
        // Nota: El presupuesto puede cambiar en cualquier momento, ya que tanto los actores como el director pueden modificar sus cachés.
        //  Entiendo que, como la función del cálculo del presupuesto es pública, siempre puede sre llamada antes del getter en caso necesario,
        //  por lo que no lo recalculo antes de mostrarlo.
        //  Sí lo recalculo, en cambio, en el constructor y cuando añado un actor.
        //  Quedaría la duda de si se debe recalcular también el presupuesto como primer paso de la función exito().

        return presupuesto;
    }

    /**
     * Calcula el presupuesto de la película como la suma del caché
     * de todos los actores más un porcentaje que dependerá del género de la película
     */
    @Override
    public void presupuesto()
    {
        float sumaCaches = 0;

        sumaCaches += this.getSumaCachesActores();

        if (this.director != null)
        {
            String tipoPelicula = this.getClass().getSimpleName();
            if (this.director.getCache().containsKey(tipoPelicula))
            {
                sumaCaches += this.director.getCache().get(tipoPelicula);
            } else
            {
                System.out.println("ERROR: EL director seleccionado no dispone de caché para este género de películas");
            }
        }
        
        this.presupuesto = sumaCaches;
    }
    
    protected float getSumaCachesActores()
    {
        float sumaCachesActores = 0;
        if (this.getActores() != null)
        {
            for (HashMap<String, IActor> hashMapTiposActores : this.getActores().values())
            {
                for (IActor actor : hashMapTiposActores.values())
                {
                    sumaCachesActores += actor.getCache();
                }
            }
        }
        return sumaCachesActores;
    }
    
    @Override
    public HashMap<String, Float> getRecaudacion()
    {
        return recaudacion;
    }

    /**
     * Recaudación total de la película. Este
     * método no puede ser sobreescrito en ninguna otra clase de la jerarquía de clases. El HashMap se
     * debe recorrer a partir de las claves.
     *
     * @return Suma de toda la recaudación.
     */

    @Override
    public final float recaudacionTotal()
    {
        float sumaTotal = 0;
        for (String nombrePais : this.recaudacion.keySet())
        {
            sumaTotal += this.recaudacion.get(nombrePais);
        }
        return sumaTotal;
    }

    public void setRecaudacion(HashMap<String, Float> recaudacion)
    {
        if (recaudacion == null)
        {
            System.out.println("AVISO: La recaudación recibida no es válida, no se guardará este dato.");

        } else
        {
            if (!this.recaudacion.isEmpty())
            {
                System.out.println("AVISO: Ya existía información sobre recaudación. Esta será sobreescrita.");
            }

            this.recaudacion = new HashMap<>();

            for (Map.Entry<String, Float> recaudacionIndividual : recaudacion.entrySet())
            {
                if (recaudacionIndividual.getValue() == null)
                {
                    System.out.println("AVISO: La recaudación es nula");
                    continue;
                }
                if (recaudacionIndividual.getValue() <= 0)
                {
                    System.out.println("AVISO: La recaudación es menor o igual a 0");
                    continue;
                }
                this.recaudacion.put(recaudacionIndividual.getKey(), recaudacionIndividual.getValue());
            }
        }
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
    @Override
    public boolean darAlta(String rol, ArrayList<IActor> actores)
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

        for (IActor actor : actores)
        {
            if (this.actores.get(rol).containsKey(actor.getNombre()))
            {
                return false;
            }
        }

        for (IActor actor : actores)
        {
            this.actores.get(rol).put(actor.getNombre(), actor);
            actor.introducirPelicula(this);
        }

        this.presupuesto();

        return true;

    }

    /**
     * @param director Director del cual se buscarán los actores
     * @return Conjunto de actores que han sido dirigidos anteriormente (es decir, en otras películas)
     * por el director
     * Nota: Originalmente, se especificaba que era "el de la película", pero entiendo que hay que buscar el pasado como parámetro.
     * @implNote Todos los HashMap deben recorrerse usando un iterator de claves.
     */
    @Override
    public HashMap<String, IActor> actoresDirigidos(String director)
    {
        //Entiendo que se piden los actores (que intervienen en esta película) que han sido dirigidos por el director en películas QUE NO SEAN ESTA.
        HashMap<String, IActor> salida = new HashMap<>();

        if (director == null)
        {
            System.out.println("ERROR (actoresDirigidos): El campo de director no puede ser nulo");
            return salida;
        }

        HashMap<String, HashMap<String, IActor>> actoresPelicula = this.getActores();

        if (actoresPelicula == null)
        {
            System.out.println("ERROR (actoresDirigidos): Instancia no inicializada correctamente");
            return salida;
        }

        for (Iterator<String> keyIteratorTipoActor = actoresPelicula.keySet().iterator(); keyIteratorTipoActor.hasNext(); )
        {
            String tipoActor = keyIteratorTipoActor.next();

            for (Iterator<String> keyIteratorNombreActor = actoresPelicula.get(tipoActor).keySet().iterator(); keyIteratorNombreActor.hasNext(); )
            {
                String nombreActor = keyIteratorNombreActor.next();

                IActor actor = actoresPelicula.get(tipoActor).get(nombreActor);

                if (actor.getPeliculas() != null && !salida.containsKey(actor.getNombre()))
                {
                    for (Iterator<String> keyIteratorNombrePelicula = actor.getPeliculas().keySet().iterator(); keyIteratorNombrePelicula.hasNext(); )
                    {
                        String nombrePelicula = keyIteratorNombrePelicula.next();

                        //  if (!nombrePelicula.equals(this.nombre))
                        if (!this.equals(actor.getPeliculas().get(nombrePelicula)))
                        {
                            if (director.equals(actor.getPeliculas().get(nombrePelicula).getDirector().getNombre()))
                            {
                                salida.put(actor.getNombre(), actor);
                            }
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
     * @return Set de actores que han participado
     * @implNote Los HashMap se deben recorrer con un iterator de valores.
     */
    @Override
    public Set<IActor> actoresFracaso()
    {
        //Entiendo que se piden los actores (que intervienen en esta película) que han tenido algún fracaso en alguna pelicula QUE NO SEA ESTA.
        Set<IActor> salida = new HashSet<>();

        HashMap<String, HashMap<String, IActor>> actoresPelicula = this.getActores();

        if (actoresPelicula == null)
        {
            System.out.println("ERROR (actoresDirigidos): Instancia no inicializada correctamente");
            return salida;
        }

        for (Iterator<HashMap<String, IActor>> iteratorTipoActor = actoresPelicula.values().iterator(); iteratorTipoActor.hasNext(); )
        {
            HashMap<String, IActor> actoresDeCiertoTipo = iteratorTipoActor.next();

            for (Iterator<IActor> iteratorActor = actoresDeCiertoTipo.values().iterator(); iteratorActor.hasNext(); )
            {
                IActor actor = iteratorActor.next();

                if (actor.getPeliculas() != null && !salida.contains(actor))
                {
                    for (Iterator<IPelicula> iteratorPelicula = actor.getPeliculas().values().iterator(); iteratorPelicula.hasNext(); )
                    {
                        Pelicula pelicula = (Pelicula) iteratorPelicula.next();

                        if (!pelicula.equals(this))
                        {
                            if (!pelicula.exito())
                            {
                                salida.add(actor);
                            }
                        }
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
    @Override
    public abstract boolean exito();

    @Override
    public String toString()
    {
        String salida = new String();
        boolean primeraCadena = true;

        salida += "{\n";
        if (this.nombre != null)
        {
            salida += "\"nombre\": \"" + this.nombre + "\"";
            primeraCadena = false;
        }

        if (this.anho != null)
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }

            salida += "\"anho\": " + "\"" + this.anho + "\"";
            primeraCadena = false;
        }

        if (this.duracion != null)
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }

            salida += "\"duracion\": \"" + this.duracion + "\"";
            primeraCadena = false;
        }

        if (this.director != null)
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }

            salida += "\"director\": " + this.director ;
            primeraCadena = false;
        }


        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }

            salida += "\"recaudacion\": " + this.recaudacion;
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
            String cadenaListadoActores = getCadenaListadoActores();

            if (cadenaListadoActores.isEmpty() == false)
            {
                if (primeraCadena == false)
                {
                    salida += ",\n";
                } else
                {
                    primeraCadena = false;
                }

                salida += "\"" + "actores" + "\"" + ": " + "[";
                salida += cadenaListadoActores;
                salida += "\n]";
            }
        }

        salida += "\n}";
        return salida;
    }

    private String getCadenaListadoActores()
    {
        String salida = "";
        boolean primerTipoDeActores = true;

        for (Map.Entry<String, HashMap<String, IActor>> parActores : this.actores.entrySet())
        {
            String clave = parActores.getKey();
            HashMap<String, IActor> valores = parActores.getValue();

            if (clave == null || valores == null || valores.isEmpty())
            {
                continue;
            }

            if (primerTipoDeActores == false)
            {
                salida += ", ";

            } else
            {
                primerTipoDeActores = false;
            }

            salida += "\n{ \"" + clave + "\": [";

            boolean primerActorDeEsteTipo = true;

            for (String actor : valores.keySet())
            {
                if (primerActorDeEsteTipo == false)
                {
                    salida += ", ";
                } else
                {
                    primerActorDeEsteTipo = false;
                }

                salida += "\"" + actor + "\"";
            }

            salida += "] }";


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
        final IPelicula other = (IPelicula) obj;

        if (!this.nombre.equals(other.getNombre()))
        {
            return false;
        }

        return true;
    }

}
