/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package gui.modelos;

import aplicacion.objetos.Libro;

import javax.swing.table.*;
import java.util.ArrayList;
import java.util.List;

/**
 * @author basesdatos
 */
public class ModeloTablaLibros extends AbstractTableModel
{
    private List<Libro> libros;

    public ModeloTablaLibros()
    {
        this.libros = new ArrayList<>();
    }

    public int getColumnCount()
    {
        return 5;
    }

    public int getRowCount()
    {
        return libros.size();
    }

    @Override
    public String getColumnName(int col)
    {
        String nombre = "";

        switch (col)
        {
            case 0:
                nombre = "Id";
                break;
            case 1:
                nombre = "Autores";
                break;
            case 2:
                nombre = "Título";
                break;
            case 3:
                nombre = "Editorial";
                break;
            case 4:
                nombre = "año";
                break;
        }
        return nombre;
    }

    @Override
    public Class getColumnClass(int col)
    {
        Class clase = null;

        switch (col)
        {
            case 0:
                clase = java.lang.Integer.class;
                break;
            case 1:
                clase = java.lang.String.class;
                break;
            case 2:
                clase = java.lang.String.class;
                break;
            case 3:
                clase = java.lang.String.class;
                break;
            case 4:
                clase = java.lang.String.class;
                break;
        }
        return clase;
    }

    @Override
    public boolean isCellEditable(int row, int col)
    {
        return false;
    }

    public Object getValueAt(int row, int col)
    {
        Object resultado = null;

        switch (col)
        {
            case 0:
                resultado = libros.get(row).getIdLibro();
                break;
            case 1:
                resultado = libros.get(row).getAutoresAsString();
                break;
            case 2:
                resultado = libros.get(row).getTitulo();
                break;
            case 3:
                resultado = libros.get(row).getEditorial();
                break;
            case 4:
                resultado = libros.get(row).getAno();
                break;
        }
        return resultado;
    }

    public void setFilas(List<Libro> libros)
    {
        this.libros = libros;
        fireTableDataChanged();
    }

    public Libro obtenerLibro(int i)
    {
        return this.libros.get(i);
    }

}
