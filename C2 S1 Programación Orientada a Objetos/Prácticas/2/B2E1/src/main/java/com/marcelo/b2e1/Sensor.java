/**
 * @Author Marcelo Fort Muñoz
 */
package com.marcelo.b2e1;

import java.util.ArrayList;

public class Sensor
{
    private static final String[] TIPOS_VALIDOS ={"temperatura","sonido","luz","humedad"};

    /// ATRIBUTOS: ///
    /**
     * Identificador del sensor.
     */
    private String id;
    /**
     * Tipo de sensor.
     */
    private String tipo;
    /**
     * Nombre de la estancia en la que se encuentra instalado el sensor
     */
    private Estancia estancia;
    /**
     * Conjunto de datos que ha sido capturado por el sensor. El dato más
     * reciente deberá estar en la última posición y el más antiguo en la primera
     */
    private ArrayList<Float> datos;
    /**
     * : Rango de valores que puede tomar el sensor.
     */
    private Float[] rango;
    /**
     * Precio del sensor.
     */
    private Float precio;

    /// Constructores ///

    /**
     * @param id
     * @param tipo
     * @param rango
     * @param precio
     */
    Sensor(String id, String tipo, float[] rango, float precio)
    {
        if (id == null || tipo == null)
        {
            System.out.println("ERROR: Se ha pasado un argumento nulo.");
            return;
        }
        if (rango.length < 2)
        {
            System.out.println("ERROR: El campo rango ha de tener 2 valores");
            return;
        }

        this.id = id;

        boolean tipoValido=false;
        for(String tipo:TIPOS_VALIDOS)
        {
            if(tipo.contentEquals(tipo))
            {
                this.tipo = tipo;
                tipoValido=true;
            }
        }
        if(!tipoValido)
        {
            System.out.println("ERROR: El tipo no se encuentra entre los admitidos");
            return;
        }

        Float[] nuevoRango = new Float[2];
        nuevoRango[0] = rango[0];
        nuevoRango[1] = rango[1];
        this.rango = nuevoRango;

    }
}

