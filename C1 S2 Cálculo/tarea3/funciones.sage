def gauss_vs_inv():
    N  = [200,400..2000]
    ti = []
    tg = []
    for n in N:
        print('Working with dimension ',n)
        A  = matrix.random(RDF, n)
        b  = vector(RDF, n*[1])
        #gauss
        t0 = cputime()
        x  = A\b
        tg.append(cputime()-t0)
        #inversa
        t0 = cputime()
        x  = ~A*b
        ti.append(cputime()-t0)
    p = line(zip(N, tg), color='blue',  legend_label='Gauss')
    q = line(zip(N, ti), color='green', legend_label='Inversa')
    show(p+q)

def chol(A):
    if A.is_symmetric() and A.is_positive_definite():
        return A.cholesky()
    else:
        raise RuntimeError('A matriz non é simétrica ou definida positiva')
