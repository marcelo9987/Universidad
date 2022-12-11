package com.marcelo.b4e1;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;

public class PrincipalB4E1
{
    public static void main(String[] args)
    {
        System.out.println("a:");
        Actor actor1,actor2,actor3,actor4;
    
        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Steven Spielberg");
            deseos.add("Martin Scorsese");
            actor1 = new Actor("Cameron Diaz", deseos, 20);
        }
    
        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Steven Spielberg");
            deseos.add("Martin Scorsese");
            actor2 = new Actor("Ben Stiller", deseos, 15);
        }
    
        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Christofer Nolan");
            deseos.add("Woody Alen");
            deseos.add("Martin Scorsese");
            actor3 = new Actor("Matthew McConaughey", deseos, 25);
        }
    
        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Christopher Nolan");
            deseos.add("Woody Alen");
            deseos.add("Martin Scorsese");
            actor4 = new Actor("Anne Hathaway", deseos, 30);
        }
    
        System.out.println("\n");
        
    
        System.out.println("b:");
        
        {
            Actor[] actores1a4={actor1,actor2,actor3,actor4};
            for(Actor actor:actores1a4)
            {
                System.out.println(actor);
            }
        }
        System.out.println("\n");
        
        
        System.out.println("e: ");
        
        HashSet<String> especialista1 = new HashSet<>(Arrays.asList("ComediaRomantica", "ComediaNegra"));
        HashMap<String, Float> cache1 = new HashMap<>();
    
        cache1.put("ComediaRomantica", 2.00f);
        cache1.put("ComediaNegra", 1.5f);
    
        Director director1 = new Director("Hermanos Farrelly", especialista1, cache1);
        HashSet<String> especialista2 = new HashSet<>(Arrays.asList("Ficcion", "Guerra", "Thriller"));
    
        HashMap<String, Float> cache2 = new HashMap<String, Float>();
        cache2.put("Ficcion", 4.00f);
        cache2.put("Guerra", 8f);
        cache2.put("Thriller", 5f);
        Director director2 = new Director("Cristopher Nolan", especialista2, cache2);
    
        System.out.println("\n");
    
        
        System.out.println("f:");
    
        {
            Director[] director1a2={director1,director2};
            for(Director director:director1a2)
            {
                System.out.println(director);
            }
        }
    
        System.out.println("\n");
    
    
        System.out.println("c:");
        
        HashMap<String, Float> recaudacionPelicula1 = new HashMap<>();
        recaudacionPelicula1.put("EE.UU", 40f);
        recaudacionPelicula1.put("España", 8f);
        recaudacionPelicula1.put("Italia", 9f);
        recaudacionPelicula1.put("Alemania", 10f);
        recaudacionPelicula1.put("Francia", 8f);
        recaudacionPelicula1.put("Reino Unido", 8f);
        recaudacionPelicula1.put("Polonia", 5f);
        
        Pelicula pelicula1 = new ComediaRomantica("Algo pasa con Mary", 1998, null, director1, recaudacionPelicula1);
        
        
        HashMap<String, Float> recaudacionPelicula2 = new HashMap<>();
    
        recaudacionPelicula2.put("EE.UU", 50f);
        recaudacionPelicula2.put("España", 8f);
        recaudacionPelicula2.put("Italia", 8f);
        recaudacionPelicula2.put("Alemania", 10f);
        recaudacionPelicula2.put("Francia", 5f);
        recaudacionPelicula2.put("Reino Unido", 15f);
        recaudacionPelicula2.put("Polonia", 4f);
        
        Pelicula pelicula2 = new Ficcion("Interstellar", 2014, 169, director2, recaudacionPelicula2);
    
    
        HashMap<String, Float> recaudacionPelicula3 = new HashMap<>();
        recaudacionPelicula3.put("EE.UU", 120f);
        recaudacionPelicula3.put("España", 30f);
        recaudacionPelicula3.put("Italia", 30f);
        recaudacionPelicula3.put("Alemania", 50f);
        recaudacionPelicula3.put("Francia", 25f);
        recaudacionPelicula3.put("Reino Unido", 24f);
        recaudacionPelicula3.put("Polonia", 21f);
        
        Pelicula pelicula3 = new Ficcion("Origen", 2010, 148, director2, recaudacionPelicula3);
        
        HashMap<String, Float> recaudacionPelicula4 = new HashMap<>();
        recaudacionPelicula4.put("EE.UU", 180f);
        recaudacionPelicula4.put("España", 80f);
        recaudacionPelicula4.put("Italia", 50f);
        recaudacionPelicula4.put("Alemania", 40f);
        recaudacionPelicula4.put("Francia", 40f);
        recaudacionPelicula4.put("Reino Unido", 80f);
        recaudacionPelicula4.put("Polonia", 30f);
    
        Pelicula pelicula4 = new Ficcion("El caballero Oscuro", 2008, 152, director2, recaudacionPelicula4);
    
    
        //Uso la función asList para introducir los actores en una línea. Esta función devuelve una Lista.
        if (!pelicula1.darAlta("principal", new ArrayList<>(Arrays.asList(actor1, actor2))))
        {
            System.out.println("Los actores principales de la película 1 no han sido dados de alta correctamente.");
        }
    
        if (!pelicula2.darAlta("principal", new ArrayList<>(Arrays.asList(actor3, actor4))))
        {
            System.out.println("Los actores principales de la película 2 no han sido dados de alta correctamente.");
        }
//        if (!pelicula2.darAlta("secundario", new ArrayList<>(Arrays.asList(actor13, actor9))))
//        {
//            System.out.println("Los actores secundarios de la película 2 no han sido dados de alta correctamente.");
//        }
    
//        if (!pelicula3.darAlta("principal", new ArrayList<>(Arrays.asList(actor5, actor6))))
//        {
//            System.out.println("Los actores principales de la película 3 no han sido dados de alta correctamente.");
//        }
//        if (!pelicula3.darAlta("secundario", new ArrayList<>(Collections.singletonList(actor13))))
//        {
//            System.out.println("Los actores secundarios de la película 3 no han sido dados de alta correctamente.");
//        }
    
        if (!pelicula4.darAlta("principal", new ArrayList<>(Arrays.asList(/*actor7, actor8, */actor4))))
        {
            System.out.println("Los actores principales de la película 4 no han sido dados de alta correctamente.");
        }
//        if (!pelicula4.darAlta("secundario", new ArrayList<>(Arrays.asList(actor13, actor14))))
//        {
//            System.out.println("Los actores secundarios de la película 4 no han sido dados de alta correctamente.");
//        }
        
        
        System.out.println("\n");
    
        System.out.println("d:");
        for(Pelicula pelicula: new Pelicula[]{pelicula1, pelicula2, pelicula3, pelicula4})
        {
            System.out.println(pelicula);
        }
        System.out.println("\n");
    
        System.out.println("g:");
        System.out.println(pelicula1.numeroActores());
        System.out.println(pelicula2.numeroActores());
        System.out.println("\n");
        
        System.out.println("h:");
        System.out.println(pelicula1.costeActores());
        System.out.println(pelicula2.costeActores());
        System.out.println("\n");
        
        System.out.println("i:");
        System.out.println(IActor.participa("Leonardo DiCaprio",pelicula2));
        System.out.println(pelicula2.costeActores());
        System.out.println("\n");
        
        System.out.println("i:");
        System.out.println(IActor.participa("Leonardo DiCaprio",pelicula2));
        System.out.println(pelicula2.costeActores());
        System.out.println("\n");
    }
}