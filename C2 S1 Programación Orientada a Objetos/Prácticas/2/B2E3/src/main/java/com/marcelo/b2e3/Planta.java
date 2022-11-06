package com.marcelo.b2e3;

import java.util.*;

public class Planta
{
    public static final String[] TIPOS_VALIDOS = {"oficinas", "viviendas libres", "viviendas de protección oficial", "administración"};

    /// ATRIBUTOS ///
    private int numero;
    private String tipo;
    private Edificio edificio;
    private HashMap<String, Estancia> estancias;
    private float presupuesto;
    private HashMap<String, Sensor> sensoresConProblemas;

    Planta(int numero, String tipo, Edificio edificio, HashMap<String, Estancia> estancias)
    {
        if (tipo == null || edificio == null || estancias == null)// || estancias.isEmpty())
        {
            System.out.println("Argumento incorrecto, no se puede crear el objeto");
            return;
        }

        boolean tipo_valido = false;
        for (String tipoA : TIPOS_VALIDOS)
        {
            if (tipoA.equals(tipo))
            {
                tipo_valido = true;
            }
        }
        if (!tipo_valido)
        {

            System.out.println("ERROR: El tipo no se encuentra entre los admitidos, no se ha creado el objeto con éxito");
            return;
        }

        this.numero = numero;
        this.tipo = tipo;
        this.edificio = edificio;
        this.estancias = estancias;

        this.presupuesto = 0;
        for (Estancia estancia : this.estancias.values())
        {
            this.presupuesto += 1.1 * estancia.getCoste();
        }

        this.sensoresConProblemas = new HashMap<>();
    }

    Planta(int numero, String tipo)
    {
        if (tipo == null)
        {
            System.out.println("Argumento incorrecto, no se puede crear el objeto");
            return;
        }

        boolean tipo_valido = false;
        for (String tipoA : TIPOS_VALIDOS)
        {
            if (tipoA.equals(tipo))
            {
                tipo_valido = true;
            }
        }
        if (!tipo_valido)
        {

            System.out.println("ERROR: El tipo no se encuentra entre los admitidos, no se ha creado el objeto con éxito");
            return;
        }

        this.numero = numero;
        this.tipo = tipo;
        this.edificio = null;
        this.estancias = new HashMap<>();
        this.presupuesto = 0;
        this.sensoresConProblemas = new HashMap<>();


    }

    public int getNumero()
    {
        return numero;
    }

    public String getTipo()
    {
        return tipo;
    }

    public void setTipo(String tipo)
    {
        if (tipo == null)
        {
            return;
        }

        boolean tipoValido = false;
        for (String tipoV : TIPOS_VALIDOS)
        {
            if (tipo.equals(tipoV))
            {
                tipoValido = true;
                break;
            }
        }

        if (!tipoValido)
        {
            return;
        }

        this.tipo = tipo;
    }

    public Edificio getEdificio()
    {
        return edificio;
    }

    public void setEdificio(Edificio edificio)
    {
        if (edificio == null)
        {
            return;
        }
        this.edificio = edificio;
    }


    public HashMap<String, Estancia> getEstancias()
    {
        return estancias;
    }

    public void setEstancias(HashMap<String, Estancia> estancias)
    {
        if (estancias == null)
        {
            return;
        }

        this.presupuesto = 0;
        for (Estancia estancia : this.estancias.values())
        {
            this.presupuesto += 1.1 * estancia.getCoste();
        }

        this.estancias = estancias;

    }

    public float getPresupuesto()
    {
        return presupuesto;
    }

    public HashMap<String, Sensor> getSensoresConProblemas()
    {
        return sensoresConProblemas;
    }

    /**
     * @param estancias Estancias
     * @return false en caso de que fallen una o más estancias y, true en caso contrario
     * Es posible usar la función darAltaEstancia(Estancia estancia) para introducir estancias de forma individual.
     */
    public boolean darAltaEstancia(ArrayList<Estancia> estancias)
    {
        if (estancias == null || estancias.isEmpty())
        {
            return false;
        }

        for (Estancia estancia : estancias)
        {
            if (estancia == null)
            {
                return false;
            }
            if (estancia.getPlanta().getNumero() != this.numero)
            {
                return false;
            }
            if (this.estancias.containsKey(estancia.getNombre()))
            {
                return false;
            }
        }

        for (Estancia estancia : estancias)
        {
            this.estancias.put(estancia.getNombre(), estancia);
            this.presupuesto += 1.1 * estancia.getCoste();
        }
        return true;
    }

    public boolean darAltaEstancia(Estancia estancia)
    {
        if (estancia == null)
        {
            return false;
        }
        if (estancia.getPlanta().getNumero() != this.numero)
        {
            return false;
        }
        if (this.estancias.containsKey(estancia.getNombre()))
        {
            return false;
        }

        this.estancias.put(estancia.getNombre(), estancia);
        this.presupuesto += 1.1 * estancia.getCoste();

        return true;
    }

    public void darAltaSensor(String id, ArrayList<Sensor> sensores)
    {
        if (id == null || sensores == null || sensores.isEmpty())
        {
            System.out.println("ERROR: Argumentos no válidos.");
            return;
        }

        if (this.estancias == null || this.estancias.containsKey(id) == false)
        {
            System.out.println("ERROR: Argumentos no válidos.");
            return;
        }

        for (Sensor sensor : sensores)
        {
            if (this.estancias.get(id).getSensores().containsKey(sensor.getId()))
            {
                System.out.println("ERROR: El sensor " + sensor.getId() + " ya existe en esta estancia.");
                return;
            }
        }
        for (Sensor sensor : sensores)
        {
            this.estancias.get(id).darAlta(sensor);
            this.presupuesto += 1.1 * sensor.getPrecio();
        }
    }

    public void darAltaSensor(String id, Sensor sensor)
    {
        if (id == null || sensor == null || this.estancias == null || !this.estancias.containsKey(id))
        {
            System.out.println("ERROR: Argumentos no válidos.");
            return;
        }
        if (this.estancias.get(id).getSensores().containsKey(sensor.getId()))
        {
            System.out.println("ERROR: El sensor " + sensor.getId() + " ya existe en esta estancia.");
            return;
        }
        this.estancias.get(id).darAlta(sensor);
        this.presupuesto += 1.1 * sensor.getPrecio();
    }

    public void darBajaSensor(String id, Sensor sensor)
    {
        //COMPRUÉBAME
        if (id == null || sensor == null || this.estancias == null)
        {
            System.out.println("ERROR: Argumentos no válidos.");
            return;
        }
        if (this.sensoresConProblemas.containsKey(id))
        {
            System.out.println("ERROR: El sensor " + id + " ya existe en sensores con problemas.");
            return;
        }
        for (Estancia estancia : this.estancias.values())
        {
            if (estancia.getSensores().containsKey(id))
            {

                this.sensoresConProblemas.put(id, estancia.getSensores().get(id));
                estancia.darBaja(id);
                estancia.darAlta(sensor);
                this.presupuesto += 1.1 * sensor.getPrecio();
                return;
            }
        }


    }

    public Set<Sensor> sensoresTipo(String tipo)
    {
        Set<Sensor> salida = new HashSet<>();
        if (tipo == null || this.estancias == null || this.estancias.isEmpty())
        {
            return salida;
        }

        for (Iterator<Estancia> iterator = this.estancias.values().iterator(); iterator.hasNext(); )
        {
            Estancia estancia = iterator.next();
            salida.addAll(estancia.sensoresTipo(tipo));
        }
        return salida;
    }


    public Set<String> tipoSensoresMasDefectuosos()
    {
        Set<String> salida = new HashSet<>();

        for (Iterator<String> keyIterator = sensoresConProblemas.keySet().iterator(); keyIterator.hasNext(); )
        {
            String idSensor = keyIterator.next();
            if (!salida.contains(this.sensoresConProblemas.get(idSensor).getTipo()))
            {
                salida.add(this.sensoresConProblemas.get(idSensor).getTipo());
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


        final Planta other = (Planta) obj;

        if (this.getNumero() != other.getNumero())
        {
            return false;
        }
        if (this.edificio.equals(other.edificio) == false)
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

        {
            salida += "\"numero\": \"" + this.numero + "\"";
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
        if (this.edificio != null && this.edificio.getId() != null)
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }
            salida += "\"edificio\": \"" + this.edificio.getId() + "\"";
            primeraCadena = false;
        }
        if (this.estancias != null && this.estancias.isEmpty()==false)
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }
            salida += "\"estancias\": [";

            boolean primeraSubCadena = true;
            for (Iterator<String> keysIterator = this.estancias.keySet().iterator(); keysIterator.hasNext(); )
            {
                if (primeraSubCadena == false)
                {
                    salida += ",";
                }
                String estanciaId = keysIterator.next();
                salida += this.estancias.get(estanciaId).getNombre();
                primeraSubCadena = false;
            }
            salida += "]";

            primeraCadena = false;
        }
        if (this.presupuesto>0)
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }
            salida += "\"presupuesto\": \"" + this.presupuesto + "\"";
            primeraCadena = false;
        }

        if (this.sensoresConProblemas != null && !this.sensoresConProblemas.isEmpty())
        {
            if (primeraCadena == false)
            {
                salida += ",\n";
            }

            salida += "\"" + "sensoresConProblemas" + "\"" + ": " + "[";
            boolean primeraSubCadena = true;
            for (Iterator<String> keysIterator = this.sensoresConProblemas.keySet().iterator(); keysIterator.hasNext(); )
            {
                if (primeraSubCadena == false)
                {
                    salida += ",";
                }
                String sensorId = keysIterator.next();
                salida += sensorId;
                primeraSubCadena = false;
            }
            salida += "]";
            primeraCadena = false;
        }
        salida+="\n}";
        return salida;
    }
}
