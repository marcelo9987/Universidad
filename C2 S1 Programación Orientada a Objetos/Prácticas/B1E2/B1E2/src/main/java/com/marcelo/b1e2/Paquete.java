package com.marcelo.b1e2;

public class Paquete
    {
        private String id;
        private String descripcion;
        private String destino;

        private String[] trayectoActual;
        private Producto[] productos;
        private Float peso;
        private Float precio;

        Paquete(String id)
            {
                this.setId(id);
            }

        Paquete(String id, String destino, Producto[] productos)
            {
                this.setId(id);
                this.setDestino(destino);//orden?
                this.setProductos(productos);


            }

        public void setId(String id)
            {

                this.id = id;//todo: ¿es aceptable que el id sea nulo?

            }

        public String getId()
            {
                return this.id;
            }

        public void setDescripcion(String descripcion)
            {
                if (descripcion == null) return;
                if (descripcion.length() > 200)
                    {
                        this.descripcion = descripcion.substring(0, 200);
                    }
                this.descripcion = descripcion;
            }

        public String getDescripcion()
            {
                return this.descripcion;
            }

        public void setDestino(String destino)
            {
                String destinosAceptables[] = {"A Coruña", "Santiago de Compostela", "Lugo", "Vigo", "Pontevedra", "Ourense", "Lalín", "Verín", "Muros", "Noia", "Ferrol"};
                boolean hit = false;

                int longitud_str = destinosAceptables.length;

                for (int i = 0; i < longitud_str; i++)
                    {
                        if (destino.equals(destinosAceptables[i]))
                            {
                                hit = true;
                                return;
                            }
                    }
                if (hit)
                    {
                        this.destino = destino;
                    } else
                    {
                        System.err.println("No se reconoce el destino seleccionado");
                    }
            }

        public String getDestino()
            {
                return this.destino;
            }

        public void setTrayectoActual(String[] trayectoActual)
            {
                this.trayectoActual = trayectoActual;//todo: trayectoActual puede ser null?
            }

        public String[] getTrayectoActual()
            {
                return this.trayectoActual;
            }
        public void setProductos(Producto[] productos)
            {
                if (productos == null) return;
                this.productos = productos;
                this.peso = calcularPeso();
            }

        public Producto[] getProductos()
            {
                return this.productos;
            }

        public void setPrecio()
            {
                Float pm = calcularPrecioMinimo();
                if (pm == null) return;
                precio = calcularPrecioMinimo() + 10F;
            }

        public Float getPrecio()
            {
                return this.precio;
            }

        public void setPeso()
            {
                this.peso = calcularPeso();
            }

        public Float getPeso()
            {
                return this.peso;
            }

        private Float calcularPeso()
            {
                Float peso = 0F;
                for (int i = 0; i < productos.length; i++)
                    {
                        peso += productos[i].getPeso();
                    }
                return peso;
            }

        private Float calcularPrecioMinimo()
            {
                Float precio_minimo = 0.0f;
                setPeso();
                if (peso < 1)
                    {
                        precio_minimo = 2.5F;
                    } else if (peso < 3)
                    {
                        precio_minimo = 4F;
                    } else
                    {
                        precio_minimo = peso * 1.05F;
                    }
                return precio_minimo;
            }
    }