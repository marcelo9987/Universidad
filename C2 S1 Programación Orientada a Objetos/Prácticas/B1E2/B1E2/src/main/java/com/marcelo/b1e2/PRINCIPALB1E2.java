/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */

package com.marcelo.b1e2;

/**
 *
 * @author imarc
 */
public class PRINCIPALB1E2 {

    public static void main(String[] args)
    {
        Producto[] uvedoble=new Producto[2];
        uvedoble[0]=new Producto("1425E");

        uvedoble[1]=new Producto("5268E");
        Paquete r = new Paquete("5658","ES",uvedoble);
    }
}
