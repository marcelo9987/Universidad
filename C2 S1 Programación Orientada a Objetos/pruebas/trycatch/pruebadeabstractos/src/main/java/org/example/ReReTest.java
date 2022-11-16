package org.example;

public class ReReTest extends ReTest
{
    public void quienSoy()
    {
        System.out.println("soy ReReTest");;
    }
    @Override
    void printMessage(String message)
    {
        System.out.println("nope");
    }
}
