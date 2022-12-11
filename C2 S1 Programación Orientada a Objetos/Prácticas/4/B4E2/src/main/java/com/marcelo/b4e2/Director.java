package com.marcelo.b4e2;

import java.util.*;

public class Director implements IDirector
{
    /**
     * Director de la película (Ver b3e1 para diferencias)
     *
     * @see Director
     */
    private String nombre;
    
    /**
     * Caché del director en función del género de las
     * películas en las que participa. El género se indica en el atributo especialista y debe coincidir con el
     * género de la jerarquía de películas.
     *
     * @implNote Voy a asumir que se quiere que pongamos los tipos de películas en una constante.
     * Voy a asumir que especialista es un limitante respecto a los tipos de película admisibles en caché.
     * @see Director
     * @see Pelicula
     */
    private HashMap<String, Float> cache;
    
    /**
     * Conjunto de películas en las que ha participado el
     * director.
     *
     * @see Director
     * @see Pelicula
     */
    private ArrayList<IPelicula> peliculas;
    
    /**
     * géneros de las películas en las cuales el director es un especialista.
     *
     * @see Director
     */
    private Set<String> especialista;
    
    public Director(String nombre, Set<String> especialista, HashMap<String, Float> cache) throws ExcepcionParticipante
    {
        if (nombre == null)
        {
//            throw new ExcepcionParticipante("No se puede crear el director: El nombre del director no puede ser nulo.");
            throw new ExcepcionParticipante("el nombre del director no puede ser nulo.");
        }
        this.nombre = nombre;
        
        
        if (especialista == null)
        {
            //todo: ver como mostrar la instancia de especialista
//            throw new ExcepcionDirector("No se puede crear el director: especialista no puede ser nulo");
            throw new ExcepcionDirector("especialista no puede ser nulo");
        }
        if (especialista.isEmpty())
        {
//            throw new ExcepcionDirector("No se puede crear el director: especialista es una lista vacía");
            throw new ExcepcionDirector("especialista es una lista vacía");
        }
        
        this.especialista = new HashSet<>();
        
        for (String tipoPelicula : especialista)
        {
            //Solo aceptaré tipos de películas que sean válidos.
            if (Pelicula.TIPOS_DE_PELICULAS_FINALES.contains(tipoPelicula))
            {
                this.especialista.add(tipoPelicula);
            } else
            {
//                throw new ExcepcionDirector("No se puede crear el director: alguno de los géneros no está permitido");
                throw new ExcepcionDirector("alguno de los géneros no está permitido");
            }
        }
        
        this.cache = new HashMap<>();
        if (cache != null)
        {
            for (Map.Entry<String, Float> kvCache : cache.entrySet())
            {
                // Solo aceptaré el caché de tipos de películas de los cuales sea especialista
                // En este caso me ahorro mirar si el tipo de película es válido o no, porque ya se miró al introducirlas en la var. especialista.
                
                String keyCache = kvCache.getKey();
                
                if (this.especialista.contains(keyCache))
                {
                    if (!this.cache.containsKey(keyCache))
                    {
                        Float valCache = kvCache.getValue();
                        
                        if (valCache == null || valCache <= 0)
                        {
                            System.out.println("Aviso: El cache debe ser mayor a 0, no se guardará este dato");
                        } else
                        {
                            this.cache.put(keyCache, valCache);
                        }
                    }
                } else
                {
                    System.out.println("Aviso: El director no es especialista en este género de películas (" + keyCache + "), no se guardará este caché");
                }
            }
        }
        
        this.peliculas = new ArrayList<>();
    }
    
    @Override
    public String getNombre()
    {
        return nombre;
    }
    
    @Override
    public void setNombre(String nombre) throws ExcepcionDirector
    {
        
        if (nombre == null)
        {
//            throw new ExcepcionDirector("No se puede crear el director: el nombre del director no puede ser nulo.");
            throw new ExcepcionDirector("el nombre del director no puede ser nulo.");
        }
        this.nombre = nombre;
        
        
    }
    
    @Override
    
    public HashMap<String, Float> getCache()
    {
        return cache;
    }
    
    @Override
    public void setCache(HashMap<String, Float> cache)
    {
        if (cache == null)
        {
            //todo: revisar si hay que lanzar excepción
            System.out.println("ERROR: el cache pasado como parámetro es nulo, no se modificará la variable.");
        } else
        {
            System.out.println("AVISO: Este método eliminará cualquier información previa que hubiera almacenada sobre el caché de este director.");
            
            this.cache = new HashMap<>();
            for (Map.Entry<String, Float> kvCache : cache.entrySet())
            {
                // Solo aceptaré el caché de tipos de películas de los cuales sea especialista
                // En este caso me ahorro mirar si el tipo de película es válido o no, porque ya se miró al introducirlas en la var. especialista.
                
                String keyCache = kvCache.getKey();
                
                if (this.especialista.contains(keyCache))
                {
                    if (!this.cache.containsKey(keyCache))
                    {
                        Float valCache = kvCache.getValue();
                        
                        if (valCache == null || valCache <= 0)
                        {
                            System.out.println("Aviso: El cache debe ser mayor a 0, no se guardará este dato");
                        } else
                        {
                            this.cache.put(keyCache, valCache);
                        }
                    }
                } else
                {
                    System.out.println("Aviso: El director no es especialista en este género de películas (" + keyCache + "), no se guardará este caché");
                }
            }
        }
    }
    
    @Override
    public ArrayList<IPelicula> getPeliculas()
    {
        ArrayList<IPelicula> salida = new ArrayList<>();
        
        for (IPelicula pelicula : this.peliculas)
        {
            salida.add(pelicula);
        }
        
        return salida;
    }
    
    @Override
    public Set<String> getEspecialista()
    {
        return especialista;
    }
    
    @Override
    public void setEspecialista(Set<String> especialista) throws ExcepcionDirector
    {
        if (especialista == null)
        {
//            throw new ExcepcionDirector("No se puede modificar el atributo especialista del director " + this.getNombre() + ": la instancia de especialista no puede ser nula");
            throw new ExcepcionDirector("la instancia de especialista no puede ser nula");
        }
        if (especialista.isEmpty())
        {
//            throw new ExcepcionDirector("No se puede modificar el atributo especialista del director " + this.getNombre() + ": la instancia de especialista es una lista vacía");
            throw new ExcepcionDirector("la instancia de especialista es una lista vacía");
        }
        
        System.out.println("AVISO: Este método eliminará cualquier información previa que hubiera almacenada sobre las especialidades de este director.");
        this.especialista = new HashSet<>();
        for (String tipoPelicula : especialista)
        {
            //Solo aceptaré tipos de películas que sean válidos.
            if (Pelicula.TIPOS_DE_PELICULAS_FINALES.contains(tipoPelicula))
            {
                this.especialista.add(tipoPelicula);
            } else
            {
//                throw new ExcepcionDirector("No se puede modificar el atributo especialista del director" + this.getNombre() + ": alguno de los géneros indicados en la lista no está permitido.");
                throw new ExcepcionDirector("alguno de los géneros indicados en la lista no está permitido.");
            }
            
        }
    }
    
    /// Metodos Funcionales ///
    
    /**
     * Introduce una película
     * en la que ha participado el director. Si el género de la película no coincide con la lista de las películas
     * en las cuales es un especialista, no se deberá dar de alta.
     *
     * @param pelicula Pelicula a introducir
     */
    @Override
    public void introducirPelicula(IPelicula pelicula)
    {
        //todo: revisar si hay que lanzar excepción
        if (pelicula == null)
        {
            //todo: revisar si hay que lanzar excepción
            System.out.println("ERROR: La película no puede ser nula");
        } else if (!this.equals(pelicula.getDirector()))
        {
            //todo: revisar si hay que lanzar excepción
            System.out.println("ERROR: El director no coincide");
        } else
        {
            String tipoPelicula = pelicula.getClass().getSimpleName();
            
            if (this.getEspecialista().contains(tipoPelicula))
            {
                if (!this.getPeliculas().contains(pelicula))
                {
                    this.getPeliculas().add(pelicula);
                } else
                {
                    //todo: revisar si hay que lanzar excepción
                    System.out.println("ERROR: La película ya está en la lista.");
                }
            } else
            {
                //todo: revisar si hay que lanzar excepción
                System.out.println("ERROR: El director no es especialista en este tipo de películas, NO se ha introducido la película.");
            }
        }
    }
    
    
    /**
     * devuelve el número de veces que un
     * director ha dirigido a un actor
     *
     * @param actor actor sobre el que se va a realizar la búsqueda
     * @return número de veces que un director ha dirigido a un actor
     */
    @Override
    public int dirigirActor(String actor)
    {
//      int salida = 42 - 21 * 2;
        int salida = 0;
        
        if (actor == null)
        {
            //todo: revisar si hay que lanzar excepción
            System.out.println("ERROR: El nombre del actor es nulo.");
            return salida;
        }
        
        for (IPelicula pelicula : this.getPeliculas())
        {
            for (HashMap<String, IActor> actoresCiertoTipo : pelicula.getActores().values())
            {
                if (actoresCiertoTipo.containsKey(actor))
                {
                    ++salida;
                    break;
                }
            }
        }
        
        return salida;
    }
    
    /**
     * Devuelve el conjunto de géneros en los que el
     * director tiene un caché más alto.
     *
     * @return Conjunto de géneros en los que el director tiene un caché más alto.
     */
    @Override
    public Set<String> generoMasCaro()
    {
        
        
        float cacheMasAlto = 0;
        
        for (Float cacheCiertoGenero : this.cache.values())
        {
            if (cacheCiertoGenero > cacheMasAlto)
            {
                cacheMasAlto = cacheCiertoGenero;
            }
        }
        
        Set<String> salida = new HashSet<>();
        
        for (Map.Entry<String, Float> kvGenero : this.cache.entrySet())
        {
            Float vGenero = kvGenero.getValue();
            if (vGenero == cacheMasAlto)
            {
                salida.add(kvGenero.getKey());
            }
        }
        
        return salida;
    }
    
    
    /**
     * Devuelve las películas que ha dirigido el director que han tenido una recaudación mayor que una
     * cantidad mínima, donde la clave del HashMap es el nombre de la película y el dato la instancia.
     *
     * @param minimo Mínimo que tiene que pasar para que entre en la salida
     * @return Películas que superan el mínimo estipulado por el usuario
     */
    @Override
    public HashMap<String, IPelicula> peliculasMasBeneficio(float minimo)
    {
        HashMap<String, IPelicula> salida = new HashMap<>();
        
        for (IPelicula pelicula : this.getPeliculas())
        {
            if (pelicula.getNombre() != null)
            {
                if (pelicula.recaudacionTotal() > minimo)
                {
                    salida.put(pelicula.getNombre(), pelicula);
                }
            }
        }
        
        return salida;
    }
    
    @Override
    public boolean equals(Object o)
    {
        if (this == o)
        {
            return true;
        }
        if (o == null || getClass() != o.getClass())
        {
            return false;
        }
        
        IDirector director = (IDirector) o;
        
        return nombre.equals(director.getNombre());
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
        
        if (this.cache != null && !this.cache.isEmpty())
        {
            if (!primeraCadena)
            {
                salida += ",\n";
            }
            
            salida += "\"cache\": [\n";
            
            for (Iterator<Map.Entry<String, Float>> entryIterator = cache.entrySet().iterator(); entryIterator.hasNext(); )
            {
                Map.Entry<String, Float> cache = entryIterator.next();
                
                if (cache.getKey() == null || cache.getValue() == null)
                {
                    continue;
                }
                salida += "   {" + cache.getKey() + ",\"" + cache.getValue() + "\"}";
                if (entryIterator.hasNext())
                {
                    salida += ",\n";
                }
            }
            
            salida += "\n   ]";
            primeraCadena = false;
        }
        
        if (this.peliculas != null && !this.peliculas.isEmpty())
        {
            if (!primeraCadena)
            {
                salida += ",\n";
            }
            salida += "\"peliculas\":[";
            for (Iterator<IPelicula> PeliculaIterator = this.getPeliculas().iterator(); PeliculaIterator.hasNext(); )
            {
                IPelicula pelicula = PeliculaIterator.next();
                
                if (pelicula == null || pelicula.getNombre() == null)
                {
                    continue;
                }
                salida += "\"" + pelicula.getNombre() + "\"";
                
                if (PeliculaIterator.hasNext())
                {
                    salida += ", ";
                }
            }
            salida += "]";
            primeraCadena = false;
        }
        
        
        if (especialista != null || !peliculas.isEmpty())
        {
            if (!primeraCadena)
            {
                salida += ",\n";
            }
            salida += "\"especialista\":[";
            for (Iterator<String> PeliculaIterator = this.especialista.iterator(); PeliculaIterator.hasNext(); )
            {
                String especialista = PeliculaIterator.next();
                
                if (especialista == null)
                {
                    continue;
                }
                salida += "\"" + especialista + "\"";
                if (PeliculaIterator.hasNext())
                {
                    salida += ", ";
                }
            }
            salida += "]";
            primeraCadena = false;
        }
        
        
        salida += "\n}";
        
        return salida;
        
        
    }
}
