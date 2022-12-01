package com.marcelo.b4e1;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Set;

public interface IAPelicula
{
    boolean darAlta(String rol, ArrayList<Actor> actores);
    HashMap<String, Actor> actoresDirigidos(String director);
    Set<Actor> actoresFracaso();
}
