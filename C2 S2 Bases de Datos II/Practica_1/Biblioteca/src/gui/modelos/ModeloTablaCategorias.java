/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package gui.modelos;

import aplicacion.objetos.Categoria;

import javax.swing.table.*;
import java.util.ArrayList;
import java.util.List;

/**
 * @author Marcelo Fort Muñoz
 */
public class ModeloTablaCategorias extends AbstractTableModel
{

    private List<Categoria> categorias;

    public ModeloTablaCategorias()
    {
        this.categorias = new ArrayList<>();
    }

    @Override
    public int getColumnCount()
    {
        return 1;
    }
    @Override
    public int getRowCount()
    {
        return categorias.size();
    }



    @Override
    public String getColumnName(int column)
    {
        switch (column)
        {
            case 0:
                return "Nombre";
//            case 1:
//                return "Descripcion";
            default:
                return "";
        }
    }

    @Override
    public Object getValueAt(int fila, int columna)
    {
        switch (columna)
        {
            case 0:
                return categorias.get(fila).getNombre();
//            case 1:
//                return categorias.get(fila).getDescripcion();
            default:
                return "";
        }
    }

    public void setFilas(List<Categoria> categorias)
    {
        this.categorias = categorias;
        fireTableDataChanged();
    }

    public Categoria obtenerCategoria(int i)
    {
        return this.categorias.get(i);
    }
}
