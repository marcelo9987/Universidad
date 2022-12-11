package com.marcelo.b4e2;

import java.util.HashMap;

public interface IPelicula extends IAPelicula, ICPelicula,ITPelicula  {
    /**
     * Devuelve el número de actores que han
     * participado en la película.
     *
     * @return número de actores que han participado en la película.
     */
    public default int numeroActores()
    {
        int salida = 0;
        
        for (HashMap<String, IActor> mapaActores : this.getActores().values())
        {
            salida += mapaActores.values().size();
        }
        
        
        return salida;
    }
    
    /**
     * Devuelve el coste de los actores que han participado en la película.
     *
     * @return Devuelve el coste de los actores que han participado en la película.
     */
    public default float costeActores()
    {
        float sumaCostes = 0;
        for (HashMap<String, IActor> conjuntoActores : this.getActores().values())
        {
            for (IActor actor : conjuntoActores.values())
            {
                sumaCostes += actor.getCache();
            }
        }
        return sumaCostes;
    }
}
