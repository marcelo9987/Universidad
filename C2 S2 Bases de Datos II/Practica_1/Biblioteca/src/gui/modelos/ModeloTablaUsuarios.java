
package gui.modelos;

import aplicacion.enums.TipoUsuario;
import aplicacion.objetos.Usuario;

import javax.swing.table.*;
import java.util.ArrayList;
import java.util.List;

/**
 * @author Marcelo F.M.
 * @version 1.0 (global: 2.0)
 * @since global: 2.0
 */
public class ModeloTablaUsuarios extends AbstractTableModel
{
    private List<Usuario> usuarios;

    public ModeloTablaUsuarios()
    {
        this.usuarios = new ArrayList<>();
    }

    @Override
    public int getColumnCount()
    {
        return 4;
    }

    @Override
    public int getRowCount()
    {
        return usuarios.size();
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
                nombre = "Nombre";
                break;
            case 2:
                nombre = "E-mail";
                break;
            case 3:
                nombre = "Tipo";
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
            case 0: // Id
                clase = java.lang.String.class;
                break;
            case 1: // Nombre
                clase = java.lang.String.class;
                break;
            case 2: // E-mail
                clase = java.lang.String.class;
                break;
            case 3: // Tipo
                clase = TipoUsuario.class;
                break;
        }
        return clase;
    }

    @Override
    public Object getValueAt(int row, int col)
    {
        Object resultado = null;
        switch (col)
        {
            case 0: // Id
                resultado = usuarios.get(row).getIdUsuario();
                break;
            case 1: // Nombre
                resultado = usuarios.get(row).getNombre();
                break;
            case 2: // E-mail
                resultado = usuarios.get(row).getEmail();
                break;
            case 3: // Tipo
                resultado = usuarios.get(row).getTipoUsuario();
                break;
        }
        return resultado;
    }

    public void setFilas(List<Usuario> usuarios)
    {
        this.usuarios = usuarios;
        fireTableDataChanged();
    }

    public Usuario obtenerUsuario(int i)
    {
        return this.usuarios.get(i);
    }
}

       
