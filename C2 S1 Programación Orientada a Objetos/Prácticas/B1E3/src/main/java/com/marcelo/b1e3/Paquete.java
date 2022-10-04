package com.marcelo.b1e3;

import java.util.Objects;

public class Paquete
{
    public static final float PESO_NO_VALIDO = -1.0f;
    public static final float FACTOR_AUMENTO_PESO = 1.1f;
    public static final float PRECIO_NO_VALIDO = -1.0f;
    private String id;
    private String descripcion;
    private String destino;
    private String[] trayectoActual;
    private Producto[] productos;
    private Float peso;
    private Float precio;
    private Mensajeria mensajeria;

    Paquete(String id)
    {
        if (id == null)
        {
            System.out.println("Argumento NULL. No se puede crear el objeto");
            return;
        }

        this.id = id;
        this.peso = 0f;
    }


    Paquete(String id, String destino, Producto[] productos)
    {
        if (id == null || destino == null || productos == null)
        {
            System.out.println("Argumento NULL. No se puede crear el objeto");
            return;
        }

        this.id = id;
        this.peso = 0f;
        this.setDestino(destino);
        this.setProductos(productos);
    }


    public String getId()
    {
        return this.id;
    }


    public void setDescripcion(String descripcion)
    {
        if (descripcion == null)
        {
            System.out.println("ERROR: Descripción no puede ser nulo");
            return;
        }

        if (descripcion.length() > 200)
        {
            this.descripcion = descripcion.substring(0, 200);
        } else
        {
            this.descripcion = descripcion;
        }
    }


    public String getDescripcion()
    {
        return this.descripcion;
    }


    public void setDestino(String destino)
    {
        if (destino == null)
        {
            System.out.println("El destino no puede ser nulo");
            return;
        }

        String[] destinosAceptables = {"A Coruña", "Santiago de Compostela", "Lugo", "Vigo", "Pontevedra", "Ourense", "Lalín", "Verín", "Muros", "Noia", "Ferrol"};

        for (String destinoAceptable : destinosAceptables)
        {
            if (destino.equals(destinoAceptable))
            {
                this.destino = destino;
                return;
            }
        }

        System.out.println("ERROR: No se reconoce el destino seleccionado");

    }


    public String getDestino()
    {
        return this.destino;
    }


    public String[] getTrayectoActual()
    {
        return this.trayectoActual;
    }


    public void setProductos(Producto[] productos)
    {
        if (productos == null)
        {
            System.out.println("Error: El array de productos no puede apuntar a NULL.");//todo: ¿Puede ser productos un array con 0 elementos dentro?
            return;
        }
        for (Producto producto : productos)
        {
            if (producto == null)
            {
                System.out.println("ERROR: existe un elemento nulo en el array de productos.");
                return;
            }
        }

        this.productos = productos;
        this.peso = this.calcularPeso();
    }

    private float calcularPeso()
    {
        float pesosSumados = this.sumarPesos();

        float pesoAumentado = pesosSumados;
        if (pesosSumados > 0)
        {
            pesoAumentado *= Paquete.FACTOR_AUMENTO_PESO;
        }

        return pesoAumentado;
    }


    public Producto[] getProductos()
    {
        return this.productos;
    }


    public void setPrecio(float precio)
    {

        if (this.productos == null)
        {
            System.out.println("ERROR: No se puede calcular el precio hasta que se introduzcan los productos.");
        }

        float precioMin = this.calcularPrecioMinimo();

        if (precioMin == Paquete.PRECIO_NO_VALIDO)
        {
            System.out.println("ERROR: No se ha podido calcular el precio mínimo.");
            return;
        }

        if (precio <= precioMin)
        {
            System.out.println("ERROR: El precio introducido debe ser mayor a: " + precioMin);
            return;
        }

        this.precio = precio;
    }

    public Float getPrecio()
    {
        return this.precio;
    }

    public Float getPeso()
    {
        return this.peso;
    }

    public Mensajeria getMensajeria()
    {
        return mensajeria;
    }

    public void setMensajeria(Mensajeria mensajeria)
    {
        if (mensajeria == null)
        {
            System.out.println("Mensajeria no puede ser nula");
            return;
        }
        this.mensajeria = mensajeria;
    }

    public boolean actualizarTrayectoria(String poblacion)
    {
        //
        if (poblacion == null)
        {
            System.out.println("ERROR: No se ha recibido una población válida.");
            return false;
        }
        if (this.destino == null)
        {
            System.out.println("ERROR: No se ha podido establecer el destino. ¿Se ha realizado correctamente un setDestino()?");
            return false;
        }

        int longitud;

        if (this.trayectoActual == null || this.trayectoActual.length == 0)
        {

            longitud = 0;

        } else
        {

            longitud = this.trayectoActual.length;

            if (Objects.equals(this.trayectoActual[longitud - 1], this.destino))
            {
                System.out.println("ERROR: Como ha sido introducida la población la cual es destino del paquete, no se pueden volver a introducir nuevos valores en el atributo");
                return false;
            }

        }

        String[] arrayNuevo = new String[longitud + 1];

        for (int i = 0; i < longitud; i++)
        {
            arrayNuevo[i] = this.trayectoActual[i];
        }

        arrayNuevo[longitud] = poblacion;

        this.trayectoActual = arrayNuevo;
        return true;
    }

    private float sumarPesos()
    {

        if (this.productos == null)//todo: ¿si productos es null devuelvo peso 0 en sumaPesos()?
        {
            System.out.println("ERROR: Los productos no pueden ser nulos.");
            return Paquete.PESO_NO_VALIDO;//Error crítico de la funcion, devuelvo valor -1 para denotar el fallo
        }

        float pesoSumado = 0;
        for (Producto producto : this.productos)
        {
            if (producto.getPeso() == null)//todo:¿Que pasa en la función sumaPesos cuando uno de los pesos es nulo?, ¿sale error o suma 0?
            {
                System.out.println("ERROR: El peso del producto del paquete: " + this.getId() + " Numero Serie: " + producto.getNumSerie() + " es nulo");
                return Paquete.PESO_NO_VALIDO;//Error crítico de la funcion, devuelvo valor -1 para denotar el fallo
            } else
            {
                pesoSumado += producto.getPeso();
            }
        }
        return pesoSumado;

    }


    private float calcularPrecioMinimo()
    {
        float precio_minimo = 0;
        float peso = this.sumarPesos();


        if (peso == Paquete.PESO_NO_VALIDO)
        {
            System.out.println("ERROR: No se ha podido calcular el precio mínimo");
            return Paquete.PRECIO_NO_VALIDO;
        }

        if (peso < 1.0f)
        {
            precio_minimo = 2.5f;
        } else if (peso < 3.0f)
        {
            precio_minimo = 4.0f;
        } else
        {
            precio_minimo = peso * 1.05f;
        }
        return precio_minimo;
    }

    @Override
    public boolean equals(Object obj)
    {
        if (this == obj)
        {
            return true;
        }
        if (obj == null)
        {
            return false;
        }
        if (getClass() != obj.getClass())
        {
            return false;
        }

        final Paquete other = (Paquete) obj;
        if(this.id ==null)
        {
            if(other.id==null)
            {
                return true;
            }
            return false;
        }
        if (!this.id.equals(other.id))
        {
            return false;
        }
        return true;
    }

    @Override
    public String toString()
    {
        boolean yaSeHaImpresoAntes = false;
        String salida = "{\n";
        if (this.id != null)
        {
            salida += "  \"id\": " + "\"" + this.getId() + "\"";
            yaSeHaImpresoAntes = true;
        }
        if (this.descripcion != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                salida += ",\n";
            }
            salida += "  \"descripcion\": " + "\"" + this.getDescripcion() + "\"";
            yaSeHaImpresoAntes = true;
        }
        if (this.destino != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                salida += "\n";
            }
            salida += "  \"destino\": " + "\"" + this.getDestino() + "\"";
            yaSeHaImpresoAntes = true;
        }
        if (this.trayectoActual != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                salida += ",\n";
            }
            salida += "  \"trayectoriaActual\": [";
            for (int i = 0; i < this.trayectoActual.length; i++)
            {
                if (i > 0)
                {
                    salida += ", ";
                }
                salida += "\"" + this.trayectoActual[i] + "\"";
            }
            salida += "]";
            yaSeHaImpresoAntes = true;
        }
        if (this.productos != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                salida += ",\n";
            }
            salida += "  \"productos\": [\n";
            for (int i = 0; i < this.productos.length; i++)
            {
                if (i > 0)
                {
                    salida += ",\n";
                }
                salida += this.productos[i];
            }
            salida += "]";
            yaSeHaImpresoAntes = true;
        }
        if (this.peso != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                salida += ",\n";
            }
            salida += "  \"peso\": " + "\"" + this.getPeso() + "\"";
            yaSeHaImpresoAntes = true;
        }
        if (this.precio != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                salida += ",\n";
            }
            salida += "  \"precio\": " + "\"" + this.getPrecio() + "\"";
            yaSeHaImpresoAntes = true;
        }
        salida += "\n}";
        return salida;
    }
}
