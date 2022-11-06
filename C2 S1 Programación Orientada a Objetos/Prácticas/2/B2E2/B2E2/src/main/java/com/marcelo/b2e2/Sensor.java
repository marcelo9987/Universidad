/**
 * @author Marcelo Fort Muñoz
 */
package com.marcelo.b2e2;

import java.util.ArrayList;

import static java.lang.Float.*;

public class Sensor
{
    /// CONSTANTES: ///
    public static final String[] TIPOS_VALIDOS = {"temperatura", "sonido", "luz", "humedad"};

    /// ATRIBUTOS: ///

    /**
     * Identificador del sensor.
     */
    private String id;
    /**
     * Tipo de sensor.
     */
    private String tipo;
    /**
     * Nombre de la estancia en la que se encuentra instalado el sensor
     */
    private Estancia estancia;
    /**
     * Conjunto de datos que ha sido capturado por el sensor. El dato más
     * reciente deberá estar en la última posición y el más antiguo en la primera
     */
    private ArrayList<Float> datos;// = new ArrayList<>();
    /**
     * Rango de valores que puede tomar el sensor.
     *
     * @implNote La posición 0 es la inferior y la posición 1 la superior.
     */
    private Float[] rango;
    /**
     * Precio del sensor.
     */
    private Float precio;

    /// Constructores ///

    /**
     * @param id
     * @param tipo
     * @param rango
     * @param precio
     */
    Sensor(String id, String tipo, float[] rango, float precio)
    {
        if (id == null || tipo == null || rango == null)
        {
            System.out.println("Argumento null, no se puede crear el objeto");
            return;
        }
        if (rango.length != 2)
        {
            System.out.println("ERROR: El campo rango ha de tener 2 valores, no se ha podido realizar con éxito la creación del objeto.");
            return;
        }
        if (rango[0] > rango[1])
        {
            System.out.println("ERROR: El valor de rango mínimo ha de ser menor al máximo");
            return;
        }
        if (precio < 0)
        {
            System.out.println("El precio no puede ser negativo y no nulo");
            return;
        }

        boolean tipoValido = false;

        for (String tipoA : TIPOS_VALIDOS)
        {
            if (tipoA.contentEquals(tipo))
            {
                this.tipo = tipo;
                tipoValido = true;
            }
        }

        if (!tipoValido)
        {
            System.out.println("ERROR: El tipo no se encuentra entre los admitidos, no se ha creado el objeto con éxito");
            return;
        }

        this.id = id;
        this.precio = precio;
        this.datos = new ArrayList<>();

        this.rango = new Float[2];
        this.rango[0] = rango[0];
        this.rango[1] = rango[1];

    }


/// GETTERS & SETTERS: ///

    public String getId()
    {
        return id;
    }

    public String getTipo()
    {
        return tipo;
    }

    public Estancia getEstancia()
    {
        return estancia;
    }

    public void setEstancia(Estancia estancia)
    {
        if (this.estancia == null)
        {
            System.out.println("ERROR: La estancia provista es nula.");
            return;
        }
        this.estancia = estancia;
    }

    public ArrayList<Float> getDatos()
    {
        return datos;
    }

    public Float getPrecio()
    {
        return precio;
    }


    /// MÉTODOS: ///

    /**
     * Devuelve el valor mínimo que puede tomar el sensor.
     *
     * @return Devuelve el valor inferior del rango de valores. En caso de que el valor almacenado sea erróneo devuelve -infinito.
     * @see com.marcelo.b2e2.Sensor
     */
    public float limiteInferior()
    {
        if (this.rango == null)
        {
            System.out.println("ERROR: El rango es nulo");
            return Float.NEGATIVE_INFINITY;
        }
        if (this.rango[0] == null)
        {
            System.out.println("ERROR: El valor almacenado es incorrecto");
            return Float.NEGATIVE_INFINITY;
        }
        return this.rango[0];

    }

    /**
     * Devuelve el valor máximo que puede tomar el sensor.
     *
     * @return Devuelve el valor superior del rango de valores. En caso de que el valor almacenado sea erróneo devuelve +infinito.
     * @see Sensor
     */
    public float limiteSuperior()
    {
        if (this.rango == null)
        {
            System.out.println("ERROR: El rango es nulo");
            return Float.POSITIVE_INFINITY;
        }
        if (this.rango[1] == null)
        {
            System.out.println("ERROR: El valor almacenado es incorrecto");
            return Float.POSITIVE_INFINITY;
        }
        return this.rango[1];
    }

    /**
     * Añade un nuevo datos al array de datos.
     *
     * @param dato dato a ser añadido
     * @see Sensor
     */
    public void nuevoDato(float dato)
    {

        if (dato > this.limiteSuperior() || dato < this.limiteInferior())
        {
            System.out.println("ERROR: El dato " + dato + " no está en el rango [" + this.limiteInferior() + ", " + this.limiteSuperior() + "]");
            return;
        }

        this.datos.add(dato);
    }


    /**
     * Devuelve la media de los valores del sensor.
     *
     * @return La media de todos los valores almacenados en el array de datos. En caso de error devuelve NaN
     * @see Sensor
     */
    public float media()
    {
        float media = 0;
        if (this.datos == null || this.datos.isEmpty())
        {
            //   System.out.println("ERROR: No hay datos");
            return Float.NaN;
        }

        for (Float dato : this.datos)
        {
//            if (dato == null)
//            {
//                System.out.println("Hay uno o más datos corruptos. No se ha podido hacer la media");
//                return NaN;
//            }
            media += dato;
        }
        media /= datos.size();
        return media;
    }

    /**
     * Devuelve el máximo de los valores del sensor.
     *
     * @return Devuelve el valor máximo que se encuentra entre los datos. En caso de error, devuelve NaN.
     * @see Sensor
     */
    public float maximo()
    {
        if (this.datos == null || this.datos.isEmpty())
        {
            // System.out.println("ERROR: No No hay datos");
            return NaN;
        }

        float maximo = NEGATIVE_INFINITY;

        for (Float dato : this.datos)
        {
//            if (dato == null)
//            {
//                System.out.println("Hay uno o más datos corruptos. No se ha podido encontrar el máximo");
//                return NaN;
//            }
            if (maximo < dato)
            {
                maximo = dato;
            }
        }

        return maximo;
    }

    /**
     * Devuelve el mínimo de los valores del sensor.
     *
     * @return Devuelve el valor mínimo que se encuentra entre los datos. En caso de error, devuelve NaN.
     * @see Sensor
     */
    public float minimo()
    {
        if (this.datos == null || this.datos.isEmpty())
        {
            //     System.out.println("ERROR: No hay datos");
            return NaN;
        }

        float minimo = POSITIVE_INFINITY;


        for (Float dato : this.datos)
        {
            if (dato == null)
            {
                System.out.println("Hay uno o más datos corruptos. No se ha podido encontrar el mínimo");
                return NaN;
            }
            if (minimo > dato)
            {
                minimo = dato;
            }
        }

        return minimo;
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
        if (this.id == null)
        {
            return false;
        }
        final Sensor other = (Sensor) obj;

        if (!this.id.equals(other.id))
        {
            return false;
        }

        return true;
    }

    @Override
    public String toString()
    {
        String salida = new String();
        boolean primeraCadena = true;
        salida += "{\n";
        if (this.id != null)
        {
            salida += "\"id\": \"" + this.id + "\"";
            primeraCadena = false;
        }
        if (this.tipo != null)
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }
            salida += "\"tipo\": \"" + this.tipo + "\"";
            primeraCadena = false;
        }
        if (this.estancia != null)
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }
            salida += "\"estancia\": \"" + this.estancia.getNombre() + "\"";
            primeraCadena = false;
        }
        if (this.rango != null)
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }
            salida += "\"rango\": " + "[" + "\"" + this.rango[0] + "\"" + ", \"" + this.rango[1] + "\"" + "]";
            primeraCadena = false;
        }
        if (this.datos != null)
        {
            if (this.datos.isEmpty())
            {
            } else
            {
                if (primeraCadena == false)
                {
                    salida += ",\n";
                }
                salida += "\"" + "valores" + "\"" + ": " + "[";
                for (int i = (datos.size() >= 10) ? (datos.size() - 10) : 0; i < datos.size(); i++)
                {
                    salida += "\"" + this.datos.get(i) + "\"";
                    if (i != datos.size() - 1)
                    {
                        salida += ", ";
                    }
                }
                salida += "]";
                primeraCadena = false;
            }
        }
        if (this.precio != null)
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }
            salida += "\"precio\": \"" + this.precio + "\"";
            primeraCadena = false;
        }
        if (!isNaN(this.minimo()))
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }
            salida += "\"minimo\": \"" + this.minimo() + "\"";
            primeraCadena = false;
        }
        if (!isNaN(this.maximo()))
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }
            salida += "\"maximo\": \"" + this.maximo() + "\"";
            primeraCadena = false;
        }
        if (!isNaN(this.media()))
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }
            salida += "\"media\": \"" + this.media() + "\"";
        }
        salida += "\n}\n";
        return salida;
    }

    @Override
    public int hashCode()
    {
        if (this.id == null)
        {
            return 0;
        }
        return this.id.hashCode();
    }

}
