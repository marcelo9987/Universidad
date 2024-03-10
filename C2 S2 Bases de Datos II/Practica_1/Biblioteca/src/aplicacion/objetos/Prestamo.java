package aplicacion.objetos;

import auxiliares.Utilidades;

import java.time.LocalDate;

/**
 * @version 1.0 (global: 2.0)
 * @since 2.0 global
 */
public class Prestamo {

    private String idUsuario;
    private String fechaInicio;

    private String fechaFin;


    public Prestamo(/*Integer idLibro, Integer idEjemplar, */ String idUsuario, String fechaInicio, String fechaFin) {
        this.idUsuario = idUsuario;
        this.fechaInicio = fechaInicio;
        this.fechaFin = fechaFin;
    }

    public String getIdUsuario() {
        return idUsuario;
    }

    public void setIdUsuario(String idUsuario) {
        this.idUsuario = idUsuario;
    }


    public String getFechaInicio() {
        return fechaInicio;
    }

    public void setFechaInicio(String fechaInicio) {
        this.fechaInicio = fechaInicio;
    }


    public String getFechaFin() {
        return fechaFin;
    }


    public String getFechaVencimiento() {
        return Prestamo.calculaFechaVencimiento(fechaInicio);
    }

    public boolean esPrestamoActivo() {
        return Prestamo.esPrestamoActivo(this);
    }


    public static String calculaFechaVencimiento(String cadenaFechaInicioFormatoIso) {
        if (cadenaFechaInicioFormatoIso == null || cadenaFechaInicioFormatoIso.isEmpty()) {
            return null;
        }

        LocalDate fechaInicio = LocalDate.parse(cadenaFechaInicioFormatoIso);
        LocalDate fechaDevolucion = fechaInicio.plusDays(30);

        return fechaDevolucion.toString();

    }

    private static boolean esPrestamoActivo(Prestamo prestamo) {

        if (prestamo == null) {
            return false;
        }

        if (Utilidades.isEmpty(prestamo.fechaInicio)) {
            return false;
        }

        if (Utilidades.isEmpty(prestamo.fechaFin)) {
            return true;
        }

        return false;
    }

}
