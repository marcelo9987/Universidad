package org.example;

public class Espiral implements ObjetoPlano
{
    float radio;
    
    Espiral(float radio)
    {
        this.radio = radio;
    }
    
    
    @Override
    public float area() {
        return Float.NaN;
    }
}
