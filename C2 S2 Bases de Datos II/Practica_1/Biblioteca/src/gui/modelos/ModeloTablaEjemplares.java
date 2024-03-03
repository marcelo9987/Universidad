/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package gui.modelos;

import aplicacion.objetos.Ejemplar;
import aplicacion.objetos.Prestamo;
// import baseDatos.FachadaBaseDatos;

import javax.swing.table.AbstractTableModel;
import java.util.*;

/**
 * @author basesdatos
 */
public class ModeloTablaEjemplares extends AbstractTableModel {

    private List<Ejemplar> ejemplares;
    private Map<Integer, Prestamo> prestamosActivos;

//    private FachadaBaseDatos fbd;

    public ModeloTablaEjemplares() {
//    public ModeloTablaEjemplares(FachadaBaseDatos fbd) {
//        this.fbd = fbd;
        this.ejemplares = new ArrayList<>();
        this.prestamosActivos = new HashMap<>();
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
            case 4:
                nombre = "Fecha de inicio";
                break;
            case 5:
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
            case 3:
                clase = java.lang.String.class;
                break;
            case 4:
                clase = java.lang.String.class;
                break;
            case 5:
                clase = java.lang.String.class;
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
                resultado = ejemplares.get(row).getNumEjemplar();
                break;
            case 1:
                resultado = ejemplares.get(row).getLocalizador();
                break;
            case 2:
                resultado = ejemplares.get(row).getAnoCompra();
                break;
            case 3:
                Integer id = ejemplares.get(row).getNumEjemplar();
                if (id == null || prestamosActivos.get(id) == null) {
                    resultado = null;
                }
                else {
                    resultado = prestamosActivos.get(id).getIdUsuario();
                }

                break;
            case 4:
                Integer id2 = ejemplares.get(row).getNumEjemplar();
                if (id2 == null || prestamosActivos.get(id2) == null) {
                    resultado = null;
                }
                else {
                    resultado = prestamosActivos.get(id2).getFechaInicio();
                }
                //resultado = prestamos.get(ejemplares.get(row).getNumEjemplar()).getFechaInicio();
                break;
            case 5:
                Integer id3 = ejemplares.get(row).getNumEjemplar();
                if (id3 == null || prestamosActivos.get(id3) == null) {
                    resultado = null;
                }
                else {
                    //Tengo que sumarle 30 días a la fecha de inicio
                    Calendar fechaInicio = Calendar.getInstance();
                    String fechaInicioSinFormato = prestamosActivos.get(id3).getFechaInicio();

                    fechaInicio.set(Integer.parseInt(fechaInicioSinFormato.substring(0, 4)), Integer.parseInt(fechaInicioSinFormato.substring(5, 7)), Integer.parseInt(fechaInicioSinFormato.substring(8, 10)));
                    fechaInicio.add(Calendar.DAY_OF_MONTH, 30);
                    resultado = fechaInicio.get(Calendar.YEAR) + "-" + fechaInicio.get(Calendar.MONTH) + "-" + fechaInicio.get(Calendar.DAY_OF_MONTH);
                }
                //resultado = prestamos.get(ejemplares.get(row).getNumEjemplar()).getFechaFin();
                break;
        }
        return resultado;
    }

    @Override
    public void setValueAt(Object v, int row, int col) {
        Ejemplar ejemplar = ejemplares.get(row);

        switch (col) {
            case 0:
                ejemplar.setLibro((aplicacion.objetos.Libro) v);
                break;
            case 1:
                ejemplar.setLocalizador((String) v);
                break;
            case 2:
                ejemplar.setAnoCompra((String) v);
                break;
            case 3:
                prestamosActivos.get(ejemplar.getNumEjemplar()).setIdUsuario((String) v);
                break;
            case 4:
                prestamosActivos.get(ejemplar.getNumEjemplar()).setFechaInicio((String) v);
                break;
            case 5:
                prestamosActivos.get(ejemplar.getNumEjemplar()).setFechaFin((String) v);
                break;
        }
    }

    public void setFilas(List<Ejemplar> ejemplares, Map<Integer, Prestamo> prestamosActivos) {
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

        this.prestamosActivos = prestamosActivos;

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

    public Ejemplar obtenerEjemplar(int i) {
        return this.ejemplares.get(i);
    }

}
