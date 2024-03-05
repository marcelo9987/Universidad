/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package aplicacion;

import aplicacion.controladores.GestionLibros;
import aplicacion.controladores.GestionPrestamos;
import aplicacion.controladores.GestionUsuarios;
import aplicacion.objetos.*;
import baseDatos.FachadaBaseDatos;

import java.util.List;


/**
 * @author basesdatos
 */
public class FachadaAplicacion {
    gui.FachadaGui fgui; // Interfaz gráfica de usuario
    baseDatos.FachadaBaseDatos fbd; // Acceso a la base de datos
    GestionLibros cl; // Controlador de la lógica de negocio de los libros
    GestionUsuarios cu; // Controlador de la lógica de negocio de los usuarios
    GestionPrestamos cp;


    public FachadaAplicacion() {
        fgui = new gui.FachadaGui(this);
        fbd = new baseDatos.FachadaBaseDatos(this);
        cl = new GestionLibros(fgui, fbd);
        cu = new GestionUsuarios(fgui, fbd);
        cp = new GestionPrestamos(fbd, fgui);
    }

    public static void main(String args[]) {
        FachadaAplicacion fa;

        fa = new FachadaAplicacion();
        fa.iniciaInterfazUsuario();
    }

    public void iniciaInterfazUsuario() {
        fgui.iniciaVista();
    }

    public void muestraExcepcion(String e) {
        fgui.muestraExcepcion(e);
    }

    public List<Libro> obtenerLibros(Integer id, String titulo, String isbn, String autor) {
        return cl.obtenerLibros(id, titulo, isbn, autor);
    }

    ;

    /**
     * @param id     Identificador del usuario
     * @param nombre Nombre del usuario
     * @return Lista de usuarios que cumplen con los criterios de búsqueda
     */
    public List<Usuario> obtenerUsuarios(String id, String nombre) {
        return cu.consultarUsuarios(id, nombre);
    }

    public Integer obtenerNumPrestamosVencidosPorUsuario(String idUsuario) {
        return cu.consultarNumPrestamosVencidosPorUsuario(idUsuario);
    }

    public List<Categoria> obtenerCategorias() {
        return fbd.consultarCategorias();
    }

    public void visualizarLibro(Integer idLibro) {
        cl.visualizarLibro(idLibro);
    }

    public void nuevoLibro() {
        cl.nuevoLibro();
    }

    public void lanzarGestionUsuarios() {
        fgui.gestionUsuarios();
    }

    public void lanzarGestionCategorias() {
        fgui.gestionCategorias();
    }

    public void lanzarGestionPrestamos(Ejemplar ejemplarAprestar) {
        fgui.gestionPrestamos(ejemplarAprestar);
    }

    public Integer actualizarLibro(Libro l) {
        return cl.actualizarLibro(l);
    }

    public void borrarLibro(Integer idLibro) {
        cl.borrarLibro(idLibro);
    }

    public void actualizarCategoriasLibro(Integer idLibro, List<String> categorias) {
        cl.actualizarCategoriasLibro(idLibro, categorias);
    }

    public void actualizarEjemplaresLibro(Integer idLibro, List<Ejemplar> ejemplares, List<Integer> borrar) {
         /*return*/cl.actualizarEjemplaresLibro(idLibro, ejemplares, borrar);
    }


    public Boolean comprobarAutentificacion(String idUsuario, String clave) {
        return cu.comprobarAutentificacion(idUsuario, clave);
    }

    public void insertarUsuario(Usuario usuario) {
        cu.insertarUsuario(usuario);
    }

    public void actualizarUsuario(Usuario usuarioAguardar) {
        cu.actualizarUsuario(usuarioAguardar);
    }

    public void borrarUsuario(String text) {
        cu.borrarUsuario(text);
    }


    public void insertarCategoria(Categoria c) {
        fbd.insertarCategoria(c);
    }

    public void borrarCategoria(Categoria c) {
        fbd.borrarCategoria(c);
    }

    public boolean tienePrestamos(Integer idLibro) {
        return cl.tienePrestamos(idLibro);
    }

//    public FachadaBaseDatos getFachadaBaseDeDatos() {
//        return fbd;
//    }

    public Prestamo consultarPrestamoActivoParaEjemplar(Integer idLibro, Integer numEjemplar) {
        return cl.consultarPrestamoActivoParaEjemplar(idLibro, numEjemplar);
    }

    public Libro consultarLibro(Integer idLibro) {
        return cl.consultarLibro(idLibro);
    }


/*

public void actualizarUsuario(Usuario u)
{
    cu.ac
}
*/

    public void realizarPrestamo(String usuarioSolicitante, Integer idLibro, Integer numEjemplar) {
        cp.realizarPrestamo(usuarioSolicitante, idLibro, numEjemplar);
        
    }


    public void devolverEjemplar(int idLibro, int numEjemplar) {
        cp.devolverEjemplar(idLibro,numEjemplar);
    }
}
