package aplicacion.objetos;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 * @author basesdatos
 */
public class Categoria {

    private final String nombre;
    private final String descripcion;

    public Categoria(String nombre, String descripcion) {
        this.nombre = nombre;
        this.descripcion = descripcion;
    }

    public String getNombre() {

        return this.nombre;
    }

    public String getDescripcion() {

        return this.descripcion;
    }
}

