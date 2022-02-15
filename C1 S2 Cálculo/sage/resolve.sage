def dicotomia(f, a, b, xtol=1e-12, rtol=1e-14):
    """DICOTOMIA    Calculo de raices por el metodo de dicotomia.

    """
    r = a
    k = 0
    v = []
    I = []
    # comprobacions previas
    if abs(f(a)).n() < rtol:
        r = a.n(); return r,k,v,I
    elif abs(f(b)).n() < rtol:
        r = b.n(); return r,k,v,I
    elif (f(a)*f(b)).n() > 0:
        raise RuntimeError('Mismo signo en ambos extremos!')
    # calculo iterativo
    while abs(b - a) > xtol:
        r = (a + b).n() / 2
        k = k + 1
        v.append(r)
        I.append((a,b))
        if abs(f(r)).n() < rtol:
            return r,k,v,I
        elif (f(a)*f(r)).n() < 0:
            b = r
        else:
            a = r
    return r,k,v,I

def newton(f, df, x0, xtol=1e-12, rtol=1e-14, M=100):
    """NEWTON    Calculo de raices por el metodo de Newton.
    """
    v = [x0.n()]
    for k in range(M):
        dfx = df(v[k]).n()
        if abs(dfx) < rtol:
            raise RuntimeError('La derivada de la funcion se anula!')
        r = (v[k] - f(v[k]) / dfx).n()
        v.append(r)
        # test de parada
        if abs(r-v[k]) < xtol or abs(f(r)).n() < rtol:
            return r, len(v), v
    raise RuntimeError('Se excedio el numero maximo de iteraciones.')   

def debuxa_dicotomia(f, a, b, xtol=1e-12, rtol=1e-14):
    """DEBUXA_DICOTOMIA    Visualizacion del metodo de dicotomia.
    """
    r,k,v,I = dicotomia(f, a, b, xtol, rtol)
    # grafica
    p = plot(f, a, b) + point(zip(v,[0]*len(v)), color='green')
    h = (p.ymax() - p.ymin())/(1.5*k)
    show(sum(line([(a,h*i),    (b,h*i)],     color='green') + \
             line([(a,h*i-h/4),(a,h*i+h/4)], color='green') + \
             line([(b,h*i-h/4),(b,h*i+h/4)], color='green')   \
             for i, (a,b) in enumerate(I)) + p, xmin=a, xmax=b)
    # iterantes
    for i in range(len(v)):
        print('Iterante ' + str(i) + ': ' + str(v[i]) + \
        '; lonxitude do intervalo: ' + str((b-a)*.5^i))

def debuxa_newton(f, df, x0, a, b, xtol=1e-6, rtol=1e-6, M=100, return_coef=False):
    """DEBUXA_NEWTON    Visualizacion del metodo de Newton.
    """
    r,k,v = newton(f, df, x0, xtol, rtol, M)
    # grafica
    show(plot(f, a, b) + point(zip(v,[0]*len(v)), color='green') +\
         sum(line([(v[i],0),(v[i],f(v[i]))], color='green',linestyle='--') \
             for i in range(k)) + \
         sum(line([(v[i-1],f(v[i-1])), (v[i],0)], color='green') \
             for i in range(1,k)), xmin=a, xmax=b)
    # iterantes
    raiz = find_root(f, a, b, xtol=9.e-16, rtol=9.e-16)
    coef = []
    for i in range(1,len(v)):
        coef.append( abs(raiz - v[i]) / (raiz - v[i-1])^2 )
        print('Iterante ' + str(i) + ': ' + str(v[i]) + \
        '; coeficiente da orde de conv.: ' + str(coef[-1]))
    if return_coef:
        return coef
