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
 */
public class ModeloTablaEjemplares extends AbstractTableModel {

    private List<Ejemplar> ejemplares;
//    private Map<Integer, Prestamo> estadoPrestamoEjemplares;

//    private FachadaBaseDatos fbd;

    public ModeloTablaEjemplares() {
//    public ModeloTablaEjemplares(FachadaBaseDatos fbd) {
//        this.fbd = fbd;
        this.ejemplares = new ArrayList<>();
//        this.estadoPrestamoEjemplares = new HashMap<>();
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

        //        Integer numEjemplarSeleccionado;

        Ejemplar ejemplarSeleccionado = ejemplares.get(row);
//        Prestamo prestamoActivo = ejemplarSeleccionado.getPrestamoActivo();

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
//                numEjemplarSeleccionado = ejemplares.get(row).getNumEjemplar();
//                if (numEjemplarSeleccionado == null || estadoPrestamoEjemplares.get(numEjemplarSeleccionado) == null) {
//                    resultado = null;
//                }
//                else {
//                    resultado = estadoPrestamoEjemplares.get(numEjemplarSeleccionado).getIdUsuario();
//                }

//                resultado = prestamoActivo == null ? null : prestamoActivo.getIdUsuario();
                resultado = ejemplarSeleccionado.getPrestamoActivo().getIdUsuario();
                break;

            case 4: // Fecha de inicio del préstamo
//                numEjemplarSeleccionado = ejemplarSeleccionado.getNumEjemplar();
//                if (numEjemplarSeleccionado == null || estadoPrestamoEjemplares.get(numEjemplarSeleccionado) == null) {
//                    resultado = null;
//                }
//                else {
//                    resultado = estadoPrestamoEjemplares.get(numEjemplarSeleccionado).getFechaInicio();
//                }

//                resultado = prestamoActivo == null ? null : prestamoActivo.getFechaInicio();
                resultado = ejemplarSeleccionado.getPrestamoActivo().getFechaInicio();
                break;

            case 5: // Fecha (máxima) de vencimiento
//                numEjemplarSeleccionado = ejemplarSeleccionado.getNumEjemplar();
//                if (numEjemplarSeleccionado == null || estadoPrestamoEjemplares.get(numEjemplarSeleccionado) == null) {
//                    resultado = null;
//                }
//                else {
//                    String cadenaFechaInicioFormatoIso = estadoPrestamoEjemplares.get(numEjemplarSeleccionado).getFechaInicio();
//
//                    resultado = Utilidades.calculaFechaVencimiento(cadenaFechaInicioFormatoIso);
//                }

//                resultado = prestamoActivo == null ? null : prestamoActivo.getFechaVencimiento();
                resultado = ejemplarSeleccionado.getPrestamoActivo().getFechaVencimiento();
                break;

        }
        return resultado;
    }


    @Override
    public void setValueAt(Object v, int row, int col) {
        Ejemplar ejemplarSeleccionado = ejemplares.get(row);
//        Prestamo prestamoActivo = ejemplarSeleccionado.getPrestamoActivo();

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
                // estadoPrestamoEjemplares.get(ejemplarSeleccionado.getNumEjemplar()).setFechaFin((String) v);
//                ejemplarSeleccionado.getPrestamoActivo().setFechaVencimiento((String) v);
                break;
        }
    }

//    public void setFilas(List<Ejemplar> ejemplares, Map<Integer, Prestamo> estadoPrestamoEjemplares) {
    public void setFilas(List<Ejemplar> ejemplares) {
//        int numeroEjemplar = 0;
//        for (Ejemplar ejemplarActual:ejemplares)
//        {
//            // Si el ejemplar no tiene libro asociado es porque acaba de llegar de la base de datos
//            if(ejemplarActual.getLibro()== null && ejemplarActual.getNumEjemplar() != null)
//
//            {
//                Ejemplar old = this.ejemplares.get(this.ejemplares.indexOf(ejemplarActual));
//                ejemplarActual.setLibro(old.getLibro());
//            }
//        }
        this.ejemplares = ejemplares;

//        this.estadoPrestamoEjemplares = estadoPrestamoEjemplares;

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
        /*
        if (!this.estadoPrestamoEjemplares.containsKey(idEjemplar)) {
            return false;
        }

        return this.estadoPrestamoEjemplares.get(idEjemplar) != null;
         */
    }
}
