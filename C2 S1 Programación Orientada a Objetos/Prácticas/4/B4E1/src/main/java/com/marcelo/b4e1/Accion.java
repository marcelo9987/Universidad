package com.marcelo.b4e1;

import java.util.HashMap;

public abstract class Accion extends Pelicula
{
    /**
     * @param nombre      Nombre de la película.
     * @param anho        Año en el que se ha grabado la película, este debe estar comprendido entre 1895 y 2022.
     * @param duracion    Duración de la película en minutos, esta debe ser de más de 5 minutos.
     * @param director    Director de la película.
     * @param recaudacion Recaudación de la película(No puede ser negativa).
     */
    Accion(String nombre, Integer anho, Integer duracion, Director director, HashMap<String, Float> recaudacion)
    {
        super(nombre, anho, duracion, director, recaudacion);
    }

    @Override
    public void presupuesto()
    {
        super.presupuesto();
        this.presupuesto += this.presupuesto * 1.1f;
    }

    @Override
    public boolean exito()
    {
        // Entiendo que un 150% mayor quiere decir que es 2.5 veces más

        if (this.recaudacionTotal() <= (1 + 1.5) * this.getPresupuesto())
        {
            return false;
        }
        else if (this.getRecaudacion().containsKey("EE.UU") && this.getRecaudacion().get("EE.UU") > (1 + 0.3) * this.getPresupuesto())
        {
            return true;
        } else
        {
            return false;
        }
    }


}
