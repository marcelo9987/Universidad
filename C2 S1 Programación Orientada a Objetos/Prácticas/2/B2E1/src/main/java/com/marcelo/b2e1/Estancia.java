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
    private Set<Sensor> sensores = new HashSet<>();
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
     * @param sensor
     * @return 1 si se ha ejecutado correctamente y 0 en caso de fallo.
     */
    public boolean darAlta(Sensor sensor)
    {
        // if(this.sensores==)
        if (this.sensores == null)
        {
            return false;
        }
        if (sensor == null)
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
     * @return false si el dato ha sido introducido incorrectamente y false en caso contrario.
     */
    public boolean darAlta(String id, String tipo, float[] rango, float precio)
    {
        if (rango == null)
        {
            System.out.println("ERROR: El rango es nulo");
            return false;
        }
        if (rango.length == 0)
        {
            System.out.println("ERROR: El rango es erróneo");
            return false;
        }
        if (id == null || tipo == null)
        {
            System.out.println("ERROR: Uno de los parámetros es nulo.");
            return false;
        }
        Sensor nuevoSensor = new Sensor(id, tipo, rango, precio);
        if (this.sensores.contains(nuevoSensor))
        {
            return false;
        }
        this.coste += precio;
        this.sensores.add(nuevoSensor);
        return true;
    }

    public boolean nuevoDato(String id, float dato)
    {
        //COMPRUÉBAME
        if (this.sensores == null)
        {
            System.out.println("FUERA DE RANGO");
            return false;
        }
        if (id == null)
        {
            return false;
        }
        {
            for (Iterator<Sensor> actual = this.sensores.iterator(); actual.hasNext(); )
            {
                Sensor posicionActual = actual.next(); //Aquí se produce aliasing
                if (posicionActual.getId().contentEquals(id))
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
        if (tipo == null || this.sensores.size() == 0)
        {
            System.out.println("ERROR en sensoresTipo()");
        }


        Set<Sensor> salidaSensores = new HashSet<>();
        for (Iterator<Sensor> actual = this.sensores.iterator(); actual.hasNext(); )
        {
            Sensor r = actual.next();
            if (r.getTipo().equals(tipo))
            {
                System.out.println(r.getId());
                salidaSensores.add(r);
            }
        }

//        for (Sensor elem:arrSens)
//        {
//            if(elem.getTipo().contentEquals(tipo))
//            {
//                salidaSensores.add(elem);
//            }
//        }
        return salidaSensores;
    }

    /**
     * @param tipo Tipo de sensores a comparar.
     * @return Sensor (o sensores) de
     * un determinado tipo que ha capturado el valor máximo.
     **/

    public Sensor[] sensorMaxValor(String tipo)
    {
        //COMPRUÉBAME


        if(this.sensores==null ||this.sensores.isEmpty())
        {
            System.out.println("ERROR: El Set de sensores no se ha creado correctamente.");
        }
        if (tipo == null)
        {
            System.out.println("ERROR: El tipo no  puede ser nulo");
            return new Sensor[0];
        }

        float maximo = 0;
        byte numerosIguales = 0; //Con un byte es más que necesario, no necesito más espacio
        String[] maximos = new String[this.sensores.size()];//Esta variable aunque tiene mayor tamaño del necesario se desechará al final de la función. Aquesta almacena ids.
        Set<Sensor> sensores = this.sensores;//Haciendo aliasing a pos de ello mismo, no es accidental
        for (Iterator<Sensor> iterator = sensores.iterator(); iterator.hasNext(); )
        {
            Sensor next = iterator.next();
            if (next.maximo() > maximo)
            {
                for (byte i = 0; i < numerosIguales; i++)
                {
                    maximos[i] = " ";
                }
                numerosIguales = 1;
                maximos[0] = next.getId();
                maximo = next.maximo();
            } else if (next.maximo() == maximo)
            {
                numerosIguales++;
                maximos[numerosIguales-1] = next.getId();
            }
        }
        Sensor[] salida = new Sensor[numerosIguales];
        {
            byte contadorReceloso=0;
            for (Iterator<Sensor> iterator = sensores.iterator(); iterator.hasNext(); )
            {
                Sensor next = iterator.next();
                if (maximos[contadorReceloso]!= null && maximos[contadorReceloso].contentEquals(next.getId()))
                {
                    salida[contadorReceloso] = next;
                    contadorReceloso++;
                }

            }
        }
        return salida;
    }


    /**
     * devuelve el sensor (o sensores) de un determinado tipo que ha capturado el valor mínimo.
     *
     * @param tipo
     * @return
     */
    public Sensor[] sensorMinValor(String tipo)
    {
        //COMPRUÉBAME
        if (tipo == null)
        {
            System.out.println("ERROR: El tipo no  puede ser nulo");
            return new Sensor[0];
        }
        if (this.sensores.size() == 0)
        {
            System.out.println("INFO: No existen sensores en esta  estancia, por lo que no se devolverá ninguno.");
            return new Sensor[0];
        }
        float minimo = MAX_VALUE;
        byte numerosIguales = 0; //ídem î
        String[] minimos = new String[this.sensores.size()];
        Set<Sensor> sensores = this.sensores;//Haciendo aliasing a pos de ello mismo, no es accidental
        for (Iterator<Sensor> iterator = sensores.iterator(); iterator.hasNext(); )
        {
            Sensor next = iterator.next();
            if (next.minimo() < minimo)
            {
                for (byte i = 0; i < numerosIguales; i++)
                {
                    minimos[i] = "";
                }
                numerosIguales = 1;
                minimos[numerosIguales] = next.getId();
            } else if (next.maximo() == minimo)
            {
                numerosIguales++;
                minimos[numerosIguales] = next.getId();
            }
        }
        Sensor[] salida = new Sensor[numerosIguales];
        {
            byte contadorReceloso = 0, contadorSinCondiciones = 0;
            for (Iterator<Sensor> iterator = sensores.iterator(); iterator.hasNext(); )
            {
                Sensor next = iterator.next();
                if (next.getId().contentEquals(minimos[contadorSinCondiciones]))
                {
                    salida[contadorReceloso] = next;
                    contadorReceloso++;
                }
                ++contadorSinCondiciones;
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
        //COMPRUÉBAME
        if (id == null)
        {
            return new ArrayList<Float>();
        }
        ArrayList<Float> salida = new ArrayList<Float>();

        for (Iterator<Sensor> iterator = this.sensores.iterator(); iterator.hasNext(); )
        {
            Sensor next = iterator.next();
            if (next.getId().contentEquals(id))
            {
                ArrayList<Float> lista_A_MedioCamino = next.getDatos();//otro aliasing intencional
                for (Float valorActual : lista_A_MedioCamino)
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
                    salida+="   {" + "\"" + actual.getId() + "\"" + ", " + "\"" + actual.media() + "\"" + "}\n";
                }
                salida += "]";
                primeraCadena = false;
            }
        }
        salida += "\n}\n";
        return salida;

    }
}
