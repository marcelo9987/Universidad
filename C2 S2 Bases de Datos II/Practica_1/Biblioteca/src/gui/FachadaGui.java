/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gui;

import aplicacion.objetos.Categoria;
import aplicacion.objetos.Libro;
import aplicacion.objetos.Prestamo;
import gui.formularios.*;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * @author alumno
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


    public void iniciaVista()
    {
        VAutentificacion va;

        va = new VAutentificacion(vp, true, fa);
        vp.setVisible(true);
        va.setVisible(true);
    }


    public void visualizaLibro(Libro l, Map<Integer, Prestamo> prestamosActivos, List<String> restoCategorias)
    {
        VLibro vl;
        List<String> categorias = new ArrayList<>();

        for (Categoria c : l.getCategorias())
        {
            categorias.add(c.getNombre());
        }

        vl = new VLibro(vp, true, fa, l, prestamosActivos, categorias, restoCategorias);
        vl.setVisible(true);
    }

    public void nuevoLibro(List<String> restoCategorias)
    {
        VLibro vl;

        vl = new VLibro(vp, true, fa, restoCategorias);
        vl.setVisible(true);
    }

    public void gestionUsuarios()
    {
        VGesUsuarios vu = new VGesUsuarios(vp, true, fa);
        vu.setVisible(true);
    }

    public void muestraExcepcion(String txtExcepcion)
    {
        VAviso va;

        va = new VAviso(vp, true, txtExcepcion);
        va.setVisible(true);
    }


    public void gestionCategorias()
    {
        VGesCategorias vc = new VGesCategorias(vp, true, fa);
        vc.setVisible(true);
    }

    public void gestionPrestamos()
    {
        VGesPrestamos vp = new VGesPrestamos(this.vp, true, fa);
        vp.setVisible(true);
    }
}
