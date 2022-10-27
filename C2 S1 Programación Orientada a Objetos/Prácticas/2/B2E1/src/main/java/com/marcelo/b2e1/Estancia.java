package com.marcelo.b2e1;

import java.util.*;

import static java.lang.Float.*;

/**
 * @author Marcelo Fort Muñoz
 */
public class Estancia
{


    public static final String[] TIPOS_VALIDOS = {"temperatura", "sonido", "luz", "humedad"};


    /**
     * Nombre de la estancia, que también es su identificador único.
     */
    private String nombre;
    /**
     * Planta en la que se encuentra la estancia.
     */
    private int planta;
    /**
     * Conjunto de sensores que están instalados en la estancia.
     */
    private Set<Sensor> sensores;
    /**
     * Coste de la estancia, entendida como la suma del precio de todos los sensores de la
     * estancia.
     */
    private float coste;

    /// CONSTRUCTORES: ///
    Estancia(String nombre, int planta)
    {
        if (nombre == null)
        {
            System.out.println("ERROR: El campo nombre del constructor es nulo. No se ha podido crear el objeto.");
            return;
        }

        this.nombre = nombre;
        this.planta = planta;
        this.sensores = new HashSet<>();
        this.coste = 0;

    }

    /// GETTERS & SETTERS ///

    public String getNombre()
    {
        return this.nombre;
    }

    public int getPlanta()
    {
        return this.planta;
    }

    public Set<Sensor> getSensores()
    {
        return this.sensores;
    }

    public float getCoste()
    {
        return this.coste;
    }

    /// FUNCIONES ///

    /**
     * @param sensor Sensor a dar de alta.
     * @return 1 si se ha ejecutado correctamente y 0 en caso de fallo.
     */
    public boolean darAlta(Sensor sensor)
    {
        if (this.sensores == null)
        {
            return false;
        }
        if (sensor == null)
        {
            return false;
        }
        if (sensor.getId() == null)
        {
            return false;
        }
        if (this.sensores.contains(sensor))
        {
            return false;
        }

        this.sensores.add(sensor);
        this.coste += sensor.getPrecio();

        return true;
    }

    /**
     * @param id
     * @param tipo
     * @param rango
     * @param precio
     * @return false si el dato ha sido introducido incorrectamente y true en caso contrario.
     */
    public boolean darAlta(String id, String tipo, float[] rango, float precio)
    {
//        if (rango == null)
//        {
//            System.out.println("ERROR: El rango es nulo");
//            return false;
//        }
//        if (rango.length == 0)
//        {
//            System.out.println("ERROR: El rango es erróneo");
//            return false;
//        }
//        if (id == null || tipo == null)
//        {
//            System.out.println("ERROR: Uno de los parámetros es nulo.");
//            return false;
//        }
        //
        Sensor nuevoSensor = new Sensor(id, tipo, rango, precio);
//        if (this.sensores.contains(nuevoSensor))
//        {
//            return false;
//        }
//
//        this.sensores.add(nuevoSensor);
//        this.coste += precio;

        return this.darAlta(nuevoSensor);
    }

    public boolean nuevoDato(String id, float dato)
    {

        if (this.sensores == null)
        {
            return false;
        }
        if (id == null)
        {
            return false;
        }

        for (Sensor sensor_actual : this.sensores)
        {
            if (sensor_actual.getId() != null && sensor_actual.getId().equals(id))
            {
                sensor_actual.nuevoDato(dato);
                return true;
            }

        }
        return false;
    }

    /**
     * @param tipo tipo de los sensores a devolver
     * @return : Devuelve el conjunto de sensores
     * de un determinado tipo que hay en la estancia
     */
    public Set<Sensor> sensoresTipo(String tipo)
    {
        Set<Sensor> salidaSensores = new HashSet<>();

        if (tipo == null || this.sensores == null)
        {
            System.out.println("ERROR en sensoresTipo()");
            return salidaSensores;
        }

//        for (Iterator<Sensor> actual = this.sensores.iterator(); actual.hasNext(); )
//        {
//            Sensor r = actual.next();
//            if (r.getTipo().equals(tipo))
//            {
//                System.out.println(r.getId());
//                salidaSensores.add(r);
//            }
//        }

        for (Sensor sensor : this.sensores)
        {
            if (sensor.getTipo() != null && sensor.getTipo().equals(tipo))
            {
                salidaSensores.add(sensor);
            }
        }
        return salidaSensores;
    }

    /**
     * @param tipo Tipo de sensores a comparar.
     * @return Sensor (o sensores) de
     * un determinado tipo que ha capturado el valor máximo.
     **/

    public Sensor[] sensorMaxValor(String tipo)
    {


        if (this.sensores == null || this.sensores.isEmpty())
        {
            System.out.println("ERROR: El Set de sensores no se ha creado correctamente.");
            return new Sensor[0];
        }
        if (tipo == null)
        {
            System.out.println("ERROR: El tipo no  puede ser nulo");
            return new Sensor[0];
        }

        float valorMaximo = Float.MIN_VALUE;
        int n_sensoresConValorMaximo = 0;

        for (Sensor sensor : this.sensores)
        {
            if (sensor.maximo() > valorMaximo)
            {
                valorMaximo = sensor.maximo();
                n_sensoresConValorMaximo = 1;
            }
            if (sensor.maximo() == valorMaximo)
            {
                n_sensoresConValorMaximo++;
            }
        }

        Sensor[] salida = new Sensor[n_sensoresConValorMaximo];

        int i = 0;
        for (Sensor sensor : this.sensores)
        {
            if (sensor.maximo() == valorMaximo)
            {
                salida[i] = sensor;
                i++;
            }
        }
        return salida;
//        for (Sensor sensor : this.sensores)
//        {
//            if (sensor.maximo() > valorMaximo)
//            {
//                for (int i = 0; i < numerosIguales; i++)
//                {
//                    ids_de_los_sensores_cuyos_valores_son_maximos[i] = " ";
//                }
//                numerosIguales = 1;
//                ids_de_los_sensores_cuyos_valores_son_maximos[0] = sensor.getId();
//                valorMaximo = sensor.maximo();
//            } else if (sensor.maximo() == valorMaximo)
//            {
//                numerosIguales++;
//                ids_de_los_sensores_cuyos_valores_son_maximos[numerosIguales - 1] = sensor.getId();
//            }
//        }
//        Sensor[] salida = new Sensor[numerosIguales];
//        {
//            int contador = 0;
//            for (Sensor next : sensores)
//            {
//                if (ids_de_los_sensores_cuyos_valores_son_maximos[contador] != null && ids_de_los_sensores_cuyos_valores_son_maximos[contador].equals(next.getId()))
//                {
//                    salida[contador] = next;
//                    contador++;
//                }
//
//            }
//        }
//        return salida;
    }

    /**
     * devuelve el sensor (o sensores) de un determinado tipo que ha capturado el valor mínimo.
     *
     * @param tipo
     * @return
     */
    public Sensor[] sensorMinValor(String tipo)
    {


        if (this.sensores == null || this.sensores.isEmpty())
        {
            System.out.println("ERROR: El Set de sensores no se ha creado correctamente.");
            return new Sensor[0];
        }
        if (tipo == null)
        {
            System.out.println("ERROR: El tipo no  puede ser nulo");
            return new Sensor[0];
        }

        float valorMinimo = Float.MAX_VALUE;
        int n_sensoresConValorMinimo = 0;

        for (Sensor sensor : this.sensores)
        {
            if (sensor.minimo() < valorMinimo)
            {
                valorMinimo = sensor.minimo();
                n_sensoresConValorMinimo = 1;
            }
            if (sensor.minimo() == valorMinimo)
            {
                n_sensoresConValorMinimo++;
            }
        }

        Sensor[] salida = new Sensor[n_sensoresConValorMinimo];

        int i = 0;
        for (Sensor sensor : this.sensores)
        {
            if (sensor.minimo() == valorMinimo)
            {
                salida[i] = sensor;
                i++;
            }
        }
        return salida;
    }


//    public Sensor[] sensorMaxValor(String tipo)
//    {
//        int tamanhoLista = this.sensores.size();
//        float max = 0;
//        byte numeroPos;
//        byte numSensoresMax =0;
//        Sensor[] arrSens=(Sensor[]) this.sensores.toArray(new Sensor[tamanhoLista]);
//        for(Sensor sensor:arrSens)
//        {
//            if(sensor.getTipo().contentEquals(tipo))
//            {
//                if(sensor.maximo()>max)
//                {
//                    max = sensor.maximo();
//                }
//                if(sensor.maximo()==max)
//                {
//                    numSensoresMax++;
//                }
//            }
//        }
//
//
////        byte[] validosArray=new byte[validos];
//
//
//
//        return void;
//    }

    /**
     * Devuelve el conjunto de valores de un sensor con identificador id que superan un determinado valor.
     *
     * @param id
     * @param valor
     * @return
     */
    public ArrayList<Float> valoresSuperiores(String id, float valor)
    {
        ArrayList<Float> salida = new ArrayList<>();

        if (id == null)
        {
            return salida;
        }


        for (Sensor sensor : this.sensores)
        {
            if (sensor.getId().equals(id))
            {
                for (Float valorActual : sensor.getDatos())
                {
                    if (valorActual > valor)
                    {
                        salida.add(valorActual);
                    }
                }
                break;
            }
        }

        return salida;
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
        if (this.nombre == null)
        {
            return false;
        }

        final Estancia other = (Estancia) obj;

        if (!this.nombre.equals(other.nombre))
        {
            return false;
        }
        if (this.planta != other.planta)
        {
            return false;
        }

        return true;
    }

    @Override
    public java.lang.String toString()
    {

        String salida = new String();
        boolean primeraCadena = true;

        salida += "{\n";
        if (this.nombre != null)
        {
            salida += "\"nombre\": \"" + this.nombre + "\"";
            primeraCadena = false;
        }
        if (primeraCadena == false)
        {
            salida += ",\n";
        }
        salida += "\"planta\": \"" + this.planta + "\"";
        primeraCadena = false;

        if (this.sensores != null)
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }
            salida += "\"estancia\": \"" + this.sensores.toString() + "\"";
            primeraCadena = false;
        }

        if (primeraCadena == false)
        {
            salida += ",\n";
        }
        salida += "\"coste\": " + "\"" + this.coste + "\"";
        primeraCadena = false;

        if (this.sensores != null)
        {
            if (this.sensores.isEmpty())
            {

            } else
            {
                if (primeraCadena == false)
                {
                    salida += ",\n";
                }
                salida += "\"" + "sensores_media" + "\"" + ": " + "[";
                for (Iterator<Sensor> iterator = this.sensores.iterator(); iterator.hasNext(); )
                {
                    Sensor actual = iterator.next();
                    salida += "   {" + "\"" + actual.getId() + "\"" + ", " + "\"" + actual.media() + "\"" + "}\n";
                }
                salida += "]";
                primeraCadena = false;
            }
        }
        salida += "\n}\n";
        return salida;

    }

    @Override
    public int hashCode()
    {
        int result = nombre != null ? nombre.hashCode() : 0;
        result = 31 * result + planta;
        return result;
    }
}
