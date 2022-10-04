
package com.marcelo.b1e3;

/**
 * @author Marcelo Fort Muñoz
 */
public class Producto
{
    private String numSerie;
    private String nombre;
    private String descripcion;
    private String marca;
    private Float peso;
    private Float precio;

    private Paquete paquete;

    public Producto(String numSerie)
    {

        if (numSerie == null)
        {
            System.out.println("Argumento NULL. No se ha podido crear el objeto");
            return;
        }

        this.numSerie = numSerie;
    }

    public Producto(String numSerie, String nombre, float peso, float precio)
    {
        if (numSerie == null || nombre == null)
        {
            System.out.println("Argumento NULL. No se ha podido crear el objeto");
            return;
        }

        this.numSerie = numSerie;
        this.setNombre(nombre);
        this.setPeso(peso);
        this.setPrecio(precio);
    }


    public String getNumSerie()
    {
        return numSerie;
    }


    public String getNombre()
    {
        return nombre;
    }


    public void setNombre(String nombre)
    {
        if (nombre == null)
        {
            System.out.println("ERROR: Nombre no puede ser nulo");
            return;
        }

        if (nombre.length() <= 30)
        {
            this.nombre = nombre;
        } else
        {
            this.nombre = nombre.substring(0, 30);
        }
    }


    public String getDescripcion()
    {
        return descripcion;
    }


    public void setDescripcion(String descripcion)
    {
        if (descripcion == null)
        {
            System.out.println("ERROR: Descripción no puede ser nulo");
            return;
        }

        if (descripcion.length() <= 200)
        {
            this.descripcion = descripcion;
        } else
        {
            this.descripcion = descripcion.substring(0, 200);

        }
    }


    public String getMarca()
    {
        return marca;
    }


    public void setMarca(String marca) //throws Exception
    {
        if (
                marca != null && (
                        marca.equals("HP") ||
                                marca.equals("Amazon") ||
                                marca.equals("Microsoft") ||
                                marca.equals("iPhone") ||
                                marca.equals("Samsung") ||
                                marca.equals("Asus")
                )

        )
        {
            this.marca = marca;
        } else
        {
            System.out.println("ERROR: La marca seleccionada no se encuentra entre las admitidas \n");
        }
    }


    public Float getPeso()
    {
        return peso;
    }

    public void setPeso(float peso)
    {
        if (peso > 0)
        {
            this.peso = peso;
        } else
        {
            System.out.println("ERROR: El peso ha de ser mayor a 0");
        }
    }

    public Float getPrecio()
    {
        return precio;
    }

    public void setPrecio(float precio)
    {
        if (precio > 0)
        {
            this.precio = precio;
        } else
        {
            System.out.println("ERROR: El precio ha de ser mayor a 0");
        }
    }

    public Paquete getPaquete()
    {
        return this.paquete;
    }

    public void setPaquete(Paquete paquete)
    {
        if (paquete == null)
        {
            System.out.println("ERROR: El paquete no puede ser nulo");
            return;
        }
        this.paquete = paquete;
    }

    @Override
    public String toString()
    {
        boolean yaSeHaImpresoAntes = false;
        String aux = "{\n";
        if (numSerie != null)
        {
            aux += "  \"numSerie\": \"" + numSerie + "\"";
            yaSeHaImpresoAntes = true;
        }

        if (nombre != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                aux += ",\n";
            }
            aux += "  \"nombre\": \"" + nombre + "\"";
            yaSeHaImpresoAntes = true;
        }
        if (descripcion != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                aux += ",\n";
            }
            aux += "  \"descripcion\": \"" + descripcion + "\"";
            yaSeHaImpresoAntes = true;
        }
        if (marca != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                aux += ",\n";
            }
            aux += "  \"marca\": \"" + marca + "\"";
            yaSeHaImpresoAntes = true;
        }
        if (peso != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                aux += ",\n";
            }
            aux += "  \"peso\": \"" + peso + "\"";
            yaSeHaImpresoAntes = true;
        }
        if (precio != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                aux += ",\n";
            }
            aux += "  \"precio\": \"" + precio + "\"";
            yaSeHaImpresoAntes = true;

        }
        aux += "\n}";

        return aux;
    }
}
