
package com.marcelo.b1e2;


public class PrincipalB1E2
{

    public static void main(String[] args)
    {

        System.out.println("a:");
        Producto prod1 = new Producto("000A","Patatas",3f,3f);
        Producto prod2 = new Producto("001A","Lechugas",0.5f,1.88f);
        Producto prod3 = new Producto("002A","Cebollas",1f,3.0f);
        Producto[] arrProds = {prod1, prod2, prod3};


        System.out.println("b:");
        Paquete paq1 = new Paquete("20220915AA");


        System.out.println("c:");
        paq1.setDescripcion("El paquete tiene tres productos que hay que enviar conjuntamente para completar lo que es realmente un producto completo");
        paq1.setDestino("Noia");
        paq1.setProductos(arrProds);


        System.out.println("d:");
        for (Producto producto : arrProds)
        {
            producto.setPaquete(paq1);
        }


        System.out.println("e:");
        System.out.println("id: " + paq1.getId());
        System.out.println("Descripción: " + paq1.getDescripcion());
        System.out.println("Destino: " + paq1.getDestino());

        System.out.print("Trayecto actual: ");
        if (paq1.getTrayectoActual() != null)
        {
            for (String localizacion : paq1.getTrayectoActual())
            {
                System.out.println(localizacion);
            }
        } else
        {
            System.out.println("No existe trayecto.");
        }
        System.out.print("Productos:");
        if (paq1.getTrayectoActual() != null)
        {
            for (Producto producto : paq1.getProductos())
            {
                System.out.println(producto);
            }
        } else
        {
            System.out.println("No existen productos.");
        }
        System.out.println("Peso: " + paq1.getPeso());
        System.out.println("Precio: " + paq1.getPrecio());


        System.out.println("f:");
        System.out.println(paq1);


        System.out.println("g:");
        paq1.actualizarTrayectoria("Lugo");


        System.out.println("h:");
        paq1.actualizarTrayectoria("Santiago de Compostela");


        System.out.println("i:");
        paq1.actualizarTrayectoria("Lugo");

        System.out.println("j:");
        paq1.actualizarTrayectoria("Noia");


        System.out.println("k:");
        paq1.actualizarTrayectoria("Vigo");


        System.out.println("l:");
        System.out.println(paq1);


        System.out.println("m: ");
        Producto prod4 = new Producto("003A");
        prod4.setPrecio(49.99f);
        prod4.setPaquete(paq1);


        System.out.println("n: ");
        arrProds[1] = prod4;

        System.out.println("o: ");
        System.out.println(paq1);
        /*
        * Explicación:
        *   Al crear un array y asociarle objetos, este guarda en las posiciones de dichos objetos.
        *   Al modificar el puntero de la segunda posición, en vez de apuntar al objeto original apuntará a otro.
         */


        System.out.println("p: ");
        Producto prod5=new Producto("004A");
        Producto prod6=new Producto("005A");
        Producto prod7=new Producto("006A");
        Producto[] arrProds2={prod5,prod6,prod7};


        System.out.println("q:");
        Paquete paq2 = new Paquete("20220915AB","Vigo",arrProds2);


        System.out.println("r: ");
        System.out.println(paq2);


        System.out.println("s: ");
        paq2.actualizarTrayectoria("Vigo");


        System.out.println("t: ");
        System.out.print("Trayecto actual: ");
        if (paq2.getTrayectoActual() != null)
        {
            for (String localizacion : paq2.getTrayectoActual())
            {
                System.out.println(localizacion);
            }
        } else
        {
            System.out.println("No existe trayecto.");
        }
    }

}
