package org.example;

import java.util.ArrayList;

public class Main
{
    public static void main(String[] args)
    {
        
//      main1();
        main2();
    }
    public static void main1()
    {
        Circulo circulo = new Circulo(2);
        Cuadrado cuadrado = new Cuadrado(3);
        Espiral espiral = new Espiral(5);
        
        //UPCAST
        FiguraGeometrica fg_circulo = circulo;
        FiguraGeometrica fg_cuadrado = cuadrado;
        
        //DOWNCAST
        Circulo dc_circulo = (Circulo) fg_circulo;
        Cuadrado dc_cuadrado = (Cuadrado) fg_cuadrado;
        Cuadrado dc_erroneo = (Cuadrado) fg_circulo;
    
        System.out.println("El area del circulo es: "  + circulo.area());
        System.out.println("El diametro del circulo es: " + circulo.diametro());
        System.out.println("El area del cuadrado es: " + cuadrado.area());
        System.out.println("El area de la espiral es: " + espiral.area());
        
        System.out.println("El area del fg_circulo es: "  + fg_circulo.area());
        System.out.println("El area del fg_circulo es: "  + fg_circulo.area());
        System.out.println("El diametro del fg_circulo es: " + ((Circulo)fg_circulo).diametro());
        System.out.println("El area del fg_cuadrado es: " + fg_cuadrado.area());
        
        System.out.println("El area del dc_circulo es: "  + dc_circulo.area());
        System.out.println("El diametro del dc_circulo es: " + dc_circulo.diametro());
        System.out.println("El area del dc_cuadrado es: " + dc_cuadrado.area());
    }
    
    public static void imprime_area(String descr,ObjetoPlano figura)
    {
        System.out.println("El area "+descr+" es: "  + figura.area());
        if(figura instanceof Circulo)
        {
            
            System.out.println("Diametro: "+((Circulo) figura).diametro());
        }
        ObjetoPlano.areaMinima();
    }
    
    public static void main2()
    {
        Circulo circulo = new Circulo(2);
        Circulo.radianes_en_un_circulo();
        ObjetoPlano.areaMinima();
        ObjetoPlano.presentarObjeto(circulo);
        
        Cuadrado cuadrado = new Cuadrado(3);
        ObjetoPlano.presentarObjeto(cuadrado);
    
        Espiral espiral = new Espiral(5);
    
        //UPCAST
        FiguraGeometrica fg_circulo = circulo;
        FiguraGeometrica fg_cuadrado = cuadrado;
    
        //DOWNCAST
        Circulo dc_circulo = (Circulo) fg_circulo;
        Cuadrado dc_cuadrado = (Cuadrado) fg_cuadrado;
//        Cuadrado dc_erroneo = (Cuadrado) fg_circulo;
//        Cuadrado dc_erroneo = (ArrayList) fg_circulo;
    
        imprime_area("del circulo",circulo);
        System.out.println("El diametro del circulo es: " + circulo.diametro());
        imprime_area("del cuadrado" ,cuadrado);
        imprime_area("de la espiral" , espiral);
    
        System.out.println("El area del fg_circulo es: "  + fg_circulo.area());
        System.out.println("El area del fg_circulo es: "  + fg_circulo.area());
        System.out.println("El diametro del fg_circulo es: " + ((Circulo)fg_circulo).diametro());
        System.out.println("El area del fg_cuadrado es: " + fg_cuadrado.area());
    
        System.out.println("El area del dc_circulo es: "  + dc_circulo.area());
        System.out.println("El diametro del dc_circulo es: " + dc_circulo.diametro());
        System.out.println("El area del dc_cuadrado es: " + dc_cuadrado.area());
    
    }
}