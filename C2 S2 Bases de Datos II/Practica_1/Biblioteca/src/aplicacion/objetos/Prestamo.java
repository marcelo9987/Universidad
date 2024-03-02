package aplicacion.objetos;

public class Prestamo {
    private Integer idLibro;
    private Integer idEjemplar;
    private String idUsuario;
    private String fechaInicio;
    private String fechaFin;

    public Prestamo(Integer idLibro, Integer idEjemplar, String idUsuario, String fechaInicio, String fechaFin) {
        this.idLibro = idLibro;
        this.idEjemplar = idEjemplar;
        this.idUsuario = idUsuario;
        this.fechaInicio = fechaInicio;
        this.fechaFin = fechaFin;
    }


    public Integer getIdLibro() {
        return idLibro;
    }

    public Integer getIdEjemplar() {
        return idEjemplar;
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

    public void setFechaFin(String fechaFin) {
        this.fechaFin = fechaFin;
    }
}
