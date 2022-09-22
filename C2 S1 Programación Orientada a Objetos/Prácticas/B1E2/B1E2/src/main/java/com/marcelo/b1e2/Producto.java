/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.marcelo.b1e2;
//TODO: cambiar los requerimientos segun las buenas prácticas(comprocar nulls)

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

        public Producto(String _numSerie)
            {
                numSerie = _numSerie;
            }

        public Producto(String _numSerie, String _nombre, Float _peso, Float _precio)
            {
                numSerie = _numSerie;
                nombre = _nombre;
                peso = _peso;
                precio = _precio;
            }

        public void setNumSerie(String _numSerie)
            {
                if(_numSerie == null)return;
                this.numSerie = _numSerie;
            }

        public void setNombre(String _nombre)
            {
                if (_nombre != null && _nombre.length() <= 30)
                    {
                        this.nombre = _nombre;
                    } else
                    {
                        System.out.println("El nombre no puede exceder los 30 caracteres. y ha de ser válido \n");
                    }
            }

        public void setDescripcion(String _descr)
            {
                if (_descr != null && _descr.length() <= 200)
                    {
                        this.descripcion = _descr;
                    } else
                    {
                        System.out.println("La descripción no ha de superar los 200 caracteres en extensión y no nula. \n");
                    }
            }

        public void setMarca(String _marca)
            {
                if (
                        _marca != null &&
                                (
                                        _marca.contentEquals("HP") ||
                                                _marca.contentEquals("Amazon") ||
                                                _marca.contentEquals("Microsoft") ||
                                                _marca.contentEquals("iPhone") ||
                                                _marca.contentEquals("Samsung") ||
                                                _marca.contentEquals("Asus")
                                )

                )
                    {
                        this.marca = _marca;
                    } else
                    {
                        System.err.println("La marca seleccionada no se encuentra entre las admitidas \n");
                    }
            }

        public void setPeso(Float _peso)
            {
                if (_peso != null && _peso > 0)
                    {
                        this.peso = _peso;
                    } else
                    {
                        System.out.println("El peso ha de ser mayor a 0 y un valor válido");
                    }
            }

        public void setPrecio(Float _precio)
            {
                if (_precio != null && _precio > 0)
                    {
                        this.precio = _precio;
                    } else
                    {
                        System.out.println("El precio ha de ser mayor a 0 y un valor válido");
                    }
            }

        public String getNumSerie()
            {
                return numSerie;
            }

        public String getNombre()
            {
                return nombre;
            }

        public String getDescripcion()
            {
                return descripcion;
            }

        public String getMarca()
            {
                return marca;
            }

        public Float getPeso()
            {
                return peso;
            }

        public Float getPrecio()
            {
                return precio;
            }

        @Override
        public String toString()
            {
                String aux;
                aux = "{";
                if (numSerie != null)
                    {
                        aux += "\nNumSerie: " + numSerie;
                    }
                if (nombre != null)
                    {
                        aux += "\nNombre: " + nombre;
                    }
                if (descripcion != null)
                    {
                        aux += "\nDescripción: " + descripcion;
                    }
                if (marca != null)
                    {
                        aux += "\nMarca: " + marca;
                    }
                if (peso != null)
                    {
                        aux += "\nPeso: " + peso;
                    }
                if (descripcion != null)
                    {
                        aux += "\nPrecio: " + precio;
                    }
                aux += "\n}";
                return aux;
            }
    }
