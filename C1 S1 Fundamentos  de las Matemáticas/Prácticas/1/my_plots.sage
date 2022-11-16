def plotNsave(f, a, b, file):
    """
    Aqui se pon a documentacion da funcion.
    Esta informacion mostrase ao escribir plotNsave? ou help(plotNsave).
    """
    p = plot(f, (a, b))
    show(p)
    p.save(file)