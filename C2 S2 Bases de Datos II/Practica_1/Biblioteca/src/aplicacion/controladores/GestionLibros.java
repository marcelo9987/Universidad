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

import java.util.List;
import java.util.ArrayList;

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
        Libro libro = fbd.consultarLibro(idLibro);
//        List<Ejemplar> ejemplares  = fbd.consultarEjemplaresLibro(idLibro);
        List<String> restoCategorias = fbd.obtenerRestoCategorias(idLibro);
//        List<Prestamo> prestamos  = fbd.consultarTodosLosPrestamosParaLibro(idLibro);

//        Map<Integer, Prestamo> estadoPrestamoEjemplares = new HashMap<>();
//        for (Ejemplar ejemplarActual : libro.getEjemplares()) {
//            estadoPrestamoEjemplares.put(ejemplarActual.getNumEjemplar(), fbd.consultarPrestamoActivoParaEjemplar(ejemplarActual.getLibro().getIdLibro(), ejemplarActual.getNumEjemplar()));
//        }

//        fgui.visualizaLibro(libro, estadoPrestamoEjemplares, restoCategorias);
        fgui.visualizaLibro(libro, restoCategorias);
    }

    public void nuevoLibro() {
        List<String> restoCategorias = new ArrayList<>();

        for (Categoria c : fbd.consultarCategorias()) {
            restoCategorias.add(c.getNombre());
        }

        fgui.nuevoLibro(restoCategorias);
    }

    public Integer actualizarLibro(Libro libro) {

        Integer idLibro;

        if (libro.getIdLibro() == null) {
            idLibro = fbd.insertarLibro(libro);
        }
        else {
            fbd.modificarLibro(libro);
            idLibro = libro.getIdLibro();
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

//    public Prestamo consultarPrestamoActivoParaEjemplar(Integer idLibro, Integer numEjemplar) {
//        return fbd.consultarPrestamoActivoParaEjemplar(idLibro, numEjemplar);
//    }

    public Libro consultarLibro(Integer idLibro) {
        return fbd.consultarLibro(idLibro);
    }
}
