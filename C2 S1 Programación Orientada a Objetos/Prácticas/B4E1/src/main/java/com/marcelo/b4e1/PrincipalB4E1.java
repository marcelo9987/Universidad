package com.marcelo.b4e1;

import com.sun.xml.internal.ws.api.model.wsdl.WSDLOutput;

import java.util.ArrayList;
import java.util.Arrays;

public class PrincipalB4E1
{
    public static void main(String[] args)
    {
        System.out.println("a:");
        Actor actor1,actor2,actor3,actor4;
    
        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Steven Spielberg");
            deseos.add("Martin Scorsese");
            actor1 = new Actor("Cameron Diaz", deseos, 20);
        }
    
        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Steven Spielberg");
            deseos.add("Martin Scorsese");
            actor2 = new Actor("Ben Stiller", deseos, 15);
        }
    
        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Christofer Nolan");
            deseos.add("Woody Alen");
            deseos.add("Martin Scorsese");
            actor3 = new Actor("Matthew McConaughey", deseos, 25);
        }
    
        {
            ArrayList<String> deseos = new ArrayList<>();
            deseos.add("Christopher Nolan");
            deseos.add("Woody Alen");
            deseos.add("Martin Scorsese");
            actor4 = new Actor("Anne Hathaway", deseos, 30);
        }
    
    
        System.out.println("b:");
        
        {
            Actor[] actores1a4={actor1,actor2,actor3,actor4};
            for(Actor actor:actores1a4)
            {
                System.out.println(actor);
            }
        }
        
        System.out.println("c: ");
        
    }
}