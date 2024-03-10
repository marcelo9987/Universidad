package aplicacion.objetos;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


import java.util.ArrayList;
import java.util.List;

/**
 * @author basesdatos
 * @author Marcelo F.M.
 * @version 2.0
 */
public class Libro {

    private final Integer idLibro;
    private final String titulo;
    private final String isbn;
    private final String editorial;
    private final Integer paginas;
    private final String ano;
    private List<String> autores;
    private final List<Categoria> categorias;
    private final List<Ejemplar> ejemplares;

    public Libro(Integer idLibro, String titulo, String isbn, String editorial, Integer paginas, String ano) {
        this.idLibro = idLibro;
        this.titulo = titulo;
        this.isbn = isbn;
        this.editorial = editorial;
        this.paginas = paginas;
        this.ano = ano;
        autores = new ArrayList<>();
        categorias = new ArrayList<>();
        ejemplares = new ArrayList<>();
    }

    public Integer getIdLibro() {
        return this.idLibro;
    }

    public String getTitulo() {
        return this.titulo;
    }

    public String getIsbn() {
        return this.isbn;
    }

    public String getEditorial() {
        return this.editorial;
    }

    public Integer getPaginas() {
        return this.paginas;
    }

    public String getAno() {
        return this.ano;
    }

    public List<String> getAutores() {
        return this.autores;
    }

    public void setAutores(List<String> autores) {
        this.autores = autores;
    }

    public void addAutor(String autor) {
        this.autores.add(autor);
    }

    public List<Categoria> getCategorias() {
        return this.categorias;
    }

    public void addCategoria(Categoria categoria) {
        this.categorias.add(categoria);
    }

    public List<Ejemplar> getEjemplares() {
        return this.ejemplares;
    }

    public void addEjemplar(Ejemplar ejemplar) {
        this.ejemplares.add(ejemplar);
    }

    public String getAutoresAsString() {
        String resultado = "";
        Boolean inicial = true;

        for (String a : this.autores) {
            if (inicial) {
                resultado = a;
                inicial = false;
            }
            else {
                resultado = resultado + ", " + a;
            }
        }
        return resultado;
    }


}
