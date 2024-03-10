/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package gui.modelos;

import aplicacion.objetos.Ejemplar;
// import baseDatos.FachadaBaseDatos;

import javax.swing.table.AbstractTableModel;
import java.util.*;

/**
 * @author basesdatos
 * @version 2.0
 */
public class ModeloTablaEjemplares extends AbstractTableModel {

    private List<Ejemplar> ejemplares;


    public ModeloTablaEjemplares() {

        this.ejemplares = new ArrayList<>();
    }

    public int getColumnCount() {
        return 6;
    }

    public int getRowCount() {
        return ejemplares.size();
    }

    @Override
    public String getColumnName(int col) {
        String nombre = "";

        switch (col) {
            case 0:
                nombre = "Id";
                break;
            case 1:
                nombre = "Localizador";
                break;
            case 2:
                nombre = "Año de compra";
                break;
            case 3:
                nombre = "Prestado a";
                break;
            case 4: // Fecha de inicio del préstamo
                nombre = "Fecha de inicio";
                break;
            case 5: // Fecha (máxima) de vencimiento
                nombre = "Vence";
        }
        return nombre;
    }

    @Override
    public Class getColumnClass(int col) {
        Class clase = null;

        switch (col) {
            case 0:
                clase = java.lang.Integer.class;
                break;
            case 1:
                clase = java.lang.String.class;
                break;
            case 2:
                clase = java.lang.String.class;
                break;
            case 3: // "Prestado a"
                clase = java.lang.String.class;
                break;
            case 4: // Fecha de inicio del préstamo
                clase = java.lang.String.class;
                break;
            case 5: // Fecha (máxima) de vencimiento
                clase = java.lang.String.class;
                break;
        }
        return clase;
    }

    @Override
    public boolean isCellEditable(int row, int col) {

        switch (col){
            case 1:
            case 2:
                if (tienePrestamosActivos(row)) {
                    return false;
                } else {
                    return true;
                }

            default:
                return false;
        }

    }

    public Object getValueAt(int row, int col) {
        Object resultado = null;

        Ejemplar ejemplarSeleccionado = ejemplares.get(row);

        switch (col) {
            case 0:
                resultado = ejemplarSeleccionado.getNumEjemplar();
                break;
            case 1:
                resultado = ejemplarSeleccionado.getLocalizador();
                break;
            case 2:
                resultado = ejemplarSeleccionado.getAnoCompra();
                break;
            case 3: // "Prestado a"
                resultado = ejemplarSeleccionado.getPrestamoActivo().getIdUsuario();
                break;

            case 4: // Fecha de inicio del préstamo
                resultado = ejemplarSeleccionado.getPrestamoActivo().getFechaInicio();
                break;

            case 5: // Fecha (máxima) de vencimiento
                resultado = ejemplarSeleccionado.getPrestamoActivo().getFechaVencimiento();
                break;

        }
        return resultado;
    }


    @Override
    public void setValueAt(Object v, int row, int col) {
        Ejemplar ejemplarSeleccionado = ejemplares.get(row);

        switch (col) {
            case 0:
                ejemplarSeleccionado.setLibro((aplicacion.objetos.Libro) v);
                break;
            case 1:
                ejemplarSeleccionado.setLocalizador((String) v);
                break;
            case 2:
                ejemplarSeleccionado.setAnoCompra((String) v);
                break;
            case 3: // "Prestado a"
//                estadoPrestamoEjemplares.get(ejemplarSeleccionado.getNumEjemplar()).setIdUsuario((String) v);
                ejemplarSeleccionado.getPrestamoActivo().setIdUsuario((String) v);
                break;
            case 4: // Fecha de inicio del préstamo
//                estadoPrestamoEjemplares.get(ejemplarSeleccionado.getNumEjemplar()).setFechaInicio((String) v);
                ejemplarSeleccionado.getPrestamoActivo().setFechaInicio((String) v);
                break;
            case 5: // Fecha (máxima) de vencimiento
                break;
        }
    }

    public void setFilas(List<Ejemplar> ejemplares) {

        this.ejemplares = ejemplares;
        fireTableDataChanged();
    }

    public void nuevoEjemplar(Ejemplar e) {
        this.ejemplares.add(e);
        fireTableRowsInserted(this.ejemplares.size() - 1, this.ejemplares.size() - 1);
    }

    public void borrarEjemplar(int indice) {
        this.ejemplares.remove(indice);
        fireTableRowsDeleted(indice, indice);
    }

    public List<Ejemplar> getFilas() {
        return this.ejemplares;
    }

    public Ejemplar obtenerEjemplar(int indice) {
        return this.ejemplares.get(indice);
    }

    public boolean tienePrestamosActivos(int indice) {
        return this.ejemplares.get(indice).getPrestamoActivo ().esPrestamoActivo();
    }
}
