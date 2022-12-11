package com.marcelo.b4e2;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Set;

public interface IAPelicula
{
    boolean darAlta(String rol, ArrayList<IActor> actores);
    HashMap<String, IActor> actoresDirigidos(String director);
    Set<IActor> actoresFracaso();
}
