package com.marcelo.b3e2;

import java.util.HashMap;
import java.util.Map;

public final class Ficcion extends Accion
{
    /**
     * @param nombre      Nombre de la película.
     * @param anho        Año en el que se ha grabado la película, este debe estar comprendido entre 1895 y 2022.
     * @param duracion    Duración de la película en minutos, esta debe ser de más de 5 minutos.
     * @param director    Director de la película.
     * @param recaudacion Recaudación de la película(No puede ser negativa).
     */
    Ficcion(String nombre, Integer anho, Integer duracion, Director director, HashMap<String, Float> recaudacion)
    {
        super(nombre, anho, duracion, director, recaudacion);
    }

    public boolean exito()
    {
        //todo: ¿Que tengo que hacer aqui?
        boolean cond1 = recaudacionTotal() > 3 * this.getPresupuesto();

        float recaudacion_FR = 0, recaudacion_GR = 0, recaudacion_IT = 0, recaudacion_UK = 0;
        for (Map.Entry<String, Float> kvRecaudacionActor : this.getRecaudacion().entrySet())
        {
            switch (kvRecaudacionActor.getKey())
            {
                case "Francia":
                    recaudacion_FR += kvRecaudacionActor.getValue()*0.2;
                    break;
                case "Alemania":
                    recaudacion_GR += kvRecaudacionActor.getValue()*0.2;
                    break;
                case "Italia":
                    recaudacion_IT += kvRecaudacionActor.getValue()*0.2;
                    break;
                case "Reino Unido":
                    recaudacion_UK += kvRecaudacionActor.getValue()*0.2;
                    break;
            }
        }
        float sumaPaises = recaudacion_GR+recaudacion_FR+recaudacion_UK+recaudacion_IT;


        float recaudacionTotal = this.recaudacionTotal()-this.getRecaudacion().get("Francia")-this.getRecaudacion().get("Italia")-this.getRecaudacion().get("Alemania")+sumaPaises;

        float sumaCacheActores = 0;
        this.getActores().get(null);

        return this.recaudacionTotal() > sumaCacheActores;
    }


}
