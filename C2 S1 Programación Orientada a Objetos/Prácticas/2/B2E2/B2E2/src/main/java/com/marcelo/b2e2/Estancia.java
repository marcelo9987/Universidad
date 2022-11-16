package com.marcelo.b2e2;

import java.util.*;

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
    private HashMap<String, Sensor> sensores;
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
        this.sensores = new HashMap<>();
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

    public HashMap<String, Sensor> getSensores()
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
        if (this.sensores.containsKey(sensor.getId()))
        {
            return false;
        }

        if (sensor.getPrecio() == null || sensor.getPrecio() <= 0)
        {
            return false;
        }

        this.sensores.put(sensor.getId(), sensor);
        this.coste += sensor.getPrecio();

        return true;
    }

    /**
     * @param id     id del sensor a introducir.
     * @param tipo   tipo del sensor a introducir.
     * @param rango  rango del sensor a introducir.
     * @param precio precio del sensor a introducir.
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

        {
            for (Iterator<Sensor> iterator = this.sensores.values().iterator(); iterator.hasNext(); )
            {
                Sensor sensor_actual = iterator.next(); //Aquí se produce aliasing
                if (sensor_actual.getId() != null && sensor_actual.getId().equals(id))
                {
                    int tamInicial = sensor_actual.getDatos().size();
                    sensor_actual.nuevoDato(dato);
                    int tamFinal = sensor_actual.getDatos().size();
                    return tamInicial != tamFinal;
                }
            }

        }
        return false;
    }

    /**
     * @param tipo tipo de los sensores a devolver
     * @return Devuelve el conjunto de sensores
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

        for (Iterator<String> keysIterator = this.sensores.keySet().iterator(); keysIterator.hasNext(); )
        {
            String sensorId = keysIterator.next();
            if (this.sensores.get(sensorId).getTipo().equals(tipo))
            {
                salidaSensores.add(this.sensores.get(sensorId));
            }
        }
        return salidaSensores;
    }

    /**
     * Devuelve el sensor (o sensores) de un determinado tipo que ha capturado el valor máximo.
     *
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

        for (Iterator<Sensor> iterator = this.sensores.values().iterator(); iterator.hasNext(); )
        {
            Sensor sensor = iterator.next();

            if (sensor.getTipo().equals(tipo))
            {
                if (sensor.maximo() == valorMaximo)
                {
                    n_sensoresConValorMaximo++;
                } else if (sensor.maximo() > valorMaximo)
                {
                    valorMaximo = sensor.maximo();
                    n_sensoresConValorMaximo = 1;
                }
            }
        }

        Sensor[] salida = new Sensor[n_sensoresConValorMaximo];

        int i = 0;
        for (Iterator<Sensor> iterator = this.sensores.values().iterator(); iterator.hasNext(); )
        {
            Sensor sensor = iterator.next();

            if (sensor.getTipo().equals(tipo))
            {
                if (sensor.maximo() == valorMaximo)
                {
                    salida[i] = sensor;
                    i++;
                }
            }
        }
        return salida;
    }

    /**
     * @param tipo Tipo de sensores a comparar.
     * @return Sensor (o sensores) de
     * un determinado tipo que ha capturado el valor máximo.
     **/

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

        for (String sensorId : this.sensores.keySet())
        {
            Sensor sensor = this.sensores.get(sensorId);

            if (sensor.getTipo().equals(tipo))
            {
                if (sensor.minimo() == valorMinimo)
                {
                    n_sensoresConValorMinimo++;
                } else if (sensor.minimo() < valorMinimo)
                {
                    valorMinimo = sensor.minimo();
                    n_sensoresConValorMinimo = 1;
                }
            }
        }

        Sensor[] salida = new Sensor[n_sensoresConValorMinimo];

        int i = 0;
        for (String sensorId : this.sensores.keySet())
        {
            Sensor sensor = this.sensores.get(sensorId);

            if (sensor.getTipo().equals(tipo))
            {
                if (sensor.minimo() == valorMinimo)
                {
                    salida[i] = sensor;
                    i++;
                }
            }
        }
        return salida;
    }

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


        for (Sensor sensor : this.sensores.values())
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


    public HashMap<String, ArrayList<Float>> valoresSensorTipo(String tipo)
    {
        HashMap<String, ArrayList<Float>> salida = new HashMap<>();
        if (tipo == null)
        {
            System.out.println("ERROR en valoresSensorTipo: tipo es nulo, devolviendo HashMap vacío.");
            return salida;
        }

        for (Iterator<String> keysIterator = this.sensores.keySet().iterator(); keysIterator.hasNext(); )
        {
            String sensorId = keysIterator.next();
            if (this.sensores.get(sensorId).getTipo().equals(tipo))
            {
                salida.put(sensorId, this.sensores.get(sensorId).getDatos());
            }
        }
        return salida;
    }

    public ArrayList<Sensor> sensoresCosteMayor(float valor)
    {
        ArrayList<Sensor> salida = new ArrayList<>();
        if (valor <= 0)
        {
            System.out.println("ERROR en sensoresCosteMayor: El valor es inferior o igual a 0");
            return salida;
        }

        for (Iterator<Map.Entry<String, Sensor>> entryIterator = this.sensores.entrySet().iterator(); entryIterator.hasNext(); )
        {
            Map.Entry<String, Sensor> entry = entryIterator.next();
            if (entry.getValue().getPrecio() > valor)
            {
                salida.add(entry.getValue());
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
        if (this.getNombre() == null)
        {
            return false;
        }

        final Estancia other = (Estancia) obj;

        if (!this.getNombre().equals(other.getNombre()))
        {
            return false;
        }
        if (this.getPlanta() != other.getPlanta())
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
        if (this.nombre != null)
        {
            salida += "\"nombre\": \"" + this.nombre+"\"";
            primeraCadena = false;
        }
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }

            salida += "\"planta\": \"" + this.planta + "\"";
            primeraCadena = false;
        }
        if (this.sensores != null && !this.sensores.isEmpty())
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }
            salida += "\"" + "sensores" + "\"" + ": " + "[";
            boolean primeraSubCadena = true;
            for (Iterator<String> keysIterator = this.sensores.keySet().iterator(); keysIterator.hasNext(); )
            {
                if (primeraSubCadena == false)
                {
                    salida += ", ";
                }
                String sensorId = keysIterator.next();
                salida += sensorId;
                primeraSubCadena = false;
            }
            salida += "]";
            primeraCadena = false;
        }

        if (coste > 0)
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }

            salida += "\"coste\": " + "\"" + this.coste + "\"";
            primeraCadena = false;
        }

        if (this.sensores != null && !this.sensores.isEmpty())
        {

            if (primeraCadena == false)
            {
                salida += ",\n";
            }
            salida += "\"" + "sensores_media" + "\"" + ": " + "[";
            boolean primeraSubCadena = true;
            for (Iterator<Sensor> iterator = this.sensores.values().iterator(); iterator.hasNext(); )
            {
                if (primeraSubCadena == false)
                {
                    salida += ",\n";
                }
                Sensor sensor = iterator.next();
                salida += "   {" + "\"" + sensor.getId() + "\"" + ", " + "\"" + sensor.media() + "\"" + "}";
                primeraSubCadena = false;
            }
            salida += "]";
            primeraCadena = false;
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
