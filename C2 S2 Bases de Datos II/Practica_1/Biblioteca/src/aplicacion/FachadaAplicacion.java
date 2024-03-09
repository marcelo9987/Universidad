/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package aplicacion;

import aplicacion.controladores.GestionLibros;
import aplicacion.controladores.GestionPrestamos;
import aplicacion.controladores.GestionUsuarios;
import aplicacion.objetos.*;

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

    /**
     * Inicia la interfaz de usuario
     */
    public void iniciaInterfazUsuario() {
        fgui.iniciaVista();
    }

    /**
     * Muestra una excepción
     *
     * @param e Excepción a mostrar
     */
    public void muestraExcepcion(String e) {
        fgui.muestraExcepcion(e);
    }

    /**
     * @param id     Identificador del libro
     * @param titulo Título del libro
     * @param isbn   ISBN del libro
     * @param autor  Autor del libro
     * @return Lista de libros que cumplen con los criterios de búsqueda
     */
    public List<Libro> obtenerLibros(Integer id, String titulo, String isbn, String autor) {
        return cl.obtenerLibros(id, titulo, isbn, autor);
    }



    /**
     * @param id     Identificador del usuario
     * @param nombre Nombre del usuario
     * @return Lista de usuarios que cumplen con los criterios de búsqueda
     */
    public List<Usuario> obtenerUsuarios(String id, String nombre) {
        return cu.consultarUsuarios(id, nombre);
    }

    /**
     * @param idUsuario Identificador del usuario
     * @return Número de préstamos vencidos por el usuario
     */
    public Integer obtenerNumPrestamosVencidosPorUsuario(String idUsuario) {
        return cu.consultarNumPrestamosVencidosPorUsuario(idUsuario);
    }

    /**
     * @return Lista de categorías
     */
    public List<Categoria> obtenerCategorias() {
        return fbd.consultarCategorias();
    }

    /**
     * Muestra una ventana con el libro seleccionado
     * @param idLibro Identificador del libro
     */
    public void visualizarLibro(Integer idLibro) {
        cl.visualizarLibro(idLibro);
    }

    /**
     * Muestra una ventana que permite añadir un nuevo libro
     */
    public void nuevoLibro() {
        cl.nuevoLibro();
    }

    /**
     * Muestra una ventana que permite gestionar los usuarios
     */
    public void lanzarGestionUsuarios() {
        fgui.gestionUsuarios();
    }

    /**
     * Muestra una ventana que permite gestionar las categorías
     */
    public void lanzarGestionCategorias() {
        fgui.gestionCategorias();
    }

    /**
     * Muestra una ventana que permite gestionar los préstamos de un ejemplar
     * @param ejemplarAprestar Ejemplar a prestar
     */
    public void lanzarGestionPrestamos(Ejemplar ejemplarAprestar) {
        fgui.gestionPrestamos(ejemplarAprestar);
    }

    /**
     * Actualiza un libro
     * @param libro Libro a actualizar
     * @return  Nuevo identificador del libro
     */
    public Integer actualizarLibro(Libro libro) {
        return cl.actualizarLibro(libro);
    }

    /**
     * Borra un libro
     * @param idLibro Identificador del libro
     */
    public void borrarLibro(Integer idLibro) {
        cl.borrarLibro(idLibro);
    }

    /**
     * Actualiza las categorías de un libro
     * @param idLibro    Identificador del libro
     * @param categorias Nuevas categorías del libro
     */
    public void actualizarCategoriasLibro(Integer idLibro, List<String> categorias) {
        cl.actualizarCategoriasLibro(idLibro, categorias);
    }

    /**
     * Actualiza los ejemplares de un libro
     * @param idLibro   Identificador del libro
     * @param ejemplares Nuevos ejemplares del libro
     * @param borrar   Ejemplares a borrar
     */
    public void actualizarEjemplaresLibro(Integer idLibro, List<Ejemplar> ejemplares, List<Integer> borrar) {
         /*return*/cl.actualizarEjemplaresLibro(idLibro, ejemplares, borrar);
    }

    /**
     *  Comprueba si un usuario está autentificado
     * @param idUsuario Identificador del usuario
     * @param clave Clave de autenticación del usuario
     * @return true si el usuario está autentificado, false en caso contrario
     */
    public Boolean comprobarAutentificacion(String idUsuario, String clave) {
        return cu.comprobarAutentificacion(idUsuario, clave);
    }

    /**
     * Inserta un usuario
     * @param usuario Usuario a insertar
     */
    public void insertarUsuario(Usuario usuario) {
        cu.insertarUsuario(usuario);
    }

    /**
     * Actualiza un usuario
     * @param usuarioAguardar Usuario con los datos actualizados
     */
    public void actualizarUsuario(Usuario usuarioAguardar) {
        cu.actualizarUsuario(usuarioAguardar);
    }

    /**
     * Borra un usuario
     * @param idUsuario Identificador del usuario
     */
    public void borrarUsuario(String idUsuario) {
        cu.borrarUsuario(idUsuario);
    }

    /**
     * Inserta una categoría
     * @param c Categoría a insertar
     */
    public void insertarCategoria(Categoria c) {
        fbd.insertarCategoria(c);
    }

    /**
     * Borra una categoría
     * @param c Categoría a borrar
     */
    public void borrarCategoria(Categoria c) {
        fbd.borrarCategoria(c);
    }

    /**
     * Comprueba si un libro tiene préstamos
     * @param idLibro Identificador del libro
     * @return true si el libro tiene préstamos, false en caso contrario
     */
    public boolean tienePrestamos(Integer idLibro) {
        return cl.tienePrestamos(idLibro);
    }

    /**
     * Busca (de haberlo) un préstamo activo para un ejemplar de un libro
     * @param idLibro Identificador del libro
     * @param numEjemplar Número del ejemplar
     * @return Préstamo activo para el ejemplar en el libro
     */
//    public Prestamo consultarPrestamoActivoParaEjemplar(Integer idLibro, Integer numEjemplar) {
//        return cl.consultarPrestamoActivoParaEjemplar(idLibro, numEjemplar);
//    }

    /**
     * Busca un libro
     * @param idLibro Identificador del libro
     * @return Libro consultado
     */
    public Libro consultarLibro(Integer idLibro) {
        return cl.consultarLibro(idLibro);
    }

    /**
     * Realiza un préstamo
     * @param usuarioSolicitante Usuario que solicita el préstamo
     * @param idLibro Identificador del libro
     * @param numEjemplar Número del ejemplar a prestar
     */
    public void realizarPrestamo(String usuarioSolicitante, Integer idLibro, Integer numEjemplar) {
        cp.realizarPrestamo(usuarioSolicitante, idLibro, numEjemplar);
        
    }

    /**
     * Devuelve un ejemplar
     * @param idLibro Identificador del libro
     * @param numEjemplar Número del ejemplar a devolver
     */
    public void devolverEjemplar(int idLibro, int numEjemplar) {
        cp.devolverEjemplar(idLibro,numEjemplar);
    }
}
