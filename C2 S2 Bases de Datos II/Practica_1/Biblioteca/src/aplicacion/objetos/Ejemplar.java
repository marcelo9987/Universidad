/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package aplicacion.objetos;

import aplicacion.objetos.Libro;

import java.util.Objects;

/**
 * @author basesdatos
 */
public class Ejemplar {

    private Integer numEjemplar;
    private String localizador;
    private String anoCompra;
    private Libro libro;

//    private java.util.List<Prestamo> prestamos;
    private Prestamo prestamoActivo;


    public Ejemplar(Libro libro, Integer numEjemplar, String localizador, String anoCompra, Prestamo prestamoActivo) {
        this.numEjemplar = numEjemplar;
        this.anoCompra = anoCompra;
        this.localizador = localizador;
        this.libro = libro;

//        prestamos = new java.util.ArrayList<Prestamo>();
        this.prestamoActivo = prestamoActivo;
    }

    public Integer getNumEjemplar() {
        return this.numEjemplar;
    }

    public String getAnoCompra() {
        return this.anoCompra;
    }

    public String getLocalizador() {
        return this.localizador;
    }

    public Libro getLibro() {
        return this.libro;
    }

    public void setLibro(Libro l) {
        libro = l;
    }

    public void setLocalizador(String l) {
        localizador = l;
    }

    public void setAnoCompra(String a) {
        anoCompra = a;
    }

    public Prestamo getPrestamoActivo() {
        return prestamoActivo;
    }

    public void setPrestamoActivo(Prestamo prestamoActivo) {
        this.prestamoActivo = prestamoActivo;
    }
}
