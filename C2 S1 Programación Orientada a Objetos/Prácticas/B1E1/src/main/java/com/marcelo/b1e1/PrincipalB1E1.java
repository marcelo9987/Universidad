
package com.marcelo.b1e1;


public class PrincipalB1E1
{

    public static void main(String[] args)
    {//throws Exception
        System.out.println("a:");
        Producto primerObjeto = new Producto("A0001B");

        System.out.println("b:");
        System.out.println(primerObjeto + "\n");

        System.out.println("c:");
        primerObjeto.setNombre("Echo Dot");
        primerObjeto.setDescripcion(
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
        primerObjeto.setPrecio((float) 33.99);


        primerObjeto.setPeso((float) 0.30);

        System.out.println("d:");
        System.out.println("Número de serie: " + primerObjeto.getNumSerie());
        System.out.println("Nombre: " + primerObjeto.getNombre());
        System.out.println("Descripción: "+primerObjeto.getDescripcion());
        System.out.println("Marca: "+primerObjeto.getMarca());
        System.out.println("Precio: "+ primerObjeto.getPrecio());
        System.out.println("Peso: "+ primerObjeto.getPeso());



        System.out.println("e:");
        System.out.println(primerObjeto + "\n");

        System.out.println("f:");
        Producto segundoObjeto = new Producto("C0003F");
        segundoObjeto.setNombre("Impresora LaserJetM110we");
        //segundoObjeto.setPrecio(null); //En la construcción del objeto se inicializa el precio a null, por lo que no hace falta hacer el set.
        segundoObjeto.setPeso(0f);


        System.out.println("g:");
        System.out.println("Número de serie: " + segundoObjeto.getNumSerie());
        System.out.println("Nombre: " + segundoObjeto.getNombre());
        System.out.println("Descripción: "+segundoObjeto.getDescripcion());
        System.out.println("Marca: "+segundoObjeto.getMarca());
        System.out.println("Precio: "+ segundoObjeto.getPrecio());
        System.out.println("Peso: "+ segundoObjeto.getPeso());


        System.out.println("h:");
        segundoObjeto.setDescripcion("Impresión a doble cara de forma automática, Wi-Fi de doble banda con " +
                "restablecimiento automático, Wi-Fi Direct, Fast Ethernet, HP Smart App, USB 2.0 de alta " +
                "velocidad, Apple AirPrint y Mopria.");
        segundoObjeto.setMarca("HP");


        System.out.println("i:");
        segundoObjeto.setPrecio(12f);

        System.out.println("j:");
        System.out.println("Descripción: "+segundoObjeto.getDescripcion());
        System.out.println("Marca: "+segundoObjeto.getMarca());
        System.out.println("Precio: "+ segundoObjeto.getPrecio());

        System.out.println("k:");
        System.out.println(segundoObjeto);
    }
}
