/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */

package com.marcelo.b1e1;

/**
 *
 * @author imarc
 */
public class PrincipalB1E1 {

    public static void main(String[] args) //throws Exception
        {
        Producto primerObjeto = new Producto("A0001B");

        System.out.println(primerObjeto+"\n");

        primerObjeto.setNombre("Echo Dot");
        primerObjeto.setDescripcion
        (
            "Te presentamos el Echo Dot: nuestro altavoz inteligente más popular. Viene con " +
            "un diseño con acabado en tela que se ajusta perfectamente a cualquier espacio pequeño. " +
            "Controla la música con la voz: reproduce en streaming canciones en Amazon Music, Spotify, " +
            "TuneIn y otros servicios. Un sonido más intenso y de mayor calidad: vincula un segundo Echo " +
            "Dot (3.ª generación) para obtener un sonido estéreo más profundo. Si tienes dispositivos Echo " +
            "compatibles repartidos en varias habitaciones, podrás llenar de música toda tu casa. Lista para " +
            "ayudarte: pídele a Alexa que reproduzca música, responda a preguntas, narre las noticias, " +
            "consulte la previsión del tiempo, configure alarmas, controle dispositivos de Hogar digital " +
            "compatibles y mucho más."
        );
        primerObjeto.setMarca("Amazon");
        primerObjeto.setPrecio((float)33.99);

        
        primerObjeto.setPeso((float)0.30);

        System.out.println(primerObjeto+"\n");
        
        Producto segundoObjeto = new Producto("C0003F","Impresora LaserJetM110we",0f,null);

        System.out.println(segundoObjeto);

        segundoObjeto.setDescripcion("Impresión a doble cara de forma automática, Wi-Fi de doble banda con " +
                "restablecimiento automático, Wi-Fi Direct, Fast Ethernet, HP Smart App, USB 2.0 de alta " +
                "velocidad, Apple AirPrint y Mopria.");
        segundoObjeto.setMarca("HP");
        segundoObjeto.setPrecio(12f);

        System.out.println("\nDescripción: "+segundoObjeto.getDescripcion()+"\nMarca"+segundoObjeto.getMarca()+"\nPrecio: "+ segundoObjeto.getPrecio());

        System.out.println(segundoObjeto);
    }
}
/*todo:
    j. Mostrar por pantalla los valores de los atributos descripcion, marca y precio del producto creado en (f).
k. Mostrar por pantalla la representación en cadena de texto del producto creado en (f).
 //---i. Escribir un valor correcto para el atributo precio del producto creado en (f).---//
 */