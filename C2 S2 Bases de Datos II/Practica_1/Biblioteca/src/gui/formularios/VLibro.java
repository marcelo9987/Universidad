/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * VLibro.java
 *
 * Created on 16-feb-2011, 18:17:07
 */

package gui.formularios;

import aplicacion.objetos.Libro;
import aplicacion.objetos.Ejemplar;
import auxiliares.IntegerFormatter;
import gui.modelos.ModeloListaStrings;
import gui.modelos.ModeloTablaEjemplares;
import auxiliares.Utilidades;

import javax.swing.*;
import java.awt.*;
import java.util.*;
import java.util.List;

/**
 * @author basesdatos
 */
public class VLibro extends javax.swing.JDialog {

    private Integer idLibro;
    private List<Integer> ejemplaresBorrados;
    private VPrincipal padre;
    private aplicacion.FachadaAplicacion fa;

    /**
     * Creates new form VLibro
     */

    // Constructor para libros aún NO existentes en la BD
    public VLibro(java.awt.Frame parent, boolean modal, aplicacion.FachadaAplicacion fa, List<String> restoCategorias) {
        super(parent, modal);
        this.fa = fa;
        initComponents();
        this.padre = (VPrincipal) parent;

        this.idLibro = null;

        // --

        // --

        btnActualizarCategoriasLibro.setEnabled(false);
        btnActualizarEjemplaresLibro.setEnabled(false);
        btnBorrarLibro.setEnabled(false);

        // --

        // Categorías no seleccionadas
        ModeloListaStrings mListaRC = new ModeloListaStrings();
        lstRestoCategorias.setModel(mListaRC);
        mListaRC.setElementos(restoCategorias);
        if (mListaRC.getSize() > 0) {
            lstRestoCategorias.setSelectedIndex(0);
            btnSiAsignarCategoria.setEnabled(true);
        }
        else {
            btnSiAsignarCategoria.setEnabled(false);
        }

        // --

        // Categorías seleccionadas
        btnNoAsignarCategoria.setEnabled(false);

        // --

        // Ejemplares
//        btnBorrarEjemplar.setEnabled(false);

        gestionarBotonesPrestamos();

        this.ejemplaresBorrados = new ArrayList<>();

        // --
    }

    // Constructor para libros ya existentes en la BD
//    public VLibro(java.awt.Frame parent, boolean modal, aplicacion.FachadaAplicacion fa, Libro libro, Map<Integer, Prestamo> estadoPrestamoEjemplares, List<String> categorias, List<String> restoCategorias) {
    public VLibro(java.awt.Frame parent, boolean modal, aplicacion.FachadaAplicacion fa, Libro libro, List<String> categorias, List<String> restoCategorias) {
        super(parent, modal);
        this.fa = fa;
        initComponents();
        this.padre = (VPrincipal) parent;

        this.idLibro = libro.getIdLibro();

        // --
        // Datos básicos del libro
        textoAno.setText(libro.getAno());

        textoEditorial.setText(libro.getEditorial());
        textoIsbn.setText(libro.getIsbn());

        /* INI controlar nulos en páginas 2024-03-09 */
        textoPaginas.setText(libro.getPaginas() == null ? null : libro.getPaginas().toString());
        /* FIN controlar nulos en páginas 2024-03-09 */

        textoTitulo.setText(libro.getTitulo());
        textoId.setText(idLibro.toString());

        // --

        // --

        ModeloListaStrings mListaAutores = new ModeloListaStrings();
        lstAutores.setModel(mListaAutores);
        mListaAutores.setElementos(libro.getAutores());
        if (mListaAutores.getSize() > 0) {
            lstAutores.setSelectedIndex(0);
            btnBorrarAutor.setEnabled(true);
        }
        else {
            btnBorrarAutor.setEnabled(false);
        }

        // --

        // Categorías no seleccionadas
        ModeloListaStrings mListaRC = new ModeloListaStrings();
        lstRestoCategorias.setModel(mListaRC);
        mListaRC.setElementos(restoCategorias);
        if (mListaRC.getSize() > 0) {
            lstRestoCategorias.setSelectedIndex(0);
            btnSiAsignarCategoria.setEnabled(true);
        }
        else {
            btnSiAsignarCategoria.setEnabled(false);
        }

        // --

        // Categorías seleccionadas
        ModeloListaStrings mListaC = new ModeloListaStrings();
        lstCategoriasLibro.setModel(mListaC);
        mListaC.setElementos(categorias);
        if (mListaC.getSize() > 0) {
            lstCategoriasLibro.setSelectedIndex(0);
            btnNoAsignarCategoria.setEnabled(true);
        }
        else {
            btnNoAsignarCategoria.setEnabled(false);
        }

        // --

        // Ejemplares
        ModeloTablaEjemplares mTEjemplares = new ModeloTablaEjemplares();
//        ModeloTablaEjemplares mTEjemplares = new ModeloTablaEjemplares(fa.getFachadaBaseDeDatos());
        tablaEjemplares.setModel(mTEjemplares);

//        mTEjemplares.setFilas(libro.getEjemplares(), estadoPrestamoEjemplares);
        mTEjemplares.setFilas(libro.getEjemplares());

        if (mTEjemplares.getRowCount() > 0) {
            tablaEjemplares.setRowSelectionInterval(0, 0);
//            btnBorrarEjemplar.setEnabled(true);
        }
//        else {
//            btnBorrarEjemplar.setEnabled(false);
//        }

        gestionarBotonesPrestamos();

        this.ejemplaresBorrados = new ArrayList<>();

        // --
    }

    /**
     * This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        panelLibro = new javax.swing.JTabbedPane();
        panelGeneralAutores = new javax.swing.JPanel();
        jLabel2 = new javax.swing.JLabel();
        textoTitulo = new javax.swing.JTextField();
        jLabel3 = new javax.swing.JLabel();
        textoIsbn = new javax.swing.JTextField();
        jLabel4 = new javax.swing.JLabel();
        textoEditorial = new javax.swing.JTextField();
        jLabel5 = new javax.swing.JLabel();

        Dimension tamañoPantalla = Toolkit.getDefaultToolkit().getScreenSize();
        int xMedio = tamañoPantalla.width/2;
        int yMedio = tamañoPantalla.height/2;

        setLocation(new java.awt.Point(xMedio-300, yMedio-250));

        /* INI Integer fields 2024-03-09 */
        //textoPaginas = new javax.swing.JTextField();
        textoPaginas = new JFormattedTextField(IntegerFormatter.getNumberFieldFormatter(0, 10000));
        /* FIN Integer fields 2024-03-09 */

        jLabel6 = new javax.swing.JLabel();

        /* INI Integer fields 2024-03-09 */
        // textoAno = new javax.swing.JTextField();
        textoAno = new JFormattedTextField(IntegerFormatter.getNumberFieldFormatter(1, 2100));
        /* FIN Integer fields 2024-03-09 */

        jScrollPane1 = new javax.swing.JScrollPane();
        lstAutores = new javax.swing.JList();
        jLabel7 = new javax.swing.JLabel();
        textoNuevoAutor = new javax.swing.JTextField();
        btnNuevoAutor = new javax.swing.JButton();
        btnBorrarAutor = new javax.swing.JButton();
        btnActualizarLibro = new javax.swing.JButton();
        jLabel1 = new javax.swing.JLabel();
        textoId = new javax.swing.JTextField();
        panelCategorias = new javax.swing.JPanel();
        jLabel8 = new javax.swing.JLabel();
        jLabel9 = new javax.swing.JLabel();
        jScrollPane2 = new javax.swing.JScrollPane();
        lstRestoCategorias = new javax.swing.JList();
        jScrollPane3 = new javax.swing.JScrollPane();
        lstCategoriasLibro = new javax.swing.JList();
        btnSiAsignarCategoria = new javax.swing.JButton();
        btnNoAsignarCategoria = new javax.swing.JButton();
        btnActualizarCategoriasLibro = new javax.swing.JButton();
        panelEjemplares = new javax.swing.JPanel();
        jScrollPane4 = new javax.swing.JScrollPane();

        /* INI tabla editable sólo para los ejemploares no prestados 2024-03-09 */
//        tablaEjemplares = new javax.swing.JTable();
        tablaEjemplares = new javax.swing.JTable() {
            public boolean isCellEditable(int row, int column) {
                return getModel().isCellEditable(row, column);
            }
        };

        /* FIN tabla editable sólo para los ejemploares no prestados 2024-03-09 */

        btnBorrarEjemplar = new javax.swing.JButton();
        btnNuevoEjemplar = new javax.swing.JButton();
        btnActualizarEjemplaresLibro = new javax.swing.JButton();
        btnPrestarLibro = new javax.swing.JButton();
        btnDevolverLibro = new javax.swing.JButton();
        btnRefrescarEjemplares = new javax.swing.JButton();
        btnBorrarLibro = new javax.swing.JButton();
        btnSalir = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        setTitle("Gestión de libros");
        setResizable(false);

        jLabel2.setText("Título:");

        jLabel3.setText("Isbn:");

        jLabel4.setText("Editorial:");

        jLabel5.setText("Páginas:");

        jLabel6.setText("Año:");

        lstAutores.setModel(new ModeloListaStrings());
        lstAutores.setSelectionMode(javax.swing.ListSelectionModel.SINGLE_SELECTION);
        jScrollPane1.setViewportView(lstAutores);

        jLabel7.setText("Autores:");

        btnNuevoAutor.setText("Añadir");
        btnNuevoAutor.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnNuevoAutorActionPerformed(evt);
            }
        });

        btnBorrarAutor.setText("Borrar");
        btnBorrarAutor.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnBorrarAutorActionPerformed(evt);
            }
        });

        btnActualizarLibro.setText("Actualizar");
        btnActualizarLibro.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnActualizarLibroActionPerformed(evt);
            }
        });

        jLabel1.setText("Id:");

        textoId.setEditable(false);
        textoId.setEnabled(false);

//        btnBorrarEjemplar.setEnabled(false);

        javax.swing.GroupLayout panelGeneralAutoresLayout = new javax.swing.GroupLayout(panelGeneralAutores);
        panelGeneralAutores.setLayout(panelGeneralAutoresLayout);
        panelGeneralAutoresLayout.setHorizontalGroup(
                panelGeneralAutoresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(panelGeneralAutoresLayout.createSequentialGroup()
                                .addContainerGap()
                                .addGroup(panelGeneralAutoresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addGroup(panelGeneralAutoresLayout.createSequentialGroup()
                                                .addComponent(jLabel2)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addComponent(textoTitulo, javax.swing.GroupLayout.DEFAULT_SIZE, 560, Short.MAX_VALUE))
                                        .addGroup(panelGeneralAutoresLayout.createSequentialGroup()
                                                .addComponent(jLabel3)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addComponent(textoIsbn, javax.swing.GroupLayout.PREFERRED_SIZE, 152, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                                .addComponent(jLabel4)
                                                .addGap(51, 51, 51)
                                                .addComponent(textoEditorial, javax.swing.GroupLayout.DEFAULT_SIZE, 298, Short.MAX_VALUE))
                                        .addGroup(panelGeneralAutoresLayout.createSequentialGroup()
                                                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 160, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addGroup(panelGeneralAutoresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                                        .addComponent(btnBorrarAutor, javax.swing.GroupLayout.Alignment.LEADING)
                                                        .addGroup(javax.swing.GroupLayout.Alignment.LEADING, panelGeneralAutoresLayout.createSequentialGroup()
                                                                .addComponent(btnNuevoAutor)
                                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                                                .addComponent(textoNuevoAutor, javax.swing.GroupLayout.DEFAULT_SIZE, 354, Short.MAX_VALUE))
                                                        .addComponent(btnActualizarLibro)))
                                        .addGroup(panelGeneralAutoresLayout.createSequentialGroup()
                                                .addGroup(panelGeneralAutoresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                                        .addComponent(jLabel7)
                                                        .addGroup(panelGeneralAutoresLayout.createSequentialGroup()
                                                                .addComponent(jLabel5)
                                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                                .addComponent(textoPaginas, javax.swing.GroupLayout.PREFERRED_SIZE, 94, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                                .addGap(35, 35, 35)
                                                                .addComponent(jLabel6)
                                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                                .addComponent(textoAno, javax.swing.GroupLayout.PREFERRED_SIZE, 94, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                                .addGap(42, 42, 42)
                                                                .addComponent(jLabel1)
                                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                                .addComponent(textoId, javax.swing.GroupLayout.PREFERRED_SIZE, 94, javax.swing.GroupLayout.PREFERRED_SIZE)))
                                                .addGap(0, 0, Short.MAX_VALUE)))
                                .addContainerGap())
        );
        panelGeneralAutoresLayout.setVerticalGroup(
                panelGeneralAutoresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(panelGeneralAutoresLayout.createSequentialGroup()
                                .addContainerGap()
                                .addGroup(panelGeneralAutoresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                        .addComponent(textoTitulo, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(jLabel2))
                                .addGap(18, 18, 18)
                                .addGroup(panelGeneralAutoresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                        .addComponent(jLabel3)
                                        .addComponent(textoIsbn, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(jLabel4)
                                        .addComponent(textoEditorial, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGap(18, 18, 18)
                                .addGroup(panelGeneralAutoresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                        .addComponent(jLabel5)
                                        .addComponent(textoPaginas, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(jLabel6)
                                        .addComponent(textoAno, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addComponent(jLabel1)
                                        .addComponent(textoId, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGap(20, 20, 20)
                                .addComponent(jLabel7)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(panelGeneralAutoresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addGroup(panelGeneralAutoresLayout.createSequentialGroup()
                                                .addGroup(panelGeneralAutoresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                        .addComponent(btnNuevoAutor)
                                                        .addComponent(textoNuevoAutor, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                                                .addGap(18, 18, 18)
                                                .addComponent(btnBorrarAutor)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                                .addComponent(btnActualizarLibro))
                                        .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 176, Short.MAX_VALUE))
                                .addContainerGap())
        );

        panelLibro.addTab("Libro", panelGeneralAutores);

        jLabel8.setText("Categorías disponibles");

        jLabel9.setText("Categorías del libro");

        lstRestoCategorias.setModel(new ModeloListaStrings());
        jScrollPane2.setViewportView(lstRestoCategorias);

        lstCategoriasLibro.setModel(new ModeloListaStrings());
        jScrollPane3.setViewportView(lstCategoriasLibro);

        btnSiAsignarCategoria.setIcon(new javax.swing.ImageIcon(getClass().getResource("/gui/imagenes/flechaD.jpg"))); // NOI18N
        btnSiAsignarCategoria.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnSiAsignarCategoriaActionPerformed(evt);
            }
        });

        btnNoAsignarCategoria.setIcon(new javax.swing.ImageIcon(getClass().getResource("/gui/imagenes/flechaI.jpg"))); // NOI18N
        btnNoAsignarCategoria.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnNoAsignarCategoriaActionPerformed(evt);
            }
        });

        btnActualizarCategoriasLibro.setText("Actualizar");
        btnActualizarCategoriasLibro.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnActualizarCategoriasLibroActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout panelCategoriasLayout = new javax.swing.GroupLayout(panelCategorias);
        panelCategorias.setLayout(panelCategoriasLayout);
        panelCategoriasLayout.setHorizontalGroup(
                panelCategoriasLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(panelCategoriasLayout.createSequentialGroup()
                                .addGroup(panelCategoriasLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addGroup(panelCategoriasLayout.createSequentialGroup()
                                                .addGap(25, 25, 25)
                                                .addComponent(jLabel8))
                                        .addGroup(panelCategoriasLayout.createSequentialGroup()
                                                .addContainerGap()
                                                .addComponent(jScrollPane2, javax.swing.GroupLayout.DEFAULT_SIZE, 341, Short.MAX_VALUE)))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addGroup(panelCategoriasLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addGroup(panelCategoriasLayout.createSequentialGroup()
                                                .addGroup(panelCategoriasLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                                        .addComponent(btnSiAsignarCategoria, 0, 0, Short.MAX_VALUE)
                                                        .addComponent(btnNoAsignarCategoria, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                                .addComponent(jScrollPane3, javax.swing.GroupLayout.PREFERRED_SIZE, 195, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addContainerGap())
                                        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, panelCategoriasLayout.createSequentialGroup()
                                                .addComponent(jLabel9)
                                                .addGap(65, 65, 65))))
                        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, panelCategoriasLayout.createSequentialGroup()
                                .addContainerGap(517, Short.MAX_VALUE)
                                .addComponent(btnActualizarCategoriasLibro)
                                .addContainerGap())
        );
        panelCategoriasLayout.setVerticalGroup(
                panelCategoriasLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, panelCategoriasLayout.createSequentialGroup()
                                .addGroup(panelCategoriasLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                        .addGroup(javax.swing.GroupLayout.Alignment.LEADING, panelCategoriasLayout.createSequentialGroup()
                                                .addGap(58, 58, 58)
                                                .addComponent(btnSiAsignarCategoria, javax.swing.GroupLayout.PREFERRED_SIZE, 26, javax.swing.GroupLayout.PREFERRED_SIZE)
                                                .addGap(18, 18, 18)
                                                .addComponent(btnNoAsignarCategoria, javax.swing.GroupLayout.PREFERRED_SIZE, 27, javax.swing.GroupLayout.PREFERRED_SIZE))
                                        .addGroup(javax.swing.GroupLayout.Alignment.LEADING, panelCategoriasLayout.createSequentialGroup()
                                                .addContainerGap()
                                                .addGroup(panelCategoriasLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                        .addComponent(jLabel8)
                                                        .addComponent(jLabel9))
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                                .addGroup(panelCategoriasLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                                        .addComponent(jScrollPane2)
                                                        .addComponent(jScrollPane3, javax.swing.GroupLayout.DEFAULT_SIZE, 255, Short.MAX_VALUE))))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(btnActualizarCategoriasLibro)
                                .addContainerGap())
        );

        panelLibro.addTab("Categorías", panelCategorias);

        tablaEjemplares.setModel(new ModeloTablaEjemplares());
        tablaEjemplares.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                tablaEjemplaresMouseClicked(evt);
            }
        });

        jScrollPane4.setViewportView(tablaEjemplares);

        btnBorrarEjemplar.setText("Borrar");
//        btnBorrarEjemplar.setEnabled(false);

        btnBorrarEjemplar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnBorrarEjemplarActionPerformed(evt);
            }
        });

        btnNuevoEjemplar.setText("Nuevo");
        btnNuevoEjemplar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnNuevoEjemplarActionPerformed(evt);
            }
        });

        btnActualizarEjemplaresLibro.setText("Actualizar");
        btnActualizarEjemplaresLibro.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnActualizarEjemplaresLibroActionPerformed(evt);
            }
        });

        btnPrestarLibro.setText("Prestar");
//        btnPrestarLibro.setEnabled(false);
        btnPrestarLibro.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnPrestarLibroActionPerformed(evt);
            }
        });

        btnDevolverLibro.setText("Devolver");
//        btnDevolverLibro.setEnabled(false);
        btnDevolverLibro.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnDevolverLibroActionPerformed(evt);
            }
        });

        btnRefrescarEjemplares.setIcon(new javax.swing.ImageIcon(getClass().getResource("/gui/imagenes/recargar.jpg"))); // NOI18N
        btnRefrescarEjemplares.setBorder(javax.swing.BorderFactory.createBevelBorder(javax.swing.border.BevelBorder.RAISED));
        btnRefrescarEjemplares.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mousePressed(java.awt.event.MouseEvent evt) {
                btnRefrescarEjemplaresMousePressed(evt);
            }

            public void mouseReleased(java.awt.event.MouseEvent evt) {
                btnRefrescarEjemplaresMouseReleased(evt);
            }
        });
        btnRefrescarEjemplares.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnRefrescarEjemplaresActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout panelEjemplaresLayout = new javax.swing.GroupLayout(panelEjemplares);
        panelEjemplares.setLayout(panelEjemplaresLayout);
        panelEjemplaresLayout.setHorizontalGroup(
                panelEjemplaresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(panelEjemplaresLayout.createSequentialGroup()
                                .addGroup(panelEjemplaresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                        .addGroup(panelEjemplaresLayout.createSequentialGroup()
                                                .addContainerGap()
                                                .addComponent(btnNuevoEjemplar)
                                                .addGap(18, 18, 18)
                                                .addComponent(btnBorrarEjemplar)
                                                .addGap(59, 59, 59)
                                                .addComponent(btnPrestarLibro)
                                                .addGap(18, 18, 18)
                                                .addComponent(btnDevolverLibro)
                                                .addGap(68, 68, 68)
                                                .addComponent(btnActualizarEjemplaresLibro)
                                                .addGap(9, 9, 9))
                                        .addComponent(jScrollPane4, javax.swing.GroupLayout.PREFERRED_SIZE, 577, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(btnRefrescarEjemplares))
        );
        panelEjemplaresLayout.setVerticalGroup(
                panelEjemplaresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, panelEjemplaresLayout.createSequentialGroup()
                                .addGroup(panelEjemplaresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addGroup(panelEjemplaresLayout.createSequentialGroup()
                                                .addComponent(jScrollPane4, javax.swing.GroupLayout.DEFAULT_SIZE, 277, Short.MAX_VALUE)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED))
                                        .addGroup(panelEjemplaresLayout.createSequentialGroup()
                                                .addGap(104, 104, 104)
                                                .addComponent(btnRefrescarEjemplares)
                                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                                .addGroup(panelEjemplaresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addGroup(panelEjemplaresLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                                .addComponent(btnNuevoEjemplar)
                                                .addComponent(btnBorrarEjemplar)
                                                .addComponent(btnPrestarLibro)
                                                .addComponent(btnDevolverLibro))
                                        .addComponent(btnActualizarEjemplaresLibro))
                                .addGap(24, 24, 24))
        );

        btnPrestarLibro.getAccessibleContext().setAccessibleDescription("Abre el menu de prestamo de ejemplares");
        btnDevolverLibro.getAccessibleContext().setAccessibleDescription("Hace efectiva la devolución de un ejemplar en la fecha actual");
        btnRefrescarEjemplares.getAccessibleContext().setAccessibleName("RefrescarTablaEjemplares");
        btnRefrescarEjemplares.getAccessibleContext().setAccessibleDescription("Muestra la información más actualizada en la tabla de ejemplares");

        panelLibro.addTab("Ejemplares", panelEjemplares);

        btnBorrarLibro.setText("Borrar Libro");
        btnBorrarLibro.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnBorrarLibroActionPerformed(evt);
            }
        });

        btnSalir.setText("Salír");
        btnSalir.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnSalirActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
                layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addContainerGap()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addGroup(layout.createSequentialGroup()
                                                .addComponent(btnBorrarLibro)
                                                .addGap(394, 394, 394)
                                                .addComponent(btnSalir)
                                                .addGap(0, 0, Short.MAX_VALUE))
                                        .addComponent(panelLibro))
                                .addContainerGap())
        );
        layout.setVerticalGroup(
                layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(layout.createSequentialGroup()
                                .addComponent(panelLibro, javax.swing.GroupLayout.PREFERRED_SIZE, 371, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addGap(12, 12, 12)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                        .addComponent(btnBorrarLibro)
                                        .addComponent(btnSalir))
                                .addContainerGap(8, Short.MAX_VALUE))
        );

        panelLibro.getAccessibleContext().setAccessibleName("Libro");

        gestionarBotonesPrestamos();

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void btnSalirActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnSalirActionPerformed
        // TODO add your handling code here:
        padre.buscarLibros();
        this.dispose();
    }//GEN-LAST:event_btnSalirActionPerformed

    private void btnNuevoAutorActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnNuevoAutorActionPerformed
        // TODO add your handling code here:
        ModeloListaStrings ma = (ModeloListaStrings) lstAutores.getModel();

        if ((textoNuevoAutor.getText() == null) || (textoNuevoAutor.getText().isEmpty())) // Caso en el que el campo de texto esté vacío
        {
            fa.muestraExcepcion("El autor no puede estar vacío");
            return; // Primera salida forzada
        }
        if (ma.getElementos().contains(textoNuevoAutor.getText())) {
            fa.muestraExcepcion("El autor ya existe");
            return; // Segunda salida forzada
        }

        ma.nuevoElemento(textoNuevoAutor.getText());
        lstAutores.setSelectedIndex(ma.getSize() - 1);
        btnBorrarAutor.setEnabled(true);
        return;// Todo bien, no hay nada más que hacer
    }//GEN-LAST:event_btnNuevoAutorActionPerformed

    private void btnBorrarAutorActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnBorrarAutorActionPerformed
        // TODO add your handling code here:
        ModeloListaStrings ma;
        ma = (ModeloListaStrings) lstAutores.getModel();

        ma.borrarElemento(lstAutores.getSelectedIndex());
        if (ma.getSize() == 0) {
            btnBorrarAutor.setEnabled(false);
        }
        else {
            lstAutores.setSelectedIndex(0);
        }
    }//GEN-LAST:event_btnBorrarAutorActionPerformed

    private void btnSiAsignarCategoriaActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnSiAsignarCategoriaActionPerformed
        // TODO add your handling code here:
        ModeloListaStrings mRC;
        ModeloListaStrings mC;

        mRC = (ModeloListaStrings) lstRestoCategorias.getModel();
        mC = (ModeloListaStrings) lstCategoriasLibro.getModel();
        mC.nuevoElemento(mRC.getElementAt(lstRestoCategorias.getSelectedIndex()));
        mRC.borrarElemento(lstRestoCategorias.getSelectedIndex());
        if (mRC.getSize() == 0) {
            btnSiAsignarCategoria.setEnabled(false);
        }
        else {
            lstRestoCategorias.setSelectedIndex(0);
        }
        lstCategoriasLibro.setSelectedIndex(mC.getSize() - 1);
        btnNoAsignarCategoria.setEnabled(true);
    }//GEN-LAST:event_btnSiAsignarCategoriaActionPerformed

    private void btnNoAsignarCategoriaActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnNoAsignarCategoriaActionPerformed
        // TODO add your handling code here:
        ModeloListaStrings mRC;
        ModeloListaStrings mC;

        mRC = (ModeloListaStrings) lstRestoCategorias.getModel();
        mC = (ModeloListaStrings) lstCategoriasLibro.getModel();
        mRC.nuevoElemento(mC.getElementAt(lstCategoriasLibro.getSelectedIndex()));
        mC.borrarElemento(lstCategoriasLibro.getSelectedIndex());
        if (mC.getSize() == 0) {
            btnNoAsignarCategoria.setEnabled(false);
        }
        else {
            lstCategoriasLibro.setSelectedIndex(0);
        }
        lstRestoCategorias.setSelectedIndex(mRC.getSize() - 1);
        btnSiAsignarCategoria.setEnabled(true);
    }//GEN-LAST:event_btnNoAsignarCategoriaActionPerformed

    private void btnBorrarLibroActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnBorrarLibroActionPerformed

//        if (fa.tieneEjemplares(idLibro)) {
//            fa.muestraExcepcion("No se puede borrar el libro porque tiene ejemplares");
//            return;
//        }

        fa.borrarLibro(idLibro);
        padre.buscarLibros();
        this.dispose();
    }//GEN-LAST:event_btnBorrarLibroActionPerformed

    private void btnActualizarLibroActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnActualizarLibroActionPerformed
        Libro libro = new Libro(idLibro, textoTitulo.getText(), textoIsbn.getText(), textoEditorial.getText(),
                Utilidades.getIntOrNull(textoPaginas.getText()), textoAno.getText());
        ModeloListaStrings ma = (ModeloListaStrings) lstAutores.getModel();
        libro.setAutores(ma.getElementos());
        idLibro = fa.actualizarLibro(libro);
        textoId.setText(idLibro.toString());
        btnActualizarCategoriasLibro.setEnabled(true);
        btnActualizarEjemplaresLibro.setEnabled(true);
        btnBorrarLibro.setEnabled(true);
    }//GEN-LAST:event_btnActualizarLibroActionPerformed

    private void btnActualizarCategoriasLibroActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnActualizarCategoriasLibroActionPerformed
        // TODO add your handling code here:
        ModeloListaStrings ma = (ModeloListaStrings) lstCategoriasLibro.getModel();
        fa.actualizarCategoriasLibro(idLibro, ma.getElementos());
    }//GEN-LAST:event_btnActualizarCategoriasLibroActionPerformed

    private void btnPrestarLibroActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnPrestarLibroActionPerformed
        // TODO add your handling code here:
        /*
        Libro libro = new Libro(idLibro, textoTitulo.getText(), textoIsbn.getText(), textoEditorial.getText(),
                Integer.parseInt(textoPaginas.getText()), textoAno.getText());
        
        int filaSeleccionada = tablaEjemplares.getSelectedRow();
        
        Ejemplar ejemplarAprestar = new Ejemplar(libro,(Integer) tablaEjemplares.getValueAt(filaSeleccionada, 0), (String) tablaEjemplares.getValueAt(filaSeleccionada, 1), (String)tablaEjemplares.getValueAt(filaSeleccionada, 2));
        */


        ModeloTablaEjemplares mTEjemplares = (ModeloTablaEjemplares) tablaEjemplares.getModel();
        Ejemplar ejemplarAprestar = mTEjemplares.obtenerEjemplar(tablaEjemplares.getSelectedRow());

        if (ejemplarAprestar != null) {
            fa.lanzarGestionPrestamos(ejemplarAprestar);
        }

        // ==

        // Refrescamos desde la BD la información que tenemos sobre el libro

        refrescarContenidoEjemplares();

    }//GEN-LAST:event_btnPrestarLibroActionPerformed

    private void btnActualizarEjemplaresLibroActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnActualizarEjemplaresLibroActionPerformed

        // Actualizamos la BD con la información del los ejemplares, tal cual está ahora mismo en pantalla

        ModeloTablaEjemplares mTEjemplares = (ModeloTablaEjemplares) tablaEjemplares.getModel();

        // Itero por las fechas
        for (int ejemplarActual = 0; ejemplarActual < mTEjemplares.getRowCount(); ejemplarActual++) {
            // Si la fecha de adquisición es nula, la pongo a la fecha actual
            String fechaAdquisicion = (String) /*Casteo de Object a String (la tabla no sabe el tipo)*/ mTEjemplares.getValueAt(ejemplarActual, 2);
            if(Integer.decode(fechaAdquisicion.substring(0,4))>2100)
            {
                fa.muestraExcepcion("La fecha de adquisición no puede ser mayor a 2100. Los cambios no se han guardado");
                return;
            }else if(Integer.decode(fechaAdquisicion.substring(0,4)) < 1900)
            {
                fa.muestraExcepcion("La fecha de adquisición no puede ser menor a 1900. Los cambios no se han guardado");
                return;
            }
        }

        fa.actualizarEjemplaresLibro(idLibro, mTEjemplares.getFilas(), ejemplaresBorrados);

        // ==

        // Refrescamos desde la BD la información que tenemos sobre el libro

        refrescarContenidoEjemplares();

    }//GEN-LAST:event_btnActualizarEjemplaresLibroActionPerformed

    private void btnNuevoEjemplarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnNuevoEjemplarActionPerformed
        // TODO add your handling code here:
        ModeloTablaEjemplares mTEjemplares = (ModeloTablaEjemplares) tablaEjemplares.getModel();
        // TODO: Revisar este caso
        Ejemplar ejemplar = new Ejemplar(null, null, null, null, null);
        mTEjemplares.nuevoEjemplar(ejemplar);

        tablaEjemplares.setRowSelectionInterval(mTEjemplares.getRowCount() - 1, mTEjemplares.getRowCount() - 1);

//        btnBorrarEjemplar.setEnabled(true);
        gestionarBotonesPrestamos();

    }//GEN-LAST:event_btnNuevoEjemplarActionPerformed

    private void btnBorrarEjemplarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnBorrarEjemplarActionPerformed
        // TODO add your handling code here:
        ModeloTablaEjemplares mTEjemplares = (ModeloTablaEjemplares) tablaEjemplares.getModel();
        if (mTEjemplares.obtenerEjemplar(tablaEjemplares.getSelectedRow()).getNumEjemplar() != null) {
            ejemplaresBorrados.add(mTEjemplares.obtenerEjemplar(tablaEjemplares.getSelectedRow()).getNumEjemplar());
        }

        mTEjemplares.borrarEjemplar(tablaEjemplares.getSelectedRow());

        if (mTEjemplares.getRowCount() > 0) {
            tablaEjemplares.setRowSelectionInterval(0, 0);
        }
//        else {
//            btnBorrarEjemplar.setEnabled(false);
//        }

        gestionarBotonesPrestamos();

    }//GEN-LAST:event_btnBorrarEjemplarActionPerformed

    private void btnDevolverLibroActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnDevolverLibroActionPerformed
        // TODO add your handling code here:
        ModeloTablaEjemplares mtPrestamos = (ModeloTablaEjemplares) tablaEjemplares.getModel();
        int id_libro = this.idLibro;
        int num_ejemplar = (Integer) mtPrestamos.getValueAt(tablaEjemplares.getSelectedRow(), 0);

        fa.devolverEjemplar(id_libro, num_ejemplar);
    }//GEN-LAST:event_btnDevolverLibroActionPerformed

    private void btnRefrescarEjemplaresActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnRefrescarEjemplaresActionPerformed
        refrescarContenidoEjemplares();

    }//GEN-LAST:event_btnRefrescarEjemplaresActionPerformed

    private void refrescarContenidoEjemplares() {

        Libro libro = fa.consultarLibro(this.idLibro);

        // --

        List<Ejemplar> ejemplares = libro.getEjemplares();

        // --

//        Map<Integer, Prestamo> estadoPrestamoEjemplares = new HashMap<>();
//        for (Ejemplar ejemplarActual : ejemplares) {
//            estadoPrestamoEjemplares.put(ejemplarActual.getNumEjemplar(), fa.consultarPrestamoActivoParaEjemplar(ejemplarActual.getLibro().getIdLibro(), ejemplarActual.getNumEjemplar()));
//        }

        // --

        ModeloTablaEjemplares mTEjemplares = (ModeloTablaEjemplares) tablaEjemplares.getModel();

        // --

//        mTEjemplares.setFilas(ejemplares, estadoPrestamoEjemplares);
        mTEjemplares.setFilas(ejemplares);

        // --

        if (mTEjemplares.getRowCount() > 0) {
            tablaEjemplares.setRowSelectionInterval(0, 0);
//            btnBorrarEjemplar.setEnabled(true);
        }
//        else {
//            btnBorrarEjemplar.setEnabled(false);
//            btnPrestarLibro.setEnabled(false);
//            btnDevolverLibro.setEnabled(false);
//        }

        gestionarBotonesPrestamos();

        // --

    }

    private void gestionarBotonesPrestamos() {
        ModeloTablaEjemplares mTEjemplares = (ModeloTablaEjemplares) tablaEjemplares.getModel();

//        Ejemplar ejemplarSeleccionado = mTEjemplares.obtenerEjemplar(tablaEjemplares.getSelectedRow());


        if (!tablaEjemplares.getSelectionModel().isSelectionEmpty()) {
            int selectedRow = tablaEjemplares.getSelectedRow();

            // if (estadoPrestamoEjemplares.get(ejemplarSeleccionado.getNumEjemplar()) != null){
            if (mTEjemplares.tienePrestamosActivos(selectedRow)) {
                // Tiene un préstamo activo
                btnPrestarLibro.setEnabled(false);
                btnDevolverLibro.setEnabled(true);
                btnBorrarEjemplar.setEnabled(false);
            }
            else {
                // NO tiene un préstamo activo
                btnPrestarLibro.setEnabled(true);
                btnDevolverLibro.setEnabled(false);
                btnBorrarEjemplar.setEnabled(true);
            }

            // btnDevolverLibro.setEnabled(true);
        }
        else {
            btnPrestarLibro.setEnabled(false);
            btnDevolverLibro.setEnabled(false);
            btnBorrarEjemplar.setEnabled(false);
        }
    }

    private void btnRefrescarEjemplaresMousePressed(java.awt.event.MouseEvent evt) {
        // TODO add your handling code here:
        btnRefrescarEjemplares.setBackground(Color.DARK_GRAY);
        btnRefrescarEjemplares.setForeground(Color.DARK_GRAY);
    }


    private void btnRefrescarEjemplaresMouseReleased(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_btnRefrescarEjemplaresMousePressed
        // TODO add your handling code here:
        btnRefrescarEjemplares.setBackground(Color.lightGray);
        btnRefrescarEjemplares.setForeground(Color.lightGray);
    }//GEN-LAST:event_btnRefrescarEjemplaresMousePressed

    private void tablaEjemplaresMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_tablaEjemplaresMouseClicked
        gestionarBotonesPrestamos();
        /*
        btnPrestarLibro.setEnabled(true);
        btnDevolverLibro.setEnabled(true);
        btnBorrarEjemplar.setEnabled(true);
        */
    }//GEN-LAST:event_tablaEjemplaresMouseClicked


    /**
     * @param args the command line arguments
     */

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnActualizarCategoriasLibro;
    private javax.swing.JButton btnActualizarEjemplaresLibro;
    private javax.swing.JButton btnActualizarLibro;
    private javax.swing.JButton btnBorrarAutor;
    private javax.swing.JButton btnBorrarEjemplar;
    private javax.swing.JButton btnBorrarLibro;
    private javax.swing.JButton btnSiAsignarCategoria;
    private javax.swing.JButton btnDevolverLibro;
    private javax.swing.JButton btnNoAsignarCategoria;
    private javax.swing.JButton btnNuevoAutor;
    private javax.swing.JButton btnNuevoEjemplar;
    private javax.swing.JButton btnPrestarLibro;
    private javax.swing.JButton btnRefrescarEjemplares;
    private javax.swing.JButton btnSalir;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JLabel jLabel8;
    private javax.swing.JLabel jLabel9;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JScrollPane jScrollPane3;
    private javax.swing.JScrollPane jScrollPane4;
    private javax.swing.JList lstAutores;
    private javax.swing.JList lstCategoriasLibro;
    private javax.swing.JList lstRestoCategorias;
    private javax.swing.JPanel panelCategorias;
    private javax.swing.JPanel panelEjemplares;
    private javax.swing.JPanel panelGeneralAutores;
    private javax.swing.JTabbedPane panelLibro;
    private javax.swing.JTable tablaEjemplares;
    private javax.swing.JTextField textoAno;
    private javax.swing.JTextField textoEditorial;
    private javax.swing.JTextField textoId;
    private javax.swing.JTextField textoIsbn;
    private javax.swing.JTextField textoNuevoAutor;
    private javax.swing.JTextField textoPaginas;
    private javax.swing.JTextField textoTitulo;
    // End of variables declaration//GEN-END:variables

}
