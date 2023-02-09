package com.marcelo.congreso;

public class Main
{
	public static void main(String[] args)
	{
		Congreso test,test1;
		try
		{
			test = new Congreso("Hola", null);
		}catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		System.out.println("hola");
	}
}
