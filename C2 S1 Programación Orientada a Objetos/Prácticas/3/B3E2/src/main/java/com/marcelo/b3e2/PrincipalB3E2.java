package com.marcelo.b3e2;

import java.util.*;

public class PrincipalB3E2
{
    public static void main(String[] args)
    {
        //a. Crear las instancias del conjunto de actores indicados en el fichero Excel (B3E1_instancias.xls)
        System.out.println("a: ");
        Actor actor1, actor2, actor3, actor4, actor5, actor6, actor7, actor8, actor9, actor10;
        Actor actor11, actor12, actor13, actor14, actor15, actor16, actor17, actor18, actor19, actor20;

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

        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Christopher Nolan");
            deseos.add("Quentin tarantino");
            deseos.add("Clint Eastwood");
            actor5 = new Actor("Leonardo DiCaprio", deseos, 50);
        }

        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Christopher Nolan");
            deseos.add("David Fincher");
            deseos.add("Pedro Almodóvar");
            deseos.add("Roger Mitchell");
            actor6 = new Actor("Marion Cotillard", deseos, 15);
        }

        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Quentin Tarantino");
            deseos.add("David Fincher");
            deseos.add("Francis Ford Coppola");
            deseos.add("Clint Eastwood");
            deseos.add("Tim Burton");
            actor7 = new Actor("Christian Bale", deseos, 20);
        }

        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Martin Scorsese");
            deseos.add("James Cameron");
            deseos.add("Alejandro Amenábar");
            deseos.add("Clint Eastwood");
            deseos.add("Guillermo del Toro");
            actor8 = new Actor("Gary Oldman", deseos, 20);
        }

        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Christopher Nolan");
            deseos.add("Greta Gerwig");
            deseos.add("Steven Spielberg");
            deseos.add("Woody Allen");
            actor9 = new Actor("Matt Damon", deseos, 40);
        }

        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Quentin Tarantino");
            deseos.add("M. Night Shymalan");
            deseos.add("Paul Thomas Anderson");
            actor10 = new Actor("Daniel Day-Lewis", deseos, 70);
        }

        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Ridley Scott");
            deseos.add("Sofia Coppola");
            deseos.add("Danny Boyle");
            deseos.add("Hermanos Coen");
            actor11 = new Actor("Jhon Travolta", deseos, 25);
        }

        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Steven Spielberg");
            deseos.add("M. Night Shymalan");
            deseos.add("Martin Scorsese");
            deseos.add("Alfonso Carón ");
            actor12 = new Actor("Bruce Willis", deseos, 30);
        }

        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Steven Soderberg");
            deseos.add("Sofia Coppola");
            deseos.add("Paul Haggis");
            deseos.add("Steven Soderberg");
            actor13 = new Actor("Michael Caine", deseos, 10);
        }

        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Steven Spielberg");
            deseos.add("Ridley Scott");
            deseos.add("James Cameron");
            deseos.add("Martin Scorsese");
            actor14 = new Actor("Morgan Freeman", deseos, 15);
        }

        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Ridley Scott");
            deseos.add("Jean Jacques Annaud");
            deseos.add("Roman Polanski");
            deseos.add("Woody Allen");
            actor15 = new Actor("Jack Nicholson", deseos, 20);
        }

        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Quentin Tarantino");
            deseos.add("Sofia Coppola");
            deseos.add("J.J. Abrahams");
            deseos.add("M. Night Shymalan");
            actor16 = new Actor("Liam Neeson", deseos, 20);
        }

        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Martin Scorsese");
            deseos.add("Cristopher Nolan");
            deseos.add("J.J. Abrahams");
            deseos.add("Sofia Coppola");
            actor17 = new Actor("Al pacino", deseos, 50);
        }

        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Sofia Coppola");
            deseos.add("Quentin Tarantino");
            deseos.add("Martin Scorsese");
            deseos.add("Clint Eastwood");

            actor18 = new Actor("Julia Roberts", deseos, 80);
        }

        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Quentin Tarantino");
            deseos.add("Clint Eastwood");
            deseos.add("Greta Gerwig");
            deseos.add("Mel Gibson");

            actor19 = new Actor("Hugh Grant", deseos, 55);
        }

        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Martin Scorsese");
            deseos.add("Sofia Coppola");
            deseos.add("Paul Haggis");

            actor20 = new Actor("Brad Pitt", deseos, 80);
        }
        System.out.println("\n");


        System.out.println("b: ");

        HashSet<String> especialista1 = new HashSet<>(Arrays.asList("ComediaRomantica", "ComediaNegra"));
        HashMap<String, Float> cache1 = new HashMap<>();

        cache1.put("ComediaRomantica", 2.00f);
        cache1.put("ComediaNegra", 1.5f);


        Director director1 = new Director("Hermanos Farrelly", especialista1, cache1);

        HashMap<String, Float> recaudacionPelicula1 = new HashMap<>();
        recaudacionPelicula1.put("EE.UU", 40f);
        recaudacionPelicula1.put("España", 8f);
        recaudacionPelicula1.put("Italia", 9f);
        recaudacionPelicula1.put("Alemania", 10f);
        recaudacionPelicula1.put("Francia", 8f);
        recaudacionPelicula1.put("Reino Unido", 8f);
        recaudacionPelicula1.put("Polonia", 5f);


        Pelicula pelicula1 = new ComediaRomantica("Algo pasa con Mary", 1998, null, director1, recaudacionPelicula1);


        HashSet<String> especialista2 = new HashSet<>(Arrays.asList("Ficcion", "Guerra", "Thriller"));

        HashMap<String, Float> cache2 = new HashMap<String, Float>();
        cache2.put("Ficcion", 4.00f);
        cache2.put("Guerra", 8f);
        cache2.put("Thriller", 5f);


        Director director2 = new Director("Cristopher Nolan", especialista2, cache2);

        HashMap<String, Float> recaudacionPelicula2 = new HashMap<>();

        recaudacionPelicula2.put("EE.UU", 50f);
        recaudacionPelicula2.put("España", 8f);
        recaudacionPelicula2.put("Italia", 8f);
        recaudacionPelicula2.put("Alemania", 10f);
        recaudacionPelicula2.put("Francia", 5f);
        recaudacionPelicula2.put("Reino Unido", 15f);
        recaudacionPelicula2.put("Polonia", 4f);


        Pelicula pelicula2 = new Ficcion("Interstellar", 2014, 169, director2, recaudacionPelicula2);
        Set<String> especialista3 = new HashSet<>();
        especialista3.add("Thriller");
        especialista3.add("Psicologico");

        HashMap<String, Float> cache3 = new HashMap<>();
        cache3.put("Thriller", 4.0f);
        cache3.put("Psicologico", 6.00f);

        Director director3 = new Director("Martin Scorsese", especialista3, cache3);

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

        HashMap<String, Float> recaudacionPelicula5 = new HashMap<>();
        recaudacionPelicula5.put("EE.UU", 30f);
        recaudacionPelicula5.put("España", 5f);
        recaudacionPelicula5.put("Italia", 10f);
        recaudacionPelicula5.put("Alemania", 10f);
        recaudacionPelicula5.put("Francia", 8f);
        recaudacionPelicula5.put("Reino Unido", 15f);
        recaudacionPelicula5.put("Polonia", 2f);

        Pelicula pelicula5 = new Thriller("Infiltrados", 2006, 151, director3, recaudacionPelicula5);

        HashMap<String, Float> recaudacionPelicula6 = new HashMap<>();
        recaudacionPelicula6.put("EE.UU", 20f);
        recaudacionPelicula6.put("España", 5f);
        recaudacionPelicula6.put("Italia", 5f);
        recaudacionPelicula6.put("Alemania", 10f);
        recaudacionPelicula6.put("Francia", 12f);
        recaudacionPelicula6.put("Reino Unido", 13f);
        recaudacionPelicula6.put("Polonia", 5f);

        Pelicula pelicula6 = new Thriller("Gans of New York", 2002, 166, director3, recaudacionPelicula6);

        Set<String> especialista4 = new HashSet<>();
        especialista4.add("ComediaNegra");
        especialista4.add("Ficcion");
        especialista4.add("Guerra");

        HashMap<String, Float> cache4 = new HashMap<>();
        cache4.put("ComediaNegra", 5.0f);
        cache4.put("Ficcion", 4.50f);
        cache4.put("Guerra", 4.00f);

        Director director4 = new Director("Quentin Tarantino", especialista4, cache4);

        HashMap<String, Float> recaudacionPelicula7 = new HashMap<>();
        recaudacionPelicula7.put("EE.UU", 15f);
        recaudacionPelicula7.put("España", 3f);
        recaudacionPelicula7.put("Italia", 4f);
        recaudacionPelicula7.put("Alemania", 8f);
        recaudacionPelicula7.put("Francia", 7f);
        recaudacionPelicula7.put("Reino Unido", 10f);
        recaudacionPelicula7.put("Polonia", 3f);

        Pelicula pelicula7 = new ComediaNegra("Pulp Fiction", 1994, 153, director4, recaudacionPelicula7);

        Set<String> especialista5 = new HashSet<>();
        especialista5.add("Psicologico");
        especialista5.add("Ficcion");
        especialista5.add("TerrorGotico");

        HashMap<String, Float> cache5 = new HashMap<>();
        cache5.put("Psicologico", 5.0f);
        cache5.put("Ficcion", 1.50f);
        cache5.put("TerrorGotico", 2.00f);

        Director director5 = new Director("M. Night Shymalan", especialista5, cache5);

        HashMap<String, Float> recaudacionPelicula8 = new HashMap<>();

        recaudacionPelicula8.put("EE.UU", 35f);
        recaudacionPelicula8.put("España", 5f);
        recaudacionPelicula8.put("Italia", 5f);
        recaudacionPelicula8.put("Alemania", 10f);
        recaudacionPelicula8.put("Francia", 15f);
        recaudacionPelicula8.put("Reino Unido", 11f);
        recaudacionPelicula8.put("Polonia", 9f);

        Pelicula pelicula8 = new Psicologico("El sexto Sentido", 1999, 107, director5, recaudacionPelicula8);

        Set<String> especialista6 = new HashSet<>();
        especialista6.add("ComediaRomantica");
        especialista6.add("Parodia");

        HashMap<String, Float> cache6 = new HashMap<>();
        cache6.put("ComediaRomantica", 3.0f);
        cache6.put("Parodia", 2.50f);

        Director director6 = new Director("M. Night Shymalan", especialista6, cache6);

        HashMap<String, Float> recaudacionPelicula9 = new HashMap<>();

        recaudacionPelicula9.put("EE.UU", 40f);
        recaudacionPelicula9.put("España", 10f);
        recaudacionPelicula9.put("Italia", 10f);
        recaudacionPelicula9.put("Alemania", 15f);
        recaudacionPelicula9.put("Francia", 14f);
        recaudacionPelicula9.put("Reino Unido", 24f);
        recaudacionPelicula9.put("Polonia", 11f);

        Pelicula pelicula9 = new ComediaRomantica("Noting Hill", 1999, 166, director6, recaudacionPelicula9);

        Set<String> especialista7 = new HashSet<>();
        //especialista7.add("DeRobos");
        especialista7.add("Robos");
        especialista7.add("Thriller");
        especialista7.add("Ficcion");

        HashMap<String, Float> cache7 = new HashMap<>();
        //cache7.put("DeRobos", 4f);
        cache7.put("Robos", 4f);
        cache7.put("Thriller", 5f);
        cache7.put("Ficcion", 6f);

        Director director7 = new Director("M. Night Shymalan", especialista7, cache7);

        HashMap<String, Float> recaudacionPelicula10 = new HashMap<>();

        recaudacionPelicula10.put("EE.UU", 120f);
        recaudacionPelicula10.put("España", 24f);
        recaudacionPelicula10.put("Italia", 35f);
        recaudacionPelicula10.put("Alemania", 35f);
        recaudacionPelicula10.put("Francia", 60f);
        recaudacionPelicula10.put("Reino Unido", 80f);
        recaudacionPelicula10.put("Polonia", 44f);

        Pelicula pelicula10 = new Robos("Ocean 11", 2011, 117, director7, recaudacionPelicula10);

        //Uso la función asList para introducir los actores en una línea. Esta función devuelve una Lista.
        if (!pelicula1.darAlta("principal", new ArrayList<>(Arrays.asList(actor1, actor2))))
        {
            System.out.println("Los actores principales de la película 1 no han sido dados de alta correctamente.");
        }

        if (!pelicula2.darAlta("principal", new ArrayList<>(Arrays.asList(actor3, actor4))))
        {
            System.out.println("Los actores principales de la película 2 no han sido dados de alta correctamente.");
        }
        if (!pelicula2.darAlta("secundario", new ArrayList<>(Arrays.asList(actor13, actor9))))
        {
            System.out.println("Los actores secundarios de la película 2 no han sido dados de alta correctamente.");
        }

        if (!pelicula3.darAlta("principal", new ArrayList<>(Arrays.asList(actor5, actor6))))
        {
            System.out.println("Los actores principales de la película 3 no han sido dados de alta correctamente.");
        }
        if (!pelicula3.darAlta("secundario", new ArrayList<>(Collections.singletonList(actor13))))
        {
            System.out.println("Los actores secundarios de la película 3 no han sido dados de alta correctamente.");
        }

        if (!pelicula4.darAlta("principal", new ArrayList<>(Arrays.asList(actor7, actor8, actor4))))
        {
            System.out.println("Los actores principales de la película 4 no han sido dados de alta correctamente.");
        }
        if (!pelicula4.darAlta("secundario", new ArrayList<>(Arrays.asList(actor13, actor14))))
        {
            System.out.println("Los actores secundarios de la película 4 no han sido dados de alta correctamente.");
        }

        if (!pelicula5.darAlta("principal", new ArrayList<>(Arrays.asList(actor5, actor9))))
        {
            System.out.println("Los actores principales de la película 5 no han sido dados de alta correctamente.");
        }
        if (!pelicula5.darAlta("secundario", new ArrayList<>(Arrays.asList(actor17, actor15))))
        {
            System.out.println("Los actores secundarios de la película 5 no han sido dados de alta correctamente.");
        }

        if (!pelicula6.darAlta("principal", new ArrayList<>(Arrays.asList(actor1, actor5, actor10))))
        {
            System.out.println("Los actores principales de la película 6 no han sido dados de alta correctamente.");
        }
        if (!pelicula6.darAlta("secundario", new ArrayList<>(Arrays.asList(actor16))))
        {
            System.out.println("Los actores secundarios de la película 6 no han sido dados de alta correctamente.");
        }

        if (!pelicula7.darAlta("principal", new ArrayList<>(Arrays.asList(actor11))))
        {
            System.out.println("Los actores principales de la película 7 no han sido dados de alta correctamente.");
        }
        if (!pelicula7.darAlta("secundario", new ArrayList<>(Arrays.asList(actor12))))
        {
            System.out.println("Los actores secundarios de la película 7 no han sido dados de alta correctamente.");
        }

        Actor haleyJoelOsment;
        {
            ArrayList<String> deseos = new ArrayList<>();

            haleyJoelOsment = new Actor("Haley Joel Osment", null, 120);
        }
        if (!pelicula8.darAlta("principal", new ArrayList<>(Arrays.asList(actor12, haleyJoelOsment))))
        {
            System.out.println("Los actores principales de la película 8 no han sido dados de alta correctamente.");
        }

        if (!pelicula9.darAlta("principal", new ArrayList<>(Arrays.asList(actor18, actor19))))
        {
            System.out.println("Los actores principales de la película 9 no han sido dados de alta correctamente.");
        }

        if (!pelicula10.darAlta("principal", new ArrayList<>(Arrays.asList(actor18, actor9, actor20))))
        {

            System.out.println("Los actores principales de la película 10 no han sido dados de alta correctamente.");
        }

        System.out.println("\n");

        System.out.println("c:");
        {
            Director[] todosLosDirectores = {director1, director2, director3, director4, director5, director6, director7};
            for (Director director : todosLosDirectores)
            {
                System.out.println("Director: " + director.getNombre());
                System.out.println(director);
                System.out.println("\n");
            }
        }

        System.out.println("\n");

        System.out.println("d:");
        director1.introducirPelicula(pelicula1);

        director2.introducirPelicula(pelicula2);
        director2.introducirPelicula(pelicula3);
        director2.introducirPelicula(pelicula4);

        director3.introducirPelicula(pelicula5);
        director3.introducirPelicula(pelicula6);


        director4.introducirPelicula(pelicula7);

        director5.introducirPelicula(pelicula8);

        director6.introducirPelicula(pelicula9);

        director7.introducirPelicula(pelicula10);
        System.out.println("\n");

        System.out.println("e: ");
        {
            Director[] todosLosDirectores = {director1, director2, director3, director4, director5, director6, director7};
            for (Director director : todosLosDirectores)
            {
                System.out.println("Director" + director.getNombre());
                System.out.println(director);
                System.out.println("\n");
            }
        }
        System.out.println("\n");

        System.out.println("f: ");
        {
            Actor[] actores8_10_15 = {actor8, actor10, actor15};
            for (Actor actor : actores8_10_15)
            {
                System.out.println("Actor: " + actor.getNombre());
                System.out.println(actor);
                System.out.println("\n");
            }
        }
        System.out.println("\n");

        System.out.println("g:");
        {
            Actor[] actores5_9 = {actor5, actor9};
            for (Actor actor : actores5_9)
            {
                System.out.println("Actor: " + actor.getNombre());
                System.out.println(actor.deseosNoCumplidos());
                System.out.println("\n");

            }
        }
        System.out.println("\n");

        System.out.println("h:");
        {
            Pelicula[] peliculas129_10 = {pelicula1, pelicula2, pelicula9, pelicula10};
            for (Pelicula pelicula : peliculas129_10)
            {
                System.out.println("Película: " + pelicula.getNombre());
                System.out.println(pelicula.getPresupuesto());
                System.out.println("\n");
            }
        }
        System.out.println("\n");

        System.out.println("i:");
        {
            Pelicula[] peliculas3456 = {pelicula3, pelicula4, pelicula5, pelicula6};
            for (Pelicula pelicula : peliculas3456)
            {
                System.out.println("Película: " + pelicula.getNombre());
                System.out.println(pelicula.recaudacionTotal());
                System.out.println("\n");
            }
        }
        System.out.println("\n");

        System.out.println("j:");
        {
            boolean todasExito = true;

            Pelicula[] todasLaspeliculas = {pelicula1, pelicula2, pelicula3, pelicula4, pelicula5, pelicula6, pelicula7, pelicula8, pelicula9, pelicula10};
            for (Pelicula pelicula : todasLaspeliculas)
            {
                System.out.print("Película: " + pelicula.getNombre());
                if (pelicula.exito())
                {
                    System.out.println(": Ha tenido éxito");
                } else
                {
                    System.out.println(": No ha tenido éxito");
                    todasExito = false;
                }
                System.out.println();

            }

            if (todasExito)
            {
                System.out.println("Todas las películas han tenido éxito");
            } else
            {
                System.out.println("Alguna(s) película(s) no ha(n) tenido éxito");

            }
        }
        System.out.println("\n");

        System.out.println("k:");
        System.out.println("Michael Kaine ha sido dirigido " + director2.dirigirActor(actor13.getNombre()) + " veces por Christopher Nolan");
        System.out.println("\n");

        System.out.println("l:");
        System.out.println("Leonardo DiCaprio ha sido dirigido " + director3.dirigirActor(actor5.getNombre()) + " veces por Martin Scorsese");
        System.out.println("\n");

        System.out.println("m:");
        {
            Director[] directores1457 = {director1, director4, director5, director7};
            for (Director director : directores1457)
            {
                System.out.print("El genero con mayor cache de: " + director.getNombre() + " es: ");
                for (String genero : director.generoMasCaro())
                {
                    System.out.println(genero);
                }
                System.out.println("\n");
            }
        }
        System.out.println("\n");

        System.out.println("n:");
        {
            Director[] directores236 = {director2, director3, director6};
            for (Director director : directores236)
            {
                System.out.println("Películas de " + director.getNombre() + "con recaudación superior a 80:");
                for (String nombrePelicula : director.peliculasMasBeneficio(80).keySet())
                {
                    System.out.println(nombrePelicula);
                }
                System.out.println("\n");
            }
        }
        System.out.println("\n");

    }

}