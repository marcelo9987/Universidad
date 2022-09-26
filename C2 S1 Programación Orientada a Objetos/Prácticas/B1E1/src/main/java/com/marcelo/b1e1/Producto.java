/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.marcelo.b1e1;

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

    public Producto(String numSerie)
    {
        if (numSerie == null)
        {
            System.out.println("ERROR: El número de serie no puede ser nulo");
        } else
        {
            this.numSerie = numSerie;
        }
    }

    public Producto(String numSerie, String nombre, float peso, float precio)
    {

        if (numSerie == null)
        {
            System.out.println("ERROR: El número de serie no puede ser nulo");
        } else
        {
            this.numSerie = numSerie;
        }
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
            this.marca = null;
            System.out.println("ERROR: La marca seleccionada no se encuentra entre las admitidas \n");
            //throw new Exception("La marca seleccionada no se encuentra entre las admitidas");
        }
    }


    public Float getPeso()
    {
        return peso;
    }

    public void setPeso(float peso) //throws Exception
    {
        if (peso > 0)
        {
            this.peso = peso;
        } else
        {
            this.peso = null;

            System.out.println("ERROR: El peso ha de ser mayor a 0 y un valor válido");
            //throw new Exception("El peso ha de ser mayor a 0 y un valor válido");
        }
    }

    public Float getPrecio()
    {
        return precio;
    }

    public void setPrecio(float precio) //throws Exception
    {
        if (precio > 0)
        {
            this.precio = precio;
        } else
        {
            this.precio = null;
            System.out.println("ERROR: El precio ha de ser mayor a 0 y un valor válido");
            //throw new Exception("El precio ha de ser mayor a 0 y un valor válido");
        }
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
                aux += "\",\n";
            }
            aux += "  \"nombre\": \"" + nombre;
            yaSeHaImpresoAntes = true;
        }
        if (descripcion != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                aux += "\",\n";
            }
            aux += "  \"descripcion\": \"" + descripcion;
            yaSeHaImpresoAntes = true;
        }
        if (marca != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                aux += "\",\n";
            }
            aux += "  \"marca\": \"" + marca;
            yaSeHaImpresoAntes = true;
        }
        if (peso != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                aux += "\",\n";
            }
            aux += "  \"peso\": \"" + peso;
            yaSeHaImpresoAntes = true;
        }
        if (precio != null)
        {
            if (yaSeHaImpresoAntes == true)
            {
                aux += "\",\n";
            }
            aux += "  \"precio\": \"" + precio + "\"";
            yaSeHaImpresoAntes = true;

        }
        aux += "\n}";

        return aux;
    }
}
