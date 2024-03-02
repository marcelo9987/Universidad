/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package aplicacion.controladores;

import aplicacion.objetos.Categoria;
import aplicacion.objetos.Ejemplar;
import aplicacion.objetos.Libro;
import gui.FachadaGui;
import baseDatos.FachadaBaseDatos;

/**
 * @author basesdatos
 */
public class GestionLibros {
    FachadaGui fgui; // Fachada del GUI
    FachadaBaseDatos fbd; // Fachada de la Base de Datos

    public GestionLibros(FachadaGui fgui, FachadaBaseDatos fbd) {
        this.fgui = fgui;
        this.fbd = fbd;
    }

    public java.util.List<Libro> obtenerLibros(Integer id, String titulo, String isbn, String autor) {
        return fbd.consultarCatalogo(id, titulo, isbn, autor);
    }

    public void visualizarLibro(Integer idLibro) {
        Libro l = fbd.consultarLibro(idLibro);
//        java.util.List<Ejemplar> ejemplares  = fbd.consultarEjemplaresLibro(idLibro);
        java.util.List<String> restoCategorias = fbd.obtenerRestoCategorias(idLibro);

        fgui.visualizaLibro(l, restoCategorias, prestamos);
    }

    public void nuevoLibro() {
        java.util.List<String> restoCategorias = new java.util.ArrayList<String>();

        for (Categoria c : fbd.consultarCategorias()) {
            restoCategorias.add(c.getNombre());
        }

        fgui.nuevoLibro(restoCategorias);
    }

    public Integer actualizarLibro(Libro l) {

        Integer idLibro;

        if (l.getIdLibro() == null) {
            idLibro = fbd.insertarLibro(l);
        }
        else {
            fbd.modificarLibro(l);
            idLibro = l.getIdLibro();
        }

        return idLibro;
    }

    public void borrarLibro(Integer idLibro) {
        if (fbd.tieneEjemplares(idLibro)) {
            fgui.muestraExcepcion("[Aviso] Borrar libro: El libro tiene ejemplares asociados. No se borrará");
            return;
        }
        fbd.borrarLibro(idLibro);
    }

    public void actualizarCategoriasLibro(Integer idLibro, java.util.List<String> categorias) {
        fbd.modificarCategoriasLibro(idLibro, categorias);
    }

    public java.util.List<Ejemplar> actualizarEjemplaresLibro(Integer idLibro, java.util.List<Ejemplar> ejemplares, java.util.List<Integer> borrar) {

        for (Ejemplar e : ejemplares) {
            if (e.getNumEjemplar() == null) {
                fbd.insertarEjemplarLibro(idLibro, e);
            }
            else {
                if (fbd.tienePrestamoEnActivoEjemplar(idLibro, e.getNumEjemplar())) {
                    fgui.muestraExcepcion("[Aviso] Modificar ejemplar: El ejemplar tiene un préstamo asociado. No se modificará");
                    continue;
                }
                fbd.modificarEjemplarLibro(idLibro, e);
            }
        }

        fbd.borrarEjemplaresLibro(idLibro, borrar);

        return fbd.consultarEjemplaresLibro(idLibro);
    }

    public boolean tienePrestamos(Integer idLibro) {
        return fbd.tienePrestamos(idLibro);
    }
}
