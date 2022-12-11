package org.example;

import java.util.HashSet;
import java.util.Set;
import java.util.regex.*;

import static java.lang.Thread.sleep;

public class Main
{
    public static void main(String[] args) throws InterruptedException
    {
       final String text    =
                "This is the text to be searched " +
                        "for occurrences of the http:// pattern." +
                        "http://www.google.es. "+
                        "http://www.test.net " +
                        "https://www.hola.net";

        Pattern patron = Pattern.compile("https?://\\S*.(\\.com|\\.net|\\.es)");
        Matcher ocurrencias = patron.matcher(text);
//        boolean matches = Pattern.matches(patron, text);
        Set<String> out = new HashSet(2);
        while(ocurrencias.find())
        {
            String n = ocurrencias.group();
            out.add(n);
        }
        for(String cadena: out)
        {
            System.out.println("Ocurrencia Actual: "+cadena+"\n");
        }

    }
}