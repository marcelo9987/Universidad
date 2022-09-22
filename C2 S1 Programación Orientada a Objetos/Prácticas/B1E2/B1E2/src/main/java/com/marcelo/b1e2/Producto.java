/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.marcelo.b1e2;

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
                setNumSerie(numSerie);
            }

        public Producto(String numSerie, String nombre, Float peso, Float precio) //throws Exception //cambio de float a Float para admitir valores a null
        {
            this.setNumSerie(numSerie);
            this.setNombre(nombre);
            this.setPeso(peso);
            this.setPrecio(precio);
        }


        public String getNumSerie()
            {
                return numSerie;
            }

        public void setNumSerie(String numSerie)
            {
                /*
                if (numSerie == null)
                    {
                        return;
                    }
                 */
                this.numSerie = numSerie;       //todo: es aceptable que el numero de serie sea nulo?
            }

        public String getNombre()
            {
                return nombre;
            }

        public void setNombre(String nombre)
            {
                if (nombre == null || nombre.length() <= 30)
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
                if (descripcion == null || descripcion.length() <= 200)
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
                    System.err.println("La marca seleccionada no se encuentra entre las admitidas \n");
                    //throw new Exception("La marca seleccionada no se encuentra entre las admitidas");
                }
        }


        public Float getPeso()
            {
                return peso;
            }

        public void setPeso(Float peso) //throws Exception
        {
            if (peso != null && peso > 0)
                {
                    this.peso = peso;
                } else
                {
                    this.peso = null;
                    System.err.println("El peso ha de ser mayor a 0 y un valor válido");
                    //throw new Exception("El peso ha de ser mayor a 0 y un valor válido");
                }
        }

        public Float getPrecio()
            {
                return precio;
            }

        public void setPrecio(Float precio) //throws Exception
        {
            if (precio != null && precio > 0)
                {
                    this.precio = precio;
                } else
                {
                    this.precio=null;
                    System.out.println("El precio ha de ser mayor a 0 y un valor válido");
                    //throw new Exception("El precio ha de ser mayor a 0 y un valor válido");
                }
        }


        @Override
        public String toString()
            { //¿Que hago con las comas?
                String aux = "{\n";
                if (numSerie != null)
                    {
                        aux += "  \"numSerie\": \"" + numSerie + "\",\n";
                    }
                if (nombre != null)
                    {
                        aux += "  \"nombre\": \"" + nombre + "\",\n";
                    }
                if (descripcion != null)
                    {
                        aux += "  \"descripcion\": \"" + descripcion + "\",\n";
                    }
                if (marca != null)
                    {
                        aux += "  \"marca\": \"" + marca + "\",\n";
                    }
                if (peso != null)
                    {
                        aux += "  \"peso\": \"" + peso + "\",\n";
                    }
                if (precio != null)
                    {
                        aux += "  \"precio\": \"" + precio + "\"\n";
                    }
                aux += "}";

                return aux;
            }
    }
