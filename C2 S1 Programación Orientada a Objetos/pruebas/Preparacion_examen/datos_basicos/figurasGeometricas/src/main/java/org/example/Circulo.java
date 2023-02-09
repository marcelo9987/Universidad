package org.example;

public class Circulo extends FiguraGeometrica
{
    float radio;
    
    public static float radianes_en_un_circulo()
    {
        return 2 * (float) Math.PI;
    }
    
    Circulo(float radio)
    {
        this.radio = radio;
    }
    
    @Override
    public float area()
    {
        return (float) Math.PI * radio * radio;
    }
    
    public float diametro()
    {
        return 2 * radio;
    }
}
