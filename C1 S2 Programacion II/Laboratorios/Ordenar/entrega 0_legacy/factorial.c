int factorial(int n) {
    int valor = 1;
    if (n >= 0) {
        int i;
        //for (i = 0; i <= n; i++) //si i=0 valor será siempre 0
        for (i = 1; i <= n; i++)
            valor = valor * i;
        
    }
    return valor;
}

