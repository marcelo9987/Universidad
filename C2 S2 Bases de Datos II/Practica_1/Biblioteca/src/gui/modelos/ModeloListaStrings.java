/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package gui.modelos;

import java.util.ArrayList;
import java.util.List;

/**
 * @author basesdatos
 */
public class ModeloListaStrings extends javax.swing.AbstractListModel
{
    List<String> elementos;

    public ModeloListaStrings()
    {
        this.elementos = new ArrayList<>();
    }

    public int getSize()
    {
        return this.elementos.size();
    }

    public String getElementAt(int i)
    {
        return elementos.get(i);
    }

    public void nuevoElemento(String e)
    {
        this.elementos.add(e);
        fireIntervalAdded(this, this.elementos.size() - 1, this.elementos.size() - 1);
    }

    public void borrarElemento(int i)
    {
        String e;
        e = this.elementos.get(i);
        this.elementos.remove(i);
        fireIntervalRemoved(this, i, i);
    }

    public void setElementos(List<String> elementos)
    {
        this.elementos = elementos;
        fireContentsChanged(this, 0, elementos.size() - 1);
    }

    public List<String> getElementos()
    {
        return this.elementos;
    }
}
