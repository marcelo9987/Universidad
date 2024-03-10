/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package baseDatos.dao;

import aplicacion.objetos.Ejemplar;
import aplicacion.objetos.Categoria;
import aplicacion.objetos.Libro;
import aplicacion.objetos.Prestamo;
import auxiliares.Utilidades;

import java.util.ArrayList;
import java.util.List;

import java.sql.*;
import java.util.StringJoiner;

/**
 * @author basesdatos
 * @author Marcelo F.M.
 * @version 2.0
 */
public class DAOLibros extends AbstractDAO {

    public DAOLibros(Connection conexion, aplicacion.FachadaAplicacion fa) {
        super.setConexion(conexion);
        super.setFachadaAplicacion(fa);
    }

    public List<Libro> consultarCatalogo(Integer id, String titulo, String isbn, String autor) {
        List<Libro> resultado = new ArrayList<>();
        Libro libroActual;
        Connection con;
        PreparedStatement stmCatalogo = null;
        ResultSet rsCatalogo;
        PreparedStatement stmAutores = null;
        ResultSet rsAutores;

        con = this.getConexion();

        StringJoiner sjConsulta = new StringJoiner("\n");

        sjConsulta.add("select id_libro, titulo, isbn, editorial, paginas, ano");
        sjConsulta.add("from libro as l");
        sjConsulta.add("where lower(titulo) like ?"); // ?: 1
        sjConsulta.add("  and lower(isbn) like ?");   // ?: 2
        if (id != null) {
            sjConsulta.add(" and id_libro = ?"); // ?: 3
        }

        if (!autor.isEmpty()) {
            sjConsulta.add("  and exists (");
            sjConsulta.add("        select *");
            sjConsulta.add("        from autor a");
            sjConsulta.add("        where a.id_libro=l.id_libro");
            sjConsulta.add("          and lower(nombre) like ?)"); // ?: 3/4
        }

        sjConsulta.add("order by id_libro");

        try {
            stmCatalogo = con.prepareStatement(sjConsulta.toString());
            stmCatalogo.setString(1, "%" + Utilidades.getLowerCase(titulo) + "%");
            stmCatalogo.setString(2, "%" + Utilidades.getLowerCase(isbn) + "%");

            if (id != null) {
                stmCatalogo.setInt(3, id);

            }

            if (!autor.isEmpty()) {
                stmCatalogo.setString((id != null) ? 4 : 3, "%" + Utilidades.getLowerCase(autor) + "%");
            }

            System.out.println(stmCatalogo);

            rsCatalogo = stmCatalogo.executeQuery();
            while (rsCatalogo.next()) {
                libroActual = new Libro(rsCatalogo.getInt("id_libro"), rsCatalogo.getString("titulo"),
                        rsCatalogo.getString("isbn"), rsCatalogo.getString("editorial"),
                        (Integer) rsCatalogo.getObject("paginas"), rsCatalogo.getString("ano"));
                try {
                    stmAutores = con.prepareStatement("select nombre as autor " +
                            "from autor " +
                            "where id_libro = ? " +
                            "order by orden");
                    stmAutores.setInt(1, libroActual.getIdLibro());
                    rsAutores = stmAutores.executeQuery();
                    while (rsAutores.next()) {
                        libroActual.addAutor(rsAutores.getString("autor"));
                    }
                } catch (SQLException e) {
                    System.out.println(e.getMessage());
                    this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
                } finally {
                    if (stmAutores != null) {
                        stmAutores.close();
                    }
                }
                resultado.add(libroActual);
            }

        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmCatalogo != null) {
                    stmCatalogo.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
        return resultado;
    }

    public Libro consultarLibro(Integer idLibro) {
        Libro libroResultado = null;
        Connection con;
        PreparedStatement stmLibro = null;
        ResultSet rsLibro;
        PreparedStatement stmAutores = null;
        ResultSet rsAutores;
        PreparedStatement stmCategorias = null;
        ResultSet rsCategorias;
        PreparedStatement stmEjemplares = null;
        ResultSet rsEjemplares;

        con = super.getConexion();

        try {
            stmLibro = con.prepareStatement("select id_libro, titulo, isbn, editorial, paginas, ano " +
                    "from libro " +
                    "where id_libro = ?");
            stmLibro.setInt(1, idLibro);
            rsLibro = stmLibro.executeQuery();
            if (rsLibro.next()) {
                libroResultado = new Libro(rsLibro.getInt("id_libro"), rsLibro.getString("titulo"),
                        rsLibro.getString("isbn"), rsLibro.getString("editorial"),
                        (Integer) rsLibro.getObject("paginas"), rsLibro.getString("ano"));

                try {
                    stmAutores = con.prepareStatement("select nombre as autor " +
                            "from autor " +
                            "where id_libro = ? " +
                            "order by orden");
                    stmAutores.setInt(1, libroResultado.getIdLibro());
                    rsAutores = stmAutores.executeQuery();
                    while (rsAutores.next()) {
                        libroResultado.addAutor(rsAutores.getString("autor"));
                    }
                } catch (SQLException e) {
                    System.out.println(e.getMessage());
                    this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
                } finally {
                    if (stmAutores != null) {
                        stmAutores.close();
                    }
                }
                try {
                    stmCategorias = con.prepareStatement("select categoria " +
                            "from cat_tiene_libro " +
                            "where id_libro = ?");
                    stmCategorias.setInt(1, libroResultado.getIdLibro());
                    rsCategorias = stmCategorias.executeQuery();
                    while (rsCategorias.next()) {
                        libroResultado.addCategoria(new Categoria(rsCategorias.getString("categoria"), null));
                    }
                } catch (SQLException e) {
                    System.out.println(e.getMessage());
                    this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
                } finally {
                    if (stmCategorias != null) {
                        stmCategorias.close();
                    }
                }
                try {
                    stmEjemplares = con.prepareStatement("select e.id_libro, e.num_ejemplar, e.ano_compra, e.localizador, p.fecha_prestamo, p.id_usuario, p.fecha_devolucion " +
                            "from ejemplar e left join prestamo p on p.id_libro = e.id_libro and p.num_ejemplar = e.num_ejemplar and p.fecha_devolucion is null " +
                            "where e.id_libro = ?");
                    stmEjemplares.setInt(1, libroResultado.getIdLibro());
                    rsEjemplares = stmEjemplares.executeQuery();
                    while (rsEjemplares.next()) {
                        Prestamo prestamoActivo = new Prestamo(rsEjemplares.getString("id_usuario"),
                                rsEjemplares.getString("fecha_prestamo"),
                                rsEjemplares.getString("fecha_devolucion"));

                        Ejemplar ejemplar = new Ejemplar(libroResultado,
                                rsEjemplares.getInt("num_ejemplar"),
                                rsEjemplares.getString("localizador"),
                                rsEjemplares.getString("ano_compra"), prestamoActivo);
                        libroResultado.addEjemplar(ejemplar);
                    }
                } catch (SQLException e) {
                    System.out.println(e.getMessage());
                    this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
                } finally {
                    if (stmEjemplares != null) {
                        stmEjemplares.close();
                    }
                }
            }

        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmLibro != null) {
                    stmLibro.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
        return libroResultado;
    }

    @Deprecated
    public List<Ejemplar> consultarEjemplaresLibro(Integer idLibro) {
        List<Ejemplar> resultado = new ArrayList<>();
        Connection con;
        PreparedStatement stmEjemplares = null;
        ResultSet rsEjemplares;

        con = super.getConexion();

        try {
            stmEjemplares = con.prepareStatement("select num_ejemplar, ano_compra, localizador " +
                    "from ejemplar " +
                    "where id_libro = ?");
            stmEjemplares.setInt(1, idLibro);
            rsEjemplares = stmEjemplares.executeQuery();
            while (rsEjemplares.next()) {
                resultado.add(new Ejemplar(null, rsEjemplares.getInt("num_ejemplar"),
                        rsEjemplares.getString("localizador"),
                        rsEjemplares.getString("ano_compra"), null));
            }


        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmEjemplares != null) {
                    stmEjemplares.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
        return resultado;
    }


    public List<String> obtenerRestoCategorias(Integer idLibro) {
        List<String> resultado = new ArrayList<>();
        String categoriaActual;
        Connection con;
        PreparedStatement stmCategorias = null;
        ResultSet rsCategorias;


        con = super.getConexion();

        try {
            stmCategorias = con.prepareStatement("select nombre " +
                    "from categoria c " +
                    "where not exists (select *  " +
                    "		  from cat_tiene_libro cl " +
                    "		  where cl.id_libro=? and cl.categoria=c.nombre)");
            stmCategorias.setInt(1, idLibro);
            rsCategorias = stmCategorias.executeQuery();
            while (rsCategorias.next()) {
                categoriaActual = rsCategorias.getString("nombre");
                resultado.add(categoriaActual);
            }

        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmCategorias != null) {
                    stmCategorias.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }

        return resultado;
    }

    public Integer insertarLibro(Libro libro) {
        Connection con;
        PreparedStatement stmLibro = null;
        PreparedStatement stmAutores = null;
        PreparedStatement stmIdLibro = null;
        ResultSet rsIdLibro;
        Integer numAutor;
        Integer idLibro = null;

        con = super.getConexion();

        try {
            stmLibro = con.prepareStatement("insert into libro(titulo, isbn, editorial, paginas, ano) " +
                    "values (?,?,?,?,?)");
            stmLibro.setString(1, libro.getTitulo());
            stmLibro.setString(2, libro.getIsbn());
            stmLibro.setString(3, libro.getEditorial());

            /* INI controlar nulos en páginas 2024-03-09 */
            if (libro.getPaginas() == null) {
                stmLibro.setNull(4, Types.INTEGER);
            }
            else {
                stmLibro.setInt(4, libro.getPaginas());
            }
            /* FIN controlar nulos en páginas 2024-03-09 */

            stmLibro.setString(5, libro.getAno());

            stmLibro.executeUpdate();

            try {
                stmIdLibro = con.prepareStatement("select currval('seq_libro_id_libro') as idLibro");
                rsIdLibro = stmIdLibro.executeQuery();
                rsIdLibro.next();
                idLibro = rsIdLibro.getInt("idLibro");
            } catch (SQLException e) {
                System.out.println(e.getMessage());
            } finally {
                if (stmIdLibro != null) {
                    stmIdLibro.close();
                }
            }

            try {
                stmAutores = con.prepareStatement("insert into autor(id_libro, nombre, orden) " +
                        "values (?,?,?)");
                numAutor = 1;
                for (String s : libro.getAutores()) {
                    stmAutores.setInt(1, idLibro);
                    stmAutores.setString(2, s);
                    stmAutores.setInt(3, numAutor);
                    stmAutores.executeUpdate();
                    numAutor = numAutor + 1;
                }
            } catch (SQLException e) {
                System.out.println(e.getMessage());
                this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
            } finally {
                if (stmAutores != null) {
                    stmAutores.close();
                }
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmLibro != null) {
                    stmLibro.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }

        return idLibro;
    }

    public void borrarLibro(Integer idLibro) {
        Connection con;
        PreparedStatement stmLibro = null;

        con = super.getConexion();

        try {
            stmLibro = con.prepareStatement("delete from libro where id_libro = ?");
            stmLibro.setInt(1, idLibro);
            stmLibro.executeUpdate();

        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                stmLibro.close();
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }

    public void modificarLibro(Libro libro) {
        Connection con;
        PreparedStatement stmLibro = null;
        PreparedStatement stmAutores = null;
        PreparedStatement stmBorrado = null;
        Integer numAutor;

        con = super.getConexion();

        try {
            stmLibro = con.prepareStatement("update libro " +
                    "set titulo=?, " +
                    "    isbn=?, " +
                    "    editorial=?, " +
                    "    paginas=?, " +
                    "    ano=? " +
                    "where id_libro=?");
            stmLibro.setString(1, libro.getTitulo());
            stmLibro.setString(2, libro.getIsbn());
            stmLibro.setString(3, libro.getEditorial());

            /* INI controlar nulos en páginas 2024-03-09 */
            if (libro.getPaginas() == null) {
                stmLibro.setNull(4, Types.INTEGER);
            }
            else {
                stmLibro.setInt(4, libro.getPaginas());
            }
            /* FIN controlar nulos en páginas 2024-03-09 */

            stmLibro.setString(5, libro.getAno());

            stmLibro.setInt(6, libro.getIdLibro());
            stmLibro.executeUpdate();


            try {
                stmBorrado = con.prepareStatement("delete from autor where id_libro=?");
                stmBorrado.setInt(1, libro.getIdLibro());
                stmBorrado.executeUpdate();
            } catch (SQLException e) {
                System.out.println(e.getMessage());
                this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
            } finally {
                stmBorrado.close();
            }


            try {
                stmAutores = con.prepareStatement("insert into autor (id_libro, nombre, orden) " +
                        "values (?,?,?)");
                numAutor = 1;
                for (String s : libro.getAutores()) {
                    stmAutores.setInt(1, libro.getIdLibro());
                    stmAutores.setString(2, s);
                    stmAutores.setInt(3, numAutor);
                    stmAutores.executeUpdate();
                    numAutor = numAutor + 1;
                }
            } catch (SQLException e) {
                System.out.println(e.getMessage());
                this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
            } finally {
                if (stmAutores != null) {
                    stmAutores.close();
                }
            }


        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmLibro != null) {
                    stmLibro.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }

    public void modificarCategoriasLibro(Integer idLibro, List<String> categorias) {
        Connection con;
        PreparedStatement stmBorrado = null;
        PreparedStatement stmInsercion = null;

        con = super.getConexion();

        try {
            stmBorrado = con.prepareStatement("delete from cat_tiene_libro where id_libro = ?");
            stmBorrado.setInt(1, idLibro);
            stmBorrado.executeUpdate();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmBorrado != null) {
                    stmBorrado.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
        try {
            stmInsercion = con.prepareStatement("insert into cat_tiene_libro(id_libro, categoria) values (?,?)");
            for (String c : categorias) {
                stmInsercion.setInt(1, idLibro);
                stmInsercion.setString(2, c);
                stmInsercion.executeUpdate();
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmBorrado != null) {
                    stmBorrado.close();
                }
                if (stmInsercion != null) {
                    stmInsercion.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }

    public void insertarEjemplarLibro(Integer idLibro, Ejemplar ejemplar) {
        Connection con;
        PreparedStatement stmEjemplar = null;

        con = super.getConexion();

        try {
            stmEjemplar = con.prepareStatement("insert into ejemplar(id_libro, ano_compra, localizador) " +
                    "values (?,?,?)");
            stmEjemplar.setInt(1, idLibro);
            stmEjemplar.setString(2, ejemplar.getAnoCompra());
            stmEjemplar.setString(3, ejemplar.getLocalizador());
            stmEjemplar.executeUpdate();

        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmEjemplar != null) {
                    stmEjemplar.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }

    public void borrarEjemplaresLibro(Integer idLibro, List<Integer> numsEjemplar) {
        Connection con;
        PreparedStatement stmEjemplar = null;

        con = super.getConexion();

        try {
            stmEjemplar = con.prepareStatement("delete from ejemplar where id_libro=? and num_ejemplar=?");
            for (Integer i : numsEjemplar) {
                stmEjemplar.setInt(1, idLibro);
                stmEjemplar.setInt(2, i);
                stmEjemplar.executeUpdate();
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmEjemplar != null) {
                    stmEjemplar.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }

    public void modificarEjemplarLibro(Integer idLibro, Ejemplar ejemplar) {
        Connection con;
        PreparedStatement stmEjemplar = null;

        con = super.getConexion();

        try {
            stmEjemplar = con.prepareStatement("update ejemplar " +
                    "set ano_compra=?, " +
                    "   localizador=? " +
                    "where id_libro=? and num_ejemplar=?");
            stmEjemplar.setString(1, ejemplar.getAnoCompra());
            stmEjemplar.setString(2, ejemplar.getLocalizador());
            stmEjemplar.setInt(3, idLibro);
            stmEjemplar.setInt(4, ejemplar.getNumEjemplar());
            stmEjemplar.executeUpdate();

        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmEjemplar != null) {
                    stmEjemplar.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
    }

    public boolean tienePrestamos(Integer idLibro) {
        Connection con;
        PreparedStatement stmTienePrestamos = null;
        ResultSet rsTienePrestamos = null;
        boolean resultado = false;

        con = super.getConexion();

        try {
            stmTienePrestamos = con.prepareStatement("SELECT COUNT (*) as prestamos " +
                    "from ejemplar e " +
                    "where e.id_libro = ? " +
                    "  and exists (select * " +
                    "              from prestamo p " +
                    "              where p.num_ejemplar = e.num_ejemplar)");
            stmTienePrestamos.setInt(1, idLibro);
            rsTienePrestamos = stmTienePrestamos.executeQuery();

            if (rsTienePrestamos.next()) {
                resultado = rsTienePrestamos.getInt("prestamos") > 0;
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmTienePrestamos != null) {
                    stmTienePrestamos.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
        return resultado;
    }

    public boolean tieneEjemplares(Integer idLibro) {
        Connection con;
        PreparedStatement stmTieneEjemplares = null;
        ResultSet rsTieneEjemplares = null;
        boolean resultado = false;

        con = super.getConexion();

        try {
            stmTieneEjemplares = con.prepareStatement("SELECT COUNT (*) as ejemplares " +
                    "from ejemplar e " +
                    "where e.id_libro = ?");
            stmTieneEjemplares.setInt(1, idLibro);
            rsTieneEjemplares = stmTieneEjemplares.executeQuery();

            if (rsTieneEjemplares.next()) {
                resultado = rsTieneEjemplares.getInt("ejemplares") > 0;
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
            this.getFachadaAplicacion().muestraExcepcion(e.getMessage());
        } finally {
            try {
                if (stmTieneEjemplares != null) {
                    stmTieneEjemplares.close();
                }
            } catch (SQLException e) {
                System.out.println("Imposible cerrar cursores");
            }
        }
        return resultado;
    }
}
