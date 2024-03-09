package aplicacion.controladores;

import baseDatos.FachadaBaseDatos;
import gui.FachadaGui;

public class GestionPrestamos {
    private final FachadaBaseDatos fbd;
    private final FachadaGui fgui;

    public GestionPrestamos(baseDatos.FachadaBaseDatos fbd, FachadaGui fgui) {
        this.fbd = fbd;
        this.fgui = fgui;
    }

    public void realizarPrestamo(String usuarioSolicitante, Integer idLibro, Integer numEjemplar) 
    {
        if(fbd.consultarNumPrestamosVencidosPorUsuario(usuarioSolicitante)>0)
        {
            fgui.muestraExcepcion("No se puede prestar: El usuario '"+usuarioSolicitante+"' tiene prestamos vencidos");
            return;
        }

        if(fbd.tienePrestamoEnActivoEjemplar(idLibro,numEjemplar))
        {
            fgui.muestraExcepcion("No se puede prestar: El ejemplar "+idLibro+":"+numEjemplar+" ya está prestado");
            return;
        }

        fbd.nuevoPrestamo(usuarioSolicitante, idLibro, numEjemplar);
    }

    public void devolverEjemplar(int idLibro, int numEjemplar)
    {
        if(!fbd.tienePrestamoEnActivoEjemplar(idLibro,numEjemplar))
        {
            fgui.muestraExcepcion("No hay ningún préstamo pendiente para el libro "+idLibro+":"+numEjemplar+". Por lo tanto, no se llevará a cabo ninguna acción");
            return;
        }
        fbd.devolverEjemplar(idLibro, numEjemplar);
    }
}
