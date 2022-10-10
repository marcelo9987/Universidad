/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */

package com.marcelo.b1e3;

/**
 * @author Marcelo Fort Muñoz
 */
public class PrincipalB1E3
{

    public static void main(String[] args)
    {
        System.out.println("A: ");

        System.out.println("A.a:");
        Producto prod1 = new Producto("000A", "Patatas", 3f, 3f);//todo: ¿Pongo marcas?/.-
        Producto prod2 = new Producto("001A", "Lechugas", 0.5f, 1.88f);
        Producto prod3 = new Producto("002A", "Cebollas", 1f, 3.0f);
        Producto[] arrProds = {prod1, prod2, prod3};


        System.out.println("A.b:");
        Paquete paq1 = new Paquete("20220915AA");


        System.out.println("A.c:");
        paq1.setDescripcion("El paquete tiene tres productos que hay que enviar conjuntamente para completar lo que es realmente un producto completo");
        paq1.setDestino("Noia");
        paq1.setProductos(arrProds);

        paq1.setPrecio(12);//todo: ¿puedo asignar precio a paquetes no estando en el enunciado?/.-

        System.out.println("A.d:");
        for (Producto producto : arrProds)
        {
            producto.setPaquete(paq1);
        }


        System.out.println("A.e:");
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


        System.out.println("A.f:");
        System.out.println(paq1);


        System.out.println("A.g:");
        paq1.actualizarTrayectoria("Lugo");


        System.out.println("A.h:");
        paq1.actualizarTrayectoria("Santiago de Compostela");


        System.out.println("A.i:");
        paq1.actualizarTrayectoria("Lugo");

        System.out.println("A.j:");
        paq1.actualizarTrayectoria("Noia");


        System.out.println("A.k:");
        paq1.actualizarTrayectoria("Vigo");


        System.out.println("A.l:");
        System.out.println(paq1);


        System.out.println("A.m: ");
        Producto prod4 = new Producto("003A");
        prod4.setPrecio(49.99f);
        prod4.setPaquete(paq1);


        System.out.println("A.n: ");
        arrProds[1] = prod4;

        System.out.println("A.o: ");
        System.out.println(paq1);
        /*
         * Explicación:
         *   Al crear un array y asociarle objetos, este guarda en las posiciones de dichos objetos.
         *   Al modificar el puntero de la segunda posición, en vez de apuntar al objeto original apuntará a otro.
         */


        System.out.println("A.p: ");
        Producto prod5 = new Producto("004A","Saco de piedras",50,19.99f);
        prod5.setMarca("Asus");
        Producto prod6 = new Producto("005A","hormigón",40,30);
        prod6.setMarca("Microsoft");
        Producto prod7 = new Producto("006A","arcilla",0.5f,2);
        prod7.setMarca("HP");
        Producto[] arrProds2 = {prod5, prod6, prod7};


        System.out.println("A.q:");
        Paquete paq2 = new Paquete("20220915AB", "Vigo", arrProds2);

        paq2.setPrecio(96.36f);


        System.out.println("A.r: ");
        System.out.println(paq2);


         System.out.println("A.s: ");
        paq2.actualizarTrayectoria("Vigo");


         System.out.println("A.t: ");
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

        System.out.println("b: ");
        Mensajeria empresa1 = new Mensajeria("AA1234Z", "PRONTO&TARDE");


        System.out.println("c:");
        empresa1.enviarPaquete(paq1);
        empresa1.enviarPaquete(paq2);


        System.out.println("d:");
        System.out.println(empresa1);


        System.out.println("e:");
        paq1.setMensajeria(empresa1);
        paq2.setMensajeria(empresa1);


        System.out.println("f: ");
        Paquete paq3 = new Paquete("20220915AB");

        System.out.println("g: ");
        empresa1.enviarPaquete(paq3);

        System.out.println("h: ");
        System.out.println(empresa1);

        System.out.println("i: ");
        String[] marcasMasFrecuentes = empresa1.marcasFrecuentes();
        for (String marca : marcasMasFrecuentes)
        {
            System.out.println("marca: " + marca);
        }

        System.out.println("j: ");
        Producto[] productosPrecMay20 = empresa1.productosCaros(20);
        for (Producto producto : productosPrecMay20)
        {
            System.out.println("Producto: " + producto);
        }

        System.out.println("k: ");//todo: ¿Tengo que imprimir los valores de la empresa?/.-
        System.out.println("Cif: "+empresa1.getCif());
        System.out.println("Nombre: "+empresa1.getNombre());
        System.out.println("Paquetes: ");
        for (Paquete paquete: empresa1.getPaquetes())
        {
            System.out.println(paquete);
        }
        System.out.println("Beneficio: "+empresa1.getBeneficio());

    }
}
