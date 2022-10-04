
package com.marcelo.b1e3;


public class Mensajeria
{

    public final static String[] MARCAS = {"HP", "Amazon", "Microsoft", "iPhone", "Samsung", "Asus"};

    private String cif;
    private String nombre;
    private Paquete[] paquetes;
    private Float beneficio;

    //---- CONSTRUCTORES ----//

    /**
     * Constructor de mensajería(vacío)
     */
    Mensajeria()
    {

    }

    /**
     * Constructor 2 de mensajería
     * @param cif
     * @param nombre
     */
    Mensajeria(String cif, String nombre)
    {
        if (cif == null || nombre == null)
        {
            System.out.println("Argumento NULL. No se puede crear el objeto");
            return;
        }

        this.cif = cif;
        this.nombre = nombre;
    }

    //---- GETTERS & SETTERS ----//

    public String getCif()
    {
        return this.cif;
    }

    public void setCif(String cif)
    {
        if (cif == null)
        {
            System.out.println("ERROR: El cif no puede ser nulo");
            return;
        }

        this.cif = cif;
    }


    public String getNombre()
    {
        return this.nombre;
    }

    public void setNombre(String nombre)
    {
        if (nombre == null)
        {
            System.out.println("ERROR: El nombre no puede ser nulo.");
            return;
        }

        this.nombre = nombre;
    }

    public Paquete[] getPaquetes()
    {
        return this.paquetes;
    }

    public Float getBeneficio()
    {
        return this.beneficio;
    }


    //---- FUNCIONES ----//


    public void enviarPaquete(Paquete paquete)//añade un paquete a paquetes
    {
        int longitud;
        if (paquete == null)
        {
            System.out.println("ERROR: El paquete es nulo.");
            return;
        }

        if (this.paquetes != null)
        {
            longitud = this.paquetes.length;
        } else
        {
            longitud = 0;
        }

        Paquete[] paqueteArr = new Paquete[longitud + 1];
        for (int i = 0; i < longitud; i++)
        {
            if (paquete == this.paquetes[i])
            {
                System.out.println("ERROR: El paquete ya había sido incluido previamente.");
                return;
            }
            paqueteArr[i] = this.paquetes[i];
        }
        paqueteArr[longitud] = paquete;
        this.paquetes = paqueteArr;
        this.beneficio = this.calcularBeneficio();

    }


    public String[] marcasFrecuentes()
    {
        if (this.paquetes == null)
        {
            System.out.println("No existen paquetes");
            return new String[0];
        }

        int numeroMarcas = MARCAS.length;

        int[] marcasFrecuencia = new int[numeroMarcas];

        for (Paquete paquete : this.getPaquetes())
        {
            if (paquete == null)
            {
                System.out.println("ERROR: El paquete es nulo, no se tendrá en cuenta");
            } else if (paquete.getProductos() == null)
            {
                System.out.println("ERROR: los productos son nulos, no se tedrán en cuenta");
            } else
            {
                for (Producto prod : paquete.getProductos())
                {
                    if (prod == null)
                    {
                        System.out.println("ERROR: El producto es nulo, no se tendrá en cuenta");
                    } else
                    {
                        for (int i = 0; i < numeroMarcas; i++)
                        {
                            if (prod.getMarca() == null)
                            {
                                System.out.println("ERROR: La marca del producto es nula, no se puede incluir");
                                break;
                            } else if (prod.getMarca().equals(MARCAS[i]))
                            {
                                marcasFrecuencia[i]++;
                            }
                        }
                    }
                }
            }
        }

        int frecuenciaMaxima = 0;
        int numGanadoras = 0;

        for (int i = 0; i < numeroMarcas; i++)
        {
            if (frecuenciaMaxima < marcasFrecuencia[i])
            {
                frecuenciaMaxima = marcasFrecuencia[i];
            }
        }

        if (frecuenciaMaxima == 0)
        {
            return new String[0];
        }

        for (int i = 0; i < numeroMarcas; i++)
        {
            if (frecuenciaMaxima == marcasFrecuencia[i])
            {
                numGanadoras++;
            }
        }


        String[] marcasFrec = new String[numGanadoras];
        int entradaActual = 0;
        for (int i = 0; i < numeroMarcas; i++)
        {
            if (marcasFrecuencia[i] == frecuenciaMaxima)
            {
                marcasFrec[entradaActual] = MARCAS[i];
                entradaActual++;
            }
        }
        return marcasFrec;
    }

    public Producto[] productosCaros(float precioMin)
    {

        if (this.paquetes == null)
        {
            System.out.println("ERROR: No existen paquetes");
            return null;
        }

        Producto[] productosCaros;

        int conteoCaros = 0;

        for (Paquete paq : this.paquetes)
        {
            if (paq.getProductos() == null)
            {
                System.out.println("ERROR:  Los productos son nulos");
            } else
            {
                for (Producto prod : paq.getProductos())
                {
                    if (prod.getPrecio() == null)
                    {
                        System.out.println("ERROR: el precio es nulo");
                    } else if (prod.getPrecio() > precioMin)
                    {
                        conteoCaros++;
                    }
                }
            }
        }

        if (conteoCaros == 0)
        {
            return new Producto[0];
        }

        productosCaros = new Producto[conteoCaros];

        int i = 0;
        for (Paquete paq : this.paquetes)
        {
            if (paq.getProductos() == null)
            {
                System.out.println("ERROR:  Los productos son nulos");
            } else
            {
                for (Producto prod : paq.getProductos())
                {
                    if (prod.getPrecio() == null)
                    {
                        System.out.println("ERROR: el precio es nulo");
                    } else if (prod.getPrecio() > precioMin)
                    {
                        productosCaros[i] = prod;
                        i++;
                    }
                }
            }
        }
        return productosCaros;
    }

    /**
     * @return float beneficio. Suma de todos los precios
     */
    private float calcularBeneficio()
    {
        if (this.paquetes == null)
        {

            System.out.print("ERROR: Los paquetes no pueden ser nulos");
            return Paquete.PRECIO_NO_VALIDO;
        }

        float beneficioCalculado = 0;
        for (Paquete paquete : this.paquetes)
        {
            if (paquete == null)
            {
                System.out.println("ERROR: El paquete es nulo");
                return Paquete.PRECIO_NO_VALIDO;
            } else if (paquete.getPrecio() == null)
            {
                System.out.println("ERROR: El precio del paquete es nulo");
                return Paquete.PRECIO_NO_VALIDO;
            } else
            {
                beneficioCalculado += paquete.getPrecio();
            }
        }
        return beneficioCalculado;
    }


    @Override
    public String toString()
    {
        boolean yaSeHaImpresoAntes = false;
        String salida = "{\n";
        if (this.cif != null)
        {
            salida += "\"cif\": " + "\"" + this.getCif() + "\"";
            yaSeHaImpresoAntes = true;
        }
        if (this.nombre != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                salida += " ,\n";
            }
            salida += "\"nombre\": " + "\"" + this.getNombre() + "\"";
            yaSeHaImpresoAntes = true;
        }
        if (this.paquetes != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                salida += " ,\n";
            }
            salida += "\"paquetes\": [\n";
            for (int i = 0; i < this.paquetes.length; i++)
            {
                if (i > 0)
                {
                    salida += " ,\n";
                }
                salida += this.paquetes[i];
            }
            salida += "]";
            yaSeHaImpresoAntes = true;
        }
        if (this.beneficio != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                salida += " ,\n";
            }
            salida += "\"beneficio\": " + "\"" + this.getBeneficio() + "\"";
            yaSeHaImpresoAntes = true;
        }
        salida += "\n}";
        return salida;

    }
}



