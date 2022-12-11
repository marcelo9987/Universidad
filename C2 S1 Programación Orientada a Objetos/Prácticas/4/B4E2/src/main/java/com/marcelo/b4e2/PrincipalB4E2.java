package com.marcelo.b4e2;

import java.util.*;

public class PrincipalB4E2
{
    public static void main(String[] args) throws ExcepcionActor, ExcepcionPelicula, ExcepcionDirector
    {
        //********************************************//
        System.out.println("    *** a:");
        
        HashSet<String> especialista2 = new HashSet<>(Arrays.asList("Ficcion", "Guerra", "Thriller"));
        
        HashMap<String, Float> cache2 = new HashMap<String, Float>();
        cache2.put("Ficcion", 4.00f);
        cache2.put("Guerra", 8f);
        cache2.put("Thriller", 5f);
        
        Director director2 = null;
        try
        {
            director2 = new Director("Christopher Nolan", especialista2, cache2);
        }
        catch (ExcepcionParticipante e)
        {
            System.out.println("No se puede crear el director: " + e.getMessage());
        }
        
        HashMap<String, Float> recaudacionPelicula2 = new HashMap<>();
        
        recaudacionPelicula2.put("EE.UU", 50f);
        recaudacionPelicula2.put("España", 8f);
        recaudacionPelicula2.put("Italia", 8f);
        recaudacionPelicula2.put("Alemania", 10f);
        recaudacionPelicula2.put("Francia", 5f);
        recaudacionPelicula2.put("Reino Unido", 15f);
        recaudacionPelicula2.put("Polonia", 4f);
        
        Pelicula pelicula2 = null;
        try
        {
            pelicula2 = new Ficcion(null, 2014, 169, director2, recaudacionPelicula2);
        }
        catch (ExcepcionPelicula excp)
        {
            System.out.println("No se puede crear la película 2: " + excp.getMessage());
        }
        
        //********************************************//
        System.out.println("    *** b:");
        
        try
        {
            pelicula2 = new Ficcion("Interstellar", 2030, 169, director2, recaudacionPelicula2);
        }
        catch (ExcepcionPelicula excp)
        {
            System.out.println("No se puede crear la película 2: " + excp.getMessage());
        }
        
        //********************************************//
        System.out.println("    *** c:");
        
        System.out.println("Características de la película 2: " + pelicula2);
        
        //********************************************//
        System.out.println("    *** d:");
        try
        {
            pelicula2 = new Ficcion("Interstellar", 2014, 169, director2, recaudacionPelicula2);
        }
        catch (ExcepcionPelicula excp)
        {
            System.out.println("No se puede crear la película 2: " + excp.getMessage());
        }
        
        
        //********************************************//
        System.out.println("    *** e:");
        
        System.out.println("Características de la película 2: " + pelicula2);
        
        
        //********************************************//
        System.out.println("    *** f:");
        
        try
        {
            pelicula2.setAnho(2027);
        }
        catch (ExcepcionPelicula excp)
        {
            System.out.println("No se puede modificar el año de la película " + pelicula2.getNombre() + ": " + excp.getMessage());
        }
        
        //********************************************//
        System.out.println("    *** g:");
        
        System.out.println("Características de la película 2: " + pelicula2);
        
        
        //********************************************//
        System.out.println("    *** h:");
        
        HashMap<String, Float> recaudacionPelicula3 = new HashMap<>();
        
        recaudacionPelicula3.put("EE.UU", 120f);
        recaudacionPelicula3.put("España", 30f);
        recaudacionPelicula3.put("Italia", 30f);
        recaudacionPelicula3.put("Alemania", 50f);
        recaudacionPelicula3.put("Francia", 25f);
        recaudacionPelicula3.put("Reino Unido", 24f);
        recaudacionPelicula3.put("Polonia", 21f);
        
        Pelicula pelicula3 = null;
        try
        {
            pelicula3 = new Ficcion("Origen", 2010, -35, director2, recaudacionPelicula3);
        }
        catch (ExcepcionPelicula excp)
        {
            System.out.println("No se puede crear la película 3: " + excp.getMessage());
        }
        
        
        //********************************************//
        System.out.println("    *** i:");
        
        System.out.println("Características de la película 3: " + pelicula3);
        
        
        //********************************************//
        System.out.println("    *** j:");
        
        try
        {
            pelicula3 = new Ficcion("Origen", 2010, 148, director2, recaudacionPelicula3);
        }
        catch (ExcepcionPelicula excp)
        {
            System.out.println("No se puede crear la película 3: " + excp.getMessage());
        }
        
        
        //********************************************//
        System.out.println("    *** k:");
        
        System.out.println("Características de la película 3: " + pelicula3);
        
        
        //********************************************//
        System.out.println("    *** l:");
        
        try
        {
            pelicula3.setAnho(4);
        }
        catch (ExcepcionPelicula excp)
        {
            System.out.println("No se puede modificar el año de la película " + pelicula3.getNombre() + ": " + excp.getMessage());
        }
        
        
        //********************************************//
        System.out.println("    *** m:");
        
        System.out.println("Características de la película 3: " + pelicula3);
        
        
        //********************************************//
        System.out.println("    *** n:");
        Actor actor3 = null;
        try
        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Christofer Nolan");
            deseos.add("Woody Alen");
            deseos.add("Martin Scorsese");
            actor3 = new Actor(null, deseos, 25);
            
        }
        catch (ExcepcionParticipante excp)
        {
            System.out.println("No se puede crear el actor: " + excp.getMessage());
        }
        
        
        //********************************************//
        System.out.println("    *** o:");
        
        System.out.println("Características del actor 3: " + actor3);
        
        
        //********************************************//
        System.out.println("    *** p:");
        try
        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Christofer Nolan");
            deseos.add("Woody Alen");
            deseos.add("Martin Scorsese");
            actor3 = new Actor("Matthew McConaughey", deseos, 0);
            
        }
        catch (ExcepcionParticipante excp)
        {
            System.out.println("No se puede crear el actor: " + excp.getMessage());
        }
        
        
        //********************************************//
        System.out.println("    *** q:");
        
        System.out.println("Características del actor 3: " + actor3);
        
        
        //********************************************//
        System.out.println("    *** r:");
        try
        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Christofer Nolan");
            deseos.add("Woody Alen");
            deseos.add("Martin Scorsese");
            actor3 = new Actor("Matthew McConaughey", deseos, 25);
            
        }
        catch (ExcepcionParticipante excp)
        {
            System.out.println("No se puede crear el actor: " + excp.getMessage());
        }
        
        
        //********************************************//
        System.out.println("    *** s:");
        
        System.out.println("Características del actor 3: " + actor3);
        
        
        //********************************************//
        System.out.println("    *** t:");
        try
        {
            actor3.setCache(-400);
        }
        catch (ExcepcionActor excp)
        {
            System.out.println("No se puede modificar el cache del actor " + actor3.getNombre() + ": " + excp.getMessage());
        }
        
        
        //********************************************//
        System.out.println("    *** u:");
        
        System.out.println("Características del actor 3: " + actor3);
        
        
        //********************************************//
        System.out.println("    *** v:");
        try
        {
            System.out.println("importancia del actor3 entre los 'figurantes': " + actor3.importancia("figurantes"));
        }
        catch (ExcepcionActor excp)
        {
            System.out.println(excp.getMessage());
        }
        
        
        //********************************************//
        System.out.println("    *** w:");
        try
        {
            System.out.println("importancia del actor3 entre los actores secundarios: " + actor3.importancia("secundario"));
        }
        catch (ExcepcionActor excp)
        {
            System.out.println(excp.getMessage());
        }
        
        
        //********************************************//
        System.out.println("    *** x:");
        ArrayList<String> listaDeseos = new ArrayList<>();
        
        
        //********************************************//
        System.out.println("    *** y:");
        try
        {
            actor3.setDeseos(listaDeseos);
        }
        catch (ExcepcionActor excp)
        {
            System.out.println("No se pueden modificar los deseos del actor " + actor3.getNombre() + ": " + excp.getMessage());
        }
        
        
        //********************************************//
        System.out.println("    *** z:");
        try
        {
            actor3.setDeseos(null);
        }
        catch (ExcepcionActor excp)
        {
            System.out.println("No se pueden modificar los deseos del actor " + actor3.getNombre() + ": " + excp.getMessage());
        }
        
        
        //********************************************//
        System.out.println("    *** aa:");
        
        System.out.println("Características del actor 3: " + actor3);
        
        
        //********************************************//
        System.out.println("    *** bb:");
        try
        {
            director2 = new Director(null, especialista2, cache2);
        }
        catch (ExcepcionParticipante e)
        {
            System.out.println("No se puede crear el director: " + e.getMessage());
        }
        
        
        //********************************************//
        System.out.println("    *** cc:");
        
        System.out.println("Características del director 2: " + director2);
        
        
        //********************************************//
        System.out.println("    *** dd:");
        try
        {
            director2 = new Director("Christopher Nolan", especialista2, cache2);
        }
        catch (ExcepcionParticipante e)
        {
            System.out.println("No se puede crear el director: " + e.getMessage());
        }
        
        
        //********************************************//
        System.out.println("    *** ee:");
        Set<String> setNuevoEspecialista = new HashSet<>();
        
        
        //********************************************//
        System.out.println("    *** ff:");
        try
        {
            director2.setEspecialista(setNuevoEspecialista);
        }
        catch (ExcepcionDirector excp)
        {
            System.out.println("No se puede modificar el atributo especialista del director " + director2.getNombre() + ": " + excp.getMessage());
        }
        
        
        //********************************************//
        System.out.println("    *** gg:");
        try
        {
            director2.setEspecialista(null);
        }
        catch (ExcepcionDirector excp)
        {
            System.out.println("No se puede modificar el atributo especialista del director " + director2.getNombre() + ": " + excp.getMessage());
        }
    
    
        //********************************************//
        System.out.println("    *** hh:");
    
        System.out.println("Características del director 2: " + director2);
    
    
    
        //********************************************//
        System.out.println("    *** ii:");
        setNuevoEspecialista.add("Gore");
    
    
        //********************************************//
        System.out.println("    *** jj:");
        try
        {
            director2.setEspecialista(setNuevoEspecialista);
        }
        catch (ExcepcionDirector excp)
        {
            System.out.println("No se puede modificar el atributo especialista del director " + director2.getNombre() + ": " + excp.getMessage());
        }
    
    
        //********************************************//
        System.out.println("    *** kk:");
    
        System.out.println("Características del director 2: " + director2);
        
        
    }
}