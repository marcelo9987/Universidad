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

    Paquete(String _id)
    {
        this.setId(_id);
    }

    Paquete(String _id,String _destino,Producto[] _productos)
    {
        this.setId (_id);
        this.setProductos(_productos);
        this.setDestino(_destino);

    }

    public void setId(String _id)
    {
        if(_id==null)return;
        this.id = _id;
    }

    public void setDescripcion(String _descripcion)
    {
        if(_descripcion==null)return;
        if(_descripcion.length()>200)
        {
            _descripcion=_descripcion.substring(0,200);
        }
        this.descripcion = _descripcion;
    }

    public void setDestino(String _destino)
        {
            String destinosAceptables[]={"A Coruña","Santiago de Compostela", "Lugo","Vigo","Pontevedra","Ourense","Lalín","Verín","Muros","Noia","Ferrol"};
            boolean hit = false;

            int longitud_str = destinosAceptables.length;

            for (int i =0; i< longitud_str;i++)
            {
                if(_destino.equals(destinosAceptables[i]))
                {
                    hit = true;
                    return;
                }
            }
            if(hit)
            {
                destino = _destino;
            }else
            {
                System.err.println("No se reconoce el destino seleccionado");
            }
        }

    public void setProductos(Producto[] _productos)
    {
        if(_productos==null)return;
        productos = _productos;
        peso=calcularPeso();
    }
    public void setPrecio()
        {
            precio = calcularPrecioMinimo()+10F;
        }

    @Override
    public String toString()
    {
        return this.descripcion;
    }
    public void setPeso()
        {
            calcularPeso();
        }
    private Float calcularPeso()
    {
        Float peso = 0F;
        for(int i =0; i<productos.length;i++)
        {
            peso += productos[i].getPeso();
        }
        return peso;
    }

    private Float calcularPrecioMinimo()
        {
            Float precio_minimo=0.0F;
            setPeso();
            if(peso<1)
            {
                precio_minimo = 2.5F;
            }else if (peso<3)
            {
                precio_minimo = 4F;
            }else
            {
                precio_minimo = peso * 1.05F;
            }
            return precio_minimo;
        }
}