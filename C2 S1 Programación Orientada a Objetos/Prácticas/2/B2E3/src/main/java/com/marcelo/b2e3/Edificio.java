package com.marcelo.b2e3;


import java.util.*;

public class Edificio
{
    String id;
    int[] rango;
    HashMap<Integer, Planta> plantas;
    float presupuesto;

    /*
     * id (String), rango (int[]) y plantas
     * (ArrayList<Planta>),
     */
    Edificio(String id, int[] rango, ArrayList<Planta> plantas)
    {
        if (id == null || rango == null || plantas == null)
        {
            return;
        }
        if (plantas.isEmpty())
        {
            return;
        }
        if (rango[0] > rango[1])
        {
            return;
        }
        if (rango[0] < -2 || rango[1] > 6)
        {
            return;
        }
//        for (Planta planta : plantas)
//        {
//            if (planta.getNumero() < rango[0] || planta.getNumero() > rango[1])
////            {
////                return;
////            }
//        }


        this.id = id;

        this.rango = new int[2];
        this.rango[0] = rango[0];
        this.rango[1] = rango[1];
        this.plantas = new HashMap<>();
        this.presupuesto = 0;
        for (Planta planta : plantas)
        {
            if (planta.getNumero() >= rango[0] && planta.getNumero() <= rango[1])
            {
                if (this.plantas.containsKey(planta.getNumero()) == false)
                {
                    planta.setEdificio(this);
                    this.plantas.put(planta.getNumero(), planta);
                    this.presupuesto += planta.getPresupuesto();
                } else
                {
                    System.out.println("ERROR: La planta " + planta.getNumero() + " ya se encuentra en el edificio.");
                }
            } else
            {
                System.out.println("ERROR: La planta " + planta.getNumero() + " no se encuentra en el rango aceptable.");
            }
        }

    }

    Edificio(String id)
    {
        if (id == null)
        {
            return;
        }
        this.id = id;
        this.rango = new int[]{-2, 6};
        this.plantas = new HashMap<>();
        this.presupuesto = 0;
    }


    public String getId()
    {
        return id;
    }

    public int[] getRango()
    {
        return rango;
    }

    public HashMap<Integer, Planta> getPlantas()
    {
        return plantas;
    }

    public float getPresupuesto()
    {
        return presupuesto;
    }


    public void setRango(int[] rango)
    {
        if (rango == null || rango[0] > rango[1])
        {
            return;
        }
        if (rango[0] < -2 || rango[1] > 6)
        {
            return;
        }
        this.rango[0] = rango[0];
        this.rango[1] = rango[1];
    }


    /**
     * Da de alta una planta, teniendo
     * en cuenta las restricciones indicadas en los constructores.
     *
     * @param planta Planta a dar de alta.
     * @return false en fallo, true en caso de éxito.
     */

    public boolean darAltaPlanta(Planta planta)
    {
        if (planta == null)
        {
            return false;
        }

        int numPlanta = planta.getNumero();
        if (numPlanta < this.rango[0] || numPlanta > this.rango[1])
        {
            System.out.println("ERROR: La planta " + planta.getNumero() + " no se encuentra en el rango aceptable.");
            return false;
        }

        if (this.plantas.containsKey(numPlanta))
        {
            System.out.println("ERROR: La planta " + planta.getNumero() + " ya se encuentra en el edificio.");
            return false;
        }

        planta.setEdificio(this);
        this.plantas.put(numPlanta, planta);
        this.presupuesto += planta.getPresupuesto();
        return true;
    }

    /**
     * Devuelve los número de las plantas que aún no han sido
     * dadas de alta en el edificio.
     *
     * @return número de las plantas que aún no han sido
     * dadas de alta en el edificio
     */
    public int[] plantasNoAlta()
    {
        int n_plantasAusentes = 0;
        for (int i = this.rango[0]; i <= this.rango[1]; i++)
        {
            if (!this.plantas.containsKey(i))
            {
                n_plantasAusentes++;
            }
        }
        int[] salida = new int[n_plantasAusentes];

        int indicePlantaNoImplementada = 0;
        for (int i = this.rango[0]; i <= this.rango[1]; i++)
        {
            if (!this.plantas.containsKey(i))
            {
                salida[indicePlantaNoImplementada] = i;
                indicePlantaNoImplementada++;
            }
        }
        return salida;
    }

    /**
     * Obtiene las plantas que tienen un
     * presupuesto mayor
     *
     * @return Plantas con presupuesto mayor
     */
    public Set<Planta> plantasMasCaras()
    {
        int numPlantasCaras = 0;
        float precioMasCaro = 0;
        for (Iterator<Planta> iterator = this.plantas.values().iterator(); iterator.hasNext(); )
        {
            Planta planta = iterator.next();

            if (planta.getPresupuesto() > precioMasCaro)
            {
                precioMasCaro = planta.getPresupuesto();
                numPlantasCaras = 1;
            }
            if (planta.getPresupuesto() == precioMasCaro)
            {
                numPlantasCaras++;
            }

        }
        Set<Planta> salida = new HashSet<>(numPlantasCaras);
        for (Iterator<Planta> iterator = this.plantas.values().iterator(); iterator.hasNext(); )
        {
            Planta planta = iterator.next();
            if (planta.getPresupuesto() == precioMasCaro)
            {
                salida.add(planta);
            }
        }
        return salida;
    }


    /**
     * @return Conjunto de estancias que tiene un mayor número de problemas en cada planta, donde la clave
     * será el número de la planta y los valores serán el conjunto de estancias de cada planta que tienen un
     * mayor número de problemas (en el caso de que haya más de una estancia con un mismo número).
     */

    public HashMap<Integer, Set<Estancia>> plantasMasProblemas()
    {
//        int n_plantasConProblemas = 0;

        HashMap<Integer, Set<Estancia>> salida = new HashMap<>();

        if (this.plantas == null)
        {
            return salida;
        }


        for (Planta planta : this.plantas.values())
        {
//            int n_estanciasProblematicasPlanta = 0;

            if (planta.getSensoresConProblemas() == null || planta.getSensoresConProblemas().isEmpty())
            {
                continue;
            }

            int maxNumProblemas = 0;

            Map<String, Integer> sensoresConProblemasPorEstancia = new HashMap<>();
            for (Sensor sensor : planta.getSensoresConProblemas().values())
            {
                int numProblemas = 0;
                Estancia estancia = sensor.getEstancia();
                String nombreEstancia = estancia.getNombre();
                if (sensoresConProblemasPorEstancia.containsKey(nombreEstancia))
                {
                    numProblemas = sensoresConProblemasPorEstancia.get(nombreEstancia);
                }

                numProblemas++;

                if (numProblemas > maxNumProblemas)
                {
                    maxNumProblemas = numProblemas;
                }
                sensoresConProblemasPorEstancia.put(nombreEstancia, numProblemas);

            }

            Set<Estancia> estanciasMasProblematicas = new HashSet<>();
            for (String nombreEstancia : sensoresConProblemasPorEstancia.keySet())
            {
                if (sensoresConProblemasPorEstancia.get(nombreEstancia) == maxNumProblemas)
                {
                    estanciasMasProblematicas.add(planta.getEstancias().get(nombreEstancia));
                }
            }

            salida.put(planta.getNumero(), estanciasMasProblematicas);

        }


        return salida;
    }

    @Override
    public String toString()
    {

        String salida = new String();
        boolean primeraCadena = true;

        salida += "{\n";
        if (this.id != null)
        {
            salida += "\"nombre\": \"" + this.id + "\",\n";
            primeraCadena = false;
        }
        if (this.plantas != null)
        {
            if (!primeraCadena)
            {
                salida += ",\n";
            }
            salida += "\"plantas\":\" [{";
            for (Iterator<Planta> iterator = this.plantas.values().iterator(); iterator.hasNext(); )
            {
                Planta plantaActual = iterator.next();
                salida += "\"<" + plantaActual.getNumero() + ">\"";
                if (iterator.hasNext())
                {
                    salida += ",";
                }
                if (!iterator.hasNext())
                {
                    salida += "}";
                }
            }
            primeraCadena = false;
        }
        return salida;
    }

}
