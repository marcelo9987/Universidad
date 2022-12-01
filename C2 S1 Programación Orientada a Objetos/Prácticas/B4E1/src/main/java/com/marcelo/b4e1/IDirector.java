package com.marcelo.b4e1;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Set;

public interface IDirector extends IParticipante
{
    String getNombre();
    
    void setNombre(String nombre);
    
    HashMap<String, Float> getCache();
    
    void setCache(HashMap<String, Float> cache);
    
    ArrayList<IPelicula> getPeliculas();
    
    Set<String> getEspecialista();
    
    void setEspecialista(Set<String> especialista);
    
    int dirigirActor(String actor);
    
    Set<String> generoMasCaro();
    
    HashMap<String, IPelicula> peliculasMasBeneficio(float minimo);
}
