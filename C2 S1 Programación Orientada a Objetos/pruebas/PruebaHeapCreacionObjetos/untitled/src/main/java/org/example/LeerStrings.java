package org.example;

import java.util.HashMap;

public class LeerStrings
{
   public HashMap <String,String> misStrings;

   LeerStrings()
   {
       misStrings=new HashMap<>();
       misStrings.put("ho","oh");

   }
    public void leerMisStrings()
    {
        for(String str:misStrings.values())
        {
            System.out.println(str);
        }
    }


    LeerStrings(HashMap<String,String> miHash)
    {
        this.misStrings=miHash;
    }

}
