package baseDatos;

import aplicacion.enums.TipoUsuario;
import aplicacion.objetos.Categoria;
import aplicacion.objetos.Ejemplar;
import aplicacion.objetos.Libro;
import aplicacion.objetos.Usuario;
import baseDatos.dao.DAOCategorias;
import baseDatos.dao.DAOLibros;
import baseDatos.dao.DAOPrestamos;
import baseDatos.dao.DAOUsuarios;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.List;
import java.util.Properties;

/**
 * @author basesdatos
 * @author Marcelo F.M.
 * @version 2.0
 */
public class FachadaBaseDatos {
    private aplicacion.FachadaAplicacion fa;
    private java.sql.Connection conexion;
    private DAOLibros daoLibros;
    private DAOCategorias daoCategorias;
    private DAOUsuarios daoUsuarios;

    private DAOPrestamos daoPrestamos;

    public FachadaBaseDatos(aplicacion.FachadaAplicacion fa) {

        Properties configuracion = new Properties();
        this.fa = fa;
        FileInputStream arqConfiguracion;

        try {
            arqConfiguracion = new FileInputStream("baseDatos.properties");
            configuracion.load(arqConfiguracion);
            arqConfiguracion.close();

            Properties usuario = new Properties();


            String gestor = configuracion.getProperty("gestor");

            usuario.setProperty("user", configuracion.getProperty("usuario"));
            usuario.setProperty("password", configuracion.getProperty("clave"));
            this.conexion = java.sql.DriverManager.getConnection("jdbc:" + gestor + "://" +
                            configuracion.getProperty("servidor") + ":" +
                            configuracion.getProperty("puerto") + "/" +
                            configuracion.getProperty("baseDatos"),
                    usuario);

            daoLibros = new DAOLibros(conexion, fa);
            daoCategorias = new DAOCategorias(conexion, fa);
            daoUsuarios = new DAOUsuarios(conexion, fa);
            daoPrestamos = new DAOPrestamos(conexion, fa);


        } catch (FileNotFoundException f) {
            System.out.println(f.getMessage());
            fa.muestraExcepcion(f.getMessage());
        } catch (IOException i) {
            System.out.println(i.getMessage());
            fa.muestraExcepcion(i.getMessage());
        } catch (java.sql.SQLException e) {
            System.out.println(e.getMessage());
            fa.muestraExcepcion(e.getMessage());
        }


    }


    /**
     *  Busca ciertos libros que cumplen x criterios en la base de datos
     * @param id Identificador del libro
     * @param titulo Titulo del libro
     * @param isbn ISBN del libro
     * @param autor Autor del libro
     * @return Lista de libros que cumplen con los criterios de búsqueda
     */
    public List<Libro> consultarCatalogo(Integer id, String titulo, String isbn, String autor) {
        return daoLibros.consultarCatalogo(id, titulo, isbn, autor);
    }

    /**
     * Busca un libro en la base de datos
     * @param idLibro Identificador del libro a buscar
     * @return Libro que cumple con el identificador o null si no existe
     */
    public Libro consultarLibro(Integer idLibro) {
        return daoLibros.consultarLibro(idLibro);
    }


    /**
     * Busca las categorías que tiene un libro
     * @param idLibro Identificador del libro
     * @return Lista de categorías que tiene el libro
     */
    public List<String> obtenerRestoCategorias(Integer idLibro) {
        return daoLibros.obtenerRestoCategorias(idLibro);
    }

    /**
     * Inserta un libro en la base de datos
     * @param libro Libro a insertar
     * @return Identificador del libro insertado
     */
    public Integer insertarLibro(Libro libro) {
        return daoLibros.insertarLibro(libro);
    }

    /**
     * Borra un libro de la base de datos
     * @param idLibro Identificador del libro a borrar
     */
    public void borrarLibro(Integer idLibro) {
        daoLibros.borrarLibro(idLibro);
    }

    /**
     * Modifica un libro en la base de datos
     * @param libro Libro a modificar
     */
    public void modificarLibro(Libro libro) {
        daoLibros.modificarLibro(libro);
    }

    /**
     * Modifica las categorías de un libro
     * @param idLibro Identificador numérico del libro
     * @param categorias Lista de categorías a modificar
     */
    public void modificarCategoriasLibro(Integer idLibro, List<String> categorias) {
        daoLibros.modificarCategoriasLibro(idLibro, categorias);
    }

    /**
     * Inserta el ejemplar de un libro en la base de datos
     * @param idLibro Identificador del libro al que pertenece el ejemplar
     * @param ejemplar Ejemplar a insertar
     */
    public void insertarEjemplarLibro(Integer idLibro, Ejemplar ejemplar) {
        daoLibros.insertarEjemplarLibro(idLibro, ejemplar);
    }

    /**
     * Borra los ejemplares de un libro en la base de datos
     * @param idLibro Identificador del libro al que pertenecen los ejemplares
     * @param numsEjemplar Lista de números de ejemplares a borrar
     */
    public void borrarEjemplaresLibro(Integer idLibro, List<Integer> numsEjemplar) {
        daoLibros.borrarEjemplaresLibro(idLibro, numsEjemplar);
    }


    /**
     * Modifica un ejemplar de un libro en la base de datos
     * @param idLibro Identificador del libro al que pertenece el ejemplar
     * @param ejemplar Ejemplar a modificar
     */
    public void modificarEjemplarLibro(Integer idLibro, Ejemplar ejemplar) {
        daoLibros.modificarEjemplarLibro(idLibro, ejemplar);
    }


    /**
     * Modifica un usuario en la base de datos
     * @param Id Identificador del usuario
     * @param clave Nueva clave del usuario
     * @param tipo Nuevo tipo del usuario
     * @param nombre Nuevo nombre del usuario
     * @param email Nuevo email del usuario
     * @param direccion Nueva dirección del usuario
     */
    public void modificarUsuario(String Id, String clave, String tipo, String nombre, String email, String direccion) {
        daoUsuarios.editarUsuario(Id, clave, tipo.contentEquals("Administrador") ? TipoUsuario.Administrador : TipoUsuario.Normal, nombre, email, direccion);
    }


    /**
     * Valída un usuario en la base de datos
     * @param idUsuario Identificador del usuario
     * @param clave Clave del usuario
     * @return true si consigue autenticar al usuario, false si no lo consigue
     */
    public Usuario validarUsuario(String idUsuario, String clave) {
        return daoUsuarios.validarUsuario(idUsuario, clave);
    }


    /**
     * Consulta las categorías de la base de datos
     * @return Lista de categorías
     */
    public List<Categoria> consultarCategorias() {
        return daoCategorias.consultarCategorias();
    }

    /**
     * Consulta los usuarios de la base de datos
     * @param id     Identificador del usuario
     * @param nombre Nombre del usuario
     * @return Lista de usuarios que cumplen con los criterios de búsqueda
     */
    public List<Usuario> consultarUsuarios(String id, String nombre) {
        return daoUsuarios.consultarUsuarios(id, nombre);
    }

    /**
     * Inserta un usuario en la base de datos
     * @param usuario Identificador del usuario
     */
    public void insertarUsuario(Usuario usuario) {
        daoUsuarios.insertarUsuario(usuario);
    }


    /**
     * Actualiza un usuario en la base de datos
     * @param usuarioAguardar Usuario a actualizar
     */
    public void actualizarUsuario(Usuario usuarioAguardar) {
        daoUsuarios.actualizarUsuario(usuarioAguardar);
    }

    /**
     * Borra un usuario de la base de datos
     * @param idUsuario Identificador del usuario a borrar
     */
    public void borrarUsuario(String idUsuario) {
        daoUsuarios.borrarUsuario(idUsuario);
    }


    /**
     * Inserta una categoría en la base de datos
     * @param c Categoría a insertar
     */
    public void insertarCategoria(Categoria c) {
        daoCategorias.insertarCategoria(c);
    }


    /**
     * Borra una categoría de la base de datos
     * @param c Categoría a borrar
     */
    public void borrarCategoria(Categoria c) {
        daoCategorias.borrarCategoria(c);
    }

    /**
     * Comprueba si un libro tiene prestamos
     * @param idLibro Identificador del libro
     * @return true si el libro tiene prestamos, false si no los tiene
     */
    public boolean tienePrestamos(Integer idLibro) {
        return daoLibros.tienePrestamos(idLibro);
    }


    /**
     * Comprueba si un libro tiene ejemplares
     * @param idLibro Identificador del libro
     * @return true si el libro tiene ejemplares, false si no los tiene
     */
    public boolean tieneEjemplares(Integer idLibro) {
        return daoLibros.tieneEjemplares(idLibro);
    }

    /**
     * Comprueba si un ejemplar de un libro tiene préstamos activos
     * @param idLibro Identificador del libro
     * @param numEjemplar Número del ejemplar
     * @return true si el ejemplar tiene prestamos activos, false si no los tiene
     */
    public boolean tienePrestamoEnActivoEjemplar(Integer idLibro, Integer numEjemplar) {
        return daoPrestamos.tienePrestamoEnActivoEjemplar(idLibro, numEjemplar);
    }

    /**
     * Mira los préstamos vencidos de un usuario
     * @param idUsuario Identificador del usuario
     * @return Número de préstamos vencidos del usuario
     */
    public Integer consultarNumPrestamosVencidosPorUsuario(String idUsuario) {
        return daoPrestamos.consultarNumPrestamosVencidosPorUsuario(idUsuario);
    }


    /**
     * Realiza el alta de un nuevo préstamo
     * @param usuarioSolicitante Identificador del usuario solicitante
     * @param idLibro Identificador del libro
     * @param numEjemplar Número de ejemplar a prestar
     */
    public void nuevoPrestamo(String usuarioSolicitante, Integer idLibro, Integer numEjemplar) 
    {
        daoPrestamos.nuevoPrestamo(usuarioSolicitante, idLibro, numEjemplar);
    }

    /**
     * Realiza la devolución de un préstamo
     * @param idLibro Identificador del libro
     * @param numEjemplar Número de ejemplar a devolver
     */
    public void devolverEjemplar(int idLibro, int numEjemplar)
    {
        daoPrestamos.devolverEjemplar(idLibro, numEjemplar);
    }

    /**
     * Comprueba si un ejemplar tiene prestamos
     * @param id_libro Identificador del libro
     * @param numEjemplar Número de ejemplar
     * @return true si el ejemplar tiene prestamos, false si no los tiene
     */
    public boolean tienePrestamosEjemplar(int id_libro, int numEjemplar)
    {
        return daoPrestamos.tienePrestamosEjemplar(id_libro, numEjemplar);
    }

    /**
     * Comprueba si un usuario tiene préstamos activos
     * @param idUsuario Identificador del usuario
     * @return true si el usuario tiene prestamos activos, false si no los tiene
     */
    public boolean tienePrestamosActivosUsuario(String idUsuario) {
        return daoPrestamos.tienePrestamosActivosUsuario(idUsuario);
    }

    /**
     * Comprueba si una categoría tiene libros
     * @param c Categoría a comprobar
     * @return true si la categoría tiene libros, false si no los tiene
     */
    public boolean tieneLibrosCategoria(Categoria c) {
        return daoCategorias.tieneLibrosCategoria(c);
    }
}
