/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */

package com.marcelo.b2e1;

import java.util.ArrayList;

/**
 * @author Marcelo Fort Muñoz
 */
public class PrincipalB2E1
{
//    public static final char MODO_RANGO = 'r';
//    public static final char MODO_DIRECTO = 'a';

    public static void main(String[] args)
    {
        System.out.println("a: ");//BORRAME
        float[] in_rango = new float[2];
        in_rango[0] = -5;
        in_rango[1] = 35;
        Sensor sensor1 = new Sensor("100", "temperatura", in_rango, 54.4f);

        in_rango[0] = -5;
        in_rango[1] = 40;
        Sensor sensor2 = new Sensor("101", "temperatura", in_rango, 48.5f);

        in_rango[0] = 0;
        in_rango[1] = 120;
        Sensor sensor3 = new Sensor("200", "sonido", in_rango, 30.5f);

        in_rango[0] = 0;
        in_rango[1] = 110;
        Sensor sensor4 = new Sensor("201", "sonido", in_rango, 28.3f);


        System.out.println("\n");//BORRAME

        System.out.println("b:");//BORRAME
        imprimirSensores(sensor1, sensor2, sensor3, sensor4);//, MODO_RANGO);


        System.out.println("c:");//BORRAME
        Estancia estancia1 = new Estancia("Aula1", 2);
        System.out.println("\n");//BORRAME


        System.out.println("d:");//BORRAME

        {
            boolean ok = estancia1.darAlta(sensor1);
            if (!ok)
            {
                System.out.println("Alta de sensor1 incorrecta");
            } else
            {
                System.out.println("Alta de sensor1 realizada correctamente");
            }

            ok = estancia1.darAlta(sensor2);
            if (!ok)
            {
                System.out.println("Alta de sensor2 incorrecta");
            } else
            {
                System.out.println("Alta de sensor2 realizada correctamente");
            }

            ok = estancia1.darAlta(sensor3);
            if (!ok)
            {
                System.out.println("Alta de sensor3 incorrecta");
            } else
            {
                System.out.println("Alta de sensor3 realizada correctamente");
            }

            ok = estancia1.darAlta(sensor4);
            if (!ok)
            {
                System.out.println("Alta de sensor4 incorrecta");
            } else
            {
                System.out.println("Alta de sensor4 realizada correctamente");
            }
        }

        System.out.println("\n");//BORRAME


        System.out.println("e: ");//BORRAME
        {
            float datos_a_entrar1[] = {23.4f, 23.4f, 23.5f, 24.1f, 23.2f, -23.5f, 24.6f, -23.8f, 23.9f, 24.1f, 24.3f, 25.4f};
            float datos_a_entrar2[] = {22.1f, -22.1f, 22.5f, 22.4f, 22.9f, 21.2f, 21.5f, 21.1f, 20.9f, -23.1f, 22.8f, 23.2f};
            float datos_a_entrar3[] = {21.4f, -21.3f, 21.2f, -21.2f, 21.2f, 21.5f, 22.3f, 21.8f, 22.1f, 21.7f, -21.9f, 22.5f};
            float datos_a_entrar4[] = {10.1f, 10.1f, -5.2f, 30.6f, 37.8f, 45.8f, 50.2f, 52.1f, 46.3f, -10.3f, 89.2f, 34.3f};


            introducirValoresEnMasa(datos_a_entrar1, sensor1.getId(), estancia1);
            introducirValoresEnMasa(datos_a_entrar2, sensor2.getId(), estancia1);
            introducirValoresEnMasa(datos_a_entrar3, sensor3.getId(), estancia1);
            introducirValoresEnMasa(datos_a_entrar4, sensor4.getId(), estancia1);
        }
        System.out.println("\n");//BORRAME


        System.out.println("f:");//BORRAME
        System.out.println(sensor1);
        System.out.println(sensor2);
        System.out.println(sensor3);
        System.out.println(sensor4);
        System.out.println("\n");//BORRAME


        System.out.println("g:");//BORRAME
        System.out.println(estancia1);
        System.out.println("\n");//BORRAME

        System.out.println("h: ");//BORRAME

        {
            boolean ok = false;
            in_rango[0] = 0f;
            in_rango[1] = 118f;
            ok = estancia1.darAlta("202", "sonido", in_rango, 28.4f);
            if (!ok)
            {
                System.out.println("Alta de sensor5 incorrecta");
            } else
            {
                System.out.println("Alta de sensor5 realizada correctamente");
            }

            in_rango[0] = 0f;
            in_rango[1] = 100f;
            ok = estancia1.darAlta("301", "humedad", in_rango, 34.3f);
            if (!ok)
            {
                System.out.println("Alta de sensor6 incorrecta");
            } else
            {
                System.out.println("Alta de sensor6 realizada correctamente");
            }

            in_rango[0] = 0f;
            in_rango[1] = 100f;
            ok = estancia1.darAlta("302", "humedad", in_rango, 42.5f);
            if (!ok)
            {
                System.out.println("Alta de sensor7 incorrecta");
            } else
            {
                System.out.println("Alta de sensor7 realizada correctamente");
            }
            System.out.println("\n");//BORRAME
        }


        System.out.println("i: ");//BORRAME

        {
            for (Sensor sensor : estancia1.getSensores())
            {
                switch (sensor.getId())
                {
                    case "202":
                    case "301":
                    case "302":
                        System.out.println("Sensor " + sensor.getId() + " Rango: [" + sensor.limiteInferior() + ", " + sensor.limiteSuperior() + "]");
                        break;
                    default:
                        break;

                }
            }
        }

        System.out.println("\n");//BORRAME

        System.out.println("j: ");//BORRAME

        {
            for (Sensor sensor : estancia1.getSensores())
            {
                switch (sensor.getId())
                {
                    case "202":
                    case "301":
                    case "302":
                        System.out.println(sensor);
                        break;
                    default:
                        break;

                }
            }
        }

        System.out.println("\n");//BORRAME

        System.out.println("k: ");//BORRAME
        System.out.println(estancia1);
        System.out.println("\n");//BORRAME


        System.out.println("l: ");//BORRAME
        {
            float[] datos_entrada_s5 = {5.1f, 5.2f, 3.5f, 25.5f, 25.5f, -29.3f, 35.1f, 35.4f, -35.1f, 40.1f, 49.8f, 34.5f};
            introducirValoresEnMasa(datos_entrada_s5, "202", estancia1);

            float[] datos_entrada_s6 = {31.0f, 31.2f, 31.4f, 32.1f, 32.4f, 32.0f, 32.4f, 33.4f, 33.0f, 32.8f, 32.9f, 32.5f};
            introducirValoresEnMasa(datos_entrada_s6, "301", estancia1);

            float[] datos_entrada_s7 = {-45.1f, -45.2f, -45.2f, -45.2f, 34.9f, 34.5f, 34.6f, 38.9f, 37.2f, -45.1f, 36.4f, 35.4f};
            introducirValoresEnMasa(datos_entrada_s7, "302", estancia1);
        }
        System.out.println("\n");//BORRAME


        System.out.println("m: ");//BORRAME
        System.out.println(estancia1);
        System.out.println("\n");


        System.out.println("n:");//BORRAME
        for (Sensor sensorActual : estancia1.sensoresTipo("temperatura"))
        {
            System.out.println(sensorActual);
        }
        System.out.println("\n");//BORRAME


        System.out.println("o:");//BORRAME
        for (Sensor sensorActual : estancia1.sensoresTipo("sonido"))
        {
            System.out.println(sensorActual);
        }
        System.out.println("\n");//BORRAME


        System.out.println("p:");//BORRAME
        {
            System.out.println("Sensor con el valor más alto:");
            Sensor[] maxHumedad = estancia1.sensorMaxValor("humedad");

            for (Sensor sensor : maxHumedad)
            {
                System.out.println(sensor);
            }
        }
        {
            System.out.println("Sensor con el valor más bajo:");
            Sensor[] minHumedad = estancia1.sensorMinValor("humedad");

            for (Sensor sensor : minHumedad)
            {
                System.out.println(sensor);
            }
        }
        System.out.println("\n");//BORRAME


        System.out.println("q: ");//BORRAME
        ArrayList<Float> valoresMaximos301 = estancia1.valoresSuperiores("301", 33.0f);
        for (Float aFloat : valoresMaximos301)
        {
            System.out.println(aFloat);
        }
        System.out.println("\n");//BORRAME


        System.out.println("r:");//BORRAME
        in_rango[0] = 0;
        in_rango[1] = 118;
        {
            boolean ok = estancia1.darAlta("202", "sonido", in_rango, 67.6f);
            if (!ok)
            {
                System.out.println("Alta de sensor8 incorrecta");
            } else
            {
                System.out.println("Alta de sensor8 realizada correctamente");
            }
        }
        System.out.println("\n");//BORRAME

        System.out.println("s:");//BORRAME
        System.out.println(estancia1);
        System.out.println("\n");//BORRAME
    }

    /**
     * @param sensor1 Primer Sensor a imprimir ANTIGUO:(Poner a null para que no sea impreso)
     * @param sensor2 Segundo Sensor a imprimir ANTIGUO:(ídem 1)
     * @param sensor3 Tercer Sensor a imprimir ANTIGUO:(ídem 1)
     * @param sensor4 Cuarto Sensor a imprimir ANTIGUO:(ídem 1)
     *                ANTIGUO: param op Tipo de operación
     *                Modos disponibles de funcionamiento:
     *                'r': imprime el rango de los sensores
     *                'a': imprime todos los datos de los sensores
     */
    private static void imprimirSensores(Sensor sensor1, Sensor sensor2, Sensor sensor3, Sensor sensor4)
    {
        //  if (op == MODO_RANGO)
        //  {
        //      if (sensor1 != null)
        //      {
        System.out.println("Sensor " + sensor1.getId() + " Rango: [" + sensor1.limiteInferior() + ", " + sensor1.limiteSuperior() + "]");
        //     }
        //     if (sensor2 != null)
        //     {
        System.out.println("Sensor " + sensor2.getId() + " Rango: [" + sensor2.limiteInferior() + ", " + sensor2.limiteSuperior() + "]");
        //     }
        //     if (sensor3 != null)
        //     {
        System.out.println("Sensor " + sensor3.getId() + " Rango: [" + sensor3.limiteInferior() + ", " + sensor3.limiteSuperior() + "]");
        //     }
        //     if (sensor4 != null)
        //     {
        System.out.println("Sensor " + sensor4.getId() + " Rango: [" + sensor4.limiteInferior() + ", " + sensor4.limiteSuperior() + "]");
        //    }
//        }
        /*
        if (op == MODO_DIRECTO)
        {
            if (sensor1 != null)
            {
                System.out.println(sensor1);
            }
            if (sensor2 != null)
            {
                System.out.println(sensor2);
            }
            if (sensor3 != null)
            {
                System.out.println(sensor3);
            }
            if (sensor4 != null)
            {
                System.out.println(sensor4);
            }
        }

         */
    }

    private static void introducirValoresEnMasa(float[] valores, String id, Estancia estancia)
    {
        if (valores == null || estancia == null || id == null)
        {
            System.out.println("Uno de los argumentos de la función (IntroducirValoresEnMasa es nulo, no se ha podido proceder)");
            return;
        }
        if (valores.length == 0)
        {
            System.out.println("Error en alguno de los parámetros");
            return;
        }
        System.out.println("\n* Introduciendo valores en el sensor id: " + id);
        for (float valor : valores)
        {
            boolean ok = estancia.nuevoDato(id, valor);
            if (ok)
            {
                System.out.println("El valor " + valor + " ha sido introducido con éxito");
            }
            if (!ok)
            {
                System.out.println("ERROR: El valor " + valor + " no ha sido introducido con éxito");
            }
        }
    }
}
