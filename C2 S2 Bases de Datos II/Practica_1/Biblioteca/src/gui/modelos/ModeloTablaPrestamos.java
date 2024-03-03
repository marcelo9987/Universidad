/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package gui.modelos;

import aplicacion.objetos.Usuario;
import baseDatos.FachadaBaseDatos;

import javax.swing.table.AbstractTableModel;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * @author basesdatos
 */
public class ModeloTablaPrestamos extends AbstractTableModel {
    private List<Usuario> usuarios;
    private Map<String, Integer> numPrestamosVencidosPorUsuario;


    //    public ModeloTablaPrestamos(FachadaBaseDatos fbd)
    public ModeloTablaPrestamos() {
        this.usuarios = new ArrayList<>();
        this.numPrestamosVencidosPorUsuario = new HashMap<>();
    }

    public int getColumnCount() {
        return 4;
    }

    public int getRowCount() {
        return usuarios.size();
    }

    @Override
    public String getColumnName(int col) {
        String nombre = "";

        switch (col) {
            case 0:
                nombre = "Id";
                break;
            case 1:
                nombre = "Nombre";
                break;
            case 2:
                nombre = "Email";
                break;
            case 3:
                nombre = "Prestamos vencidos";
                break;
        }
        return nombre;
    }

    @Override
    public Class getColumnClass(int col) {
        Class clase = null;

        switch (col) {
            case 0:
                clase = String.class;
                break;
            case 1:
                clase = String.class;
                break;
            case 2:
                clase = String.class;
                break;
            case 3:
                clase = Integer.class;
                break;
        }
        return clase;
    }

    @Override
    public boolean isCellEditable(int row, int col) {
        return col > 0;
    }

    public Object getValueAt(int row, int col) {
        Object resultado = null;

        switch (col) {
            case 0:
                resultado = usuarios.get(row).getIdUsuario();
                break;
            case 1:
                resultado = usuarios.get(row).getNombre();
                break;
            case 2:
                resultado = usuarios.get(row).getEmail();
                break;
            case 3:
                String idUsuario = usuarios.get(row).getIdUsuario();
                resultado = numPrestamosVencidosPorUsuario.get(idUsuario);
                break;
        }
        return resultado;
    }


    public void setFilas(List<Usuario> usuarios, Map<String, Integer> numPrestamosVencidosPorUsuario) {
        this.usuarios = usuarios;
        this.numPrestamosVencidosPorUsuario = numPrestamosVencidosPorUsuario;

        fireTableDataChanged();
    }


}
