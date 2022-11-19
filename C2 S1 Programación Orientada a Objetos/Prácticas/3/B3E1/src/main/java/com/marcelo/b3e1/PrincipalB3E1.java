package com.marcelo.b3e1;

import java.util.*;

public class PrincipalB3E1
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


        pelicula1 = new ComediaRomantica("Algo pasa con Mary", 1998, null, "Hermanos Farrelly", 90);

        pelicula2 = new Ficcion("Interstellar", 2014, 169, "Christopher Nolan", 100);

        pelicula3 = new Ficcion("Origen", 2010, 148, "Christopher Nolan", 300);

        pelicula4 = new Ficcion("El caballero Oscuro", 2008, 152, "Christopher Nolan", 500);

        pelicula5 = new Thriller("Infiltrados", 2006, 151, "Martin Scorsese", 80);

        pelicula6 = new Thriller("Gans of New York", 2002, 166, "Martin Scorsese", 70);

        pelicula7 = new ComediaNegra("Pulp Fiction", 1994, 153, "Quentin Tarantino", 50);

        pelicula8 = new Psicologico("El sexto Sentido", 1999, 107, "M. Night Shymalan", 90);

        pelicula9 = new ComediaRomantica("Noting Hill", 1999, 166, "Roger Mitchell", 124);

        pelicula10 = new Robos("Ocean 11", 2011, 117, "Steven Soderberg", 400);


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
