package com.marcelo.b2e3;

import java.util.*;

public class Planta
{
    public static final String[] TIPOS_VALIDOS_PLANTA = {"oficinas", "viviendas libres",};
    /// ATRIBUTOS ///
    private int numero;
    private String tipo;
    private Edificio edificio;
    private HashMap<String, Estancia> estancias;
    private float presupuesto;
    private HashMap<String, Sensor> sensoresConProblemas;

    Planta(int numero, String tipo, Edificio edificio, HashMap<String, Estancia> estancias)
    {
        if (tipo == null ||estancias == null || edificio==null || estancias.isEmpty())
        {
            System.out.println("Argumento incorrecto, no se puede crear el objeto");
            return;
        }

        boolean tipo_valido = false;
        for (String tipoA : TIPOS_VALIDOS_PLANTA)
        {
            if (tipoA.equals(tipo))
            {
                tipo_valido = true;
            }
        }
        if (!tipo_valido)
        {

            System.out.println("ERROR: El tipo no se encuentra entre los admitidos, no se ha creado el objeto con éxito");
            return;
        }

        this.numero = numero;
        this.tipo = tipo;
        this.edificio=edificio;
        this.estancias = estancias;
        this.sensoresConProblemas = new HashMap<>();
    }

    Planta (int numero, String tipo)
    {
        if(tipo == null)
        {
            System.out.println("Argumento incorrecto, no se puede crear el objeto");
            return;
        }

        boolean tipo_valido = false;
        for (String tipoA : TIPOS_VALIDOS_PLANTA)
        {
            if (tipoA.equals(tipo))
            {
                tipo_valido = true;
            }
        }
        if (!tipo_valido)
        {

            System.out.println("ERROR: El tipo no se encuentra entre los admitidos, no se ha creado el objeto con éxito");
            return;
        }

        this.numero=numero;
        this.tipo=tipo;
        //todo: ¿He de crear un edificio?
        this.estancias = new HashMap<>();
        this.sensoresConProblemas=new HashMap<>();


    }
    public boolean darAltaEstancia(ArrayList<Estancia> estancias)
    {
        if(estancias==null || estancias.isEmpty())
        {
            return false;
        }
        for (Estancia estancia:estancias)
        {
            if(estancia==null || estancia.getPlanta()!=this.numero)
            {
                return false;
            }
        }
        for(Estancia estancia:estancias)
        {
            this.estancias.put(estancia.getNombre(),estancia);
        }
        return true;
    }

    public boolean darAlta(Estancia estancia)
    {
        if(estancia==null || estancia.)
    }

}
