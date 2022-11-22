package org.example;

import java.util.HashMap;

public class Main
{


    public static void main(String[] args)
    {

        LeerStrings test = new LeerStrings();
        HashMap<String,String> viejoArr = test.misStrings;
        meterStr(test,"w");

        test.leerMisStrings();
        sout(viejoArr.e)
    }

    static void meterStr(LeerStrings entrada, String str)
    {
        HashMap<String,String> i = new HashMap<>();
        i.put("Hola","holis");
        i.put("Chao","Chau");
        entrada.misStrings = i;
    }

}

