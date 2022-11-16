package org.example;

public class Main
{
    public static void main(String[] args)
    {
        try
        {
            System.out.println("voy a mandar un null:");
            generarError(null);
        } catch(Exception w)
        {
            System.out.println("he detectado algo: " + w);

        }





    }

    public static void generarError (Integer fallo)
    {
        fallo += (fallo + 8) * 6;
    }
}