package gui;

import aplicacion.objetos.Categoria;
import aplicacion.objetos.Ejemplar;
import aplicacion.objetos.Libro;
import gui.formularios.*;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Profesorado asignatura bases de datos II
 * @author Marcelo F.M.
 * @version 2.0
 */
public class FachadaGui
{
    aplicacion.FachadaAplicacion fa;
    VPrincipal vp;

    public FachadaGui(aplicacion.FachadaAplicacion fa)
    {
        this.fa = fa;
        this.vp = new VPrincipal(fa);
    }


    /**
     * Inicia la aplicación y lanza el formulario de autentificación
     */
    public void iniciaVista()
    {
        VAutentificacion va;

        va = new VAutentificacion(vp, true, fa);
        vp.setVisible(true);
        va.setVisible(true);
    }


    /**
     * Muestra la pantalla de edición de un libro
     * @param libro Libro a editar
     * @param restoCategorias Categorías
     */
    public void visualizaLibro(Libro libro, List<String> restoCategorias)
    {
        VLibro vl;
        List<String> categorias = new ArrayList<>();

        for (Categoria c : libro.getCategorias())
        {
            categorias.add(c.getNombre());
        }

        vl = new VLibro(vp, true, fa, libro, categorias, restoCategorias);
        vl.setVisible(true);
    }

    /**
     * Muestra la pantalla de edición de libro pero para un libro nuevo
     * @param restoCategorias Categorías
     */
    public void nuevoLibro(List<String> restoCategorias)
    {
        VLibro vl;

        vl = new VLibro(vp, true, fa, restoCategorias);
        vl.setVisible(true);
    }

    /**
     * Muestra la pantalla de gestión de usuarios
     */
    public void gestionUsuarios()
    {
        VGesUsuarios vu = new VGesUsuarios(vp, true, fa);
        vu.setVisible(true);
    }


    /**
     * Muestra por pantalla una ventana de aviso
     * @param txtExcepcion Texto del aviso
     */
    public void muestraExcepcion(String txtExcepcion)
    {
        VAviso va;

        va = new VAviso(vp, true, txtExcepcion);
        va.setVisible(true);
    }


    /**
     * Muestra la pantalla de gestión de categorías
     */
    public void gestionCategorias()
    {
        VGesCategorias vc = new VGesCategorias(vp, true, fa);
        vc.setVisible(true);
    }


    /**
     * Muestra la pantalla de gestión de préstamos
     * @param ejemplarAprestar Ejemplar a prestar
     */
    public void gestionPrestamos(Ejemplar ejemplarAprestar)
    {
        VGesPrestamos vp = new VGesPrestamos(this.vp, true, fa, ejemplarAprestar);
        vp.setVisible(true);
    }
}
