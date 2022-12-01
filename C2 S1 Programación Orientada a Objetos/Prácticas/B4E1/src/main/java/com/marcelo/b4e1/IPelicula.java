package com.marcelo.b4e1;

import java.util.HashMap;

public interface IPelicula extends ITPelicula, ICPelicula, IAPelicula
{
    /**
     * Devuelve el número de actores que han
     * participado en la película.
     *
     * @return número de actores que han participado en la película.
     */
    public default int numeroActores()
    {
        int salida = 0;

        for (HashMap<String, Actor> mapaActores : this.getActores().values()) {
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
        //todo: Termíname
        //PENDIENTE

        return Float.NaN;
    }
}
