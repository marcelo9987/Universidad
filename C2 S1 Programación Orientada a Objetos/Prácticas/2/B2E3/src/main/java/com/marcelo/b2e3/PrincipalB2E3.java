package com.marcelo.b2e3;

import java.util.ArrayList;
import java.util.Map;
import java.util.Set;

public class PrincipalB2E3
{
    public static void main(String[] args)
    {
        System.out.println("a:");//BORRAME
        Sensor sensor1, sensor2, sensor3, sensor4, sensor5, sensor6, sensor7, sensor8, sensor9;
        Sensor sensor10, sensor11, sensor12, sensor13, sensor14, sensor15, sensor16, sensor17, sensor18;
        Sensor sensor19, sensor20, sensor21, sensor22, sensor23, sensor24, sensor25;
        Sensor sensor26, sensor27, sensor28, sensor29, sensor30, sensor31;

        {
            float[] rango_in = {-5, 35};
            sensor1 = new Sensor("100", "temperatura", rango_in, 54.4f);
        }

        {
            float[] rango_in = {-5, 40};
            sensor2 = new Sensor("101", "temperatura", rango_in, 48.5f);
        }

        {
            float[] rango_in = {-5, 40};
            sensor3 = new Sensor("102", "temperatura", rango_in, 80);
        }

        {
            float[] rango_in = {-5, 40};
            sensor4 = new Sensor("103", "temperatura", rango_in, 45);
        }

        {
            float[] rango_in = {-5, 40};
            sensor5 = new Sensor("104", "temperatura", rango_in, 67);
        }

        {
            float[] rango_in = {-5, 40};
            sensor6 = new Sensor("105", "temperatura", rango_in, 86);
        }

        {
            float[] rango_in = {-10, 50};
            sensor7 = new Sensor("106", "temperatura", rango_in, 34);
        }

        {
            float[] rango_in = {-10, 50};
            sensor8 = new Sensor("107", "temperatura", rango_in, 35);
        }

        {
            float[] rango_in = {-10, 50};
            sensor9 = new Sensor("108", "temperatura", rango_in, 78);
        }


        {
            float[] rango_in = {0, 118};
            sensor10 = new Sensor("200", "sonido", rango_in, 67.6f);
        }
        {
            float[] rango_in = {0, 118};
            sensor11 = new Sensor("201", "sonido", rango_in, 56);
        }
        {
            float[] rango_in = {0, 118};
            sensor12 = new Sensor("202", "sonido", rango_in, 57);
        }
        {
            float[] rango_in = {0, 130};
            sensor13 = new Sensor("203", "sonido", rango_in, 57);
        }
        {
            float[] rango_in = {0, 150};
            sensor14 = new Sensor("204", "sonido", rango_in, 60);
        }
        {
            float[] rango_in = {0, 120};
            sensor15 = new Sensor("205", "sonido", rango_in, 70);
        }
        {
            float[] rango_in = {0, 120};
            sensor16 = new Sensor("206", "sonido", rango_in, 70);
        }
        {
            float[] rango_in = {0, 120};
            sensor17 = new Sensor("207", "sonido", rango_in, 70);
        }
        {
            float[] rango_in = {0, 120};
            sensor18 = new Sensor("208", "sonido", rango_in, 70);
        }


        {
            float[] rango_in = {0, 100};
            sensor19 = new Sensor("300", "humedad", rango_in, 44);
        }
        {
            float[] rango_in = {0, 100};
            sensor20 = new Sensor("301", "humedad", rango_in, 50);
        }
        {
            float[] rango_in = {0, 100};
            sensor21 = new Sensor("302", "humedad", rango_in, 45);
        }
        {
            float[] rango_in = {0, 100};
            sensor22 = new Sensor("303", "humedad", rango_in, 45);
        }
        {
            float[] rango_in = {0, 100};
            sensor23 = new Sensor("304", "humedad", rango_in, 45);
        }
        {
            float[] rango_in = {0, 80};
            sensor24 = new Sensor("305", "humedad", rango_in, 45);
        }
        {
            float[] rango_in = {0, 80};
            sensor25 = new Sensor("306", "humedad", rango_in, 60);
        }


        {
            float[] rango_in = {-10, 50};
            sensor26 = new Sensor("109", "temperatura", rango_in, 56);
        }
        {
            float[] rango_in = {-10, 50};
            sensor27 = new Sensor("110", "temperatura", rango_in, 45);
        }
        {
            float[] rango_in = {0, 120};
            sensor28 = new Sensor("209", "sonido", rango_in, 89);
        }
        {
            float[] rango_in = {0, 80};
            sensor29 = new Sensor("307", "humedad", rango_in, 34);
        }
        {
            float[] rango_in = {0, 80};
            sensor30 = new Sensor("308", "humedad", rango_in, 45);
        }
        {
            float[] rango_in = {0, 80};
            sensor31 = new Sensor("309", "humedad", rango_in, 34);
        }
        System.out.println("\n");//BORRAME

        System.out.println("b:");//BORRAME
        Planta planta_1, planta0, planta1, planta2;
        planta_1 = new Planta(-1, "oficinas");
        planta0 = new Planta(0, "administración");
        planta1 = new Planta(1, "oficinas");
        planta2 = new Planta(2, "viviendas libres");
        System.out.println("\n");//BORRAME

        System.out.println("c:");//BORRAME
        {
            System.out.println(planta_1);
            System.out.println(planta0);
            System.out.println(planta1);
            System.out.println(planta2);

        }
        System.out.println("\n");//BORRAME


        System.out.println("d:");//BORRAME



        Estancia estancia1 = new Estancia("-100", planta_1);
        Estancia estancia2 = new Estancia("-101", planta_1);
        Estancia estancia3 = new Estancia("-102", planta_1);
        Estancia estancia4 = new Estancia("000", planta0);
        Estancia estancia5 = new Estancia("001", planta0);
        Estancia estancia6 = new Estancia("002", planta0);
        Estancia estancia7 = new Estancia("003", planta0);
        Estancia estancia8 = new Estancia("100", planta1);
        Estancia estancia9 = new Estancia("101", planta1);
        Estancia estancia10 = new Estancia("102", planta1);
        Estancia estancia11 = new Estancia("200", planta2);
        Estancia estancia12 = new Estancia("201", planta2);
        Estancia estancia13 = new Estancia("202", planta2);


        if (estancia4.darAlta(sensor1))
        {
            System.out.println("Alta de sensor1 correcta");
        } else
        {
            System.out.println("Alta de sensor1 incorrecta");
        }

        if (estancia5.darAlta(sensor2))
        {
            System.out.println("Alta de sensor2 correcta");
        } else
        {
            System.out.println("Alta de sensor2 incorrecta");
        }

        if (estancia6.darAlta(sensor3))
        {
            System.out.println("Alta de sensor3 correcta");
        } else
        {
            System.out.println("Alta de sensor3 incorrecta");
        }

        if (estancia7.darAlta(sensor4))
        {
            System.out.println("Alta de sensor4 correcta");
        } else
        {
            System.out.println("Alta de sensor4 incorrecta");
        }

        if (estancia8.darAlta(sensor5))
        {
            System.out.println("Alta de sensor5 correcta");
        } else
        {
            System.out.println("Alta de sensor5 incorrecta");
        }

        if (estancia9.darAlta(sensor6))
        {
            System.out.println("Alta de sensor6 correcta");
        } else
        {
            System.out.println("Alta de sensor6 incorrecta");
        }

        if (estancia10.darAlta(sensor7))
        {
            System.out.println("Alta de sensor7 correcta");
        } else
        {
            System.out.println("Alta de sensor7 incorrecta");
        }

        if (estancia11.darAlta(sensor8))
        {
            System.out.println("Alta de sensor8 correcta");
        } else
        {
            System.out.println("Alta de sensor8 incorrecta");
        }

        if (estancia12.darAlta(sensor9))
        {
            System.out.println("Alta de sensor9 correcta");
        } else
        {
            System.out.println("Alta de sensor9 incorrecta");
        }

        if (estancia1.darAlta(sensor10))
        {
            System.out.println("Alta de sensor10 correcta");
        } else
        {
            System.out.println("Alta de sensor10 incorrecta");
        }

        if (estancia3.darAlta(sensor11))
        {
            System.out.println("Alta de sensor11 correcta");
        } else
        {
            System.out.println("Alta de sensor11 incorrecta");
        }

        if (estancia5.darAlta(sensor12))
        {
            System.out.println("Alta de sensor12 correcta");
        } else
        {
            System.out.println("Alta de sensor12 incorrecta");
        }

        if (estancia10.darAlta(sensor13))
        {
            System.out.println("Alta de sensor13 correcta");
        } else
        {
            System.out.println("Alta de sensor13 incorrecta");
        }

        if (estancia12.darAlta(sensor14))
        {
            System.out.println("Alta de sensor14 correcta");
        } else
        {
            System.out.println("Alta de sensor14 incorrecta");
        }

        if (estancia13.darAlta(sensor15))
        {
            System.out.println("Alta de sensor15 correcta");
        } else
        {
            System.out.println("Alta de sensor15 incorrecta");
        }

        if (estancia6.darAlta(sensor16))
        {
            System.out.println("Alta de sensor16 correcta");
        } else
        {
            System.out.println("Alta de sensor16 incorrecta");
        }

        if (estancia7.darAlta(sensor17))
        {
            System.out.println("Alta de sensor17 correcta");
        } else
        {
            System.out.println("Alta de sensor17 incorrecta");
        }

        System.out.println("\n");//BORRAME


        System.out.println("e:");//BORRAME
        {
            Estancia[] estancias = {estancia1, estancia2, estancia4, estancia5, estancia6, estancia7, estancia8, estancia9, estancia10, estancia11, estancia12, estancia13};
            for (Estancia estancia : estancias)
            {
                System.out.println(estancia);
            }
        }
        System.out.println("\n");//BORRAME


        System.out.println("f:");//BORRAME
        {
            ArrayList<Estancia> estancias_1 = new ArrayList<>();
            ArrayList<Estancia> estancias0 = new ArrayList<>();
            ArrayList<Estancia> estancias1 = new ArrayList<>();
            estancias_1.add(estancia1);
            estancias_1.add(estancia2);
            estancias_1.add(estancia3);
            estancias0.add(estancia4);
            estancias0.add(estancia5);
            estancias0.add(estancia6);
            estancias0.add(estancia7);
            estancias1.add(estancia8);
            estancias1.add(estancia9);
            estancias1.add(estancia10);


            if (planta_1.darAltaEstancia(estancias_1))
            {
                System.out.println("Alta estancias de la planta -1 correcta");
            } else
            {
                System.out.println("ERROR: Alta estancias de la planta -1 correcta");
            }
            if (planta0.darAltaEstancia(estancias0))
            {
                System.out.println("Alta estancias de la planta 0 correcta");
            } else
            {
                System.out.println("ERROR: Alta estancias de la planta 0 correcta");
            }

            if (planta1.darAltaEstancia(estancias1))
            {
                System.out.println("Alta estancias de la planta 1 correcta");
            } else
            {
                System.out.println("ERROR: Alta estancias de la planta 1 correcta");
            }


        }

        System.out.println("\n");//BORRAME

        System.out.println("g: ");//BORRAME
        System.out.println(planta_1);
        System.out.println(planta0);
        System.out.println(planta1);
        System.out.println(planta2);
        System.out.println("\n");//BORRAME

        System.out.println("h:"); //BORRAME
        {
            ArrayList<Sensor> sensores18y23 = new ArrayList<>();
            sensores18y23.add(sensor18);
            sensores18y23.add(sensor23);
            planta1.darAltaSensor(estancia8.getNombre(), sensores18y23);
        }
        System.out.println("\n");//BORRAME

        System.out.println("i:"); //BORRAME //todo: revisa desde aquí
        planta1.darAltaSensor(estancia9.getNombre(), sensor24);

        System.out.println("\n");//BORRAME

        System.out.println("j:"); //BORRAME
        System.out.println(planta1);
        System.out.println("\n");//BORRAME

        System.out.println("k:"); //BORRAME
        planta_1.darAltaSensor(estancia1.getNombre(), sensor19);
        planta_1.darAltaSensor(estancia2.getNombre(), sensor20);
        planta_1.darAltaSensor(estancia3.getNombre(), sensor21);
        System.out.println("\n");//BORRAME

        System.out.println("l:"); //BORRAME
        System.out.println(planta_1);
        System.out.println("\n");//BORRAME

        System.out.println("m:"); //BORRAME
        planta2.darAltaEstancia(estancia11);
        planta2.darAltaEstancia(estancia12);
        planta2.darAltaEstancia(estancia13);
        System.out.println("\n");//BORRAME

        System.out.println("n:"); //BORRAME
        planta2.darAltaSensor(estancia11.getNombre(), sensor25);
        System.out.println("\n");//BORRAME

        System.out.println("o:"); //BORRAME
        System.out.println(planta2);
        System.out.println("\n");//BORRAME

        System.out.println("p:"); //BORRAME
        planta0.darAltaSensor(estancia4.getNombre(), sensor22);
        System.out.println("\n");//BORRAME

        System.out.println("q:"); //BORRAME
        System.out.println(planta0);
        System.out.println("\n");//BORRAME

        System.out.println("r:"); //BORRAME
        Edificio edificio1;

        {
            ArrayList<Planta> plantasEdificio1 = new ArrayList<>();
            plantasEdificio1.add(planta_1);
            plantasEdificio1.add(planta1);
            plantasEdificio1.add(planta2);
            edificio1 = new Edificio("edificio1", new int[]{-1, 2}, plantasEdificio1);
        }

        System.out.println("\n");//BORRAME


        System.out.println("s:"); //BORRAME
        System.out.println("plantas no asignadas:");
        for (int numPlanta : edificio1.plantasNoAlta())
        {
            System.out.println(numPlanta);
        }

        System.out.println("\n");//BORRAME


        System.out.println("t:"); //BORRAME
        System.out.println(planta2);
        System.out.println("\n");//BORRAME


        System.out.println("u:"); //BORRAME
        planta2.darBajaSensor(sensor8.getId(), sensor26);
        System.out.println("\n");//BORRAME


        System.out.println("v:"); //BORRAME
        System.out.println(planta2);
        System.out.println("\n");//BORRAME


        System.out.println("w:"); //BORRAME
        planta1.darBajaSensor(sensor6.getId(), sensor27);
        System.out.println("\n");//BORRAME


        System.out.println("x:"); //BORRAME
        System.out.println(planta1);
        System.out.println("\n");//BORRAME


        System.out.println("y:"); //BORRAME
        planta_1.darBajaSensor(sensor10.getId(), sensor28);
        System.out.println("\n");//BORRAME


        System.out.println("z:"); //BORRAME
        System.out.println(planta_1);
        System.out.println("\n");//BORRAME


        System.out.println("aa:"); //BORRAME
        planta0.darBajaSensor(sensor22.getId(), sensor29);
        System.out.println("\n");//BORRAME


        System.out.println("bb:"); //BORRAME
        planta0.darBajaSensor(sensor29.getId(), sensor30);
        System.out.println("\n");//BORRAME


        System.out.println("cc:"); //BORRAME
        planta0.darBajaSensor(sensor30.getId(), sensor31);
        System.out.println("\n");//BORRAME


        System.out.println("dd:"); //BORRAME
        System.out.println(planta0);
        System.out.println("\n");//BORRAME


        System.out.println("ee:"); //BORRAME
        System.out.println(planta0.tipoSensoresMasDefectuosos());
        System.out.println("\n");//BORRAME


        System.out.println("ff:"); //BORRAME
        System.out.println(planta2.sensoresTipo("humedad"));
        System.out.println("\n");//BORRAME


        System.out.println("gg:"); //BORRAME
        System.out.println(planta1.sensoresTipo("sonido"));
        System.out.println("\n");//BORRAME


        System.out.println("hh:"); //BORRAME
        edificio1.darAltaPlanta(planta0);
        System.out.println("\n");//BORRAME


        System.out.println("ii:"); //BORRAME
        System.out.println("plantas no asignadas:");
        for (int numPlanta : edificio1.plantasNoAlta())
        {
            System.out.println(numPlanta);
        }
        System.out.println("\n");//BORRAME


        System.out.println("jj:"); //BORRAME
        Map<Integer, Set<Estancia>> estanciasMasProblemas = edificio1.plantasMasProblemas();
        for (int numPlanta : estanciasMasProblemas.keySet())
        {
            System.out.println("planta " + numPlanta + ":");
            for(Estancia estancia:estanciasMasProblemas.get(numPlanta))
            {
                System.out.println(estancia.getNombre());
            }
        }
        System.out.println("\n");//BORRAME


        System.out.println("kk:"); //BORRAME
        System.out.println(edificio1.plantasMasCaras());
        System.out.println("\n");//BORRAME


    }

}

