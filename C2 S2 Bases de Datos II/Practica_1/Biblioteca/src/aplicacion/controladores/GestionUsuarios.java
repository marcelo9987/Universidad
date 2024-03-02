/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package aplicacion.controladores;

import aplicacion.enums.TipoUsuario;
import aplicacion.objetos.Usuario;
import gui.FachadaGui;
import baseDatos.FachadaBaseDatos;

import java.util.List;

/**
 * @author basesdatos
 */
public class GestionUsuarios {

    FachadaGui fgui; // Fachada del GUI
    FachadaBaseDatos fbd; // Fachada de la Base de Datos


    public GestionUsuarios(FachadaGui fgui, FachadaBaseDatos fbd) {
        this.fgui = fgui;
        this.fbd = fbd;
    }


    public Boolean comprobarAutentificacion(String idUsuario, String clave) {
        Usuario u;

        u = fbd.validarUsuario(idUsuario, clave);
        if (u != null) {
            return u.getTipoUsuario() == TipoUsuario.Administrador;
        }
        else {
            return false;
        }
    }

    public List<Usuario> consultarUsuarios(String id, String nombre) {
        return fbd.consultarUsuarios(id, nombre);
    }

    public void insertarUsuario(Usuario usuario) {
        if (usuario.getIdUsuario().isBlank()) {
            String nombreYapellidos = usuario.getNombre();
            String nombreSinApellidos = nombreYapellidos.split(" ")[0];
            String idUsuario = nombreSinApellidos.charAt(0) + usuario.getNombre().split(" ")[1];
            Usuario usuarioConId = new Usuario(idUsuario, usuario.getClave(), usuario.getNombre(), usuario.getDireccion(), usuario.getEmail(), usuario.getTipoUsuario());
            fbd.insertarUsuario(usuarioConId);
        }
        else {
            fbd.insertarUsuario(usuario);
        }

    }

    public void actualizarUsuario(Usuario usuarioAguardar) {
        fbd.actualizarUsuario(usuarioAguardar);
    }

    public void borrarUsuario(String text) {
        fbd.borrarUsuario(text);
    }
}
