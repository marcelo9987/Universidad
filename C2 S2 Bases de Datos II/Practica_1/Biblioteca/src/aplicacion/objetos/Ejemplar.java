/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package aplicacion.objetos;


/**
 * @author basesdatos
 * @author Marcelo F.M.
 * @version 2.0
 */
public class Ejemplar {

    private final Integer numEjemplar;
    private String localizador;
    private String anoCompra;
    private Libro libro;

    private Prestamo prestamoActivo;


    public Ejemplar(Libro libro, Integer numEjemplar, String localizador, String anoCompra, Prestamo prestamoActivo) {
        this.numEjemplar = numEjemplar;
        this.anoCompra = anoCompra;
        this.localizador = localizador;
        this.libro = libro;
        this.prestamoActivo = prestamoActivo == null ? new Prestamo(/*libro, numEjemplar,*/ null, null, null) : prestamoActivo;

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

    public void setLibro(Libro libro) {
        this.libro = libro;
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

}
