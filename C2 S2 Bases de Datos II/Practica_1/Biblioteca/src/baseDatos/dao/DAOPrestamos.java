package baseDatos.dao;

import aplicacion.objetos.Prestamo;

import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class DAOPrestamos extends AbstractDAO {
    public DAOPrestamos(java.sql.Connection conexion, aplicacion.FachadaAplicacion fa) {
        super.setConexion(conexion);
        super.setFachadaAplicacion(fa);
    }

    public Prestamo consultarPrestamoParaEjemplar(Integer idLibro, Integer numEjemplar) {

        if (idLibro == null || numEjemplar == null) {
            return null;
        }

        Prestamo Salida = null;

        PreparedStatement stmPrestamo = null;
        ResultSet rsPrestamo;

        // TODO: Cambiar esta query
        String consulta = "select fecha_prestamo, usuario, id_libro, num_ejemplar, fecha_devolucion from prestamo where id_libro = ? and num_ejemplar = ?";

        java.sql.Connection con;
        con = super.getConexion();

        try {
            stmPrestamo = con.prepareStatement(consulta);

            stmPrestamo.setInt(1, idLibro);
            stmPrestamo.setInt(2, numEjemplar);

            rsPrestamo = stmPrestamo.executeQuery();
            if (rsPrestamo.next()) {
                Salida = new Prestamo(rsPrestamo.getInt("id_libro"), rsPrestamo.getInt("num_ejemplar"), rsPrestamo.getString("id_usuario"), rsPrestamo.getString("fecha_prestamo"), rsPrestamo.getString("fecha_devolucion"));
            }
        } catch (Exception e) {
            super.getFachadaAplicacion().muestraExcepcion("Dao prestamos : " + e.getMessage());
        }
        return Salida;
    }

    public boolean tienePrestamoEnActivoEjemplar(Integer idLibro, Integer numEjemplar) {
        boolean Salida = false;

        PreparedStatement stmPrestamo = null;
        ResultSet rsPrestamo;

        String consulta = "select * from prestamo where id_libro = ? and num_ejemplar = ? and fecha_devolucion is null";

        java.sql.Connection con;
        con = super.getConexion();

        try {
            stmPrestamo = con.prepareStatement(consulta);

            stmPrestamo.setInt(1, idLibro);
            stmPrestamo.setInt(2, numEjemplar);

            rsPrestamo = stmPrestamo.executeQuery();
            if (rsPrestamo.next()) {
                Salida = true;
            }
        } catch (Exception e) {
            super.getFachadaAplicacion().muestraExcepcion("Dao prestamos : " + e.getMessage());
        }
        return Salida;
    }

    public Integer consultarPrestamosVencidos(String idUsuario) {
        Integer Salida = 0;

        PreparedStatement stmPrestamo = null;
        ResultSet rsPrestamo;

        String consulta = "select count(*) as numPrestamos from prestamo where usuario = ? and fecha_devolucion < current_date";

        java.sql.Connection con;
        con = super.getConexion();

        try {
            stmPrestamo = con.prepareStatement(consulta);

            stmPrestamo.setString(1, idUsuario);

            rsPrestamo = stmPrestamo.executeQuery();
            if (rsPrestamo.next()) {
                Salida = rsPrestamo.getInt("numPrestamos");
            }
        } catch (Exception e) {
            super.getFachadaAplicacion().muestraExcepcion("Dao prestamos : " + e.getMessage());
        }
        return Salida;
    }

    public Prestamo consultarPrestamoActivoParaEjemplar(Integer idLibro, Integer numEjemplar) {
        if (idLibro == null || numEjemplar == null) {
            return null;
        }

        Prestamo Salida = null;

        PreparedStatement stmPrestamo = null;
        ResultSet rsPrestamo;

        String consulta = "select fecha_prestamo, usuario, id_libro, num_ejemplar, fecha_devolucion " +
                "from prestamo where id_libro = ? and num_ejemplar = ? and fecha_devolucion is null";

        java.sql.Connection con;
        con = super.getConexion();

        try {
            stmPrestamo = con.prepareStatement(consulta);

            stmPrestamo.setInt(1, idLibro);
            stmPrestamo.setInt(2, numEjemplar);

            rsPrestamo = stmPrestamo.executeQuery();
            if (rsPrestamo.next()) {
                Salida = new Prestamo(rsPrestamo.getInt("id_libro"), rsPrestamo.getInt("num_ejemplar"), rsPrestamo.getString("id_usuario"), rsPrestamo.getString("fecha_prestamo"), rsPrestamo.getString("fecha_devolucion"));
            }
        } catch (Exception e) {
            super.getFachadaAplicacion().muestraExcepcion("Dao prestamos : " + e.getMessage());
        }
        return Salida;
    }
}
