package com.marcelo.b4e1;

import java.util.*;


public class Actor implements IActor
{
    
    public static final String[] TIPOS_DE_ACTORES = {"principal", "secundario"};
    
    /// ATRIBUTOS ///
    private String nombre;
    private ArrayList<String> deseos;
    private HashMap<String, IPelicula> peliculas;
    private float cache;
    
    /// CONSTRUCTORES ///
    
    /**
     * @param nombre Nombre del actor
     * @param deseos Directores con los que el autor quiere trabajar.
     * @param cache  Dinero que maneja el actor.
     */
    
    Actor(String nombre, ArrayList<String> deseos, float cache)
    {
        if (nombre == null)
        {
            System.out.println("AVISO: Argumento nulo, podrá haber inconsistencias");
        } else
        {
            this.nombre = nombre;
        }
        
        if (deseos == null)
        {
            this.deseos = null;
        } else
        {
            this.deseos = new ArrayList<>();
            for (String deseo : deseos)
            {
                if (!this.deseos.contains(deseo))
                {
                    this.deseos.add(deseo);
                }
            }
        }
        
        this.peliculas = new HashMap<>();
        
        if (cache <= 0)
        {
            System.out.println("AVISO: El cache debe ser mayor a 0, no se guardará este dato");
        } else
        {
            this.cache = cache;
        }
        
        
    }
    
    
    Actor(String nombre, float cache)
    {
        if (nombre == null)
        {
            System.out.println("AVISO: Argumento nulo, podrá haber inconsistencias");
        } else
        {
            this.nombre = nombre;
        }
        
        this.nombre = nombre;
        this.deseos = null;
        this.peliculas = new HashMap<>();
        
        if (cache <= 0)
        {
            System.out.println("AVISO: El cache debe ser mayor a 0, no se guardará este dato");
        } else
        {
            this.cache = cache;
        }
        
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
        if (deseos == null)
        {
            this.deseos = null;
        } else
        {
            this.deseos = new ArrayList<>();
            for (String deseo : deseos)
            {
                if (!this.deseos.contains(deseo))
                {
                    this.deseos.add(deseo);
                }
            }
        }
    }
    
    public HashMap<String, IPelicula> getPeliculas()
    {
        return this.peliculas;
    }
    
    public float getCache()
    {
        return cache;
    }
    
    public void setCache(float cache)
    {
        if (cache <= 0)
        {
            System.out.println("ERROR: El cache debe ser mayor a 0");
            return;
        }
        this.cache = cache;
    }
    /// MÉTODOS FUNCIONALES ///
    
    /**
     * introduce una película
     * en la que ha participado el actor.
     *
     * @param pelicula Pelicula a introducir.
     */
    public void introducirPelicula(IPelicula pelicula)
    {
        if (pelicula == null || pelicula.getNombre() == null)
        {
            System.out.println("ERROR (introducirPelicula): parámetros incorrectos.");
            return;
        }
        
        if (this.peliculas.containsKey(pelicula.getNombre()))
        {
            System.out.println("AVISO (Actor: introducirPelicula): La película \"" + pelicula.getNombre() + "\" ya existe.");
        } else
        {
            this.getPeliculas().put(pelicula.getNombre(), pelicula);
            
            String director = pelicula.getDirector().getNombre();
            if (this.deseos != null && this.deseos.contains(director))
            {
                this.deseos.remove(director);
            }
        }
    }
    
    
    /**
     * Devuelve las
     * películas de un determinado género en las que ha participado el actor.
     *
     * @param genero genero a buscar
     * @return Películas del género especificado
     */
    
    public Set<IPelicula> peliculasDeGenero(String genero)
    {
        Set<IPelicula> salida = new HashSet<>();
        
        if (genero == null)
        {
            System.out.println("Error (peliculasDeGenero), parámetros incorrectos.");
            return salida;
        }
        
        
        Collection<IPelicula> todasLasPeliculas = this.peliculas.values();
        
        for (IPelicula pelicula : todasLasPeliculas)
        {
            if (pelicula.getClass().getSimpleName().equalsIgnoreCase(genero))
            {
                salida.add(pelicula);
            }
        }
        
        return salida;
    }
    
    
    /**
     * @param genero género de las películas a buscar
     * @return Películas de un determinado género en las que ha participado el actor y que han sido un fracaso.
     */
    public ArrayList<IPelicula> peliculasFracaso(String genero)
    {
        ArrayList<IPelicula> salida = new ArrayList<>();
        
        if (genero == null)
        {
            System.out.println("Error (peliculasFracaso), parámetros incorrectos.");
            return salida;
        }
        
        Set<IPelicula> peliculasGenero = this.peliculasDeGenero(genero);
        for (IPelicula pelicula : peliculasGenero)
        {
            if (pelicula.exito() == false)
            {
                salida.add(pelicula);
            }
        }
        return salida;
    }
    
    /**
     * devuelve el número de
     * veces que el actor participado como actor "principal" o actor "secundario" en las películas en las que
     * ha participado.
     *
     * @param tipoParticipacion principal o secundario
     * @return número de veces que ha participado en ese tipo de participación.
     */
    public int importancia(String tipoParticipacion)
    {
        int salida = 0;
        boolean tipoCorrectoActor = false;
        for (String tipo : Actor.TIPOS_DE_ACTORES)
        {
            if (tipo.equals(tipoParticipacion))
            {
                tipoCorrectoActor = true;
                break;
            }
        }
        if (!tipoCorrectoActor)
        {
            System.out.println("Error (importancia): Tipo de actor incorrecto.");
            return salida;
        }
        
        for (IPelicula pelicula : this.getPeliculas().values())
        {
            if (pelicula.getActores().get(tipoParticipacion).containsValue(this))
            {
                salida++;
            }
        }
        return salida;
    }
    
    /**
     * Devuelve la cantidad total que ha ganado el actor por
     * las películas en las que ha participado.
     * Entry.Map.
     *
     * @return cantidad total que ha ganado el actor por
     * las películas en las que ha participado.
     * @implNote Los HashMap se deben recorrer con un iterator de Map.Entry
     */
    public float totalGanancias()
    {
        float ganancias = 0;
        
        for (Iterator<Map.Entry<String, IPelicula>> iterator = this.getPeliculas().entrySet().iterator(); iterator.hasNext(); )
        {
            Map.Entry<String, IPelicula> kvEntry = iterator.next();
            ganancias += kvEntry.getValue().getPresupuesto();
        }
        return ganancias;
    }
    
    /**
     * Devuelve el conjunto de directores con los
     * que el actor quiere trabajar, pero que aún no lo han dirigido en ninguna película.
     *
     * @return conjunto de directores con los
     * que el actor quiere trabajar, pero que aún no lo han dirigido en ninguna película.
     */
    public Set<String> deseosNoCumplidos()
    {
        Set<String> salida = new HashSet<>();
        ArrayList<String> deseos = this.getDeseos();
        
        if (deseos != null)
        {
            salida.addAll(deseos);
        }
        
        return salida;
    }
    
    
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
        
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }
            
            salida += "\"cache\": " + "\"" + this.cache + "\"";
            primeraCadena = false;
        }
        
        if (this.deseos != null && !this.deseos.isEmpty())
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }
            salida += "\"" + "deseos" + "\"" + ": " + "[";
            boolean primeraSubCadena = true;
            for (Iterator<String> keysIterator = this.deseos.iterator(); keysIterator.hasNext(); )
            {
                if (primeraSubCadena == false)
                {
                    salida += ",";
                }
                String deseo = keysIterator.next();
                salida += "\"" + deseo + "\"";
                primeraSubCadena = false;
            }
            salida += "]";
            primeraCadena = false;
        }
        
        
        if (this.peliculas != null)
        {
            if (!primeraCadena)
            {
                salida += ",\n";
            }
            salida += "\"peliculas\":\" [";
            for (Iterator<IPelicula> iterator = this.peliculas.values().iterator(); iterator.hasNext(); )
            {
                IPelicula peliculaActual = (IPelicula) iterator.next();
                salida += "\"" + peliculaActual.getNombre() + "\"";
                if (iterator.hasNext())
                {
                    salida += ",";
                }
                if (!iterator.hasNext())
                {
                    salida += "]";
                }
            }
            primeraCadena = false;
        }
        salida += "\n}";
        
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
        final IActor other = (IActor) obj;
        
        if (!this.nombre.equals(other.getNombre()))
        {
            return false;
        }
        
        return true;
    }
}

