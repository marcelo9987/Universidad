package com.marcelo.congreso;

import java.util.HashMap;


public class Congreso
{
	private String nombre;
	private String localizacion;
	private float presupuesto;
	//private HashMap<String,Ponente> ponentes;
	private int maximo_ponentes;
	

	public Congreso(String nombre,String localizacion) throws Exception
	{
		if(nombre==null)
		{
			throw new Exception("El nombre es nulo");
		}
		this.nombre = nombre;
		if(localizacion == null)
		{
			throw new Exception("La localización es nula");
		}
		this.localizacion = localizacion;
	}
	
	
}
