package org.example;

public class Rectangulo extends FiguraGeometrica
{
    float base, altura;
    
    public Rectangulo(float base, float altura) {
        this.base = base;
        this.altura = altura;
    }
    
    @Override
    public float area()
    {
        return base * altura;
    }

    @Override
    public String mePresento()
    {
        return "Soy un rectangulo de "+this.base+" * "+this.altura;
        
    }

}
