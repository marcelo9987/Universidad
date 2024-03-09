package aplicacion.objetos;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


import aplicacion.enums.TipoUsuario;

/**
 * @author basesdatos
 */
public class Usuario {
    private final String idUsuario;
    private final String clave;
    private final String nombre;
    private final String direccion;
    private final String email;
    private final TipoUsuario tipo;
//    private Integer numPrestamosVencidos;

    public Usuario(String idUsuario, String clave, String nombre, String direccion, String email, TipoUsuario tipo) {
        this.idUsuario = idUsuario;
        this.clave = clave;
        this.nombre = nombre;
        this.direccion = direccion;
        this.email = email;
        this.tipo = tipo;
//        this.numPrestamosVencidos = numPrestamosVencidos;
    }

    public String getIdUsuario() {

        return this.idUsuario;
    }

    public String getClave() {

        return this.clave;
    }

    public String getNombre() {

        return this.nombre;
    }

    public String getDireccion() {

        return this.direccion;
    }

    public String getEmail() {

        return this.email;
    }

    public TipoUsuario getTipoUsuario() {

        return this.tipo;
    }

}
