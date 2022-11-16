package com.marcelo.b2e3;

import java.util.*;

/**
 * @author Marcelo Fort Muñoz
 */
public class Estancia
{


    public static final String[] TIPOS_VALIDOS_ESTANCIAS = {"temperatura", "sonido", "luz", "humedad"};


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
        this.sensores= new HashMap<String, Sensor>();
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
        if (this.sensores.containsKey(sensor.getId()))
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
     * @return false si el dato ha sido introducido incorrectamente y false en caso contrario.
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

    public boolean darBaja(String id)
    {
        if(id==null)
        {
            System.out.println("ERROR: el id es nulo.");
            return false;
        }
        if (this.sensores.containsKey(id))
        {
            this.sensores.remove(id);
            return true;
        }else
        {
            System.out.println("El id no existe");
        }
        return false;
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
            for (Iterator<Sensor> actual = this.sensores.values().iterator(); actual.hasNext(); )
            {
                Sensor posicionActual = actual.next(); //Aquí se produce aliasing
                if (posicionActual.getId()!= null && posicionActual.getId().equals(id))
                {
                    posicionActual.nuevoDato(dato);
                    return true;
                }
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

        for (Iterator<String> actual = this.sensores.keySet().iterator(); actual.hasNext(); )
        {
            String posAct = actual.next();
            if (this.sensores.get(posAct).getTipo().equals(tipo))
            {
                System.out.println(posAct);
                salidaSensores.add(this.sensores.get(posAct));
            }
        }
        return salidaSensores;
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

        float valorMaximo = Float.MIN_VALUE;
        int n_sensoresConValorMaximo = 0;

        for (Iterator<Sensor> iterator = this.sensores.values().iterator(); iterator.hasNext(); )
        {
            Sensor sensorActual = iterator.next();
            if(sensorActual.maximo()>valorMaximo)
            {
                valorMaximo = sensorActual.maximo();
            }
            if(sensorActual.maximo() == valorMaximo)
            {
                n_sensoresConValorMaximo++;
            }

        }

        Sensor[] salida = new Sensor[n_sensoresConValorMaximo];

        int i =0;
        for (Iterator<Sensor> iterator = this.sensores.values().iterator(); iterator.hasNext();)
        {
             Sensor sensor = iterator.next();
             if(sensor.maximo() == valorMaximo)
             {
                 salida[i] = sensor;
                 i++;
             }
        }
        return salida;
    }


//    /**
//     * devuelve el sensor (o sensores) de un determinado tipo que ha capturado el valor mínimo.
//     *
//     * @param tipo tipo de los sensores a comparar.
//     * @return Conjunto de sensores con el valor mínimo.
//     */
//    public Sensor[] sensorMinValor(String tipo)
//    {
//        //COMPRUÉBAME
//        if (tipo == null)
//        {
//            System.out.println("ERROR: El tipo no  puede ser nulo");
//            return new Sensor[0];
//        }
//        if (this.sensores.size() == 0)
//        {
//            System.out.println("INFO: No existen sensores en esta  estancia, por lo que no se devolverá ninguno.");
//            return new Sensor[0];
//        }
//        float minimo = MAX_VALUE;
//        byte numerosIguales = 0;
//        String[] minimos = new String[this.sensores.size()];
//
//        for (String claveActual : this.sensores.keySet())
//        {
//            if (this.sensores.get(claveActual).minimo() < minimo)
//            {
//                for (byte i = 0; i < numerosIguales; i++)
//                {
//                    minimos[i] = "";
//                }
//                numerosIguales = 1;
//                minimos[numerosIguales] = claveActual;
//            } else if (this.sensores.get(claveActual).maximo() == minimo)
//            {
//                numerosIguales++;
//                minimos[numerosIguales] = claveActual;
//            }
//        }
//        Sensor[] salida = new Sensor[numerosIguales];
//        {
//            byte contadorReceloso = 0, contadorSinCondiciones = 0;
//            for (String claveActual : this.sensores.keySet())
//            {
//                if (claveActual.contentEquals(minimos[contadorSinCondiciones]))
//                {
//                    salida[contadorReceloso] = this.sensores.get(claveActual);
//                    contadorReceloso++;
//                }
//                ++contadorSinCondiciones;
//            }
//        }
//        return salida;
//    }

    /**
          * devuelve el sensor (o sensores) de un determinado tipo que ha capturado el valor mínimo.
          *
          * @param tipo tipo de los sensores a comparar.
          * @return Conjunto de sensores con el valor mínimo.
     */
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

        float valorMinimo = Float.MAX_VALUE;
        int n_sensoresConValorMinimo = 0;

        for (Iterator<Sensor> iterator = this.sensores.values().iterator(); iterator.hasNext(); )
        {
            Sensor sensorActual = iterator.next();
            if(sensorActual.minimo()>valorMinimo)
            {
                valorMinimo = sensorActual.maximo();
            }
            if(sensorActual.minimo() == valorMinimo)
            {
                n_sensoresConValorMinimo++;
            }

        }

        Sensor[] salida = new Sensor[n_sensoresConValorMinimo];

        int i =0;
        for (Iterator<Sensor> iterator = this.sensores.values().iterator(); iterator.hasNext();)
        {
            Sensor sensor = iterator.next();
            if(sensor.maximo() == valorMinimo)
            {
                salida[i] = sensor;
                i++;
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


        for (Sensor sensAct : this.sensores.values())
        {
            if (sensAct.getId().equals(id))
            {
                for (Float valorActual : sensAct.getDatos())
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
        if (tipo == null)
        {
            System.out.println("ERROR en valoresSensorTipo: tipo es nulo, devolviendo HashMap vacío.");
            return new HashMap<String, ArrayList<Float>>();
        }
        HashMap<String, ArrayList<Float>> salida = new HashMap<String, ArrayList<Float>>();

        for (Iterator<String> iterator = this.sensores.keySet().iterator(); iterator.hasNext(); )
        {
            String posAct = iterator.next();
            if (this.sensores.get(posAct).getTipo().contentEquals(tipo))
            {
                salida.put(posAct, this.sensores.get(posAct).getDatos());
            }
        }
        return salida;
    }

    public ArrayList<Sensor> sensoresCosteMayor(float valor)
    {
        if (valor <= 0)
        {
            System.out.println("ERROR en sensoresCosteMayor: El valor es inferior o igual a 0");
            return new ArrayList<>();
        }
        ArrayList<Sensor> salida = new ArrayList<>();
        for(Iterator<Map.Entry<String,Sensor>> iterator= this.sensores.entrySet().iterator() ; iterator.hasNext();)
        {
            Map.Entry<String,Sensor> objAct = iterator.next();
            if(objAct.getValue().getPrecio()>valor)
            {
                salida.add(objAct.getValue());
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
        final Estancia other = (Estancia) obj;
        if (!this.nombre.equals(other.getNombre()))
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
            salida += "\"nombre\": \"" + this.nombre + "\",\n";
            primeraCadena = false;
            salida += "\"planta\": \"" + this.planta + "\"";
            primeraCadena = false;
        }
        if (this.sensores != null)
        {
            if (!primeraCadena)
            {
                salida += ",\n";
            }
            salida += "\"sensores: \": [" ;
            int cnt=0;
            for(Iterator<String> ids=this.sensores.keySet().iterator();ids.hasNext();)
            {
                String clave=ids.next();
                salida+="<"+clave+">";
                cnt++;
                if(this.sensores.keySet().size()<cnt)
                {
                    salida+=",";
                }else
                {
                   salida+="]";
                }

            }
            primeraCadena = false;
        }

        if (coste > 0)
        {
            if (!primeraCadena)
            {
                salida += ",\n";
            }
            salida += "\"coste\": " + "\"" + this.coste + "\"";
            primeraCadena = false;
        }

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
                for (Iterator<Sensor> iterator = this.sensores.values().iterator(); iterator.hasNext(); )
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
