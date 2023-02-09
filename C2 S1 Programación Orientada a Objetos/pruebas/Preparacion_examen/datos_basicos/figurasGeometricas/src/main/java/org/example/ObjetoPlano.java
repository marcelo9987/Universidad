package org.example;

public interface ObjetoPlano
{
    float area();
    
    static float areaMinima()
    {
        return 0;
    }
    
    
    default String mePresento()
    {
        return "Soy un Objeto Plano";
    }
    
    static void presentarObjeto(ObjetoPlano op)
    {
        System.out.println(op.mePresento());
        
    }
}
