package baseDatos.dao;

import aplicacion.objetos.Prestamo;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 * @author Marcelo F.M.
 * @version 1.0
 * @since global: 2.0
 */
public class DAOPrestamos extends AbstractDAO {
    public DAOPrestamos(java.sql.Connection conexion, aplicacion.FachadaAplicacion fa) {
        super.setConexion(conexion);
        super.setFachadaAplicacion(fa);
    }

    public boolean tienePrestamoEnActivoEjemplar(Integer idLibro, Integer numEjemplar) {
        boolean salida = false;

        PreparedStatement stmPrestamo;
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
        int salida = 0;

        PreparedStatement stmPrestamo;
        ResultSet rsPrestamo;

        String consulta = "select count(*) as numPrestamos from prestamo where id_usuario = ? and (fecha_prestamo+30)< CURRENT_DATE and fecha_devolucion is null";

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

    @Deprecated
    public List<Prestamo> consultarTodosLosPrestamosParaEjemplar(Integer idLibro, Integer numEjemplar) {
        if (idLibro == null || numEjemplar == null) {
            return null;
        }

        List<Prestamo> listaprestamoActivos = new ArrayList<>();

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
                listaprestamoActivos.add(new Prestamo(/*idLibro, numEjemplar, */ rsPrestamo.getString("id_usuario"), rsPrestamo.getString("fecha_prestamo"), rsPrestamo.getString("fecha_devolucion")));
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

        return listaprestamoActivos;
    }

    @Deprecated
    public List<Prestamo> consultarTodosLosPrestamosParaLibro(Integer idLibro) {
        if (idLibro == null) {
            return null;
        }

        List<Prestamo> listaprestamoActivos = new ArrayList<>();

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
                listaprestamoActivos.add(new Prestamo(/*idLibro, rsPrestamo.getInt("num_ejemplar"),*/ rsPrestamo.getString("id_usuario"), rsPrestamo.getString("fecha_prestamo"), rsPrestamo.getString("fecha_devolucion")));
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

        return listaprestamoActivos;
    }

    @Deprecated
    public Prestamo consultarPrestamoActivoParaEjemplar(Integer idLibro, Integer numEjemplar) {
        if (idLibro == null || numEjemplar == null) {
            return null;
        }

        Prestamo salida = null;

        PreparedStatement stmPrestamo;
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
                salida = new Prestamo(/*rsPrestamo.getInt("id_libro"), rsPrestamo.getInt("num_ejemplar"),*/ rsPrestamo.getString("id_usuario"), rsPrestamo.getString("fecha_prestamo"), rsPrestamo.getString("fecha_devolucion"));
            }
        } catch (Exception e) {
            super.getFachadaAplicacion().muestraExcepcion("Dao prestamos : " + e.getMessage());
        }
        return salida;
    }

    public void nuevoPrestamo(String usuarioSolicitante, Integer idLibro, Integer numEjemplar) {
        PreparedStatement stmInsertarPrestamo = null;
        String consulta = "INSERT INTO prestamo(fecha_prestamo,id_usuario,id_libro,num_ejemplar)"
                + "values(CURRENT_DATE,?,?,?);";
        java.sql.Connection con = super.getConexion();
        
        try
        {
            stmInsertarPrestamo= con.prepareStatement(consulta);
            stmInsertarPrestamo.setString(1,usuarioSolicitante);
            stmInsertarPrestamo.setInt(2,idLibro);
            stmInsertarPrestamo.setInt(3,numEjemplar);
            
            stmInsertarPrestamo.executeUpdate();

        }catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmInsertarPrestamo != null) {
                    stmInsertarPrestamo.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }

    public void devolverEjemplar(int idLibro, int numEjemplar) {

        PreparedStatement stmDevolucion = null;
        String setenciaDevolucion = "UPDATE " +
                                    "   prestamo " +
                                    "SET " +
                                    "   fecha_devolucion = CURRENT_DATE " +
                                    "WHERE" +
                                    "   id_libro = ?" +
                                    "   and num_ejemplar = ?";

        java.sql.Connection con = super.getConexion();

        try
        {
            stmDevolucion = con.prepareStatement(setenciaDevolucion);
            stmDevolucion.setInt(1, idLibro);
            stmDevolucion.setInt(2, numEjemplar);

            stmDevolucion.executeUpdate();
        }catch (SQLException excp)
        {
            System.out.println(excp.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(excp.getMessage());
        } finally
        {
            try
            {
                if (stmDevolucion != null) {
                    stmDevolucion.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }

    public boolean tienePrestamosEjemplar(int id_libro, int numEjemplar) {
        boolean salida = false;

        PreparedStatement stmPrestamo;
        ResultSet rsPrestamo;

        String consulta = "select count(*) from prestamo where num_ejemplar = ? and id_libro = ?";
        java.sql.Connection con = super.getConexion();

        try
        {
            stmPrestamo = con.prepareStatement(consulta);
            stmPrestamo.setInt(1, numEjemplar);
            stmPrestamo.setInt(2, id_libro);
            rsPrestamo = stmPrestamo.executeQuery();
            if (rsPrestamo.next()) {
                salida = rsPrestamo.getInt(1) > 0;
            }
        }catch (SQLException excp)
        {
            System.out.println(excp.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(excp.getMessage());
        }
        return salida;
    }

    public boolean tienePrestamosActivosUsuario(String text)
    {
        boolean salida = false;

        PreparedStatement stmPrestamo;
        ResultSet rsPrestamo;

        String consulta = "select count(*) from prestamo where id_usuario = ? and fecha_devolucion is null";
        java.sql.Connection con = super.getConexion();

        try
        {
            stmPrestamo = con.prepareStatement(consulta);
            stmPrestamo.setString(1, text);
            rsPrestamo = stmPrestamo.executeQuery();
            if (rsPrestamo.next()) {
                salida = rsPrestamo.getInt(1) > 0;
            }
        }catch (SQLException excp)
        {
            System.out.println(excp.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(excp.getMessage());
        }
        return salida;
    }
}
