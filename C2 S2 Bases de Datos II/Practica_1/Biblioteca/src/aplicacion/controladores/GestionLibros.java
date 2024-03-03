/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package aplicacion.controladores;

import aplicacion.objetos.Categoria;
import aplicacion.objetos.Ejemplar;
import aplicacion.objetos.Libro;
import aplicacion.objetos.Prestamo;
import gui.FachadaGui;
import baseDatos.FachadaBaseDatos;

import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;

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

    public List<Libro> obtenerLibros(Integer id, String titulo, String isbn, String autor) {
        return fbd.consultarCatalogo(id, titulo, isbn, autor);
    }

    public void visualizarLibro(Integer idLibro) {
        Libro l = fbd.consultarLibro(idLibro);
//        List<Ejemplar> ejemplares  = fbd.consultarEjemplaresLibro(idLibro);
        List<String> restoCategorias = fbd.obtenerRestoCategorias(idLibro);
//        List<Prestamo> prestamos  = fbd.consultarTodosLosPrestamosParaLibro(idLibro);

        Map<Integer, Prestamo> prestamosActivos = new HashMap<>();
        for (Ejemplar ejemplarActual : l.getEjemplares()) {
            prestamosActivos.put(ejemplarActual.getNumEjemplar(), fbd.consultarPrestamoActivoParaEjemplar(ejemplarActual.getLibro().getIdLibro(), ejemplarActual.getNumEjemplar()));
        }

        fgui.visualizaLibro(l, prestamosActivos, restoCategorias);
    }

    public void nuevoLibro() {
        List<String> restoCategorias = new ArrayList<>();

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

    public void actualizarCategoriasLibro(Integer idLibro, List<String> categorias) {
        fbd.modificarCategoriasLibro(idLibro, categorias);
    }

    public void actualizarEjemplaresLibro(Integer idLibro, List<Ejemplar> ejemplares, List<Integer> borrar) {

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

//        Libro libro = fbd.consultarLibro(idLibro);
////        return fbd.consultarEjemplaresLibro(idLibro);
//        return libro.getEjemplares();
    }

    public boolean tienePrestamos(Integer idLibro) {
        return fbd.tienePrestamos(idLibro);
    }

    public Prestamo consultarPrestamoActivoParaEjemplar(Integer idLibro, Integer numEjemplar) {
        return fbd.consultarPrestamoActivoParaEjemplar(idLibro, numEjemplar);
    }

    public Libro consultarLibro(Integer idLibro) {
        return fbd.consultarLibro(idLibro);
    }
}
