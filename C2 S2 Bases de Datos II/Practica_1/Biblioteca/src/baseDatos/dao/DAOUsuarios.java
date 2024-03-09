/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package baseDatos.dao;

import aplicacion.FachadaAplicacion;
import auxiliares.Criptografia;
import aplicacion.objetos.Usuario;
import aplicacion.enums.TipoUsuario;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/**
 * @author basesdatos
 */
public class DAOUsuarios extends AbstractDAO {

    public DAOUsuarios(Connection conexion, aplicacion.FachadaAplicacion fa) {
        super.setConexion(conexion);
        super.setFachadaAplicacion(fa);
    }

    public Usuario validarUsuario(String idUsuario, String clave) {
        Usuario resultado = null;
        Connection con;
        PreparedStatement stmUsuario = null;
        ResultSet rsUsuario;

        clave = Criptografia.cifradoCaesar(clave);

        con = this.getConexion();

        try {
            stmUsuario = con.prepareStatement("select id_usuario, clave, nombre, direccion, email, tipo_usuario " +
                    "from usuario " +
                    "where id_usuario = ? and clave = ?");
            stmUsuario.setString(1, idUsuario);
            stmUsuario.setString(2, clave);
            rsUsuario = stmUsuario.executeQuery();
            if (rsUsuario.next()) {
                resultado = new Usuario(rsUsuario.getString("id_usuario"), rsUsuario.getString("clave"),
                        rsUsuario.getString("nombre"), rsUsuario.getString("direccion"),
                        rsUsuario.getString("email"), TipoUsuario.valueOf(rsUsuario.getString("tipo_usuario")));
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                stmUsuario.close();
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
        return resultado;
    }


    public void editarUsuario(String Id, String clave, TipoUsuario tipo, String nombre, String email, String direccion) {
        FachadaAplicacion fa = this.getFachadaAplicacion();

        if (Id == null) {
            fa.muestraExcepcion("[ERROR] editarUsuario (DAO) El id del usuario no puede ser nulo");
            return;
        }

        PreparedStatement stmEditarUsuario;
        Connection con = this.getConexion();

        int camposOcupados = 0b0000000;
        String consultaActualizacion = "UPDATE usuario SET";

        camposOcupados = camposOcupados | 0b00000001;
        consultaActualizacion += "Id = ?, ";

        if (clave != null) {
            camposOcupados = camposOcupados | 0b000010;
            consultaActualizacion += "clave = ?, ";
        }
        if (tipo != null) {
            camposOcupados = camposOcupados | 0b0000100;
            consultaActualizacion += "tipo_usuario = ?, ";
        }
        if (nombre != null) {
            camposOcupados = camposOcupados | 0b0001000;
            consultaActualizacion += "nombre = ?, ";
        }
        if (email != null) {
            camposOcupados = camposOcupados | 0b0010000;
            consultaActualizacion += "email = ?, ";
        }
        if (direccion != null) {
            camposOcupados = camposOcupados | 0b0100000;
            consultaActualizacion += "direccion = ? ";
        }


        if (consultaActualizacion.endsWith(", ")) {
            consultaActualizacion = consultaActualizacion.substring(0, consultaActualizacion.length() - 2);
        }


        try {
            stmEditarUsuario = con.prepareStatement(consultaActualizacion + " WHERE id_usuario = ?");

            int i = 0;

            stmEditarUsuario.setString(i, Id);
            i++;

            if ((camposOcupados & 0b0000010) != 0) {
                clave = Criptografia.cifradoCaesar(clave);
                stmEditarUsuario.setString(i, (clave));
                i++;
            }
            if ((camposOcupados & 0b0000100) != 0) {
                stmEditarUsuario.setString(i, tipo.toString());
                i++;
            }
            if ((camposOcupados & 0b0001000) != 0) {
                stmEditarUsuario.setString(i, nombre);
                i++;
            }
            if ((camposOcupados & 0b0010000) != 0) {
                stmEditarUsuario.setString(i, email);
                i++;
            }
            if ((camposOcupados & 0b0100000) != 0) {
                stmEditarUsuario.setString(i, direccion);
            }

            stmEditarUsuario.executeUpdate();


        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        }
    }

    /**
     * @param id     Identificador del usuario
     * @param nombre Nombre del usuario
     * @return Lista de usuarios que cumplen con los criterios de búsqueda
     */
    public List<Usuario> consultarUsuarios(String id, String nombre) {
        ArrayList<Usuario> UsuariosSalida = new ArrayList<>();
        Usuario usuarioActual;
        PreparedStatement stmUsuarios;
        ResultSet rsUsuarios;

        Connection con = this.getConexion();

        String consulta = "SELECT id_usuario, clave, nombre, direccion, email, tipo_usuario " +
                "FROM usuario ";


        if (id != null) {
            consulta += "WHERE id_usuario like ?";
            if (nombre != null) {
                consulta += "and nombre like ?";
            }
        }
        else if (nombre != null) {
            consulta += "WHERE nombre like ?";
        }


        try {

            stmUsuarios = con.prepareCall(consulta);

            if (id != null) {
                stmUsuarios.setString(1, "%" + id + "%");
                if (nombre != null) {
                    stmUsuarios.setString(2, "%" + nombre + "%");
                }
            }
            else if (nombre != null) {
                stmUsuarios.setString(1, "%" + nombre + "%");
            }

            rsUsuarios = stmUsuarios.executeQuery();

            while (rsUsuarios.next()) {
                usuarioActual = new Usuario(rsUsuarios.getString("id_usuario"), Criptografia.descifradoCaesar(rsUsuarios.getString("clave")), rsUsuarios.getString("nombre"),
                        rsUsuarios.getString("direccion"), rsUsuarios.getString("email"), Objects.equals(rsUsuarios.getString("tipo_usuario"), "Administrador") ? TipoUsuario.Administrador : TipoUsuario.Normal);
                UsuariosSalida.add(usuarioActual);
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());

        }
        return UsuariosSalida;
    }

    public void insertarUsuario(Usuario usuario) {
        Connection con = this.getConexion();
        PreparedStatement stmUsuario = null;
        String consulta = "insert into usuario(id_usuario, clave, nombre, direccion, email, tipo_usuario) " +
                "values (?,?,?,?,?,?)";
        try {
            stmUsuario = con.prepareStatement(consulta);
            stmUsuario.setString(1, Criptografia.cifradoCaesar(usuario.getIdUsuario()));
            stmUsuario.setString(2, Criptografia.cifradoCaesar(usuario.getClave()));
            stmUsuario.setString(3, usuario.getNombre());
            stmUsuario.setString(4, usuario.getDireccion());
            stmUsuario.setString(5, usuario.getEmail());
            stmUsuario.setString(6, usuario.getTipoUsuario().toString());
            stmUsuario.executeUpdate();
        } catch (SQLException excp) {
            System.out.println(excp.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(excp.getMessage());
        } finally {
            try {
                stmUsuario.close();
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }

    public void actualizarUsuario(Usuario usuarioAguardar) {
        Connection con = this.getConexion();
        PreparedStatement stmUsuario = null;
        String consulta = "update usuario " +
                "set clave = ?, nombre = ?, direccion = ?, email = ?, tipo_usuario = ? " +
                "where id_usuario = ?";
        try {
            stmUsuario = con.prepareStatement(consulta);
            stmUsuario.setString(1, Criptografia.cifradoCaesar(usuarioAguardar.getClave()));
            stmUsuario.setString(2, usuarioAguardar.getNombre());
            stmUsuario.setString(3, usuarioAguardar.getDireccion());
            stmUsuario.setString(4, usuarioAguardar.getEmail());
            stmUsuario.setString(5, usuarioAguardar.getTipoUsuario().toString());
            stmUsuario.setString(6, usuarioAguardar.getIdUsuario());
            stmUsuario.executeUpdate();
        } catch (SQLException excp) {
            System.out.println(excp.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(excp.getMessage());
        } finally {
            try {
                stmUsuario.close();
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }

    public void borrarUsuario(String text) {
        Connection con = this.getConexion();
        PreparedStatement stmUsuario = null;
        String consulta = "delete from usuario where id_usuario = ?";
        try {
            stmUsuario = con.prepareStatement(consulta);
            stmUsuario.setString(1, text);
            stmUsuario.executeUpdate();
        } catch (SQLException excp) {
            System.out.println(excp.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(excp.getMessage());
        } finally {
            try {
                stmUsuario.close();
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }
}
