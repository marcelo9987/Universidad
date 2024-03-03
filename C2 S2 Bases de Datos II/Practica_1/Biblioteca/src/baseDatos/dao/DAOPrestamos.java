package baseDatos.dao;

import aplicacion.objetos.Prestamo;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class DAOPrestamos extends AbstractDAO {
    public DAOPrestamos(java.sql.Connection conexion, aplicacion.FachadaAplicacion fa) {
        super.setConexion(conexion);
        super.setFachadaAplicacion(fa);
    }

    public boolean tienePrestamoEnActivoEjemplar(Integer idLibro, Integer numEjemplar) {
        boolean salida = false;

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
                salida = true;
            }
        } catch (Exception e) {
            super.getFachadaAplicacion().muestraExcepcion("Dao prestamos : " + e.getMessage());
        }
        return salida;
    }

    public Integer consultarNumPrestamosVencidosPorUsuario(String idUsuario) {
        Integer salida = 0;

        PreparedStatement stmPrestamo = null;
        ResultSet rsPrestamo;

        String consulta = "select count(*) as numPrestamos from prestamo where id_usuario = ? and fecha_devolucion < current_date";

        java.sql.Connection con;
        con = super.getConexion();

        try {
            stmPrestamo = con.prepareStatement(consulta);

            stmPrestamo.setString(1, idUsuario);

            rsPrestamo = stmPrestamo.executeQuery();
            if (rsPrestamo.next()) {
                salida = rsPrestamo.getInt("numPrestamos");
            }
        } catch (Exception e) {
            super.getFachadaAplicacion().muestraExcepcion("Dao prestamos : " + e.getMessage());
        }
        return salida;
    }

    public List<Prestamo> consultarTodosLosPrestamosParaEjemplar(Integer idLibro, Integer numEjemplar) {
        if (idLibro == null || numEjemplar == null) {
            return null;
        }

        List<Prestamo> listaPrestamos = new ArrayList<>();

        PreparedStatement stmPrestamos = null;
        ResultSet rsPrestamo;

        String consulta = "select fecha_prestamo, id_usuario, fecha_devolucion " +
                "from prestamo where id_libro = ? and num_ejemplar = ? " +
                "order by fecha_prestamo, id_usuario";

        java.sql.Connection con = super.getConexion();

        try {
            stmPrestamos = con.prepareStatement(consulta);

            stmPrestamos.setInt(1, idLibro);
            stmPrestamos.setInt(2, numEjemplar);

            rsPrestamo = stmPrestamos.executeQuery();
            while (rsPrestamo.next()) {
                listaPrestamos.add(new Prestamo(idLibro, numEjemplar, rsPrestamo.getString("id_usuario"), rsPrestamo.getString("fecha_prestamo"), rsPrestamo.getString("fecha_devolucion")));
            }
        } catch (Exception e) {
            super.getFachadaAplicacion().muestraExcepcion("Dao prestamos : " + e.getMessage());
        } finally {
            try {
                if (stmPrestamos != null) {
                    stmPrestamos.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }

        return listaPrestamos;
    }

    public List<Prestamo> consultarTodosLosPrestamosParaLibro(Integer idLibro) {
        if (idLibro == null) {
            return null;
        }

        List<Prestamo> listaPrestamos = new ArrayList<>();

        PreparedStatement stmPrestamos = null;
        ResultSet rsPrestamo;

        String consulta = "select fecha_prestamo, id_usuario, fecha_devolucion " +
                "from prestamo where id_libro = ? " +
                "order by num_ejemplar, fecha_prestamo, id_usuario";

        java.sql.Connection con = super.getConexion();

        try {
            stmPrestamos = con.prepareStatement(consulta);

            stmPrestamos.setInt(1, idLibro);

            rsPrestamo = stmPrestamos.executeQuery();
            while (rsPrestamo.next()) {
                listaPrestamos.add(new Prestamo(idLibro, rsPrestamo.getInt("num_ejemplar"), rsPrestamo.getString("id_usuario"), rsPrestamo.getString("fecha_prestamo"), rsPrestamo.getString("fecha_devolucion")));
            }
        } catch (Exception e) {
            super.getFachadaAplicacion().muestraExcepcion("Dao prestamos : " + e.getMessage());
        } finally {
            try {
                if (stmPrestamos != null) {
                    stmPrestamos.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }

        return listaPrestamos;
    }

    public Prestamo consultarPrestamoActivoParaEjemplar(Integer idLibro, Integer numEjemplar) {
        if (idLibro == null || numEjemplar == null) {
            return null;
        }

        Prestamo salida = null;

        PreparedStatement stmPrestamo = null;
        ResultSet rsPrestamo;

        String consulta = "select fecha_prestamo, id_usuario, id_libro, num_ejemplar, fecha_devolucion " +
                "from prestamo where id_libro = ? and num_ejemplar = ? and fecha_devolucion is null";

        java.sql.Connection con;
        con = super.getConexion();

        try {
            stmPrestamo = con.prepareStatement(consulta);

            stmPrestamo.setInt(1, idLibro);
            stmPrestamo.setInt(2, numEjemplar);

            rsPrestamo = stmPrestamo.executeQuery();
            if (rsPrestamo.next()) {
                salida = new Prestamo(rsPrestamo.getInt("id_libro"), rsPrestamo.getInt("num_ejemplar"), rsPrestamo.getString("id_usuario"), rsPrestamo.getString("fecha_prestamo"), rsPrestamo.getString("fecha_devolucion"));
            }
        } catch (Exception e) {
            super.getFachadaAplicacion().muestraExcepcion("Dao prestamos : " + e.getMessage());
        }
        return salida;
    }
}
