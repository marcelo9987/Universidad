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

        {
            Actor[] actores1_6 = {actor1, actor2, actor3, actor4, actor5, actor6};
            for (Actor actor : actores1_6)
            {
                System.out.println(actor);
            }
        }

        System.out.println("\n");


        System.out.println("c: ");

        Pelicula pelicula1, pelicula2, pelicula3, pelicula4, pelicula5, pelicula6, pelicula7, pelicula8, pelicula9, pelicula10;


        Director director1;

        Director director2, director3, director4, director5, director6, director7;

        HashSet<String> especialista1 = new HashSet<>(Arrays.asList("ComediaRomantica", "ComediaNegra"));
        HashMap<String, Float> cache1 = new HashMap<String, Float>();

        cache1.put("ComediaRomantica", 2.00f);
        cache1.put("ComediaNegra", 1.5f);


        director1 = new Director("Hermanos Farrelly", especialista1, cache1);

        HashMap<String,Float> recaudacionPelicula1 = new HashMap<>();
        recaudacionPelicula1.put("EE.UU",40f);
        recaudacionPelicula1.put("España",8f);
        recaudacionPelicula1.put("Italia",9f);
        recaudacionPelicula1.put("Alemania",10f);
        recaudacionPelicula1.put("Francia",8f);
        recaudacionPelicula1.put("Reino Unido",8f);
        recaudacionPelicula1.put("Polonia",5f);


        pelicula1 = new ComediaRomantica("Algo pasa con Mary", 1998, null, director1, recaudacionPelicula1);


        HashSet<String> especialista2 = new HashSet<>(Arrays.asList("Ficcion", "Guerra", "Thriller"));

        HashMap<String, Float> cache2 = new HashMap<String, Float>();
        cache2.put("Ficcion", 4.00f);
        cache2.put("Guerra", 8f);
        cache2.put("Thriller", 5f);



        director2 = new Director("Cristopher Nolan", especialista2, cache2);

        HashMap<String,Float> recaudacionPelicula2 = new HashMap<>();

        recaudacionPelicula2.put("EE.UU",50f);
        recaudacionPelicula2.put("España",8f);
        recaudacionPelicula2.put("Italia",8f);
        recaudacionPelicula2.put("Alemania",10f);
        recaudacionPelicula2.put("Francia",5f);
        recaudacionPelicula2.put("Reino Unido",15f);
        recaudacionPelicula2.put("Polonia",4f);


        pelicula2 = new Ficcion("Interstellar", 2014, 169, director2, recaudacionPelicula2);

        Set<String> especialista3 = new HashSet<>();
        especialista3.add("Thriller");
        especialista3.add("Psicologico");

        HashMap<String,Float> cache3 = new HashMap<>();
        cache3.put("Thriller",4.0f);
        cache3.put("Psicologico",6.00f);

        director3 = new Director("Martin Scorsese",especialista3,cache3);

        HashMap<String,Float> recaudacionPelicula3= new HashMap<>();
        recaudacionPelicula3.put("EE.UU",120f);
        recaudacionPelicula3.put("España",30f);
        recaudacionPelicula3.put("Italia",30f);
        recaudacionPelicula3.put("Alemania",50f);
        recaudacionPelicula3.put("Francia",25f);
        recaudacionPelicula3.put("Reino Unido",24f);
        recaudacionPelicula3.put("Polonia",21f);


        pelicula3 = new Ficcion("Origen", 2010, 148, director2, recaudacionPelicula3);


        HashMap<String,Float> recaudacionPelicula4= new HashMap<>();
        recaudacionPelicula4.put("EE.UU",180f);
        recaudacionPelicula4.put("España",80f);
        recaudacionPelicula4.put("Italia",50f);
        recaudacionPelicula4.put("Alemania",40f);
        recaudacionPelicula4.put("Francia",40f);
        recaudacionPelicula4.put("Reino Unido",80f);
        recaudacionPelicula4.put("Polonia",30f);

        pelicula4 = new Ficcion("El caballero Oscuro", 2008, 152, director2, recaudacionPelicula4);

        HashMap<String,Float> recaudacionPelicula5= new HashMap<>();
        recaudacionPelicula5.put("EE.UU",30f);
        recaudacionPelicula5.put("España",5f);
        recaudacionPelicula5.put("Italia",10f);
        recaudacionPelicula5.put("Alemania",10f);
        recaudacionPelicula5.put("Francia",8f);
        recaudacionPelicula5.put("Reino Unido",15f);
        recaudacionPelicula5.put("Polonia",2f);

        pelicula5 = new Thriller("Infiltrados", 2006, 151, director3, recaudacionPelicula5);

        HashMap<String,Float> recaudacionPelicula6 = new HashMap<>();
        recaudacionPelicula6.put("EE.UU",20f);
        recaudacionPelicula6.put("España",5f);
        recaudacionPelicula6.put("Italia",5f);
        recaudacionPelicula6.put("Alemania",10f);
        recaudacionPelicula6.put("Francia",12f);
        recaudacionPelicula6.put("Reino Unido",13f);
        recaudacionPelicula6.put("Polonia",5f);

        pelicula6 = new Thriller("Gans of New York", 2002, 166, director3, recaudacionPelicula6);

        Set<String> especialista4 = new HashSet<>();
        especialista4.add("ComediaNegra");
        especialista4.add("Ficcion");
        especialista4.add("Guerra");

        HashMap<String,Float> cache4 = new HashMap<>();
        cache4.put("ComediaNegra",5.0f);
        cache4.put("Ficcion",4.50f);
        cache4.put("Guerra",4.00f);

        director4 = new Director("Quentin Tarantino",especialista4,cache4);

        HashMap<String,Float> recaudacionPelicula7 = new HashMap<>();
        recaudacionPelicula7.put("EE.UU",15f);
        recaudacionPelicula7.put("España",3f);
        recaudacionPelicula7.put("Italia",4f);
        recaudacionPelicula7.put("Alemania",8f);
        recaudacionPelicula7.put("Francia",7f);
        recaudacionPelicula7.put("Reino Unido",10f);
        recaudacionPelicula7.put("Polonia",3f);

        pelicula7 = new ComediaNegra("Pulp Fiction", 1994, 153, director4, recaudacionPelicula7);

        Set<String> especialista5 = new HashSet<>();
        especialista5.add("Psicologico");
        especialista5.add("Ficcion");
        especialista5.add("TerrorGotico");

        HashMap<String,Float> cache5 = new HashMap<>();
        cache5.put("Psicologico",5.0f);
        cache5.put("Ficcion",1.50f);
        cache5.put("TerrorGotico",2.00f);

        director5 = new Director("M. Night Shymalan",especialista5,cache5);

        HashMap<String,Float> recaudacionPelicula8 = new HashMap<>();

        recaudacionPelicula8.put("EE.UU",35f);
        recaudacionPelicula8.put("España",5f);
        recaudacionPelicula8.put("Italia",5f);
        recaudacionPelicula8.put("Alemania",10f);
        recaudacionPelicula8.put("Francia",15f);
        recaudacionPelicula8.put("Reino Unido",11f);
        recaudacionPelicula8.put("Polonia",9f);

        pelicula8 = new Psicologico("El sexto Sentido", 1999, 107, director5, recaudacionPelicula8);

        Set<String> especialista6 = new HashSet<>();
        especialista6.add("ComediaRomantica");
        especialista6.add("Parodia");

        HashMap<String,Float> cache6 = new HashMap<>();
        cache6.put("ComediaRomantica",3.0f);
        cache6.put("Parodia",2.50f);

        director6 = new Director("M. Night Shymalan",especialista6,cache6);

        HashMap<String,Float> recaudacionPelicula9 = new HashMap<>();

        recaudacionPelicula9.put("EE.UU",40f);
        recaudacionPelicula9.put("España",10f);
        recaudacionPelicula9.put("Italia",10f);
        recaudacionPelicula9.put("Alemania",15f);
        recaudacionPelicula9.put("Francia",14f);
        recaudacionPelicula9.put("Reino Unido",24f);
        recaudacionPelicula9.put("Polonia",11f);

        pelicula9 = new ComediaRomantica("Noting Hill", 1999, 166, director6, recaudacionPelicula9);


        Set<String> especialista7 = new HashSet<>();
        especialista7.add("DeRobos");
        especialista7.add("Thriller");
        especialista7.add("Ficcion");

        HashMap<String,Float> cache7 = new HashMap<>();
        cache7.put("DeRobos",4f);
        cache7.put("Thriller",5f);
        cache7.put("Ficcion",6f);

        director7 = new Director("M. Night Shymalan",especialista7,cache7);

        HashMap<String,Float> recaudacionPelicula10 = new HashMap<>();

        recaudacionPelicula10.put("EE.UU",120f);
        recaudacionPelicula10.put("España",24f);
        recaudacionPelicula10.put("Italia",35f);
        recaudacionPelicula10.put("Alemania",35f);
        recaudacionPelicula10.put("Francia",60f);
        recaudacionPelicula10.put("Reino Unido",80f);
        recaudacionPelicula10.put("Polonia",44f);

        pelicula10 = new Robos("Ocean 11", 2011, 117, director7, recaudacionPelicula10);


        System.out.println("\n");

        System.out.println("d: ");
        {
            Pelicula[] pelis1_4 = {pelicula1, pelicula2, pelicula3, pelicula4};
            for (Pelicula pelicula : pelis1_4)
            {
                System.out.println(pelicula);
            }
        }
        System.out.println("\n");

        System.out.println("e: ");
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

        //todo: No puedo insertar a Haley Joel Osment porque no existe su variable
        if (!pelicula8.darAlta("principal", new ArrayList<>(Arrays.asList(actor12 /*, algo*/))))
        {
            System.out.println("Los actores principales de la película 7 no han sido dados de alta correctamente.");
        }
        if (!pelicula8.darAlta("secundario", new ArrayList<>(Arrays.asList(actor12))))
        {
            System.out.println("Los actores secundarios de la película 7 no han sido dados de alta correctamente.");
        }

        if (!pelicula9.darAlta("principal", new ArrayList<>(Arrays.asList(actor18, actor19))))
        {
            System.out.println("Los actores principales de la película 7 no han sido dados de alta correctamente.");
        }

        if (!pelicula10.darAlta("principal", new ArrayList<>(Arrays.asList(actor18, actor9, actor20))))
        {

            System.out.println("Los actores principales de la película 7 no han sido dados de alta correctamente.");
        }

        System.out.println("\n");


        System.out.println("f: ");
        {
            Pelicula[] pelis1_45678 = {pelicula1, pelicula4, pelicula5, pelicula6, pelicula7, pelicula8};
            for (Pelicula pelicula : pelis1_45678)
            {
                System.out.println(pelicula);
                System.out.println();
            }
        }
        System.out.println("\n");


        System.out.println("g: ");
        {
            Actor[] actores15789_10 = {actor1, actor5, actor7, actor8, actor9, actor10};
            for (Actor actor : actores15789_10)
            {
                System.out.println(actor);
                System.out.println();
            }
        }
        System.out.println("\n");

        System.out.println("h: ");
        {
            for (Pelicula pelicula : actor5.getPeliculas().values())
            {
                System.out.println(pelicula);
                System.out.println();
            }
        }
        System.out.println("\n");

        System.out.println("i:");
        for (Actor actor : pelicula1.actoresDirigidos("Martin Scorsese").values())
        {
            System.out.println(actor);
            System.out.println();
        }
        System.out.println("\n");


        System.out.println("j:");
        System.out.println("Para Christofer Nolan(Mal escrito):");
        for (Actor actor : pelicula6.actoresDirigidos("Christofer Nolan").values())
        {
            System.out.println(actor);
        }
        System.out.println("\n");

        System.out.println("Para Christopher Nolan:");
        for (Actor actor : pelicula6.actoresDirigidos("Christopher Nolan").values())
        {
            System.out.println(actor);
        }
        System.out.println("\n");

        System.out.println("k:");
        {
            Pelicula[] pelis4_7 = {pelicula4, pelicula5, pelicula6, pelicula7};
            for (Pelicula pelicula : pelis4_7)
            {
                System.out.print("La película " + pelicula.getNombre());
                if (pelicula.exito())
                {
                    System.out.println(" ha tenido éxito.");
                } else
                {
                    System.out.println(" no ha tenido éxito.");
                }
            }
        }
        System.out.println("\n");

        System.out.println("l: ");
        //todo: confirmar si es con todas o una pelicula en especifico
        {
            System.out.println("Actores que han participado en películas que no han tenido éxito:");
            Set<Actor> actoresNoExito = new HashSet<>();
            Pelicula[] todasLasPeliculas = {pelicula1, pelicula2, pelicula3, pelicula4, pelicula5, pelicula6, pelicula7, pelicula8, pelicula9, pelicula10};
            for (Pelicula pelicula : todasLasPeliculas)
            {
                //if (pelicula != null )//&& pelicula.getActores() != null)
                //{
                actoresNoExito.addAll(pelicula.actoresFracaso());
                //}
            }

            for (Actor actor : actoresNoExito)
            {
                System.out.println(actor.getNombre());
            }
        }

        System.out.println("m: ");
        {
            Pelicula[] peliculas_1y2y9y10 = {pelicula1, pelicula2, pelicula9, pelicula10};
            for (Pelicula pelicula : peliculas_1y2y9y10)
            {
                System.out.println("La película " + pelicula.getNombre() + " tuvo un presupuesto de: " + pelicula.getPresupuesto());
            }
        }
        System.out.println("\n");

        System.out.println("n:");
        {
            Actor[] actores1a3 = {actor1, actor2, actor3};
            for (Actor actor : actores1a3)
            {
                System.out.println("El actor " + actor.getNombre() + " ha participado en las siguientes peliculas de ficción: ");
                Set<Pelicula> peliculasFiccionDelActor = actor.peliculasDeGenero("Ficcion");

                for (Pelicula pelicula : peliculasFiccionDelActor)
                {
                    System.out.println(pelicula.getNombre());
                }
            }
        }
        System.out.println("\n");

        System.out.println("o:");
        {
            Actor[] actores7a9 = {actor7, actor8, actor9};
            for (Actor actor : actores7a9)
            {
                System.out.println("El actor " + actor.getNombre() + " ha participado en las siguientes Comedias Románticas: ");
                Set<Pelicula> peliculasCR = actor.peliculasDeGenero("ComediaRomantica");

                for (Pelicula pelicula : peliculasCR)
                {
                    System.out.println(pelicula.getNombre());
                }
            }
        }
        System.out.println("\n");

        System.out.println("p:");
        {
            Actor[] actores10a12 = {actor10, actor11, actor12};
            for (Actor actor : actores10a12)
            {
                System.out.println("El actor " + actor.getNombre() + " ha participado en las siguientes películas de Terror Psicológico: ");
                Set<Pelicula> peliculasPsi = actor.peliculasDeGenero("Psicologico");

                for (Pelicula pelicula : peliculasPsi)
                {
                    System.out.println(pelicula.getNombre());
                }
            }
        }
        System.out.println("\n");

        System.out.println("q:");
        {
            Actor[] actores13a15 = {actor13, actor14, actor15};
            for (Actor actor : actores13a15)
            {
                System.out.println("El actor " + actor.getNombre() + " ha participado en los siguientes Thrillers: ");
                Set<Pelicula> peliculasThr = actor.peliculasDeGenero("Thriller");

                for (Pelicula pelicula : peliculasThr)
                {
                    System.out.println(pelicula.getNombre());
                }
            }
        }
        System.out.println("\n");

        System.out.println("r:");
        {
            Actor[] actores1a4 = {actor1, actor2, actor3, actor4};
            for (Actor actor : actores1a4)
            {
                System.out.println("El actor " + actor.getNombre() + " ha participado con el rol principal " + actor.importancia("principal") + " veces");
            }
        }
        System.out.println("\n");

        System.out.println("s:");
        {
            Actor[] actores5a8 = {actor5, actor6, actor7, actor8};
            for (Actor actor : actores5a8)
            {
                System.out.println("El actor " + actor.getNombre() + " ha participado con el rol secundario " + actor.importancia("secundario") + " veces");
            }
        }
        System.out.println("\n");

        System.out.println("t:");
        {
            Actor[] actores10a14 = {actor10, actor11, actor12, actor13, actor14};
            for (Actor actor : actores10a14)
            {
                System.out.println("El actor " + actor.getNombre() + " tiene unas ganacias de " + actor.totalGanancias());
            }
        }
        System.out.println("\n");

        System.out.println("u:");
        {
            Actor[] actores15a18 = {actor15, actor16, actor17, actor18};
            for (Actor actor : actores15a18)
            {
                System.out.println("El actor " + actor.getNombre() + " tiene los siguientes deseos no cumplidos: " + actor.deseosNoCumplidos());
            }
        }
        System.out.println("\n");

    }

}