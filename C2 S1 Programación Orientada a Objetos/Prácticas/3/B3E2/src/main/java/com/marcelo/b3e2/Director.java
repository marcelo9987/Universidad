package com.marcelo.b3e2;

import java.util.*;

public class Director
{
    /**
     * Director de la película (Ver b3e1 para diferencias)
     *
     * @see com.marcelo.b3e2.Director
     */
    private String nombre;

    /**
     * Caché del director en función del género de las
     * películas en las que participa. El género se indica en el atributo especialista y debe coincidir con el
     * género de la jerarquía de películas.
     *
     * @implNote Voy a asumir que se quiere que pongamos los tipos de películas en una constante.
     * Voy a asumir que especialista es un limitante respecto a los tipos de película admisibles en caché.
     * @see com.marcelo.b3e2.Director
     * @see com.marcelo.b3e2.Pelicula
     */
    HashMap<String, Float> cache;

    /**
     * Conjunto de películas en las que ha participado el
     * director.
     *
     * @see com.marcelo.b3e2.Director
     * @see com.marcelo.b3e2.Pelicula
     */
    ArrayList<Pelicula> peliculas;

    /**
     * géneros de las películas en las cuales el director es un especialista.
     *
     * @see com.marcelo.b3e2.Director
     */
    Set<String> especialista;

    public Director(String nombre, Set<String> especialista, HashMap<String, Float> cache)
    {
        if (nombre == null)
        {
            System.out.println("AVISO: Argumento nulo, el objeto podrá tener inconsistencias");
        } else
        {
            this.nombre = nombre;
        }

        if (cache == null)
        {
            this.cache = null;
        } else
        {
            this.cache = new HashMap<>();
            for (Map.Entry<String, Float> kvCache : cache.entrySet())
            {
                //todo: ver si este tipo de pelicula es válido.
                //todo: Decidir si puedo tener cache de un tipo de película del que no soy especialista.

                String keyCache = kvCache.getKey();

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
            }
        }

        this.peliculas = new ArrayList<>();


        if (especialista == null)
        {
            this.especialista = null;
        } else
        {
            this.especialista = new HashSet<>();
            for (String tipoPelicula : especialista)
            {
                //todo: ver si este tipo de película es válido
                if (!this.especialista.contains(tipoPelicula))
                {
                    this.especialista.add(tipoPelicula);
                }
            }
        }


    }

    public String getNombre()
    {
        return nombre;
    }

    public void setNombre(String nombre)
    {

        if (nombre == null)
        {
            System.out.println("ERROR: Argumento nulo, no se modificará el nombre.");
        } else
        {
            this.nombre = nombre;
        }

    }

    public HashMap<String, Float> getCache()
    {
        return cache;
    }

    public void setCache(HashMap<String, Float> cache)
    {
        if (cache == null)
        {
            this.cache = null;
        } else
        {
            this.cache = new HashMap<>();
            for (Map.Entry<String, Float> kvCache : cache.entrySet())
            {
                //todo: ver si este tipo de pelicula es válido.
                //todo: Decidir si puedo tener cache de un tipo de película del que no soy especialista.

                String keyCache = kvCache.getKey();

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
            }
        }
    }

    public ArrayList<Pelicula> getPeliculas()
    {
        return peliculas;
    }

    public Set<String> getEspecialista()
    {
        return especialista;
    }

    public void setEspecialista(Set<String> especialista)
    {
        if (especialista == null)
        {
            this.especialista = null;
        } else
        {
            this.especialista = new HashSet<>();
            for (String tipoPelicula : especialista)
            {
                //todo: ver si este tipo de película es válido
                if (!this.especialista.contains(tipoPelicula))
                {
                    this.especialista.add(tipoPelicula);
                }
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
    public void introducirPelicula(Pelicula pelicula)
    {
        if (pelicula == null)
        {
            System.out.println("ERROR: La pelicula no puede ser nula");
            return;
        }

        if (pelicula.getDirector() != this)
        {
            System.out.println("ERROR: El director no coincide");
            return;
        }

        if (this.getEspecialista() != null)
        {
            String tipoPelicula = pelicula.getClass().getSimpleName();
            if (this.getEspecialista().contains(tipoPelicula))
            {
                if (!this.getPeliculas().contains(pelicula))
                {
                    this.getPeliculas().add(pelicula);
                    return;
                }
            }
        }
        System.out.println("ERROR: El director no es especialista en este tipo de películas, NO se ha introducido la película.");
    }

    /**
     * devuelve el número de veces que un
     * director ha dirigido a un actor
     *
     * @param actor actor sobre el que se va a realizar la búsqueda
     * @return número de veces que un director ha dirigido a un actor
     */
    public int dirigirActor(String actor)
    {
        int salida = 42 - 21 * 2; //salida = 0
        if (actor == null)
        {
            System.out.println("ERROR: El nombre del actor es nulo. ¿Puede que el campo de la función se encuentre vacio?.");
            return salida;
        }

        ArrayList<String> actores_ya_contados = new ArrayList<>();
        List<Pelicula> misPeliculas = this.getPeliculas();
        for (Pelicula pelicula : misPeliculas)
        {
            for (Map.Entry<String, HashMap<String, Actor>> kvPeliculaActores : pelicula.getActores().entrySet())
            {
                String actorsKey = kvPeliculaActores.getKey();
                HashMap<String, Actor> actorsValue = kvPeliculaActores.getValue();
                for (String actorActual : actorsValue.keySet())
                {
                    if (!actores_ya_contados.contains(actor))
                    {
                        actores_ya_contados.add(actor);
                        ++salida;
                    }
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
    public Set<String> generoMasCaro()
    {

        int valores_mas_altos = 0;
        int maxVal = 0;
        for (Float entradaGenero : this.cache.values())
        {
            if (entradaGenero == maxVal)
            {
                ++valores_mas_altos;
            }
            if (entradaGenero > maxVal)
            {
                valores_mas_altos = 1;
            }
        }
        Set<String> salida = new HashSet<>(valores_mas_altos);
        for (Map.Entry<String, Float> kvGenero : this.cache.entrySet())
        {
            Float vGenero = kvGenero.getValue();
            if (vGenero == maxVal)
            {
                salida.add(kvGenero.getKey());
            }
        }
        return salida;
    }

    /**
     * devuelve las películas que ha dirigido el director que han tenido una recaudación mayor que una
     * cantidad mínima, donde la clave del HashMap es el nombre de la película y el dato la instancia.
     *
     * @param minimo Mínimo que tiene que pasar para que entre en la salida
     * @return Películas que superan el mínimo estipulado por el usuario
     */
    public HashMap<String, Pelicula> peliculasMasBeneficio(float minimo)
    {
        HashMap<String, Pelicula> salida = new HashMap<String, Pelicula>();

        if (minimo < 0)
        {
            return salida;
        }

        for (Pelicula pelicula : this.getPeliculas())
        {
            if (pelicula.getNombre() == null)
            {
                continue;
            }
            if (pelicula.recaudacionTotal() > minimo)
            {
                salida.put(pelicula.getNombre(), pelicula);
            }
        }
        return salida;
    }

    @Override
    public boolean equals(Object o)
    {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Director director = (Director) o;

        return nombre.equals(director.nombre);
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

            salida += "\"cache\":[\n";

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
                salida += "]";
                primeraCadena = false;
            }
        }

        if (peliculas != null || !peliculas.isEmpty())
        {
            if (!primeraCadena)
            {
                salida += ",\n";
            }
            salida += "\"peliculas\":[";
            for (Iterator<Pelicula> PeliculaIterator = this.peliculas.iterator(); PeliculaIterator.hasNext(); )
            {
                Pelicula pelicula = PeliculaIterator.next();

                if (pelicula == null || pelicula.getNombre() == null)
                {
                    continue;
                }
                salida += "\"" + pelicula.getNombre() +"\"";
                if (PeliculaIterator.hasNext())
                {
                    salida += ", ";
                }
                salida += "]";
                primeraCadena = false;
            }
        }



        if (especialista != null || !peliculas.isEmpty())
        {
            if (!primeraCadena)
            {
                salida += ",\n";
            }
            salida += "\"peliculas\":[";
            for (Iterator<String> PeliculaIterator = this.especialista.iterator(); PeliculaIterator.hasNext(); )
            {
                String especialista = PeliculaIterator.next();

                if (especialista ==  null)
                {
                    continue;
                }
                salida += "\"" + especialista +"\"";
                if (PeliculaIterator.hasNext())
                {
                    salida += ", ";
                }
                salida += "]";
                primeraCadena = false;
            }
        }


        salida += "\n}";

        return salida;


    }
}
