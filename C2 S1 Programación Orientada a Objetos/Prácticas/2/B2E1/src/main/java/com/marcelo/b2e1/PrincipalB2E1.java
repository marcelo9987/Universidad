/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */

package com.marcelo.b2e1;

/**
 *
 * @author imarc
 */
public class PrincipalB2E1 {

    public static void main(String[] args)
    {
        Estancia miEstancia=new Estancia("'Ello",3);
        float[] a ={1,2};
        Sensor sensortest = new Sensor("000","sonido",a,55);
        sensortest.nuevoDato(1);
        Sensor sensortest1 = new Sensor("001","luz",a,55);
        Sensor sensortest2 = new Sensor("002","sonido",a,55);
        Sensor sensortest3 = new Sensor("003","humedad",a,55);


        //miEstancia.
        miEstancia.darAlta(sensortest);
        miEstancia.darAlta(sensortest1);
        miEstancia.darAlta(sensortest2);
        miEstancia.darAlta(sensortest3);

        miEstancia.sensoresTipo("sonido");
        System.out.println(miEstancia.getSensores());
    }
}
