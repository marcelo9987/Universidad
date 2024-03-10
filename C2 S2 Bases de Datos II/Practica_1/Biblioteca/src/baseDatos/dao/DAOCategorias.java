/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package baseDatos.dao;

import aplicacion.objetos.Categoria;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

/**
 * @author basesdatos
 * @author Marcelo F.M.
 * @version 2.0
 */
public class DAOCategorias extends AbstractDAO {


    public DAOCategorias(Connection conexion, aplicacion.FachadaAplicacion fa) {
        super.setConexion(conexion);
        super.setFachadaAplicacion(fa);
    }

    public List<Categoria> consultarCategorias() {
        List<Categoria> resultado = new ArrayList<>();
        Categoria categoriaActual;
        Connection con;
        PreparedStatement stmCategorias = null;
        ResultSet rsCategorias;

        con = this.getConexion();

        try {
            stmCategorias = con.prepareStatement("select nombre, descripcion from categoria");
            rsCategorias = stmCategorias.executeQuery();
            while (rsCategorias.next()) {
                categoriaActual = new Categoria(rsCategorias.getString("nombre"), rsCategorias.getString("descripcion"));
                resultado.add(categoriaActual);
            }

        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                stmCategorias.close();
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
        return resultado;
    }


    public void insertarCategoria(Categoria c) {
        Connection con;
        PreparedStatement stmCategorias = null;

        con = this.getConexion();

        try {
            stmCategorias = con.prepareStatement("insert into categoria(nombre, descripcion) values (?, ?)");
            stmCategorias.setString(1, c.getNombre());
            stmCategorias.setString(2, c.getDescripcion());
            stmCategorias.executeUpdate();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        } finally {
            try {
                stmCategorias.close();
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }

    public void borrarCategoria(Categoria c) {
        Connection con;
        PreparedStatement stmCategorias = null;

        con = this.getConexion();

        try {
            stmCategorias = con.prepareStatement("delete from categoria where nombre = ?");
            stmCategorias.setString(1, c.getNombre());
            stmCategorias.executeUpdate();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        } finally {
            try {
                stmCategorias.close();
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }

    public boolean tieneLibrosCategoria(Categoria c) {
        Connection con;
        PreparedStatement stmCategorias = null;
        ResultSet rsCategorias;
        boolean resultado = false;

        con = this.getConexion();

        try {
            stmCategorias = con.prepareStatement("select id_libro from cat_tiene_libro where categoria = ?");
            stmCategorias.setString(1, c.getNombre());
            rsCategorias = stmCategorias.executeQuery();
            if (rsCategorias.next()) {
                resultado = true;
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        } finally {
            try {
                stmCategorias.close();
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
        return resultado;
    }
}
